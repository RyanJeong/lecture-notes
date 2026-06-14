#include <cassert>
#include <iostream>

class Person {
  int64_t id_;

 public:
  void set_id(int64_t id) { (assert(id >= 1e8 && id < 1e9)), id_ = id; }
  int64_t get_id() const { return id_; }
};

class Student : public Person {
  double gpa_;

 public:
  void set_gpa(double gpa) { (assert(gpa >= 0 && gpa <= 4.0)), gpa_ = gpa; }
  double get_gpa() const { return gpa_; }
};

int main() {
  Person person;
  person.set_id(123456789L);
  std::cout << "Person’s ID: " << person.get_id() << std::endl << std::endl;

  Student student;
  student.set_id(987654321L);
  student.set_gpa(3.9);
  std::cout << "Student’s ID: " << student.get_id() << std::endl;
  std::cout << "Student’s GPA: " << student.get_gpa() << std::endl << std::endl;

  Person test_person;
  test_person.set_id(12345654321L);
  return 0;
}
