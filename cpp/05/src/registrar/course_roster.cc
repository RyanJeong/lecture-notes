#include "course_roster.hpp"

#include <iostream>
#include <string>

void CourseRoster::Print() const {
  std::cout << "List of Students" << std::endl;
  for (int i = 0; i < size_; ++i) std::cout << student_names_[i] << std::endl;
  std::cout << std::endl;
}

void CourseRoster::AddStudent(const std::string& student_name) {
  if (size_ < capacity_) {
    // Add the student to the roster
    student_names_[size_++] = student_name;
  }
}
