# C++ Value Categories

## glvalue, lvalue, xvalue, prvalue, rvalue

### **1. 값 범주 정의와 메모리**

#### **값 범주의 분류**

1. **glvalue** (generalized lvalue):
   - 메모리 주소를 참조할 수 있는 값.
   - **lvalue**와 **xvalue**의 상위 개념.
   - 예: 변수, 객체, 이동 가능한 값(`std::move(x)`).

2. **prvalue** (pure rvalue):
   - 순수 계산 결과로 메모리와 연결되지 않는 값.
   - 컴파일러가 필요할 때만 메모리를 할당하거나 레지스터에서 처리.
   - 예: 리터럴 값(`42`), 계산 결과(`x + y`).

3. **xvalue** (eXpiring value):
   - 이동 의미론에서 소유권을 이전하기 위해 설계된 값.
   - 기존 객체의 메모리를 참조하며, 더 이상 사용되지 않을 값으로 간주.
   - 예: `std::move(x)`, 함수가 반환하는 rvalue 레퍼런스.

4. **lvalue** (left value):
   - 이름을 가지며, 지속적으로 참조할 수 있는 값.
   - 메모리 주소를 가지며 읽기 및 쓰기가 가능.
   - 예: 변수(`int x`), 객체 참조(`std::string& ref`).

5. **rvalue** (right value):
   - 임시로 생성되는 값.
   - **prvalue**와 **xvalue**의 상위 개념.
   - 예: `42`, `x + y`, `std::move(x)`.

---

### **2. 이동 의미론과 값 범주**

#### **`std::move`와 xvalue**

- **`std::move(x)`**는 기존 객체 `x`를 **rvalue로 캐스팅**하여 xvalue를 생성합니다.
- xvalue는 기존 객체의 메모리 주소를 참조하지만, 소유권 이전을 통해 더 이상 의미 있는 상태로 간주되지 않습니다.

#### **xvalue와 소멸**

1. xvalue는 메모리에 존재하며, 기존 객체를 참조합니다.
2. **xvalue의 "expiring" 의미**:
   - "더 이상 논리적으로 유효하지 않은 상태"를 나타냅니다.
   - 객체는 여전히 메모리에 존재하지만, 이후의 사용은 의미가 없거나 정의되지 않은 동작을 초래할 수 있습니다.
3. xvalue를 참조한 객체는 스코프가 끝날 때 소멸됩니다.
   - 이는 스택 지역 객체와 동일한 생명 주기를 따릅니다.

#### **prvalue와 임시 객체**

- **prvalue**는 값 자체로 존재하며, 메모리를 직접 점유하지 않을 수 있습니다.
- 컴파일러는 필요할 때 prvalue를 임시 객체로 변환하여 rvalue 참조(`T&&`)에 바인딩합니다.
- 바인딩된 prvalue는 **표현식이 종료될 때 소멸**됩니다.

---

### **3. 이동 연산 후 객체의 상태**

#### **의미 있는 상태와 의미 없는 상태**

- **의미 있는 상태**: 객체가 유효한 값을 가지며, 프로그램에서 안전하게 사용할 수 있는 상태.
  - 예: 변수 초기화(`int x = 42;`), 이동되지 않은 상태의 객체.
- **의미 없는 상태**: 이동 연산 이후 객체가 더 이상 유효하지 않은 상태.
  - 예: `std::move(x)` 이후의 `x`는 의미 없는 상태로 간주됩니다.
  - 이동된 객체는 **다시 초기화하거나 소멸**할 수는 있지만, 그 값을 신뢰해서는 안 됩니다.

#### **C++ 표준에서 이동 후 객체의 상태 보장**

1. 이동된 객체는 **다시 초기화하거나 소멸할 수 있는 상태**로 남아 있어야 합니다.
2. 이동 후 객체를 사용하는 것은 정의되지 않은 동작을 초래할 수 있습니다.

---

### **4. 예제: 값 범주와 이동 의미론의 동작**

#### **값 범주 확인**

