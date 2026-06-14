#pragma once

#include <string>

class CourseRoster {
  int size_;
  const int capacity_ = 20;
  std::string* student_names_;

 public:
  CourseRoster() : size_(0), student_names_(new std::string[capacity_]) {}
  ~CourseRoster() { delete[] student_names_; }

  void Print() const;
  void AddStudent(const std::string& student_name);
};
