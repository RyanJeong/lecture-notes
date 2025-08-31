#include <iostream>

int main() {
  int a = 10;
  int& ref = a;  // `ref` is a reference to `a`.

  // Modifying `ref` will also modify `a`.
  ref += 5;
  std::cout << "a = " << a << std::endl;  // Output: "a = 15"
  return 0;
}
