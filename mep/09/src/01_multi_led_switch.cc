#include <unistd.h>
#include <cstdio>
#include <ctime>

#include "button.hpp"
#include "gpio_helper.hpp"
#include "signal_stop.hpp"

namespace {
constexpr const char* kChip = "gpiochip0";
constexpr const char* kConsumer = "mep-lab01";
// BCM numbering. Wire each LED through a 330 ohm resistor, and each button
// with a 10k pull-up to 3.3V.
constexpr unsigned int kLedPins[] = {17, 27, 22};
constexpr unsigned int kModePin = 23;        // SW1: manual <-> candle
constexpr unsigned int kBrightnessPin = 24;  // SW2: brightness step
constexpr int kLedCount = 3;
// 100 steps of 100 us is a 10 ms period, or 100 Hz -- fast enough that the
// eye sees steady brightness rather than blinking.
constexpr int kPwmSteps = 100;
constexpr int kStepUs = 100;
constexpr int kBrightnessStep = 25;  // 0, 25, 50, 75, 100 percent
constexpr int kSettleMs = 50;        // line must idle HIGH this long to re-arm
constexpr int kSampleSteps = 10;     // read the buttons every 10 steps = ~1 ms
}  // namespace

// A GPIO can only be HIGH or LOW, so brightness comes from switching faster
// than the eye can follow. The fraction of the period spent HIGH is the duty
// cycle, and that fraction is the brightness.
bool PwmLevel(int step, int duty_percent) { return step < duty_percent; }

// SW2 walks the brightness up and wraps back to off: 0, 25, 50, 75, 100, 0.
int NextBrightness(int duty_percent) {
  return (duty_percent + kBrightnessStep) % (100 + kBrightnessStep);
}

enum class Mode {
  kManual,
  kCandle
};

Mode NextMode(Mode mode) {
  return mode == Mode::kManual ? Mode::kCandle : Mode::kManual;
}

// A candle is not random brightness. It drifts toward a new level rather
// than jumping to it, and every so often a draught pulls it much lower for a
// moment. Jumping straight to random values reads as electrical noise; the
// drift plus the occasional deep dip is what reads as a flame.
//
// Where the flame is heading next. One target in eight is a draught, which
// dips far below the usual flutter.
int FlickerTarget(int base_percent, unsigned int noise) {
  if (base_percent <= 0) return 0;
  const int floor_percent =
      (noise & 7u) == 0 ? base_percent / 5 : (base_percent * 55) / 100;
  const int span = base_percent - floor_percent;
  if (span <= 0) return base_percent;
  return floor_percent + static_cast<int>((noise >> 3) % (span + 1));
}

// How fast it drifts there, in percent per tick. Varying this stops all
// three candles moving in step with one another.
int FlickerStep(unsigned int noise) { return 1 + static_cast<int>(noise % 4u); }

// Move toward the target without overshooting it.
int ApproachTarget(int current, int target, int step) {
  if (step <= 0) return target;
  if (current < target) {
    return current + step < target ? current + step : target;
  }
  if (current > target) {
    return current - step > target ? current - step : target;
  }
  return current;
}

// A linear congruential generator: no <random>, no global state, and the same
// seed always replays the same flame -- which makes it testable.
unsigned int NextRandom(unsigned int state) {
  return state * 1103515245u + 12345u;
}

namespace {
long NowMillis() {
  timespec ts;
  clock_gettime(CLOCK_MONOTONIC, &ts);
  return ts.tv_sec * 1000L + ts.tv_nsec / 1000000L;
}
}  // namespace

// Lab 01: three LEDs dimmed by software PWM, two buttons to control them.
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

  GpioLine leds[kLedCount] = {GpioLine(chip, kLedPins[0]),
                              GpioLine(chip, kLedPins[1]),
                              GpioLine(chip, kLedPins[2])};
  for (int i = 0; i < kLedCount; ++i) {
    if (!leds[i].RequestOutput(kConsumer, 0)) {
      std::fprintf(stderr, "cannot claim LED line %u\n", kLedPins[i]);
      return 1;
    }
  }

  Button mode_button(chip, kModePin, kSettleMs);
  Button brightness_button(chip, kBrightnessPin, kSettleMs);
  if (!mode_button.Claim(kConsumer) || !brightness_button.Claim(kConsumer)) {
    std::fprintf(stderr, "cannot claim button lines %u/%u\n", kModePin,
                 kBrightnessPin);
    return 1;
  }

  Mode mode = Mode::kManual;
  int base_duty = 50;
  int duty[kLedCount] = {50, 50, 50};
  int target[kLedCount] = {50, 50, 50};
  int step_size[kLedCount] = {1, 2, 3};
  unsigned int random = 1u;

  std::printf("SW1(GPIO%u) mode, SW2(GPIO%u) brightness. Ctrl-C to stop\n",
              kModePin, kBrightnessPin);
  std::printf("mode=manual  brightness=%d%%\n", base_duty);
  std::fflush(stdout);

  while (!StopRequested()) {
    bool changed = false;

    // One PWM period, with the buttons read every 10 steps -- about 1 ms,
    // which is far faster than any press and costs almost nothing.
    for (int step = 0; step < kPwmSteps; ++step) {
      for (int i = 0; i < kLedCount; ++i) {
        if (!leds[i].Set(PwmLevel(step, duty[i]) ? 1 : 0)) {
          std::fprintf(stderr, "cannot drive LED %u\n", kLedPins[i]);
          return 1;
        }
      }
      if (step % kSampleSteps == 0) {
        const long now = NowMillis();
        if (mode_button.Pressed(now)) {
          mode = NextMode(mode);
          changed = true;
        }
        if (brightness_button.Pressed(now)) {
          base_duty = NextBrightness(base_duty);
          changed = true;
        }
      }
      usleep(kStepUs);
    }

    if (!mode_button.ok() || !brightness_button.ok()) {
      std::fprintf(stderr, "button read failed -- stopping\n");
      break;
    }
    if (changed) {
      std::printf("mode=%s  brightness=%d%%\n",
                  mode == Mode::kCandle ? "candle" : "manual", base_duty);
      std::fflush(stdout);
    }

    if (mode == Mode::kManual) {
      for (int i = 0; i < kLedCount; ++i) duty[i] = base_duty;
      continue;
    }
    // Candle: each flame drifts toward its own target, and picks a new one
    // as soon as it arrives. They never line up, so the three never pulse
    // together.
    for (int i = 0; i < kLedCount; ++i) {
      duty[i] = ApproachTarget(duty[i], target[i], step_size[i]);
      if (duty[i] != target[i]) continue;
      random = NextRandom(random);
      target[i] = FlickerTarget(base_duty, random >> 8);
      random = NextRandom(random);
      step_size[i] = FlickerStep(random >> 8);
    }
  }

  for (int i = 0; i < kLedCount; ++i) leds[i].Set(0);
  std::printf("stopped\n");
  return 0;
}
