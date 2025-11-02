#include <iostream>

// Definition of a template function
template <typename T>
T Smaller(const T& op1, const T& op2) {
  return op1 < op2 ? op1 : op2;
}

int main() {
  std::cout << "Smaller of 'a' and 'b': " << Smaller('a', 'b') << std::endl;
  std::cout << "Smaller of 12 and 15: " << Smaller(12, 15) << std::endl;
  std::cout << "Smaller of 44.2 and 33.1: " << Smaller(44.2, 33.1) << std::endl;
  return 0;
}
