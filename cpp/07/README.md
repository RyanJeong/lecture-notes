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

# 다형성 (Polymorphism)

## 실세계에서의 다형성 예시: Plug-compatible Objects

![center](Figure_12_1.png)

* 두 개의 전자기기 (램프, 텔레비전)는 **표준 플러그**를 **표준 소켓**에 꽂을 수 있음
  * At time t1: 램프를 소켓에 연결
  * At time t2: 텔레비전을 소켓에 연결
* 각 전자기기는 소켓으로부터 **동일한 전원**을 공급받아 서로 다른 일을 수행
  * 램프는 전기를 공급 받아 빛을 냄
  * 텔레비전은 전기를 공급 받아 화면에 영상을 표시하고 스피커를 통해 소리를 재생함

---

## 프로그래밍에서의 다형성

* 객체의 **실제 형**에 따라 **같은 인터페이스**로 **다양한 동작**을 실행할 수 있는 기능
  * 실제 형: 전자기기의 유형
  * 같은 인터페이스: 전자기기의 표준 플러그
  * 다양한 동작: 동일한 전원을 공급받는 전자기기는 서로 다른 일을 수행

### 다형성을 사용하기 위한 조건

* 기반 클래스 형 포인터 혹은 레퍼런스
  * 예시에서의 **표준 소켓**
  * 포인터는 여러 형 객체를 가리킬 수 있어야 함
* 상속 계층 (inheritance hierarchy)에 속하는 호환 객체 (exchangeable ojbects)
  * 예시에서의 **표준 플러그**
  * 기반 클래스 형 포인터는 호환 객체를 가리킬 수 있음
* 가상 함수 (virtual functions)
  * 예시에서의 **동일한 전원**
  * 가상 함수는 자기 자신을 호출한 객체의 **실제 형**에 맞는 함수를 찾아 호출할 수 있음

---

### 파생 클래스 형 객체의 실체화

* 파생 클래스 형 객체를 생성하면 아래 주어진 절차에 따라 메모리를 할당:
  1. 최상위 클래스 (기반 클래스이자 모든 클래스들이 이를 상속받음)의 데이터 멤버를 메모리에 점유한다.
  2. 첫 번째 파생 클래스 (immediate derived class, first-level derived class)의 데이터 멤버를 메모리에 점유한다.
  3. 두 번째 파생 클래스 (second-level derived class)의 데이터 멤버를 메모리에 점유한다.
  4. ...

```text
+------------+  <-- Base Address
| T0 members |    --> Base Class member (Size: sizeof(T0))
+------------+  <-- Base Address + sizeof(T0)
| T1 members |    --> 1st level member (Size: sizeof(T1))
+------------+  <-- Base Address + sizeof(T0) + sizeof(T1)
| T2 members |    --> 2nd level member (Size: sizeof(T2))
+------------+  <-- Base Address + sizeof(T0) + sizeof(T1) + sizeof(T2)
| ...        |
+------------+  <-- Base Address + ∑(sizeof(Ti)) (i = 0 to n - 1)
| Tn members |    --> n-level member (Size: sizeof(Tn))
+------------+  <-- Base Address + ∑(sizeof(Ti)) (i = 0 to n)
```

* **기반 클래스 형 포인터는 기반 클래스를 상속한 모든 클래스 형 객체를 가리킬 수 있음**
  * 기반 클래스로부터 파생된 모든 객체는 **기반 클래스 영역**을 포함
  * 기반 클래스 형 포인터가 파생 클래스 형 객체를 가리키면 **기반 클래스 영역**만 가리킴

---

### 불완전한 다형성 - 일반 함수 오버라이드 (Non-virtual Function Override)

```cpp
#include <iostream>

class Base {
 public:
  void print() const { std::cout << "In the base class" << std::endl; }
};

class Derived : public Base {
 public:
  void print() const { std::cout << "In the derived class" << std::endl; }
};

int main() {
  Base* ptr = new Base();
  ptr->print();
  delete ptr;
  ptr = new Derived();
  ptr->print();
  delete ptr;
  return 0;
}
```

* `ptr`은 기반 클래스 형 포인터
* 컴파일러는 `ptr->print()` 문장을 처리할 때 **포인터의 형**을 보고 `Base::print()` 호출
  * 가리키는 대상과 관계 없이 컴파일 시점에 호출할 대상이 결정됨

---

### 완전한 다형성 - 가상 함수 오버라이드 (Virtual Function Override)

```cpp
#include <iostream>

class Base {
 public:
  virtual void print() const { std::cout << "In the base class" << std::endl; }
};

class Derived : public Base {
 public:
  void print() const override {
    std::cout << "In the derived class" << std::endl;
  }
};

int main() {
  Base* ptr = new Base();
  ptr->print();
  delete ptr;
  ptr = new Derived();
  ptr->print();
  delete ptr;
  return 0;
}
```

* 가상 함수는 **런타임 시점에 함수를 호출한 객체의 실제 형에 따라 함수를 선택할 수 있도록 설계됨**

---

## 가상 함수 (Virtual Functions)

* 기반 클래스에서 선언되고 파생 클래스에서 재정의 (override)될 수 있는 함수
* 가상 테이블과 가상 포인터의 도움을 받아 런타임 시점에 호출될 함수를 결정할 수 있음

### 가상 테이블 (Virtual Tables, Vtables)

* 상속 계층 구조에 속한 클래스가 가상 함수를 사용할 경우 생성되는 테이블
  * 컴파일 시점에 생성됨
  * 만약 가상 함수를 사용하지 않는다면 가상 테이블은 생성되지 않음
* 객체가 호출한 함수가 가상 함수라면, 객체의 실제 형에 해당하는 가상 테이블을 참조
  * 가상 테이블은 객체가 실제로 호출할 수 있는 가상 함수들을 기록한 **함수 포인터 테이블**
  * **런타임 시점**에 호출될 함수를 결정할 수 있음

![center](Figure_12_2.png)

---

### 가상 포인터 (Virtual Pointers, Vptr)

* 가상 테이블은 상속 계층 구조에 속한 모든 클래스마다 생성됨
* 각 클래스마다 가상 테이블을 참조할 수 있도록 가상 포인터가 **객체 내에 생성됨**
  * 컴파일러에 의해 런타임 시점에 추가되는 포인터
    * 컴파일러가 컴파일 시점에 가상 포인터를 설정하는 코드를 생성
    * 런타임 시스템은 컴파일러가 만들어 놓은 코드를 처리
  * 클래스에 속하는 것이 아닌 **객체에만 존재하는 포인터**
