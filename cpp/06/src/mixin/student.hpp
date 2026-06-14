#pragma once

#include <string>

#include "person.hpp"
#include "stdtype.hpp"

class Student : public Person, public StdType {
 public:
  Student(const std::string& name, double gpa);
  ~Student() = default;

  void PrintGpa() const override;

  void Print() const;
};
