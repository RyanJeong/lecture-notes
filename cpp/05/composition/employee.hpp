#pragma once

#include <cassert>
#include <iostream>
#include <string>

#include "name.hpp"

class Employee {
  Name name_;
  double salary_;

 public:
  Employee(const std::string& fst, const std::string& i, const std::string& lst,
           double salary);

  void Print() const;
};
