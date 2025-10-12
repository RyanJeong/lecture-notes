#include <string>

class Person {
  std::string name;

 public:
  explicit Person(const std::string& name) : name(name) {}
  virtual ~Person() = default;  // Virtual destructor
};

class Student : public Person {
  double gpa;

 public:
  Student(const std::string& name, double gpa) : Person(name), gpa(gpa) {}
  ~Student() override = default;
};

int main() {
  Person* ptr = new Student("John", 3.8);
  delete ptr;  // It correctly deletes `Student` because of the virtual
               // destructor. No memory leak occurs.
  return 0;
}
