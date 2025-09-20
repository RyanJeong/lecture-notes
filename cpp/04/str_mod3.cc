#include <iostream>
#include <string>

int main() {
  std::string str("This is a sample string.");

  // Clear the entire string
  str.clear();
  std::cout << "After clear: \"" << str << "\"" << std::endl;
  // Create a new string and erase part of it
  str = "Another example string";
  str.erase(8, 8);  // Erase "example "
  std::cout << "After erase: " << str << std::endl;
  // Assignment and addition
  std::string str1 = "Hello", str2 = " World";
  str1 += str2;
  std::cout << "After compound assignment: " << str1 << std::endl;
  return 0;
}
