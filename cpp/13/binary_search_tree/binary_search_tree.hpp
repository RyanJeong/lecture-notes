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
  Node* Insert(const T& value, Node* ptr) {
    if (!ptr)  // Base case: create new node
      ptr = MakeNode(value);
    else if (value < ptr->data)  // Smaller: insert at the left subtree
      ptr->left = Insert(value, ptr->left);
    else  // Larger: insert at the right subtree
      ptr->right = Insert(value, ptr->right);
    return ptr;
  }

  void Destroy(Node* ptr) noexcept {
    if (!ptr) return;

    Destroy(ptr->left);   // Destroy the left subtree.
    Destroy(ptr->right);  // Destroy the right subtree.
    delete ptr;           // Delete a data item in the root.
  }

  bool Search(const T& value, Node* ptr) const noexcept {
    if (!ptr) return false;

    if (ptr->data == value)
      return true;
    else
      return Search(value, (value < ptr->data ? ptr->left : ptr->right));
  }

  void PreOrder(Node* ptr) const noexcept {
    if (!ptr) return;

    std::cout << ptr->data << std::endl;
    PreOrder(ptr->left);
    PreOrder(ptr->right);
  }

  void InOrder(Node* ptr) const noexcept {
    if (!ptr) return;

    InOrder(ptr->left);
    std::cout << ptr->data << std::endl;
    InOrder(ptr->right);
  }

  void PostOrder(Node* ptr) const noexcept {
    if (!ptr) return;

    PostOrder(ptr->left);
    PostOrder(ptr->right);
    std::cout << ptr->data << std::endl;
  }
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
