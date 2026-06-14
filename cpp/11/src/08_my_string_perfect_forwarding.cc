#include <iostream>
#include <string>
#include <utility>  // for std::forward

class User {
  std::string name_;

 public:
  User() { std::cout << "User created." << std::endl; }

  template <typename T>
  void SetName(T&& name) {
    // 1. T&&: Universal reference; accepts lvalues, rvalues, and const char*
    //         strings.
    // 2. std::forward: Forwards the argument exactly as received (preserving
    //                  value category) to the operator=(const char*).
    name_ = std::forward<T>(name);
  }
};

int main() {
  User u;
  u.SetName("Alice");  // "Alice" is a string literal (has a static memory
                       // address), passed as a reference (const char*&).
  return 0;
}
