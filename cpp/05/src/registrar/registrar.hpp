#pragma once

#include "course.hpp"
#include "student.hpp"

class Registrar {
 public:
  // Enroll a student in a course
  void Enroll(const Student& student, const Course& course) {
    course.roster()->AddStudent(student.name());
    student.schedule()->AddCourse(course.name());
  }
};
