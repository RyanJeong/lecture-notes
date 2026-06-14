#include <iostream>

#include "stack.hpp"

int main() {
  try {
    Stack<int> stack(3);
    stack.Push(10);
    stack.Push(20);
    stack.Push(30);
    // stack.Push(40);  // Exception occurred: Stack is full (Stack::Push)

    std::cout << "Popped: " << stack.Pop() << std::endl
              << "Popped: " << stack.Pop() << std::endl
              << "Popped: " << stack.Pop() << std::endl;
    stack.Pop();  // Exception occurred: Stack is empty (Stack::Pop)
  } catch (const StackException& e) {
    std::cerr << "Exception occurred: " << e.what() << " (" << e.where() << ")"
              << std::endl;
  }
  return 0;
}
