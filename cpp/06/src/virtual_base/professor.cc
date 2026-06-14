#include "professor.hpp"

#include <iostream>
#include <string>

Professor::Professor(const std::string& nm, double sal)
    : Person(nm), salary_(sal) {}

void Professor::Print() const {
  std::cout << "Professor" << std::endl;
  std::cout << "Name: " << name_ << " ";
  std::cout << "Salary: " << salary_ << std::endl << std::endl;
}
