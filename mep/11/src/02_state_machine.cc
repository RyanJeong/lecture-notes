#include <unistd.h>

#include <cstdio>
#include <ctime>

#include "gpio.hpp"
#include "signal_stop.hpp"

namespace {
constexpr unsigned int kRedPin = 17;     // walk for people
constexpr unsigned int kGreenPin = 27;   // go for cars
constexpr unsigned int kButtonPin = 23;  // pedestrian request
constexpr int kPollUs = 1000;
constexpr long kSettleMs = 50;
constexpr long kBlinkMs = 400;
// A request cannot stop cars instantly: the green phase still gets this much
// time, which is the minimum green a real crossing guarantees.
constexpr long kGraceMs = 2000;
#if 1 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
enum State {
  kCarGo,
  kWarn,
  kWalk,
  kStateCount
};
constexpr long kDurationMs[kStateCount] = {10000, 3000, 8000};
const char* const kNames[kStateCount] = {"CAR GO", "WARN", "WALK"};
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
}  // namespace

#if 1 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
// Output is a function of the state alone, so the wiring cannot drift out of
// step with the sequence. Green blinks during the warning phase.
bool RedOn(int state) { return state == kWalk; }
bool GreenOn(int state, bool blink) {
  return state == kCarGo || (state == kWarn && blink);
}
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */

long NowMillis() {
  timespec ts;
  clock_gettime(CLOCK_MONOTONIC, &ts);
  return ts.tv_sec * 1000L + ts.tv_nsec / 1000000L;
}

// Lab 2-C: a time-driven crossing; the button pulls the next transition in.
int main() {
  Gpio red(kRedPin, Gpio::kOutputLow);
  Gpio green(kGreenPin, Gpio::kOutputLow);
  Gpio button(kButtonPin, Gpio::kInputPullUp);
  if (!InstallStopHandler() || !red.ok() || !green.ok() || !button.ok())
    return 1;

  int state = kCarGo;
  long deadline = NowMillis() + kDurationMs[state];
  long last_low = 0;
  bool armed = false;
  bool requested = false;
  std::printf("-> %s\n", kNames[state]);
  while (!StopRequested()) {
    const long now = NowMillis();
    const int level = button.Get();
    if (level < 0) break;
    if (level == 0) {  // pressed
      last_low = now;
      if (armed) {
        armed = false;
        requested = true;
      }
    } else if (now - last_low >= kSettleMs) {
      armed = true;
    }
#if 1 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
    // A request only shortens the green phase, and never below the minimum
    // green, so pressing ten times is the same as pressing once.
    if (requested && state == kCarGo && now + kGraceMs < deadline)
      deadline = now + kGraceMs;
    if (now >= deadline) {
      state = (state + 1) % kStateCount;
      deadline = now + kDurationMs[state];
      if (state == kWalk) requested = false;  // the crossing served it
      std::printf("-> %s\n", kNames[state]);
      std::fflush(stdout);
    }
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
    const bool blink = (now % kBlinkMs) < (kBlinkMs / 2);
    if (!red.Set(RedOn(state) ? 1 : 0) ||
        !green.Set(GreenOn(state, blink) ? 1 : 0)) {
      return 1;
    }
    usleep(kPollUs);
  }
  return (red.Set(0) && green.Set(0)) ? 0 : 1;
}
