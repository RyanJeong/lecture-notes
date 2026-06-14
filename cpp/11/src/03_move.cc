#include <iostream>
#include <string>
#include <utility>  // for std::move

int main() {
#if 1 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
  std::string s1 = "Hello, World!";
  std::move(s1);                 // Casts to rvalue reference; result ignored
  std::cout << s1 << std::endl;  // `s1` is unchanged (move didn't occur)

  std::string s2 = std::move(s1);          // Move ctor; `s1` is now unspecified
  std::cout << "s2: " << s2 << std::endl;  // Outputs: Hello, World!
  if (!s1.empty())                         // Safe: empty() has no preconditions
    std::cout << s1.back() << std::endl;   // Safe: Precondition (!empty) met
  s1.back();  // Undefined Behavior: Violates precondition if empty
#endif        /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
  return 0;
}