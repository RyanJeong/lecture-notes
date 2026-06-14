#pragma once

#include <string>

#include "person.hpp"

class Professor : virtual public Person {
 protected:
  double salary_;

 public:
  Professor(const std::string& name, double salary);
  ~Professor() = default;

  void Print() const;
};
