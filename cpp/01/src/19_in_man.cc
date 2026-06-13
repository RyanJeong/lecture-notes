#include <iostream>

int main() {
  int decimal, octal, hex;
  bool flag;

  // Boolean input format
  std::cout << "Enter boolean (true/false): ";
  std::cin >> std::boolalpha >> flag;
  std::cout << "You entered: " << flag << std::endl;
  // Number base input formats
  std::cout << "Enter decimal number: ";
  std::cin >> std::dec >> decimal;
  std::cout << "Enter octal number (e.g., 077): ";
  std::cin >> std::oct >> octal;
  std::cout << "Enter hex number (e.g., 0xff): ";
  std::cin >> std::hex >> hex;
  std::cout << "Values: " << std::dec << decimal << " " << octal << " " << hex
            << std::endl;
  return 0;
}
