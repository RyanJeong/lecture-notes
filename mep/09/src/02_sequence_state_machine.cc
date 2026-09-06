#include <unistd.h>
#include <cstdio>
#include <ctime>

#include "button.hpp"
#include "gpio_helper.hpp"
#include "signal_stop.hpp"

namespace {
constexpr const char* kChip = "gpiochip0";
constexpr const char* kConsumer = "mep-lab02";
constexpr unsigned int kRedPin = 17;     // stop for cars, walk for people
constexpr unsigned int kGreenPin = 27;   // go for cars
constexpr unsigned int kButtonPin = 23;  // pedestrian request
constexpr int kPollIntervalUs = 1000;    // 1 ms
constexpr int kSettleMs = 50;         // line must idle HIGH this long to re-arm
constexpr long kBlinkPeriodMs = 400;  // full on/off cycle while warning
constexpr long kCarGoMs = 10000;
constexpr long kWarnMs = 3000;
constexpr long kWalkMs = 8000;
// A request cannot stop cars instantly: the green phase still gets this
// much time, which is the minimum green a real crossing guarantees.
constexpr long kRequestGraceMs = 2000;
}  // namespace

// Three phases, and the light only ever moves forward through them. Naming
// the states is what turns a pile of flags into something you can draw.
enum class State {
  kCarGo,
  kWarn,
  kWalk
};

// How long a phase runs before it times out on its own.
long StateDurationMs(State state) {
  switch (state) {
    case State::kCarGo:
      return kCarGoMs;
    case State::kWarn:
      return kWarnMs;
    case State::kWalk:
    default:
      return kWalkMs;
  }
}

State NextState(State state) {
  switch (state) {
    case State::kCarGo:
      return State::kWarn;
    case State::kWarn:
      return State::kWalk;
    case State::kWalk:
    default:
      return State::kCarGo;
  }
}

// The event transition. A request only shortens the green phase, and never
// below the minimum green, so pressing ten times is the same as pressing
// once. A press made at any other moment is not thrown away: it is latched
// and applied the next time the light is green, which is what a real
// crossing does with the button.
long EarliestDeadline(State state, long deadline_ms, long now_ms) {
  if (state != State::kCarGo) return deadline_ms;
  const long soonest = now_ms + kRequestGraceMs;
  return soonest < deadline_ms ? soonest : deadline_ms;
}

// Output is a function of the state alone, so the wiring cannot drift out of
// step with the sequence. Green blinks during the warning phase.
bool RedOn(State state) { return state == State::kWalk; }

bool GreenOn(State state, bool blink_phase) {
  if (state == State::kCarGo) return true;
  if (state == State::kWarn) return blink_phase;
  return false;
}

namespace {
const char* StateName(State state) {
  if (state == State::kCarGo) return "CAR GO";
  if (state == State::kWarn) return "WARN";
  return "WALK";
}

long NowMillis() {
  timespec ts;
  clock_gettime(CLOCK_MONOTONIC, &ts);
  return ts.tv_sec * 1000L + ts.tv_nsec / 1000000L;
}

}  // namespace

// Lab 02: a time-driven pedestrian crossing. The sequence advances on its own
// and the button is an event that pulls the next transition forward.
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

  GpioLine red(chip, kRedPin);
  GpioLine green(chip, kGreenPin);
  Button button(chip, kButtonPin, kSettleMs);
  if (!red.RequestOutput(kConsumer, 0) || !green.RequestOutput(kConsumer, 0) ||
      !button.Claim(kConsumer)) {
    std::fprintf(stderr, "cannot claim lines\n");
    return 1;
  }

  State state = State::kCarGo;
  long deadline = NowMillis() + StateDurationMs(state);
  bool requested = false;

  std::printf("pedestrian crossing; press GPIO%u to request. Ctrl-C to stop\n",
              kButtonPin);
  std::printf("-> %s\n", StateName(state));
  std::fflush(stdout);

  while (!StopRequested()) {
    const long now = NowMillis();
    const bool pressed = button.Pressed(now);
    if (!button.ok()) {
      std::fprintf(stderr, "button read failed -- stopping\n");
      break;
    }

    // Every press is acknowledged. A button that sometimes does nothing and
    // says nothing is indistinguishable from a broken one.
    if (pressed) {
      if (requested) {
        std::printf("   already requested\n");
      } else {
        requested = true;
        std::printf("   request registered\n");
      }
      std::fflush(stdout);
    }

    // Event transition: a pending request pulls the green phase in. Outside
    // the green phase there is nothing to shorten, so the request simply
    // waits -- it is not discarded.
    if (requested) {
      const long pulled = EarliestDeadline(state, deadline, now);
      if (pulled < deadline) {
        deadline = pulled;
        std::printf("   crossing in %ld ms\n", pulled - now);
        std::fflush(stdout);
      }
    }

    // Timeout transition, with the entry action printed once per phase.
    if (now >= deadline) {
      state = NextState(state);
      deadline = now + StateDurationMs(state);
      // The crossing is the request being served, so the latch clears here.
      if (state == State::kWalk) requested = false;
      std::printf("-> %s\n", StateName(state));
      std::fflush(stdout);
    }

    // Derived from the clock, not a blocking sleep, so the button stays
    // responsive while the warning phase blinks.
    const bool blink_phase = (now % kBlinkPeriodMs) < (kBlinkPeriodMs / 2);
    if (!red.Set(RedOn(state) ? 1 : 0) ||
        !green.Set(GreenOn(state, blink_phase) ? 1 : 0)) {
      std::fprintf(stderr, "cannot drive the LEDs\n");
      return 1;
    }
    usleep(kPollIntervalUs);
  }

  // Both lights off on the way out: a crossing left showing CAR GO after the
  // program has exited is worse than a dark one.
  red.Set(0);
  green.Set(0);
  std::printf("stopped\n");
  return 0;
}
