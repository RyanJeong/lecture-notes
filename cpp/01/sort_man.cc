#include <iomanip>
#include <iostream>

int main() {
  int num = 1234;
  std::cout << "[" << std::right << std::setw(6) << num << "]" << std::endl;
  std::cout << "[" << std::left << std::setw(6) << num << "]" << std::endl;
  std::cout << "[" << std::internal << std::setw(6) << -num << "]"
            << std::endl;  // internal: The sign is placed on the left, and the
                           // number is right-aligned within the field.
  // Example output:
  // [- 1234]
  // The minus sign is always at the far left, and spaces are inserted between
  // the sign and the digits to fill the width.
  return 0;
}
