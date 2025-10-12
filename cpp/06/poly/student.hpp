#pragma once

#include <string>

#include "person.hpp"

class Student : public Person {
  double gpa_;

 public:
  Student(const std::string& name, double gpa);

  // A virtual destructor enables proper cleanup of derived objects when deleted
  // through base class pointers, with the language allowing destructor
  // overriding despite name differences due to their special role.
  ~Student() override;  // vtable[0]

  void print() const override;  // vtable[1]
};
