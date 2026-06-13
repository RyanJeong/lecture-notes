#include <iostream>

int main() {
  int a = 10;
  int& ref = a;  // `ref` is a reference to `a`.

  // The address of `a` and `ref` are the same
  std::cout << "Address of a: " << &a << std::endl;
  std::cout << "Address of ref: " << &ref
            << std::endl;  // Outputs the same address as `a`.

  // Example where the reference might not have a distinct address:
  int* ptr = &a;     // Pointer to `a`.
  int& ref2 = *ptr;  // Reference to `a` through pointer `ptr`.

  std::cout << "Address of ptr: " << ptr << std::endl;
  std::cout << "Address of ref2: " << &ref2
            << std::endl;  // Same as `a` and `ptr`.
  return 0;
}