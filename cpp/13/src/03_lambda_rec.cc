#include <functional>  // for std::function
#include <iostream>

int main() {
  std::function<int64_t(int64_t)> fib = [&fib](int64_t n) -> int64_t {
    if (n == 0 || n == 1) return n;  // Base case
    return fib(n - 1) + fib(n - 2);  // General case (recursive call)
  };
  std::cout << "fib(10): " << fib(static_cast<int64_t>(10)) << std::endl;
  return 0;
}
