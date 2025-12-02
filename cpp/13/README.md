<!-- _class: lead -->
# 객체지향프로그래밍

## 재귀와 자료구조

### [munseong.jeong@daejin.ac.kr](mailto:munseong.jeong@daejin.ac.kr)

---

## 재귀 (Recursion)

- 함수가 자기 자신을 호출하여 문제를 해결하는 방법

![h:400 center](Figure_Recursion.png)

---

## 재귀 (Recursion) (Cont'd - 1)

### 재귀 vs 반복문

#### 공통점

- 반복문과 재귀 모두 반복적인 작업 수행 시 활용
- **특정 조건이 만족될 때까지** 반복 실행

#### 차이점

- 재귀는 반복문보다 코드 형태가 **간결하고 직관적**임
  - 특히 수학적 문제를 표현할 때 재귀를 사용하면 간결하게 표현할 수 있음
- 재귀는 **매 호출마다 고유한 상태 (지역 변수)를 가질 수 있음**
  - 함수 호출마다 독립적인 함수 스택 프레임이 스택 메모리에 저장됨
    - 각 스택 프레임은 함수의 지역 변수, 함수 종료 시 복귀 주소, 호출된 함수의 매개변수 보관
  - **재귀 호출이 깊어질수록 메모리 사용량은 증가함**

---

## 재귀 (Recursion) (Cont'd - 2)

### 재귀의 기반 조건 (Base Case), 일반 조건 (General Case)

#### 기반 조건

- **재귀 호출을 중단하고 결과를 반환하는 조건**
- 일반적으로 문제의 가장 작은 단위를 해결하는 조건

#### 일반 조건

- 문제를 **더 작은 문제로 분할**하기 위해 자기 자신을 호출
- 재귀 호출이 깊어질수록 문제의 규모는 점점 축소되고, **결국 기반 조건을 만나게 됨**

---

## 재귀 (Recursion) (Cont'd - 3)

### 재귀로 구현한 피보나치 수열 (Fibonacci Number) 문제

![h:150 center](Figure_Fibonacci.png)

- 기반 조건: `fib(0) = 0, fib(1) = 1`
- 일반 조건: `fib(n) = fib(n - 1) + fib(n - 2)`

