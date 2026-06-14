#include <cassert>
#include <iostream>

#if 1 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
class Person {
  int64_t identity_;

 public:
  void set(int64_t id) { (assert(id >= 1e8 && id < 1e9)), identity_ = id; }
};

class Student : public Person {
  double gpa_;

 public:
  // Function override
  void set(int64_t id) { Person::set(id); }

  // Function overload
  void set(double gpa) { (assert(gpa >= 0 && gpa <= 4.0)), gpa_ = gpa; }
};
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */

void Snippet1(void) {
#if 1 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
  Person person;
  person.set(123456789L);  // try to invoke a `set` function of the Person class

  Student student;
  student.set(3.9);  // try to invoke a `set` function of the Student class
#endif               /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */

  (void) person;   // Avoid unused variable warning.
  (void) student;  // Avoid unused variable warning.
}
