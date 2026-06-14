#pragma once

#include <string>

#include "person.hpp"
#include "prftype.hpp"

class Professor : public Person, public PrfType {
 public:
  Professor(const std::string& name, double salary);
  ~Professor() = default;

  void PrintSalary() const override;

  void Print() const;
};
