#include "my_class.hpp"

#include <algorithm>  // for std::copy
#include <iostream>
#include <utility>  // for std::swap

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

// Just swaps the pointers (very fast).
// It provides the Strong Exception Guarantee (noexcept).
void Swap(MyClass& first, MyClass& second) noexcept {
  std::swap(first.data_, second.data_);
}

// Unified Assignment Operator Implementation.
MyClass& MyClass::operator=(MyClass other) {
  // Strategy: "Copy first."
  // If the copy fails (e.g., bad_alloc), the original (*this) remains safe.
  std::cout << "Unified assignment operator called" << std::endl;

  // Strategy: "Swap if successful."
  // Since the copy succeeded, we swap. This never fails (noexcept).
  Swap(*this, other);

  // Return *this (now holding the new resource).
  return *this;

  // 'other' goes out of scope here.
  // Its destructor is called, releasing the OLD resource automatically.
}
