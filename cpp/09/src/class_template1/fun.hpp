#pragma once

template <typename T>
class Fun {
  T data_;

 public:
  explicit Fun(const T& data);
  ~Fun() = default;

  T get() const;
  void set(const T& data);
};
