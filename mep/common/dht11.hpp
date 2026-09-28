#ifndef MEP_COMMON_DHT11_HPP_
#define MEP_COMMON_DHT11_HPP_

#include <unistd.h>
#include <cstdint>
#include <ctime>

#include "gpio_helper.hpp"

// The DHT11 from lab 03, wrapped for the integration lab.
//
// This device sets the pace for the whole hub: the datasheet forbids reading
// it more than once a second, so the class caches its last good sample and
// serves that in between. Callers can poll as fast as they like.
class Dht11Device {
 public:
  Dht11Device(const GpioChip& chip, unsigned int pin, const char* consumer)
      : chip_(chip),
        pin_(pin),
        consumer_(consumer),
        humidity_(0),
        temperature_(0),
        valid_(false),
        last_attempt_us_(0),
        failures_(0) {}

  bool valid() const { return valid_; }
  int humidity() const { return humidity_; }
  int temperature() const { return temperature_; }

  // Consecutive failed attempts since the last good one. Non-zero here with
  // valid() still true means the reported sample is stale but usable.
  int failures() const { return failures_; }


  // Re-reads only if the minimum interval has elapsed. Returns true when a
  // cached or fresh sample is available, so a caller may poll as fast as it
  // likes without violating the datasheet.
  bool Refresh(long min_interval_us) {
    const long now = NowMicros();
    if (valid_ && now - last_attempt_us_ < min_interval_us) return true;
    last_attempt_us_ = now;
    if (Sample()) {
      failures_ = 0;
      return true;
    }
    ++failures_;
    return valid_;  // a previous good sample is still worth reporting
  }

 private:
  static long NowMicros() {
    timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return ts.tv_sec * 1000000L + ts.tv_nsec / 1000L;
  }

  static long WaitFor(const GpioLine& line, int level, long timeout_us) {
    const long start = NowMicros();
    for (;;) {
      const int value = line.Get();
      if (value < 0) return -1;
      if (value == level) return NowMicros() - start;
      if (NowMicros() - start > timeout_us) return -1;
    }
  }

  bool Sample() {
    GpioLine line(chip_, pin_);
    if (!line.ok()) return false;

    // Hold LOW then release; do not drive HIGH first, or the re-request
    // overruns the sensor's 80 us preamble.
    if (!line.RequestOutput(consumer_, 0)) return false;
    usleep(20000);
    line.Release();
    if (!line.RequestInput(consumer_)) return false;

    if (WaitFor(line, 0, 200) < 0) return false;
    if (WaitFor(line, 1, 200) < 0) return false;
    if (WaitFor(line, 0, 200) < 0) return false;

    std::uint8_t data[5] = {0, 0, 0, 0, 0};
    for (int i = 0; i < 40; ++i) {
      if (WaitFor(line, 1, 200) < 0) return false;
      const long high_us = WaitFor(line, 0, 200);
      if (high_us < 0) return false;
      const int bit = (high_us > 50) ? 1 : 0;
      data[i / 8] = static_cast<std::uint8_t>((data[i / 8] << 1) | bit);
    }

    const std::uint8_t sum =
        static_cast<std::uint8_t>(data[0] + data[1] + data[2] + data[3]);
    if (sum != data[4]) return false;

    humidity_ = data[0];
    temperature_ = data[2];
    valid_ = true;
    return true;
  }

  const GpioChip& chip_;
  unsigned int pin_;
  const char* consumer_;
  int humidity_;
  int temperature_;
  bool valid_;
  long last_attempt_us_;
  int failures_;
};

#endif  // MEP_COMMON_DHT11_HPP_
