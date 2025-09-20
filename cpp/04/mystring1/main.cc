#include <iostream>

#include "mystring.hpp"

int main() {
  MyString str1("Hello C++ strings!");
  str1.Println();

  MyString str2 = str1;  // '=' symbol is invoking the copy constructor of the
                         // MyString and the compiler will treat this sentence
                         // as MyString str2(str1);
  str2.Println();

  MyString str3 = "implicit conversion example";
  str3.Println();

  MyString str4(10);  // MyString str4 = 10; is forbidden
  str4.Insert(0, "Hello, World!").Insert(0, "C++! ");
  str4.Println();
  std::cout << "length: " << str4.length() << std::endl;
  std::cout << "capacity: " << str4.capacity() << std::endl;

  str4.Erase(0, 5);
  str4.Println();
  std::cout << "length: " << str4.length() << std::endl;
  std::cout << "capacity: " << str4.capacity() << std::endl;
  return 0;
}
