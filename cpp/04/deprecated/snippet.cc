#ifdef CPP_04_NOBUILD
class MyString {
  char* string_;
  int length_;
  int capacity_;

 public:
  // ... skipped ...
  MyString& Insert(int pos, const MyString& str);
  MyString& Insert(int pos, const char* str);
  // ... skipped ...
};

int main() {
  MyString str(10);
  str.Insert(0, "Hello, World!").Insert(0, "C++! ");
  return 0;
}
#endif  // CPP_04_NOBUILD

#ifdef CPP_04_NOBUILD
class MyString {
  char* string_;
  int length_;
  int capacity_;

 public:
  explicit MyString(int cap);
  // ... skipped ...
};

int main() {
  MyString str1(10);   // OK : explicit constructor call
  MyString str2 = 10;  // Error: cannot convert 'int' to 'MyString' implicitly
  return 0;
}
#endif  // CPP_04_NOBUILD