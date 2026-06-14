#if 1 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
#include <iostream>
#include <string>
#include <utility>  // for std::move

class User {
  std::string name_;

 public:
  User() { std::cout << "User created." << std::endl; }

  // 1. Create a temporary object (std::string) from the argument.
  // 2. Move the temporary into the member variable (inefficient)
  void SetName1(std::string name) { name_ = std::move(name); }

  // 1. Create a temporary object (std::string) from the argument.
  // 2. Copy the temporary into the member variable (more inefficient)
  void SetName2(const std::string& name) { name_ = name; }
};
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */

int main() {
  User u, v;
  u.SetName1("Alice");
  v.SetName2("Bob");
  return 0;
}
