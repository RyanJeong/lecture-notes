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

# C++ 기초

## Hello, World

```cpp
#include <iostream>

int main() {
  std::cout << "Hello, World" << std::endl;
  return 0;
}
```

### `#include <iostream>`

* C++ 표준 입출력 관련 내용들을 포함하는 헤더파일
* 확장자를 붙이지 않음

### `int main()`

* 프로그램 시작점

---

### `std::cout`

* 표준 출력 객체 (*object*)

### `std::endl`

* 개행 함수 (*function*)
* 출력 버퍼에 담긴 데이터를 즉시 내보냄
  * 개행 문자를 출력 버퍼로 내보낸 뒤 출력 버퍼에 그동안 축적한 데이터를 표준 출력으로 내보냄

---

## 이름 공간 (*Namespace*)

* 사용하고자 하는 이름 (*name*)의 **소속**을 구분하기 위함
* 프로그램 규모가 커짐에 따라 식별자 (*identifier*) 중복으로 인한 컴파일 오류 급증
* 효율적으로 이름을 구분하여 사용하기 위해 이름 공간 개념 도입
  * `std::cout`: `std`라는 이름 공간에 속해 있는 `cout` 객체 사용

* 함수 `foo, bar`는 서로 이름이 같지만 이름 공간에 의해 서로 구분됨:

```cpp
// header1.hpp
#pragma once

namespace header1 {
int foo();
void bar();
}  // header1
```

```cpp
// header2.hpp
#pragma once

namespace header2 {
double foo();
int bar();
}  // header2
```

---

* 같은 이름 공간 내에서 범위지정연산자 (`::`, *scope-resolution operator*) 생략 가능

```cpp
#include "header1.hpp"

namespace header1 {
int func() { 
  return foo();  // header1::foo()
}
}  // header1
```

* 범위지정연산자를 사용해 다른 이름 공간에 속한 이름 사용 가능
  * e.g., 변수 사용, 함수 호출, etc.

```cpp
#include "header1.hpp"
#include "header2.hpp"

namespace header1 {
int func() {
  header2::bar();
  return foo();  // header1::foo()
}
}  // header1
```

---

* 범위지정연산자를 사용하면 이름 공간에 속한 이름 직접 지정 가능

```cpp
#include "header1.hpp"
#include "header2.hpp"

int func() {
  int res = header1::foo();
  return 0;
}
```

* `using` 키워드를 사용해 범위지정연산자 생략 가능

```cpp
#include "header1.hpp"

using header1::foo;  // Brings header1::foo into the current scope as foo

int func() {
  return foo();  // header1::foo()
}
```

```cpp
#include "header1.hpp"

// Brings all names from header1 namespace into the current scope
using namespace header1;

int func() {
  bar();  // header1::bar()
  return foo();  // header1::foo()
}
```

---

### `using namespace std;`

> Do not use namespace using-directives. Use using-declarations instead.

* 표준 이름 공간 (`std`)은 명시적으로 사용 권장
  * 표준 라이브러리 내 무수히 많은 이름이 정의되어 있음
  * `using namespace std` 선언 시 이름 충돌 위험

### 이름 없는 이름 공간 (Anonymous Namespaces)

* 정적 함수 혹은 정적 변수 생성 시 사용
  * C 언어에서의 `static` 키워드 역할

```cpp
namespace {
int foo_func() { return 3; }
int foo_var = 1;
}  // namespace

int main() {
  foo_var = foo_func();
  return 0;
}
```

---

* **이름 없는 이름 공간을 사용하는 헤더 파일은 두 개 이상의 소스코드 파일에 포함될 수 없음**

```cpp
// foo.hpp
#pragma once

namespace {
int foo_func() { return 3; }
int foo_var = 1;
}  // namespace
```

```cpp
// main.cc
#include <iostream>

#include "foo.hpp"

int main() {
  foo_var = foo_func();
  return 0;
}
```

---

* 아래의 경우는 오류 발생

```cpp
// foo.hpp
#pragma once

namespace {
int foo_func();
int foo_var;
}  // namespace
```

```cpp
// foo.cc
#include "foo.hpp"

namespace {
int foo_func() { return 3; }
}  // namespace
```

```cpp
// main.cc
#include <iostream>

#include "foo.hpp"

int main() {
  foo_var = foo_func();
  return 0;
}
```

---

```shell
% g++ main.cc foo.cc 
In file included from main.cc:3:
./foo.hpp:4:7: warning: function '(anonymous namespace)::foo_func' has internal 
linkage but is not defined [-Wundefined-internal]
  int foo_func();
      ^
main.cc:6:13: note: used here
  foo_var = foo_func();
            ^
1 warning generated.
Undefined symbols for architecture x86_64:
  "(anonymous namespace)::foo_func()", referenced from:
      _main in main-f07283.o
ld: symbol(s) not found for architecture x86_64
clang: error: linker command failed with exit code 1 (use -v to see invocation)
```

---

## C++와 C언어의 공통 문법 구조

### 변수 선언

```cpp
int main() {
  char c;
  int i;
  float f;
  double d;
  return 0;
}
```

### [이름 규칙](https://google.github.io/styleguide/cppguide.html#Naming)

```cpp
// variable names: snake case
int num_entries;

// constant names: named with a leading "k" followed by camel case
const int kDaysInAWeek = 7;

// function names: pascal case
int OpenFileOrDie();
int StartRpc();  // When using abbreviations in function names, treat the
                 // abbreviation as a single word and capitalize only the first
                 // letter of the abbreviation
```

