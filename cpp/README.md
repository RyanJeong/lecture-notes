# TODOs

### 리터럴 (*Literals*)

* 코드에서 직접 값 자체를 표현하는 고정된 값 (상수)
  * 정수 리터럴: `10`, `-5`, `0`
  * 부동 소수점 리터럴: `3.14`, `2.718`
  * 문자 리터럴: `'a'`, `'1'`
  * 문자열 리터럴: `"Hello, World!"`
  * 불리언 (`bool`, *boolean type*) 리터럴: `true`, `false`

#### 리터럴 종류에 따른 메모리 실체화 여부

* 컴파일 타임 상수로 처리되어 메모리를 사용하지 않는 경우

```cpp
int a = 53; // '53' is a compile-time constant literal and it does not occupy
            // memory
```

---

* 임시로 생성되었다가 소멸되는 경우

```cpp
#include <iostream>

// Function that takes a constant reference to an integer
void PrintValue(const int& t) {
  // Print the value passed to the function
  std::cout << "Value: " << t << std::endl;
}

int main() {
  // Passing an integer literal (42) to the function
  // This creates a temporary object to hold the value 42, since the function
  // expects a reference, and a reference cannot bind directly to a literal.
  // The temporary object exists for the duration of the function call.
  PrintValue(42);
  return 0;
}
```

* 메모리에 항상 실체화되어 프로그램 실행 중 유지되는 경우

```cpp
#include <iostream>

int main() {
  const char* str = "cpp";  // The string literal "cpp" is stored in the
                            // read-only data segment of the program's memory
  std::cout << str << std::endl;  // Outputs "cpp"
  return 0;
}
```

---

### 좌측값 (*Lvalue*)

* 메모리 주소를 가지는 식 (*expression*)
* 할당 연산자 (`=`, *assignment operator*)의 왼쪽에 올 수 있는 값
* `100`과 같은 리터럴은 좌측값으로 간주

```cpp
int x = 10;  // 'x' is an lvalue, 10 is an rvalue
x = 20;      // 'x' is still an lvalue
int* p = &x; // '&x' is an rvalue, p is an lvalue
*p = 30;     // '*p' is an lvalue (dereferencing p gives an lvalue)
```

### 우측값 (*Rvalue*)

* 메모리 주소를 가지지 않는 식
* 메모리에 실체화되지 않거나, 임시로 실체화되었다가 바로 제거되는 값
* 할당 연산자의 오른쪽에 올 수 있는 값

```cpp
int x = 10;   // '10' is an rvalue (an integer literal), 'x' is an lvalue
x = 20;       // '20' is an rvalue
int* p = &x;  // '&x' is an rvalue (evaluated to the address of 'x'), p is an
              // lvalue
```

---

## `auto`, Type, Lambda -> Recursion에 소개

---

## Rule of Three/Five

* **Rule of Three**: 클래스가 소멸자, 복사 생성자, 복사 할당 연산자 중 하나를 명시적으로 정의한다면, 나머지 두 개도 정의 필요
* **Rule of Five**: C++11 이후, 이동 생성자와 이동 할당 연산자가 추가되어 다섯 개 모두 고려 필요
* 리소스 관리의 일관성을 보장하기 위함

### RAII (Resource Acquisition Is Initialization)

* 리소스의 획득과 해제를 객체의 생명주기와 연결하는 C++의 핵심 원칙
* **리소스 획득**: 생성자에서 수행
* **리소스 해제**: 소멸자에서 수행
* 예외 안전성과 메모리 안전성을 보장

```cpp
class FileManager {
 private:
  std::FILE* file_;
  
 public:
  // Constructor: acquire resource
  FileManager(const char* filename) : file_(std::fopen(filename, "r")) {
    if (!file_) {
      throw std::runtime_error("Failed to open file");
    }
  }
  
  // Destructor: release resource
  ~FileManager() {
    if (file_) {
      std::fclose(file_);
    }
  }
  
  // Delete copy operations to simplify resource management
  FileManager(const FileManager&) = delete;
  FileManager& operator=(const FileManager&) = delete;
};

// Usage example
void process_file() {
  FileManager fm("data.txt");  // File opened automatically
  // File operations...
  // File closed automatically when function ends (even if exception occurs)
}
```

```cpp
auto str = "hello"s;
```

---

## 가상

### Appendix A. `vptr`의 유무에 따른 객체 크기 비교

```cpp
#include <iostream>

class NoVirtual {
 public:
  int a;
  double b;
};

class WithVirtual {
 public:
  int a;
  double b;
  virtual void func() {}  // declare a virtual function using a virtual keyword
};

int main() {
  NoVirtual no_virtual_obj;
  WithVirtual with_virtual_obj;

  std::cout << "Size of NoVirtual object: " << sizeof(no_virtual_obj)
            << " bytes" << std::endl;
  std::cout << "Size of WithVirtual object: " << sizeof(with_virtual_obj)
            << " bytes" << std::endl;

  return 0;
}
```

---

### Appendix B. 가상 테이블의 포인터와 실제 멤버 함수 포인터 간 비교

* test.hpp

```cpp
#pragma once

#include <iostream>

class Base {
 public:
  virtual void Show() { std::cout << "Base::Show called" << std::endl; }
  virtual void Display() { std::cout << "Base::Display called" << std::endl; }
};

class Derived : public Base {
 public:
  void Show() override { std::cout << "Derived::Show called" << std::endl; }
  virtual void Print() { std::cout << "Derived::Print called" << std::endl; }
};

// Helper function to get the virtual function pointer from vtable
typedef void (*FuncPtr)();  // Function pointer type definition

FuncPtr GetVirtualFunctionPointer(Base* obj, int index) {
  // Retrieves vptr from the object and returns the function pointer
  // from the vtable at the specified index
  return reinterpret_cast<FuncPtr*>(*reinterpret_cast<void**>(obj))[index];
}
```

* In this code, a `Base*` pointer **can only call `Show()` and `Display()`** because that's the only virtual method declared in `Base`.

---

* main.cc

```cpp
#include <iostream>

#include "test.hpp"

int main() {
  // Get the function pointers from the vtable for the Base class using index
  Base base_obj;
  FuncPtr base_vtable_show = GetVirtualFunctionPointer(&base_obj, 0);
  FuncPtr base_vtable_display = GetVirtualFunctionPointer(&base_obj, 1);

  // Get the function pointers from the vtable for the Derived class using index
  Derived derived_obj;
  FuncPtr derived_vtable_show = GetVirtualFunctionPointer(&derived_obj, 0);
  FuncPtr derived_vtable_display = GetVirtualFunctionPointer(&derived_obj, 1);
  FuncPtr derived_vtable_print = GetVirtualFunctionPointer(&derived_obj, 2);

  // Compare the pointers for the Base class
  std::cout << "Base class vtable function pointers:" << std::endl;
  std::cout << "Show function pointer from vtable(" << (void*) base_vtable_show
            << "):";
  base_vtable_show();
  std::cout << "Display function pointer from vtable("
            << (void*) base_vtable_display << "):";
  base_vtable_display();

  // Compare the pointers for the Derived class
  std::cout << "\nDerived class vtable function pointers:" << std::endl;
  std::cout << "Show function pointer from vtable("
            << (void*) derived_vtable_show << "):";
  derived_vtable_show();
  std::cout << "Display function pointer from vtable("
            << (void*) derived_vtable_display << "):";
  derived_vtable_display();
  std::cout << "Print function pointer from vtable("
            << (void*) derived_vtable_print << "):";
  derived_vtable_print();
  return 0;
}
```