* 가상 포인터는 해당 객체의 형에 해당하는 가상 테이블을 가리키도록 설정됨
* **실체화된 객체의 가장 낮은 메모리 번지에 가상 포인터가 위치함**

![center](Figure_12_Vptr.png)

---

### 가상 함수 사용 방법

#### 기반 클래스 가상 함수

* 함수 선언부에 `virtual` 키워드 사용
  * 함수의 정의와 선언을 분리할 경우, 선언부에만 `virtual` 키워드 사용

#### 파생 클래스 가상 함수

* 기반 클래스의 가상 함수를 **재정의**하여 사용
  * 파생 클래스의 함수 시그니처는 기반 클래스의 가상 함수의 시그니처와 동일해야 함
* 함수 선언부에 `virtual` 또는 `override` 키워드 사용
  * 함수의 정의와 선언을 분리할 경우, 선언부에만 `virtual` 또는 `override` 키워드 사용

```cpp
class Animal {
 public:
  // This is a virtual function in the base class with no parameters
  virtual void move() const { /* ... */ }
};

class Cat : public Animal {
 public:
  // `override` is used to ensure that the derived class function is overriding
  // a virtual function from the base class. In this case, the function
  // signature `move()` matches the base class function (`move()`).

  // This function correctly overrides the base class's `move` function.
  void move() const override { /* ... */ }  // Ok
};
```

---

#### 파생 클래스에서의 가상 함수 재정의

* **`virtual` 키워드를 사용하는 것 보다는 `override` 키워드를 사용할 것을 적극 권장**

```cpp
class Animal {
 public:
  // This is a virtual function in the base class with no parameters
  virtual void move() const { /* ... */ }
};

class Dog : public Animal {
 public:
  // Error: `override` is used to ensure that the derived class function is
  // overriding a virtual function from the base class. In this case, the
  // function signature `move(int, int)` does not match the base class
  // function (`move()`). When function signatures don't match, the
  // `override` keyword triggers a compile-time error, preventing accidental new
  // function declaration.
  //
  // If `virtual` is used instead of `override` without matching the base class
  // function, this would declare a new virtual function in the derived class
  // instead of overriding the base class function.
  void move(int x, int y) const override { /* ... */ }  // Error
};
```

---

### 가상 함수 동작 예시

* 가상 테이블은 **기반 클래스에서의 가상 함수 선언 순서대로 함수 포인터를 엔트리에 삽입**
  * 가상 테이블은 컴파일 시점에 생성되고, 가상 포인터는 런타임 시점에 객체 내부에 설정됨

```cpp
#include <iostream>

class B {
 public:
  virtual void bar();  // vtable[0]
  virtual void qux();  // vtable[1]
};

void B::bar() { std::cout << "This is B's implementation of bar"; }
void B::qux() { std::cout << "This is B's implementation of qux"; }

class C : public B {
 public:
  // Class C's vtable entry at index 1 is assigned to C::bar during compile time
  void bar() override;
};

void C::bar() { std::cout << "This is C's implementation of bar"; }
```

![center h:200](Figure_12_Vtable_Vptr.png.png)

---

### 다형성에서의 기반 클래스

```cpp
#include <iostream>

class A {
  // A does not have a virtual function.
};

class B : public A {
 public:
  virtual void print() {  // Declares a virtual function.
    std::cout << "B's print" << std::endl;
  }
};

class C : public B {
 public:
  void print() override {  // Overrides the virtual function.
    std::cout << "C's print" << std::endl;
  }
};

int main() {
  B* obj = new C();
  obj->print();  // Calls C's print() (dynamic binding).
}
```

* 일반 상속 관계라면 기반 클래스는 `A`
* **다형성에서의 기반 클래스는 `B`**
  * 가상 함수를 선언한 클래스
  * 다형성을 사용하기 위해서는 `B` 형 포인터를 사용해야 함

---

### 일반 오버라이드 함수와 가상 오버라이드 함수 간 동작 비교

#### 일반 함수

```cpp
#include <iostream>

class Base {
 public:
  void NormalFunction() { std::cout << "Base normal function" << std::endl; }
};

class Derived : public Base {
 public:
  void NormalFunction() { std::cout << "Derived normal function" << std::endl; }
};

int main() {
  Base* ptr = new Derived();
  ptr->NormalFunction();
  delete ptr;
}
```

* 컴파일 시점에서의 `ptr->NormalFunction()` 문장 처리:
  * 일반 함수이므로 `Base::NormalFunction()`을 호출하도록 결정
    * 함수의 주소를 바로 참조하여 호출
  * 정적 바인딩 (static binding)

---

#### 가상 함수

```cpp
#include <iostream>

class Base {
 public:
  virtual void VirtualFunction() {
    std::cout << "Base virtual function" << std::endl;
  }
};

class Derived : public Base {
 public:
  void VirtualFunction() override {
    std::cout << "Derived virtual function" << std::endl;
  }
};

int main() {
  Base* ptr = new Derived();
  ptr->VirtualFunction();
  delete ptr;
}
```

* 컴파일 시점에서의 `ptr->VirtualFunction()` 문장 처리:
  * 가상 함수이므로 호출할 함수를 결정할 수 없음
    * `vptr` → `vtable` → 가상 테이블의 함수 포인터를 호출
    * `VirtualFunction`은 기반 클래스에서 0번째 인덱스에 존재
    * 가상 테이블의 0번째 인덱스의 함수 포인터를 호출하도록 처리
  * 동적 바인딩 (dynamic binding)

---

### 생성자와 소멸자

* 생성자는 가상화 불가
  * 생성자는 클래스마다 이름이 다름
    * 오버라이드 불가
  * 생성자를 가상화할 경우, 파생 클래스 형 객체 생성 시 생성자 호출 순서가 깨질 수 있음
  * **가상 포인터는 객체가 실체화되는 시점에 객체 내에 할당**
    * 가상 생성자는 가상 테이블을 참조할 수 없는 상태

