#include "student.hpp"

#include <iostream>
#include <string>

Student::Student(const std::string& name, double gp) : Person(name) {
  gpa_ = gp;
}

void Student::PrintGpa() const { std::cout << "GPA: " << gpa_ << std::endl; }

void Student::Print() const {
  PrintName();
  PrintGpa();
  std::cout << std::endl;
}
