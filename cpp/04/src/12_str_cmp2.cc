#include <iostream>
#include <string>

int main() {
  // Creation of four C++ strings
  std::string str1;                   // <EMPTY>
  std::string str2(5, 'a');           // "aaaaa"
  std::string str3("Hello Friends");  // "Hello Friends"
  std::string str4("Hi People", 4);   // "Hi P"

  // Using logical operators (relational and equality)
  std::cout << "str1 > str2 : " << std::boolalpha << (str1 > str2);
  std::cout << std::endl;
  std::cout << "str3 <= str4: " << std::boolalpha << (str3 <= str4);
  std::cout << std::endl;
  std::cout << "str1 != str2: " << std::boolalpha << (str1 != str2);
  std::cout << std::endl;
  std::cout << "\"Hi P\" == str4: " << std::boolalpha << ("Hi P" == str4);
  std::cout << std::endl;
  return 0;
}
