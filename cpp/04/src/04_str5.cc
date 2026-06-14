#include <iostream>
#include <string>

int main() {
  // Construction of a string
  std::string sentence("The C++ language is fun to work with.");

  // Retrieving two substrings
  // 1. from index 8 ('l') to the end: "language is fun to work with."
  std::cout << sentence.substr(8) << std::endl;
  // 2. 12 characters from index 4 ('C'): "C++ language"
  std::cout << sentence.substr(4, 12) << std::endl;
  return 0;
}
