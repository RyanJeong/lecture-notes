#include <iostream>
#include <string>

#include "list.hpp"

int main() {
  try {
    List<std::string> list;
    list.Insert(0, "Michael");
    list.Insert(1, "Jane");
    list.Insert(2, "Sophie");
    list.Insert(3, "Thomas");

    std::cout << "Printing the list" << std::endl;
    list.Print();

    std::cout << "Getting data in some nodes" << std::endl;
    std::cout << list.GetNodeData(1) << std::endl;
    std::cout << list.GetNodeData(2) << std::endl;

    std::cout << "Erasing some nodes and printing after erasures" << std::endl;
    list.Erase(0);
    list.Erase(2);
    list.Print();

    std::cout << "Checking the list size" << std::endl;
    std::cout << "List size: " << list.count() << std::endl;
    list.Erase(0);
    list.Erase(0);
    list.Print();
  } catch (const ListException& e) {
    std::cerr << "Error: " << e.what() << "(" << e.where() << ")" << std::endl;
  }
  return 0;
}
