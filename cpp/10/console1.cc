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

void Foo() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int number;
  std::cout << "Enter a number:";
  std::cin >> number;
}
