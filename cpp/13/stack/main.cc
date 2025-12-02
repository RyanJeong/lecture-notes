#include <iostream>
#include <string>

#include "stack.hpp"

int main() {
  try {
    Stack<std::string> stack;
    stack.Push("Henry");
    stack.Push("William");
    std::cout << "Stack size: " << stack.Size() << std::endl;

    while (stack.Size() > 0) {
      std::cout << "Node value at the top: " << stack.Top() << std::endl;
      stack.Pop();
    }
    stack.Pop();  // it will occur an exception
  } catch (const ListException& e) {
    std::cerr << "Error: " << e.what() << " (" << e.where() << ")" << std::endl;
  }
  return 0;
}
