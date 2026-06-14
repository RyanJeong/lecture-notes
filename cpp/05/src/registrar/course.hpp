#pragma once

#include <string>

#include "course_roster.hpp"

class Course {
  std::string name_;
  int units_;
  CourseRoster* roster_;

 public:
  Course(const std::string& course_name, int units)
      : name_(course_name), units_(units), roster_(new CourseRoster) {}
  ~Course() { delete roster_; }

  std::string name() const { return name_; }
  CourseRoster* roster() const { return roster_; }
  void Print() const;
  void AddStudent(const std::string& student_name);
};