* **소멸자는 가상화 가능**
  * 소멸자도 클래스마다 이름이 다르지만, 객체의 소멸 시점에 런타임이 자동으로 호출
  * 객체 소멸 시점에는 가상 포인터도 객체 내에 설정되어 있음
  * **클래스 설계 시 가상 함수를 사용할 경우 반드시 가상 소멸자를 사용해야 함**

---

#### 다형성을 사용하지 않는 상황에서의 소멸

* 기반 클래스 `Person`
  * `std::string` 형 데이터 멤버 `name`
* 파생 클래스 `Student`
  * 상속 받은 `std::string` 형 데이터 멤버 `name`과 `double` 형 데이터 멤버 `gpa`

![center](Figure_12_3.png)

* 각 클래스 형 객체가 스택 영역에 할당되었다가 소멸될 경우 소멸자에 의해 올바르게 자원 반환
  * 만약 파생 클래스 형 객체가 소멸되어야 한다면, 런타임 시스템에 의해 소멸자가 자동 호출됨
    * 파생 클래스 형 소멸자 호출 → 기반 클래스 형 소멸자 호출
  * 메모리 누수 (memory leak) 없음

---

#### 다형성을 사용하는 상황에서의 소멸

![center](Figure_12_4.png)

```cpp
Person* ptr = new Student();
// do something...
delete ptr;   // It does not deletes Student because ptr type is `Person*`
```

* 기반 클래스 형 포인터는 스택 영역, 파생 클래스 형 객체는 힙 영역 할당
* 기반 클래스 형 포인터가 파생 클래스 형 객체를 가리키는 상황에서, 포인터 삭제 시 문제 발생
  * 컴파일 시점에 `ptr`의 형을 확인해 해당 형의 소멸자 (`~Person()`)가 호출되도록 결정 
  * 힙 영역의 파생 클래스 객체는 **기반 클래스 멤버**만 소멸 (**메모리 누수**)

---

* 다형성을 사용하는 상황에서의 안전한 자원 해제 방법
  * 기반 클래스 형 포인터로 호환 객체를 동적 할당하여 가리키고 삭제하는 경우
  * 소멸자를 가상화하여 런타임 시스템이 소멸자를 호출할 때 **가상 테이블**을 참조하도록 해야 함

![center](Figure_12_5.png)

* 가상 소멸자 또한 가상 테이블에 인덱싱됨
  * 객체 소멸 시점에는 객체 내부에 가상 포인터가 존재하며, 가상 소멸자를 사용할 수 있음
  * 클래스마다 소멸자의 이름은 다르지만, 소멸 시점에 런타임 시스템에 의해 자동 호출됨
    * 소멸 시점에 호출되는 특별한 멤버 함수는 소멸자 뿐이므로, 이름은 중요하지 않음

---

### 가상 소멸자를 사용한 다형성 예시

* person.hpp

```cpp
#pragma once

#include <string>

class Person {
  std::string name_;

 public:
  explicit Person(const std::string& name);
  virtual ~Person();           // vtable[0]

  virtual void print() const;  // vtable[1]
};
```

---

* person.cc

```cpp
#include "person.hpp"

#include <iostream>
#include <string>

Person::Person(const std::string& nm) : name_(nm) {
  std::cout << "Person's ctor" << std::endl;
}

Person::~Person() { std::cout << "Person's dtor" << std::endl; }

void Person::print() const { std::cout << "Name: " << name_ << std::endl; }
```

---

* student.hpp

```cpp
#pragma once

#include <string>

#include "person.hpp"  

class Student : public Person {
  double gpa_;

 public:
  Student(const std::string& name, double gpa);

  // Note that a virtual destructor, despite having a different name, is a
  // special member function that is automatically called by the system at the
  // time of destruction. It is also managed in the virtual table (vtable) by an
  // index, just like other virtual functions.
  //
  // Class Student's vtable entry at index 0 is assigned to Student::~Student
  // during compile time
  ~Student() override;

  // Class Student's vtable entry at index 1 is assigned to Student::print
  // during compile time
  void print() const override;
};
```

---

* student.cc

```cpp
#include "student.hpp"  

#include <iostream>
#include <string>

Student::Student(const std::string& nm, double gp) : Person(nm), gpa_(gp) {
  std::cout << "Student's ctor" << std::endl;
}

Student::~Student() { std::cout << "Student's dtor" << std::endl; }

void Student::print() const {
  Person::print();
  std::cout << "GPA: " << gpa_ << std::endl;
}
```

---

* main.cc

```cpp
#include "student.hpp"  

int main() {
  Person* ptr = new Person("Lucie");
  std::cout << "Person Information";
  ptr->print();
  std::cout << std::endl;
  delete ptr;

  ptr = new Student("John", 3.9);
  std::cout << "Student Information";
  ptr->print();
  std::cout << std::endl;
  delete ptr;
  return 0;
}
```

---

### 배열에서의 다형성

![center](Figure_12_6.png)

* 여러 개의 호환 객체를 동시에 사용하여 다형성 사용
  * 이전 실습 코드에서 main.cc 부분만 배열을 사용하도록 수정

---

* main.cc

```cpp
#include <iostream>

#include "student.hpp"  

int main() {
  Person* ptr[4];
  ptr[0] = new Student("Joe", 3.7);
  ptr[1] = new Student("John", 3.9);
  ptr[2] = new Person("Bruce");
  ptr[3] = new Person("Sue");
  for (int i = 0; i < 4; ++i) {
    ptr[i]->print();
    std::cout << std::endl;
  }
  for (int i = 0; i < 4; ++i) delete ptr[i];
  return 0;
}
```

---

### 다른 객체지향 프로그래밍 언어에서의 다형성

* C++에서 다형성을 사용하기 위한 조건 3가지
  * 기반 클래스 형 포인터 혹은 기반 클래스 형 레퍼런스
  * 호환 객체
  * 가상 함수
* Java에서의 모든 메서드는 기본적으로 가상 메서드

#### 가상 함수의 비용

* 일반 함수는 컴파일 시점에 호출할 대상이 결정되어 비용이 발생하지 않음
* 가상 함수는 컴파일 시점에 호출할 대상을 결정하지 못하므로 비용 발생
  * `vptr` → `vtable` → 가상 테이블의 함수 포인터를 호출하도록 명령어 생성

---

## 정적 바인딩 (Static Binding)과 동적 바인딩 (Dynamic Binding)

