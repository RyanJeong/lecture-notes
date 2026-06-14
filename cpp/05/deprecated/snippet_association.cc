#ifdef CPP_05_NOBUILD
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
#endif  // CPP_05_NOBUILD

#ifdef CPP_05_NOBUILD
#include <string>

class Student;  // forward declaration

class Course {
  static const int kMaxStudent = 40;
  std::string title_;
  Student* student_[kMaxStudent] = {nullptr};

 public:
  explicit Course(const std::string& t) : title_(t) {}

  void AddStudent(Student* student) {
    for (int i = 0; i < kMaxStudent; ++i) {
      if (student_[i]) continue;
      student_[i] = student;
      student->AddCourse(this);
      break;
    }
  }
};
#endif  // CPP_05_NOBUILD