---

### 포인터와 배열

```cpp
int arr[5] = {1, 2, 3, 4, 5};
int* parr = arr;

int i = 10;
int* pi = &i;
```

### 반복문

* **C 언어 변수는 블록의 상단에서만 선언 가능하나, C++ 변수는 아무 위치에서나 선언 가능**

```cpp
#include <iomanip>
#include <iostream>

int main() {
  for (int i = 2; i <= 9; ++i) {
    for (int j = 1; j <= 9; ++j) {
      std::cout << i << " x " << j << ": " << std::setw(2) << i * j
                << std::endl;
    }
    std::cout << std::endl;
  }
  return 0;
}
```

---

```cpp
#include <iostream>

int main() {
  std::cout << "Enter numbers to add to sum (enter 0 to stop): " << std::endl;

  int number;
  std::cin >> number;

  int sum = 0;
  while (number) {
    sum += number;
    std::cin >> number;
  }
  std::cout << "Total sum: " << sum << std::endl;

  return 0;
}
```

```cpp
#include <cstring>
#include <iostream>

int main() {
  const char kPassword[] = "cpp";

  char password[128];
  do {
    std::cout << "Enter your password: ";
    std::cin >> password;
  } while (std::strcmp(password, kPassword));
  std::cout << "Access granted." << std::endl;

  return 0;
}
```

---

#### Including Standard C Library Headers in C++

In C++, standard C library headers are prefixed with 'c' and omit the '.h' extension.

```cpp
// <string.h>
#include <cstring>

// <math.h>
#include <cmath>

// <stdio.h>
#include <cstdio>
```

* Key Differences:
  * C Header:
    * This brings in the C-style standard library.
    * While it can be used in C++, it does not place functions in the `std` namespace.
  * C++ Header:
    * This provides the same functionality as the C header but places the functions in the `std` namespace (for example, the `strcmp` function is called as `std::strcmp`).

**By using C++ style headers (e.g., `<cstring>`, `<cmath>`), C++ code benefits from better integration with the C++ standard library while maintaining compatibility with C functions.**

---

### 조건문

```cpp
#include <iostream>

int main() {
  std::cout << "Enter your score (0-100): ";

  int score;
  std::cin >> score;

  if (score >= 90)
    std::cout << "Grade: A" << std::endl;
  else if (score >= 80)
    std::cout << "Grade: B" << std::endl;
  else if (score >= 70)
    std::cout << "Grade: C" << std::endl;
  else if (score >= 60)
    std::cout << "Grade: D" << std::endl;
  else
    std::cout << "Grade: F" << std::endl;

  return 0;
}
```

---

```cpp
#include <iostream>

int main() {
  std::cout << "Enter first number: ";
  double num1;
  std::cin >> num1;

  std::cout << "Enter an operator (+, -, *, /): ";
  char operation;
  std::cin >> operation;

  std::cout << "Enter second number: ";
  double num2;
  std::cin >> num2;

  if (operation == '+') {
    std::cout << "Result: " << num1 + num2 << std::endl;
  } else if (operation == '-') {
    std::cout << "Result: " << num1 - num2 << std::endl;
  } else if (operation == '*') {
    std::cout << "Result: " << num1 * num2 << std::endl;
  } else if (operation == '/') {
    if (num2 != 0)
      std::cout << "Result: " << num1 / num2 << std::endl;
    else
      std::cout << "Error: Division by zero!" << std::endl;
  } else {
    std::cout << "Error: Invalid operator!" << std::endl;
  }
  return 0;
}
```

---

## 동적 할당 (`new`, `delete`)

* C++에 추가된 기본 연산자

### 스칼라 객체

```cpp
#include <iostream>

int main() {
  int* p_i = new int;

  *p_i = 42;
  std::cout << "Value of p_i: " << *p_i << std::endl;

  delete p_i;
  return 0;
}
```

---

### 배열 객체

```cpp
#include <iostream>

int main() {
  int* p_arr = new int[5];

  for (int i = 0; i < 5; ++i) p_arr[i] = i * 10;
  for (int i = 0; i < 5; ++i)
    std::cout << "p_arr[" << i << "]: " << p_arr[i] << std::endl;

  delete[] p_arr;
  return 0;
}
```

---

### 2차원 배열 객체 - 각 행의 길이가 같은 경우

```cpp
#include <iostream>

int main() {
  int rows = 3;
  int cols = 4;
  int* array = new int[rows * cols];

  array[0 * cols + 0] = 1;   // First element
  array[2 * cols + 3] = 10;  // Last element in a 3x4 array
  std::cout << "array[0][0] = " << array[0 * cols + 0] << std::endl;
  std::cout << "array[2][3] = " << array[2 * cols + 3] << std::endl;
  delete[] array;

  return 0;
}
```

---

### 2차원 배열 객체 - 각 행의 길이가 다른 경우

```cpp
#include <iostream>

int main() {
  int rows = 3;
  int cols = 4;
  int** array = new int*[rows];
  for (int i = 0; i < rows; ++i) array[i] = new int[cols];

  array[0][0] = 1;   // First element
  array[2][3] = 10;  // Last element in a 3x4 array
  std::cout << "array[0][0] = " << array[0][0] << std::endl;
  std::cout << "array[2][3] = " << array[2][3] << std::endl;
  for (int i = 0; i < rows; ++i) delete[] array[i];  // Delete each row
  delete[] array;  // Delete the array of pointers

  return 0;
}
```
