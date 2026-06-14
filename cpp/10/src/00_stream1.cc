#include <iostream>

void Verbose() {
  std::cout << "  - Eof: " << std::cin.eof() << std::endl;
  std::cout << "  - Fail: " << std::cin.fail() << std::endl;
  std::cout << "  - Bad: " << std::cin.bad() << std::endl << std::endl;
}

int main() {
  for (int i; std::cin >> i; Verbose())
    std::cout << "- Read an integer: " << i << std::endl;

  if (std::cin) {  // Equivalent to !std::cin.fail()
    std::cout << "- Input terminated normally" << std::endl;
  } else {  // std::cin.fail() || std::cin.bad()
    if (!std::cin.eof())
      std::cerr << "[Error] Input failure detected" << std::endl;
  }
  Verbose();
  return 0;
}
