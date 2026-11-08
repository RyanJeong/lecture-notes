#include "sensors/convert.hpp"

float RawToCelsius(int raw) { return static_cast<float>(raw) * 0.1f; }
