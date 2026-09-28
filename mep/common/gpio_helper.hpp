#ifndef MEP_COMMON_GPIO_HELPER_HPP_
#define MEP_COMMON_GPIO_HELPER_HPP_

#include <gpiod.h>

#include <string>

// RAII wrappers over libgpiod v2. The destructor releases the resource on
// every exit path, including an early return or a thrown exception.
class GpioChip {
 public:
  // Accepts a chip name ("gpiochip0") or a full device path.
  explicit GpioChip(const char* name) : chip_(nullptr) {
    if (name == nullptr) return;
    const std::string path =
        name[0] == '/' ? std::string(name) : std::string("/dev/") + name;
    chip_ = gpiod_chip_open(path.c_str());
  }
  ~GpioChip() {
    if (chip_ != nullptr) gpiod_chip_close(chip_);
  }

  GpioChip(const GpioChip&) = delete;
  GpioChip& operator=(const GpioChip&) = delete;

  bool ok() const { return chip_ != nullptr; }
  gpiod_chip* get() const { return chip_; }

 private:
  gpiod_chip* chip_;
};

// Owns the request for a single line. The object only releases a request it
// actually made, so a failed request never becomes a bogus release.
class GpioLine {
 public:
  GpioLine(const GpioChip& chip, unsigned int offset)
      : chip_(chip.ok() ? chip.get() : nullptr),
        offset_(offset),
        request_(nullptr) {}
  ~GpioLine() { Release(); }

  GpioLine(const GpioLine&) = delete;
  GpioLine& operator=(const GpioLine&) = delete;

  // Movable so that lines can be held in an array or vector. The moved-from
  // object gives up ownership, so only one object ever releases the request.
  GpioLine(GpioLine&& other) noexcept
      : chip_(other.chip_), offset_(other.offset_), request_(other.request_) {
    other.chip_ = nullptr;
    other.request_ = nullptr;
  }

  bool ok() const { return chip_ != nullptr; }

  bool RequestOutput(const char* consumer, int initial_value) {
    return Request(consumer, GPIOD_LINE_DIRECTION_OUTPUT, initial_value, false);
  }

  bool RequestInput(const char* consumer) {
    return Request(consumer, GPIOD_LINE_DIRECTION_INPUT, 0, false);
  }

  // Same, but with the SoC's internal pull-up switched on. Buttons want this:
  // libgpiod v2 defaults to "as is", which leaves whatever bias the pin
  // happened to have, and an input with no pull at all floats and reports
  // random levels. The external 10k on the breadboard is still the primary
  // pull-up -- this only means a missing or loose one degrades into a working
  // button rather than into noise.
  bool RequestInputPullUp(const char* consumer) {
    return Request(consumer, GPIOD_LINE_DIRECTION_INPUT, 0, true);
  }

  // Release early so the same line can be re-claimed in the other direction,
  // which the DHT11 protocol requires.
  void Release() {
    if (request_ != nullptr) {
      gpiod_line_request_release(request_);
      request_ = nullptr;
    }
  }

  int Get() const {
    if (request_ == nullptr) return -1;
    const gpiod_line_value value =
        gpiod_line_request_get_value(request_, offset_);
    return value == GPIOD_LINE_VALUE_ERROR ? -1 : static_cast<int>(value);
  }

  bool Set(int value) {
    if (request_ == nullptr) return false;
    const gpiod_line_value level =
        value != 0 ? GPIOD_LINE_VALUE_ACTIVE : GPIOD_LINE_VALUE_INACTIVE;
    return gpiod_line_request_set_value(request_, offset_, level) == 0;
  }

 private:
  // v2 builds a request from three throwaway config objects; each one is
  // freed here whether or not the request succeeds.
  bool Request(const char* consumer, gpiod_line_direction direction,
               int initial_value, bool pull_up) {
    if (chip_ == nullptr || request_ != nullptr) return false;

    gpiod_line_settings* settings = gpiod_line_settings_new();
    gpiod_line_config* line_cfg = gpiod_line_config_new();
    gpiod_request_config* req_cfg = gpiod_request_config_new();
    bool claimed = false;

    if (settings != nullptr && line_cfg != nullptr && req_cfg != nullptr) {
      bool configured =
          gpiod_line_settings_set_direction(settings, direction) == 0;
      if (pull_up) {
        configured = configured && gpiod_line_settings_set_bias(
                                       settings, GPIOD_LINE_BIAS_PULL_UP) == 0;
      }
      if (direction == GPIOD_LINE_DIRECTION_OUTPUT) {
        configured =
            configured &&
            gpiod_line_settings_set_output_value(
                settings, initial_value != 0 ? GPIOD_LINE_VALUE_ACTIVE
                                             : GPIOD_LINE_VALUE_INACTIVE) == 0;
      }
      if (configured && gpiod_line_config_add_line_settings(line_cfg, &offset_,
                                                            1, settings) == 0) {
        gpiod_request_config_set_consumer(req_cfg, consumer);
        request_ = gpiod_chip_request_lines(chip_, req_cfg, line_cfg);
        claimed = request_ != nullptr;
      }
    }

    if (req_cfg != nullptr) gpiod_request_config_free(req_cfg);
    if (line_cfg != nullptr) gpiod_line_config_free(line_cfg);
    if (settings != nullptr) gpiod_line_settings_free(settings);
    return claimed;
  }

  gpiod_chip* chip_;
  unsigned int offset_;
  gpiod_line_request* request_;
};

#endif  // MEP_COMMON_GPIO_HELPER_HPP_
