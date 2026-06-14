#pragma once

#include <string>

class Person {
 protected:
  std::string name_;

 public:
  explicit Person(const std::string& name);
  ~Person() = default;

  void Print() const;
};
