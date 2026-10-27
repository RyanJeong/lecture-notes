#include <unistd.h>

#include <cstdint>
#include <cstdio>
#include <ctime>

#include "gpio.hpp"
#include "signal_stop.hpp"

namespace {
constexpr unsigned int kDataPin = 4;  // BCM 4, 10k pull-up to 3.3V
constexpr long kTimeoutUs = 200;      // no edge within this: give up
constexpr long kBitThresholdUs = 50;  // a HIGH longer than this is a 1
constexpr int kBitCount = 40;         // 5 bytes
constexpr int kStartLowUs = 20000;    // the host holds the line low 20 ms
constexpr int kIntervalUs = 2000000;  // the datasheet forbids reading faster
}  // namespace

long NowMicros() {
  timespec ts;
  clock_gettime(CLOCK_MONOTONIC, &ts);
  return ts.tv_sec * 1000000L + ts.tv_nsec / 1000L;
}

// Busy-wait until the line reaches `level`; returns how long that took.
long WaitFor(const Gpio& line, int level, long timeout_us) {
  const long start = NowMicros();
  for (;;) {
    const int value = line.Get();
    if (value < 0) return -1;
    const long elapsed = NowMicros() - start;
    if (value == level) return elapsed;
    if (elapsed > timeout_us) return -1;
  }
}

// One conversion: a 20 ms start pulse, a three-edge preamble, then 40 bits
// whose value is carried by how long each HIGH lasts.
bool ReadOnce(Gpio* line, int* humidity, int* temperature) {
  if (!line->Reconfigure(Gpio::kOutputLow)) return false;
  usleep(kStartLowUs);
  if (!line->Reconfigure(Gpio::kInput)) return false;
  if (WaitFor(*line, 0, kTimeoutUs) < 0) return false;
  if (WaitFor(*line, 1, kTimeoutUs) < 0) return false;
  if (WaitFor(*line, 0, kTimeoutUs) < 0) return false;

  std::uint8_t data[5] = {0, 0, 0, 0, 0};
  for (int i = 0; i < kBitCount; ++i) {
    if (WaitFor(*line, 1, kTimeoutUs) < 0) return false;
    const long high_us = WaitFor(*line, 0, kTimeoutUs);
    if (high_us < 0) return false;
    const int bit = high_us > kBitThresholdUs ? 1 : 0;
    data[i / 8] = static_cast<std::uint8_t>((data[i / 8] << 1) | bit);
  }
  // The checksum is the whole of the error detection this sensor offers.
  if (static_cast<std::uint8_t>(data[0] + data[1] + data[2] + data[3]) !=
      data[4]) {
    return false;
  }
  *humidity = data[0];
  *temperature = data[2];
  return true;
}

// Lab 3-A: temperature and humidity over a single bit-banged wire.
int main() {
  Gpio line(kDataPin, Gpio::kInput);
  if (!InstallStopHandler() || !line.ok()) return 1;

  std::printf("DHT11 on GPIO%u. Ctrl-C to stop\n", kDataPin);
  while (!StopRequested()) {
    int humidity = 0;
    int temperature = 0;
    if (ReadOnce(&line, &humidity, &temperature))
      std::printf("%d C  %d %%\n", temperature, humidity);
    else
      std::printf("read failed -- check the pull-up and the 20 ms pulse\n");
    std::fflush(stdout);
    usleep(kIntervalUs);
  }
  return 0;
}