* 함수는 두 개의 개체 (entities)로 구분되어 있음
  * 함수 호출과 함수 정의
  * 함수 호출은 실제로 함수가 실행되는 구체적인 행위
    * 각 호출은 전달인자 형태와 실행 시점에 따라 다른 결과를 초래할 수 있음
  * 함수 호출과 함수 정의는 서로 분리하여 관리
    * 함수 정의는 함수가 호출될 때 실행될 동작을 기술
    * 함수 호출은 해당 동작을 언제, 어떻게 실행할지 결정하는 별개의 역할 담당
* 바인딩은 함수 호출과 함수 정의를 어떻게 연관할 것인지를 의미
* 일반 함수는 하나의 정의를 갖고 있음
  * 함수 호출 시 대상이 되는 함수 정의가 하나이므로, 호출 대상이 명확함
* 가상 함수는 여러 개의 정의를 가질 수 있음
  * 함수 호출 시 대상이 되는 함수 정의가 여러개일 수 있으므로, **올바른 호출 대상을 찾아야 함**
* 바인딩은 런타임 시점에 발생하는 함수 호출이 정확히 어떤 함수 정의와 연관되는지 결정하는 과정

---

### 정적 바인딩

* 컴파일 시점에 함수 호출과 함수 정의 간 연관을 확정
  * 컴파일 시점 바인딩 (compile-time binding)
  * 조기 바인딩 (early binding)
* 함수 호출 대상이 일반 함수 (클래스의 멤버 함수나 전역 함수)인 경우
  * 컴파일 시점에 어떤 함수가 호출될지 명확하게 결정됨

```cpp
Person person;
person.print();   // Person::print()

Student student;
student.print();  // Student::print()
```

---

### 동적 바인딩

* 런타임 시점에 함수 호출과 함수 정의 간 연관을 확정
  * 런타임 시점 바인딩 (run-time binding)
  * 지연 바인딩 (late binding)
* 아래와 같은 경우는 컴파일 시점에 호출될 함수를 결정할 수 없음

```cpp
int user_input;
std::cin >> user_input;
Base* ptr;
if (user_input == 1)
  ptr = new Base();
else
  ptr = new Derived();
ptr->func();  // In this case, we don't know which `func` will be invoked on 
              // compile-time
```

* 컴파일 시점에 호출될 함수를 연관하지 못하는 경우는 동적 바인딩
* C++의 가상함수는 동적 바인딩 상황에서 올바른 함수를 호출할 수 있도록 **지원**
  * 가상 함수를 사용한 동적 바인딩은 런타임 시점의 객체 형에 따라 호출할 함수 결정
  * 가상 함수를 사용한 동적 바인딩은 다형성 (run-time polymorphism)

---

## 런타임 형 정보 (RTTI, Run-Time Type Information)

* 런타임 시점에 사용 중인 객체의 형을 확인해야 할 경우가 있음
* `<typeinfo>` 헤더를 사용하면 런타임 시점에 형과 관련한 유용한 정보를 얻을 수 있음
  * `type_info` 클래스가 정의되어 있음
  * `typeid` 연산자에 표현식을 전달해 `type_info` 형 객체를 만들 수 있음
    * `typeid(5)`, `typeid(5 + 3)`, `typeid(object_name)`
* `type_info` 형 객체에 지원되는 연산들

```text
t1 == t2      // Returns true if t1 and t2 are of the same type
t1 != t2      // Returns true if t1 and t2 are of different types
t1.name()     // Returns a C-type string (name of the t1)
t1.before(t2) // Returns true if t1 comes before t2
```

---

### 런타임 형 정보 예시

```cpp
#include <iostream>
#include <typeinfo>

class Animal {};
class Horse : public Animal {};

int main() {
  Animal animal;
  Horse horse;

  // Check if 'animal' and 'horse' are of the same type or not
  std::cout << "'animal' and 'horse' are of the same type: ";
  std::cout << std::boolalpha << (typeid(animal) == typeid(horse)) << std::endl;
  std::cout << "'animal' and 'horse' are of different types: ";
  std::cout << std::boolalpha << (typeid(animal) != typeid(horse)) << std::endl;

  // Get the type's name of instances
  std::cout << "Type name of animal: ";
  std::cout << typeid(animal).name() << std::endl;
  std::cout << "Type name of horse: ";
  std::cout << typeid(horse).name() << std::endl;
  return 0;
}
```

---

## 형 변환 (Type Casting)

* C++에서의 형 변환 방법은 4가지 (강한 타입 변환 규칙, explicit casting rules):
  1. `static_cast`
  2. `reinterpret_cast`
  3. `const_cast`
  4. `dynamic_cast`
* C++ 형 변환이 C 언어 형 변환보다 **안정적**
  * C++은 정적 타입 검사 (static type checking)를 수행 (type safety 언어)
    * C 언어에서 가능한 변환이 C++에서는 안될 수 있음
  * C++ 형 변환 사용 권장

---

### `static_cast`

* 컴파일 시점에 수행되는 형 변환
* **암묵적 변환**이 가능한 범위 내에서 형 변환이 가능한 경우 사용
  * **암묵적 변환**이 안 되는 상황에서 `static_cast` 사용 시 컴파일 오류
* **객체의 값이 변경됨** (메모리에 있는 객체의 비트 패턴이 수정됨)

```cpp
float f = 3.14;
int implicit_i = f;                    // OK, but it might be WARNING
int explicit_i = static_cast<int>(f);  // OK, and there's no warning!

int arr[] = {1, 2, 3};
float* c_cast_ptr = (float*) arr;                // OK, It's C-style casting
float* cpp_cast_ptr = static_cast<float*>(arr);  // Error, from 'int *' to
                                                 // 'float *' is not allowed
```

---

### `reinterpret_cast`

* 컴파일 시점에 수행되는 형 변환
* **객체의 값을 변경하지 않고** 해당 객체의 평가 방법만 변경
  * 주로 제네릭 포인터 (`void*`)의 평가 방법을 지정할 때 활용
  * 인접한 메모리 영역을 침범할 수 있음에 유의