```cpp
#include <iostream>
#include <utility>

int main() {
    int x = 42; // x는 lvalue
    int&& rref1 = 42; // rref1은 prvalue를 참조 (임시 객체 생성)
    int&& rref2 = std::move(x); // rref2는 xvalue를 참조

    std::cout << "x (lvalue): " << x << std::endl;
    std::cout << "rref1 (prvalue): " << rref1 << std::endl;
    std::cout << "rref2 (xvalue): " << rref2 << std::endl;

    x = 100; // x의 값을 변경
    std::cout << "x (modified): " << x << std::endl;
    std::cout << "rref2 (xvalue reflects x): " << rref2 << std::endl;

    return 0;
}
```

#### **출력 (1)**

```text
x (lvalue): 42
rref1 (prvalue): 42
rref2 (xvalue): 42
x (modified): 100
rref2 (xvalue reflects x): 100
```

#### **분석 (1)**

1. **`x`**:
   - `x`는 lvalue이며 메모리에 존재.
   - `std::move(x)`로 캐스팅해도 기존 메모리 주소를 유지.
2. **`std::move(x)`**:
   - `x`를 rvalue로 캐스팅하여 xvalue로 만듦.
   - xvalue는 기존 객체 `x`를 참조하며, 이동 이후 객체는 의미 없는 상태로 간주.

---

### **5. 핵심 요약**

1. **값 범주의 정의**
   - **glvalue**: 객체의 메모리 주소를 참조할 수 있음.
     - lvalue와 xvalue를 포함.
   - **rvalue**: 임시 값으로 계산 결과만 존재.
     - prvalue와 xvalue를 포함.
   - **prvalue**: 계산 결과로만 존재하며 메모리 주소와 연결되지 않음.
   - **xvalue**: 이동 가능한 값으로, 기존 객체의 메모리 주소를 참조.

2. **이동 연산과 xvalue**
   - **`std::move(x)`는 xvalue를 생성**하며, 기존 객체의 소유권을 이전 가능 상태로 표시.
   - 이동 이후 객체는 의미 없는 상태로 간주되지만, 메모리에 여전히 존재.

3. **이동 이후의 객체**
   - 이동된 객체는 재초기화하거나 소멸 가능.
   - 이동 이후 객체를 사용하려는 시도는 정의되지 않은 동작을 초래할 수 있음.

4. **"의미 없는 상태"**
   - 이동 이후 객체는 논리적으로 더 이상 유효하지 않으며, 재사용 전에 반드시 초기화가 필요.

5. **xvalue의 "expiring" 의미**
   - xvalue는 소멸 가능한 상태를 나타내지만, 실제 소멸은 스코프 종료 시점에 이루어짐.

---

## `std::move(x)`와 xvalue

### **1. `std::move(x)`의 동작**

- **`std::move`의 본질**:
  - `std::move(x)`는 단순히 `x`를 rvalue로 캐스팅하여 **xvalue**로 평가되도록 만듭니다.
  - `std::move`는 `std::remove_reference<T>::type&&` 형태의 rvalue 참조를 반환합니다.
  - 이때 **`x` 자체는 여전히 lvalue입니다.**

#### **코드 분석**

```cpp
#include <iostream>
#include <type_traits>

int main() {
    int x = 42;                      // x는 lvalue
    std::cout << std::is_lvalue_reference<decltype(x)>::value << std::endl;  // true
    std::cout << std::is_rvalue_reference<decltype(x)>::value << std::endl;  // false

    int&& r = std::move(x);          // std::move(x)는 xvalue로 평가
    std::cout << std::is_lvalue_reference<decltype(std::move(x))>::value << std::endl;  // false
    std::cout << std::is_rvalue_reference<decltype(std::move(x))>::value << std::endl;  // true

    return 0;
}
```

#### **출력 (2)**

```text
1  // x는 lvalue
0  // x는 rvalue가 아님
0  // std::move(x)는 lvalue가 아님
1  // std::move(x)는 rvalue (xvalue)
```

#### **분석 (2)**

1. `x`는 여전히 lvalue입니다. `std::move`는 `x` 자체의 값 범주를 변경하지 않습니다.
2. `std::move(x)`는 `x`를 rvalue로 캐스팅하고, 이 캐스팅된 결과가 **xvalue**로 평가됩니다.
3. **결론적으로, `std::move`는 `x` 자체의 본질(lvalue)을 변경하지 않고, rvalue로 사용할 수 있도록 "표현(expression)"을 변경하는 역할만 합니다.**

