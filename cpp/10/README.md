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

# 제네릭 프로그래밍 (Generic Programming: Templates)

## 함수 템플릿 (Function Template)

* 함수 내 일부 형을 컴파일 시점에 확정하는 기법

```cpp
template <typename T, typename U, ..., typename Z>
T function_template_syntax(U first, ... Z last) {
  // do something ...
}
```

* 함수 템플릿을 위한 템플릿 헤더 (template header)는 `template` 키워드를 사용
* 템플릿 헤더의 내용은 `<>` 괄호를 사용하며, **제네릭 형 (generic type)** 표현에 사용됨
* `T`, `U`, `Z`는 컴파일 시점에 확정되는 형의 자리 표시자 (placeholder)
* 하나의 함수 템플릿은 여러 번 호출되어 여러 개의 함수 정의가 생성될 수 있음
  * 함수 템플릿은 호출 시점의 전달 인자와 반환 형을 바탕으로 적합한 형이 컴파일 시점에 결정됨
* 함수 템플릿을 사용한 프로그래밍을 다음과 같이 표현함
  * 제네릭 프로그래밍 (generic programming)
  * 템플릿 프로그래밍 (template programming)

---

### Using One Function Template

```cpp
#include <iostream>

// Definition of a template function
template <typename T>
T Smaller(const T& op1, const T& op2) { return op1 < op2 ? op1 : op2; }

int main() {
  std::cout << "Smaller of 'a' and 'b': " << Smaller('a', 'b') << std::endl;
  std::cout << "Smaller of 12 and 15: " << Smaller(12, 15) << std::endl;
  std::cout << "Smaller of 44.2 and 33.1: " << Smaller(44.2, 33.1) << std::endl;
  return 0;
}
```

---

### 함수 템플릿과 함수 오버로딩 간 비교

```cpp
// Function to find the smaller between two characters
char Smaller(char op1, char op2)  { return op1 < op2 ? op1 : op2; }

// Function to find the smaller between two integers
int Smaller(int op1, int op2)  { return op1 < op2 ? op1 : op2; }

// Function to find the smaller between two doubles
double Smaller(double op1, double op2)  { return op1 < op2 ? op1 : op2; }
```

* 함수 템플릿 `Smaller`는 간단한 형태이므로 함수 오버로딩을 통해 동일한 동작 수행 가능
* 함수 템플릿은 호출 형태에 따라 컴파일 시점에 제네릭 형을 확정한 함수 코드가 생성됨
* 함수 오버로딩은 컴파일 전에 호출될 형태를 파악하여 필요한 만큼 코드로 직접 구현해야 함

---

### Swapping Two Values

```cpp
#include <iostream>

// Definition of template function
template <typename T>
void Exchange(T* op1, T* op2) {
  T temp = *op1;
  *op1 = *op2;
  *op2 = temp;
}

int main() {
  int i1 = 5;
  int i2 = 70;
  Exchange(&i1, &i2);  // Swapping two int types
  std::cout << "After swapping 5 and 70: " << i1 << " " << i2 << std::endl;
  double d1 = 1.2;
  double d2 = 3.4;
  Exchange(&d1, &d2);  // Swapping two double types
  std::cout << "After swapping 1.2 and 3.4: " << d1 << " " << d2 << std::endl;
  return 0;
}
```

---

## 템플릿 인스턴스화 (Template Instantiation)

![center](Figure_15_1.png)

* 함수 템플릿으로부터 컴파일 시점에 형이 확정되어 실제로 실행 가능한 함수가 생성되는 것
* 함수 템플릿은 **실제로 사용할 수 없는 코드**
  * 컴파일 시점에 필요한 형태의 함수를 만들기 위해 존재하는 일종의 틀
* 컴파일 시점에 함수 템플릿을 사용하는 형태에 맞게 동작할 수 있는 함수를 생성
* 함수 템플릿으로부터 함수 코드를 생성하는 행위를 **인스턴스화**라고 함
  * 클래스로부터 객체를 생성하는 인스턴스화와 용어는 같지만 다른 의미임에 유의

---

## 함수 템플릿의 변형 (Variations)

* 기본 함수 템플릿 문법으로부터 변형된 몇 가지 형태들

### 자료형이 아닌 템플릿 매개변수 (Non-type Template Parameter)

