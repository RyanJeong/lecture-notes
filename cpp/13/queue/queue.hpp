#pragma once

#include "list.hpp"  // Depends on the singly linked list implementation

template <typename T>
class Queue {
  List<T> list_;  // Composition: Stack uses List internally

 public:
  void Push(const T& data) { list_.Insert(Size(), data); }
  void Pop() { list_.Erase(0); }

  T Front() const { return list_.GetNodeData(0); }
  T Back() const { return list_.GetNodeData(Size() - 1); }
  int Size() const noexcept { return list_.count(); }
};
