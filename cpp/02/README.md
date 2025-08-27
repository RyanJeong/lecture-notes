---
marp: true
theme: notes
style: |
    img[alt~="center"] {
      display: block;
      margin: 0 auto;
    }
math: mathjax
---

# 레퍼런스 (*Reference*)

## C 언어에서의 함수 호출 방식 (Function Call Mechanism)

```cpp
#include <iostream>

// Modifies a copy of the argument (call by value).
void ModifyByValue(int value) { value = 100; }

// Modifies the original argument (call by address).
// Note: In C, the pointer symbol (*) is usually placed next to the variable
// name (e.g., int *ptr). In C++, it is common practice to place the pointer
// symbol (*) next to the type (e.g., int* ptr).
void ModifyByAddress(int* ptr) { *ptr = 100; }

int main() {
  int a = 10;
  int b = 10;

  std::cout << "Before ModifyByValue: a = " << a << std::endl;
  ModifyByValue(a);
  std::cout << "After ModifyByValue: a = " << a << std::endl;

  std::cout << "Before ModifyByAddress: b = " << b << std::endl;
  ModifyByAddress(&b);
  std::cout << "After ModifyByAddress: b = " << b << std::endl;
  return 0;
}
```

---

## 레퍼런스 소개

* C++에서 변수의 별칭 (*alias*)을 만드는 방법
* 추가적인 연산자 없이 원본 객체에 접근 가능

```cpp
#include <iostream>

int main() {
  int a = 10;
  int& ref = a;  // 'ref' is a reference to 'a'.

  // Modifying 'ref' will also modify 'a'.
  ref += 5;
  std::cout << "a = " << a << std::endl;  // Output: a = 15
  return 0;
}
```

---

### 컴파일러가 레퍼런스를 처리하는 방법

```cpp
int x = 10;
int& ref = x;
ref += 20;
```

* 레퍼런스를 포인터로 변환

```cpp
// The compiler converts references and their associated expressions.
int x = 10;
int* const ref = &x;
*ref += 20;
```

* 레퍼런스 최적화

```cpp
// The compiler optimizes by removing unnecessary memory accesses.
int x = 10;
x += 20;
```

---

### 레퍼런스 특징

레퍼런스는 반드시 대상이 있어야 한다.

```cpp
#include <iostream>

int main() {
  int a = 10;

  // Reference MUST be initialized at declaration.
  int& ref = a;  // Valid: 'ref' is initialized to refer to 'a'.
  // int& ref2;  // !!! ERROR: References must be initialized.

  // Pointer can be declared without initialization.
  int* ptr;  // Valid: 'ptr' is declared but not initialized.
  ptr = &a;  // Now 'ptr' points to 'a'.

  // Pointer can be initialized to nullptr.
  int* null_ptr = nullptr;  // Valid: 'null_ptr' does not point to any object.
  return 0;
}
```

---

레퍼런스는 한 번 지정한 대상을 변경할 수 없다.

```cpp
#include <iostream>

int main() {
  int a = 10;
  int b = 20;

  // 'ref' is a reference to 'a'.
  int& ref = a;

  // Attempting to change the reference to another variable will modify the
  // original variable instead.
  ref = b;  // This does not change 'ref' to refer to 'b', it changes the value
            // of 'a' to 20.

  std::cout << "a = " << a << std::endl;  // Output: a = 20
  std::cout << "b = " << b << std::endl;  // Output: b = 20 (unchanged)
  return 0;
}
```

---

일반적으로 레퍼런스는 메모리 공간을 추가로 할당하지 않는다.

* 레퍼런스는 메모리에 실존하는 객체의 별명

* 컴파일러가 레퍼런스를 레퍼런스의 대상으로 치환하면 추가적인 메모리 불필요

```cpp
#include <iostream>

int main() {
  int a = 10;
  int& ref = a;  // 'ref' is a reference to 'a'.

  // The address of 'a' and 'ref' are the same, as 'ref' is just an alias for
  // 'a'.
  std::cout << "Address of a: " << &a << std::endl;
  std::cout << "Address of ref: " << &ref
            << std::endl;  // Outputs the same address as 'a'.

  // Example where the reference might not have a distinct address:
  int* ptr = &a;     // Pointer to 'a'.
  int& ref2 = *ptr;  // Reference to 'a' through pointer 'ptr'.

  std::cout << "Address of ptr: " << ptr << std::endl;
  std::cout << "Address of ref2: " << &ref2
            << std::endl;  // Same as 'a' and 'ptr'.
  return 0;
}
```

