#pragma once

#include <string>

#include "professor.hpp"
#include "student.hpp"

class TA : public Professor, public Student {
 public:
  TA(const std::string& name, double gpa, double sal);
  ~TA() = default;

  void Print() const;
};
