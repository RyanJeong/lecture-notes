#include <gpiod.h>
#include <unistd.h>
#include <cstdio>

namespace {
constexpr const char* kChipPath = "/dev/gpiochip0";
constexpr unsigned int kLedLine = 17;  // BCM 17
constexpr const char* kConsumer = "mep-blink";
}  // namespace

// Minimal libgpiod v2 output example: every resource acquired is released,
// and every library call is checked. v2 configures a line through three
// throwaway objects and then claims it in a single request.
int main() {
  gpiod_chip* chip = gpiod_chip_open(kChipPath);
  if (chip == nullptr) {
    std::fprintf(stderr, "failed to open %s\n", kChipPath);
    return 1;
  }

  gpiod_line_settings* settings = gpiod_line_settings_new();
  gpiod_line_settings_set_direction(settings, GPIOD_LINE_DIRECTION_OUTPUT);
  gpiod_line_settings_set_output_value(settings, GPIOD_LINE_VALUE_INACTIVE);

  const unsigned int offsets[] = {kLedLine};
  gpiod_line_config* line_cfg = gpiod_line_config_new();
  gpiod_line_config_add_line_settings(line_cfg, offsets, 1, settings);

  gpiod_request_config* req_cfg = gpiod_request_config_new();
  gpiod_request_config_set_consumer(req_cfg, kConsumer);

  gpiod_line_request* request =
      gpiod_chip_request_lines(chip, req_cfg, line_cfg);

  // The config objects have done their job once the request exists.
  gpiod_request_config_free(req_cfg);
  gpiod_line_config_free(line_cfg);
  gpiod_line_settings_free(settings);

  if (request == nullptr) {
    std::fprintf(stderr, "failed to request line %u\n", kLedLine);
    gpiod_chip_close(chip);
    return 1;
  }

  for (int i = 0; i < 10; ++i) {
    gpiod_line_request_set_value(
        request, kLedLine,
        i % 2 != 0 ? GPIOD_LINE_VALUE_ACTIVE : GPIOD_LINE_VALUE_INACTIVE);
    usleep(500000);  // 500 ms
  }

  gpiod_line_request_release(request);
  gpiod_chip_close(chip);
  return 0;
}
