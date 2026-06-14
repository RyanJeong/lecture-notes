#include <iostream>
#include <string>

int main() {
  std::string str1("Hello!");
  std::string str2(" Wonderful");

  // Insert at a specific position
  str1.insert(5, str2);
  std::cout << "After insert: " << str1 << std::endl;
  // Replace part of the string
  str1.replace(6, 9, "Beautiful");
  std::cout << "After replace: " << str1 << std::endl;
  // Assign a new string
  std::string new_str;
  new_str.assign(str2);
  std::cout << "After assign: " << new_str << std::endl;
  return 0;
}
