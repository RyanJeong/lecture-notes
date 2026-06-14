#pragma once

#include <string>

class StudentSchedule {
 private:
  int size_;
  const int capacity_ = 5;
  std::string* course_names_;

 public:
  StudentSchedule() : size_(0), course_names_(new std::string[capacity_]) {}
  ~StudentSchedule() { delete[] course_names_; }

  void Print() const;
  void AddCourse(const std::string& course_name);
};
