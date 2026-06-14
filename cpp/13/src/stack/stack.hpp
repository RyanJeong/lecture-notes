#pragma once

#include "list.hpp"  // Depends on the singly linked list implementation

template <typename T>
class Stack {
  List<T> list_;  // Composition: Stack uses List internally

 public:
  void Push(const T& data) { list_.Insert(0, data); }
  void Pop() { list_.Erase(0); }
  T Top() const { return list_.GetNodeData(0); }
  int size() const noexcept { return list_.count(); }
};
