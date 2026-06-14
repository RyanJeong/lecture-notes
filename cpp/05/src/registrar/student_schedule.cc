#include "student_schedule.hpp"

#include <iostream>
#include <string>

void StudentSchedule::Print() const {
  std::cout << "List of Courses" << std::endl;
  for (int i = 0; i < size_; ++i) std::cout << course_names_[i] << std::endl;
  std::cout << std::endl;
}

void StudentSchedule::AddCourse(const std::string& course_name) {
  if (size_ < capacity_) {
    // Add the course to the schedule
    course_names_[size_++] = course_name;
  }
}
