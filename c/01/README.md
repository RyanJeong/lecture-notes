---
marp: true
---

# A Tutorial Introduction

## Goals of This Chapter

### 전체적으로 C 언어 훑어보기

- C 언어 코드를 보면서 C 언어의 필수 기능들 살펴보기

### 세부 사항, 규칙, 예외 등은 이 장에서 다루지 않음

- C 언어의 기초적인 내용에 집중
  - Variables and constants
  - Arithmetic
  - Control flow
  - Functions
  - The rudiments of input and output
- 다음 내용은 다루지 않음
  - Pointers, structures, most of C's rich set of operators, several control-flow statements, and the standard library, ...
- C 언어의 기초적인 내용만을 소개함에 따라 코드가 간결하지 않거나 깔끔하지 못할 수 있음 (**drawbacks**)

---

## 프로그램 (Programs)

- 기계어 명령들의 집합으로, 각 명령어는 매우 원시적인 수준의 연산 (extremely primitive)을 수행
  - e.g., Adding two numbers, testing if a number is equal to zero, etc.
- 인터넷 브라우저 크롬 (Chrome)은 약 1.1억 개의 원시적인 명령어들의 집합

![center h:450](image.png)

---

## 프로그램 동작 방식

- 프로그램을 실행하면 프로그램은 운영체제 로더 (Loader)에 의해 메모리에 적재됨
  - Loader: the part of an operating system that is responsible for **loading programs and libraries**

![center h:200](image-1.png)

- 메모리에 적재된 프로그램은 CPU에 의해 처리됨
  > CPU runs a fetch / execute cycle.
  - 다음 두 과정 반복
    1. RAM에 복사된 프로그램으로부터 명령어 하나를 CPU로 가져옴
    2. CPU로 가져온 명령어 처리, e.g. do the addition

![center h:150](image-2.png)

---

## 프로그램 동작 방식 (Cont'd)

![center h:500](image-3.png)

---

## 프로그램 생성 과정 - 컴파일 (Compilations)

- CPU는 기계어 (machine code)를 처리하는 장치
- 고급 언어 (e.g., C, C++, etc.)로 작성된 코드는 CPU가 이해할 수 없음
- **컴파일러는 컴파일 과정을 통해 고급 언어를 CPU가 이해할 수 있는 기계어 (프로그램)로 변환함**

![center h:150](image-4.png)

### 컴파일 과정

![center](image-5.png)

---

## Getting Started

> **The only way to learn a new programming language is by writing programs in it.**\
Brian W. Kernighan, Dennis Ritchie (1988). "C Programming Language (ed. Prentice Hall, 1988)"

### `Hello, World` 출력 프로그램

