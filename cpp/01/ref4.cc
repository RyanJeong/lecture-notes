#include <cstdint>  // for uintptr_t
#include <iostream>

struct Foo {
  char c;  // 1 byte for the char member
  // The following expression will be converted to 'int* const ref'.
  int& ref;  // It takes 4 bytes on a 32-bit OS and 8 bytes on a 64-bit OS.
};

int main() {
  int i = 100;
  Foo f = {'a', i};  // Partial initialization is not allowed because 'ref' must
                     // be initialized.
  // Print the size of the Foo struct, which includes padding.
  std::cout << "Size of Foo: " << sizeof(f) << " bytes" << std::endl;

  // Print the address of 'i' and 'f.ref' to show they are the same.
  std::cout << "Address of i: " << &i << std::endl;
  std::cout << "Address of f.ref: " << &f.ref << std::endl;

  // uintptr_t is an unsigned integer type that is capable of holding a pointer.
  // It is used here to perform pointer arithmetic in a safe and portable
  // manner. The reinterpret_cast is used to convert the pointer to an integer
  // type.
  uintptr_t f_addr = reinterpret_cast<uintptr_t>(&f);
  std::cout << "Address of f: " << &f << std::endl;

  // Calculate the address of f + 8 (which should point to where ref is stored)
  // and then dereference it to get the value of the original int (i).
  int* ref_address = *reinterpret_cast<int**>(f_addr + 8);
  std::cout << "Address of f + 8: " << ref_address << std::endl;
  std::cout << "Dereferenced value at f + 8: " << *ref_address << std::endl;
  return 0;
}