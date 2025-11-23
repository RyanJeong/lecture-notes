#include <iostream>
#include <utility>  // for std::forward

void Identify(int& x) { std::cout << "int&" << std::endl; }
void Identify(const int& x) { std::cout << "const int&" << std::endl; }
void Identify(int&& x) { std::cout << "int&&" << std::endl; }

template <typename T>
void PerfectForwarding(T&& arg) {
  std::cout << std::endl << "1. Without std::forward" << std::endl;
  Identify(arg);

  std::cout << std::endl << "2. With std::forward" << std::endl;
  Identify(std::forward<T>(arg));
}

int main() {
  int a = 10;
  PerfectForwarding(a);  // Passing lvalue

  const int b = 20;
  PerfectForwarding(b);  // Passing const lvalue

  PerfectForwarding(30);  // Passing rvalue
  return 0;
}
