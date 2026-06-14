#include <iostream>

int main() {
  int num;
  float decimal;
  char character;
  bool boolean;

  std::cout << "Enter an integer: ";  // <<: stream insertion operator
  std::cin >> num;                    // >>: stream extraction operator
  std::cout << "Enter a float: ";
  std::cin >> decimal;
  std::cout << "Enter a character: ";
  std::cin >> character;
  std::cout << "Enter a boolean (0/1): ";
  std::cin >> boolean;

  std::cout << "Integer: " << num << "\nFloat: " << decimal
            << "\nCharacter: " << character << "\nBoolean: " << boolean;
  return 0;
}
