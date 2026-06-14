#include <iostream>
#include <string>

int main() {
  std::string first, last, format1, format2;
  char initial;

  std::cout << "Enter first name: ";
  std::cin >> first;
  std::cout << "Enter last name: ";
  std::cin >> last;
  std::cout << "Enter initial: ";
  std::cin >> initial;

  format1 = first + " " + initial + ". " + last;
  std::cout << "Full name in first format: ";
  std::cout << format1 << std::endl << std::endl;
  format2 = last + ", " + first + " " + initial + ".";
  std::cout << "Full name in second format: ";
  std::cout << format2 << std::endl << std::endl;
  return 0;
}
