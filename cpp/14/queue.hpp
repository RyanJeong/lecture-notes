#pragma once

#include <deque>  // for std::deque

template <typename T, typename Container = std::deque<T>>
class queue {
 private:
  Container c;

 public:
  void push(const T& val) { c.push_back(val); }
  void pop() { c.pop_front(); }
  T& front() { return c.front(); }
  T& back() { return c.back(); }
};
