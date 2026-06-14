#include <iostream>

int main() {
  int a = 10;
  int b = 20;

  // `ref` is a reference to `a`.
  int& ref = a;

  // Attempting to change the reference to another variable will modify the
  // original variable instead.
  ref = b;  // This does not change `ref` to refer to `b`, it changes the value
            // of `a` to 20.

  std::cout << "a = " << a << std::endl;      // Output: "a = 20"
  std::cout << "ref = " << ref << std::endl;  // Output: "ref = 20"
  return 0;
}