#pragma once

#include <deque>  // for std::deque

template <typename T, typename Container = std::deque<T>>
class stack {
 private:
  Container c;

 public:
  void push(const T& val) { c.push_back(val); }
  void pop() { c.pop_back(); }
  T& top() { return c.back(); }
  bool empty() const { return c.empty(); }
  size_t size() const { return c.size(); }
};
