#include "professor.hpp"

#include <iostream>
#include <string>

Professor::Professor(const std::string& nm, double sal) : Person(nm) {
  salary_ = sal;
}

void Professor::PrintSalary() const {
  std::cout << "Salary: " << salary_ << std::endl;
}

void Professor::Print() const {
  PrintName();
  PrintSalary();
  std::cout << std::endl;
}