[//]: # (INCLUDE: ./cpp/13/fib1.cc --from 3 --to 5 --no-comment)

---

## 재귀 (Recursion) (Cont'd - 4)

![center](Figure_17_5.png)

---

## 재귀 (Recursion) (Cont'd - 5)

### 재귀의 한계점

[//]: # (INCLUDE: ./cpp/13/fact.cc --from 4 --to 12 --no-comment)

- 일반 재귀는 함수가 호출될 때마다 스택 영역에 함수 스택 프레임이 추가 할당됨
  - 일반 재귀로 작성한 팩토리얼 계산 함수를 호출 시 총 *n*개의 스택 프레임이 할당됨
- **일반 재귀의 이전 함수 호출은 현재 함수 호출에 의존**:
  - 재귀 호출은 **그 다음 재귀 호출의 결과값을 받을 때까지 스택 프레임을 유지해야 함**
- 재귀 깊이가 커질수록 스택 메모리 점유율도 높아짐에 따라 **스택 오버플로우**가 발생할 수 있음

---

## 재귀 (Recursion) (Cont'd - 6)

### 재귀 최적화: 꼬리 재귀 (Tail Recursion)

[//]: # (INCLUDE: ./cpp/13/fact.cc --from 14 --to 30 --no-comment)

- 꼬리 재귀는 **함수가 호출될 때마다 스택 영역의 이전 함수 스택 프레임을 재사용**
  - e.g., 꼬리 재귀로 작성한 팩토리얼 계산 함수 호출 시 하나의 스택 프레임만 할당됨

---

## 재귀 (Recursion) (Cont'd - 7)

### 꼬리 재귀 특징

- 꼬리 재귀는 컴파일 시점에 **하나의 스택 프레임을 재활용**하도록 재귀를 최적화한 형태
- 꼬리 재귀는 **그 다음 재귀 호출의 결과값을 받을 때까지 스택 프레임을 유지할 필요가 없음**
  - 꼬리 재귀는 그 다음 재귀 호출될 함수가 필요로 하는 모든 정보를 인자로 전달함
  - 꼬리 재귀 최적화 (TCO, Tail Call Optimization) 필수 구현 조건
- 재귀 깊이에 관계 없이 고정 크기 메모리를 사용하므로 **스택 오버플로우** 위험이 거의 없음

![h:250 center](Figure_Tail_Recursion.png)

---

## 재귀 (Recursion) (Cont'd - 8)

### 메모이제이션 (Memoization)

- 재귀 호출 시 **중복되는 부분 문제 (sub-problem)의 결과를 캐싱 (caching)하여 재사용**하는 최적화 기법
  - 동일한 계산을 억제하여 실행 시간을 획기적으로 단축
    - 피보나치 수열 `fib(5)` 계산 시 `fib(3)` 연산이 여러 번 필요함
    - 처음 계산한 `fib(3)`을 저장해 두고, **두 번째부터는 저장된 값을 즉시 사용하여 중복된 계산을 억제함**
  - 결과를 기록해 둘 **추가적인 메모리**가 필요 (space-time trade-off)
- 꼬리 재귀에서는 메모이제이션을 사용하지 않음
  - **꼬리 재귀는 누적된 결과를 인자로 계속 전달하며 변화함**
  - 함수 인자가 계속 달라짐에 따라, 이전에 저장해 둔 값을 다시 찾을 확률이 거의 없음

[//]: # (INCLUDE: ./cpp/13/fact.cc --from 32 --to 38 --no-comment)

---

## 재귀 (Recursion) (Cont'd - 9)

### 재귀 벤치마크

#### 일반 재귀

[//]: # (INCLUDE: ./cpp/13/fact.cc --from 44 --to 44 --no-comment)

#### 꼬리 재귀

[//]: # (INCLUDE: ./cpp/13/fact.cc --from 54 --to 54 --no-comment)

- 일반 재귀보다 메모리를 적게 사용하면서 더 빠르게 동작함

#### 일반 재귀 + 메모이제이션

[//]: # (INCLUDE: ./cpp/13/fact.cc --from 64 --to 64 --no-comment)

- 일반 재귀보다 메모리를 많이 사용하면서 더 빠르게 동작함

---

## 람다 함수 (Lambda Functions)

- 람다 함수는 **이름이 없는 익명 함수**로, 필요한 시점에 함수를 정의하여 즉시 사용 가능
- 특히 재귀나 함수형 프로그래밍에서 간결하고 효율적인 코드 작성을 가능하게 함

### 람다 함수의 기본 구조

[//]: # (INCLUDE: ./cpp/13/lambda.hpp --from 4 --to 6 --no-comment)

- `[capture_list]`: 람다 함수 외부의 변수를 람다 함수 내부에서 사용하기 위한 **캡쳐 리스트**
- `(parameters)`: 람다 함수가 받는 매개변수
- `-> return_type`: 람다 함수의 반환 타입 (생략 가능, 컴파일러가 자동 추론)
- `{ ... }`: 람다 함수의 본문

---

## 람다 함수 (Lambda Functions) (Cont'd - 1)

### 캡쳐 리스트 (Capture List)

- 람다 함수가 외부 변수에 접근하는 방식을 지정

| Capture Syntax | Description |
|---------|------|
| `[]` | No external variable captured |
| `[&]` | All external variables captured by **reference** (by reference) |
| `[=]` | All external variables captured by **value** (by value) |
| `[x, &y]` | `x` captured by value, `y` captured by reference (mixed capture) |
| `[=, &x]` | All variables except `x` captured by value, only `x` captured by reference |

---

## 람다 함수 (Lambda Functions) (Cont'd - 2)

### `auto` 키워드와 람다 함수

- `auto` 키워드는 컴파일러가 **변수의 타입을 자동으로 추론**하도록 지시
- 람다 함수는 고유한 타입을 가지므로, 변수에 저장할 때 `auto`를 사용하는 것이 편리

[//]: # (INCLUDE: ./cpp/13/lambda.cc)

- `auto` 사용 시 이점:
  - **람다 함수의 복잡한 타입을 명시할 필요가 없음**
  - 코드가 더 간결하고 가독성이 높음

---

## 람다 함수 (Lambda Functions) (Cont'd - 3)

### 람다 함수와 재귀 (Recursion With Lambda)

- 람다 함수는 `auto` 타입 추론 완료 전에는 **자기 참조 (self-reference)가 불가**
  - 재귀 호출을 하기 위해서 `std::function` 객체를 선언한 후, 이를 람다의 캡쳐 리스트에 포함해야 함
- `std::function`은 다양한 호출 객체를 담기 위해 타입 정보를 제거함 (type erasure)
  - 가상 호출 매커니즘과 유사한 간접 호출 (indirect call)이 발생하고 인라인 최적화가 제한됨

[//]: # (INCLUDE: ./cpp/13/lambda_rec.cc)

- `std::function<int64_t(int64_t)>`: 함수 타입을 명시적으로 정의 (`<R(Args...)>`)
- `[&fib]`: 람다 함수 `fib` 자신을 참조로 캡쳐하여 재귀 호출 가능

---

## 자료구조 (Data Structures)

- 데이터를 표현하는 방식 및 데이터 표현 구조를 유지하면서 수행할 수 있는 연산을 정의한 개념
- 자료구조와 알고리즘 (algorithms)은 상호보완적 관계
  - 자료구조: **데이터를 메모리에 효율적으로 저장하고 관리하는 방법**에 대해 습득
  - 알고리즘: **주어진 문제를 효율적으로 해결하기 위한 절차와 논리를 적용하는 방법**에 대해 습득

### 데이터의 표현 (Representation)

- 데이터가 메모리 상에 배치되는 방식
- e.g., 배열은 연속적인 메모리 블록 사용, 링크드 리스트는 포인터를 통해 노드 간 연결

### 제한된 연산 (Operations)

- 데이터의 구조를 유지하면서 삽입, 삭제, 탐색 등과 같은 동작 수행
- e.g., 스택은 LIFO (last in, first out)를 유지할 수 있는 `push`, `pop` 연산 허용

---

## 자료구조 (Data Structures) (Cont'd - 1)

### 객체 (Objects)

- 자료구조에서의 객체는 데이터를 구성하는 각각의 요소 (elements)를 의미
  - 자료구조 내 기본 데이터 단위
  - e.g., 배열의 각 원소, 링크드 리스트의 노드, 트리의 각 노드, etc.
- 객체는 다른 객체와 관계를 가질 수 있음
  - 객체 간 관계는 집합 (collections)으로 표현됨
  - e.g., 링크드 리스트의 노드는 다음 노드를 가리키는 포인터를 포함하여 **선형 관계**를 나타냄

### 객체 간 관계 - 집합 (Collections)

- 집합은 여러 개의 객체가 어떻게 연결되는가를 표현하는 개념

---

## 자료구조 (Data Structures) (Cont'd - 2)

### 선형 집합 (Linear Collection)

![center](Figure_18_1.png)

- 데이터가 메모리 상에서 선형적으로 연결된 구조 (e.g., 단일 링크드 리스트, 스택, 큐, etc.)

---

## 자료구조 (Data Structures) (Cont'd - 3)

### 비선형 집합 (Non-linear Collection)

![center](Figure_18_2.png)

- 데이터가 메모리 상에서 계층적 또는 복잡한 관계로 표현된 구조 (e.g., 이진 탐색 트리, etc.)

---

## 단일 링크드 리스트 (Singly Linked List)

- 선형 집합으로 표현한 자료구조이며, 각 객체는 노드 (nodes)로 표현
- 노드는 선형 순서 상 **다음 노드만 가리킬 수 있음**
  - 전방 탐색만 가능한 형태이며, 후방 탐색은 불가능

![center](Figure_18_3.png)

- 단일 링크드 리스트를 표현하기 위해 두 가지 (types) 사용
  - 단일 링크드 리스트 내 각 노드를 표현하는 `Node` 구조체 형
  - 단일 링크드 리스트의 시작을 가리키는 `List` 클래스 형

---

## 단일 링크드 리스트 (Singly Linked List) (Cont'd - 1)

### `Node` 구조체

![center](Figure_18_4.png)

[//]: # (INCLUDE: ./cpp/13/singly-linked-list/list.hpp --from 9 --to 12 --no-comment)

---

## 단일 링크드 리스트 (Singly Linked List) (Cont'd - 2)

### 삽입 (Insertion)

- 새로 삽입될 노드는 동적 할당하며, 이 노드의 주소는 `Node` 형 포인터 `add`가 가리킴

[//]: # (INCLUDE: ./cpp/13/singly-linked-list/list.hpp --from 40 --to 40 --no-comment)

- 삽입 연산 시 세 가지 경우가 있음:
  1. 단일 링크드 리스트의 맨 앞에 새 노드를 삽입하는 경우
  2. 단일 링크드 리스트의 중간에 새 노드를 삽입하는 경우
  3. 단일 링크드 리스트의 맨 마지막에 새 노드를 삽입하는 경우

---

## 단일 링크드 리스트 (Singly Linked List) (Cont'd - 3)

- 단일 링크드 리스트의 맨 앞에 새 노드를 삽입하는 경우:
  1. `add`가 가리키는 노드의 `next` 포인터를 `List` 형 객체의 `begin`으로 설정한다.
  2. `List` 형 객체의 `begin` 포인터를 `add`로 설정한다.

![center](Figure_18_6.png)

---

## 단일 링크드 리스트 (Singly Linked List) (Cont'd - 4)

- 단일 링크드 리스트의 중간에 새 노드를 삽입하는 경우:
  1. `Node` 형 포인터 `cur`를 단일 링크드 리스트 내 삽입될 위치의 **이전 노드** 주소로 설정한다.
  2. `add`가 가리키는 노드의 `next` 포인터를 `cur`가 가리키는 노드의 `next`로 설정한다.
  3. `cur`가 가리키는 노드의 `next` 포인터를 `add`로 설정한다.

![h:400 center](Figure_18_7.png)

---

## 단일 링크드 리스트 (Singly Linked List) (Cont'd - 5)

![center](Figure_18_7_Continued.png)

---

## 단일 링크드 리스트 (Singly Linked List) (Cont'd - 6)

- 단일 링크드 리스트의 맨 마지막에 새 노드를 삽입하는 경우 (중간 노드 삽입과 동일):
  1. `Node` 형 포인터 `cur`를 단일 링크드 리스트의 마지막 노드를 가리키도록 설정한다.
  2. `add`가 가리키는 노드의 `next` 포인터를 `cur`가 가리키는 노드의 `next`로 설정한다\
  (마지막 노드의 `next` 포인터는 항상 `nullptr`이므로, 새로 추가될 노드의 `next`도 `nullptr`이 됨).
  3. `cur`가 가리키는 노드의 `next` 포인터를 `add`로 설정한다.

---

## 단일 링크드 리스트 (Singly Linked List) (Cont'd - 7)

### 삭제 (Erasure)

- 삭제할 노드는 `Node` 형 포인터 `del`가 가리킨 뒤, 동적 해제함

[//]: # (INCLUDE: ./cpp/13/singly-linked-list/list.hpp --from 62 --to 62 --no-comment)

- 삭제 연산 시 세 가지 경우가 있음:
  1. 단일 링크드 리스트의 맨 앞 노드를 삭제하는 경우
  2. 단일 링크드 리스트의 중간 노드를 삭제하는 경우
  3. 단일 링크드 리스트의 맨 마지막 노드를 삭제하는 경우

---

## 단일 링크드 리스트 (Singly Linked List) (Cont'd - 8)

- 단일 링크드 리스트의 맨 앞 노드를 삭제하는 경우:
  1. `del` 포인터를 `List` 형 객체의 `begin`으로 설정한다.
  2. `List` 형 객체의 `begin` 포인터를 `begin`이 가리키는 노드의 `next`로 설정한다.
  3. `del` 포인터가 가리키는 동적 객체를 제거한다.

![center](Figure_18_8.png)

---

## 단일 링크드 리스트 (Singly Linked List) (Cont'd - 9)

- 단일 링크드 리스트의 중간 노드를 삭제하는 경우:
  1. `Node` 형 포인터 `cur`를 단일 링크드 리스트 내 삭제할 노드의 **이전 노드** 주소로 설정한다.
  2. `del` 포인터를 `cur`가 가리키는 노드의 `next` (삭제할 노드)로 설정한다.
  3. `cur`가 가리키는 노드의 `next` 포인터를 `del`이 가리키는 노드의 `next`로 설정한다.
  4. `del` 포인터가 가리키는 동적 객체를 제거한다.

![center](Figure_18_9.png)

---

## 단일 링크드 리스트 (Singly Linked List) (Cont'd - 10)

![center](Figure_18_9_Continued.png)

---

## 단일 링크드 리스트 (Singly Linked List) (Cont'd - 11)

- 단일 링크드 리스트의 맨 마지막 노드를 삭제하는 경우 (중간 노드 삭제와 동일):
  1. `Node` 형 포인터 `cur`를 단일 링크드 리스트 내 삭제할 노드의 **이전 노드** 주소로 설정한다.
  2. `del` 포인터를 `cur`가 가리키는 노드의 `next` (삭제할 노드이자 마지막 노드)로 설정한다.
  3. `cur`가 가리키는 노드의 `next` 포인터를 `del`이 가리키는 노드의 `next`로 설정한다\
  (마지막 노드의 `next` 포인터는 항상 `nullptr`이므로, 새로 추가될 노드의 `next`도 `nullptr`이 됨).
  4. `del` 포인터가 가리키는 동적 객체를 제거한다.

---

## 단일 링크드 리스트 (Singly Linked List) (Cont'd - 12)

### 소멸자

- `Node` 형 포인터 `del`를 `List` 형 객체의 `begin`으로 설정한 뒤, `begin`이 `nullptr`가 될 때까지 아래 과정 반복:
  1. `begin` 포인터를 `del` 포인터가 가리키는 노드의 `next`로 설정한다.
  2. `del` 포인터가 가리키는 동적 객체를 제거한다.

![h:370 center](Figure_18_5.png)

---

## 단일 링크드 리스트 (Singly Linked List) (Cont'd - 13)

- `list_exception.hpp`

[//]: # (INCLUDE: ./cpp/13/singly-linked-list/list_exception.hpp)

---

## 단일 링크드 리스트 (Singly Linked List) (Cont'd - 14)

- `list.hpp`

[//]: # (INCLUDE: ./cpp/13/singly-linked-list/list.hpp --to 13)

---

## 단일 링크드 리스트 (Singly Linked List) (Cont'd - 15)

[//]: # (INCLUDE: ./cpp/13/singly-linked-list/list.hpp --from 14 --to 35)

---

## 단일 링크드 리스트 (Singly Linked List) (Cont'd - 16)

[//]: # (INCLUDE: ./cpp/13/singly-linked-list/list.hpp --from 36 --to 53)

---

## 단일 링크드 리스트 (Singly Linked List) (Cont'd - 17)

[//]: # (INCLUDE: ./cpp/13/singly-linked-list/list.hpp --from 54 --to 72)

---

## 단일 링크드 리스트 (Singly Linked List) (Cont'd - 18)

[//]: # (INCLUDE: ./cpp/13/singly-linked-list/list.hpp --from 73)

---

## 단일 링크드 리스트 (Singly Linked List) (Cont'd - 19)

- `main.cc`

[//]: # (INCLUDE: ./cpp/13/singly-linked-list/main.cc --to 20)

---

## 단일 링크드 리스트 (Singly Linked List) (Cont'd - 20)

[//]: # (INCLUDE: ./cpp/13/singly-linked-list/main.cc --from 21)

---

## 스택 (Stack)

![center](Figure_18_10.png)

- 선형 집합으로 표현한 자료구조
- LIFO (last in, first out) 구조를 유지하기 위해 제약된 연산만 허용
  - 데이터의 추가와 삭제가 한쪽 끝 (스택의 탑, top)에서만 발생

---

## 스택 (Stack) (Cont'd - 1)

### 스택 연산

![center](Figure_18_11.png)

---

## 스택 (Stack) (Cont'd - 2)

### 단일 링크드 리스트 기반 스택 구현

![center](Figure_18_12.png)

- 스택 클래스는 단일 링크드 리스트를 **구성관계**로 구현할 수 있음
  - `List` 형 객체의 `begin` 포인터가 `Stack` 형 객체의 `top` 위치로 사용됨
- 단일 링크드 리스트를 기반으로 스택에 허용된 연산만 추가 구현하여 사용
  - LIFO를 유지하기 위해 `List`의 메서드를 래핑하여 허용된 연산만 제공

---

## 스택 (Stack) (Cont'd - 3)

- `stack.hpp`

[//]: # (INCLUDE: ./cpp/13/stack/stack.hpp)

---

## 스택 (Stack) (Cont'd - 4)

- `main.cc`

[//]: # (INCLUDE: ./cpp/13/stack/main.cc)

---

## 큐 (Queue)

![center](Figure_18_14.png)

- 선형 집합으로 표현한 자료구조
- FIFO (first in, first out) 구조를 유지하기 위해 제약된 연산만 허용
  - 데이터의 추가와 삭제가 양쪽 끝 (큐의 front에서 삭제, end에서 추가)에서 발생

---

## 큐 (Queue) (Cont'd - 1)

### 단일 링크드 리스트 기반 큐 구현

![center](Figure_18_15.png)

- 큐 클래스는 단일 링크드 리스트를 **구성관계**로 구현할 수 있음
  - `List` 형 객체의 `begin` 포인터가 `Queue` 형 객체의 `front` 위치로 사용됨
- 단일 링크드 리스트를 기반으로 큐에 허용된 연산만 추가 구현하여 사용
  - FIFO를 유지하기 위해 `List`의 메서드를 래핑하여 허용된 연산만 제공

---

## 큐 (Queue) (Cont'd - 2)

- `queue.hpp`

[//]: # (INCLUDE: ./cpp/13/queue/queue.hpp)

---

## 큐 (Queue) (Cont'd - 3)

- `main.cc`

[//]: # (INCLUDE: ./cpp/13/queue/main.cc --to 19)

---

## 큐 (Queue) (Cont'd - 4)

[//]: # (INCLUDE: ./cpp/13/queue/main.cc --from 20)

---

## 이진 탐색 트리 (Binary Search Tree)

![center](Figure_18_16.png)

- 비선형 집합으로 표현한 자료구조
- 이진 트리 (binary tree) 구조를 사용해 **탐색**을 효율적으로 수행
  - 각 노드가 최대 두 개의 노드와 연결될 수 있는 구조

---

## 이진 탐색 트리 (Binary Search Tree) (Cont'd - 1)

### 이진 탐색 트리에서의 순회 (Traversals)

![center](Figure_Binary_Search_Tree.png)

- 이진 트리에서의 각 노드를 탐색하는 방법
- 각 노드는 **한 번만** 처리됨
- 이진 탐색 트리는 세 개의 순회 방법을 사용:
  1. Pre-order: 루트 노드 → 왼쪽 서브트리 → 오른쪽 서브트리 (4, 2, 1, 3, 6, 5, 7)
  2. In-order: 왼쪽 서브트리 → 루트 노드 → 오른쪽 서브트리 (1, 2, 3, 4, 5, 6, 7)
  3. Post-order: 왼쪽 서브트리 → 오른쪽 서브트리 → 루트 노드 (1, 3, 2, 5, 7, 6, 4)

---

## 이진 탐색 트리 (Binary Search Tree) (Cont'd - 2)

### 이진 탐색 트리에서의 순회 (Traversals) - Pre-Order

- Pre-order: 루트 노드 → 왼쪽 서브트리 → 오른쪽 서브트리

[//]: # (INCLUDE: ./cpp/13/binary_search_tree/binary_search_tree.hpp --from 54 --to 60 --no-comment)

---

## 이진 탐색 트리 (Binary Search Tree) (Cont'd - 3)

### 이진 탐색 트리에서의 순회 (Traversals) - In-Order

- In-order: 왼쪽 서브트리 → 루트 노드 → 오른쪽 서브트리

[//]: # (INCLUDE: ./cpp/13/binary_search_tree/binary_search_tree.hpp --from 62 --to 68 --no-comment)

---

## 이진 탐색 트리 (Binary Search Tree) (Cont'd - 4)

### 이진 탐색 트리에서의 순회 (Traversals) - Post-Order

- Post-order: 왼쪽 서브트리 → 오른쪽 서브트리 → 루트 노드

[//]: # (INCLUDE: ./cpp/13/binary_search_tree/binary_search_tree.hpp --from 70 --to 76 --no-comment)

---

## 이진 탐색 트리 (Binary Search Tree) (Cont'd - 5)

### 이진 탐색 트리에서의 삽입

- Pre-order 순회 방법을 사용:
  1. 트리가 비어있을 때 (트리 내 노드가 존재하지 않을 때), 삽입할 값을 루트 노드로 삽입한다.
  2. 삽입할 값이 루트 노드의 값보다 작다면 왼쪽 서브트리로 이동한다.
  3. 삽입할 값이 루트 노드의 값보다 크다면 오른쪽 서브트리로 이동한다.

[//]: # (INCLUDE: ./cpp/13/binary_search_tree/binary_search_tree.hpp --from 27 --to 35 --no-comment)

---

## 이진 탐색 트리 (Binary Search Tree) (Cont'd - 6)

### 이진 탐색 트리에서의 소멸

- Post-order 순회 방법을 사용:
  1. 왼쪽 서브트리를 소멸한다.
  2. 오른쪽 서브트리를 소멸한다.
  3. 루트 노드를 소멸한다.

[//]: # (INCLUDE: ./cpp/13/binary_search_tree/binary_search_tree.hpp --from 37 --to 43 --no-comment)

---

## 이진 탐색 트리 (Binary Search Tree) (Cont'd - 7)

- `binary_search_tree_exception.hpp`

[//]: # (INCLUDE: ./cpp/13/binary_search_tree/binary_search_tree_exception.hpp)

---

## 이진 탐색 트리 (Binary Search Tree) (Cont'd - 8)

- `binary_search_tree.hpp`

[//]: # (INCLUDE: ./cpp/13/binary_search_tree/binary_search_tree.hpp --to 14)
---

## 이진 탐색 트리 (Binary Search Tree) (Cont'd - 9)

[//]: # (INCLUDE: ./cpp/13/binary_search_tree/binary_search_tree.hpp --from 15 --to 36)
---

## 이진 탐색 트리 (Binary Search Tree) (Cont'd - 10)

[//]: # (INCLUDE: ./cpp/13/binary_search_tree/binary_search_tree.hpp --from 37 --to 53)
---

## 이진 탐색 트리 (Binary Search Tree) (Cont'd - 11)

[//]: # (INCLUDE: ./cpp/13/binary_search_tree/binary_search_tree.hpp --from 54 --to 69)
---

## 이진 탐색 트리 (Binary Search Tree) (Cont'd - 12)

[//]: # (INCLUDE: ./cpp/13/binary_search_tree/binary_search_tree.hpp --from 70 --to 90)
---

## 이진 탐색 트리 (Binary Search Tree) (Cont'd - 13)

[//]: # (INCLUDE: ./cpp/13/binary_search_tree/binary_search_tree.hpp --from 91)

---

## 이진 탐색 트리 (Binary Search Tree) (Cont'd - 14)

- `main.cc`

[//]: # (INCLUDE: ./cpp/13/binary_search_tree/main.cc --to 19)
---

## 이진 탐색 트리 (Binary Search Tree) (Cont'd - 15)

[//]: # (INCLUDE: ./cpp/13/binary_search_tree/main.cc --from 20)