```cpp
#include <iostream>

int main() {
  int i = 42, j = 100;
  std::cout
      << "Before, i(" << &i << "): " << i << ", j(" << &j << "): " << j
      << std::endl;  // Before, i(0x7ffda6a702f8): 42, j(0x7ffda6a702f4): 100

  // 0x7ffda6a702f4        0x7ffda6a702f8
  // [<--- j(4 bytes) --->][<--- i (4 bytes) --->]
  // ^
  // d_ptr (will use 8 bytes - j's area + i's area)
  double* d_ptr = reinterpret_cast<double*>(&j);
  *d_ptr = 123.456;
  std::cout << "After, i: " << i << ", j: " << j
            << std::endl;  // After, i: 1079958831, j: 446676599
  return 0;
}
```

---

### `const_cast`

* 컴파일 시점에 수행되는 형 변환
* 객체의 상수성 (`const`, constness) 또는 휘발성 (`volatile`, volatility) 제거 가능
* 주로 함수에서 일반 객체를 상수성 혹은 휘발성 매개변수로 받아 처리할 때 사용됨
* **아래의 경우들은 정의되지 않은 동작 (UB)**
  * 원본 객체가 상수성을 갖고 있을 때, `const_cast`를 사용해 상수성을 제거할 경우
  * 원본 객체가 휘발성을 갖고 있을 때, `const_cast`를 사용해 휘발성을 제거할 경우

```cpp
void foo(const int& i) {
  // We can't modify the `i` directly like this: i = 100;
  int& ref_i = const_cast<int&>(i);  // Safely remove constness using const_cast
                                     // to modify the parameter `i`
  ref_x = 100;  // Modify the value of `i` through `ref_i`, `i` is now 100
}

int main() {
  int i = 0;  // `i` is a normal object
  const int& ref_i = i;
  const_cast<int&>(ref_i) += 4;  // now the value of `i` is 4
  const int* ptr_i = &i;
  *const_cast<int*>(ptr_i) += 5;  // now the value of `i` is 9

  const int j = 0;  // `j` is a read-only object (constness)
  const int& ref_j = j;
  const_cast<int&>(ref_j) += 6;  // UB, we can't sure the value of `j`
  const int* ptr_j = &j;
  *const_cast<int*>(ptr_j) = 7;  // UB, we can't sure the value of `j`

  foo(i);  // now the value of `i` is 100
  return 0;
}
```

---

### `dynamic_cast`

* 런타임 시점에 **다운 캐스팅**을 명시적으로 수행할 때 사용

#### 다운 캐스팅 (Downcasting)

* 기반 클래스 형 포인터 또는 참조를 파생 클래스 형 포인터 또는 참조로 변환하는 작업
  * 기반 클래스 범위를 파생 클래스 범위로 확장해 파생 클래스 고유의 멤버에 접근 가능해짐
* 런타임 시점에 이루어지는 작업
* 주로 다형성을 사용하는 상황에서 특정 파생 클래스에 속하는 객체인지 확인할 때 사용
* 실패할 가능성이 있으므로 **명시적 형 변환**만을 허용

#### 업 캐스팅 (Upcasting)

* 파생 클래스 형 포인터 또는 참조를 기반 클래스 형 포인터 또는 참조로 변환하는 작업
* 컴파일 시점에 이루어지는 작업
* 주로 기반 클래스의 공통된 인터페이스 (e.g., 가상 함수)를 활용하는 다형성 구현에 사용
* 실패할 가능성이 없으므로 **암묵적 형 변환** 사용
  * 모든 파생 클래스는 기반 클래스의 내용을 담고 있음

---

```cpp
#include <iostream>

class Base {
 public:
  virtual ~Base() = default;  // Virtual destructor for RTTI support (vtable)
};

class Derived : public Base {};
class AnotherDerived : public Base {};

int main() {
  // Upcasting (Derived -> Base): Implicit upcasting, safe without explicit cast
  Derived derived_obj;
  Base* base_ptr = &derived_obj;
  std::cout << "Upcasting successful." << std::endl;

  // Successful downcasting (Base -> Derived)
  Derived* derived_ptr = dynamic_cast<Derived*>(base_ptr);
  std::cout << "Downcasting to Derived "
            << (derived_ptr ? "successful." : "failed.") << std::endl;

  // Failed downcasting (Base -> Derived)
  AnotherDerived another_obj;
  base_ptr = &another_obj;  // Base pointer now points to AnotherDerived object
  derived_ptr = dynamic_cast<Derived*>(base_ptr);  // Incorrect downcasting
  std::cout << "Downcasting to Derived "
            << (derived_ptr ? "successful." : "failed.") << std::endl;

  return 0;
}
```

---

## 추상 클래스 (Abstract Classes)

* 하나 이상의 순수 가상 함수를 포함하는 클래스
* 추상 클래스는 이를 상속 받는 모든 클래스에게 **특정 멤버 함수의 구현을 강제할 수 있음**

### 순수 가상 함수 (Pure Virtual Functions)

* 구현이 없는 가상 함수
* 순수 가상 함수는 파생 클래스에서 구현을 완료해야 하는 함수
  * 순수 가상 함수를 가진 클래스 형 객체는 **실체화할 수 없음**
  * 파생 클래스 내 상속 받은 순수 가상 함수가 존재할 경우 이를 반드시 구현해야 함
    * 구현하지 않는다면 컴파일 시 오류
* 가상 함수 선언 뒤에 0을 할당 (`= 0`)하면 이는 순수 가상 함수가 됨

```cpp
virtual double get_area(0) = 0;
virtual double get_perimeter(0) = 0;
```

---

## 인터페이스 (Interfaces)

* 클래스의 모든 멤버 함수가 순수 가상 함수인 경우
* 상속 받을 클래스에게 청사진 (blue print)를 제공하기 위한 용도
  * 인터페이스의 역할은 이를 상속 받는 클래스가 반드시 구현해야 할 속성을 강제함

![center](Figure_12_7.png)

---

### 클래스 다이어그램에서의 인터페이스

![center](Figure_12_Interface.png)

* 점선을 사용하여 화살표 표시
* 클래스 기호 내 `<<interface>>` 표시

---

### 인터페이스 예시

* shape.hpp

```cpp
#pragma once

class Shape {
  virtual bool is_valid() const = 0;

 public:
  virtual void print() const = 0;
  virtual double get_area() const = 0;
  virtual double get_perimeter() const = 0;
};
```

---

* circle.hpp

```cpp
#pragma once

#include "shape.hpp"

class Circle : public Shape {
  bool is_valid() const override;

  double radius_;

 public:
  explicit Circle(double radius);
  ~Circle() = default;

  void print() const override;
  double get_area() const override;
  double get_perimeter() const override;
};
```