---

몇몇 경우에서는 레퍼런스가 메모리를 추가로 할당할 수 있다.

```cpp
#include <cstdint>  // Include for uintptr_t
#include <iostream>

struct Foo {
  char c;  // 1 byte for the char member
  // The following expression will be converted to 'int* const ref'.
  int& ref;  // It takes 4 bytes on a 32-bit OS and 8 bytes on a 64-bit OS.
};

int main() {
  int i = 100;
  Foo f = {'a', i};  // Partial initialization is not allowed.
                     // e.g., Foo f = {'a'};

  // Print the size of the Foo struct, which includes padding.
  std::cout << "Size of Foo: " << sizeof(f) << " bytes" << std::endl;

  // Print the address of 'i' and 'f.ref' to show they are the same.
  std::cout << "Address of i: " << &i << std::endl;
  std::cout << "Address of f.ref: " << &f.ref << std::endl;

  // uintptr_t is an unsigned integer type that is capable of holding a pointer.
  // It is used here to perform pointer arithmetic in a safe and portable
  // manner. The reinterpret_cast is used to convert the pointer to an integer
  // type.
  uintptr_t f_addr = reinterpret_cast<uintptr_t>(&f);
  std::cout << "Address of f: " << &f << std::endl;

  // Calculate the address of f + 8 (which should point to where ref is stored)
  // and then dereference it to get the value of the original int (i).
  int* ref_address = *reinterpret_cast<int**>(f_addr + 8);
  std::cout << "Address of f + 8: " << ref_address << std::endl;
  std::cout << "Dereferenced value at f + 8: " << *ref_address << std::endl;
  return 0;
}
```

---

## C++에서 추가된 함수 호출 방식 - 참조에 의한 호출 (Call by Reference)

```cpp
#include <iostream>

// Modifies the original argument (call by reference).
// References allow direct access to the original variable without needing
// additional operators like '*' (dereferencing).
void ModifyByReference(int& ref) { ref = 100; }

int main() {
  int i = 10;

  std::cout << "Before ModifyByReference: i = " << i << std::endl;
  ModifyByReference(i);
  std::cout << "After ModifyByReference: i = " << i << std::endl;
  return 0;
}
```

---

## 레퍼런스 예제

```cpp
#include <iostream>

int main() {
  int original = 42;
  int& ref = original;  // ref is a reference to original

  std::cout << "Original value: " << original << std::endl;  // Outputs 42
  std::cout << "Reference value: " << ref << std::endl;      // Outputs 42

  // Modifying the reference modifies the original
  ref += 8;
  std::cout << "After modifying reference:" << std::endl;
  std::cout << "Original value: " << original << std::endl;  // Outputs 50
  std::cout << "Reference value: " << ref << std::endl;      // Outputs 50

  // Showing the memory addresses
  std::cout << "Address of original: " << &original << std::endl;
  std::cout << "Address of reference: " << &ref << std::endl;

  // Creating a pointer to the reference (which is actually a pointer to the
  // original)
  int* ptr = &ref;
  std::cout << "Pointer value: " << *ptr << std::endl;  // Outputs 50
  std::cout << "Pointer address: " << ptr
            << std::endl;  // Same as address of original and ref
  return 0;
}
```

---

## 상수 레퍼런스

* `int& ref = 100;`

  ```shell
  error: cannot bind non-const lvalue reference of type ‘int&’ to an rvalue of
  type ‘int’
  ```

  * 일반 레퍼런스 (*non-const references*)는 *lvalue*만 바인딩 가능

* `const int& ref = 100;`
  * `100`은 컴파일 시간에 계산이 완료되어 메모리에 실체화되지 않는 정수 리터럴
  * 상수 레퍼런스 (`const` 키워드를 사용한 레퍼런스)는 리터럴를 바인딩할 수 있음
    * 바인딩된 리터럴은 상수 레퍼런스가 유효한 기간 동안 메모리 상에 **임시 객체**로 유지
    * 임시 객체는 상수 레퍼런스 소멸 시점에 같이 소멸됨

---

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

