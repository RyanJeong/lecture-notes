#include <iostream>
#include <stack>  // for std::stack
#include <string>

int main() {
  std::string expr = "((1+2)*3)";
  std::stack<char> s;

  // Check for balanced parentheses
  for (char c : expr) {
    if (c == '(') {
      s.push(c);  // Push opening bracket
    } else if (c == ')') {
      if (s.empty())  // No matching opening bracket
        break;
      s.pop();  // Pop matching opening bracket
    }
  }
  std::cout << (s.empty() ? "Valid" : "Invalid") << std::endl;
  return 0;
}
