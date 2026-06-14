#include <iostream>

#include "fun.hpp"

int main() {
  Fun<int> fun1(23);
  fun1.set(100);
  std::cout << "fun1: " << fun1.get() << std::endl;

  Fun<double> fun2(12.7);
  fun2.set(45.6);
  std::cout << "fun2: " << fun2.get() << std::endl;

  Fun<float> fun3(123.4f);
  fun3.set(567.8f);
  std::cout << "fun3: " << fun3.get() << std::endl;
  return 0;
}
