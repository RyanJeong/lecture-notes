# 가상 소멸자의 중요성 - 예제 코드

```cpp
class Base {
 public:
  virtual void someFunction() { /* ... */ }
  // 가상 소멸자가 아닌 경우
  ~Base() { std::cout << "Base 소멸자 호출" << std::endl; }  
  
  // 올바른 방법: 가상 소멸자 선언
  // virtual ~Base() { std::cout << "Base 소멸자 호출" << std::endl; }
};

class Derived : public Base {
 private:
  int* data_;  // 동적 할당된 자원
 public:
  Derived() : data_(new int(100)) { /* ... */ }
  ~Derived() { 
    std::cout << "Derived 소멸자 호출" << std::endl;
    delete data_;  // 동적 할당된 자원 해제
  }
};

int main() {
  // 문제 상황:
  Base* ptr = new Derived();  // Derived 객체 생성
  // 사용 코드...
  delete ptr;  // Base::~Base()만 호출됨, Derived::~Derived()는 호출되지 않아 
               // data_가 해제되지 않음 (메모리 누수)
  
  return 0;
}
```

## 가상 소멸자를 사용한 올바른 해결책

```cpp
class Base {
 public:
  virtual void someFunction() { /* ... */ }
  // 가상 소멸자로 선언
  virtual ~Base() { std::cout << "Base 소멸자 호출" << std::endl; }
};

class Derived : public Base {
 private:
  int* data_;
 public:
  Derived() : data_(new int(100)) { /* ... */ }
  ~Derived() override { 
    std::cout << "Derived 소멸자 호출" << std::endl;
    delete data_;  // 이제 이 코드가 실행됨
  }
};

int main() {
  Base* ptr = new Derived();
  // 사용 코드...
  delete ptr;  // 이제 Derived::~Derived()가 먼저 호출되고, 
               // 그 후에 Base::~Base()가 호출됨
  return 0;
}
```

## 소멸자 호출 순서

1. 가상 소멸자인 경우:
   - `delete ptr;` 실행 시 `Derived::~Derived()` 호출
   - `Derived::~Derived()` 내부 코드 실행 완료 후 자동으로 `Base::~Base()` 호출

2. 비가상 소멸자인 경우:
   - `delete ptr;` 실행 시 포인터 타입인 `Base::~Base()`만 호출
   - `Derived::~Derived()`는 호출되지 않아 `data_` 메모리 누수 발생

## 가상 소멸자 필요성 핵심

- 클래스에 가상 함수가 하나라도 있다면 반드시 가상 소멸자 선언 필요
- 다형성이 사용되는 모든 기반 클래스는 가상 소멸자를 가져야 함
- 상속을 위한 기반 클래스라면 항상 가상 소멸자를 선언하는 것이 안전함
