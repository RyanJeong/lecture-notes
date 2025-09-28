#include <cassert>
#include <iostream>

#ifdef CPP_05_NOBUILD
class Person {
  int64_t identity_;

 public:
  void set(int64_t id) { (assert(id >= 1e8 && id < 1e9)), identity_ = id; }
  void Print() const { std::cout << "Person's ID: " << identity_ << std::endl; }
};

class Student : public Person {
  double gpa_;

 public:
  void set(int64_t id) { Person::set(id); }  // Function overload
  void set(double gpa) { (assert(gpa >= 0 && gpa <= 4.0)), gpa_ = gpa; }
  void Print() const {  // Function override
    Person::Print();
    std::cout << "Student's GPA: " << gpa_ << std::endl;
  }
};
#endif  // CPP_05_NOBUILD

class Person {
  int64_t identity_;

 public:
  void set(int64_t id) { (assert(id >= 1e8 && id < 1e9)), identity_ = id; }
  int get() const { return identity_; }
  void Print() const { std::cout << "Person's ID: " << identity_ << std::endl; }
};

class Student : public Person {
  double gpa_;

 public:
  void set(int64_t id) { Person::set(id); }  // Function overload
  void set(double gpa) { (assert(gpa >= 0 && gpa <= 4.0)), gpa_ = gpa; }
  void Print() const {  // Function override
    Person::Print();
    std::cout << "Student's GPA: " << gpa_ << std::endl;
  }
};

int main() {
  Person person;
  person.set(123456789L);  // try to invoke a `set` function of the Person class
  person.get();            // try to invoke a `get` function of the Person class

  Student student;
  student.set(3.9);  // try to invoke a `set` function of the Student class
  student.get();     // try to invoke a `get` function of the Person class
}

#ifdef CPP_05_NOBUILD
class Person {
  int64_t identity_;

 public:
  void set(int64_t id) { (assert(id >= 1e8 && id < 1e9)), identity_ = id; }
  void Print() const { std::cout << "Person's ID: " << identity_ << std::endl; }
};

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

int main() {
  Person person;
  person.set(111111111L);  // `person` invokes a Person::set function
  Student student;
  student.set(987654321L, 3.7);  // `student` invokes a Student::set function
  return 0;
}
#endif  // CPP_05_NOBUILD

#ifdef CPP_05_NOBUILD
// The class `First` is not inheritable
class First final;
class Second : public First;  // Error: cannot derive from 'final' base 'First'

// The class `First` is inheritable, but the class `Second` is not.
class First;
class Second final : public First;
class Third : public Second;  // Error: cannot derive from 'final' base 'Second'
#endif                        // CPP_05_NOBUILD

#ifdef CPP_05_NOBUILD
class Base {
 public:
  void Foo() { std::cout << "Base::Foo" << std::endl; }
};

class Derived : protected Base {
  // Foo() is accessible in Derived, but not accessible outside Derived
};

void FreeFunction() {
  Derived derived;
  // derived.Foo();  // Error: 'Foo' is a protected member of 'Base'
}
#endif  // CPP_05_NOBUILD

#ifdef CPP_05_NOBUILD
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
#endif  // CPP_05_NOBUILD
