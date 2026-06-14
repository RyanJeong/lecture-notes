# 가상 메서드 호출 과정 상세 설명

C++에서 가상 함수가 호출되는 메커니즘을 자세히 이해하기 위한 예제와 설명입니다.

## 가상 함수 호출의 내부 동작

```cpp
#include <iostream>

class Base {
 public:
  virtual void function1() {
    std::cout << "Base::function1()" << std::endl;
  }
  
  virtual void function2() {
    std::cout << "Base::function2()" << std::endl;
  }
  
  virtual ~Base() {
    std::cout << "Base::~Base()" << std::endl;
  }
};

class Derived : public Base {
 public:
  void function1() override {
    std::cout << "Derived::function1()" << std::endl;
  }
  
  // function2는 오버라이드하지 않음
  
  ~Derived() override {
    std::cout << "Derived::~Derived()" << std::endl;
  }
};

int main() {
  Base* ptr = new Derived();
  ptr->function1();  // 동적 바인딩: Derived::function1() 호출
  ptr->function2();  // 동적 바인딩: Base::function2() 호출 (오버라이드되지 않았으므로)
  delete ptr;        // 동적 바인딩: Derived::~Derived() 호출 후 Base::~Base() 호출
  return 0;
}
```

## 내부 메커니즘 설명

### 1. 객체 생성 시 vptr 초기화

```
[Derived 객체의 메모리 레이아웃]
+------------------+
| vptr             |  <-- 가상 포인터: Derived 클래스의 vtable을 가리킴
+------------------+
| Base 클래스 멤버 |
+------------------+
| Derived 멤버들   |
+------------------+
```

### 2. vtable 구조

```text
[Base 클래스의 vtable]          [Derived 클래스의 vtable]
+------------------+            +------------------+
| &Base::function1 |            | &Derived::function1 | <-- 오버라이드된 함수
+------------------+            +------------------+
| &Base::function2 |            | &Base::function2 |    <-- 오버라이드되지 않은 함수
+------------------+            +------------------+
| &Base::~Base     |            | &Derived::~Derived |  <-- 오버라이드된 소멸자
+------------------+            +------------------+
```

### 3. 함수 호출 과정

1. `ptr->function1()` 호출 시:
   - `ptr`의 vptr를 통해 Derived 클래스의 vtable 접근
   - vtable[0]에 저장된 함수 포인터 (`&Derived::function1`) 참조
   - `Derived::function1()` 실행

2. `ptr->function2()` 호출 시:
   - `ptr`의 vptr를 통해 Derived 클래스의 vtable 접근
   - vtable[1]에 저장된 함수 포인터 (`&Base::function2`) 참조
   - `Base::function2()` 실행

3. `delete ptr` 실행 시:
   - `ptr`의 vptr를 통해 Derived 클래스의 vtable 접근
   - vtable[2]에 저장된 소멸자 함수 포인터 (`&Derived::~Derived`) 참조
   - `Derived::~Derived()` 실행 후 자동으로 `Base::~Base()` 호출

### 4. 핵심 포인트

- vtable은 컴파일 시간에 생성됨
- vptr는 객체 생성 시 초기화되고 올바른 vtable을 가리킴
- 함수 호출은 실행 시간에 vptr → vtable → 함수 포인터 순으로 참조
- 오버라이드하지 않은 함수는 기반 클래스의 구현을 vtable에 포함
- 이 메커니즘으로 정적 타입(포인터 타입)이 아닌 동적 타입(객체의 실제 타입)의 함수가 호출됨
