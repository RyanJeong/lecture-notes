#pragma once

#include <iostream>

#include "binary_search_tree_exception.hpp"

template <typename T>
class BinarySearchTree {
  struct Node {
    T data;
    Node* left;
    Node* right;
  };

  Node* MakeNode(const T& value) {
    Node* node = new Node;
    if (!node) {
      throw BinarySearchTreeException("Can't make a node.",
                                      "BinarySearchTree::MakeNode");
    }
    node->data = value;
    node->left = node->right = nullptr;
    return node;
  }

  // --- Internal recursive helpers
#if 1 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
  Node* Insert(const T& value, Node* ptr) {
    if (!ptr)  // Base case: create new node
      ptr = MakeNode(value);
    else if (value < ptr->data)  // Smaller: insert at the left subtree
      ptr->left = Insert(value, ptr->left);
    else  // Larger: insert at the right subtree
      ptr->right = Insert(value, ptr->right);
    return ptr;
  }
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */

#if 1 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
  void Destroy(Node* ptr) noexcept {
    if (!ptr) return;

    Destroy(ptr->left);   // Destroy the left subtree.
    Destroy(ptr->right);  // Destroy the right subtree.
    delete ptr;           // Delete a data item in the root.
  }
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */

  bool Search(const T& value, Node* ptr) const noexcept {
    if (!ptr) return false;

    if (ptr->data == value)
      return true;
    else
      return Search(value, (value < ptr->data ? ptr->left : ptr->right));
  }

#if 1 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
  void PreOrder(Node* ptr) const noexcept {
    if (!ptr) return;

    std::cout << ptr->data << std::endl;
    PreOrder(ptr->left);
    PreOrder(ptr->right);
  }
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */

#if 1 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
  void InOrder(Node* ptr) const noexcept {
    if (!ptr) return;

    InOrder(ptr->left);
    std::cout << ptr->data << std::endl;
    InOrder(ptr->right);
  }
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */

#if 1 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
  void PostOrder(Node* ptr) const noexcept {
    if (!ptr) return;

    PostOrder(ptr->left);
    PostOrder(ptr->right);
    std::cout << ptr->data << std::endl;
  }
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
  // --- End of internal recursive helpers

  Node* root_;
  int count_;

 public:
  BinarySearchTree() : root_(nullptr), count_(0) {}
  ~BinarySearchTree() { Destroy(root_); }

  void Insert(const T& value) {
    root_ = Insert(value, root_);
    ++count_;
  }

  bool Search(const T& value) const noexcept { return Search(value, root_); }
  void PreOrder() const noexcept { PreOrder(root_); }
  void InOrder() const noexcept { InOrder(root_); }
  void PostOrder() const noexcept { PostOrder(root_); }
  int size() const noexcept { return count_; }
  bool empty() const noexcept { return !count_; }
};
