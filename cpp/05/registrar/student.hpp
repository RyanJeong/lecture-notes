#pragma once

#include <iostream>
#include <string>

#include "student_schedule.hpp"

class Student {
 private:
  std::string name_;
  StudentSchedule* schedule_;

 public:
  explicit Student(const std::string& student_name)
      : name_(student_name), schedule_(new StudentSchedule) {}
  ~Student() { delete schedule_; }

  std::string name() const { return name_; }
  StudentSchedule* schedule() const { return schedule_; }
  void Print() const;
  void AddCourse(const std::string& course_name);
};