---

* circle.cc

```cpp
#include "circle.hpp"

#include <cassert>
#include <iostream>

Circle::Circle(double r) : radius_(r) {
  if (!is_valid()) {
    std::cout << "Invalid circle!";
    assert(false);
  }
}

void Circle::print() const {
  std::cout << "Circle of radius : " << radius_ << std::endl;
}

double Circle::get_area() const { return 3.14 * radius_ * radius_; }

double Circle::get_perimeter() const { return 2 * 3.14 * radius_; }

bool Circle::is_valid() const { return radius_ > 0.0; }
```

---

* ellipse.hpp

```cpp
#pragma once

#include "shape.hpp"

class Ellipse : public Shape {
  bool is_valid() const override;

  double radius1_;
  double radius2_;

 public:
  Ellipse(double r1, double r2);
  ~Ellipse() = default;

  void print() const override;
  double get_area() const override;
  double get_perimeter() const override;
};
```

---

* ellipse.cc

```cpp
#include "ellipse.hpp"

#include <cassert>
#include <cmath>
#include <iostream>

Ellipse::Ellipse(double r1, double r2) : radius1_(r1), radius2_(r2) {
  if (!is_valid()) {
    std::cout << "Invalid ellipse!";
    assert(false);
  }
}

void Ellipse::print() const {
  std::cout << "Ellipse of radii : " << radius1_ << " X " << radius2_
            << std::endl;
}

double Ellipse::get_area() const { return 3.14 * radius1_ * radius2_; }

double Ellipse::get_perimeter() const {
  double temp = (radius1_ * radius1_ + radius2_ * radius2_) / 2.0;
  return 2 * 3.14 * std::sqrt(temp);
}

bool Ellipse::is_valid() const { return radius1_ > 0.0 && radius2_ > 0.0; }
```

---

* rectangle.hpp

```cpp
#pragma once

#include "shape.hpp"

class Rectangle : public Shape {
  bool is_valid() const override;

  double length_;
  double width_;

 public:
  Rectangle(double length, double width);
  ~Rectangle() = default;

  void print() const override;
  double get_area() const override;
  double get_perimeter() const override;
};
```

---

* rectangle.cc

```cpp
#include "rectangle.hpp"

#include <cassert>
#include <iostream>

Rectangle::Rectangle(double length, double width)
    : length_(length), width_(width) {
  if (!is_valid()) {
    std::cout << "Invalid rectangle!";
    assert(false);
  }
}

void Rectangle::print() const {
  std::cout << "Rectangle of " << length_ << " X " << width_ << std::endl;
}

double Rectangle::get_area() const { return length_ * width_; }

double Rectangle::get_perimeter() const { return 2 * (length_ + width_); }

bool Rectangle::is_valid() const { return length_ > 0.0 && width_ > 0.0; }
```

---

* square.hpp

```cpp
#pragma once

#include "shape.hpp"

class Square : public Shape {
  bool is_valid() const override;

  double side_;

 public:
  explicit Square(double side);
  ~Square() = default;

  void print() const override;
  double get_area() const override;
  double get_perimeter() const override;
};
```

---

* square.cc

```cpp
#include "square.hpp"

#include <cassert>
#include <iostream>

Square::Square(double s) : side_(s) {
  if (!is_valid()) {
    std::cout << "Invalid square!";
    assert(false);
  }
}

void Square::print() const {
  std::cout << "Square of size " << side_ << std::endl;
}

double Square::get_area() const { return side_ * side_; }

double Square::get_perimeter() const { return 4 * side_; }

bool Square::is_valid() const { return side_ > 0.0; }
```

---

* triangle.hpp

```cpp
#pragma once

#include "shape.hpp"

class Triangle : public Shape {
  bool is_valid() const override;

  double side1_;
  double side2_;
  double side3_;

 public:
  Triangle(double side1, double side2, double side3);
  ~Triangle() = default;

  void print() const override;
  double get_area() const override;
  double get_perimeter() const override;
};
```

---

* triangle.cc

```cpp
#include "triangle.hpp"

#include <cassert>
#include <cmath>
#include <iostream>

Triangle::Triangle(double s1, double s2, double s3)
    : side1_(s1), side2_(s2), side3_(s3) {
  if (!is_valid()) {
    std::cout << "Invalid triangle!";
    assert(false);
  }
}

void Triangle::print() const {
  std::cout << "Triangle of : " << side1_ << " X " << side2_ << " X " << side3_
            << std::endl;
}

double Triangle::get_area() const {
  double s = (side1_ + side2_ + side3_) / 2;
  return (std::sqrt(s * (s - side1_) * (s - side2_) * (s - side3_)));
}

double Triangle::get_perimeter() const { return side1_ + side2_ + side3_; }

bool Triangle::is_valid() const {
  bool fact1 = side1_ + side2_ > side3_;
  bool fact2 = side1_ + side3_ > side2_;
  bool fact3 = side2_ + side3_ > side1_;
  return fact1 && fact2 && fact3;
}
```

---

* main.cc

```cpp
#include <iostream>

#include "circle.hpp"
#include "ellipse.hpp"
#include "rectangle.hpp"
#include "square.hpp"
#include "triangle.hpp"

int main() {
  Square square(5);
  square.print();
  std::cout << "area: " << square.get_area() << std::endl;
  std::cout << "Perimeter: " << square.get_perimeter() << std::endl;
  std::cout << std::endl;

  Rectangle rectangle(5, 4);
  rectangle.print();
  std::cout << "area: " << rectangle.get_area() << std::endl;
  std::cout << "Perimeter: " << rectangle.get_perimeter() << std::endl;
  std::cout << std::endl;
  std::cout << "Information about a triangle" << std::endl;

  Triangle triangle(3, 4, 5);
  triangle.print();
  std::cout << "area: " << triangle.get_area() << std::endl;
  std::cout << "Perimeter: " << triangle.get_perimeter() << std::endl;
  std::cout << std::endl;
  std::cout << "Information about a circle" << std::endl;

  Circle circle(5);
  circle.print();
  std::cout << "area: " << circle.get_area() << std::endl;
  std::cout << "Perimeter: " << circle.get_perimeter() << std::endl;
  std::cout << std::endl;
  std::cout << "Information about an ellipse" << std::endl;

  Ellipse ellipse(5, 4);
  ellipse.print();
  std::cout << "area: " << ellipse.get_area() << std::endl;
  std::cout << "Perimeter: " << ellipse.get_perimeter() << std::endl;
  return 0;
}
```

