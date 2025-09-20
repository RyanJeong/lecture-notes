#include <iostream>

int main() {
  int x = 8, y = 7;
  int& ref = x;  // type definition (&)
  int* p = &x;   // type definition (*)

  std::cout << "p: " << p << std::endl;
  std::cout << "&ref: " << &ref << std::endl;  // unary operator (&)
  std::cout << "*p: " << *p << std::endl;      // unary operator (*)
  std::cout << "ref: " << ref << std::endl;
  std::cout << "x & y: " << (x & y) << std::endl;  // binary operator (&)
  std::cout << "x * y: " << (x * y) << std::endl;  // binary operator (*)
  return 0;
}