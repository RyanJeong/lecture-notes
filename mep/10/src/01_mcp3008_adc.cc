#include <unistd.h>

#include <cstdio>

#include "gpio_helper.hpp"
#include "mcp3008.hpp"
#include "signal_stop.hpp"

namespace {
constexpr float kVref = 3.3f;                      // reference voltage
constexpr float kFixedResistor = 10000.0f;         // 10k in the CdS divider
constexpr const char* kSpiDev = "/dev/spidev0.0";  // CE0
constexpr unsigned int kCdsChannel = 0;            // CdS divider feeds CH0
constexpr const char* kChip = "gpiochip0";
constexpr const char* kConsumer = "mep-lab04";
constexpr unsigned int kLedPin = 17;  // BCM 17, through a 330 ohm resistor
// Two thresholds, not one: a single one makes the LED chatter whenever the
// reading sits on the boundary.
constexpr float kLightOnV = 1.0f;          // darker than this turns the LED on
constexpr float kLightOffV = 1.3f;         // brighter than this turns it off
constexpr int kSampleIntervalUs = 500000;  // report twice a second
}  // namespace

// The Raspberry Pi has NO analog input. An external ADC such as the MCP3008
// converts the CdS divider voltage into a 10-bit digital value over SPI.
// Keeping the conversion pure means it can be unit-tested without hardware.
float AdcToVoltage(int raw) {
  if (raw < 0) raw = 0;
  if (raw > Mcp3008Device::kAdcMax) raw = Mcp3008Device::kAdcMax;
  return (static_cast<float>(raw) /
          static_cast<float>(Mcp3008Device::kAdcMax)) *
         kVref;
}

// Voltage divider: 3.3V -- [CdS] -- node -- [10k] -- GND
// The node voltage rises as light increases (CdS resistance falls).
float VoltageToCdsResistance(float v_node) {
  if (v_node <= 0.0f || v_node >= kVref) return -1.0f;  // out of range
  return kFixedResistor * (kVref - v_node) / v_node;
}

// Hysteresis, kept pure so the switching rule can be tested on a host.
bool NextLedState(bool lit, float v_node) {
  if (!lit && v_node < kLightOnV) return true;
  if (lit && v_node > kLightOffV) return false;
  return lit;  // inside the band: hold whatever we already had
}

// A CdS cell drops in resistance as light rises, so the node voltage rises.
const char* DescribeBrightness(float v_node) {
  if (v_node < 0.0f) return "?";
  if (v_node < 0.5f) return "dark";
  if (v_node < 1.5f) return "shaded";
  if (v_node < 2.5f) return "bright";
  return "very bright";
}

// Every failure mode points somewhere different on the breadboard, so each
// one says where to look rather than just reporting a bad number.
const char* DescribeReading(int raw) {
  if (raw == Mcp3008Device::kErrorNoReply) {
    return "NO REPLY: the null bit came back set, so nothing drove MISO -- "
           "check VDD/DGND, MISO->DOUT, CE0->CS and the notch orientation";
  }
  if (raw == Mcp3008Device::kErrorTransfer) return "SPI transfer failed";
  if (raw >= Mcp3008Device::kAdcMax) {
    return "PINNED HIGH: CH0 looks tied to 3.3V, not the divider node";
  }
  if (raw <= 0) return "PINNED LOW: CH0 looks tied to GND, not the node";
  return nullptr;
}

// CH1..CH7 have nothing attached, so they show what a floating input reads on
// this board. If CH0 matches them, the divider is not reaching CH0 either.
bool ScanChannels(const Mcp3008Device& adc) {
  bool success = true;
  std::printf("channel scan (CH1-CH7 are unconnected on this board):\n");
  for (unsigned int ch = 0; ch < 8; ++ch) {
    const int raw = adc.ReadChannel(ch);
    if (raw < 0) success = false;
    std::printf("  CH%u raw=%5d%s\n", ch, raw,
                ch == kCdsChannel ? "   <- divider should be here" : "");
  }
  std::printf(
      "if CH0 reads the same as the unconnected channels, the wire "
      "from the divider node is not landing on CH0\n\n");
  return success;
}

int main() {
  if (!InstallStopHandler()) {
    std::fprintf(stderr, "cannot install the signal handler\n");
    return 1;
  }

  Mcp3008Device adc(kSpiDev);
  if (!adc.ok()) {
    std::fprintf(stderr,
                 "cannot open %s -- enable SPI (raspi-config > Interface "
                 "Options > SPI) and check you are in the spi group\n",
                 kSpiDev);
    return 1;
  }

  GpioChip chip(kChip);
  if (!chip.ok()) {
    std::fprintf(stderr, "cannot open %s\n", kChip);
    return 1;
  }
  GpioLine led(chip, kLedPin);
  if (!led.RequestOutput(kConsumer, 0)) {
    std::fprintf(stderr, "cannot claim GPIO%u for the LED\n", kLedPin);
    return 1;
  }

  if (!ScanChannels(adc)) {
    std::fprintf(stderr, "cannot scan all ADC channels\n");
    return 1;
  }
  std::printf(
      "CH%u -> LED on GPIO%u; cover the sensor to light it. Ctrl-C to "
      "stop\n",
      kCdsChannel, kLedPin);

  bool lit = false;
  while (!StopRequested()) {
    const int raw = adc.ReadChannel(kCdsChannel);
    const float v = raw < 0 ? -1.0f : AdcToVoltage(raw);

    if (raw >= 0) {
      lit = NextLedState(lit, v);
      if (!led.Set(lit ? 1 : 0)) {
        std::fprintf(stderr, "cannot drive the LED\n");
        return 1;
      }
    }

    const float r = VoltageToCdsResistance(v);
    char resistance[16];
    if (r < 0.0f) {
      std::snprintf(resistance, sizeof(resistance), "%9s", "---");
    } else {
      std::snprintf(resistance, sizeof(resistance), "%9.1f", r);
    }
    std::printf("raw=%5d  V=%.3f  R_cds=%s ohm  %-11s  LED %s\n", raw, v,
                resistance, DescribeBrightness(v), lit ? "ON" : "off");
    const char* warning = DescribeReading(raw);
    if (warning != nullptr) std::printf("  ^ %s\n", warning);
    std::fflush(stdout);
    usleep(kSampleIntervalUs);
  }

  if (!led.Set(0)) {
    std::fprintf(stderr, "cannot turn off the LED\n");
    return 1;
  }
  std::printf("stopped\n");
  return 0;
}
