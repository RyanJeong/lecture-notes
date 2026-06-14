#include <iostream>
#include <utility>  // for std::move

#include "my_class.hpp"

int main() {
  MyClass obj1, obj2;

  std::cout << "1. Assignment with lvalue (Copy) ---" << std::endl;
  // 'obj2' is passed by value -> Copy Constructor called -> operator= called
  obj1 = obj2;

  std::cout << "2. Assignment with rvalue (Move) ---" << std::endl;
  // 'std::move(obj2)' is passed -> Move Constructor called -> operator= called
  obj1 = std::move(obj2);

  return 0;
}
