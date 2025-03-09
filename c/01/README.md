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

## 프로그램 (Program)

- 기계어 명령들의 집합으로, 각 명령어는 매우 원시적인 수준의 연산 (extremely primitive)을 수행
  - e.g., Adding two numbers, testing if a number is equal to zero, etc.
- 인터넷 브라우저 크롬은 약 1.1억 개의 원시적인 명령들의 집합

![center h:450](image.png)

---

## 프로그램 동작 방식

- 프로그램을 실행하면 운영체제 로더 (Loader)에 의해 프로그램은 메모리로 적재됨
  - Loader: the part of an operating system that is responsible for **loading programs and libraries**

![center h:200](image-1.png)

- 메모리에 적재된 프로그램은 CPU에 의해 처리됨
  - CPU runs a *fetch/execute* cycle.
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

```c
#include <stdio.h>
```

- 보통 코드의 맨 윗부분에 위치
- 프로그램 실행에 필요한 기능들을 프로그램 내에 포함시킴
- e.g., `stdio.h`: 표준 입출력 (`stdio`: standard inputs and outputs) 관련 내용을 프로그램에 포함시킴

### `main` 함수

```c
int main(void)
{
  /* ... */
}
```

- **프로그램의 시작점**
  - 프로그램 실행은 `main` 함수를 호출하는 것
- 함수 내용은 중괄호 (`{`, `}`)로 둘러싸여 있음
- 위의 `main` 함수는 두 문장 (statements, `printf` 문, `return` 문)을 포함하는 함수
- **함수 내 모든 문장의 마지막에는 반드시 세미콜론 (`;`)을 사용해야 함**

---

## Getting Started (Cont'd - 2)

### `return` 문 (반환문)

```c
return 0;
```

- 함수를 종료하는 문장
  - `main` 함수의 종료는 프로그램의 종료를 의미
- `return` 다음에 등장하는 표현식 (expressions)은 함수 호출 측 (caller)로 전달됨
  - 터미널에서 프로그램을 실행한 경우, `main` 함수의 `return` 값 (반환값)은 터미널로 전달

```shell
$ ./hello
Hello, World  # return 0; Terminal will receive it
$ echo $?
0
```

### `printf` 문

```c
printf("Hello, World\n");
```

- `printf` 함수를 호출하는 문장
- 전달인자 (arguments)를 콘솔 화면에 출력하는 역할 수행
  - e.g., `printf("Hello, World\n");` 문장에서의 전달인자는 `"Hello, World\n"`

---

## Getting Started (Cont'd - 3)

### 문자열 (Strings)

```c
"Hello, World"
"The C Programming Language"
```

- 큰따옴표 (`"`)를 사용해 표현한 값
- 여러 문자들을 묶은 값
- 문자열 (character string) 또는 문자열 상수 (string constant)라고 부름

### 이스케이프 시퀀스 (Escape Sequence)

```c
"Character string\n"
'\n'
```