---

## 다중 상속 (Multiple Inheritance) 시 문제점

![center](Figure_12_8.png)

* 상속 형태가 다이아몬드 상속 (diamond inheritance)일 경우 문제가 될 수 있음
  * **기반 클래스 내용이 여러 번 상속될 수 있음**
* 다이아몬드 상속 시 가상 기반 (virtual base) 또는 믹스인 클래스 (mixin class)를 사용할 것

---

### 가상 기반 (Virtual Base)

![center](Figure_12_9.png)

* `virtual` 키워드를 사용해 상속 받은 클래스의 실체화:
  1. 일반 상속 객체를 먼저 실체화한다.
  2. 가상 기반 객체 (subobject)를 실체화하되, **실체화될 객체에 하나만 포함되도록 실체화한다**.
* 가상 기반 사용 시 가상 기반 포인터 (`vbptr`)와 가상 기반 테이블 (`vbtable`)이 추가됨
* 가상 기반 포인터는 컴파일 시점에 고정된 인덱스를 사용할 수 있도록 처리됨

```cpp
class Person { /* ... skipped ... */ };
class Student: virtual public Person { /* ... skipped ... */ };
class Professor: virtual public Person { /* ... skipped ... */ };
class TA: public Student, public Professor { /* ... skipped ... */ };
```

---

#### 가상 기반 동작 방식

##### 설명을 위한 가정

Architecture: 16-bit addresses (2 bytes per address).
Pointer Size: 2 bytes.
Integer Size: 2 bytes.
Endianness: Little-endian (least significant byte first).

```cpp
class Base {
  int value = 0;

 public:
  virtual void FuncBase() { /* ... */ }
};
```

```text
Address   Content(Hex)   Description
0x1000    00 20          vptr_Base (points to 0x2000)
0x1002    00 00          int value (initialized to 0)
...
0x2000    00 30          Pointer to Base::FuncBase() (0x3000)
```

---

```cpp
class Derived1 : virtual public Base {
 public:
  void FuncBase() override { /* ... */ }
  virtual void FuncDerived1() { /* ... */ }
};
```

```text
Address   Content(Hex)   Description
0x1100    00 22          vptr_Derived1 (points to 0x2200)
0x1102    00 21          vbptr_Derived1 (points to vbtable at 0x2100)
                         -- Base Subobject within Derived1 --
0x1104    00 20          vptr_Base (points to 0x2000)
0x1106    00 00          int value (initialized to 0)
                         -- Base Subobject within Derived1 --
...
0x2000    00 30          Pointer to Base::FuncBase() (0x3000)
...
0x2100    02 00          Offset to Base subobject (+2 bytes)
...
0x2200    00 31          Pointer to Derived1::FuncBase() (0x3100)
0x2202    00 32          Pointer to Derived1::FuncDerived1() (0x3200)
```

---

```cpp
class Derived2 : virtual public Base {
 public:
  virtual void FuncDerived2() { /* ... */ }
};
```

```text
Address   Content(Hex)   Description
0x1200    00 24          vptr_Derived2 (points to 0x2400)
0x1202    00 23          vbptr_Derived2 (points to vbtable at 0x2300)
                         -- Base Subobject within Derived2 --
0x1204    00 20          vptr_Base (points to 0x2000)
0x1206    00 00          int value (initialized to 0)
                         -- Base Subobject within Derived2 --
...
0x2000    00 30          Pointer to Base::FuncBase() (0x3000)
...
0x2300    02 00          Offset to Base subobject (+2 bytes)
...
0x2400    00 30          Pointer to Base::FuncBase() (0x3000)
0x2402    00 33          Pointer to Derived2::FuncDerived2() (0x3300)
```

---

```cpp
class MostDerived : public Derived1, public Derived2 {
 public:
  void FuncBase() override { /* ... */ }
  void FuncDerived1() override { /* ... */ }
  virtual void FuncMostDerived() { /* ... */ }
};
```

```text
Address   Content(Hex)   Description
0x1300    00 25          vptr_Derived1 (points to 0x2500)
0x1302    00 27          vbptr_Derived1 (points to vbtable at 0x2700)
0x1304    00 26          vptr_Derived2 (points to 0x2600)
0x1306    00 28          vbptr_Derived2 (points to vbtable at 0x2800)
                         -- Shared Base Subobject within MostDerived --
0x1308    00 20          vptr_Base (points to 0x2000)
0x130A    00 00          int value (initialized to 0)
                         -- Shared Base Subobject within MostDerived --
...
0x2000    00 30          Pointer to Base::FuncBase() (0x3000)
...
0x2500    00 34          Pointer to MostDerived::FuncBase() (0x3400)
0x2502    00 35          Pointer to MostDerived::FuncDerived1() (0x3500)
...
0x2600    00 34          Pointer to MostDerived::FuncBase() (0x3400)
0x2602    00 33          Pointer to Derived2::FuncDerived2() (0x3300)
0x2604    00 36          Pointer to MostDerived::FuncMostDerived() (0x3600)
...
0x2700    06 00          Offset to Base subobject (+6 bytes)
...
0x2800    02 00          Offset to Base subobject (+2 bytes)
```

---

#### 가상 기반 예시

* person.hpp

```cpp
#pragma once

#include <string>

class Person {
 protected:
  std::string name_;

 public:
  explicit Person(const std::string& name);
  ~Person() = default;
  void print() const;
};
```

---

* person.cc

```cpp
#include "person.hpp"

#include <iostream>

Person::Person(const std::string& nm) : name_(nm) {}

void Person::print() const {
  std::cout << "Person" << std::endl;
  std::cout << "Name: " << name_ << std::endl << std::endl;
}
```

---

* student.hpp

```cpp
#pragma once

#include <string>

#include "person.hpp"

class Student : virtual public Person {
 protected:
  double gpa_;

 public:
  Student(const std::string& name, double gpa);
  ~Student() = default;
  void print() const;
};
```

---

* student.cc

