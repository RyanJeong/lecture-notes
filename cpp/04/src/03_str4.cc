#include <iostream>
#include <string>

int main() {
  std::string str("c++ programming");
  // Retrieving and changing a character at index 0
  str[0] = 'C';
  std::cout << str << std::endl;  // "C++ programming"
  // Retrieving and changing a character at index 4
  std::cout << "Character at index 4: " << str.at(4) << std::endl;
  str.at(4) = 'P';
  std::cout << str << std::endl;  // "C++ Programming"
  // -> Both [] and at() expression can be evaluated to l-value and r-value

  // This out-of-index-range case is handled differently by [] and at().
  // []: an undefined behavior:
  std::cout << "Character out of index range: " << str[100] << std::endl;
  // at(): a runtime error; the following line is commented out to avoid crash
  // std::cout << "Character out of index range: " << str.at(100) << std::endl;
  return 0;
}
