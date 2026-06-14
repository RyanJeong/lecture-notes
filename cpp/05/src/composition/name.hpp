#pragma once

#include <string>

class Name {
  std::string first_;
  std::string init_;
  std::string last_;

 public:
  Name(const std::string& first, const std::string& init,
       const std::string& last);

  void Print() const;
};