```cpp
#include "student.hpp"

#include <cassert>
#include <iostream>

Student::Student(const std::string& name, double gp) : Person(name), gpa_(gp) {
  assert(gpa_ <= 4.0);
}

void Student::print() const {
  std::cout << "Student " << std::endl;
  std::cout << "Name: " << name_ << " ";
  std::cout << "GPA: " << gpa_ << std::endl << std::endl;
}
```

---

* professor.hpp

```cpp
#pragma once

#include <string>

#include "person.hpp"

class Professor : virtual public Person {
 protected:
  double salary_;

 public:
  Professor(const std::string& name, double salary);
  ~Professor() = default;
  void print() const;
};
```

---

* professor.cc

```cpp
#include "professor.hpp"

#include <iostream>

Professor::Professor(const std::string& nm, double sal)
    : Person(nm), salary_(sal) {}

void Professor::print() const {
  std::cout << "Professor " << std::endl;
  std::cout << "Name: " << name_ << " ";
  std::cout << "Salary: " << salary_ << std::endl << std::endl;
}
```

---

* ta.hpp

```cpp
#pragma once

#include <string>

#include "professor.hpp"
#include "student.hpp"

class TA : public Professor, public Student {
 public:
  TA(const std::string& name, double gpa, double sal);
  ~TA() = default;
  void print() const;
};
```

---

* ta.cc

```cpp
#include "ta.hpp"

#include <iostream>

TA::TA(const std::string& nm, double gp, double sal)
    : Person(nm), Professor(nm, sal), Student(nm, gp) {}

void TA::print() const {
  std::cout << "Teaching Assistance: " << std::endl;
  std::cout << "Name: " << name_ << " ";
  std::cout << "GPA: " << gpa_ << " ";
  std::cout << "Salary: " << salary_ << std::endl << std::endl;
}
```

---

* main.cc

```cpp
#include "ta.hpp"

int main() {
  Person person("John");
  person.print();
  Student student("Anne", 3.9);
  student.print();
  Professor professor("Lucie", 78000);
  professor.print();
  TA ta("George", 3.2, 20000);
  ta.print();
  return 0;
}
```

---

### 믹스인 클래스

* 인터페이스를 사용해 **주입할 속성**을 정의
* 속성 주입 목적의 인터페이스를 상속 받은 클래스는 주입 받은 속성을 구현해야만 실체화할 수 있음

![center](Figure_12_10.png)

---

#### 믹스인 클래스 예시

* stdtype.hpp

```cpp
#pragma once

class StdType {
 protected:
  double gpa_;

 public:
  virtual void print_gpa() const = 0;
};
```

---

* prftype.hpp

```cpp
#pragma once

class PrfType {
 protected:
  double salary_;

 public:
  virtual void print_salary() const = 0;
};
```

---

* person.hpp

```cpp
#pragma once

#include <string>

class Person {
 protected:
  std::string name_;

 public:
  explicit Person(const std::string& name);
  ~Person() = default;
  void print() const;
};
```

---

* person.cc

```cpp
#include "person.hpp"

#include <iostream>

Person::Person(const std::string& nm) : name_(nm) {}

void Person::print() const { std::cout << "Name: " << name_ << std::endl; }
```

---

* student.hpp

```cpp
#pragma once

#include <string>

#include "person.hpp"
#include "stdtype.hpp"

class Student : public Person, public StdType {
 public:
  Student(const std::string& name, double gpa);
  ~Student() = default;
  void print_gpa() const override;
  void print() const;
};
```

---

* student.cc

```cpp
#include "student.hpp"

#include <iomanip>
#include <iostream>

Student::Student(const std::string& name, double gp) : Person(name) {
  gpa_ = gp;
}

void Student::print_gpa() const {
  std::cout << "GPA: " << std::fixed << std::setprecision(2) << gpa_
            << std::endl;
}

void Student::print() const {
  Person::print();
  print_gpa();
}
```

---

* professor.hpp

```cpp
#pragma once

#include <string>

#include "person.hpp"
#include "prftype.hpp"

class Professor : public Person, public PrfType {
 public:
  Professor(const std::string& name, double salary);
  ~Professor() = default;
  void print_salary() const override;
  void print() const;
};
```

---

* professor.cc

```cpp
#include "professor.hpp"

#include <iomanip>
#include <iostream>

Professor::Professor(const std::string& nm, double sal) : Person(nm) {
  salary_ = sal;
}

void Professor::print_salary() const {
  std::cout << "Salary: ";
  std::cout << std::fixed << std::setprecision(2) << salary_ << std::endl;
}

void Professor::print() const {
  Person::print();
  print_salary();
}
```

---

* ta.hpp

```cpp
#pragma once

#include <string>

#include "person.hpp"
#include "prftype.hpp"
#include "stdtype.hpp"

class TA : public Person, public StdType, public PrfType {
 public:
  TA(const std::string& name, double gpa, double sal);
  ~TA() = default;
  void print_gpa() const override;
  void print_salary() const override;
  void print() const;
};
```

---

* ta.cc

```cpp
#include "ta.hpp"

#include <iomanip>
#include <iostream>

TA::TA(const std::string& nm, double gp, double sal) : Person(nm) {
  gpa_ = gp;
  salary_ = sal;
}

void TA::print_gpa() const { std::cout << "GPA: " << gpa_ << std::endl; }

void TA::print_salary() const {
  std::cout << "Salary: ";
  std::cout << std::fixed << std::setprecision(2) << salary_ << std::endl;
}

void TA::print() const {
  Person::print();
  print_gpa();
  print_salary();
}
```

---

* main.cc

```cpp
#include <iostream>

#include "professor.hpp"
#include "student.hpp"
#include "ta.hpp"

int main() {
  std::cout << "Information about person" << std::endl;
  Person per("John");
  per.print();
  std::cout << std::endl;

  std::cout << "Information about student" << std::endl;
  Student std("Linda", 3.9);
  std.print();
  std::cout << std::endl;

  std::cout << "Information about professor" << std::endl;
  Professor prf("George", 89000);
  prf.print();
  std::cout << std::endl;

  std::cout << "Information about teaching assistance " << std::endl;
  TA ta("Lucien", 3.8, 23000);
  ta.print();
  std::cout << std::endl;

  return 0;
}
```

---

## Appendix A. `vptr`의 유무에 따른 객체 크기 비교

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

## Appendix B. 가상 테이블의 포인터와 실제 멤버 함수 포인터 간 비교

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
