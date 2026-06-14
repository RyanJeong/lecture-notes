#pragma once

#include <string>

#include "person.hpp"

class Student : virtual public Person {
 protected:
  double gpa_;

 public:
  Student(const std::string& name, double gpa);
  ~Student() = default;

  void Print() const;
};
