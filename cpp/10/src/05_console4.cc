#include <iostream>
#include <limits>  // for std::numeric_limits

int main() {
  // 1. Use ignore(size_t n = 1, int delim = EOF) to skip characters
  std::cout << "Enter a line of text (this line will be skipped): ";
  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

  // 2. Use ignore() to skip a character
  std::cout << "Enter an integer: ";
  int i;
  std::cin >> i;
  std::cin.ignore();  // to skip the '\n' character left in the buffer

  char c;
  std::cout << "Enter a character: ";
  std::cin.get(c);
  std::cout << "Entered integer: " << i << ", character: " << c << std::endl;
  return 0;
}