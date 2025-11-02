<!-- _class: lead -->
# 객체지향프로그래밍

## 제네릭 프로그래밍 (Generic Programming: Templates)

### [munseong.jeong@daejin.ac.kr](mailto:munseong.jeong@daejin.ac.kr)

---

## 함수 템플릿 (Function Template)

* 함수 내 일부 형을 컴파일 시점에 확정하는 기법
* 동일한 로직을 서로 다른 여러 형에 대해 중복 없이 구현할 수 있게 해주는 메커니즘

[//]: # (INCLUDE: ./cpp/09/snippet_template.hpp --from 4 --to 7 --no-comment)

* 함수 템플릿을 위한 템플릿 헤더 (template header)는 `template` 키워드를 사용
* 템플릿 헤더의 내용은 `<>` 괄호를 사용하며, **제네릭 형 (generic type)** 표현에 사용됨
* `T`, `X`, `Y`, `Z`는 템플릿 매개변수 (template parameter)이며, 컴파일 시점에 확정되는 형의 자리 표시자 (placeholder)
  * 템플릿 매개변수는 필요한 만큼 추가 가능
* 하나의 함수 템플릿은 여러 번 호출되어 여러 개의 함수 정의가 생성될 수 있음
  * 함수 템플릿은 호출 시점의 전달 인자와 반환 형을 바탕으로 적합한 형이 컴파일 시점에 결정됨
* 함수 템플릿을 사용한 프로그래밍을 다음과 같이 표현함:
  * 제네릭 프로그래밍 (generic programming)
  * 템플릿 프로그래밍 (template programming)

---

## 함수 템플릿 (Function Template) (Cont'd - 1)

### Using One Function Template

[//]: # (INCLUDE: ./cpp/09/template.cc)

---

## 함수 템플릿 (Function Template) (Cont'd - 2)

### 함수 템플릿과 함수 오버로딩 간 비교 (Comparison: Function Template vs Overloading)

[//]: # (INCLUDE: ./cpp/09/snippet_template.hpp --from 9 --to 13 --no-comment)

* 함수 템플릿은 **컴파일 시점에 호출 형태에 따라 제네릭 형을 확정한 함수 코드가 생성됨**

[//]: # (INCLUDE: ./cpp/09/snippet_template.hpp --from 15 --to 22 --no-comment)

* 함수 오버로딩은 컴파일 전에 **호출될 형태를 파악하여 필요한 만큼 코드로 직접 구현해야 함**

---

## 함수 템플릿 (Function Template) (Cont'd - 3)

### Swapping Two Values

[//]: # (INCLUDE: ./cpp/09/template_swap.cc)

---

## 템플릿 인스턴스화 (Template Instantiation)

![center](Figure_15_1.png)

* 함수 템플릿은 **템플릿 인스턴스화 없이는 사용할 수 없는 코드**
  * 컴파일 시점에 필요한 형태의 함수를 만들기 위해 존재하는 일종의 틀
  * 함수 템플릿은 미완성 상태이며, 구체적인 형 (concrete type)이 없으면 컴파일되지 않음
* 템플릿 인스턴스화는 컴파일 시점에 함수 템플릿의 형이 확정되어 실제로 실행 가능한 함수가 생성되는 것
  * e.g., `Smaller(12, 15)` 호출 → 컴파일러가 `int` 형 인스턴스 생성
  * e.g., `Smaller(3.14, 2.71)` 호출 → 컴파일러가 `double` 형 인스턴스 생성

---

## 함수 템플릿의 변형 (Variations)

### 자료형이 아닌 템플릿 매개변수 (Non-Type Template Parameter)

* 템플릿 매개변수에 **값을 명시적으로 표현**하는 형태
  * 값으로 사용 가능한 형 ([Template parameters and template arguments](https://en.cppreference.com/w/cpp/language/template_parameters)):
    * 정수 형 (`int`, `long`, `size_t`, etc.), 포인터 또는 참조, 열거형, `nullptr`
  * 값으로 사용 가능한 형이 제한적인 이유는 **컴파일 시점에 값이 확정되는 형태**만 사용 가능
  * **부동소수점 자료형이 허용되지 않음에 유의**
    * 부동소수점 수는 정밀도 제약이 존재해 값이 다르게 표현될 수 있음

[//]: # (INCLUDE: ./cpp/09/snippet_template.hpp --from 24 --to 34 --no-comment)

---

## 함수 템플릿의 변형 (Variations) (Cont'd - 1)

### Non-Type Template Parameter: Printing an Array

[//]: # (INCLUDE: ./cpp/09/printarray1.cc)

---

## 함수 템플릿의 변형 (Variations) (Cont'd - 2)

### 템플릿에서의 기본 매개변수 (Default Arguments for Template Parameters)

[//]: # (INCLUDE: ./cpp/09/snippet_template.hpp --from 36 --to 42 --no-comment)

* 템플릿 매개변수에 기본 값 또는 기본 자료형을 설정할 수 있음
* 템플릿 기본 매개변수는 오른쪽부터 채워져야 함
* 템플릿 기본 매개변수 값은 컴파일 시점에 값이 확정되는 형태만 사용 가능
  * 정수 형 (`int`, `long`, `size_t`, etc.), 포인터 또는 참조, 열거형, `nullptr`

---

## 함수 템플릿의 변형 (Variations) (Cont'd - 3)

### Default Arguments for Template Parameters: Printing an Array

[//]: # (INCLUDE: ./cpp/09/printarray2.cc)
