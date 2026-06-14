#include <string>

#if 1 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
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
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */

int main() {
#if 1 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
  Person* ptr = new Student("John", 3.8);
  delete ptr;  // It correctly deletes `Student` because of the virtual
               // destructor. No memory leak occurs.
#endif         /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */

  (void) ptr;  // Avoid unused variable warning.
  return 0;
}