* 함수 템플릿에 제네릭 형 뿐만 아니라 값을 정의할 수도 있음
* 값을 정의하고자 할 경우 해당 값의 형을 **명시적으로 표현해야 함**
* 값으로 사용 가능한 형 ([Template parameters and template arguments](https://en.cppreference.com/w/cpp/language/template_parameters)):
  * 정수 형 (`int`, `long`, `size_t`, etc.)
  * 포인터 또는 참조
  * 열거형
  * `nullptr`
* 값으로 사용 가능한 형이 제한적인 이유는 컴파일 시점에 값이 확정되는 형태만을 사용할 수 있음
* **부동소수점 자료형이 허용되지 않음에 유의**
  * 부동소수점 표현은 컴파일러에 따라 값이 다르게 표현될 수 있음
  * 부동소수점 표현은 정밀도 제약이 존재해 값이 매번 다르게 표현될 수 있음
    * `0.1f == 0.1f` 표현은 항상 같다고 평가되지 않음
  * 함수 템플릿에 사용되는 값은 어떠한 상황에서도 항상 같은 값을 표현해야 함

---

#### Printing an Array - 1st Version

```cpp
#include <iostream>

// Definition of the print template function
template <typename T, int n>
void print(T (&array)[n]) {
  for (int i = 0; i < n; ++i) std::cout << array[i] << " ";
  std::cout << std::endl;
}

int main() {
  // Creation of two arrays
  int arr1[4] = {7, 3, 5, 1};
  double arr2[3] = {7.5, 6.1, 4.6};
  // Calling template function
  print(arr1);
  print(arr2);
  return 0;
}
```

---

### 템플릿에서의 기본 매개변수 (Default Arguments for Template Parameters)

* 함수의 매개변수에 기본 값을 설정하듯 템플릿에도 사용 가능
  * 형 또는 형이 아닌 값을 설정할 수 있음

```cpp
// Default argument for type template parameters
template <typename T1, typename T2 = int>

// Default argument for non-type template parameters
template <typename T, int n, int step = 1>
```

* 기본 매개변수 자리에 명시적으로 값을 전달해 기본 매개변수 대신 명시적인 값을 사용할 수 있음
* 기본 매개변수는 오른쪽부터 채워져야 함
* 기본 매개변수를 형이 아닌 값으로 사용할 경우 아래와 같은 형이여야 함:
  * 정수 형 (`int`, `long`, `size_t`, etc.)
  * 포인터 또는 참조
  * 열거형
  * `nullptr`

---

#### Printing an Array - 2nd Version

```cpp
#include <iostream>

// Definition of the print template function with a default parameter
template <typename T, int n, int step = 1>
void print(T (&array)[n]) {  // int (&array)[3] = arr, T is int, n is 3
  for (int i = 0; i < n; i += step) std::cout << array[i] << " ";
  std::cout << std::endl;
}

int main() {
  // Creation of two arrays
  int arr1[4] = {7, 3, 5, 1};
  double arr2[3] = {7.5, 6.1, 4.6};

  // Calling the template function with and without the default parameter
  print(arr1);                 // Uses the default step = 1
  print<arr2[0], 3, 2>(arr2);  // Specifies step = 2 explicitly

  return 0;
}
```

---

### 명시적 자료형 결정 (Explicit Type Determination)

```cpp
// Definition of a template function
template <typename T>
T Smaller(const T& op1, const T& op2) { return op1 < op2 ? op1 : op2; }
```

```cpp
Smaller(12.34, 15);
```

* 이 경우는 함수 템플릿에서 하나의 제네릭 형을 사용했지만, 전달인자의 두 형이 서로 다름
* 제네릭 형을 다음과 같이 명시적으로 사용하면 위 문제를 해결할 수 있음

```cpp
Smaller<double>(12.34, 15);
```

* 함수 템플릿 호출 시 이름과 전달인자 사이에 제네릭 형을 결정할 수 있음
  * `double`로 제네릭 형을 이미 결정했으므로, 함수 템플릿 `T`는 `double`
  * `15`는 실제로 매개변수로의 복사 시 `15.0`으로 암묵적 형 변환 발생

---

### 미리 정의된 연산 (Predefined Operation)

```cpp
// Definition of a template function
template <typename T>
T Smaller(const T& op1, const T& op2) { return op1 < op2 ? op1 : op2; }
```

* `Smaller(100, 200)` 또는 `Smaller(12.3, 45.6)` 등의 호출은 사용 시 문제가 없음
  * 기본 자료형에 대해 비교 연산이 이미 **컴파일러 내부에 정의**되어 있음
* 만약 사용자 정의 형 객체를 함수 템플릿 `Smaller`에 전달할 경우 문제가 생길 수 있음:
  * 사용자 정의 형 클래스가 작음 비교 연산자 (`<`, less than operator)를 재정의한 경우:

  ```cpp
  Smaller(std::string("hello"), std::string("bye"));  // bye
  ```

  * 만약 작음 비교 연산자가 구현되어 있지 않다면, **컴파일 시 오류 발생**

  ```cpp
  Smaller("hello", "bye");  // const char* has no '<' implementation
  ```

---

### 특수화 (Specialization)

```cpp
// Definition of a template function
template <typename T>
T Smaller(const T& op1, const T& op2) { return op1 < op2 ? op1 : op2; }

#include <cstring>

// specialization
template <>
const char* Smallest(const char* op1, const char* op2) {
  return std::strcmp(op1, op2) < 0 ? op1 : op2;
}
```

* 존재하는 함수 템플릿에 대해 예외 상황을 추가하여 특수화할 수 있음
* 특수화를 의미하는 템플릿 헤더는 `template <>`
* 함수 템플릿으로부터 특정 타입을 위한 **독립된 함수를 정의**
  * 함수 템플릿은 완성된 함수가 아닌 일종의 틀인 반면, 특수화된 함수는 완성된 함수임
* 위 예시는 작음 비교 연산자가 없는 경우를 특수화하여 컴파일 오류를 해결한 형태

---

### 오버로딩 (Overloading)

* 함수 템플릿에 오버로딩을 적용하면 가변 길이의 전달인자를 효율적으로 다룰 수 있음

#### The Program for Overloaded `Smaller` Function

```cpp
#include <iostream>

// Definition of a template function
template <typename T>
T Smallest(const T& op1, const T& op2) { return op1 < op2 ? op1 : op2; }

// Template function with three parameters
// Note that we have defined the second function in terms of the first one.
// That is the reason the second function is shorter.
template <typename T>
T Smallest(const T& op1, const T& op2, const T& op3) {
  return Smallest(Smallest(op1, op2), op3);
}

int main() {
  // Calling the overloaded version with three integers
  std::cout << "Smallest of 17, 12, and 27 is ";
  std::cout << Smallest(17, 12, 27) << std::endl;
  return 0;
}
```

---

## 함수 템플릿을 사용하는 경우에서의 파일 분할

* **함수 템플릿은 하나의 헤더 파일로 작성하는 것이 원칙**
  * 헤더 파일 내에 함수 템플릿 구현을 작성
  * **함수 템플릿은 선언과 구현을 분리하지 않음**
* 함수 템플릿의 선언과 구현을 분리할 경우:
  * foo.hpp, foo.cc, app.cc 세 개의 파일을 분할 컴파일한다고 가정
    * foo.hpp에는 함수 템플릿의 선언, foo.cc에는 함수 템플릿의 구현이 각각 담겨 있음
    * app.cc는 foo.hpp를 사용해 함수 템플릿을 사용하는 형태
  * 컴파일러가 app.cc를 먼저 컴파일할 경우, 함수 템플릿 선언만 존재하므로 인스턴스화 불가
    * 빌드 시 컴파일 의존관계를 고려해야 함
    * foo.cc를 먼저 컴파일해 목적파일을 생성한 뒤, 이를 app.cc 컴파일에 같이 사용해야 함

---

### Definition of a Function Template

* smaller.hpp

```cpp
#pragma once

// Definition of a template function
template <typename T>
T Smaller(const T& op1, const T& op2) {
  return op1 < op2 ? op1 : op2;
}
```

* main.cc

```cpp
#include <iostream>

#include "smaller.hpp"

int main() {
  std::cout << "Smaller of 'a' and 'b': " << Smaller('a', 'b') << std::endl;
  std::cout << "Smaller of 12 and 15: " << Smaller(12, 15) << std::endl;
  std::cout << "Smaller of 44.2 and 33.1: " << Smaller(44.2, 33.1) << std::endl;
  return 0;
}
```

---

## 클래스 템플릿 (Class Template)

```cpp
template <typename T>
class Name {
  T data;

 public:
  T get() const;            // accessor 
  void set(const T& data);  // mutator function
};

// Implementation of the get function
template <typename T>
T Name<T>::get() const { return data; }

// Implementation of the set function
template <typename T>
void Name<T>::set(const T& d) { data = d; }
```

* 기존 클래스 설계에 함수 템플릿 기능을 추가한 클래스
* 제네릭 형을 사용해 여러 형태의 클래스 인스턴스화 가능
  * 대표적인 클래스 템플릿으로는 표준 C++ 문자열 클래스가 있음
* 클래스 템플릿은 함수 템플릿과 마찬가지로 **하나의 헤더 파일**로 사용할 것을 권장
  * 헤더파일 안에 클래스 템플릿의 선언과 구현이 같이 존재해야 함

---

### 클래스 템플릿 분할 컴파일 1 - 명시적 인스턴스화 (Explicit Instantiation)

* 클래스 템플릿을 하나의 헤더 파일로 사용하지 않고, 선언과 구현을 분리하는 방법
* 미리 클래스 템플릿에 적용될 수 있는 형을 코드에 명시적으로 표현
  * 미리 인스턴스화할 형을 지정함에 따라 컴파일 속도 개선 효과가 있음
* 선언과 분리가 반드시 분리되어야 할 경우 사용할 수 있는 방법
  * 클래스 템플릿의 세부 구현은 감추고 싶은 경우
* 다양한 형을 지원해야 하는 상황이라면 명시적으로 지원해야 하는 모든 형을 표현해야 함
  * 관리 측면에서 번거로울 수 있음
* 컴파일 시 **의존성 관리**를 해주어야 함
  * 반드시 클래스 템플릿을 먼저 컴파일된 후에 이를 컴파일 과정에 포함하도록 구성해야 함
  * Makefile 또는 CMake 등을 활용할 수 있음

  ```shell
  g++ -c fun.cc -o fun.o && g++ main.cc fun.o -o run
  ```

---

* fun.hpp

```cpp
#pragma once

template <typename T>
class Fun {
  T data_;

 public:
  explicit Fun(const T& data);
  ~Fun() = default;

  T get() const;
  void set(const T& data);
};
```

---

* fun.cc

```cpp
#include "fun.hpp"

#include <string>

// Constructor
template <typename T>
Fun<T>::Fun(const T& d) : data_(d) {}

// Accessor Function
template <typename T>
T Fun<T>::get() const {
  return data_;
}

// Mutator Function
template <typename T>
void Fun<T>::set(const T& d) {
  data_ = d;
}

// Explicit instantiation
template class Fun<int>;
template class Fun<double>;
template class Fun<char>;
template class Fun<std::string>;
```

---

* main.cc

```cpp
#include <iostream>
#include <string>

#include "fun.hpp"

int main() {
  Fun<int> fun1(23);
  Fun<double> fun2(12.7);
  Fun<char> fun3('A');
  Fun<std::string> fun4("Hello");

  // undefined reference to `Fun<float>::Fun(float const&)'
  // Fun<float> fun5(123.4f);  // there's no explicit instantiation for float

  std::cout << "fun1: " << fun1.get() << std::endl;
  std::cout << "fun2: " << fun2.get() << std::endl;
  std::cout << "fun3: " << fun3.get() << std::endl;
  std::cout << "fun4: " << fun4.get() << std::endl;

  fun1.set(47);
  std::cout << "fun1 after set: " << fun1.get() << std::endl;
  fun3.set('B');
  std::cout << "fun3 after set: " << fun3.get() << std::endl;
  return 0;
}
```

---

### 클래스 템플릿 분할 컴파일 2 - 하나의 헤더 파일

* 헤더 파일에 클래스 템플릿의 선언과 구현을 같이 작성하는 방법
* **컴파일 의존관계를 고려하지 않아도 됨**
* 어떠한 형을 사용하더라도 인스턴스화가 가능함
* 컴파일 시간은 명시적 인스턴스화를 사용하는 방법보다 길어질 수 있음
* 하나의 헤더 파일이 외부에 공개되어야 한다면 클래스 템플릿의 세부 구현이 노출될 수 있음

---

* fun.hpp

```cpp
#pragma once

#include <string>

template <typename T>
class Fun {
  T data_;

 public:
  explicit Fun(const T& data);
  ~Fun() = default;

  T get() const;
  void set(const T& data);
};

// Constructor
template <typename T>
Fun<T>::Fun(const T& d) : data_(d) {}

// Accessor Function
template <typename T>
T Fun<T>::get() const {
  return data_;
}

// Mutator Function
template <typename T>
void Fun<T>::set(const T& d) {
  data_ = d;
}
```

---

* main.cc

```cpp
#include <iostream>
#include <string>

#include "fun.hpp"

int main() {
  Fun<int> fun1(23);
  Fun<double> fun2(12.7);
  Fun<char> fun3('A');
  Fun<std::string> fun4("Hello");

  // It can create an instance corresponding to any type it is given.
  Fun<float> fun5(123.4f);

  std::cout << "fun1: " << fun1.get() << std::endl;
  std::cout << "fun2: " << fun2.get() << std::endl;
  std::cout << "fun3: " << fun3.get() << std::endl;
  std::cout << "fun4: " << fun4.get() << std::endl;

  fun1.set(47);
  std::cout << "fun1 after set: " << fun1.get() << std::endl;
  fun3.set('B');
  std::cout << "fun3 after set: " << fun3.get() << std::endl;
  return 0;
}
```

---

### 어떤 방법을 사용해야 하는가?

* 외부 공개용 헤더 파일 내에 클래스 템플릿을 사용하는 경우는 **거의 없음**
* 대부분의 클래스 템플릿은 내부적으로 사용하는 경우가 대부분
* **클래스 템플릿은 하나의 헤더 파일로 작성하는 것이 일반적**
* 외부에 공개할 헤더 파일에 클래스 템플릿이 존재한다면 이를 사용하지 않는 형태로 재작성 후 배포

---

### 클래스 템플릿을 사용한 스택 클래스 구현

* 제네릭 형을 사용해 범용적인 스택 클래스 구현

![center](Figure_15_4.png)

---

* stack_exception.hpp

```cpp
#pragma once

#include <exception>
#include <string>

class StackException : public std::exception {
 public:
  StackException(const std::string& what, const std::string& where) noexcept
      : what_(what), where_(where) {}
  ~StackException() noexcept override = default;

  const char* what() const noexcept override { return what_.c_str(); }
  const char* where() const noexcept { return where_.c_str(); }

 private:
  const std::string what_;
  const std::string where_;
};
```

---

* stack.hpp

```cpp
#pragma once

#include <iostream>
#include "stack_exception.hpp"

template <typename T>
class Stack {
 public:
  explicit Stack(int capacity) : capacity_(capacity), size_(0) {
    ptr_ = new T[capacity_];
  }

  ~Stack() { delete[] ptr_; }

  void push(const T& elem) {
    if (size_ >= capacity_)
      throw StackException("Stack is full", "Stack::push");
    ptr_[size_++] = elem;
  }

  T pop() {
    if (size_ <= 0) throw StackException("Stack is empty", "Stack::pop");
    return ptr_[--size_];
  }

 private:
  T* ptr_;
  int capacity_;
  int size_;
};
```

---

* main.cc

```cpp
#include <iostream>

#include "stack.hpp"

int main() {
  try {
    Stack<int> stack(3);
    stack.push(10);
    stack.push(20);
    stack.push(30);

    // Uncommenting this line will throw an exception
    // stack.push(40);

    std::cout << "Popped: " << stack.pop() << std::endl;
    std::cout << "Popped: " << stack.pop() << std::endl;
    std::cout << "Popped: " << stack.pop() << std::endl;

    // Uncommenting this line will throw an exception
    // std::cout << "Popped: " << stack.pop() << std::endl;

  } catch (const StackException& e) {
    std::cerr << "Exception occurred: " << e.what()
              << ", Location: " << e.where() << std::endl;
  }

  return 0;
}
```

---

## 템플릿과 관련한 기타 문제 (Other Issues)

### `friend`

* 클래스 템플릿은 일반 함수, 함수 템플릿, 특수화된 함수 템플릿을 `friend`로 가질 수 있음

```cpp
#include <iostream>

// Function declarations
void NonTemplateFunction();

template <typename T>
void TemplateFunction(T value);

// specialization for int
template <>
void TemplateFunction<int>(int value);

template <typename T>
class MyClass {
  T value_;  // Internal value of the class

 public:
  explicit MyClass(T value) : value_(value) {}

  // Declare friend functions
  friend void NonTemplateFunction();
  template <typename U>
  friend void TemplateFunction(U value);
  friend void TemplateFunction<int>(int value);
};
```

---

### 별칭 (Aliases)

* 템플릿은 코드가 길어짐에 따라 가독성이 낮아질 수 있음
* 별칭 (`using`)을 사용해 코드의 길이를 줄이거나 더욱 명료한 표현을 통해 가독성을 높일 수 있음

```cpp
// This allows us to use the alias as the full definition of the class in the
// code (program):
using IntStack = Stack<int>;
using DoubleStack = Stack<double>;
using StringStack = Stack<std::string>;

// Then we can use the type definitions in our program as shown below:
IntStack s1;
DoubleStack s2;
StringStack s3;
```

```cpp
template<typename T>
using Ptr = T*;  // Using 'using' to define a pointer alias in a concise way

int x = 42;
Ptr<int> intPointer = &x;  // Using the Ptr alias to declare an int pointer
```

---

### 상속 (Inheritance)

* 클래스 템플릿 또는 일반 클래스를 기반으로 사용해 새로운 클래스 템플릿을 파생할 수 있음

```cpp
template <typename T>
class BaseTemplate {
  T value_

 public:
  BaseTemplate(T val) : value_(val) {}
};

template <typename T>
class DerivedTemplate : public BaseTemplate<T> {
 public:
  DerivedTemplate(T val) : BaseTemplate<T>(val) {}
};
```

```cpp
class NonTemplateClass {
  int value_

 public:
  NonTemplateClass(int val) : value_(val) {}
};

template <typename T>
class DerivedFromNonTemplate : public NonTemplateClass {
 public:
  DerivedFromNonTemplate(T val) : NonTemplateClass(val) {}
};
```

---

### 이전에 학습했던 클래스 (in Retrospect)

* 이전에 학습한 클래스 중 일부는 **클래스 템플릿**

#### C++ 문자열 클래스

* 클래스 템플릿을 [`std::basic_string`](https://en.cppreference.com/w/cpp/string/basic_string) 형으로 특수화한 것

```cpp
template <typename CharT,
          typename Traits = std::char_traits<CharT>,
          typename Allocator = std::allocator<CharT>>
class basic_string;
```

* `CharT`
  * 문자열 구성에 사용하는 개별 문자 형
  * C++ 문자열은 제네릭 형 `CharT`를 `char` 형으로 특수화한 것
* `Traits`
  * 문자열 연산 방법을 정의하는 클래스
  * `Traits` 형은 기본 형이 지정되어 있으며, 필요에 따라 변경해 사용 가능
* `Allocator`
  * 메모리 관리 방법을 정의하는 클래스
  * `Allocator` 형은 기본 형이 지정되어 있으며, 필요에 따라 변경해 사용 가능

---

* my_char_traits.hpp

```cpp
#pragma once

#include <cctype>
#include <iostream>
#include <string>

// Custom char_traits implementation to get case-insentive comparison
class MyCharTraits : public std::char_traits<char> {
  // std::char_traits requires specific method names like `lt` and `compare` for
  // STL compatibility. These methods are static to allow direct access without
  // instantiating the class. Changing method names breaks the contract and
  // causes the standard library to fail.

 public:
  static int MyRank(char c) noexcept { return std::tolower(c); }

  static bool lt(const char c1, const char c2) noexcept {
    return MyRank(c1) < MyRank(c2);
  }
  static int compare(const char* s1, const char* s2, size_t n) noexcept {
    while (n--) {
      if (MyRank(*s1) < MyRank(*s2)) return -1;
      if (MyRank(*s1) > MyRank(*s2)) return 1;
      ++s1;
      ++s2;
    }
    return 0;
  }
};
```

---

* main.cc

```cpp
#include <iostream>

#include "my_char_traits.hpp"

int main() {
  // Using MyCharTraits with basic_string
  std::basic_string<char, MyCharTraits> my_s1 = "ABcd";
  std::basic_string<char, MyCharTraits> my_s2 = "abCD";
  std::cout << "MyCharTraits: " << std::boolalpha << (my_s1 == my_s2)
            << std::endl;

  // Using std::string for comparison
  std::string s1 = "ABcd";
  std::string s2 = "abCD";
  std::cout << "C++ string: " << std::boolalpha << (s1 == s2) << std::endl;

  return 0;
}
```

---

#### 입출력 클래스

* [`std::basic_istream`](https://en.cppreference.com/w/cpp/io/basic_istream), [`std::basic_ostream`](https://en.cppreference.com/w/cpp/io/basic_ostream) 클래스 템플릿을 특수화한 것

```cpp
template <typename CharT, typename Traits = std::char_traits<CharT>>
class basic_istream;

template <typename CharT, typename Traits = std::char_traits<CharT>>
class basic_ostream;
```

* `std::cin` 객체와 `std::cout` 객체는 `CharT` 형을 `char`형으로 특수화하여 생성한 객체

```cpp
using std::istream = std::basic_istream<char>;
using std::ostream = std::basic_ostream<char>;
```

---

## 스마트 포인터 (Smart Pointers)

```cpp
class Fraction;  // Forward declaration for the type you want to use

class SmartPtr {
  Fraction* ptr_;

 public:
  explicit SmartPtr(Fraction* p) : ptr_(p) {}
  ~SmartPtr() { delete ptr_; }
  Fraction& operator*() const { return *ptr_; }
  Fraction* operator->() const { return ptr_; }
};

int main() {
  SmartPtr sp(new Fraction(2, 5));
  (*sp).print();
  sp->print();  // `sp` is a stack instance; it's dtor will auto-invoke!
}
```

* 동적 메모리 관리의 자동화를 위한 포인터 래퍼 (wrapper) 클래스
* 메모리 누수와 자원 관리 문제 해결
* **제네릭 프로그래밍과 결합하여 메모리 안전성 향상**

---

### RAII (Resource Acquisition Is Initialization)

* 자원의 획득과 해제를 객체의 수명에 묶어 관리
* 객체 생성 시 자원 획득, 소멸 시 자원 해제
* **스마트 포인터의 동작 원리**
  * 스마트 포인터는 RAII 원칙을 적용하여 메모리 관리 자동화
  * 예외 발생 시에도 자원이 자동으로 해제되어 안전성 향상
  * 명시적인 메모리 해제 코드 불필요
  * 예외 안전성 제공 및 코드의 유지보수성 향상

```cpp
#include <iostream>

class Resource {
 public:
  Resource() { std::cout << "Acquired resource\n"; }
  ~Resource() { std::cout << "Released resource\n"; }
};

int main() {
  {
    Resource res;  // Acquire resource upon construction
    // Use the resource
  }  // Automatically release resource upon scope exit
  return 0;
}
```

---

### `std::unique_ptr`

* **단독 소유권**을 가지는 스마트 포인터
* 복사와 대입 불가
  * 복사 연산자와 대입 연산자가 삭제 (`delete`)되어 있음
  * 소유권 이동은 가능
* 자동 메모리 해제 제공

```cpp
#include <iostream>
#include <memory>  // for smart pointers

class MyObject {
 public:
  MyObject() { std::cout << "MyObject created\n"; }
  ~MyObject() { std::cout << "MyObject destroyed\n"; }
  void DoSomething() { std::cout << "Doing something\n"; }
};

int main() {
  std::unique_ptr<MyObject> ptr(new MyObject());
  ptr->DoSomething();  // Use the object
  // No need to delete; memory is managed automatically

  // Attempt to copy the unique_ptr (this will cause a compile-time error)
  // Error: Copy constructor is deleted
  // std::unique_ptr<MyObject> ptr_copy = ptr;
  return 0;
}
```

---

#### `get()` 메서드

* 스마트 포인터 객체가 가리키는 객체의 **주소**을 얻어올 때 사용
* 기존의 C API나 라이브러리와의 호환성을 위해 필요
* `get()`으로 받은 포인터를 통해 메모리를 관리하지 말 것

```cpp
#include <iostream>
#include <memory>  // for smart pointers

class MyObject {
 public:
  MyObject() { std::cout << "MyObject created\n"; }
  ~MyObject() { std::cout << "MyObject destroyed\n"; }

  void DoSomething() { std::cout << "Doing something\n"; }
};

void UseRawPointer(MyObject* obj) { if (obj) obj->DoSomething(); }

int main() {
  // Create a unique_ptr managing a new MyObject
  std::unique_ptr<MyObject> ptr(new MyObject());
  UseRawPointer(ptr.get());

  // MyObject* raw_ptr = ptr.get(); // Improperly manage memory using the raw
  // ptr delete raw_ptr; // Logical Error: Deletes the object managed by
  // unique_ptr

  // At the end of scope, unique_ptr will try to delete the object again
  // This leads to undefined behavior (double deletion)
  return 0;
}
```

---

### `std::make_unique`

* C++14에서 도입된 유틸리티 함수
* 스마트 포인터 객체 생성과 포인터 래핑을 한 줄로 처리

```cpp
#include <iostream>
#include <memory>

class MyObject {
 public:
  MyObject() { std::cout << "MyObject created\n"; }
  ~MyObject() { std::cout << "MyObject destroyed\n"; }
  void DoSomething() { std::cout << "Doing something\n"; }
};

int main() {
  // You can replace std::unique_ptr<MyObject> ptr(new MyObject()) with:
  std::unique_ptr<MyObject> ptr = std::make_unique<MyObject>();
  ptr->DoSomething();
  return 0;
}
```

---

### `std::shared_ptr`, `std::make_shared`

* 복수의 소유자를 가질 수 있는 스마트 포인터
* 참조 개수 계산 (reference counting)을 통해 객체 생명 주기 관리
  * `std::unique_ptr`은 단일 소유이므로 해당 객체가 소멸될 때 반드시 소멸됨을 보장
  * `std::shared_ptr`은 해당 객체가 소멸되더라도 참조 개수가 0이 아니면 소멸되지 않음
* 복사 및 대입 가능

```cpp
#include <iostream>
#include <memory>

class MyObject {
 public:
  MyObject() { std::cout << "MyObject created\n"; }
  ~MyObject() { std::cout << "MyObject destroyed\n"; }
};

int main() {
  // Create a shared_ptr using make_shared
  std::shared_ptr<MyObject> ptr1 = std::make_shared<MyObject>();
  std::cout << "Reference count after creation: " << ptr1.use_count() << "\n";
  {
    // Copy ptr1 to ptr2, increasing the reference count
    std::shared_ptr<MyObject> ptr2 = ptr1;
    std::cout << "Reference count after copying to ptr2: " << ptr1.use_count()
              << "\n";
  }  // ptr2 goes out of scope here, decreasing the reference count
  std::cout << "Reference count after ptr2 is out of scope: "
            << ptr1.use_count() << "\n";
  return 0;
}
```

---

* 원시 포인터로 `std::shard_ptr`을 생성하지 말 것
  * 원시 포인터를 사용해 `std::shared_ptr`을 생성할 경우 **이중 삭제**를 유발하게 됨
    * 서로 다른 제어 블록 (control block)을 생성하게 됨 (참조 개수 계산이 분산됨)

```cpp
#include <iostream>
#include <memory>

class Foo {
  int* data_;

 public:
  Foo() {
    data_ = new int[100];
    std::cout << "Acquired resources!\n";
  }

  ~Foo() {
    std::cout << "Destructor called!\n";
    delete[] data_;
  }
};

int main() {
  Foo* a = new Foo();

  std::shared_ptr<Foo> pa1(a);
  std::shared_ptr<Foo> pa2(a);

  std::cout << "Use count: " << pa1.use_count() << std::endl;
  std::cout << "Use count: " << pa2.use_count() << std::endl;
  return 0;
}
```

---

* 원시 포인터로 `std::shard_ptr`을 생성하지 말 것
  * `std::make_shared`를 사용한 객체를 활용할 것

```cpp
#include <iostream>
#include <memory>

class Foo {
  int* data_;

 public:
  Foo() {
    data_ = new int[100];
    std::cout << "Acquired resources!\n";
  }

  ~Foo() {
    std::cout << "Destructor called!\n";
    delete[] data_;
  }
};

int main() {
  std::shared_ptr<Foo> pa1 = std::make_shared<Foo>();
  std::shared_ptr<Foo> pa2 = pa1;

  std::cout << "Use count: " << pa1.use_count() << std::endl;
  std::cout << "Use count: " << pa2.use_count() << std::endl;
  return 0;
}
```

---

* 클래스 내부에서 자신의 `std::shared_ptr`을 생성해야 하는 상황
  * 직접 `this` 포인터 (원시 포인터)를 사용해 생성할 경우 **독립적인 제어 블록**이 생성됨
* `std::enable_shared_from_this`를 상속받아 `shared_from_this()` 함수를 사용할 것
  * 이미 생성된 `std::shared_ptr` 객체 (호스트 객체)의 제어 블록을 사용하는 객체를 반환

```cpp
#include <iostream>
#include <memory>

class Foo : public std::enable_shared_from_this<Foo> {
  int* data_;

 public:
  Foo() {
    data_ = new int[100];
    std::cout << "Acquired resources!\n";
  }

  ~Foo() {
    std::cout << "Destructor called!\n";
    delete[] data_;
  }

  std::shared_ptr<Foo> GetSharedPtr() { return shared_from_this(); }
};

int main() {
  std::shared_ptr<Foo> pa1 = std::make_shared<Foo>();
  std::shared_ptr<Foo> pa2 = pa1->GetSharedPtr();

  std::cout << "Use count: " << pa1.use_count() << std::endl;
  std::cout << "Use count: " << pa2.use_count() << std::endl;
  return 0;
}
```

---

### 순환 참조와 `std::weak_ptr`

* `std::shared_ptr` 간의 순환 참조로 인해 참조 개수가 0이 되지 않아 메모리 누수 발생

```cpp
#include <iostream>
#include <memory>

class B;  // Forward declaration

class A {
  std::shared_ptr<B> partner_;  // Causes circular reference

 public:
  ~A() { std::cout << "A destroyed\n"; }

  void SetPartner(const std::shared_ptr<B>& partner) { partner_ = partner; }
};

class B {
  std::shared_ptr<A> partner_;  // Causes circular reference

 public:
  ~B() { std::cout << "B destroyed\n"; }

  void SetPartner(const std::shared_ptr<A>& partner) { partner_ = partner; }
};

int main() {
  std::shared_ptr<A> a = std::make_shared<A>();
  std::shared_ptr<B> b = std::make_shared<B>();
  a->SetPartner(b);
  b->SetPartner(a);
  // Objects 'a' and 'b' will not be destroyed due to circular reference
  return 0;
}
```

---

* `std::weak_ptr`을 사용해 순환 참조 문제 해결 가능
* `std::weak_ptr`은 일반 포인터와 `std::shared_ptr` 사이에 위치한 스마트 포인터
* 객체를 직접 소유하지 않으며, 객체의 소멸 여부 확인 가능
  * **참조 개수를 증가시키지 않고** 객체를 안전하게 관찰 가능

```cpp
#include <iostream>
#include <memory>

class B;  // Forward declaration

class A {
  std::weak_ptr<B> partner_;  // Use weak_ptr to prevent circular reference

 public:
  ~A() { std::cout << "A destroyed\n"; }

  void SetPartner(const std::shared_ptr<B>& partner) { partner_ = partner; }
};

class B {
  std::weak_ptr<A> partner_;  // Use weak_ptr to prevent circular reference

 public:
  ~B() { std::cout << "B destroyed\n"; }

  void SetPartner(const std::shared_ptr<A>& partner) { partner_ = partner; }
};

int main() {
  std::shared_ptr<A> a = std::make_shared<A>();
  std::shared_ptr<B> b = std::make_shared<B>();
  a->SetPartner(b);
  b->SetPartner(a);
  // Both objects can be destroyed properly as there is no circular strong
  // reference
  return 0;
}
```

---

* `std::weak_ptr`은 객체로의 직접 참조가 불가하며, `lock()` 메서드를 사용해야 함
  * 현재 객체를 가리키는 `std::shared_ptr` 값 반환
  * 만약 객체가 이미 소멸되었다면 `nullptr` 반환

```cpp
#include <iostream>
#include <memory>

int main() {
  std::weak_ptr<int> weak;

  {
    std::shared_ptr<int> sp = std::make_shared<int>(42);
    weak = sp;  // weak_ptr observes the shared_ptr

    // Before shared_ptr goes out of scope
    if (std::shared_ptr<int> locked = weak.lock())
      std::cout << "Shared_ptr value: " << *locked << "\n";
    else
      std::cout << "Shared_ptr is empty\n";
  }  // sp goes out of scope, the managed object is destroyed

  // After shared_ptr is destroyed
  if (std::shared_ptr<int> locked = weak.lock()) {
    std::cout << "Shared_ptr value: " << *locked << "\n";
  } else {
    std::cout << "Shared_ptr is empty (nullptr)\n";
  }

  return 0;
}
```
