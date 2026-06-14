#include <iostream>
#include <string>

#include "binary_search_tree.hpp"

int main() {
  try {
    BinarySearchTree<std::string> bct;
    bct.Insert("Michael");
    bct.Insert("Jane");
    bct.Insert("Sophie");
    bct.Insert("Thomas");
    bct.Insert("Rose");
    bct.Insert("Richard");

    std::cout << "Using preorder traversal" << std::endl;
    bct.PreOrder();
    std::cout << std::endl;

    std::cout << "Using inorder traversal" << std::endl;
    bct.InOrder();
    std::cout << std::endl;

    std::cout << "Using postorder traversal" << std::endl;
    bct.PostOrder();
    std::cout << std::endl;

    std::cout << "Searching: " << std::boolalpha << std::endl;
    std::cout << "Is Sophie in the tree? ";
    std::cout << bct.Search("Sophie") << std::endl;
    std::cout << "Is Mary in the tree? ";
    std::cout << bct.Search("Mary") << std::endl;
  } catch (const BinarySearchTreeException& e) {
    std::cerr << "Error: " << e.what() << "(" << e.where() << ")" << std::endl;
  }
  return 0;
}
