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

#if 0  /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
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
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
