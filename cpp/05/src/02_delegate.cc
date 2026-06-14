#include <cassert>
#include <iostream>

#if 1 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
class Person {
  int64_t identity_;

 public:
  void set(int64_t id) { (assert(id >= 1e8 && id < 1e9)), identity_ = id; }
  void Print() const { std::cout << "Person's ID: " << identity_ << std::endl; }
};
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */

#if 1 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
class Student : public Person {
  double gpa_;

 public:
  void set(int64_t id, double gpa) {
    Person::set(id);  // Delegate to Person::set
    (assert(gpa >= 0 && gpa <= 4.0)), gpa_ = gpa;
  }
  void Print() const {
    Person::Print();  // Delegate to Person::Print
    std::cout << "Student's GPA: " << gpa_ << std::endl;
  }
};
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */

void Snippet1(void) {
#if 1 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
  Person person;
  person.set(111111111L);  // `person` invokes a Person::set function

  Student student;
  student.set(987654321L, 3.7);  // `student` invokes a Student::set function
#endif                           /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */

  (void) person;   // Avoid unused variable warning.
  (void) student;  // Avoid unused variable warning.
}
