#ifndef MEP_COMMON_BUTTON_HPP_
#define MEP_COMMON_BUTTON_HPP_

#include <cstdio>

#include "gpio_helper.hpp"

// A pull-up push button, and the whole of what debouncing needs to be.
//
// Wiring: 10k from the pin to 3.3V, switch from the pin to GND. The line
// idles HIGH and reads LOW while pressed, so one press is one HIGH->LOW
// change.
//
// The rule is two lines long: report the press at once, then refuse to report
// another until the line has been HIGH continuously for the settle time.
// Chatter while pressing is ignored because the button is already spent;
// chatter while releasing keeps restarting the settle timer, so it cannot
// re-arm halfway through a release; and a held button never re-arms at all.
// A plain "ignore everything for N ms" lockout is not enough -- chatter that
// outlasts N still gets counted twice.
class Button {
 public:
  Button(const GpioChip& chip, unsigned int offset, int settle_ms)
      : line_(chip, offset),
        offset_(offset),
        settle_ms_(settle_ms),
        last_low_ms_(0),
        armed_(false),
        ok_(true) {}

  unsigned int offset() const { return offset_; }
  const GpioLine& line() const { return line_; }

  // Claim the line, asking for the internal pull-up. Some kernels reject the
  // bias flag; that is not fatal, because the breadboard already has a real
  // pull-up resistor, so fall back rather than refusing to run.
  bool Claim(const char* consumer) {
    if (line_.RequestInputPullUp(consumer)) return true;
    std::printf(
        "[check] GPIO%u: the kernel refused the internal pull-up, "
        "using the external resistor only\n",
        offset_);
    return line_.RequestInput(consumer);
  }

  // False once a read has failed, so a dead line stops the loop instead of
  // spinning forever reporting nothing.
  bool ok() const { return ok_; }

  // True once per press, on the first sample that sees the line low.
  // `now_ms` comes from the caller's clock.
  bool Pressed(long now_ms) {
    const int level = line_.Get();
    if (level < 0) {
      ok_ = false;
      return false;
    }
    if (level != 0) {
      if (now_ms - last_low_ms_ >= settle_ms_) armed_ = true;
      return false;
    }
    last_low_ms_ = now_ms;
    if (!armed_) return false;
    armed_ = false;
    return true;
  }

 private:
  GpioLine line_;
  unsigned int offset_;
  int settle_ms_;
  long last_low_ms_;
  bool armed_;
  bool ok_;
};

#endif  // MEP_COMMON_BUTTON_HPP_
