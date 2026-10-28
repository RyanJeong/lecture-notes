#ifndef MEP_LAB04_SENSORS_HPP_
#define MEP_LAB04_SENSORS_HPP_

#include <fcntl.h>
#include <lgpio.h>
#include <linux/spi/spidev.h>
#include <sys/ioctl.h>
#include <unistd.h>

#include <cstdint>
#include <cstring>
#include <ctime>

#include "gpio.hpp"

// The three sensor routines from lab 3, collected so the hub can call them
// without repeating the protocols. Nothing here is new -- only gathered.
class Sensors {
 public:
  static const int kDhtPin = 4;
  static const int kTrigPin = 23;
  static const int kEchoPin = 24;
  static const int kAdcMax = 1023;

  Sensors()
      : dht_(kDhtPin, Gpio::kInput),
        spi_(::open("/dev/spidev0.0", O_RDWR)),
        lg_(lgGpiochipOpen(0)),
        last_dht_us_(0),
        temperature_(0),
        humidity_(0),
        dht_valid_(false) {
    const std::uint8_t mode = SPI_MODE_0;
    const std::uint8_t bits = 8;
    if (spi_ >= 0 && (::ioctl(spi_, SPI_IOC_WR_MODE, &mode) < 0 ||
                      ::ioctl(spi_, SPI_IOC_WR_BITS_PER_WORD, &bits) < 0 ||
                      ::ioctl(spi_, SPI_IOC_WR_MAX_SPEED_HZ, &kSpeedHz) < 0)) {
      ::close(spi_);
      spi_ = -1;
    }
    if (lg_ >= 0) {
      lgGpioClaimOutput(lg_, 0, kTrigPin, 0);
      lgGpioClaimInput(lg_, 0, kEchoPin);
    }
  }

  ~Sensors() {
    if (spi_ >= 0) ::close(spi_);
    if (lg_ >= 0) {
      lgGpioFree(lg_, kEchoPin);
      lgGpioFree(lg_, kTrigPin);
      lgGpiochipClose(lg_);
    }
  }

  Sensors(const Sensors&) = delete;
  Sensors& operator=(const Sensors&) = delete;

  // The DHT11 forbids reading faster than once every two seconds, so a fresh
  // conversion is only attempted when the interval has elapsed.
  bool ReadDht(float* temperature, float* humidity) {
    const long now = NowMicros();
    if (now - last_dht_us_ >= kDhtIntervalUs) {
      last_dht_us_ = now;
      dht_valid_ = Convert();
    }
    if (!dht_valid_) return false;
    *temperature = static_cast<float>(temperature_);
    *humidity = static_cast<float>(humidity_);
    return true;
  }

  bool ReadLight(float* volts) {
    if (spi_ < 0) return false;
    const std::uint8_t tx[3] = {0x01, 0x80, 0x00};  // start, CH0, idle clocks
    std::uint8_t rx[3] = {0, 0, 0};
    spi_ioc_transfer tr;
    std::memset(&tr, 0, sizeof(tr));
    tr.tx_buf = reinterpret_cast<std::uintptr_t>(tx);
    tr.rx_buf = reinterpret_cast<std::uintptr_t>(rx);
    tr.len = 3;
    tr.speed_hz = kSpeedHz;
    tr.bits_per_word = 8;
    if (::ioctl(spi_, SPI_IOC_MESSAGE(1), &tr) < 0) return false;
    if ((rx[1] & 0x04) != 0) return false;  // null bit set: MISO floated
    const int raw = ((rx[1] & 0x03) << 8) | rx[2];
    *volts = (static_cast<float>(raw) / static_cast<float>(kAdcMax)) * kVref;
    return true;
  }

  bool ReadDistance(float* cm) {
    if (lg_ < 0 || lgGpioRead(lg_, kEchoPin) != 0) return false;
    if (lgGpioWrite(lg_, kTrigPin, 1) != LG_OKAY) return false;
    lguSleep(0.00001);
    if (lgGpioWrite(lg_, kTrigPin, 0) != LG_OKAY) return false;
    if (Await(1, kStartTimeoutUs) < 0) return false;
    const long echo_us = Await(0, kEchoTimeoutUs);
    if (echo_us < 0) return false;
    *cm = (static_cast<float>(echo_us) * kSpeedCmPerUs) / 2.0f;
    return true;
  }

 private:
  static const std::uint32_t kSpeedHz = 1350000;
  static const long kDhtIntervalUs = 2000000;
  static const long kStartTimeoutUs = 60000;
  static const long kEchoTimeoutUs = 30000;
  static const long kBitThresholdUs = 50;
  static constexpr float kVref = 3.3f;
  static constexpr float kSpeedCmPerUs = 0.0343f;

  static long NowMicros() {
    timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return ts.tv_sec * 1000000L + ts.tv_nsec / 1000L;
  }

  // lguTimestamp() counts nanoseconds; the timeouts here are microseconds.
  long Await(int level, long timeout_us) const {
    const std::uint64_t start = lguTimestamp();
    for (;;) {
      const int value = lgGpioRead(lg_, kEchoPin);
      if (value < 0) return -1;
      const long elapsed = static_cast<long>((lguTimestamp() - start) / 1000);
      if (value == level) return elapsed;
      if (elapsed > timeout_us) return -1;
    }
  }

  long WaitLine(int level, long timeout_us) const {
    const long start = NowMicros();
    for (;;) {
      const int value = dht_.Get();
      if (value < 0) return -1;
      const long elapsed = NowMicros() - start;
      if (value == level) return elapsed;
      if (elapsed > timeout_us) return -1;
    }
  }

  bool Convert() {
    if (!dht_.Reconfigure(Gpio::kOutputLow)) return false;
    usleep(20000);
    if (!dht_.Reconfigure(Gpio::kInput)) return false;
    if (WaitLine(0, 200) < 0 || WaitLine(1, 200) < 0 || WaitLine(0, 200) < 0)
      return false;
    std::uint8_t data[5] = {0, 0, 0, 0, 0};
    for (int i = 0; i < 40; ++i) {
      if (WaitLine(1, 200) < 0) return false;
      const long high_us = WaitLine(0, 200);
      if (high_us < 0) return false;
      const int bit = high_us > kBitThresholdUs ? 1 : 0;
      data[i / 8] = static_cast<std::uint8_t>((data[i / 8] << 1) | bit);
    }
    if (static_cast<std::uint8_t>(data[0] + data[1] + data[2] + data[3]) !=
        data[4]) {
      return false;
    }
    humidity_ = data[0];
    temperature_ = data[2];
    return true;
  }

  Gpio dht_;
  int spi_;
  int lg_;
  long last_dht_us_;
  int temperature_;
  int humidity_;
  bool dht_valid_;
};

#endif  // MEP_LAB04_SENSORS_HPP_
