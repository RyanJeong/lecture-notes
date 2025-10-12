#include <string>

class Person {
  std::string name;

 public:
  explicit Person(const std::string& name) : name(name) {}
  ~Person() = default;  // Not virtual destructor
};

class Student : public Person {
  double gpa;

 public:
  Student(const std::string& name, double gpa) : Person(name), gpa(gpa) {}
  ~Student() = default;
};

int main() {
  Person* ptr = new Student("John", 3.8);
  delete ptr;  // It does not correctly delete `Student` because the type of the
               // `ptr` is `Person*`; destructor of `Student` is not called.
               // Memory leak occurs.
  return 0;
}
