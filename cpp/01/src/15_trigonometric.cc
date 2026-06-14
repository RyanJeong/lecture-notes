#include <cmath>  // C++ style math.h
#include <iostream>

int main() {
  const double PI = 3.141592;
  double degree = PI / 3;  // 60 degrees
  std::cout << "sin (60): " << std::sin(degree) << "\n";
  std::cout << "cos (60): " << std::cos(degree) << "\n";
  std::cout << "tan (60): " << std::tan(degree) << "\n";
  return 0;
}
