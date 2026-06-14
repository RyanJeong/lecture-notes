#pragma once

#include <list>
#include <vector>

#if 0   // DO NOT CONTAIN THIS LINE IN THE MARKDOWN
// Algorithm does not know container directly
// Only iterator interface needed
template <typename InputIt, typename T>
InputIt find(InputIt first, InputIt last, const T& value) {
  for (; first != last; ++first) {
    if (*first == value) return first;
  }
  return last;
}
#endif  // DO NOT CONTAIN THIS LINE IN THE MARKDOWN

void Test() {
#if 0   // DO NOT CONTAIN THIS LINE IN THE MARKDOWN
  // Same algorithm usable for multiple containers
  std::vector<int> vec = {1, 2, 3};
  std::list<int> lst = {1, 2, 3};

  auto it1 = std::find(vec.begin(), vec.end(), 2);  // O(n) scan
  auto it2 = std::find(lst.begin(), lst.end(), 2);  // O(n) scan
#endif  // DO NOT CONTAIN THIS LINE IN THE MARKDOWN
}
