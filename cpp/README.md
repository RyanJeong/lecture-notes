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

