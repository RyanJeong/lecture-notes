#include <unistd.h>

#include <cstdio>
#include <ctime>

#include "gpio.hpp"
#include "signal_stop.hpp"

#if 1 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
namespace {
constexpr unsigned int kLedPin = 17;     // BCM 17, through a 330 ohm resistor
constexpr unsigned int kButtonPin = 23;  // BCM 23, 10k pull-up to 3.3V
constexpr int kPollIntervalMs = 1000;
constexpr long kSettleMs = 50;  // line must idle HIGH this long to re-arm
}  // namespace
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */

long NowMillis() {
  timespec ts;
  clock_gettime(CLOCK_MONOTONIC, &ts);
  return ts.tv_sec * 1000L + ts.tv_nsec / 1000000L;
}

// Lab 2-A: one press toggles the LED.
int main() {
#if 1 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
  Gpio led(kLedPin, Gpio::kOutputLow);
  Gpio button(kButtonPin, Gpio::kInputPullUp);
  if (!InstallStopHandler() || !led.ok() || !button.ok()) {
    std::fprintf(stderr, "cannot claim GPIO%u/%u\n", kLedPin, kButtonPin);
    return 1;
  }
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */

  bool led_is_on = false;
  bool armed = false;
  long last_low = 0;
  std::printf("press GPIO%u to toggle. Ctrl-C to stop\n", kButtonPin);
  while (!StopRequested()) {
    const int level = button.Get();
    if (level < 0) break;
    const long now = NowMillis();
#if 1 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
    // Report the press at once, then refuse another until the line has been
    // HIGH continuously for the settle time. Chatter cannot re-arm it.
    if (level == 0) {  // pressed
      last_low = now;
      if (armed) {
        armed = false;
        led_is_on = !led_is_on;
        if (!led.Set(led_is_on ? 1 : 0)) return 1;
        std::printf("LED %s\n", led_is_on ? "on" : "off");
        std::fflush(stdout);
      }
    } else if (now - last_low >= kSettleMs) {
      armed = true;
    }
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
    usleep(kPollIntervalMs);
  }
  return led.Set(0) ? 0 : 1;
}
