#include <unistd.h>

#include <cstdio>

#include "dht11.hpp"
#include "gpio_helper.hpp"
#include "signal_stop.hpp"

namespace {
constexpr const char* kChip = "gpiochip0";
constexpr const char* kConsumer = "mep-lab03";
constexpr unsigned int kDataPin = 4;  // BCM 4, 3-pin module with pull-up
// The loop runs at the sensor's own pace rather than polling faster and
// reprinting a cached value, so every line is a fresh measurement.
constexpr long kSampleIntervalUs = 2000000;  // 2 s between reports
// The datasheet asks for at least 1 s between conversions. Sitting just
// above that leaves room for a second attempt inside the same report window.
constexpr long kMinSampleIntervalUs = 1100000;
constexpr long kRetryDelayUs =
    1200000;                     // longer than the guard, so a retry
                                 // is a real conversion, not a cache hit
constexpr int kMaxAttempts = 3;  // failures fall off as p^3
}  // namespace

// Lab 03: the single-wire protocol lives in common/dht11.hpp, which every
// later chapter reuses. What is left here is the part specific to this lab --
// how often to ask, and what to show.
//
// Asking faster than the sensor allows would only return failures, so the
// report rate IS the sensor's rate. That is what keeps the output honest
// without having to label every line with an age.
//
// NOTE: the bit-banged timing inside the driver runs in Linux user space,
// where the scheduler can preempt the loop and stretch a measured phase.
// Occasional checksum failures are expected, which is why the driver holds
// the last good sample instead of discarding everything on one bad read.
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

  Dht11Device sensor(chip, kDataPin, kConsumer);
  std::printf("DHT11 on GPIO%u, reporting every %ld ms. Ctrl-C to stop\n",
              kDataPin, kSampleIntervalUs / 1000L);
  std::fflush(stdout);

  while (!StopRequested()) {
    // A failed conversion is almost always the scheduler taking the CPU away
    // in the middle of a bit, not a broken sensor, so it is worth asking
    // again. Every attempt waits out the datasheet interval first, otherwise
    // the driver would answer from its cache and the retry would be a no-op.
    for (int attempt = 1; attempt <= kMaxAttempts; ++attempt) {
      const bool available = sensor.Refresh(kMinSampleIntervalUs);
      if (available && sensor.failures() == 0) break;
      if (attempt == kMaxAttempts || StopRequested()) break;
      usleep(kRetryDelayUs);
    }

    if (sensor.valid()) {
      // The only time a line is not a fresh measurement is when the read
      // failed, and that says so rather than repeating silently.
      std::printf("humidity=%3d %%  temperature=%3d C%s\n", sensor.humidity(),
                  sensor.temperature(),
                  sensor.failures() > 0 ? "   [stale: last read failed]" : "");
    } else {
      std::printf(
          "no valid sample yet (%d failed reads) -- check DATA on "
          "GPIO%u and the 3.3V feed\n",
          sensor.failures(), kDataPin);
    }
    std::fflush(stdout);

    // Wait from the last conversion, not from the top of the loop. Pacing
    // from the top would leave the next attempt inside the guard window
    // after a retry, and the driver would silently serve a cached repeat.
    usleep(kSampleIntervalUs);
  }

  std::printf("stopped\n");
  return 0;
}
