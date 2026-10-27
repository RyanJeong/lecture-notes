#include <lgpio.h>
#include <unistd.h>

#include <cstdint>
#include <cstdio>

#include "gpio.hpp"
#include "signal_stop.hpp"

namespace {
constexpr int kChipDevice = 0;
constexpr int kTrigPin = 23;  // BCM 23
constexpr int kEchoPin = 24;  // BCM 24, via a 1k/2k divider: 5V module
constexpr unsigned int kBuzzerPin = 18;  // BCM 18, active buzzer
constexpr float kWarnCm = 10.0f;         // closer than this sounds the buzzer
constexpr long kStartTimeoutUs = 60000;
constexpr long kEchoTimeoutUs = 30000;
constexpr float kSpeedCmPerUs = 0.0343f;  // speed of sound at about 20 C
constexpr int kIntervalUs = 500000;
}  // namespace

// lguTimestamp() counts nanoseconds; every timeout here is in microseconds.
long WaitFor(int handle, int gpio, int level, long timeout_us) {
  const std::uint64_t start = lguTimestamp();
  for (;;) {
    const int value = lgGpioRead(handle, gpio);
    if (value < 0) return -1;
    const long elapsed = static_cast<long>((lguTimestamp() - start) / 1000);
    if (value == level) return elapsed;
    if (elapsed > timeout_us) return -1;
  }
}

// Returns the echo pulse width in microseconds, or -1. The trigger is driven
// directly rather than queued, so it cannot drift away from the wait below.
long MeasureEchoUs(int handle) {
  if (lgGpioRead(handle, kEchoPin) != 0) return -1;  // ECHO must rest low
  if (lgGpioWrite(handle, kTrigPin, 1) != LG_OKAY) return -1;
  lguSleep(0.00001);  // 10 us is the minimum trigger the module accepts
  if (lgGpioWrite(handle, kTrigPin, 0) != LG_OKAY) return -1;
  if (WaitFor(handle, kEchoPin, 1, kStartTimeoutUs) < 0) return -1;
  return WaitFor(handle, kEchoPin, 0, kEchoTimeoutUs);
}

// The pulse measures the round trip, so one-way distance is half of it.
float ToCm(long echo_us) {
  return (static_cast<float>(echo_us) * kSpeedCmPerUs) / 2.0f;
}

// Lab 3-C: distance from the time an ultrasonic pulse takes to come back.
int main() {
  const int handle = lgGpiochipOpen(kChipDevice);
  Gpio buzzer(kBuzzerPin, Gpio::kOutputLow);
  if (handle < 0 || !buzzer.ok() || !InstallStopHandler()) return 1;
  if (lgGpioClaimOutput(handle, 0, kTrigPin, 0) != LG_OKAY ||
      lgGpioClaimInput(handle, 0, kEchoPin) != LG_OKAY) {
    std::fprintf(stderr, "cannot claim GPIO%d/%d\n", kTrigPin, kEchoPin);
    return 1;
  }

  std::printf("TRIG=GPIO%d ECHO=GPIO%d buzzer=GPIO%u. Ctrl-C to stop\n",
              kTrigPin, kEchoPin, kBuzzerPin);
  while (!StopRequested()) {
    const long echo_us = MeasureEchoUs(handle);
    // An active buzzer sounds whenever the line is high, so the warning is a
    // single conditional write -- no waveform needed.
    const bool warn = echo_us >= 0 && ToCm(echo_us) < kWarnCm;
    if (!buzzer.Set(warn ? 1 : 0)) break;
    if (echo_us < 0)
      std::printf("no echo -- check TRIG, the 5V feed and the divider\n");
    else
      std::printf("echo=%5ld us -> %6.1f cm %s\n", echo_us, ToCm(echo_us),
                  warn ? "[WARN]" : "");
    std::fflush(stdout);
    usleep(kIntervalUs);
  }

  buzzer.Set(0);
  lgGpioFree(handle, kEchoPin);
  lgGpioFree(handle, kTrigPin);
  return lgGpiochipClose(handle) == LG_OKAY ? 0 : 1;
}
