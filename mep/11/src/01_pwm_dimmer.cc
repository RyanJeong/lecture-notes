#include <unistd.h>

#include <cstdio>
#include <ctime>

#include "gpio.hpp"
#include "signal_stop.hpp"

namespace {
constexpr unsigned int kLedPin = 17;
constexpr unsigned int kButtonPin = 24;
#if 1 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
// Ignoring GPIO and scheduling overhead, 100 steps of 100 us is a 10 ms
// period. The actual software PWM period is longer and can vary.
constexpr int kPwmSteps = 100;
constexpr int kStepUs = 100;
constexpr int kSampleSteps = 10;     // read the button every ~1 ms
constexpr int kBrightnessStep = 25;  // 0, 25, 50, 75, 100 percent
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
constexpr long kSettleMs = 50;
}  // namespace

#if 1 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
// A GPIO is only HIGH or LOW, so brightness is controlled by the fraction of
// each period spent HIGH.
bool PwmLevel(int step, int duty_percent) { return step < duty_percent; }

// Walks the brightness up and wraps back to off.
int NextBrightness(int duty_percent) {
  return (duty_percent + kBrightnessStep) % (100 + kBrightnessStep);
}
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */

long NowMillis() {
  timespec ts;
  clock_gettime(CLOCK_MONOTONIC, &ts);
  return ts.tv_sec * 1000L + ts.tv_nsec / 1000000L;
}

// Lab 2-B: software PWM with a button that steps the brightness.
int main() {
  Gpio led(kLedPin, Gpio::kOutputLow);
  Gpio button(kButtonPin, Gpio::kInputPullUp);
  if (!InstallStopHandler() || !led.ok() || !button.ok()) return 1;

  int duty = 50;
  bool armed = false;
  long last_low = 0;
  std::printf("brightness %d%%. Ctrl-C to stop\n", duty);
#if 1 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
  while (!StopRequested())
    for (int step = 0; step < kPwmSteps; ++step) {
      if (!led.Set(PwmLevel(step, duty) ? 1 : 0)) return 1;
      if (step % kSampleSteps == 0) {
        const long now = NowMillis();
        const int level = button.Get();
        if (level == 0) {  // pressed
          last_low = now;
          if (armed) {
            armed = false;
            duty = NextBrightness(duty);
            std::printf("brightness %d%%\n", duty);
            std::fflush(stdout);
          }
        } else if (now - last_low >= kSettleMs) {
          armed = true;
        }
      }
      usleep(kStepUs);
    }
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
  return led.Set(0) ? 0 : 1;
}
