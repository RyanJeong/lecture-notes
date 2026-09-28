#ifndef MEP_COMMON_HCSR04_HPP_
#define MEP_COMMON_HCSR04_HPP_

#include <lgpio.h>

#include <cstdint>

// The HC-SR04 sonar from lab 05, wrapped for the integration lab. ECHO must
// still reach the Pi through the 1k/2k divider: the module drives 5 V.
class Hcsr04Device {
 public:
  Hcsr04Device(int gpio_device, unsigned int trig_pin, unsigned int echo_pin)
      : handle_(lgGpiochipOpen(gpio_device)),
        trig_pin_(trig_pin),
        echo_pin_(echo_pin),
        trig_claimed_(false),
        echo_claimed_(false) {
    if (handle_ < 0) return;
    trig_claimed_ = lgGpioClaimOutput(handle_, 0, trig_pin_, 0) == LG_OKAY;
    if (!trig_claimed_) return;
    echo_claimed_ = lgGpioClaimInput(handle_, 0, echo_pin_) == LG_OKAY;
  }
  ~Hcsr04Device() { Close(); }

  Hcsr04Device(const Hcsr04Device&) = delete;
  Hcsr04Device& operator=(const Hcsr04Device&) = delete;

  // Each failure has a different cause on the breadboard, so they are kept
  // apart rather than collapsed into a single -1.
  static const long kErrorStuckHigh = -1;  // ECHO never returned low
  static const long kErrorNoStart = -2;    // no reply: TRIG or the 5 V feed
  static const long kErrorNoEnd = -3;      // pulse never ended: out of range
  static const long kErrorLine = -4;       // the GPIO call itself failed

  bool ok() const { return trig_claimed_ && echo_claimed_; }

  bool Close() {
    bool success = true;
    if (echo_claimed_) {
      success = lgGpioFree(handle_, echo_pin_) == LG_OKAY && success;
      echo_claimed_ = false;
    }
    if (trig_claimed_) {
      success = lgGpioFree(handle_, trig_pin_) == LG_OKAY && success;
      trig_claimed_ = false;
    }
    if (handle_ >= 0) {
      success = lgGpiochipClose(handle_) == LG_OKAY && success;
      handle_ = -1;
    }
    return success;
  }

  // Returns the echo pulse width in microseconds, or a negative error code.
  // This is the raw measurement: turning it into a distance is the caller's
  // job, and is a pure function worth testing on its own.
  long MeasureEchoUs() {
    if (!ok()) return kErrorLine;
    // ECHO rests low between measurements. Already high means the divider
    // node is not reaching the Pi, so measuring now would return garbage.
    const int resting = lgGpioRead(handle_, echo_pin_);
    if (resting < 0) return kErrorLine;
    if (resting != 0) return kErrorStuckHigh;

    if (lgGpioWrite(handle_, trig_pin_, 0) != LG_OKAY) return kErrorLine;
    lguSleep(0.000005);
    // Driven directly, not with lgTxPulse(): that call queues the pulse for a
    // background thread and returns the free queue slots, not LG_OKAY.
    if (lgGpioWrite(handle_, trig_pin_, 1) != LG_OKAY) return kErrorLine;
    lguSleep(0.00001);
    if (lgGpioWrite(handle_, trig_pin_, 0) != LG_OKAY) return kErrorLine;

    const long start_us = WaitFor(1, 60000);
    if (start_us == kErrorLine) return kErrorLine;
    if (start_us < 0) return kErrorNoStart;
    const long width_us = WaitFor(0, 30000);
    if (width_us == kErrorLine) return kErrorLine;
    if (width_us < 0) return kErrorNoEnd;
    return width_us;
  }

  // Convenience for callers that only want the distance. Returns -1 on any
  // failure, which is enough when a dashboard just shows a dash.
  float MeasureCm() {
    const long width_us = MeasureEchoUs();
    if (width_us < 0) return -1.0f;
    return (static_cast<float>(width_us) * 0.0343f) / 2.0f;
  }

 private:
  // lguTimestamp() counts nanoseconds; every timeout here, and the width the
  // caller turns into centimetres, is in microseconds.
  long WaitFor(int level, long timeout_us) const {
    const std::uint64_t start = lguTimestamp();
    for (;;) {
      const int value = lgGpioRead(handle_, echo_pin_);
      if (value < 0) return kErrorLine;
      const long elapsed_us =
          static_cast<long>((lguTimestamp() - start) / 1000);
      if (value == level) return elapsed_us;
      if (elapsed_us > timeout_us) return -1;
    }
  }

  int handle_;
  unsigned int trig_pin_;
  unsigned int echo_pin_;
  bool trig_claimed_;
  bool echo_claimed_;
};

#endif  // MEP_COMMON_HCSR04_HPP_