---

### **2. `std::move`와 값 범주의 관계**

#### **lvalue에서 xvalue로의 변환이 아님**

- `std::move`는 lvalue인 `x`를 **xvalue로 바꿔버리는 것이 아니라**, lvalue를 rvalue로 캐스팅한 표현을 반환합니다.
- 캐스팅된 표현식인 `std::move(x)`는 **xvalue로 평가**됩니다.

#### **xvalue와 lvalue의 차이**

- **lvalue**: 이름을 가지며 지속적으로 참조 가능한 객체.
- **xvalue**: 이동을 위해 설계된 "소멸 가능한 값(expiring value)"로, lvalue와 다르게 더 이상 유효한 상태로 간주되지 않습니다.

---

### **3. 이동 의미론에서 xvalue로 평가되는 이유**

이동 의미론에서 xvalue가 중요한 이유는 다음과 같습니다:

1. **소유권 이전**: `std::move(x)`는 객체를 이동 대상으로 표시하여, 다른 객체가 해당 객체의 자원을 소유할 수 있도록 합니다.
2. **기존 객체를 안전하게 사용하지 않도록 표시**:
   - `std::move(x)` 이후에도 `x`는 여전히 메모리에 존재하지만, 의미 있는 상태로 간주되지 않습니다.
   - 이는 이동 연산의 설계 원칙에 따라 **기존 객체를 다시 사용하지 말라는 암묵적 신호**를 전달합니다.

---

### **4. 구체적인 예제**

#### 코드 (이동 의미론 예제)

```cpp
#include <iostream>
#include <string>
#include <utility>

int main() {
    std::string s1 = "Hello";
    std::string s2 = std::move(s1); // s1의 자원이 s2로 이동

    std::cout << "s1: " << s1 << std::endl; // s1은 비어 있는 상태
    std::cout << "s2: " << s2 << std::endl; // s2는 "Hello"

    return 0;
}
```

#### 출력 (3)

```text
s1:
s2: Hello
```

#### 분석 (3)

1. **`std::move(s1)`의 역할**:
   - `s1`은 여전히 lvalue입니다.
   - `std::move(s1)`는 rvalue로 캐스팅된 표현을 반환하며, 이 표현은 xvalue로 평가됩니다.
   - `s1`의 내부 자원이 `s2`로 이동하고, 이후 `s1`은 의미 없는 상태가 됩니다.
2. **`s1` 자체는 변경되지 않음**:
   - `std::move`는 `s1`의 값 범주를 변경하지 않으며, 이동 이후에도 여전히 lvalue로 간주됩니다.
   - 다만, 논리적으로 더 이상 의미 있는 값을 가지지 않으므로, 이동 후에는 `s1`을 다시 사용하지 않는 것이 권장됩니다.

---

### **5. "lvalue에서 xvalue로 바뀌는 것인가?"에 대한 답변**

**아니요, `std::move(x)`는 `x`를 xvalue로 "바꾸는 것"이 아닙니다.**

- `x`는 여전히 **lvalue**로 남아 있습니다.
- `std::move(x)`는 **`x`를 rvalue로 캐스팅하고, 이 캐스팅된 표현이 xvalue로 평가되는 것**입니다.
- 즉, `std::move`는 단지 `x`의 표현을 rvalue로 다루도록 만들 뿐이며, 객체의 본질적인 값 범주는 변경되지 않습니다.

---

### **6. 결론**

1. `std::move(x)`는 lvalue인 `x`를 **rvalue로 캐스팅**하여, **xvalue로 평가되는 표현식**을 생성합니다.
2. `x` 자체는 여전히 lvalue이며, 메모리에 그대로 존재합니다.
3. xvalue는 이동 대상(expiring value)으로, 이동 후 객체는 의미 있는 상태로 간주되지 않습니다.
4. `std::move`는 객체의 값 범주를 변경하지 않으며, 단지 객체를 이동 가능 상태로 표시하는 도구일 뿐입니다.
