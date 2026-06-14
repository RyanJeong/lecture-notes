#include <string>

class Course;  // forward declaration

class Student {
  static const int kMaxCourse = 5;
  std::string name_;
  Course* course_[kMaxCourse] = {nullptr};

 public:
  explicit Student(const std::string& n) : name_(n) {}

  void AddCourse(Course* course) {
    for (int i = 0; i < kMaxCourse; ++i) {
      if (course_[i]) continue;
      course_[i] = course;
      break;
    }
  }
};
