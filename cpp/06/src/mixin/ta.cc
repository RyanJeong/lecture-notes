#include "ta.hpp"

#include <iostream>
#include <string>

TA::TA(const std::string& nm, double gp, double sal) : Person(nm) {
  gpa_ = gp;
  salary_ = sal;
}

void TA::PrintGpa() const { std::cout << "GPA: " << gpa_ << std::endl; }

void TA::PrintSalary() const {
  std::cout << "Salary: " << salary_ << std::endl;
}

void TA::Print() const {
  PrintName();
  PrintGpa();
  PrintSalary();
  std::cout << std::endl;
}
