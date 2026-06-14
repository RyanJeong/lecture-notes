#pragma once

class MyClass {
  int* data_;

 public:
  MyClass() : data_(new int[1'000'000]) {}

  ~MyClass() {
    if (data_) delete[] data_;
  }

  MyClass(const MyClass& other);      // Copy constructor
  MyClass(MyClass&& other) noexcept;  // Move constructor

  MyClass& operator=(const MyClass& other);      // Copy assignment operator
  MyClass& operator=(MyClass&& other) noexcept;  // Move assignment operator
};
