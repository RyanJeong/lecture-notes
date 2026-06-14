#include "student.hpp"

#include <iostream>
#include <string>

void Student::Print() const {
  std::cout << "Student name: " << name_ << std::endl;
  schedule_->Print();
}

void Student::AddCourse(const std::string& course_name) {
  // Add the course to the schedule
  schedule_->AddCourse(course_name);
}