## 레퍼런스 배열, 배열 레퍼런스

* C++ Standard §8.3.2/4
  > There shall be no references to references, no arrays of references, and no pointers to references.

* **레퍼런스는 메모리에 존재하지 않을 수 있음**
  * 레퍼런스 배열의 이름을 활용한 주소 연산 (e.g., `(arr + 1)`)이 항상 보장되지 않음
* 따라서 다음 종류의 레퍼런스를 허용하지 않음:
  * 레퍼런스에 대한 레퍼런스 (references to references)
  * 레퍼런스 배열 (arrays of references)
  * 레퍼런스에 대한 포인터 (pointers to references)

```cpp
int main() {
  int x = 10;
  int y = 20;
  int& arr[2] = {x, y};
}
```

```shell
error: declaration of ‘arr’ as array of references
```

---

### 배열 레퍼런스 (References to Arrays)

* **이미 실체화된 배열**을 가리키는 레퍼런스 (배열 레퍼런스)는 사용 가능
* **배열 레퍼런스의 형과 크기는 가리키는 대상과 일치해야 함**
* 레퍼런스 선언자 (`&`, *reference declaration*)와 이름을 함께 괄호로 묶어야 함
  * 배열 크기 지시자 (`[]`, *array size specifier*)의 우선 순위가 더 높음
  * **괄호를 사용하지 않는다면 컴파일러는 선언식을 레퍼런스 배열로 처리**

```cpp
int arr[2][3] = {1, 2, 3, 4, 5, 6};
int (&ref)[2][3] = arr;
```

---

```cpp
#include <iostream>

int main() {
  int x = 1;
  int y = 2;
  int arr[2] = {x, y};

  // Declare a reference to an array of 2 integers. 'ref' is now an alias for
  // 'arr'. This means 'ref' and 'arr' refer to the exact same array in memory.
  int (&ref)[2] = arr;

  std::cout << arr[0] << arr[1]
            << std::endl;  // Outputs the original values: 12

  // Modify the array elements through the reference 'ref'.
  // Since 'ref' is an alias for 'arr', this directly changes the values in
  // 'arr'.
  ref[0] = 3;
  ref[1] = 4;

  std::cout << arr[0] << arr[1]
            << std::endl;  // Outputs the modified values: 34
  return 0;
}
```

---

## 레퍼런스 반환 함수

### Dangling Reference

* 레퍼런스가 유효하지 않은 메모리 주소를 대상으로 하는 경우
* 잘못된 레퍼런스 반환 함수는 dangling reference가 발생
  * e.g., 함수의 지역 객체를 레퍼런스로 반환

### Dangling Reference가 발생하는 경우

* 함수 지역 객체를 레퍼런스로 반환 - 이를 일반 객체로 받는 경우
  * `main` 함수 변수들은 이미 소멸된 객체 (`temp`)로부터 값 복사 시도
    * **Segmentation fault** (dangling reference)

```cpp
int& f() {
  int temp = 10;
  return temp;  // Return by reference, but temp is a local variable
}

int main() {
  int a = f();        // Segmentation fault
  const int b = f();  // Segmentation fault
  return 0;
}
```

---

* 함수 지역 객체를 레퍼런스로 반환 - 이를 레퍼런스로 받는 경우
  * `main` 함수 레퍼런스의 대상은 이미 소멸된 `temp`
    * **Undefined behavior** (dangling reference)
  * 소멸된 객체에 대한 레퍼런스를 사용하는 것은 **유효하지 않은 주소로의 접근**을 의미
    * 유효하지 않은 주소로의 접근 시 segmentation fault 오류 발생

```cpp
int& f() {
  int temp = 10;
  return temp;  // Return by reference, but temp is a local variable
}

int main() {
  int& a = f();
  const int& b = f();
  a = b;  // Segmentation fault
  return 0;
}
```

---

### Dangling Reference가 발생하지 않도록 사용하는 방법

* 레퍼런스 반환 함수가 종료되어도 소멸되지 않는 객체 (외부 객체)를 레퍼런스로 반환

```cpp
int& Max(int& a, int& b) { return (a > b) ? a : b; }
```

* 정적 객체 또는 전역 객체를 레퍼런스로 반환

```cpp
int& Counter() {
  static int counter = 0;  // Static object
  return counter;
}
```
