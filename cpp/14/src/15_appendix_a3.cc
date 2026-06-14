#include <iostream>
#include <string>
#include <utility>
#include <vector>

class Student {
  int id_;
  std::string name_;

 public:
  Student(int id, const std::string& name);
  Student(Student&& other) noexcept;
  Student(const Student& other);
  ~Student();
};

Student::Student(int id, const std::string& name) : id_(id), name_(name) {
  std::cout << "Ctor: " << id_ << ", " << name_ << std::endl;
}
Student::Student(Student&& other) noexcept
    : id_(other.id_), name_(std::move(other.name_)) {
  std::cout << "Move Ctor:" << id_ << ", " << name_ << std::endl;
}
Student::Student(const Student& other) : id_(other.id_), name_(other.name_) {
  std::cout << "Copy Ctor:" << id_ << ", " << name_ << std::endl;
}
Student::~Student() {
  std::cout << "Dtor: " << id_ << ", " << name_ << std::endl;
}

int main() {
  std::vector<Student> students;
  students.reserve(100);  // Pre-allocate memory to avoid reallocation noise

  // 1. push_back with temporary object
  // [Correction] This calls Move Ctor, NOT Copy Ctor (in C++11+).
  // Overhead: Constructor (temp) + Move Ctor + Destructor (temp)
  students.push_back(Student(101, "Alice"));

  // 2. emplace_back with arguments
  // [Optimization] Perfectly efficient.
  // Constructs the object directly in the vector's memory.
  // No temporary object created, no move, no copy.
  students.emplace_back(102, "Bob");

  // 3. push_back with temporary object
  // Same as Alice. Inefficient compared to emplace_back.
  // Wasted cost: 1 Move + 1 Destructor call for the temporary.
  students.push_back(Student(103, "Charlie"));

  // 4. emplace_back with arguments
  // [Correction] This is Direct Construction, NOT Move Ctor.
  // Just like Bob, this avoids the overhead of creating/moving a temporary.
  students.emplace_back(104, "David");

  return 0;
}
