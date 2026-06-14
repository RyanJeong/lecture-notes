#if 1 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
#include <iostream>
#include <utility>  // for std::forward

void Identify(int& x) { std::cout << "int&: " << x << std::endl; }
void Identify(const int& x) { std::cout << "const int&: " << x << std::endl; }
void Identify(int&& x) { std::cout << "int&&: " << x << std::endl; }

template <typename T>
void PerfectForwarding(T&& arg) {
  std::cout << std::endl << "1. Without std::forward" << std::endl;
  Identify(arg);

  std::cout << std::endl << "2. With std::forward" << std::endl;
  Identify(std::forward<T>(arg));
}
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */

int main() {
#if 1 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
  int a = 10;
  PerfectForwarding(a);  // Passing lvalue
#endif                   /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */

#if 1 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
  const int b = 20;
  PerfectForwarding(b);  // Passing const lvalue
#endif                   /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */

#if 1                     /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
  PerfectForwarding(30);  // Passing rvalue
#endif                    /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */

  return 0;
}
