#include "course.hpp"

#include <iostream>
#include <string>

void Course::Print() const {
  std::cout << "Course Name: " << name_ << std::endl;
  std::cout << "Number of Units: " << units_ << std::endl;
  roster_->Print();
}

void Course::AddStudent(const std::string& student_name) {
  // Add the student to the roster
  roster_->AddStudent(student_name);
}
