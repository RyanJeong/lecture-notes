#pragma once

#include <algorithm>   // for std::push_heap, std::pop_heap
#include <functional>  // for std::less
#include <vector>      // for std::vector

#if 1  // DO NOT CONTAIN THIS LINE IN THE MARKDOWN
template <typename T, typename Container = std::vector<T>,
          typename Compare = std::less<T>>
class priority_queue {
 private:
  Container c;
  Compare comp;

 public:
  void push(const T& val) {
    c.push_back(val);
    std::push_heap(c.begin(), c.end(), comp);  // O(log n)
  }
  void pop() {
    std::pop_heap(c.begin(), c.end(), comp);  // O(log n)
    c.pop_back();
  }
  T& top() { return c.front(); }
};
#endif  // DO NOT CONTAIN THIS LINE IN THE MARKDOWN
