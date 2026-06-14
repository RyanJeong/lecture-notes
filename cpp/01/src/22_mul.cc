#include <iomanip>  // for std::setw
#include <iostream>

int main() {
  // Print multiplication table for each number from 2 to 9
  for (int i = 2; i <= 9; ++i) {
    for (int j = 1; j <= 9; ++j) {
      std::cout << i << " x " << j << " = " << std::setw(2) << i * j
                << std::endl;
    }
    std::cout << "==========" << std::endl;
  }
  return 0;
}
