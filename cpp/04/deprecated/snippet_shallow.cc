#include <cstring>
#include <iostream>

class ShallowCopy {
  char* data_;

 public:
  explicit ShallowCopy(const char* s) : data_(new char[std::strlen(s) + 1]) {
    std::strcpy(data_, s);  // Copy string data
    std::cout << "Constructor called for: " << data_ << std::endl;
  }
  // Note: Copy constructor is missing, so the compiler creates a default one
  // that performs shallow copy (just copies the pointer, not what it points to)
  ~ShallowCopy() {
    std::cout << "Destructor called for: " << data_ << std::endl;
    delete[] data_;  // Will cause double-free error
  }
};

int main() {
  ShallowCopy obj1("Hello");

  // shallow copy occurs here - both objects now share same memory
  ShallowCopy obj2(obj1);  // it converts to ShallowCopy obj2 = obj1; (implicit)
  return 0;
  // `obj2` shares the same memory with `obj1`, so delete[] gets called
  // multiple times (it leads to memory issues)
}