[//]: # (INCLUDE: ./c/01/01_1.c)

---

## Getting Started (Cont'd - 1)

### `#include` 명령 (전처리 명령, Preprocessor Instruction)

[//]: # (INCLUDE: ./c/01/getting_started_1_ignore.c)

- 보통 코드의 맨 윗부분에 위치
- 프로그램 실행에 필요한 기능들을 프로그램 내에 포함시킴
- e.g., `stdio.h`: 표준 입출력 (`stdio`: standard inputs and outputs) 관련 내용을 프로그램에 포함시킴

### `main` 함수

[//]: # (INCLUDE: ./c/01/getting_started_2_ignore.c)

- **프로그램의 시작점**
  - 프로그램 실행은 `main` 함수를 호출하는 것
- 함수 내용은 중괄호 (`{`, `}`)로 둘러싸여 있음
- 위의 `main` 함수는 두 문장 (statements, `printf` 문, `return` 문)을 포함하는 함수
- **함수 내 모든 문장의 마지막에는 반드시 세미콜론 (`;`)을 사용해야 함**

---

## Getting Started (Cont'd - 2)

### `return` 문 (반환문)

[//]: # (INCLUDE: ./c/01/getting_started_3_ignore.c)

- 함수를 종료하는 문장
  - `main` 함수의 종료는 프로그램의 종료를 의미
- `return` 다음에 등장하는 표현식 (expressions)은 함수 호출 측 (caller)으로 전달됨
  - 터미널에서 프로그램을 실행한 경우, `main` 함수의 `return` 값 (반환값)은 터미널로 전달

```bash
$ ./hello
Hello, World  # return 0; Terminal will receive it
$ echo $?
0
```

### `printf` 문

[//]: # (INCLUDE: ./c/01/getting_started_4_ignore.c)

- `printf` 함수를 호출하는 문장
- `stdio.h` 헤더 파일 필요
- 전달인자 (arguments, `"Hello, World\n"`)를 콘솔 화면에 출력하는 역할 수행

---

## Getting Started (Cont'd - 3)

### 문자열 (Strings)

[//]: # (INCLUDE: ./c/01/getting_started_5_ignore.c)

- 큰따옴표 (`"`)를 사용해 표현한 값
- 여러 문자들을 묶은 값
- 문자열 (character string) 또는 문자열 상수 (string constant)라고 부름

### 이스케이프 시퀀스 (Escape Sequence)

[//]: # (INCLUDE: ./c/01/getting_started_6_ignore.c)

- 백슬래시 (`\`) 뒤에 한 문자 또는 숫자 조합이 오는 문자 조합
- **두 개 이상의 문자 조합이지만, 한 문자 (a character)로 간주**
  - 작은따옴표 (`'`)를 사용해 표현한 값은 문자 하나를 의미
- 데이터가 아닌 특수한 명령을 수행하는 용도로 사용
  - e.g., `'\n'`: 터미널로 데이터 출력 시 한 줄 개행 (newline)

---

## Getting Started (Cont'd - 4)

### `printf` 문의 다양한 형태

[//]: # (INCLUDE: ./c/01/01_2.c)

---

## Variables and Arithmetic Expressions

### 화씨 온도를 섭씨 온도로 변환하는 프로그램

- 공식은 다음과 같음:

$$C^\circ = \frac{5}{9} \times (F^\circ - 32)$$

[//]: # (INCLUDE: ./c/01/02_1.c)

---

## Variables and Arithmetic Expressions (Cont'd - 1)

### 주석 (Comments)

- 프로그램 내에 메모를 하거나 해당 프로그램을 설명하는 용도
- 프로그램의 구조와 중요 정보를 코드를 읽는 사람에게 전달할 수 있음
- `/*  */` 사이에 위치한 모든 내용은 **전처리기**에 의해 제거
- 프로그램 소스코드 내 공백 문자 (a blank, tab, or newline)가 등장할 수 있는 위치에 사용 가능

[//]: # (INCLUDE: ./c/01/02_2.c)

---

## Variables and Arithmetic Expressions (Cont'd - 2)

### 변수 (Variables)

[//]: # (INCLUDE: ./c/01/variables_and_arithmetic_expressions_1_ignore.c)

- 프로그램 내에서 데이터를 보관하는 용도
- **모든 변수는 반드시 사용 전에 선언 (declarations)되어야 함**
- 변수 선언은 사용할 형 (types)과 이름의 조합으로 구성:

[//]: # (INCLUDE: ./c/01/variables_and_arithmetic_expressions_2_ignore.c)

- 형 종류는 아래와 같음:

```text
char   → character - a single byte
short  → short ingeger
int    → integer
long   → long integer
float  → single-precision floating point
double → double-precision floating point
```

---

## Variables and Arithmetic Expressions (Cont'd - 3)

### 대입문 (Assignment Statements)

[//]: # (INCLUDE: ./c/01/variables_and_arithmetic_expressions_4_ignore.c)

- 변수에 값을 대입 (assignments)할 때 사용하는 문장
  - **상수에는 값을 대입할 수 없음**
- 대입 연산자 (`=`)를 사용해 변수에 값을 전달할 수 있음

### `while` 반복문

[//]: # (INCLUDE: ./c/01/variables_and_arithmetic_expressions_5_ignore.c)

- `while` 키워드 다음에 등장하는 조건 (conditions)을 만족하는 동안 중괄호 내 각 문장들을 여러 번 반복할 수 있음

---

## Variables and Arithmetic Expressions (Cont'd - 4)

### 산술 표현식 (Arithmetic Expressions)

[//]: # (INCLUDE: ./c/01/variables_and_arithmetic_expressions_6_ignore.c)

- 산술 연산자를 사용하는 표현식

| Operator | Description    | Example   | Result |
|----------|--------------|-----------|--------|
| `+`      | Addition       | `5 + 3` | `8`    |
| `-`      | Subtraction    | `5 - 3` | `2`    |
| `*`      | Multiplication | `5 * 3` | `15`   |
| `/`      | Division       | `6 / 3` | `2`    |

#### 산술 연산자 사용 시 주의사항

[//]: # (INCLUDE: ./c/01/variables_and_arithmetic_expressions_7_ignore.c)

- 2번 문장의 `5 / 9` 표현은 두 피연산자가 **정수** 값
- **정수형 나눗셈에서의 나머지는 버려지므로, `5 / 9`의 값은 0으로 평가됨**

---

## Variables and Arithmetic Expressions (Cont'd - 5)

### 형식에 따른 출력 (Formatted Output)

[//]: # (INCLUDE: ./c/01/variables_and_arithmetic_expressions_8_ignore.c)

- `printf` 함수의 첫 번째 전달인자는 화면에 실제로 출력되는 문자열 (형식 문자열, format string)
- `printf` 함수는 출력을 형식화하는 기능을 지원함
- 형식 문자열이 변환 지정자 (conversion specifiers)를 포함하면, 뒤따르는 전달인자와 조합하여 형식화된 출력 가능
  - 변환 지정자는 `%` 기호로 시작하는 연속된 문자열
  - **형식 문자열 내 변환 지정자의 수와 뒤따르는 전달인자의 수는 일치해야 함**

[//]: # (INCLUDE: ./c/01/variables_and_arithmetic_expressions_9_ignore.c)

- `%d`는 대응되는 전달인자를 **정수** 값으로 출력
- `%f`는 대응되는 전달인자를 **실수** 값으로 출력

---

## Variables and Arithmetic Expressions (Cont'd - 6)

### 출력 형식이 개선된 화씨 온도를 섭씨 온도로 변환하는 프로그램

[//]: # (INCLUDE: ./c/01/03.c)

- `%3d`는 3칸 공간을 확보한 뒤 이에 대응되는 전달인자를 정수 값으로 출력
- `%6d`는 6칸 공간을 확보한 뒤 이에 대응되는 전달인자를 정수 값으로 출력

---

## Variables and Arithmetic Expressions (Cont'd - 7)

### 실수 값을 사용한 화씨 온도를 섭씨 온도로 변환하는 프로그램

[//]: # (INCLUDE: ./c/01/04.c)

- 한 표현에 실수 값과 정수 값이 같이 사용될 경우, **정수 값은 실수 값으로 처리됨**

[//]: # (INCLUDE: ./c/01/variables_and_arithmetic_expressions_A_ignore.c)

---

## 프로그램 작성 요령

### 전체 코드가 구조적이어야 함

- 들여쓰기는 프로그램의 논리적 구조를 강조함
- 들여쓰기, 개행, 빈칸 등을 적절히 사용하면, 사람이 프로그램 코드를 읽을 때 더 편하게 읽을 수 있음
- 컴파일러는 들여쓰기, 빈칸 등 논리적인 구조를 상관하지 않음
  - 문법 구조만 확인하여 컴파일
- **프로그램 코드는 결국 사람이 작성하고 읽음**
  - 가독성을 중시할 것

### 한 줄엔 하나의 문장만 작성할 것

```c
/* VERY poor readability */
int lower, upper, step; lower = 0; upper = 300; step = 20;
```

```c
/* Principle: One statement per line */

/* variables */
int lower, upper, step;

/* initializations */
lower = 0;   /* lower limit of temperature table */
upper = 300; /* upper limit */
step = 20;   /* step size */
```

---

## 프로그램 작성 요령 (Cont'd)

### 연산자 양 옆에 빈칸 사용

- 연산자와 피연산자 간 관계를 명확히 하여 가독성을 높이기 위함

```c
celsius=5*(fahr-32)/9;
```

```c
celsius = 5 * (fahr - 32) / 9;
```

### 일관성 (Consistency)을 유지할 것

```c
int i = 0;
while (i < 10) { ++i; } /* Single-line while loop */
while (i >= 0) {        /* Multi-line while loop */
    --i;
}
```

---

## The for Statement

### `for` 반복문을 사용한 화씨 온도를 섭씨 온도로 변환하는 프로그램

[//]: # (INCLUDE: ./c/01/05.c)

### `for` 반복문
  
```c
for (/* 1: initialization */ ; /* 2: condition */ ; /* 3: updation */) {
    /* body of the loop (statements to be executed) */
}
```

- 세 개의 표현식 사용
  - 초기화 (1번 표현식)는 반복문 시작 시점에 한 번만 실행됨
  - 이후 **조건 (2번 표현식) → 반복문 본문 (loop body) 실행 → 갱신 (3번 표현식)** 과정을 반복함
  - 조건이 더 이상 만족되지 않을 때 반복문 종료

---

## The for Statement (Cont'd - 1)

### 기호 상수 (Symbolic Constants)

- 코드 내 정수형 상수를 사용했으나, 주석 등 설명이 부족해 코드를 명확히 이해하기 어려움

```c
for (fahr = 0; fahr <= 300; fahr = fahr + 20)
    printf("%3d %6.1f\n", fahr, (5.0 / 9.0) * (fahr - 32));
```

- `#define` 전처리문을 활용하면 기호 상수를 사용할 수 있음

```c
#define NAME REPLACEMENT_TEXT
```

- `NAME` 자리에는 상수를 설명할 수 있는 의미 있는 이름을 표현
- `REPLACEMENT_TEXT` 자리에는 상수 값을 표현
- **전처리기는 코드를 분석하면서 `NAME`을 발견하면 `REPLACEMENT_TEXT`로 대치**
  - 컴파일러가 코드를 컴파일하기 전 처리

```c
#define LOWER 0   /* lower limit of temperature table */
```

- `#define` 전처리문 사용 시, `REPLACEMENT_TEXT` 뒤에 세미콜론을 사용하지 않도록 주의

```c
#define COUNT 10;  /* loop 10 times */

for (i = 0; i < COUNT; ++i) { /* ... */ } /* for (i = 0; i < COUNT;; ++i) -> Syntax error */
```

---

## The for Statement (Cont'd - 2)

### 기호 상수가 추가된 화씨 온도를 섭씨 온도로 변환하는 프로그램

[//]: # (INCLUDE: ./c/01/06.c)

---

## Character Input and Output

### 스트림 (Streams)

- 프로그램에서 입력과 출력을 간단히 사용할 수 있는 인터페이스 (interfaces)
- C 언어 표준 입출력 라이브러리는 스트림을 기반으로 구현됨

![center h:250](image-6.png)

#### 텍스트 스트림 (Text Streams)

- 텍스트 데이터를 내보내거나 가져올 때 사용
- 각 문장의 끝에는 개행문자 (`'\n'`)가 포함됨

#### 이진 스트림 (Binary Streams)

- 이진 데이터로 구성되어 있음
- 메모리에 기록되어 있는 데이터를 내보내거나 가져올 때 사용

---

## Character Input and Output (Cont'd - 1)

### 기본적인 표준 라이브러리 문자 입출력 함수

#### `getchar` 함수

```c
#include <stdio.h>

char c = getchar();
```

- `stdio.h` 헤더 파일 필요
- 키보드는 데이터 소스 (data source)로써, 키보드를 누르면 데이터가 생성되어 입력 스트림 (input stream)에 기록됨
- `getchar` 함수는 입력 스트림에 기록된 문자 하나를 프로그램으로 읽어옴

#### `putchar` 함수

```c
#include <stdio.h>

putchar('a');
```

- `stdio.h` 헤더 파일 필요
- `putchar` 함수는 문자 하나를 전달인자로 넘겨받아 출력 스트림 (output stream)으로 내보냄
- 모니터는 데이터 싱크 (data sink)로써, 출력 스트림에 있는 데이터는 모니터로 전달되어 처리됨

---

## Character Input and Output (Cont'd - 2)

### ASCII (American Standard Code for Information Interchange)

- 컴퓨터에서 문자 하나를 표현하기 위해 0 ~ 255 사이의 정수 값으로 연결한 표준
- 키보드에서 `'A'`를 입력하면, 실제로 텍스트 입력 스트림에 전달되는 값은 `0x41` (`65`)
- 텍스트 출력 스트림에 `0x41` (`65`) 값이 존재할 경우, 모니터에 표현되는 결과는 `'A'`

![center h:450](image-7.png)

---

## Character Input and Output (Cont'd - 3)

### 문자 상수 (Character Constants)

- 작은따옴표 사이에 쓰여진 문자 값
- 문자 상수는 정수 상수로 간주되기도 함
  - ASCII 표를 참조하면 각 문자마다 이에 대응되는 정수 값이 정의되어 있음
  - 문자 상수 `'A'`는 실제로 정수 값 `0x41` (`65`)을 의미
  - 문자 상수 `'\n'`는 실제로 정수 값 `0x0A` (`10`)을 의미

### 상수 주의사항

- `1` vs. `'1'`
  - `1`은 정수 값 `1` (**정수 상수**)
  - `'1'`은 문자를 표현하기 위한 정수 값 `0x31` (`49`) (**문자 상수**)
- `'\n'` vs. `"\n"`
  - `'\n'`은 문자 (이스케이프 시퀀스)를 표현하기 위한 `0x0A` (`10`) (**문자 상수**)
  - `"\n"`은 문자 상수를 문자열의 일부로 사용한 값 (**문자열 상수**)

---

## Character Input and Output (Cont'd - 4)

### 파일 복사

- 기본적인 문자 입출력 함수만을 사용해 구현하는 파일 복사

```text
read a character
while (charater is not end-of-file indicator) {
    output the character just read
    read a character
}
```

[//]: # (INCLUDE: ./c/01/07.c)

- `Ctrl + D`를 누르면 텍스트 입력 스트림으로 `EOF` (end-of-file)가 전달되어 프로그램이 종료됨

---

## Character Input and Output (Cont'd - 5)

### 관계 연산자 (Relational Operators)

```c
while (c != EOF) { /* ... */ }
```

- 두 피연산자의 관계를 평가해 참 (`true`) 또는 거짓 (`false`)으로 결과를 반환
- 총 6 개의 관계연산자가 있음

| Operator | Description    | Example   |
|--------|------|------|
| `==` | Equal to | `a == b` |
| `!=` | Not equal to | `a != b` |
| `<`  | Less than | `a < b` |
| `>`  | Greater than | `a > b` |
| `<=` | Less than or equal to | `a <= b` |
| `>=` | Greater than or equal to | `a >= b` |

#### 관계 연산자 사용 시 주의사항

- 대입 연산자 (`=`)와 관계 연산자 (`==`)를 혼동하지 말 것

---

## Character Input and Output (Cont'd - 6)

### 개선된 파일 복사

[//]: # (INCLUDE: ./c/01/08.c)

### 연산자 우선순위 (Operator Precedence)

- 표현식 내 연산자들은 우선순위에 따라 높은 우선순위의 연산자부터 평가됨
- **대입 연산자 (`=`)는 논리 연산자 (`!=`)보다 우선순위가 낮음**
  - `c = getchar() != EOF` 표현은 `getchar() != EOF` 표현을 먼저 평가함
  - 변수 `c`에는 문자 값이 되입되는 것이 아닌, 논리 연산자의 평가 결과 (참 또는 거짓)가 대입됨
- 표현식 내에 여러 개의 연산자를 사용해야 할 경우, 괄호를 사용하면 실수를 피하면서 가독성을 높일 수 있음
  - 괄호로 둘러쌓인 표현은 가장 높은 우선순위를 가짐

---

## Character Input and Output (Cont'd - 7)

### 형에 따른 값 표현 범위

```c
int c;

c = getchar();
```

- `int` 형은 정수형을 표현하는 자료형
- `char` 형은 문자 하나를 표현하는 자료형
- `getchar` 함수는 문자 하나를 입력 스트림으로부터 읽어와 반환하는 함수
- `char` 형 변수가 아닌 `int`형 변수를 사용한 이유는 **`getchar` 함수가 `EOF`를 반환할 수 있기 때문**
  - `char` 형은 ASCII에 정의되어 있는 문자를 담을 수 있는 자료형
    - 총 256 가지의 값을 담을 수 있음
  - `EOF`는 `getchar` 함수를 호출했을 때, 더 이상의 데이터가 입력 스트림에 없을 경우 반환하는 상태 값
  - `getchar` 함수는 문자 (256 개) 뿐만 아니라 입력 스트림 상태 (1 개)도 반환
    - 반환 가능한 종류는 총 257가지
  - 256 가지의 값을 담을 수 있는 `char`형 변수는 `getchar` 함수의 반환을 전부 처리할 수 없음

---

## Character Input and Output (Cont'd - 8)

### 문자 세기

[//]: # (INCLUDE: ./c/01/09.c)

### 새로운 연산자 `++` (증가 연산자, Increment Operator)

- 변수의 값을 1 증가시키는 연산자

```c
int i = 3;
++i;  /* now i is 4 */
float f = 3.5;
++f;  /* now f is 4.5 */
```

---

## Character Input and Output (Cont'd - 9)

### `long` 자료형

```c
long nc;

printf("%ld\n", nc);
```

- `int` 자료형은 약 -21억 ~ 21억 사이의 값을 표현할 수 있음
- `long` 자료형은 `int` 형보다 더 작거나 더 큰 값을 표현할 수 있음
  - NB: Sizes and ranges are **platform‑dependent**; table assumes LP64
- `printf` 함수를 사용해 `long` 형 값을 출력하고자 할 경우, 변환 지정자 `%ld` 사용

| Data type  | Size (bytes) | Minimum value | Maximum value |
|------------|------------|---------------|---------------|
| `char`     | 1          | -128          | 127           |
| `short`    | 2          | -32,768       | 32,767        |
| `int`      | 4          | -2,147,483,648 | 2,147,483,647 |
| `long`     | 8          | -9,223,372,036,854,775,808 | 9,223,372,036,854,775,807 |

---

## Character Input and Output (Cont'd - 10)

### 개선된 문자 세기

[//]: # (INCLUDE: ./c/01/10.c)

---

## Character Input and Output (Cont'd - 11)

### `double` 자료형

```c
double nc;

printf("%.0f\n", nc);
```

- `float` 자료형처럼 실수 값을 표현할 수 있는 자료형
- `long` 자료형이 표현할 수 있는 최대 범위를 벗어나는 값은 `double` 형으로 표현할 수 있음
  - **오차가 발생할 수 있음**
- `printf` 함수를 사용해 `double` 형 값을 출력하고자 할 경우, 변환 지정자 `%f` 사용
  - `%f.0`: 실수형 데이터를 출력할 때, 소수점 자리를 출력하지 않도록 형식화

| Data type  | Size (bytes) | Precision (decimal digits) | Representable range |
|------------|--------------|-----------------------------|---------------------|
| `float`    | 4            | About 6~7                   | ±1.17549 × 10⁻³⁸ ~ ±3.40282 × 10³⁸ |
| `double`   | 8            | About 15~16                 | ±2.22507 × 10⁻³⁰⁸ ~ ±1.79769 × 10³⁰⁸ |

---

## Character Input and Output (Cont'd - 12)

### 줄 세기

- 텍스트 입력 스트림에 입력된 각 문장은 끝에 `'\n'` 문자가 포함되므로, `'\n'`의 개수는 곧 줄의 개수

[//]: # (INCLUDE: ./c/01/11.c)

### 조건문 (`if` 문)

```c
if (c == '\n') { /* ... */ }
```

- `if` 키워드 다음에 등장하는 조건이 참일 경우, 조건문 본문 수행

---

## Character Input and Output (Cont'd - 13)

### 줄의 수, 단어의 수, 문자의 수를 세는 프로그램

[//]: # (INCLUDE: ./c/01/12.c)

---

## Character Input and Output (Cont'd - 14)

### 연산자의 결합 방향 (Operator Associativity)

```c
nl = nw = nc = 0;
```

- 표현식 내 연산자들은 결합 방향에 따라 연산자 주변 피연산자와 결합
- 대입 연산자 (`=`)는 **오른쪽에서 왼쪽으로 결합**
- `nl = nw = nc = 0;` 문장은 아래와 같이 결합되어 평가됨:

```c
/* 1 */ nl = nw = (nc = 0);
/* 2 */ nl = (nw = (nc = 0));
/* 3 */ (nl = (nw = (nc = 0)));
```

### 논리 연산자 (Logical Operators)

```c
if ((c == ' ') || (c == '\n') || (c == '\t')) { /* ... */ }
```

- 논리 연산자 (`&&`)는 논리곱 (logical AND), (`||`)는 논리합 (logical OR)
- 논리 연산자는 **왼쪽에서 오른쪽으로 결합**
- 논리 연산자를 사용하는 표현식을 평가하는 도중 **이미 결과가 자명할 경우**, 뒤따르는 평가를 수행하지 않음
  - SCE, short-circuit evaluation

---

## Character Input and Output (Cont'd - 15)

### `else` 문

```c
if (c == '\n')
    /* ... */

if ((c == ' ') || (c == '\n') || (c == '\t')) {
    /* ... */
} else if (state == OUT) {
    /* ... */
}
```

- `if` 문의 조건이 참이라면 `if` 문의 본문을 수행
- `if` 문의 조건이 거짓이라면:
  - `else` 문이 없다면 아무 동작을 수행하지 않음
  - `else` 문이 있다면 `else` 문 본문을 수행
- 위 코드는 아래 코드를 축약한 표현

```c
if (cond_1) {
    /* ... */
} else {
    if (cond_2) {
        /* ... */
    }
}
```

---

## Arrays

- 변수 선언 방법

```c
int student_score1, student_score2, /* ... */, student_score100;
```

- 동일한 성질을 갖는 같은 형 변수를 여러 개 선언해야 하는 경우 배열을 사용하면 편리하게 선언할 수 있음
- 배열 선언 형식은 `TYPE NAME[SIZE]`
  - `TYPE` 형 변수를 `SIZE` 개 선언하는 것

```c
int student_score[100];
```

- 배열 선언 후 배열의 이름에 인덱스 번호를 지정하면 배열의 원소 (elements)를 고를 수 있음
- 배열 원소 선택은 `NAME[INDEX]`
  - 배열 선언 시 `SIZE` 크기로 선언했다면, **사용 가능한 인덱스 범위는 `0` ~ `(SIZE - 1)`**

```c
student_score[0] = 100;
student_score[1] = 75;
/* ... */
student_score[99] = 25;
```

---

## Arrays (Cont'd - 1)

### 숫자 문자, 공백 문자, 그 외 문자의 빈도 계산 프로그램

[//]: # (INCLUDE: ./c/01/13.c)

---

## Arrays (Cont'd - 2)

### ASCII 성질을 활용한 기술들

```c
int ndigit[10];

if (c >= '0' && c <= '9')
    ++ndigit[c - '0'];
```

- ASCII에 정의된 숫자 문자는 **서로 인접해 있음**
  - `'0'`은 `0x30` (`48`), `'1'`은 `0x31` (`49`), ..., `'9'`는 `0x39` (`57`)
- `c >= '0' && c <= '9'` 표현식은 문자형 변수 `c`가 숫자 문자인지 판별할 수 있음
- `c - '0'` 표현식은 배열의 인덱스를 구할 수 있음
  - 인덱스 0: 숫자 문자 `'0'`의 빈도
  - 인덱스 1: 숫자 문자 `'1'`의 빈도
  - ...
  - 인덱스 9: 숫자 문자 `'9'`의 빈도

---

## Functions

- 프로그램 내 사용 빈도가 높은 문장 또는 서로 밀접한 연관이 있는 문장을 분리해 새로운 논리적 단위로 구분할 수 있음
- 함수라는 논리적 단위를 적용하면 프로그램을 **구조화**할 수 있고, 가독성을 높일 수 있음
- 함수로 분리한 내용은 함수 호출을 통해 함수 본문을 **재사용**할 수 있음
- 지금까지 배운 함수로는 `printf`, `putchar`, `getchar`가 있음

### 함수의 정의

```c
int main(void)
{
    printf("Main function invoked!\n");

    return 0;
}
```

- 사용자가 직접 필요에 따라 함수를 정의할 수 있음
- 함수 정의 형식은 `RETURN_TYPE FUNCTION_NAME(PARAMETERS) { STATEMENTS }`
  - `RETURN_TYPE`: 자료형, 함수 종료 시 해당 자료형 값을 반환
    - 만약 함수 종료 시 값을 반환하지 않는 함수라면, `void` 사용
  - `FUNCTION_NAME`: 함수의 이름, 함수 호출 시 사용
  - `PARAMETERS`: 매개변수, 함수 호출 시 전달되는 값
    - 만약 매개변수 없는 함수를 정의할 경우, `void` 사용

---

## Functions (Cont'd - 1)

### ${m}^{n}$을 계산하는 `power` 함수

[//]: # (INCLUDE: ./c/01/14.c)

---

## Functions (Cont'd - 2)

### 함수 선언 (Function Declarations)

```c
int power(int m, int n);     /* function declaration */
int power(int base, int n)   /* function definition */
{
    /* ... */
}

```

- 함수 정의 부분에서 함수의 본문 없이 사용한 문장
- 컴파일러에게 함수의 정보를 알리는 용도로 사용
  - 컴파일러는 소스코드를 맨 윗줄부터 차례로 분석
  - 함수 정의를 만나기 전 `power`라는 이름을 마주할 경우, 해당 함수의 정보가 없으므로 컴파일 오류 발생
  - 소스코드 상단에 `power` 함수 선언을 할 경우, 컴파일러에게 다음과 같은 정보를 전달할 수 있음:
    - `power`라는 이름은 함수
    - `power` 함수는 호출 시 두 개의 `int` 형 전달인자가 필요
    - `power` 함수 종료 시 `int` 형 값 반환
- **함수 정의에서의 매개변수 이름과 함수 선언에서의 매개변수 이름은 같지 않아도 됨**
  - 컴파일러에게 필요한 정보는 매개변수 이름이 아닌 **함수 호출 시 필요한 매개변수의 개수와 각 매개변수의 자료형**
- 함수 선언과 함수 정의는 서로 동일한 반환형, 이름, 매개변수의 형태를 가져야 함

---

## Functions (Cont'd - 3)

### 지역 변수 (Local Variables)

```c
int main(void)
{
    int i;
    /* ... */
}

int power(int base, int n)
{
    int i, p;
    /* ... */
}
```

- 함수 안에 선언된 변수는 지역 변수
- 두 함수 (`main`, `power`)는 둘 다 지역 변수 `i`를 선언해 사용
- 서로 다른 함수는 **서로 다른 지역을 사용함**
- `main` 함수의 `i`와 `power` 함수의 `i`는 **서로 이름이 같지만** 구분됨

---

## Functions (Cont'd - 4)

### 함수의 반환값

```c
int power(int m, int n);

printf("%d %d %d\n", i, power(2, i), power(-3, i));
```

- `power` 함수의 반환형은 `int` 형
- `printf` 함수의 형식 문자열은 세 개의 전달인자를 정수형으로 형식화 후 출력
  - 첫 번째 변환 지정자 `%d`는 `i`의 값을 정수형으로 형식화 후 출력
  - 두 번째 변환 지정자 `%d`는 `power(2, i)`의 반환값을 정수형으로 형식화 후 출력
  - 세 번째 변환 지정자 `%d`는 `power(-3, i)`의 반환값을 정수형으로 형식화 후 출력
- 반환값은 아래와 같이 무시할 수도 있음

```c
int power(int m, int n);

power(4, i);  /* return value (int) will be ignored */
```

---

## Character Arrays

```c
#include <stdio.h>

char arr1[3];
arr1[0] = 'H';
arr1[1] = 'i';
arr1[2] = '\0';
printf("%s\n", arr1);

char arr2[100] = "Hello";
printf("%s\n", arr2);
```

- 가장 많이 사용되는 배열 형태 중 하나
- `char` 형 배열은 **문자열**을 저장할 수 있음
- `char` 형 배열에 문자열을 저장할 때, 반드시 문자열의 끝에는 널 문자 (`'\0'`)를 기록해야 함
  - 널 문자는 문자열의 끝을 의미하는 문자이며, 정수 값은 `0x00` (`0`)
  - **문자열 상수의 길이가 5라면, `char` 형 배열의 크기는 최소 6 이상이여야 함**
- `char` 형 배열 선언 시 문자열 상수를 대입하면, 문자열 끝에 자동으로 널 문자를 기록함
- `printf` 함수의 변환 지정자 `%s`를 사용하면 문자열을 출력할 수 있음

| Index  | 0  | 1  | 2  | 3  | 4  | 5  | ... | 99 |
|--------|----|----|----|----|----|----|-----|----|
| **Value**  | `'H'`  | `'e'`  | `'l'`  | `'l'`  | `'o'`  | `'\0'` | ... | `'\0'` |

---

## Character Arrays (Cont'd - 1)

### `char` 형 배열을 함수로 전달하기

[//]: # (INCLUDE: ./c/01/15_example.c)

### 입력된 문자열 중 가장 긴 문자열을 출력하는 프로그램

```text
while (there's another line) {
    if (it's longer than the previous longest)
        save it and its length
}
print longest line
```

---

## Character Arrays (Cont'd - 2)

[//]: # (INCLUDE: ./c/01/15_part1.c)

---

## Character Arrays (Cont'd - 3)

[//]: # (INCLUDE: ./c/01/15_part2.c)

---

## External Variables and Scope

### 지역 변수

- 함수 내에 선언한 변수
- 해당 함수 내에서만 사용 가능
- 지역 변수는 함수가 호출되면 생성되고, 함수가 종료되면 자동 소멸되어 자동 변수 (automatic variables)라고도 함
  - **지역 변수의 값은 함수가 종료되면 지워짐**
- 지역 변수는 생성과 동시에 **쓰레기 값**을 가짐

### 외부 변수

- 함수 외에 선언한 변수
- 여러 함수가 동시에 사용 가능
  - 여러 개의 함수가 동일한 매개변수를 사용한다면, 외부 변수를 사용해 함수의 매개변수를 줄일 수 있음
  - 함수 내에 `extern` 키워드를 사용해 외부 변수를 선언하면 해당 함수에서 사용 가능
- 외부 변수는 프로그램이 실행되면 생성되고, 프로그램이 종료되면 소멸되는 변수
  - **외부 변수의 값은 프로그램이 종료될 때까지 유지됨**
- 외부 변수는 생성과 동시에 **`0`으로 초기화됨**
- 외부 변수는 함수 외에 한 번만 선언해야 함
  - 여러 번 동일한 이름으로 외부 변수를 선언할 경우 컴파일 오류

---

## External Variables and Scope (Cont'd)

[//]: # (INCLUDE: ./c/01/16_part1.c)

---

[//]: # (INCLUDE: ./c/01/16_part2.c)
