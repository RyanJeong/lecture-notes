#pragma once

template <typename T>
class Fun {
  T data_;

 public:
  explicit Fun(const T& data) : data_(data) {}
  ~Fun() = default;

  T get() const { return data_; }
  void set(const T& data) { data_ = data; }
};

#ifdef CPP_NO_BUILD09
template <typename T>
class Fun {
  T data_;

 public:
  explicit Fun(const T& data);
  ~Fun() = default;

  void set(const T& data);
};

template <typename T>
Fun<T>::Fun(const T& d) : data_(d) {}

template <typename T>
void Fun<T>::set(const T& data) {
  data_ = data;
}
#endif  // CPP_NO_BUILD09
