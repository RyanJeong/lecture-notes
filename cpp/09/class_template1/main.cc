#include <iostream>
#include <string>

#include "fun.hpp"

int main() {
  Fun<int> fun1(23);
  fun1.set(100);
  std::cout << "fun1: " << fun1.get() << std::endl;

  Fun<double> fun2(12.7);
  fun2.set(45.6);
  std::cout << "fun2: " << fun2.get() << std::endl;

  Fun<std::string> fun3("Hello");
  fun3.set("World");
  std::cout << "fun3: " << fun3.get() << std::endl;

  // Fun<float> fun4(123.4f);  // there's no explicit instantiation for float
  // -> undefined reference to `Fun<float>::Fun(float const&)'
  return 0;
}
