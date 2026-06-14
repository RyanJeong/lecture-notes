#include "ta.hpp"

#include <iostream>
#include <string>

TA::TA(const std::string& nm, double gp, double sal)
    : Person(nm), Professor(nm, sal), Student(nm, gp) {}

void TA::Print() const {
  std::cout << "Teaching Assistance" << std::endl;
  std::cout << "Name: " << name_ << " ";
  std::cout << "GPA: " << gpa_ << " ";
  std::cout << "Salary: " << salary_ << std::endl << std::endl;
}
