#include <unistd.h>

#include <chrono>
#include <cstdio>
#include <cstring>
#include <mutex>
#include <thread>

#include "http.hpp"
#include "sensors.hpp"
#include "signal_stop.hpp"

namespace {
constexpr int kPort = 8080;
constexpr int kCollectMs = 500;
constexpr int kAcceptTimeoutMs = 300;  // so Ctrl-C is noticed while idle
constexpr int kChannels = 4;
const char* const kNames[kChannels] = {"temperature", "humidity", "light",
                                       "distance"};
const char* const kUnits[kChannels] = {"C", "%", "V", "cm"};
}  // namespace

// The collector thread writes this and the web thread reads it, so every
// access is under the mutex. Per-field atomics would not do: the fields must
// change together, or a client could see values from different collections.
class Snapshot {
 public:
  void Replace(const float* values, const bool* valid) {
    std::lock_guard<std::mutex> guard(mutex_);
    for (int i = 0; i < kChannels; ++i) {
      values_[i] = values[i];
      valid_[i] = valid[i];
    }
  }

  void Read(float* values, bool* valid) const {
    std::lock_guard<std::mutex> guard(mutex_);
    for (int i = 0; i < kChannels; ++i) {
      values[i] = values_[i];
      valid[i] = valid_[i];
    }
  }

 private:
  mutable std::mutex mutex_;
  float values_[kChannels] = {0.0f};
  bool valid_[kChannels] = {false};
};

// One sensor failing must not blank the others, so each result stands alone.
void CollectOnce(Sensors* sensors, Snapshot* out) {
  float values[kChannels] = {0.0f};
  bool valid[kChannels] = {false};  // temp., humid., light, distance
  valid[0] = sensors->ReadDht(&values[0], &values[1]);
  valid[1] = valid[0];  // one conversion carries both numbers
  valid[2] = sensors->ReadLight(&values[2]);
  valid[3] = sensors->ReadDistance(&values[3]);
  out->Replace(values, valid);
}

int BuildJson(char* out, size_t size, const float* values, const bool* valid) {
  int n = std::snprintf(out, size, "{\"sensors\":[");
  for (int i = 0; i < kChannels; ++i) {
    n += std::snprintf(out + n, size - static_cast<size_t>(n),
                       "%s{\"name\":\"%s\",\"unit\":\"%s\",\"value\":%.2f,"
                       "\"ok\":%s}",
                       i == 0 ? "" : ",", kNames[i], kUnits[i],
                       static_cast<double>(values[i]),
                       valid[i] ? "true" : "false");
    if (n <= 0 || static_cast<size_t>(n) >= size) break;
  }
  if (n > 0 && static_cast<size_t>(n) < size)
    n += std::snprintf(out + n, size - static_cast<size_t>(n), "]}");

  // snprintf reports the length it WANTED, so an unchecked return would put a
  // Content-Length on the wire longer than the buffer actually holds.
  return (n < 0 || static_cast<size_t>(n) >= size) ? -1 : n;
}

// Lab 4: the three sensors of lab 3, served over HTTP.
int main() {
  Sensors sensors;
  Http server(kPort);
  if (!InstallStopHandler() || !server.ok()) {
    std::fprintf(stderr, "cannot listen on port %d\n", kPort);
    return 1;
  }

  Snapshot snapshot;
  // Sensors are polled on a fixed period; the browser asks whenever it likes.
  // Different rates, so different threads.
  std::thread collector([&sensors, &snapshot]() {
    while (!StopRequested()) {
      CollectOnce(&sensors, &snapshot);
      std::this_thread::sleep_for(std::chrono::milliseconds(kCollectMs));
    }
  });

  std::printf("dashboard on http://<pi-address>:%d/  (JSON at /api)\n", kPort);
  std::fflush(stdout);
  while (!StopRequested()) {
    const int client = server.Accept(kAcceptTimeoutMs);
    if (client < 0) continue;
    if (Http::Wants(client, "/api")) {
      float values[kChannels];
      bool valid[kChannels];
      char body[1024];
      snapshot.Read(values, valid);
      const int length = BuildJson(body, sizeof(body), values, valid);
      if (length > 0) Http::Send(client, "application/json", body, length);
    } else {
      Http::Send(client, "text/html", kDashboard,
                 static_cast<int>(std::strlen(kDashboard)));
    }
    ::close(client);
  }

  collector.join();
  std::printf("stopped\n");
  return 0;
}
