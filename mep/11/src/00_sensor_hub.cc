#include <arpa/inet.h>
#include <netinet/in.h>
#include <poll.h>
#include <sys/socket.h>
#include <unistd.h>

#include <atomic>
#include <chrono>
#include <cstdio>
#include <cstring>
#include <mutex>
#include <thread>
#include <vector>

#include "dht11.hpp"
#include "gpio_helper.hpp"
#include "hcsr04.hpp"
#include "mcp3008.hpp"
#include "signal_stop.hpp"

namespace {
constexpr const char* kChip = "gpiochip0";
constexpr const char* kConsumer = "mep-lab06";
constexpr const char* kSpiDev = "/dev/spidev0.0";
constexpr unsigned int kDhtPin = 4;
constexpr unsigned int kTrigPin = 23;
constexpr unsigned int kEchoPin = 24;
constexpr unsigned int kCdsChannel = 0;
constexpr float kVref = 3.3f;        // MCP3008 reference, as in lab 04
constexpr float kDarkBelowV = 0.5f;  // the CdS ladder, identical to lab 04
constexpr float kShadedBelowV = 1.5f;
constexpr float kBrightBelowV = 2.5f;
constexpr float kSpeedOfSoundCmPerUs = 0.0343f;  // about 20 C
constexpr long kDhtMinIntervalUs = 2000000;  // the DHT11 sets the slowest pace
constexpr int kCollectIntervalMs = 500;
constexpr int kPort = 8080;
constexpr int kAcceptTimeoutMs = 300;  // so Ctrl-C is noticed while idle
}  // namespace

// One reading channel. The collector loop never learns what is behind it,
// which is the whole point: adding a sensor does not change the loop.
class Sensor {
 public:
  virtual ~Sensor() {}
  virtual bool Read(float* out) = 0;
  virtual const char* name() const = 0;
  virtual const char* unit() const = 0;
  // A channel may name its own state, which the dashboard shows beside the
  // number. Returning nullptr means the number speaks for itself.
  virtual const char* Describe(float value) const {
    (void) value;
    return nullptr;
  }
};

// The DHT11 gives two numbers from one conversion, so the device is shared
// and each channel is a thin view onto it.
class Dht11Temperature : public Sensor {
 public:
  explicit Dht11Temperature(Dht11Device* device) : device_(device) {}
  bool Read(float* out) override {
    if (!device_->Refresh(kDhtMinIntervalUs)) return false;
    *out = static_cast<float>(device_->temperature());
    return true;
  }
  const char* name() const override { return "temperature"; }
  const char* unit() const override { return "C"; }

 private:
  Dht11Device* device_;
};

class Dht11Humidity : public Sensor {
 public:
  explicit Dht11Humidity(Dht11Device* device) : device_(device) {}
  bool Read(float* out) override {
    if (!device_->Refresh(kDhtMinIntervalUs)) return false;
    *out = static_cast<float>(device_->humidity());
    return true;
  }
  const char* name() const override { return "humidity"; }
  const char* unit() const override { return "%"; }

 private:
  Dht11Device* device_;
};

class LightSensor : public Sensor {
 public:
  explicit LightSensor(const Mcp3008Device* adc) : adc_(adc) {}
  bool Read(float* out) override {
    const int raw = adc_->ReadChannel(kCdsChannel);
    if (raw < 0) return false;
    *out = (static_cast<float>(raw) / Mcp3008Device::kAdcMax) * kVref;
    return true;
  }
  const char* name() const override { return "light"; }
  const char* unit() const override { return "V"; }
  // A bare voltage means nothing to a reader, so the same ladder as lab 04
  // names the room and the voltage stays beside it as the evidence.
  const char* Describe(float volts) const override {
    if (volts < 0.0f) return "?";
    if (volts < kDarkBelowV) return "dark";
    if (volts < kShadedBelowV) return "shaded";
    if (volts < kBrightBelowV) return "bright";
    return "very bright";
  }

 private:
  const Mcp3008Device* adc_;
};

class DistanceSensor : public Sensor {
 public:
  explicit DistanceSensor(Hcsr04Device* sonar) : sonar_(sonar), error_(0) {}
  bool Read(float* out) override {
    const long echo_us = sonar_->MeasureEchoUs();
    error_ = echo_us < 0 ? echo_us : 0;
    if (echo_us < 0) return false;
    *out = (static_cast<float>(echo_us) * kSpeedOfSoundCmPerUs) / 2.0f;
    return true;
  }
  const char* name() const override { return "distance"; }
  const char* unit() const override { return "cm"; }
  // A bare "--" hides which wire is wrong, so the reason travels with it.
  const char* Describe(float value) const override {
    (void) value;
    const long code = error_;
    if (code == 0) return nullptr;
    if (code == Hcsr04Device::kErrorStuckHigh) return "ECHO stuck HIGH";
    if (code == Hcsr04Device::kErrorNoStart) return "no echo pulse";
    if (code == Hcsr04Device::kErrorNoEnd) return "out of range";
    return "GPIO call failed";
  }

