#pragma once

#include <cassert>
#include <iostream>

class Person {
  int64_t id_;

 public:
  Person() : id_(0) {}
  explicit Person(int64_t id) : id_(id) { assert(id_ >= 1e8 && id_ < 1e9); }

  void Print() const { std::cout << "Identity: " << id_ << std::endl; }
};
