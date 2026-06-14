#include "my_class.hpp"

#include <algorithm>  // for std::copy
#include <iostream>

MyClass::MyClass(MyClass&& other) noexcept : data_(other.data_) {
  other.data_ = nullptr;
  std::cout << "Move constructor called" << std::endl;
}

MyClass::MyClass(const MyClass& other) : data_(nullptr) {
  if (other.data_) {
    data_ = new int[1'000'000];
    std::copy(other.data_, other.data_ + 1'000'000, data_);
    std::cout << "Copy constructor called (new memory allocated)" << std::endl;
  } else {
    std::cout << "Copy constructor called (source was empty)" << std::endl;
  }
}

MyClass& MyClass::operator=(const MyClass& other) {
  if (this != &other) {  // Self-assignment check
    delete[] data_;      // Release old memory

    int* new_data = new int[1'000'000];
    std::copy(other.data_, other.data_ + 1'000'000, new_data);
    data_ = new_data;
    std::cout << "Copy assignment operator called" << std::endl;
  }
  return *this;
}

MyClass& MyClass::operator=(MyClass&& other) noexcept {
  if (this != &other) {  // Self-assignment check
    delete[] data_;      // Release old memory

    data_ = other.data_;  // Transfer ownership
    other.data_ = nullptr;
    std::cout << "Move assignment operator called" << std::endl;
  }
  return *this;
}
