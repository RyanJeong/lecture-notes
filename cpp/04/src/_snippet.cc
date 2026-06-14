void Snippet1() {
#if 1                   /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
  char str[] = "ABCD";  // 'A', 'B', 'C', 'D', '\0'
#endif                  /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */

  (void) str;  // Avoid unused variable warning.
}

void Snippet2() {
#if 0  /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
  char* str = "Hello";  // C++ does not allow conversion from string literal to
                        // 'char *', though C allows it.
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
}

void Snippet3() {
#if 0  /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
  // Memory Management:
  // C-strings require manual memory management, which can lead to issues like
  // memory leaks or buffer overflows.
  char* str = (char*) malloc(8);
  strcpy(str, "Hello, World!");  // Buffer overflow! The string's length is 13.
  free(str);
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
}

#if 0  /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
// String Length and Size:
// You need to traverse the entire string to compute its length, which can be
// inefficient for large strings since C-strings don't track their own size.

// strlen: return length of string `s`
int strlen(char* s) {
  char* p = s;

  while (*p) p++;

  return p - s;
}
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */

#include <string.h>

void Snippet4() {
#if 1 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
  char str[] = "Hello";
  int len = strlen(str);  // Traverse the entire string
#endif                    /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */

  (void) len;  // Avoid unused variable warning.
  (void) str;  // Avoid unused variable warning.
}

void Snippet5() {
#if 1 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
  // String Concatenation:
  // In C-strings, to concatenate, you need to ensure there's enough space and
  // use the strcat function.
  char buffer[20] = "Hello";
  strcat(buffer, ", World!");  // Always ensure buffer has enough space
#endif                         /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */

  (void) buffer;  // Avoid unused variable warning.
}

void Snippet6() {
#if 1 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
  // Substring Extraction and Replacement:
  // You need to ensure there's enough space and use the strncpy function.
  char str[] = "Hello, World!";
  char substring[6];
  strncpy(substring, str + 7, 5);  // Extract "World"
  substring[5] = '\0';             // Add null terminator

  char* pos = strstr(str, "World");  // Find the position of "World"
  if (pos) strncpy(pos, "C++", 3);   // Replace with "C++"
  // Note: If your replacement string is longer, ensure there's enough space
  // If your replacement string is shorter, manually do something to remove
  // leftover characters
  *(pos + 3) = '\0';  // "Hello, C++ld!" -> "Hello, C++"
#endif                /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */

  (void) str;        // Avoid unused variable warning.
  (void) substring;  // Avoid unused variable warning.
  (void) pos;        // Avoid unused variable warning.
}

#include <string>

void Snippet7() {
#if 1 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
  std::string str = "abc";
  // memory: ['a']['b']['c']['?']['?']['?']
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */

#if 1 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
  str += "de";
  // memory: ['a']['b']['c']['d']['e']['?']
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */

#if 1 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
  str += "fg";
  // memory: ['a']['b']['c']['d']['e']['f']['g']['?']['?']['?']['?']['?']
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
}

#include <cstring>
#include <iostream>

#if 1 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
class ShallowCopy {
  char* data_;

 public:
  explicit ShallowCopy(const char* s) : data_(new char[std::strlen(s) + 1]) {
    std::strcpy(data_, s);  // Copy string data
    std::cout << "Constructor called for: " << data_ << std::endl;
  }
  // Note: Copy constructor is missing, so the compiler creates a default one
  // that performs shallow copy (just copies the pointer, not what it points to)
  ~ShallowCopy() {
    std::cout << "Destructor called for: " << data_ << std::endl;
    delete[] data_;  // Will cause double-free error
  }
};
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */

void Snippet8() {
#if 1 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
  ShallowCopy obj1("Hello");

  // shallow copy occurs here - both objects now share same memory
  ShallowCopy obj2(obj1);  // it converts to ShallowCopy obj2 = obj1; (implicit)
  // `obj2` shares the same memory with `obj1`, so delete[] gets called
  // multiple times (it leads to memory issues)
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */

  (void) obj1;  // Avoid unused variable warning.
  (void) obj2;  // Avoid unused variable warning.
}

#if 1 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
class DeepCopy {
  char* data_;

 public:
  explicit DeepCopy(const char* s) : data_(new char[std::strlen(s) + 1]) {
    std::strcpy(data_, s);  // Copy string data
  }
  // Copy constructor (deep copy): It copies the actual string data, not just
  // the pointer so that each object has its own copy of the data.
  DeepCopy(const DeepCopy& str) {
    data_ = new char[std::strlen(str.data_) + 1];  // Allocate new memory
    // Copy the actual string data, not just the pointer
    std::strcpy(data_, str.data_);
  }
  ~DeepCopy() {
    delete[] data_;  // Safe because each object has its own memory
  }
};
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */

void Snippet9() {
#if 1 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
  DeepCopy obj1("Hello");
  // deep copy occurs here - each object has its own memory
  DeepCopy obj2(obj1);  // it converts to DeepCopy obj2 = obj1; (implicit)
  // another deep copy
  DeepCopy obj3(obj1);  // it converts to DeepCopy obj3 = obj1; (implicit)
  // Each object has its own memory, so delete[] is called safely for each
  // without causing double-free errors
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */

  (void) obj1;  // Avoid unused variable warning.
  (void) obj2;  // Avoid unused variable warning.
  (void) obj3;  // Avoid unused variable warning.
}

#if 0  /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
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
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */

#if 0  /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
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
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */

void Snippet10() {
#if 1 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
  std::string str("C++ string");
  std::size_t pos = str.find("C++");
  if (pos != std::string::npos)
    std::cout << "'C++' found at position: " << pos << std::endl;
  else
    std::cout << "'C++' not found" << std::endl;
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
}
