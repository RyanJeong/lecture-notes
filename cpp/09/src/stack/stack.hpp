#pragma once

#include <iostream>

#include "stack_exception.hpp"

template <typename T>
class Stack {
  T* ptr_;
  int capacity_;
  int size_;

 public:
  explicit Stack(int capacity);
  ~Stack();

  void Push(const T& elem); /* throw(StackException) */
  T Pop();                  /* throw(StackException) */
};

template <typename T>
Stack<T>::Stack(int capacity) : capacity_(capacity), size_(0) {
  ptr_ = new T[capacity_];
}

// It seems it doesn't use a generic type, but an out-of-class definition of a
// class template member must be preceded by `template <typename T>`.
template <typename T>
Stack<T>::~Stack() {
  delete[] ptr_;
}

template <typename T>
void Stack<T>::Push(const T& elem) {
  if (size_ >= capacity_) throw StackException("Stack is full", "Stack::Push");
  ptr_[size_++] = elem;
}

template <typename T>
T Stack<T>::Pop() {
  if (size_ <= 0) throw StackException("Stack is empty", "Stack::Pop");
  return ptr_[--size_];
}
