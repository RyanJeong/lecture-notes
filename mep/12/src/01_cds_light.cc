#include <fcntl.h>
#include <linux/spi/spidev.h>
#include <sys/ioctl.h>
#include <unistd.h>

#include <cstdint>
#include <cstdio>
#include <cstring>

#include "signal_stop.hpp"

namespace {
constexpr const char* kSpiDev = "/dev/spidev0.0";  // CE0
constexpr unsigned int kChannel = 0;               // CdS divider feeds CH0
constexpr int kAdcMax = 1023;
constexpr float kVref = 3.3f;
constexpr float kFixedOhm = 10000.0f;  // the 10k in the divider
// MCP3008 SCLK max is 3.6 MHz at VDD = 5 V but only 1.35 MHz at 2.7 V, and
// the datasheet gives no 3.3 V figure, so the 2.7 V limit is the safe bound.
// A slower clock also gives the sampling capacitor time to charge through the
// divider's kilo-ohm output impedance. 18 clocks per sample -> 75 ksps max.
constexpr std::uint32_t kSpeedHz = 1350000;
constexpr int kIntervalUs = 500000;
}  // namespace

// Three bytes out, three back: a start bit, the single-ended channel select,
// then eight idle clocks while the chip shifts the result out.
int ReadChannel(int fd, unsigned int channel) {
  const std::uint8_t tx[3] = {
      0x01, static_cast<std::uint8_t>(0x80 | (channel << 4)), 0x00};
  std::uint8_t rx[3] = {0, 0, 0};
  spi_ioc_transfer tr;
  std::memset(&tr, 0, sizeof(tr));
  tr.tx_buf = reinterpret_cast<std::uintptr_t>(tx);
  tr.rx_buf = reinterpret_cast<std::uintptr_t>(rx);
  tr.len = 3;
  tr.speed_hz = kSpeedHz;
  tr.bits_per_word = 8;
  if (::ioctl(fd, SPI_IOC_MESSAGE(1), &tr) < 0) return -1;
  // The null bit must come back clear. Set means nothing drove MISO, and a
  // floating line decodes to 1023 -- indistinguishable from full scale.
  if ((rx[1] & 0x04) != 0) return -2;
  return ((rx[1] & 0x03) << 8) | rx[2];
}

float AdcToVoltage(int raw) {
  return (static_cast<float>(raw) / static_cast<float>(kAdcMax)) * kVref;
}

// 3.3V -- [CdS] -- node -- [10k] -- GND. The node voltage rises as light
// rises, because the cell's resistance falls.
float CdsOhm(float volts) {
  if (volts <= 0.0f || volts >= kVref) return -1.0f;
  return kFixedOhm * (kVref - volts) / volts;
}

const char* Describe(float volts) {
  if (volts < 0.5f) return "dark";
  if (volts < 1.5f) return "shaded";
  if (volts < 2.5f) return "bright";
  return "very bright";
}

bool Configure(int fd) {
  const std::uint8_t mode = SPI_MODE_0;
  const std::uint8_t bits = 8;
  return ::ioctl(fd, SPI_IOC_WR_MODE, &mode) >= 0 &&
         ::ioctl(fd, SPI_IOC_WR_BITS_PER_WORD, &bits) >= 0 &&
         ::ioctl(fd, SPI_IOC_WR_MAX_SPEED_HZ, &kSpeedHz) >= 0;
}

// Lab 3-B: the Pi has no analog input, so an external ADC reads the cell.
int main() {
  const int fd = ::open(kSpiDev, O_RDWR);
  if (fd < 0 || !Configure(fd) || !InstallStopHandler()) {
    std::fprintf(stderr, "cannot open %s -- enable SPI with raspi-config\n",
                 kSpiDev);
    return 1;
  }

  while (!StopRequested()) {
    const int raw = ReadChannel(fd, kChannel);
    if (raw < 0) {
      std::printf("no reply -- check VDD, MISO->DOUT, CE0->CS and the notch\n");
    } else {
      const float volts = AdcToVoltage(raw);
      std::printf("raw=%4d  V=%.3f  R=%.0f ohm  %s\n", raw, volts,
                  CdsOhm(volts), Describe(volts));
    }
    std::fflush(stdout);
    usleep(kIntervalUs);
  }
  return ::close(fd) == 0 ? 0 : 1;
}
