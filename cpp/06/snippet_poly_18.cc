#include <string>

class Person {
  std::string name_;

 public:
  explicit Person(const std::string& name) : name_(name) {}
  virtual ~Person() = default;  // Virtual destructor
};

class Student : public Person {
  double gpa_;

 public:
  Student(const std::string& name, double gpa) : Person(name), gpa_(gpa) {}
  ~Student() override = default;
};

int main() {
  Person* ptr = new Student("John", 3.8);
  delete ptr;  // It correctly deletes `Student` because of the virtual
               // destructor. No memory leak occurs.
  return 0;
}
