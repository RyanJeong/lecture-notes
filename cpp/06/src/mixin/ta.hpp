#pragma once

#include <string>

#include "person.hpp"
#include "prftype.hpp"
#include "stdtype.hpp"

class TA : public Person, public StdType, public PrfType {
 public:
  TA(const std::string& name, double gpa, double sal);
  ~TA() = default;

  void PrintGpa() const override;
  void PrintSalary() const override;

  void Print() const;
};
