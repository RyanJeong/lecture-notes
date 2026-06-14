#include "student.hpp"

#include <cassert>
#include <iostream>
#include <string>

Student::Student(const std::string& name, double gp) : Person(name), gpa_(gp) {
  assert(gpa_ <= 4.0);
}

void Student::Print() const {
  std::cout << "Student" << std::endl;
  std::cout << "Name: " << name_ << " ";
  std::cout << "GPA: " << gpa_ << std::endl << std::endl;
}
