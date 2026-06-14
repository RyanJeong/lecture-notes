#include <iostream>
#include <string>

int main() {
  // Declaration of a C++ string
  std::string str = "Hello, World!";

  // Conversion to a character array using data()
  // Since C++11, data() includes a null terminator
  const char* arr = str.data();
  std::cout << "Character array (using data()): " << arr << std::endl;
  // Conversion to a C-string using c_str()
  // c_str() guarantees a null-terminated C-string
  const char* cstr = str.c_str();
  std::cout << "C-string (using c_str()): " << cstr << std::endl;
  return 0;
}
