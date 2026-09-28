#include <unistd.h>

#include <cstdio>

#include "gpio_helper.hpp"
#include "hcsr04.hpp"
#include "signal_stop.hpp"

namespace {
constexpr const char* kChip = "gpiochip0";
constexpr const char* kConsumer = "mep-lab05";
constexpr unsigned int kTrigPin = 23;    // BCM 23, header pin 16
constexpr unsigned int kEchoPin = 24;    // BCM 24, header pin 18, via 1k/2k
constexpr unsigned int kBuzzerPin = 18;  // BCM 18, header pin 12
// Speed of sound at about 20 C, in cm per microsecond.
constexpr float kSpeedOfSoundCmPerUs = 0.0343f;
constexpr float kWarnDistanceCm = 10.0f;
constexpr int kCycleMs = 500;     // two measurements per second
constexpr int kFastBeepMs = 60;   // right at the obstacle
constexpr int kSlowBeepMs = 400;  // just inside the warning band
}  // namespace

// The echo pulse width is the round-trip time, so the one-way distance is
// half of it. Keeping this as a pure function makes it unit-testable without
// any hardware -- which is why the driver returns microseconds, not
// centimetres, and this conversion stays here in the lab.
float PulseWidthToDistanceCm(long pulse_us) {
  if (pulse_us <= 0) return -1.0f;
  return (static_cast<float>(pulse_us) * kSpeedOfSoundCmPerUs) / 2.0f;
}

bool ShouldWarn(float distance_cm) {
  return distance_cm > 0.0f && distance_cm < kWarnDistanceCm;
}

// Closer means more urgent, so the gap between beeps shrinks with distance.
// Zero means silence, which is the normal case.
int WarnIntervalMs(float distance_cm) {
  if (!ShouldWarn(distance_cm)) return 0;
  const float ratio = distance_cm / kWarnDistanceCm;  // 0.0 .. 1.0
  const float span = static_cast<float>(kSlowBeepMs - kFastBeepMs);
  return kFastBeepMs + static_cast<int>(ratio * span);
}

// Each failure has a different cause on the breadboard, so each one names it.
const char* DescribeError(long code) {
  if (code == Hcsr04Device::kErrorStuckHigh) {
    return "ECHO is already HIGH -- check the 1k/2k divider and GPIO24";
  }
  if (code == Hcsr04Device::kErrorNoStart) {
    return "no echo pulse -- check TRIG on GPIO23, VCC on 5V and GND";
  }
  if (code == Hcsr04Device::kErrorNoEnd)
    return "echo never ended -- out of range";
  return "GPIO access failed";
}

// An ACTIVE buzzer: driving the line HIGH is enough to make sound. A passive
// one needs a PWM carrier instead, which is the extension task.
bool RunBuzzer(GpioLine& buzzer, int interval_ms, int window_ms) {
  if (interval_ms <= 0) {
    if (!buzzer.Set(0)) return false;
    usleep(window_ms * 1000);
    return true;
  }
  int level = 0;
  for (int elapsed = 0; elapsed < window_ms; elapsed += interval_ms) {
    if (StopRequested()) break;  // do not make Ctrl-C wait out the beeps
    level = 1 - level;
    if (!buzzer.Set(level)) return false;
    usleep(interval_ms * 1000);
  }
  return buzzer.Set(0);
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

  Hcsr04Device sonar(0, kTrigPin, kEchoPin);
  GpioLine buzzer(chip, kBuzzerPin);
  if (!sonar.ok() || !buzzer.RequestOutput(kConsumer, 0)) {
    std::fprintf(stderr, "cannot claim GPIO%u/%u/%u\n", kTrigPin, kEchoPin,
                 kBuzzerPin);
    return 1;
  }

  std::printf(
      "TRIG=GPIO%u  ECHO=GPIO%u  buzzer=GPIO%u; warning under %.0f cm."
      " Ctrl-C to stop\n",
      kTrigPin, kEchoPin, kBuzzerPin, kWarnDistanceCm);

  while (!StopRequested()) {
    const long pulse_us = sonar.MeasureEchoUs();
    if (pulse_us < 0) {
      std::printf("measurement failed: %s\n", DescribeError(pulse_us));
      std::fflush(stdout);
      usleep(kCycleMs * 1000);
      continue;
    }

    const float distance_cm = PulseWidthToDistanceCm(pulse_us);
    const int interval_ms = WarnIntervalMs(distance_cm);
    std::printf("echo=%5ld us -> %6.1f cm %s\n", pulse_us, distance_cm,
                ShouldWarn(distance_cm) ? "[WARN]" : "");
    std::fflush(stdout);

    if (!RunBuzzer(buzzer, interval_ms, kCycleMs)) {
      std::fprintf(stderr, "cannot drive the buzzer\n");
      return 1;
    }
  }

  if (!buzzer.Set(0) || !sonar.Close()) {
    std::fprintf(stderr, "cannot release the sonar or buzzer cleanly\n");
    return 1;
  }
  std::printf("stopped\n");
  return 0;
}
