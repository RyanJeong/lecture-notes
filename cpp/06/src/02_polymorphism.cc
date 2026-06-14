#include <string>

#if 1 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
class Person {
  std::string name_;

 public:
  explicit Person(const std::string& name) : name_(name) {}
  ~Person() = default;  // Not virtual destructor
};

class Student : public Person {
  double gpa_;

 public:
  Student(const std::string& name, double gpa) : Person(name), gpa_(gpa) {}
  ~Student() = default;
};
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */

int main() {
#if 1 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
  Person* ptr = new Student("John", 3.8);
  delete ptr;  // It does not correctly delete `Student` because the type of the
               // `ptr` is `Person*`; destructor of `Student` is not called.
               // Memory leak occurs.
#endif         /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */

  (void) ptr;  // Avoid unused variable warning.
  return 0;
}
