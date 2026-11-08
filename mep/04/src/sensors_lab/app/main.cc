#include <cstdio>

#include "sensors/convert.hpp"

int main() {
  std::printf("%.1f C\n", RawToCelsius(253));
  return 0;
}
