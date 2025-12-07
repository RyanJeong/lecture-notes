#include <iostream>
#include <vector>

void IterateByValue() {
  std::vector<int> vec = {1, 2, 3};

  for (int n : vec) std::cout << n << " ";  // 1 2 3

  // Equivalent code after compilation
  {
    auto begin = vec.begin();
    auto end = vec.end();
    for (; begin != end; ++begin) {
      int n = *begin;  // Copy occurs
      std::cout << n << " ";
    }
  }
}

void IterateByReference() {
  std::vector<int> vec = {1, 2, 3};

  for (int& n : vec) n *= 2;  // Modify original
  // vec: [2, 4, 6]

  // Equivalent code after compilation
  {
    auto begin = vec.begin();
    auto end = vec.end();
    for (; begin != end; ++begin) {
      int& n = *begin;  // Reference
      n *= 2;
    }
  }
}

void IterateByConstReference() {
  std::vector<int> vec = {1, 2, 3};

  // No copy, no modification
  for (const int& n : vec) std::cout << n << " ";  // 1 2 3

  // Equivalent code after compilation
  {
    auto begin = vec.begin();
    auto end = vec.end();
    for (; begin != end; ++begin) {
      const int& n = *begin;  // Const reference
      std::cout << n << " ";
    }
  }
}

#include <map>
#include <string>

void IterateWithTypeDeduction() {
  std::vector<int> vec = {1, 2, 3};

  for (auto n : vec)  // Deduced as int
    std::cout << n << " ";

  std::map<std::string, int> m = {{"a", 1}, {"b", 2}};

  for (auto p : m)  // Deduced as std::pair<const std::string, int>
    std::cout << p.first << ": " << p.second << "\n";
}

#include <list>
#include <queue>
#include <set>
#include <stack>

void UsagePatternsByContainer() {
  // Vector
  std::vector<int> v = {1, 2, 3};

  // Read-only: const auto&
  for (const auto& n : v) std::cout << n << " ";

  // Modify: auto&
  for (auto& n : v) n *= 2;

  // Copy (not recommended): auto
  for (auto n : v) std::cout << n << " ";  // Copy occurs each iteration

  // List
  std::list<int> lst = {1, 2, 3};

  // List uses same syntax as vector
  for (const auto& n : lst) std::cout << n << " ";

  // Map
  std::map<std::string, int> m = {{"a", 1}, {"b", 2}};

  // first: key (const), second: value (modifiable)
  for (const auto& p : m) std::cout << p.first << ": " << p.second << std::endl;

  // Set
  std::set<int> s = {1, 2, 3};

  for (const auto& n : s) std::cout << n << " ";
}

void PerformanceComparison() {
  std::vector<std::string> vec = {"a", "b", "c"};

  // Slow: Copy (each iteration copies)
  for (std::string s : vec) std::cout << s << " ";

  // Fast: Const reference (no copy)
  for (const auto& s : vec) std::cout << s << " ";

  // Fast: Reference when modification needed
  for (auto& s : vec) s = s + "_modified";
}