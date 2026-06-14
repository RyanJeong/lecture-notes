#include <iostream>
#include <string>

#include "queue.hpp"

int main() {
  try {
    Queue<std::string> queue;
    queue.Push("Henry");
    queue.Push("William");
    queue.Push("Tara");
    std::cout << "Element at the front: " << queue.Front() << std::endl;
    std::cout << "Element at the back: " << queue.Back() << std::endl;

    queue.Pop();
    queue.Pop();
    std::cout << "Element at the front: " << queue.Front() << std::endl;
    std::cout << "Element at the back: " << queue.Back() << std::endl;

    queue.Pop();
    queue.Pop();  // it will occur an exception
  } catch (const ListException& e) {
    std::cerr << "Error: " << e.what() << "(" << e.where() << ")" << std::endl;
  }
  return 0;
}
