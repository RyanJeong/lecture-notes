#include <iostream>

#include "smaller.hpp"

int main() {
  std::cout << "Smaller of 12 and 15: " << Smaller(12, 15) << std::endl;
  std::cout << "Smaller of 12.3 and 15.6: " << Smaller(12.3, 15.6) << std::endl;
  return 0;
}
