#include <iostream>

std::ostream& Red(std::ostream& stream) {
  std::cout << "\033[31m";
  return stream;
}

std::ostream& Green(std::ostream& stream) {
  std::cout << "\033[32m";
  return stream;
}

std::ostream& Yellow(std::ostream& stream) {
  std::cout << "\033[33m";
  return stream;
}

int main() {
  std::cout << "A" << Red << "B" << Green << "C" << std::endl;
  std::cout << "===" << Yellow << "Banana" << std::endl;
  return 0;
}
