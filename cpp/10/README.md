# 제네릭 프로그래밍 (Generic Programming: Templates)

## 함수 템플릿 (Function Template)

* 함수 내 일부 형을 컴파일 시점에 확정하는 기법
* 동일한 로직을 서로 다른 여러 형에 대해 중복 없이 구현할 수 있게 해주는 메커니즘

```cpp
template <typename T, typename U, ..., typename Z>
T function_template_syntax(U first, ..., Z last) {
  // do something ...
}
```

* 함수 템플릿을 위한 템플릿 헤더 (template header)는 `template` 키워드를 사용
* 템플릿 헤더의 내용은 `<>` 괄호를 사용하며, **제네릭 형 (generic type)** 표현에 사용됨
  * 템플릿 매개변수 (template parameter): `T`, `U`, `Z`
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

### 함수 템플릿과 함수 오버로딩 간 비교 (Comparison: Function Template vs Overloading)

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
  * 자신이 대표하는 구체적인 형(concrete type)이 없으면 컴파일되지 않음
* 컴파일 시점에 함수 템플릿을 사용하는 형태에 맞게 동작할 수 있는 함수를 생성
  * 예: `Smaller(12, 15)` 호출 → 컴파일러가 `int` 형 인스턴스 생성
  * 예: `Smaller(3.14, 2.71)` 호출 → 컴파일러가 `double` 형 인스턴스 생성
* 함수 템플릿으로부터 함수 코드를 생성하는 행위를 **인스턴스화**라고 함
  * 클래스로부터 객체를 생성하는 인스턴스화와 용어는 같지만 다른 의미임에 유의
  * 클래스 인스턴스화: 클래스로부터 객체 생성
  * 템플릿 인스턴스화: 템플릿으로부터 구체적인 함수/클래스 코드 생성

---

## 함수 템플릿의 변형 (Variations)

* 기본 함수 템플릿 문법으로부터 변형된 몇 가지 형태들

### 자료형이 아닌 템플릿 매개변수 (Non-Type Template Parameter)

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
  * 부동소수점 수는 정밀도 제약이 존재해 값이 매번 다르게 표현될 수 있음
    * 예시: `double x = 0.1; double y = 0.1;` 일 때, `x == y`가 항상 참이 아닐 수 있음
    * 템플릿 인스턴스화는 컴파일 시점에 이루어지므로 이런 부정확성을 허용할 수 없음
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
* 기본 매개변수를 형이 아닌 값으로 사용할 경우 아래와 같은 형이어야 함:
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
  print<double, 3, 2>(arr2);   // Specifies step = 2 explicitly

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
T Smallest(const T& op1, const T& op2) { return op1 < op2 ? op1 : op2; }

#include <cstring>

// specialization
template <>
const char* Smallest(const char* op1, const char* op2) {
  return std::strcmp(op1, op2) < 0 ? op1 : op2;
}
```

* 존재하는 함수 템플릿에 대해 예외 상황을 추가하여 특수화할 수 있음
* 특수화를 의미하는 템플릿 헤더는 `template <>`
  * 모든 템플릿 매개변수가 구체적인 형으로 결정됨을 의미
* 함수 템플릿으로부터 특정 타입을 위한 **독립된 함수를 정의**
  * 함수 템플릿은 완성된 함수가 아닌 일종의 틀인 반면, 특수화된 함수는 완성된 함수임
  * **컴파일러는 특수화된 함수를 일반 템플릿보다 우선 선택** (더 구체적이므로)
* 위 예시는 포인터 형식이 작음 비교 연산자를 적절히 처리하지 못하는 경우를 특수화하여 해결한 형태
  * `const char*` 형식의 문자열 포인터를 비교할 때 `std::strcmp()`를 사용하도록 특수화
  * 포인터 간 직접 비교는 메모리 주소를 비교하므로 의도와 다름

---

### 오버로딩 (Overloading)

* 함수 템플릿에 오버로딩을 적용하면 가변 길이의 전달인자를 효율적으로 다룰 수 있음
* **오버로딩과 특수화의 차이**:
  * **오버로딩**: 같은 이름의 템플릿을 **여러 개** 정의 (다른 템플릿 매개변수 개수 등)
    * `Smallest(T, T)` (2개 인자)와 `Smallest(T, T, T)` (3개 인자) 모두 정의
    * 컴파일러가 호출 인자에 맞는 템플릿을 자동으로 선택
  * **특수화**: 같은 이름의 기존 템플릿에 대해 **특정 형만** 별도 구현
    * 기존 일반 템플릿 + `const char*`에 대한 특수화

#### 오버로드된 `Smallest` 함수 (The Program for Overloaded `Smallest` Function)

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

## 함수 템플릿을 사용하는 경우에서의 파일 분할 (File Separation When Using Function Templates)

* **함수 템플릿은 하나의 헤더 파일로 작성하는 것이 원칙**
  * 헤더 파일 내에 함수 템플릿 구현을 작성
  * **함수 템플릿은 선언과 구현을 분리하지 않음**
* 함수 템플릿의 선언과 구현을 분리할 경우의 문제점:
  * foo.hpp, foo.cc, main.cc 세 개의 파일을 분할 컴파일한다고 가정
    * foo.hpp에는 함수 템플릿의 선언, foo.cc에는 함수 템플릿의 구현이 각각 담겨 있음
    * main.cc는 foo.hpp를 포함(`#include`)하여 함수 템플릿을 사용하는 형태
  * **컴파일 순서 문제**: 컴파일러가 main.cc를 먼저 컴파일할 경우
    * foo.hpp에는 함수 템플릿 **선언**만 존재하며, 실제 구현은 foo.cc에 있음
    * main.cc에서 함수 템플릿을 호출해도 인스턴스화할 정의(구현)가 없으므로 **인스턴스화 불가**
    * 빌드 시 링커 오류 발생
  * **해결 방법**: 컴파일 의존관계를 고려해야 함
    * foo.cc를 먼저 컴파일해 목적파일(object file)을 생성
    * 그 뒤 main.cc를 컴파일하면서 foo.o를 링크: `g++ main.cc foo.o -o run`

