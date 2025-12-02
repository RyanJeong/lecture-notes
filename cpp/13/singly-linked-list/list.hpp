#pragma once

#include <iostream>

#include "list_exception.hpp"

template <typename T>
class List {
  struct Node {
    T data;      // store a value
    Node* next;  // pointer to the next node
  };

  Node* MakeNode(const T& value) {
    Node* node = new Node;
    if (!node) throw ListException("Can't make a node.", "List::MakeNode");

    node->data = value;
    node->next = nullptr;
    return node;
  }

  Node* begin_;
  int count_;

 public:
  List() : begin_(nullptr), count_(0) {}
  ~List() {
    while (begin_) {
      Node* del = begin_;
      begin_ = del->next;
      delete del;
    }
  }

  void Insert(int pos, const T& value) {
    if (pos < 0 || pos > count_)
      throw ListException("The pos is out of range.", "List::Insert");

    Node* add = MakeNode(value);
    ++count_;
    if (!pos) {
      add->next = begin_;
      begin_ = add;
      return;
    }

    Node* cur = begin_;
    for (int i = 1; i < pos; ++i) cur = cur->next;
    add->next = cur->next;
    cur->next = add;
  }

  void Erase(int pos) {
    if (pos < 0 || pos > count_ - 1)
      throw ListException("The pos is out of range.", "List::Erase");

    --count_;
    if (!pos) {
      Node* del = begin_;
      begin_ = del->next;
      delete del;
      return;
    }

    Node* cur = begin_;
    for (int i = 0; i < pos - 1; ++i) cur = cur->next;
    Node* del = cur->next;
    cur->next = del->next;
    delete del;
  }

  T& GetNodeData(int pos) const {
    if (pos < 0 || pos > count_ - 1)
      throw ListException("The pos is out of range.", "List::GetNodeData");

    Node* cur = begin_;
    for (int i = 0; i < pos; ++i) cur = cur->next;
    return cur->data;
  }

  void Print() const noexcept {
    if (!count_) {
      std::cout << "\t"
                << "The list is empty." << std::endl;
      return;
    }

    for (Node* cur = begin_; cur; cur = cur->next)
      std::cout << "\t" << cur->data << std::endl;
  }

  int count() const noexcept { return count_; }
};
