#ifndef MEP_COMMON_MCP3008_HPP_
#define MEP_COMMON_MCP3008_HPP_

#include <fcntl.h>
#include <linux/spi/spidev.h>
#include <sys/ioctl.h>
#include <unistd.h>

#include <cstdint>
#include <cstring>

// The MCP3008 SPI ADC from lab 04, wrapped so the integration lab can use it
// without repeating the three-byte protocol.
class Mcp3008Device {
 public:
  static const int kAdcMax = 1023;
  // Two ways to fail, and they point at different wiring. Keeping them apart
  // is what lets the lab tell "the bus is dead" from "the chip is not there".
  static const int kErrorTransfer = -1;  // the ioctl itself failed
  static const int kErrorNoReply = -2;   // null bit set: nothing drove MISO

  explicit Mcp3008Device(const char* path) : fd_(::open(path, O_RDWR)) {
    if (fd_ < 0) return;
    const std::uint8_t mode = SPI_MODE_0;
    const std::uint8_t bits = 8;
    const std::uint32_t speed = 1350000;  // MCP3008 limit at 3.3 V
    if (::ioctl(fd_, SPI_IOC_WR_MODE, &mode) < 0 ||
        ::ioctl(fd_, SPI_IOC_WR_BITS_PER_WORD, &bits) < 0 ||
        ::ioctl(fd_, SPI_IOC_WR_MAX_SPEED_HZ, &speed) < 0) {
      ::close(fd_);
      fd_ = -1;
    }
  }

  ~Mcp3008Device() {
    if (fd_ >= 0) ::close(fd_);
  }

  Mcp3008Device(const Mcp3008Device&) = delete;
  Mcp3008Device& operator=(const Mcp3008Device&) = delete;

  bool ok() const { return fd_ >= 0; }

  // Returns the 10-bit reading, or one of the negative error codes above.
  //
  // The MCP3008 sends a null bit of 0 just above the ten data bits. If that
  // bit comes back set, nothing drove MISO and the line was floating -- which
  // decodes to 1023 and looks exactly like a full-scale input.
  int ReadChannel(unsigned int channel) const {
    if (fd_ < 0 || channel > 7) return kErrorTransfer;
    const std::uint8_t tx[3] = {
        0x01, static_cast<std::uint8_t>(0x80 | (channel << 4)), 0x00};
    std::uint8_t rx[3] = {0, 0, 0};

    spi_ioc_transfer tr;
    std::memset(&tr, 0, sizeof(tr));
    tr.tx_buf = reinterpret_cast<std::uintptr_t>(tx);
    tr.rx_buf = reinterpret_cast<std::uintptr_t>(rx);
    tr.len = 3;
    tr.speed_hz = 1350000;
    tr.bits_per_word = 8;
    if (::ioctl(fd_, SPI_IOC_MESSAGE(1), &tr) < 0) return kErrorTransfer;
    if ((rx[1] & 0x04) != 0) return kErrorNoReply;
    return ((rx[1] & 0x03) << 8) | rx[2];
  }

 private:
  int fd_;
};

#endif  // MEP_COMMON_MCP3008_HPP_
