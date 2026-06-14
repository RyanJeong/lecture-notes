#pragma once

#include <cassert>
#include <iostream>

#include "date.hpp"

class Person {
  int64_t id_;
  Date birth_date_;

 public:
  Person(int64_t id, const Date& date) : id_(id), birth_date_(date) {
    assert(id_ >= 1e8 && id_ < 1e9);
  }

  void Print() const {
    std::cout << "Person Identity: " << id_ << std::endl;
    std::cout << "Person date of birth: ";
    birth_date_.Print();
  }
};
