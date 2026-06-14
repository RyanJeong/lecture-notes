#pragma once

class MyClass {
  int* data_;

 public:
  MyClass() : data_(new int[1'000'000]) {}

  ~MyClass() {
    if (data_) delete[] data_;
  }

  MyClass(const MyClass& other);      // Copy constructor (Required)
  MyClass(MyClass&& other) noexcept;  // Move constructor (Required)

  // Unified assignment operator using Copy-and-Swap idiom.
  // Note: Parameter is passed by value ('MyClass other'), not by reference.
  MyClass& operator=(MyClass other);

  // Friend swap function to exchange resources efficiently.
  friend void Swap(MyClass& first, MyClass& second) noexcept;
};
