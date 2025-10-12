#include "student.hpp"

#include <iostream>
#include <string>

Student::Student(const std::string& nm, double gp) : Person(nm), gpa_(gp) {
  std::cout << "Student's ctor" << std::endl;
}

Student::~Student() { std::cout << "Student's dtor" << std::endl; }

void Student::print() const {
  Person::print();
  std::cout << "GPA: " << gpa_ << std::endl;
}
