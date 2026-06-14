#include <iostream>
#include <string>

int main() {
  std::string str("C++ string");
  std::size_t pos = str.find("C++");
  if (pos != std::string::npos)
    std::cout << "'C++' found at position: " << pos << std::endl;
  else
    std::cout << "'C++' not found" << std::endl;
  return 0;
}