- 백슬래시 (`\`) 뒤에 한 문자 또는 숫자 조합이 오는 문자 조합
- **두 개 이상의 문자 조합이지만, 한 문자 (a character)로 간주**
  - 작은따옴표 (`'`)를 사용해 표현한 값은 문자 하나를 의미
- 데이터가 아닌 특수한 명령을 수행하는 용도로 사용
  - e.g., `\n`: 터미널로 데이터 출력 시 한 줄 개행 (newline)

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
- `/*  */` 사이에 위치한 모든 문자는 **전처리기**에 의해 제거
- 프로그램 소스코드 내 공백 문자 (a blank, tab, or newline)가 등장할 수 있는 위치에 사용 가능

[//]: # (INCLUDE: ./c/01/02_2.c)

---

## Variables and Arithmetic Expressions (Cont'd - 2)

### 변수 (Variables)

```c
int fahr, celsius;
int lower, upper, step;
```

- 프로그램 내에서 데이터를 보관하는 용도
- **모든 변수는 반드시 사용 전에 선언 (declarations)되어야 함**
- 변수 선언은 사용할 형 (types)과 이름의 조합으로 구성:

```c
/* int : type
   step: name */
int step;
```

- 형 종류는 아래와 같음:

```c
int    /* integer */
float  /* floating point */

char   /* character - a single byte */
short  /* short integer */
long   /* long integer */
double /* double-precision floating point */
```

---

## Variables and Arithmetic Expressions (Cont'd - 3)

### 대입문 (Assignment Statements)

```c
lower = 0;   /* lower limit of temperature table */
upper = 300; /* upper limit */
step = 20;   /* step size */
fahr = lower;
```

- 변수에 값을 대입 (assignments)할 때 사용하는 문장
- 대입 연산자 (`=`)를 사용해 변수에 값을 전달할 수 있음

### `while` 반복문

```c
while (fahr <= upper) {
    celsius = 5 * (fahr - 32) / 9;
    printf("%d\t%d\n", fahr, celsius);
    fahr = fahr + step;
}
```

- `while` 키워드 다음에 등장하는 조건 (conditions)을 만족하는 동안 중괄호 내 각 문장들을 여러 번 반복할 수 있음

---

## Variables and Arithmetic Expressions (Cont'd - 4)

### 산술 표현식 (Arithmetic Expressions)

```c
celsius = 5 * (fahr - 32) / 9;
fahr = fahr + step;
```

- 산술 연산자를 사용하는 표현식

| Operator | Description    | Example   | Result |
|----------|--------------|-----------|--------|
| `+`      | Addition      | `5 + 3`   | `8`    |
| `-`      | Subtraction   | `5 - 3`   | `2`    |
| `*`      | Multiplication | `5 * 3` | `15`   |
| `/`      | Division      | `6 / 3`   | `2`    |

#### 산술 연산자 사용 시 주의사항

```c
/* 1 */ celsius = 5 * (fahr - 32) / 9;
/* 2 */ celsius = 5 / 9 * (fahr - 32);
```

- 2번 문장의 `5 / 9` 표현은 두 피연산자가 **정수** 값
- **정수형 나눗셈에서의 나머지는 버려지므로, `5 / 9`의 값은 0으로 평가됨**

---

## Variables and Arithmetic Expressions (Cont'd - 5)

### 형식에 따른 출력 (Formatted Output)

```c
/* 1 */ printf("Hello, World\n");
/* 2 */ printf("%d\t%d\n", fahr, celsius);
```

- `printf` 함수의 첫 번째 전달인자는 화면에 실제로 출력되는 문자열
- `printf` 함수는 출력을 형식화하는 기능을 지원함
- 첫 번째 전달인자가 형식 지정자 (format specifiers)를 포함하면, 뒤따르는 전달인자와 조합하여 형식화된 출력 가능
  - 형식 지정자: `%` 기호로 시작하는 연속된 문자열
  - **첫 번째 전달인자 내 형식 지정자의 수와 뒤따르는 전달인자의 수는 일치해야 함**

```c
printf("%d + %d = %d\n", 1, 2, 1 + 2);
printf("PI: %f\n", 3.141592);
printf("PI: %d\n", 3.141592);  /* 3.141592 will convert to 3 by %d */
```

- `%d`는 연관되는 전달인자를 **정수** 값으로 출력
- `%f`는 연관되는 전달인자를 **실수** 값으로 출력

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

- 산술 연산 표현에 실수 값과 정수 값이 같이 사용될 경우, **정수 값은 실수 값으로 처리됨**

```c
fahr = lower;  // 0 (the lower's value, int type) will be convert to 0.0 (float type)
```

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

---

## The for Statement (cont'd)

### 기호 상수 (Symbolic Constants)가 추가된 화씨 온도를 섭씨 온도로 변환하는 프로그램

[//]: # (INCLUDE: ./c/01/06.c)

---

# Symbolic Constants
- 컴퓨터프로그래밍기초
- 30
- Symbolic Constants
- 프로그램 작성 시 나쁜 습관
- 프로그램 내에 설명이 누락된 상수(magic numbers) 사용을 배제할 것
- 나중에 코드를 다시 본다면, 다른 사람 뿐만 아니라 해당 프로그램 작성자조차 코드 내 각 상수들이 무엇을 의미하는지 명확히 이해하기 어려움
- 유지보수 한계
- #include <stdio.h>
-     /* print Fahrenheit-Celsius table */
-     int main(void)
-     {
-       int fahr;
-       for (fahr = 0; fahr <= 300; fahr = fahr + 20)
-         printf("%3d %6.1f\n", fahr, (5.0 / 9.0) * (fahr - 32));
-       return 0;
-     }


# Symbolic Constants
- 컴퓨터프로그래밍기초
- 31
- Symbolic Constants
- 프로그램 내 상수 관리 방법
- 기호 상수(symbolic constant) 사용
- 
- 상수에 유의미한 이름 사용
- 컴파일 시 소스코드 중에서 NAME이 있는 곳을 REPLACEMENT_TEXT로 치환
- 기호 상수는 변수가 아님
- 변수 선언과 다른 방법으로 선언
- 변수는 소문자, 상수는 대문자를 사용해 서로 구분
- 상수는 불변, 변수는 가변
- #define 사용 시 REPLACEMENT_TEXT 뒤에는 세미콜론(;)을 사용하지 않음
- #define NAME REPLACEMENT_TEXT


# Symbolic Constants
- 컴퓨터프로그래밍기초
- 32
- Symbolic Constants
- 프로그램 내 상수 관리 방법 (Cont’d)
- #include <stdio.h>
-     
-     #define LOWER 0   /* lower limit of temperature table */
-     #define UPPER 300 /* upper limit */
-     #define STEP 20   /* step size */
-     
-     /* print Fahrenheit-Celsius table */
-     int main(void)
-     {
-       int fahr;
-     
-       for (fahr = LOWER; fahr <= UPPER; fahr = fahr + STEP)
-         printf("%3d %6.1f\n", fahr, (5.0 / 9.0) * (fahr - 32));
-     
-       return 0;
-     }


# Character Input and Output
- 컴퓨터프로그래밍기초
- 33
- Character Input and Output
- C 언어는 입력과 출력을 간단히 처리할 수 있는 모델을 라이브러리 형태로 제공
- 스트림(stream)
- 
- 
- 
- 
- 
- 텍스트 스트림은 연속된 문장들로 구성되어 있으며, 각 문장 끝에는 개행문자('\n')가 포함되어 있음
- C Program
- Data Source
- Data Destination
- Input Stream
- Output Stream
- Internal Data Formats:
- char, int, float, double, ...
- External Data Formats:
- Text in various encodings(US-ASCII, UTF-8, ...)
- Binary (raw bytes)


# Character Input and Output
- 컴퓨터프로그래밍기초
- 34
- Character Input and Output
- 표준 라이브러리가 제공하는 가장 기본적인 문자 입출력 함수
- getchar
- 키보드를 통해 발생된 데이터는 입력 스트림에 차례대로 기록
- 입력 스트림에 보관되어 있는 문자 하나를 프로그램으로 읽어옴
- putchar
- 전달인자로 넘겨받은 값을 출력 스트림으로 내보내며, 이 값들은 출력 스트림에 차례대로 기록됨
- ASCII. (2023, March 5). Retrieved from https://en.wikipedia.org/wiki/ASCII


# Character Input and Output
- 컴퓨터프로그래밍기초
- 35
- Character Input and Output
- 문자 상수(Character constant)
- 작은따옴표 사이에 쓰여진 문자는 ASCII 표에 있는 문자의 숫자 값과 동일한 정수 값을 나타냄
- 'A'
- ASCII 표를 보면, 값 65는 문자 'A'를 나타냄
- '\n'
- 두 개의 문자가 사용된 문자열 상수처럼 보이지만, 이스케이프 문자가 같이 사용된 경우는 예외로 간주(이스케이프 시퀀스)
- 이스케이프 시퀀스는 하나의 문자로 간주
- ASCII 표를 보면, 값 10은 이스케이프 시퀀스 '\n'를 나타냄
- "\n"
- 하나의 이스케이프 시퀀스를 포함하는 문자열 상수


# Character Input and Output
- 컴퓨터프로그래밍기초
- 36
- Character Input and Output
- 파일 복사
- 표준 라이브러리가 제공하는 가장 기본적인 문자 입출력 함수만을 사용해 파일 복사를 수행할 수 있음
- copies its input to its output one character at a time
- read a character
-     while (charater is not end-of-file indicator)
-       output the character just read
-       read a character


# Character Input and Output
- 컴퓨터프로그래밍기초
- 37
- Character Input and Output
- 파일 복사 (Cont’d)
- In Linux and macOS environments, you can terminate standard input by outputting EOF(end of file) using the CTRL + D keyboard shortcut. 
- In Windows environments, the equivalent of CTRL + D requires a two-step sequence:
- CTRL + Z followed by <return>
- #include <stdio.h> /* Already defined EOF(-1) in stdio.h */
-     /* copy input to output; 1st version */
-     int main(void)
-     {
-       int c;
-       c = getchar();
-       while (c != EOF) {
-         putchar(c);
-         c = getchar();
-       }
-       return 0;
-     }


# Character Input and Output
- 컴퓨터프로그래밍기초
- 38
- Character Input and Output
- 파일 복사 (Cont’d)
- 관계 연산자(relational operator) !=는 같지 않음을 의미
- #include <stdio.h> /* Already defined EOF(-1) in stdio.h */
-     /* copy input to output; 1st version */
-     int main(void)
-     {
-       int c;
-       c = getchar();
-       while (c != EOF) {
-         putchar(c);
-         c = getchar();
-       }
-       return 0;
-     }


# Character Input and Output
- 컴퓨터프로그래밍기초
- 39
- Character Input and Output
- 파일 복사 (Cont’d)
- 표현식 중 대입식은 표현식의 일부가 될 수 있음
- 왜 c의 형은 char 형이 아닌 int 형일까?
- getchar 함수가 반환할 수 있는 값들은 ASCII 코드 문자들(256 개) 외에 EOF 또는 오류 발생을 나타내는 기호들
- char 형은 1 byte 크기를 보관할 수 있으며, 이는 256 개의 값을 보관할 수 있음
- char 형은 getchar 함수의 반환값을 모두 표현할 수 없음
- #include <stdio.h>
-     /* copy input to output; 2nd version */
-     int main(void)
-     {
-       int c; /* instead of char type */
-       /* 연산자 우선순위 !=가 =보다 높음 */
-       while ((c = getchar()) != EOF)
-         putchar(c);
-       return 0;
-     }


# Character Input and Output
- 컴퓨터프로그래밍기초
- 40
- Character Input and Output
- 문자 세기
- 새로운 연산자(++, --)
- 1 증가 혹은 1 감소 시 사용
- #include <stdio.h>
-     
-     /*count characters in input; 1st version*/
-     int main(void)
-     {
-       long nc;
-     
-       nc = 0;
-       while (getchar() != EOF)
-         ++nc;
- 
-       printf("%ld\n", nc);
-     
-       return 0;
-     }
- ++nc; /* nc = nc + 1 */
- 	--nc; /* nc = nc - 1 */


# Character Input and Output
- 컴퓨터프로그래밍기초
- 41
- Character Input and Output
- 문자 세기 (Cont’d)
- 더 큰 수를 처리할 수 있도록 long 형을 double 형으로 변경
- 
- while 반복문을 for 반복문으로 변경
- 
- printf 함수의 형식 지정자를 실수 출력할 수 있도록 변경
- #include <stdio.h>
-     
-     /*count characters in input; 2nd version*/
-     int main(void)
-     {
-       double nc;
-     
-       for (nc = 0; getchar() != EOF; ++nc) {}
- 
-       printf("%.0f\n", nc);
-     
-       return 0;
-     }


# Character Input and Output
- 컴퓨터프로그래밍기초
- 42
- Character Input and Output
- 줄 세기
- 표준 라이브러리를 사용해 텍스트 입력을 받으면, 입력되는 문장들 끝에 개행문자를 붙임
- 
- 개행문자의 개수가 곧 줄의 개수
- #include <stdio.h>
-     
-     /* count lines in input */
-     int main(void)
-     {
-       int c, nl;
-     
-       nl = 0;
-       while ((c = getchar()) != EOF) {
-         if (c == '\n')
-           ++nl;
-       }
-       printf("%d\n", nl);
-     
-       return 0;
-     }


# Character Input and Output
- 컴퓨터프로그래밍기초
- 43
- Character Input and Output
- 줄 세기 (Cont’d)
- if 문
- 괄호 속 조건을 검사해 조건이 참이면 if 문 내부 문장 수행
- 관계 연산자(relational operator) ==는 같음을 의미
- 대입 연산자 =와 혼동하지 말 것
- #include <stdio.h>
-     
-     /* count lines in input */
-     int main(void)
-     {
-       int c, nl;
-     
-       nl = 0;
-       while ((c = getchar()) != EOF) {
-         if (c == '\n')
-           ++nl;
-       }
-       printf("%d\n", nl);
-     
-       return 0;
-     }


# Character Input and Output
- 컴퓨터프로그래밍기초
- 44
- Character Input and Output
- 단어 세기
- 줄의 수, 단어의 수, 문자의 수를 세는 프로그램
- UNIX 프로그램 wc의 중요 부분(bare-bones)만을 간추린 코드
- #include <stdio.h>
-     
-     #define IN 1  /* inside a word */
-     #define OUT 0 /* outside a word */
-     
-     /* count lines, words, and characters in input */
-     int main(void)
-     {
-       int c, nl, nw, nc, state;
-     
-       state = OUT;
-       nl = nw = nc = 0;
-       while ((c = getchar()) != EOF) {
-         ++nc;
-         if (c == '\n')
-           ++nl;
-         if ((c == ' ') || (c == '\n') || (c == '\t')) {
-           state = OUT;
-         } else if (state == OUT) {
-           state = IN;
-           ++nw;
-         }
-       }
-       printf("%d %d %d\n", nl, nw, nc);
-     
-       return 0;
-     }


# Character Input and Output
- 컴퓨터프로그래밍기초
- 45
- Character Input and Output
- 단어 세기 (Cont’d)
- 연속 대입문
- 대입문의 결합 방향은 오른쪽부터 왼쪽으로 향함
- nc, nw, nl 순으로 0 대입
- #include <stdio.h>
-     
-     #define IN 1  /* inside a word */
-     #define OUT 0 /* outside a word */
-     
-     /* count lines, words, and characters in input */
-     int main(void)
-     {
-       int c, nl, nw, nc, state;
-     
-       state = OUT;
-       nl = nw = nc = 0;
-       while ((c = getchar()) != EOF) {
-         ++nc;
-         if (c == '\n')
-           ++nl;
-         if ((c == ' ') || (c == '\n') || (c == '\t')) {
-           state = OUT;
-         } else if (state == OUT) {
-           state = IN;
-           ++nw;
-         }
-       }
-       printf("%d %d %d\n", nl, nw, nc);
-     
-       return 0;
-     }


# Character Input and Output
- 컴퓨터프로그래밍기초
- 46
- Character Input and Output
- 단어 세기 (Cont’d)
- 논리 연산자(logical operators)
- &&는 그리고(and), ||는 또는(or)을 의미
- 논리 연산자로 연결된 표현식들은 왼쪽부터 오른쪽으로 결합
- 논리 연산자로 연결된 표현식들을 계산(evaluation)하는 도중에 이미 해당 표현식의 참 또는 거짓이 확정되면 뒤따르는 표현식은 계산하지 않음
- SCE, Short-Circuit Evaluation
- #include <stdio.h>
-     
-     #define IN 1  /* inside a word */
-     #define OUT 0 /* outside a word */
-     
-     /* count lines, words, and characters in input */
-     int main(void)
-     {
-       int c, nl, nw, nc, state;
-     
-       state = OUT;
-       nl = nw = nc = 0;
-       while ((c = getchar()) != EOF) {
-         ++nc;
-         if (c == '\n')
-           ++nl;
-         if ((c == ' ') || (c == '\n') || (c == '\t')) {
-           state = OUT;
-         } else if (state == OUT) {
-           state = IN;
-           ++nw;
-         }
-       }
-       printf("%d %d %d\n", nl, nw, nc);
-     
-       return 0;
-     }


# Character Input and Output
- 컴퓨터프로그래밍기초
- 47
- Character Input and Output
- 단어 세기 (Cont’d)
- if 문
- 
- 
- 
- 괄호 속 표현식이 참이라면, statement1 수행
- 표현식이 거짓이라면, statement2 수행
- #include <stdio.h>
-     
-     #define IN 1  /* inside a word */
-     #define OUT 0 /* outside a word */
-     
-     /* count lines, words, and characters in input */
-     int main(void)
-     {
-       int c, nl, nw, nc, state;
-     
-       state = OUT;
-       nl = nw = nc = 0;
-       while ((c = getchar()) != EOF) {
-         ++nc;
-         if (c == '\n')
-           ++nl;
-         if ((c == ' ') || (c == '\n') || (c == '\t')) {
-           state = OUT;
-         } else if (state == OUT) {
-           state = IN;
-           ++nw;
-         }
-       }
-       printf("%d %d %d\n", nl, nw, nc);
-     
-       return 0;
-     }
- if (expression)
-       statement1
-     else
-       statement2


# Character Input and Output
- 컴퓨터프로그래밍기초
- 48
- Character Input and Output
- 단어 세기 (Cont’d)
- if 문 응용: 중첩된 형태
- #include <stdio.h>
-     
-     #define IN 1  /* inside a word */
-     #define OUT 0 /* outside a word */
-     
-     /* count lines, words, and characters in input */
-     int main(void)
-     {
-       int c, nl, nw, nc, state;
-     
-       state = OUT;
-       nl = nw = nc = 0;
-       while ((c = getchar()) != EOF) {
-         ++nc;
-         if (c == '\n')
-           ++nl;
-         if ((c == ' ') || (c == '\n') || (c == '\t')) {
-           state = OUT;
-         } else if (state == OUT) {
-           state = IN;
-           ++nw;
-         }
-       }
-       printf("%d %d %d\n", nl, nw, nc);
-     
-       return 0;
-     }
- if (expression1)
-       statement1
-     else if (expression2)
-       statement2
- 
- ...
- 
-     else
-       statementn


# Arrays
- 컴퓨터프로그래밍기초
- 49
- Arrays
- 같은 형 변수를 여러 개 선언해야 함과 동시에 이 변수들이 서로 밀접한 관련이 있는 경우가 있음
- 
- 다음과 같이 일일이 변수를 직접 선언하는 것 보다는 배열을 사용하는 것이 훨씬 효율적이고 편리함
- 배열의 선언
- 
- 대괄호 안에 크기를 표현하면, 동일한 형 데이터를 크기만큼 보관할 수 있는 배열을 사용할 수 있음
- int student_score1, student_score2, ..., student_score100;
- int student_score[100];


# Arrays
- 컴퓨터프로그래밍기초
- 50
- Arrays
- 배열의 사용
- 크기가 100인 배열을 선언한 경우, 사용할 수 있는 인덱스의 범위는 0부터 99까지임
- 배열의 시작 인덱스는 0
- 0번 배열 요소의 값을 99번 배열 요소의 값으로 대입하는 예:
- student_score[99] = student_score[0];


# Arrays
- 컴퓨터프로그래밍기초
- 51
- Arrays
- 각 숫자, 공백 문자, 그 외 문자들의 출현 빈도를 계산하는 프로그램
- #include <stdio.h>
-     
-     /* count digits, white space, others */
-     int main(void)
-     {
-       int c, i, nwhite, nother;
-       int ndigit[10];
-     
-       nwhite = nother = 0;
-       for (i = 0; i < 10; ++i)
-         ndigit[i] = 0;
-       while ((c = getchar()) != EOF) {
-         if (c >= '0' && c <= '9')
-           ++ndigit[c-'0'];
-         else if ((c == ' ') || (c == '\n') || (c == '\t'))
-           ++nwhite;
-         else
-           ++nother;
-       }
-     
-       printf("digits =");
-       for (i = 0; i < 10; ++i)
-         printf(" %d", ndigit[i]);
-       printf(", white space = %d, other = %d\n", nwhite, nother);
-     
-       return 0;
-     }


# Arrays
- 컴퓨터프로그래밍기초
- 52
- Arrays
- 각 숫자, 공백 문자, 그 외 문자들의 출현 빈도를 계산하는 프로그램 (Cont’d)
- 저장할 값의 종류는 총 12가지 (0-9, white space, others)
- 숫자 값을 저장하기 위한 정수 형 변수를 10개 선언하는 것 보다는, 정수 형 배열 하나를 선언하는 것이 편하고 효율적
- #include <stdio.h>
-     
-     /* count digits, white space, others */
-     int main(void)
-     {
-       int c, i, nwhite, nother;
-       int ndigit[10];
-     
-       nwhite = nother = 0;
-       for (i = 0; i < 10; ++i)
-         ndigit[i] = 0;
-       while ((c = getchar()) != EOF) {
-         if (c >= '0' && c <= '9')
-           ++ndigit[c-'0'];
-         else if ((c == ' ') || (c == '\n') || (c == '\t'))
-           ++nwhite;
-         else
-           ++nother;
-       }
-     
-       printf("digits =");
-       for (i = 0; i < 10; ++i)
-         printf(" %d", ndigit[i]);
-       printf(", white space = %d, other = %d\n", nwhite, nother);
-     
-       return 0;
-     }


# Arrays
- 컴퓨터프로그래밍기초
- 53
- Arrays
- 각 숫자, 공백 문자, 그 외 문자들의 출현 빈도를 계산하는 프로그램
- 관계 연산자(relational operators)
- 입력된 문자의 숫자 여부를 판별하기 위해 관계 연산자 사용
- ASCII 표를 참고하면, 숫자 0부터 숫자 9까지 연속적으로 할당되어 있음
- '0'은 10진수로 48, '1'은 10진수로 49, ..., '9'는 10진수로 57
- 입력받은 문자에서 '0'을 뺀 값을 배열 인덱스로 활용 가능
- #include <stdio.h>
-     
-     /* count digits, white space, others */
-     int main(void)
-     {
-       int c, i, nwhite, nother;
-       int ndigit[10];
-     
-       nwhite = nother = 0;
-       for (i = 0; i < 10; ++i)
-         ndigit[i] = 0;
-       while ((c = getchar()) != EOF) {
-         if (c >= '0' && c <= '9')
-           ++ndigit[c-'0'];
-         else if ((c == ' ') || (c == '\n') || (c == '\t'))
-           ++nwhite;
-         else
-           ++nother;
-       }
-     
-       printf("digits =");
-       for (i = 0; i < 10; ++i)
-         printf(" %d", ndigit[i]);
-       printf(", white space = %d, other = %d\n", nwhite, nother);
-     
-       return 0;
-     }


# Functions
- 컴퓨터프로그래밍기초
- 54
- Functions
- 프로그램 내에서 여러 번 반복 계산하는 부분을 함수로 정의
- 함수 내부구조를 모르더라도 해당 함수를 호출하면 함수에 정의된 계산을 재사용할 수 있음
- 지금까지 등장한 함수들
- printf, putchar, getchar
- 내부구조는 몰라도 각 함수들을 호출해 사용할 수 있음
- Function (mathematics). (2023, March 5). Retrieved from https://en.wikipedia.org/wiki/Function_(mathematics)


# Functions
- 컴퓨터프로그래밍기초
- 55
- Functions
- 사용자가 직접 함수를 정의할 수 있음
- 함수 정의 또는 선언 시 반환(return) 형, 함수 이름, 그리고 뒤따르는 괄호에 매개변수(parameters) 사용
- 함수의 매개변수가 선언되어 있지 않다면, 함수 호출 시 전달인자를 전달하지 않음
- 함수의 매개변수가 선언되어 있다면, 함수 호출 시 전달인자를 전달해야 함


# Functions
- 컴퓨터프로그래밍기초
- 56
- Functions
- m의 n제곱(mn)을 계산하는 함수 정의
- #include <stdio.h>
-     
-     int power(int m, int n);
-     
-     /* test power function */
-     int main(void)
-     {
-       int i;
-     
-       for (i = 0; i < 10; ++i)
-         printf("%d %d %d\n", i, power(2, i), power(-3, i));
-     
-       return 0;
-     }
-     
-     int power(int base, int n)
-     {
-       int i, p;
-     
-       p = 1;
-       for (i = 1; i <= n; ++i)
-         p = p * base;
-     
-       return p;
-     }


# Functions
- 컴퓨터프로그래밍기초
- 57
- Functions
- m의 n제곱(mn)을 계산하는 함수 정의 (Cont’d)
- 함수 선언
- function prototype
- 함수의 반환 형, 함수의 이름, 매개변수 목록 순으로 지정
- 매개변수 목록은 가변임
- 함수 선언 시 매개변수 이름은 선택사항
- 잘 작성된 매개변수 이름은 함수 사용에 도움을 줄 수 있음
- #include <stdio.h>
-     
-     int power(int m, int n);
-     
-     /* test power function */
-     int main(void)
-     {
-       int i;
-     
-       for (i = 0; i < 10; ++i)
-         printf("%d %d %d\n", i, power(2, i), power(-3, i));
-     
-       return 0;
-     }
-     
-     int power(int base, int n)
-     {
-       int i, p;
-     
-       p = 1;
-       for (i = 1; i <= n; ++i)
-         p = p * base;
-     
-       return p;
-     }


# Functions
- 컴퓨터프로그래밍기초
- 58
- Functions
- m의 n제곱(mn)을 계산하는 함수 정의 (Cont’d)
- 함수 정의
- 함수의 선언과 형태가 일치해야 함
- 예외적으로 함수 선언에서의 매개변수 이름과 함수 정의에서의 매개변수 이름은 바뀔 수 있음
- 만약 함수 선언과 함수 정의가 서로 다른 형태라면, 오류가 발생할 수 있음
- #include <stdio.h>
-     
-     int power(int m, int n);
-     
-     /* test power function */
-     int main(void)
-     {
-       int i;
-     
-       for (i = 0; i < 10; ++i)
-         printf("%d %d %d\n", i, power(2, i), power(-3, i));
-     
-       return 0;
-     }
-     
-     int power(int base, int n)
-     {
-       int i, p;
-     
-       p = 1;
-       for (i = 1; i <= n; ++i)
-         p = p * base;
-     
-       return p;
-     }


# Functions
- 컴퓨터프로그래밍기초
- 59
- Functions
- m의 n제곱(mn)을 계산하는 함수 정의 (Cont’d)
- 지역변수(local variables)
- main 함수에서의 변수 i와 power 함수에서의 변수 i는 서로 다른 변수
- 함수는 하나의 지역을 나타내며, 서로 다른 함수는 서로 다른 지역
- 이름은 같더라도 지역이 다르면 서로 다른 변수로 처리됨
- #include <stdio.h>
-     
-     int power(int m, int n);
-     
-     /* test power function */
-     int main(void)
-     {
-       int i;
-     
-       for (i = 0; i < 10; ++i)
-         printf("%d %d %d\n", i, power(2, i), power(-3, i));
-     
-       return 0;
-     }
-     
-     int power(int base, int n)
-     {
-       int i, p;
-     
-       p = 1;
-       for (i = 1; i <= n; ++i)
-         p = p * base;
-     
-       return p;
-     }


# Functions
- 컴퓨터프로그래밍기초
- 60
- Functions
- m의 n제곱(mn)을 계산하는 함수 정의 (Cont’d)
- 함수는 값을 반환할 수 있으며, 반환할 값이 없다면 함수의 반환형을 void로 사용
- 함수로부터 반환되는 값은 무시할 수 있음
- #include <stdio.h>
-     
-     int power(int m, int n);
-     
-     /* test power function */
-     int main(void)
-     {
-       int i;
-     
-       for (i = 0; i < 10; ++i)
-         printf("%d %d %d\n", i, power(2, i), power(-3, i));
-     
-       return 0;
-     }
-     
-     int power(int base, int n)
-     {
-       int i, p;
-     
-       p = 1;
-       for (i = 1; i <= n; ++i)
-         p = p * base;
-     
-       return p;
-     }


# Arguments - Call by Value
- 컴퓨터프로그래밍기초
- 61
- Arguments - Call by Value
- 매개변수는 전달인자의 값을 그대로 복사하며, 이때 매개변수와 전달인자는 서로 다른 메모리에 위치
- Call by value or passed by value
- 호출된 함수 내에서는 전달인자에 접근하거나 전달인자의 값을 수정할 수 없음
- int power(int base, int n)
-     {
-       int i, p;
-     
-       p = 1;
-       for (i = 1; i <= n; ++i)
-         p = p * base;
-     
-       return p;
-     }


# Character Arrays
- 컴퓨터프로그래밍기초
- 62
- Character Arrays
- 가장 많이 사용되는 배열 형태는 문자열
- 배열 중 char 형 배열은 문자열을 표현할 수 있음
- 
- 
- 
- 
- char 형 배열에 문자열을 사용해 초기화할 경우, char 형 배열 각 요소에 문자열을 구성하는 문자들이 차례대로 저장됨
- 문자열을 구성하는 문자들이 모두 기록되고 나서 바로 다음 배열의 요소에는 문자열의 끝을 표현하는 '\0' 문자가 저장됨
- char arr[100] = "Hello";


# Character Arrays
- 컴퓨터프로그래밍기초
- 63
- Character Arrays
- 입력된 문자열 중 가장 긴 문자열을 출력하는 프로그램
- 
- 
- 매개변수의 형태
- 배열을 전달인자로 넘겨줄 때 해당 배열의 이름을 사용하되, 매개변수에는 []를 사용해 해당 매개변수가 배열임을 표현해야 함
- while (there's another line)
-       if (it's longer than the previous longest)
-         save it and its length
-     print longest line
- #include <stdio.h>
- #define MAXLINE 1000 /* maximum input line size */
- int getline(char line[], int maxline);
- void copy(char to[], char from[]);
- /* print longest input line */
- int main(void)
- {
-   int len;                /* current line length */
-   int max;                /* maximum length seen so far */
-   char line[MAXLINE];     /* current input line */
-   char longest[MAXLINE];  /* longest line saved here */
-   max = 0;
-   while ((len = getline(line, MAXLINE)) > 0) {
-     if (len > max) {
-       max = len;
-       copy(longest, line);
-     }
-   }
-   if (max > 0)  /* there was a line */
-     printf("%s\n", longest);
-   return 0;
- }


# Character Arrays
- 컴퓨터프로그래밍기초
- 64
- Character Arrays
- 입력된 문자열 중 가장 긴 문자열을 출력하는 프로그램 (Cont’d)
- /* getline: read a line into s, return length */
- int getline(char s[], int lim)
- {
-   int c, i;
-   for (i = 0; i < (lim - 1) && (c = getchar()) != EOF && c != '\n'; ++i)
-     s[i] = c;
-   if (c == '\n') {
-     s[i] = c;
-     ++i;
-   }
-   s[i] = '\0';
-   return i;
- }


# Character Arrays
- 컴퓨터프로그래밍기초
- 65
- Character Arrays
- 입력된 문자열 중 가장 긴 문자열을 출력하는 프로그램 (Cont’d)
- /* copy: copy 'from' into 'to'; assume to is big enough */
- void copy(char to[], char from[])
- {
-   int i;
-   i = 0;
-   while ((to[i] = from[i]) != '\0')
-     ++i;
- }


# External Variables and Scope
- 컴퓨터프로그래밍기초
- 66
- External Variables and Scope
- 함수 내에 정의된 변수들은 해당 함수 내에서만(private or local) 사용 가능
- 함수는 다른 곳에 정의된 변수에 접근할 수 없음
- 
- 함수 내에 정의된 변수들은 해당 함수가 호출될 때 생성되고, 함수가 종료되면 제거됨(automatic)
- 
- 외부변수(external variables)를 사용하면 여러 함수가 해당 변수를 동시에 사용할 수 있음


# External Variables and Scope
- 컴퓨터프로그래밍기초
- 67
- External Variables and Scope
- 외부변수(external variables)
- 함수 외부에 선언되는 변수이며 한 번만 선언해야 함
- 
- 다른 함수에서 접근 가능
- 
- 함수 호출 시 사용되는 전달인자의 개수를 줄일 수 있음
- 
- 지역변수는 함수 호출 시 생성되고 함수 종료 시 제거되나, 외부변수는 프로그램 종료 시까지 소멸되지 않음
- 지역변수와 외부변수는 메모리 할당 위치가 서로 구분됨


# External Variables and Scope
- 컴퓨터프로그래밍기초
- 68
- External Variables and Scope
- 외부변수(external variables) (Cont’d)
- 외부변수를 사용하기 위해서는 extern 키워드를 사용해야 함
- 
- 만약 외부변수와 외부변수를 사용하고자 하는 함수가 같은 파일에 위치할 경우 extern 키워드 생략 가능


# Character Arrays
- 컴퓨터프로그래밍기초
- 69
- Character Arrays
- 입력된 문자열 중 가장 긴 문자열을 출력하는 프로그램 – 외부변수 활용
- while (there's another line)
-       if (it's longer than the previous longest)
-         save it and its length
-     print longest line
- #include <stdio.h>
- #define MAXLINE 1000    /* maximum input line size */
- int max;                /* maximum length seen so far */
- char line[MAXLINE];     /* current input line */
- char longest[MAXLINE];  /* longest line saved here */
- int getline(void);
- void copy(void);
- /* print longest input line */
- int main(void)
- {
-   int len;
-   extern int max;
-   extern char longest[];
-   max = 0;
-   while ((len = getline()) > 0) {
-     if (len > max) {
-       max = len;
-       copy();
-     }
-   }
-   if (max > 0)  /* there was a line */
-     printf("%s\n", longest);
-   return 0;
- }


# Character Arrays
- 컴퓨터프로그래밍기초
- 70
- Character Arrays
- 입력된 문자열 중 가장 긴 문자열을 출력하는 프로그램 – 외부변수 활용 (Cont’d)
- 전역변수(global variables) 또는 외부변수(external variables)
- 다른 함수에서 접근 가능한 변수
- 함수 내부에서 전역변수를 사용하고자 할 때 extern 키워드 사용 권장
- 
- 함수는 외부변수에 접근 가능하므로, 함수의 매개변수 사용을 줄일 수 있음
- #include <stdio.h>
- #define MAXLINE 1000    /* maximum input line size */
- int max;                /* maximum length seen so far */
- char line[MAXLINE];     /* current input line */
- char longest[MAXLINE];  /* longest line saved here */
- int getline(void);
- void copy(void);
- /* print longest input line */
- int main(void)
- {
-   int len;
-   extern int max;
-   extern char longest[];
-   max = 0;
-   while ((len = getline()) > 0) {
-     if (len > max) {
-       max = len;
-       copy();
-     }
-   }
-   if (max > 0)  /* there was a line */
-     printf("%s\n", longest);
-   return 0;
- }


# Character Arrays
- 컴퓨터프로그래밍기초
- 71
- Character Arrays
- 입력된 문자열 중 가장 긴 문자열을 출력하는 프로그램 – 외부변수 활용 (Cont’d)
- /* getline: read a line into s, return length */
- int getline(void)
- {
-   int c, i;
-   extern char line[];
-   for (i = 0; i < (MAXLINE - 1) && (c = getchar()) != EOF && c != '\n'; ++i)
-     line[i] = c;
-   if (c == '\n') {
-     line[i] = c;
-     ++i;
-   }
-   line[i] = '\0';
-   return i;
- }


# Character Arrays
- 컴퓨터프로그래밍기초
- 72
- Character Arrays
- 입력된 문자열 중 가장 긴 문자열을 출력하는 프로그램 – 외부변수 활용 (Cont’d)
- /* copy: copy 'from' into 'to'; assume to is big enough */
- void copy(void)
- {
-   int i;
-   extern char line[], longest[];
-   i = 0;
-   while ((longest[i] = line[i]) != '\0')
-     ++i;
- }