---

### 함수 템플릿의 정의 (Definition of a Function Template)

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

* 기존 클래스 설계에 템플릿 매개변수를 추가한 클래스
  * 클래스 내부에 템플릿 형 `T`를 사용하여 데이터, 함수 정의 가능
* 제네릭 형을 사용해 여러 형태의 클래스 인스턴스화 가능
  * `Name<int>`, `Name<double>`, `Name<std::string>` 등 각각 다른 형의 클래스 생성
  * 대표적인 클래스 템플릿: 표준 C++ 라이브러리의 `vector<T>`, `list<T>` 등
* 클래스 템플릿 메서드 정의 시 주의:
  * 일반 클래스: `void Class::method() { ... }`
  * 템플릿 클래스: `template <typename T> void Class<T>::method() { ... }`
    * 메서드도 템플릿이므로 `template` 선언 필요
* 클래스 템플릿은 함수 템플릿과 마찬가지로 **하나의 헤더 파일**로 사용할 것을 권장
  * 헤더파일 안에 클래스 템플릿의 선언과 구현이 같이 존재해야 함

---

### 클래스 템플릿 분할 컴파일 1 - 명시적 인스턴스화 (Explicit Instantiation)

* 클래스 템플릿을 하나의 헤더 파일로 사용하지 않고, 선언과 구현을 분리하는 방법
* 미리 클래스 템플릿에 적용될 수 있는 형을 코드에 명시적으로 표현
  * 미리 인스턴스화할 형을 지정함에 따라 컴파일 속도 개선 효과가 있음
  * 필요한 형만 인스턴스화하므로 바이너리 크기를 줄일 수 있음
* 선언과 구현을 분리해야 할 경우 사용할 수 있는 방법
  * 클래스 템플릿의 세부 구현은 감추고 싶은 경우
  * 대규모 프로젝트에서 컴파일 시간을 단축하고 싶은 경우
* 다양한 형을 지원해야 하는 상황이라면 명시적으로 지원해야 하는 모든 형을 표현해야 함
  * 관리 측면에서 번거로울 수 있음
  * 지원하지 않는 형을 사용할 경우 링킹 오류 발생
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

### 클래스 템플릿 분할 컴파일 2 - 하나의 헤더 파일 (Class Template Split Compilation 2 - Single Header File)

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

### 어떤 방법을 사용해야 하는가? (Which Approach Should Be Used?)

| Item | Explicit Instantiation | Single Header File |
|------|----------------------|-------------------|
| **File Separation** | Possible (Header + Implementation) | Not Possible (Header Only) |
| **Compilation Speed** | Fast (Only Required Types) | Can Be Slow (All Types Compiled) |
| **Binary Size** | Small | Can Be Large |
| **Implementation Privacy** | Hidden | Exposed |
| **Maintenance** | Tedious (Explicit All Types) | Easy |
| **Adding New Types** | Recompilation Required | Automatic Support |
| **Linking Error Risk** | High (Unsupported Types) | Low |

* 외부 공개용 헤더 파일 내에 클래스 템플릿을 사용하는 경우는 **거의 없음**
  * 구현 세부사항이 노출되므로 문제 가능성
* 대부분의 클래스 템플릿은 내부적으로 사용하는 경우가 대부분
* **권장 사항: 클래스 템플릿은 하나의 헤더 파일로 작성하는 것이 일반적**
  * 표준 라이브러리의 `vector`, `list` 등도 모두 헤더 파일에 구현
* 외부에 공개할 헤더 파일에 클래스 템플릿이 존재한다면
  * 명시적 인스턴스화를 사용하거나
  * 템플릿을 사용하지 않는 형태로 재작성 후 배포

---

### 클래스 템플릿을 사용한 스택 클래스 구현 (Stack Implementation Using Class Template)

* 제네릭 형을 사용해 범용적인 스택 클래스 구현
* 동적 메모리할당으로 임의의 용량을 가진 스택 생성 가능
* 예외 기반의 오류 처리로 안전한 스택 연산 제공

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

  // Default destructor causes memory leak for dynamically allocated memory
  // (Explicit destructor implementation for example simplification)
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
* 별칭은 단순한 이름 변경일 뿐 새로운 형을 만드는 것이 아님

```cpp
// This allows us to use the alias as the full definition of the class
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

#### 템플릿 클래스에서 상속

```cpp
template <typename T>
class BaseTemplate {
  T value_;

 public:
  BaseTemplate(T val) : value_(val) {}
};

template <typename T>
class DerivedTemplate : public BaseTemplate<T> {
 public:
  DerivedTemplate(T val) : BaseTemplate<T>(val) {}
};
```

#### 일반 클래스에서 템플릿 클래스 파생

```cpp
class NonTemplateClass {
  int value_;

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

### 이전에 학습했던 클래스 (Previously Learned Classes)

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

// Custom char_traits implementation to get case-insensitive comparison
class MyCharTraits : public std::char_traits<char> {
  // std::char_traits requires specific method names like `lt` and `compare`
  // for STL compatibility. These methods are static to allow direct access
  // without instantiating the class. Changing method names breaks the contract
  // and causes the standard library to fail.

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
