#pragma once

#include <string>

class Person {
  std::string name_;

 public:
  explicit Person(const std::string& name);
  virtual ~Person();  // vtable[0]

  virtual void print() const;  // vtable[1]
};
