#if 0  /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
// The class `First` is not inheritable
class First final;
class Second : public First;  // Error: cannot derive from 'final' base 'First'
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */

#if 0  /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
// The class `First` is inheritable, but the class `Second` is not.
class First;
class Second final : public First;
class Third : public Second;  // Error: cannot derive from 'final' base 'Second'
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */

#include <iostream>

#if 0  /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
class Base {
 public:
  void Foo() { std::cout << "Base::Foo" << std::endl; }
};

// Foo() is accessible in Derived, but not accessible outside Derived
class Derived : protected Base {};

void FreeFunction() {
  Derived derived;
  derived.Foo();  // Error: 'Foo' is a protected member of 'Base'
}
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */

#if 1 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
class Timer {
 public:
  void Start();
  void Stop();
};

// The class `Stopwatch` wants to use the functionality of Timer. However,
// `Stopwatch` is not a subtype of Timer.
class Stopwatch : private Timer {
 public:
  void StartLap() { Timer::Start(); }
  void EndLap() { Timer::Stop(); }
};
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */

#if 0 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
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
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */