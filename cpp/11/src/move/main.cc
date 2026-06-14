#include <utility>  // for std::move

#include "my_class.hpp"

void SwapUsingCopy(MyClass& first, MyClass& second) {
  MyClass temp(first);
  first = second;
  second = temp;
}

void SwapUsingMove(MyClass& first, MyClass& second) {
  MyClass temp(std::move(first));
  first = std::move(second);
  second = std::move(temp);
}

int main() {
  MyClass obj1, obj2;
  SwapUsingCopy(obj1, obj2);
  SwapUsingMove(obj1, obj2);
  return 0;
}
