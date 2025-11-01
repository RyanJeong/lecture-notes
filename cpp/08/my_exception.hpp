#pragma once

#include <exception>
#include <string>

class MyException : public std::exception {
 public:
  MyException(const std::string& what, const std::string& where) noexcept
      : what_(what), where_(where) {}
  ~MyException() noexcept override = default;

  const char* what() const noexcept override { return what_.c_str(); }
  const char* where() const noexcept { return where_.c_str(); }

 private:
  const std::string what_;
  const std::string where_;
};
