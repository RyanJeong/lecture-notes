#pragma once

namespace std {
class exception {
 public:
  exception() noexcept;
  exception(const exception& other) noexcept;
  exception& operator=(const exception& other) noexcept;
  virtual ~exception() noexcept;

  virtual const char* what() const noexcept;
};
}  // namespace std