 private:
  Hcsr04Device* sonar_;
  // Written by the collector thread, read by the web thread. One scalar that
  // stands alone, which is exactly the case std::atomic does cover.
  std::atomic<long> error_;
};

// The collector thread writes this and the web thread reads it, so every
// access is under the mutex. std::atomic would not do here: the fields must
// change together or a client could see a temperature from one sweep beside
// a distance from the next.
class SharedState {
 public:
  bool Replace(const float* values, const bool* valid, int count) {
    if (values == nullptr || valid == nullptr || count < 0 ||
        count > kMaxChannels) {
      return false;
    }
    std::lock_guard<std::mutex> guard(mutex_);
    for (int i = 0; i < count; ++i) {
      values_[i] = values[i];
      valid_[i] = valid[i];
      if (valid[i]) ++updates_;
    }
    return true;
  }

  bool Snapshot(float* values, bool* valid, long* updates) const {
    std::lock_guard<std::mutex> guard(mutex_);
    for (int i = 0; i < kMaxChannels; ++i) {
      values[i] = values_[i];
      valid[i] = valid_[i];
    }
    *updates = updates_;
    return true;
  }

  static const int kMaxChannels = 8;

 private:
  mutable std::mutex mutex_;
  float values_[kMaxChannels] = {0.0f};
  bool valid_[kMaxChannels] = {false};
  long updates_ = 0;
};

// One sensor failing must not stop the sweep: a disconnected DHT11 should
// leave the other readings live rather than blanking the dashboard.
bool CollectOnce(const std::vector<Sensor*>& sensors, SharedState* state) {
  if (state == nullptr || sensors.size() > SharedState::kMaxChannels) {
    return false;
  }
  float values[SharedState::kMaxChannels] = {0.0f};
  bool valid[SharedState::kMaxChannels] = {false};
  for (size_t i = 0; i < sensors.size(); ++i) {
    valid[i] = sensors[i]->Read(&values[i]);
  }
  return state->Replace(values, valid, static_cast<int>(sensors.size()));
}

int BuildJson(char* out, size_t size, const std::vector<Sensor*>& sensors,
              const float* values, const bool* valid, long updates) {
  int n = std::snprintf(out, size, "{\"updates\":%ld,\"sensors\":[", updates);
  for (size_t i = 0;
       i < sensors.size() && n > 0 && static_cast<size_t>(n) < size; ++i) {
    const char* text = sensors[i]->Describe(values[i]);
    n +=
        std::snprintf(out + n, size - static_cast<size_t>(n),
                      "%s{\"name\":\"%s\",\"unit\":\"%s\",\"value\":%.2f,"
                      "\"text\":\"%s\",\"ok\":%s}",
                      i == 0 ? "" : ",", sensors[i]->name(), sensors[i]->unit(),
                      static_cast<double>(values[i]),
                      text == nullptr ? "" : text, valid[i] ? "true" : "false");
  }
  if (n > 0 && static_cast<size_t>(n) < size) {
    n += std::snprintf(out + n, size - static_cast<size_t>(n), "]}");
  }
  // snprintf reports the length it WANTED, not what it wrote. Returning that
  // unchecked would put a Content-Length on the wire longer than the buffer,
  // and the send loop would walk off the end of it.
  if (n < 0 || static_cast<size_t>(n) >= size) return -1;
  return n;
}

const char* kDashboard =
    "<!doctype html><meta charset=utf-8><title>MEP Sensor Hub</title>"
    "<style>body{font-family:sans-serif;margin:2rem}"
    "td{padding:.4rem 1rem;border-bottom:1px solid #ddd}"
    ".bad{color:#c0392b}</style>"
    "<h1>Sensor Hub</h1><table id=t></table>"
    "<script>setInterval(async()=>{"
    "const r=await(await fetch('/api')).json();"
    "document.getElementById('t').innerHTML=r.sensors.map(s=>"
    "`<tr><td>${s.name}</td><td class=${s.ok?'':'bad'}>"
    "${s.ok?(s.text?`${s.text} (${s.value.toFixed(2)} ${s.unit})`"
    ":`${s.value.toFixed(2)} ${s.unit}`):(s.text||'--')}</td></tr>`).join('');"
    "},1000)</script>";

bool SendAll(int fd, const char* data, size_t size) {
  size_t sent = 0;
  while (sent < size) {
    const ssize_t n = ::write(fd, data + sent, size - sent);
    if (n <= 0) return false;
    sent += static_cast<size_t>(n);
  }
  return true;
}

