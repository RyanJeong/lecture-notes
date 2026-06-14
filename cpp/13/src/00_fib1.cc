#include <iostream>

#if 1 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
int64_t fib(int n) {
  if (n == 0 || n == 1) return n;  // Base case
  return fib(n - 1) + fib(n - 2);  // General case
}
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */

int main() {
  for (int i = 1; i <= 40; ++i)
    std::cout << "fib(" << i << "): " << fib(i) << std::endl;
  return 0;
}
