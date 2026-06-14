#include <iostream>
#include <string>

int main() {
  // Declaration of two C++ strings
  std::string str1("Hello my friends");
  std::string str2("Hello friends");
  // Comparing two C++ strings
  std::cout << str1 << " compared with " << str2 << ": ";
  std::cout << str1.compare(str2) << std::endl;  // 1 ('m' > 'f')
  // Comparing part of the two C++ strings
  std::cout << "Hello compared with Hello: ";
  std::cout << str1.compare(0, 5, str2, 0, 5) << std::endl;  // 0
  // Comparing part of the first C++ string and a C-string
  std::cout << "Hello compared with Hello: ";
  std::cout << str1.compare(0, 5, "Hello") << std::endl;  // 0
  // Comparing part of a C++ string and part of a C-string
  std::cout << "He compared with Hello: ";
  std::cout << str2.compare(0, 2, "Hello", 5)
            << std::endl;  // -1 ("He" is shorter then "Hello")
  return 0;
}
