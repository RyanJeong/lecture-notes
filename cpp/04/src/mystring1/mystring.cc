#include "mystring.hpp"

#include <cstring>
#include <iostream>

MyString::MyString(int capacity)
    : string_(new char[capacity]), length_(0), capacity_(capacity) {}

MyString::MyString(const char* str)
    : string_(new char[std::strlen(str)]),
      length_(std::strlen(str)),
      capacity_(std::strlen(str)) {
  for (int i = 0; i != length_; ++i) string_[i] = str[i];
}

MyString::MyString(const MyString& str)
    : string_(new char[str.length_]),
      length_(str.length_),
      capacity_(str.length_) {
  for (int i = 0; i != length_; ++i) string_[i] = str.string_[i];
}

MyString::~MyString() { delete[] string_; }

MyString& MyString::Insert(int pos, const MyString& str) {
  if (pos < 0 || pos > length_) return *this;

  if (length_ + str.length_ > capacity_) {
    int new_capacity;
    if (capacity_ * 2 > length_ + str.length_)
      new_capacity = capacity_ * 2;
    else
      new_capacity = length_ + str.length_;

    char* prev_string = string_;
    string_ = new char[new_capacity];

    int idx = 0;
    while (idx < pos) {
      string_[idx] = prev_string[idx];
      ++idx;
    }
    for (int i = 0; i < str.length_; ++i) string_[idx + i] = str.string_[i];
    while (idx < length_) {
      string_[idx + str.length_] = prev_string[idx];
      ++idx;
    }

    delete[] prev_string;
    capacity_ = new_capacity;  // update capacity
  } else {
    for (int i = length_ - 1; i >= pos; --i)
      string_[i + str.length_] = string_[i];
    for (int i = 0; i < str.length_; ++i) string_[i + pos] = str.string_[i];
  }
  length_ += str.length_;

  return *this;
}

MyString& MyString::Insert(int pos, const char* str) {
  MyString temp(str);
  return Insert(pos, temp);
}

MyString& MyString::Erase(int pos, int num) {
  if (num < 0 || pos < 0 || pos >= length_) return *this;
  if (pos + num > length_) num = length_ - pos;
  for (int i = pos + num; i < length_; i++) string_[i - num] = string_[i];
  length_ -= num;
  return *this;
}

void MyString::Reserve(int size) {
  if (size <= capacity_) return;
  char* prev_string = string_;
  string_ = new char[size];
  capacity_ = size;
  for (int i = 0; i != length_; ++i) string_[i] = prev_string[i];
  delete[] prev_string;
}

void MyString::Println() const {
  for (int i = 0; i != length_; ++i) std::cout << string_[i];
  std::cout << std::endl;
}

int MyString::length() const { return length_; }

int MyString::capacity() const { return capacity_; }