bool ServeClient(int fd, const std::vector<Sensor*>& sensors,
                 const SharedState& state) {
  char request[512];
  const ssize_t got = ::read(fd, request, sizeof(request) - 1);
  if (got <= 0) return false;
  request[got] = '\0';

  char body[2048];
  const char* type = "text/html";
  int length = 0;
  if (std::strncmp(request, "GET /api", 8) == 0) {
    float values[SharedState::kMaxChannels];
    bool valid[SharedState::kMaxChannels];
    long updates = 0;
    if (!state.Snapshot(values, valid, &updates)) return false;
    length = BuildJson(body, sizeof(body), sensors, values, valid, updates);
    type = "application/json";
  } else {
    length = std::snprintf(body, sizeof(body), "%s", kDashboard);
  }
  if (length < 0 || static_cast<size_t>(length) >= sizeof(body)) return false;

  char head[256];
  const int head_len = std::snprintf(
      head, sizeof(head),
      "HTTP/1.1 200 OK\r\nContent-Type: %s\r\nContent-Length: %d\r\n"
      "Connection: close\r\n\r\n",
      type, length);
  if (head_len < 0 || static_cast<size_t>(head_len) >= sizeof(head)) {
    return false;
  }
  return SendAll(fd, head, static_cast<size_t>(head_len)) &&
         SendAll(fd, body, static_cast<size_t>(length));
}

int OpenListener(int port) {
  const int fd = ::socket(AF_INET, SOCK_STREAM, 0);
  if (fd < 0) return -1;
  const int one = 1;
  if (::setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &one, sizeof(one)) < 0) {
    ::close(fd);
    return -1;
  }

  sockaddr_in addr;
  std::memset(&addr, 0, sizeof(addr));
  addr.sin_family = AF_INET;
  addr.sin_addr.s_addr = htonl(INADDR_ANY);
  addr.sin_port = htons(static_cast<uint16_t>(port));
  if (::bind(fd, reinterpret_cast<sockaddr*>(&addr), sizeof(addr)) < 0 ||
      ::listen(fd, 4) < 0) {
    ::close(fd);
    return -1;
  }
  return fd;
}

int AcceptClient(int listener) {
  pollfd descriptor;
  descriptor.fd = listener;
  descriptor.events = POLLIN;
  descriptor.revents = 0;
  const int ready = ::poll(&descriptor, 1, kAcceptTimeoutMs);
  if (ready <= 0 || (descriptor.revents & POLLIN) == 0) return -1;
  return ::accept(listener, nullptr, nullptr);
}

int main() {
  if (!InstallStopHandler()) {
    std::fprintf(stderr, "cannot install the signal handler\n");
    return 1;
  }

  GpioChip chip(kChip);
  if (!chip.ok()) {
    std::fprintf(stderr, "cannot open %s\n", kChip);
    return 1;
  }

  Dht11Device dht(chip, kDhtPin, kConsumer);
  Mcp3008Device adc(kSpiDev);
  Hcsr04Device sonar(0, kTrigPin, kEchoPin);
  if (!adc.ok()) std::fprintf(stderr, "warning: %s unavailable\n", kSpiDev);
  if (!sonar.ok()) std::fprintf(stderr, "warning: sonar lines unavailable\n");

  Dht11Temperature temperature(&dht);
  Dht11Humidity humidity(&dht);
  LightSensor light(&adc);
  DistanceSensor distance(&sonar);
  std::vector<Sensor*> sensors;
  sensors.push_back(&temperature);
  sensors.push_back(&humidity);
  sensors.push_back(&light);
  sensors.push_back(&distance);

  const int listener = OpenListener(kPort);
  if (listener < 0) {
    std::fprintf(stderr, "cannot listen on port %d\n", kPort);
    return 1;
  }

  SharedState state;

  // The sensors are polled twice a second; the web server answers whenever a
  // browser asks. Different rates, so different threads.
  std::thread collector([&sensors, &state]() {
    while (!StopRequested()) {
      CollectOnce(sensors, &state);
      std::this_thread::sleep_for(
          std::chrono::milliseconds(kCollectIntervalMs));
    }
  });

  std::printf("dashboard on http://<pi-address>:%d/  (JSON at /api)\n", kPort);
  std::printf("Ctrl-C to stop\n");
  std::fflush(stdout);

  while (!StopRequested()) {
    const int client = AcceptClient(listener);
    if (client < 0) continue;  // timed out; loop back and re-check the flag
    ServeClient(client, sensors, state);
    ::close(client);
  }

  collector.join();
  if (!sonar.Close()) {
    std::fprintf(stderr, "cannot release the sonar cleanly\n");
    ::close(listener);
    return 1;
  }
  ::close(listener);
  std::printf("stopped\n");
  return 0;
}
