#include <iostream>

int64_t fib(int n) {
  if (n == 0 || n == 1) return n;  // Base case
  return fib(n - 1) + fib(n - 2);  // General case
}

int main() {
  for (int i = 1; i <= 40; ++i)
    std::cout << "fib(" << i << "): " << fib(i) << std::endl;
  return 0;
}
