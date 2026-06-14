#include <iostream>

#include "my_exception.hpp"

void Foo() try {
  throw MyException("An error occurred in Foo", "Foo()");
} catch (const MyException& e) {
  std::cerr << "Error: " << e.what() << " at " << e.where() << std::endl;
}

int main() {
  Foo();
  return 0;
}
