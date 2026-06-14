#include <iostream>
#include <string>

int main() {
  // Append character at the end of a string
  std::string str("Hello");
  char c = '!';
  str.push_back(c);
  std::cout << "After push_back: " << str << std::endl;
  // Append a complete C++ string
  std::string temp(" World");
  str.append(temp);
  std::cout << "After append: " << str << std::endl;
  return 0;
}
