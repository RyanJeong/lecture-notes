#pragma once

// Basic iterator structure (conceptual)
template <typename T>
class Iterator {
 private:
  T* ptr;  // Pointer
 public:
  T& operator*() const { return *ptr; }  // Dereference
  T* operator->() const { return ptr; }  // Member access
  Iterator& operator++() {
    ++ptr;
    return *this;
  }  // Pre-increment
  bool operator!=(const Iterator& other) const { return ptr != other.ptr; }
};

// Algorithm functions access only through iterators
template <typename InputIt, typename T>
InputIt find(InputIt first, InputIt last, const T& value) {
  for (; first != last; ++first) {
    if (*first == value) return first;  // Dereference and compare
  }
  return last;
}
