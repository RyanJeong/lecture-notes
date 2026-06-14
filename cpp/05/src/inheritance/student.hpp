#pragma once

#include <cassert>
#include <iomanip>
#include <iostream>

#include "person.hpp"

class Student : public Person {
  double gpa_;

 public:
  Student() : Person(), gpa_(0.0) {}
  Student(int64_t id, double gpa) : Person(id), gpa_(gpa) {
    assert(gpa_ >= 0.0 && gpa_ <= 4.0);
  }

  void Print() const {
    Person::Print();
    std::cout << "GPA: " << std::setprecision(2) << gpa_ << std::endl;
  }
};
