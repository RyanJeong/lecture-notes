#include "fun.hpp"

#include <string>

template <typename T>
Fun<T>::Fun(const T& d) : data_(d) {}

template <typename T>
T Fun<T>::get() const {
  return data_;
}

template <typename T>
void Fun<T>::set(const T& d) {
  data_ = d;
}

// Explicit instantiation
template class Fun<int>;
template class Fun<double>;
template class Fun<std::string>;
