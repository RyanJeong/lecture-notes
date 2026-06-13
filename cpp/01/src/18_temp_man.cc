#include <iomanip>  // for std::setw, std::setfill
#include <iostream>

int main() {
  int num = 42;

  // std::setw() - only affects next output
  std::cout << std::setw(8) << num << "|" << std::endl;  // "      42|"
  std::cout << num << "|" << std::endl;                  // "42|"
  // std::setw() with std::setfill() - setw is temporary, setfill persists
  std::cout << std::setfill('*') << std::setw(8) << num << "|" << std::endl;
  std::cout << std::setw(6) << 99 << "|" << std::endl;
  std::cout << 123 << "|" << std::endl;
  return 0;
}