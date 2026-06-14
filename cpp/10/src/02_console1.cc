#if 1 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
#include <iostream>

int main() {
  // When sync_with_stdio(true) [default]:
  // - C++ streams are subject to C stream rules
  // - Most C standard library implementations automatically flush the stdout
  //   buffer BEFORE reading from stdin. This is a C-level behavior, separate
  //   from C++'s tie() mechanism.
  // - This automatic flush occurs even without explicit flush() or tie().
  std::ios::sync_with_stdio(false);

  // Disable tie() between std::cin and std::cout
  // - By default, std::cin.tie(&std::cout) automatically flushes std::cout
  //   buffer when std::cin is called.
  // - When tie(nullptr) is called, this C++-level automatic flush is disabled.
  std::cin.tie(nullptr);

  int number;
  std::cout << "Enter a number:";  // Prompt may not appear immediately
  std::cin >> number;
  return 0;
}
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */

void Foo() {
#if 1 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */

#if 1 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
  int number;
  std::cout << "Enter a number:";
  std::cin >> number;
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
}
