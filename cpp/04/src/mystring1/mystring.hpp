#pragma once

class MyString {
  char* string_;
  int length_;
  int capacity_;

 public:
  // MyString(int): prevent implicit conversion like MyString str = 10;
  explicit MyString(int cap);
  // MyString(const char*): allow implicit conversion like MyString str = "Hi";
  MyString(const char* str);

  MyString(const MyString& str);
  ~MyString();

  MyString& Insert(int pos, const MyString& str);
  MyString& Insert(int pos, const char* str);
  MyString& Erase(int pos, int num);

  void Reserve(int size);
  void Println() const;

  int length() const;
  int capacity() const;
};
