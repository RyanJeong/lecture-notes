---
marp: true
---

# Types, Operators and Expressions

## Goals of This Chapter

### 형 (Types)

- 각 형마다 표현할 수 있는 값과 범위
- 각 형마다 메모리에 값을 표현하는 방법
- 컴퓨터에서 음의 정수를 표현하는 방법
- 실수형 값의 오차와 정밀도

### 연산자 (Operators)

- 연산자의 종류
- 연산자 결합 방향
- 연산자 우선 순위

### 표현 (Expressions)

- 변수와 상수를 사용한 표현
- 표현식에서의 형 변환
- 복잡한 표현식의 평가 방법

---

## Variable Names

- 문자와 숫자, 밑줄 (`_`) 사용 가능
- **변수명 첫 글자에 숫자 사용 불가**

```c
int num_seat;     /* ok */
float rad_1;      /* ok */
int 2nd_trial;    /* error: invalid suffix "nd_trial" on integer constant */
```

- ANSI C (ISO C90) 표준은 `_`로 시작하는 식별자 (변수명)를 표준 라이브러리 및 구현 내부에서 사용함
  - 변수명 첫 글자에 밑줄은 사용 가능하나, **사용하지 않는 것을 권장**
  - **표준 헤더파일 포함 시 충돌날 수 있음**

```c
int _is_modified; /* ok, but don't use it */
```

- 변수명의 대소문자는 구분됨

```c
int a, A;         /* ok, `a` and `A` are difrerent variables */
```

---

## Variable Names (Cont'd)

- 예약어 (keysords)는 변수명으로 사용 불가
  - `while`, `for`, `int`, `float`, etc.
- 변수명은 사용 목적에 맞는 적합한 이름을 사용해야 함
- 지역 변수 (local variables)는 짧은 변수명을, 전역 변수 (global variables)는 긴 변수명을 사용할 것을 권장
  - 지역 변수는 선언된 함수 내에서만 사용 가능하며, **짧은 변수명을 사용해도 해당 변수를 선언한 함수가 의미를 보태줌**
  - 전역 변수는 여러 함수에서 사용 가능하며, **변수 자체만으로 의미를 충분히 전달할 수 있도록 긴 변수명 사용**

[//]: # (INCLUDE: ./c/02/variable_name.c)

---

## Data Types and Sizes

### 기본 자료형

- `char`, `int`, `float`, `double` 네 종류의 자료형이 있음
- 정수 자료형은 한정사 (qualifier)를 사용해 값의 표현 범위를 조절할 수 있음
  - `short (short int)`
  - `long (long int)`

| Type   | Description |
|--------|------------|
| `char`   | Represents a single character, typically 1 byte in size. |
| `int`    | Represents an integer value, **usually 4 bytes** in size. |
| `float`  | Represents a floating-point number with single precision, typically 4 bytes in size. |
| `double` | Represents a floating-point number with double precision, typically 8 bytes in size. |
| `short` | Represents a short integer, typically 2 bytes in size. |
| `long` | Represents a long integer, typically 4 or 8 bytes in size depending on the system. |

---

## Data Types and Sizes (Cont'd - 1)

- 정수형 크기는 데이터 모델 (CPU 구조와 운영체제 조합을 결정되는 기본 자료형 크기)에 의존
  - e.g., x86-64 CPU에 Windows x64 운영체제 설치 시 데이터 모델은 **LLP64**
  - e.g., x86-64 CPU에 Windows x32 운영체제 설치 시 데이터 모델은 **ILP64**

![center](image.png)

- 데이터 모델은 아래 규칙을 준수해 정수형 자료형을 표현
  1. `short`, `int` 형은 적어도 2 바이트 이상의 크기를 가져야 한다.
  2. `long` 형은 적어도 4 바이트 이상의 크기를 가져야 한다.
  3. `short` 형은 `int` 형보다 크기가 클 수 없다.
  4. `int` 형은 `long` 형보다 크기가 클 수 없다.

---

## Data Types and Sizes (Cont'd - 2)

### 부호형 (`signed`)과 무부호형 (`unsigned`)

- `char`, `int` 형은 한정사를 사용해 부호 값 또는 무부호 값을 표현할 수 있음
- 무부호 값은 0과 양수만 표현 가능 (**음수 표현 불가**)
  - e.g., `char` 형은 1 바이트 크기를 가지므로, `unsigned char` 형의 표현 범위는 `0 ~ 255` ($2^8 - 1$)
- 부호 값은 양수와 음수 모두 표현 가능 (2의 보수 표현 사용)
  - e.g., `char` 형은 1 바이트 크기를 가지므로, `char` 형의 표현 범위는 `-128 ~ 127`
- 문자형은 사용 환경에 따라 부호형 또는 무부호형일 수 있음 (machine-dependent)
  - 화면에 출력할 문자들은 `0 ~ 127` 범위에 정의되어 있으며, 부호형과 무부호형 둘 다 문자를 올바르게 표현 가능
- 정수형은 부호형을 기본값으로 사용
  - `short` 형은 `signed short` 형
  - `int` 형은 `signed int` 형
  - `long` 형은 `signed long` 형

---

## Data Types and Sizes (Cont'd - 3)

### `limits.h`

- 자료형 관련 기호 상수들을 정의한 표준 헤더파일

[//]: # (INCLUDE: ./c/02/01.c)

---

## Data Types and Sizes (Cont'd - 4)

```text
char size               :                    1
Minimum signed char     :                 -128
Maximum signed char     :                  127
Maximum unsigned char   :                  255

short size              :                    2
Minimum signed short    :               -32768
Maximum signed short    :                32767
Maximum unsigned short  :                65535

int size                :                    4
Minimum signed int      :          -2147483648
Maximum signed int      :           2147483647
Maximum unsigned int    :           4294967295

long size               :                    8
Minimum signed long     : -9223372036854775808
Maximum signed long     :  9223372036854775807
Maximum unsigned long   : 18446744073709551615
```

### 무부호형 형식 지정자

```c
unsigned int x = 100;
printf("Value: %u\n", x);
```

- `unsigned char`, `unsigned short`, `unsigned int` 형 값을 출력하고자 할 경우, 형식 지정자 `%u` 사용
- `unsigned long` 형 값을 출력하고자 할 경우, 형식 지정자 `%lu` 사용

---

## Data Types and Sizes (Cont'd - 5)

> 다음 코드의 실행 결과는?

[//]: # (INCLUDE: ./c/02/overflow.c)

```text
-1794967296
```

![center](image-1.png)

---

## Data Types and Sizes (Cont'd - 6)

### MSB (Most Significant Bit)

- 정수형 값을 표현하는 비트 중 가장 중요한 역할을 하는 비트
- 부호형 정수에서는 MSB가 **부호**를 결정
  - `1` in MSB → Negative number (e.g., `1000 0000 = -128` **using two's complement**)

| 7 (MSB) | 6 | 5 | 4 | 3 | 2 | 1 | 0 | Value (`signed char`) |
|---|---|---|---|---|---|---|---|------------------|
| 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | `0`            |
| 0 | 0 | 0 | 0 | 0 | 0 | 0 | 1 | `1`            |
| 0 | 0 | 0 | 0 | 0 | 0 | 1 | 0 | `2`            |
| ... | ... | ... | ... | ... | ... | ... | ... | ... |
| 0 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | `127`           |
| 1 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | `-128`          |
| 1 | 0 | 0 | 0 | 0 | 0 | 0 | 1 | `-127`          |
| 1 | 0 | 0 | 0 | 0 | 0 | 1 | 0 | `-126`          |
| ... | ... | ... | ... | ... | ... | ... | ... | ... |
| 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | `-1`            |

---

## Data Types and Sizes (Cont'd - 7)

- 무부호형 정수에서는 MSB가 **부호가 아닌 가장 큰 가중치**를 표현하는 데 사용됨
  - **No negative numbers → `1000 0000` is `128`, `1111 1111` is `255`**.

| 7 (MSB) | 6 | 5 | 4 | 3 | 2 | 1 | 0 | Value (`unsigned char`) |
|---|---|---|---|---|---|---|---|----------------------|
| 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | `0`                |
| 0 | 0 | 0 | 0 | 0 | 0 | 0 | 1 | `1`                |
| 0 | 0 | 0 | 0 | 0 | 0 | 1 | 0 | `2`                |
| ... | ... | ... | ... | ... | ... | ... | ... | ... |
| 0 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | `127`               |
| 1 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | `128`               |
| 1 | 0 | 0 | 0 | 0 | 0 | 0 | 1 | `129`               |
| 1 | 0 | 0 | 0 | 0 | 0 | 1 | 0 | `130`               |
| ... | ... | ... | ... | ... | ... | ... | ... | ... |
| 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | `255`               |

---

## Data Types and Sizes (Cont'd - 8)

### 음의 정수 표현 방법 1 - 부호화 절대치 (Sign-magnitude)

![center](image-2.png)

- MSB는 부호를 표현하고, 나머지 비트는 절대값을 저장
- **0을 표현하는 방법이 두 가지임**
- 음수를 처리하기 위해 **별도의 덧셈기가 필요**

```text
-5:   1101
+3:   0011
--------
    1 0000 != -2 (1010)
```

---

## Data Types and Sizes (Cont'd - 9)

### 음의 정수 표현 방법 2 - 보수화 (Complement)

- 뺄셈을 컴퓨터 내부에서 쉽게 수행하기 위해 뺄셈을 덧셈으로 치환하는 과정
- *n*진수는 *n*의 보수와 *n - 1*의 보수를 사용할 수 있음
  - 10진수는 10의 보수와 9의 보수를, 2진수는 2의 보수와 1의 보수 사용 가능

- 임의의 *n*진수 *X*에 대한 *n - 1*의 보수는 다음과 같음: $(n^k - 1) - X, \quad \text{where } n \text{ is the base and } k \text{ is the number of digits}$
  - e.g., `456 - 123`을 9의 보수를 사용해 계산
    1. `123`의 9의 보수 계산: `999 - 123 = 876 (k = 3)`
    2. `456` + (`-123` = `123`의 9의 보수) 계산: `456 + 876 = 1,332`
    3. 가장 왼쪽 자리 (올림수, carry) 제거: `1,332 -> 332`
    4. 제거한 올림수를 가장 오른쪽 자리에 더하여 보정: `332 + 1 = 333`

- 임의의 *n*진수 *X*에 대한 *n*의 보수는 다음과 같음: $n^k - X, \quad \text{where } n \text{ is the base and } k \text{ is the number of digits}$
  - e.g., `456 - 123`을 10의 보수를 사용해 계산
    1. `123`의 10의 보수 계산: `1,000 - 123 = 877 (k = 3)`
    2. `456` + (`-123` = `123`의 10의 보수) 계산: `456 + 877 = 1,333`
    3. 가장 왼쪽 자리 (올림수, carry) 제거: `1,333 -> 333`

---

## Data Types and Sizes (Cont'd - 10)

### 1의 보수 (1's complement)

![center](image-3.png)

- 임의의 2진수 *X*의 모든 비트를 반전하여 1의 보수를 구할 수 있음
- **0을 표현하는 방법이 두 가지임**
- **추가 보정 작업이 필요할 수 있어 비효율적임**
- e.g., `5 (0101) - 3 (0011)`을 1의 보수를 사용해 계산
  1. `3`의 1의 보수 계산: `1100`
  2. `5` + (`-3` = `3`의 1의 보수) 계산: `0101 + 1100 = 1 0001`
  3. 가장 왼쪽 자리 (올림수, carry) 제거: `1 0001 -> 0001`
  4. 제거한 올림수를 가장 오른쪽 자리에 더하여 보정: `0001 + 1 = 0010`

---

## Data Types and Sizes (Cont'd - 11)

### 2의 보수 (2's complement)

![center](image-4.png)

- 임의의 2진수 *X*의 모든 비트를 반전한 뒤 1을 더해 2의 보수를 구할 수 있음
  - 2의 보수는 1의 보수를 계산한 뒤 1을 더한 값
- **0을 유일하게 표현**
- **추가 보정 작업 불필요**
  - 하나의 덧셈기로 뺄셈과 덧셈을 **덧셈으로 일관되게** 처리할 수 있음
- e.g., `5 (0101) - 3 (0011)`을 2의 보수를 사용해 계산
  1. `3`의 1의 보수 계산: `1100`
  2. `3`의 1의 보수로 변환한 값에 1을 더하여 2의 보수 계산: `1101`
  3. `5` + (`-3` = `3`의 2의 보수) 계산: `0101 + 1101 = 1 0010`
  4. 가장 왼쪽 자리 (올림수, carry) 제거: `1 0010 -> 0010`

---

## Data Types and Sizes (Cont'd - 12)

### Integer Overflow

![center](image-5.png)

> The condition that occurs when a calculation produces a result that is greater in magnitude than that which a given register or storage location can store or represent.

- 연산 결과 값 (magnitude)이 **데이터 표헌 범위를 벗어날 경우** 오버플로우 발생
  - e.g., 값 표현에 4비트를 사용한다고 가정
    - 양수를 표현할 수 있는 비트의 범위는 `0000 ~ 0111`
    - 음수를 표현할 수 있는 비트의 범위는 `1000 ~ 1111`
  1. `+7 (0111)`에 1을 더하면 오버플로우 발생 (8을 표현하려면 한 비트가 더 필요함)
  2. `-8 (1000)`에 1을 빼면 **오버플로우** 발생 (-9를 표현하려면 한 비트가 더 필요함)
    > NB: The term **underflow** normally refers to floating point numbers only!

---

## Data Types and Sizes (Cont'd - 13)

> Counting just 50,000 sheep should do the trick... What?

![center](image-6.png)

---

## Data Types and Sizes (Cont'd - 14)

> 다음 코드의 실행 결과는?

[//]: # (INCLUDE: ./c/02/precision.c)

```text
0.1 + 0.2 and 0.3 are NOT the same.
```

![center h:280](image-7.png)

---

## Data Types and Sizes (Cont'd - 15)

### 고정소수점 (Fixed-Point)

- 실수 값을 표현하는 **비표준 방식**이며, 필요에 따라 정의해 사용할 수 있음
- 오차가 발생하지 않으나, **표현할 수 있는 값의 범위가 제한적인 방법**
e.g., 고정소수점을 표현하기 위한 1 byte, 2 bytes, 4 bytes 정의 예시

![center](image-8.png)

| Size | Sign | Integer Part | Fractional Part |
|----|----|-------------|---------------|
| 1 byte | 1 bit | 4 bits | 3 bits |
| 2 bytes | 1 bit | 9 bits | 6 bits |
| 4 bytes | 1 bit | 15 bits | 16 bits |

- e.g., 고정소수점을 사용해 `37.25`, `-37.25`를 2 bytes에 표현한 예

```text
        S.(1) |   Int.(9)   | Frac.(6)    Fixed-Point Representation
+36.25:   0   | 0 0010 0100 | 01 0000   ->      0000 1001 0001 0000
-36.25:   1   | 0 0010 0100 | 01 0000   ->      1000 1001 0001 0000
```

---

## Data Types and Sizes (Cont'd - 16)

### 부동소수점 (Floating-Point)

- 실수 값을 표현하는 **표준 방식**
  - [IEEE Standard for Floating-Point Arithmetic (IEEE 754)](https://en.wikipedia.org/wiki/IEEE_754)
  - `float` (single precision)
  - `double` (double precision)
  - `long double` (extended precision)
    - 표준에서 허용하는 범위 내에서 구현된 자료형
    - Implementation-defined behavior (컴파일러마다 동작이 상이할 수 있음)
- 고정소수점 방식에 비해 복잡하고 많은 연산을 요구함
- 오차가 발생할 수 있지만, **표현할 수 있는 값의 범위가 광범위함**

---

## Data Types and Sizes (Cont'd - 17)

### 단정도 부동소수점 (Single-Precision Floating-Point)

![center](image-9.png)

$$(-1)^S \times 1.M \times 2^{E - 127}$$

- 4 bytes를 사용해 실수 데이터를 표현하는 방법
- 부호부 (*S*, `sign`)는 1 bit, 지수부 (*E*, `exponent`)는 8 bits, 가수부 (*M*, `mantissa`)는 23 bits를 사용
- 실수 데이터를 2진수로 변환한 뒤, **정규화**를 한 결과를 부호부, 지수부, 가수부에 표현
- e.g., 단정도 부동소수점을 사용해 37.25를 표현한 예

```text
- Integer Part                             : 10 0101
- Fractional Part                          :      01
- Fixed-Point Representation               : 10 0101.01
- Normalized Floating-Point Representation :       1.0010 101 x 2^5
- IEEE 754 Floating-Point Representation   : (1). S: 0
                                                  (positive: 0, negative: 1)
                                             (2). E: 1000 0100
                                                  (E - 127 = 5, E = 132)
                                           : (3). M: 0010 101
                                                  (fill the rest bits with 0)
                                           : 0100 0010 0001 0101 0000 0000 0000 0000
```

- 가수부는 실제 23 bits의 정밀도를 갖는게 아닌, **24 bits의 정밀도를 가짐**
  - 정규화된 형태는 1 bit가 암묵적으로 표현되므로, 이를 implicit bit 또는 hidden bit라고 부름

---

## Data Types and Sizes (Cont'd - 18)

### 단정도 부동소수점의 미리 정의된 형태

- `E = 0`, `M = 0`
  - 부동소수점에서 0 (`±0`)을 표현하는 방식 (부호 비트에 따라 `+0` 또는 `-0`)
- `E = 0`, `M != 0`
  - 서브노멀 값 (subnormal number, denormalized number)을 표현: $(-1)^S \times 0.M \times 2^{-126}$
  - **연산 결과가 정규화된 최소값보다 작은 경우를 저장할 때 사용 (언더플로우)**
  - 정규화된 수와 달리 implicit bit (`1.XXX` 형태의 `1`)가 없으므로 정밀도가 더 낮음
  - 연산 결과가 서브노멀 값보다도 작을 경우 **0으로 처리됨 (flush to zero)**
- `E = 1 ~ 254`, `M = any value`
  - 정규화된 수 (normalized number)를 표현: $(-1)^S \times 1.M \times 2^{E - 127}$
  - 일반적인 부동소수점 값을 저장할 때 사용
- `E = 255`, `M = 0`
  - **연산 결과가 표현할 수 있는 최대치를 초과해 오버플로우가 발생한 경우**
  - IEEE 754에서는 무한대 (`±∞`)로 처리됨 (부호 비트에 따라 `+∞` 또는 `-∞`)
- `E = 255`, `M != 0`
  - `NaN` (not a number)
  - 정의되지 않은 연산 결과로 인해 숫자가 아닌 결과가 반환된 경우 (e.g., `0/0`, `∞ - ∞`, etc.)

---

## Data Types and Sizes (Cont'd - 19)

### 단정도 부동소수점에서 표현할 수 있는 최대 및 최소값

#### 정규화된 값 (Normalized Number)

$$(-1)^S \times 1.M \times 2^{E - 127}$$

- `S = 0`, `E = 254`, `M = 1111111...111`
  - 가장 큰 정규화된 값 (양수): `+3.4028235 × 10^(+38)`
- `S = 0`, `E = 1`, `M = 0000000...000`
  - 가장 작은 정규화된 값 (양수): `+1.17549435 × 10^(-38)`
- `S = 1`, `E = 254`, `M = 1111111...111`
  - 가장 큰 정규화된 값 (음수): `-3.4028235 × 10^(+38)`
- `S = 1`, `E = 1`, `M = 0000000...000`
  - 가장 작은 정규화된 값 (음수): `-1.17549435 × 10^(-38)`

#### 서브노멀 값 (Subnormal Number)

$$(-1)^S \times 0.M \times 2^{-126}$$

- `S = 0`, `E = 0`, `M = 0000000...001`
  - 가장 작은 서브노멀 값 (양수): `+1.40129846 × 10^(-45)`
- `S = 1`, `E = 0`, `M = 0000000...001`
  - 가장 큰 서브노멀 값 (음수): `-1.40129846 × 10^(-45)`

---

## Data Types and Sizes (Cont'd - 20)

### 배정도 부동소수점 (Double-Precision Floating-Point)

---

### 수직선 상에 표현한 배정도 부동소수점

![center](floating-point-number-line.png)

---

- 
- 
- Floating point format IEEE-754, 64 bits:  (−1)S × 1.M × 2E−1,023
- 주황색 부분: 부호 (sign), 1 bit
- 초록색 부분: 지수부 (exponent), 11 bits
- 파란색 부분: 소수부 (mantissa), 52 bits
- 정규화된 (normalized) 가수부는 1과 같거나 크며, 102보다는 작음
- 정규화된 가수부는 53비트의 정밀도를 가짐


# Data Types and Sizes
- 컴퓨터프로그래밍기초
- 32
- Data Types and Sizes
- 배정도 부동 소수점 (double-precision floating-point)  (Cont’d)
- 
- 
- 단정도 부동 소수점 형에서 미리 정의한 규칙들 그대로 사용
- E = 0, M = 0Underflow, S가 0이면 +0, S가 1이면 −0 (같은 0으로 봐도 무방)
- E = 0, M ≠ 0Might be underflow, 정규화되지 않은 경우이며, 식  (−1)S × 0.M × 2E−1,022으로 처리
- E = 2,047, M = 0Overflow, S가 0이면 양의 무한대 (+∞), S가 1이면 음의 무한대 (−∞)
- E = 2,047, M ≠ 0NaN (Not a Number)를 의미하며, 연산이 잘못되어 알 수 없는 값이 나온 경우


# Data Types and Sizes
- 컴퓨터프로그래밍기초
- 33
- Data Types and Sizes
- 배정도 부동 소수점 (double-precision floating-point)  (Cont’d)
- 
- 
- 배정도 부동 소수점이 나타낼 수 있는 가장 작은 수
- 1.0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 00002 × 2−1022  (2.2250738585072014 × 10-308)
- 정규화되지 않았다면 (E = 0, M ≠ 0) 더 작은 값 표현 가능:0.0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 00012 × 2−1022 = 2-1074
- 배정도 부동 소수점이 나타낼 수 있는 가장 큰 수
- 1.1111 1111 1111 1111 1111 1111 1111 1111 1111 1111 1111 1111 11112 × 21023  (1.7976931348623158 × 10308)


# Data Types and Sizes
- 컴퓨터프로그래밍기초
- 34
- Data Types and Sizes
- Underflow (Arithmetic underflow)
- The condition in a computer program that can occur when the true result of a floating point operation is smaller in magnitude  (that is, closer to zero) than the smallest value representable as a normal floating point number in the target datatype.
- 
- 
- 언더플로우 발생 시, 다음 중 한 가지 방법으로 처리됨:
- 0으로 처리 (-0 or +0)
- 형에서 표현할 수 있는 최소값으로 처리
- NaN으로 처리
- float a = 1e-30;  /* smallest positive normal number of single-precision: 1.175494351 10-38 */
-     a /= 1e20;        /* Underflow! */


# Data Types and Sizes
- 컴퓨터프로그래밍기초
- 35
- Data Types and Sizes
- 값에 오차가 발생하면 안 되는 경우 고정 소수점 사용 
- 은행, 군사무기체계 등
- 값의 크기가 크거나 작을수록 메모리 사용량 증가
- 
- 연산 속도가 중요할 경우 단정도 부동 소수점 (float) 사용
- 
- 단정도 부동 소수점 형보다 정밀하게 값을 표현해야 할 경우 배정도 부동 소수점 (double) 사용


# Data Types and Sizes
- 컴퓨터프로그래밍기초
- 36
- Data Types and Sizes
- 다음 코드의 실행 결과는?
- #include <stdio.h>
-     
-     int main (void)
-     {
-       float f1, f2, f3, f4, f5, f6, f7;
-     
-       f1 = 9999876.0;  /* 7 자리, 값이 정확히 출력될 것을 보장 */
-       f2 = 99998765.0; /* 8 자리, 값이 정확히 출력될 것을 보장받지 못함*/
-       f3 = 16777216.0; /* 1.0000 0000 0000 0000 0000 0000 X 2^24 */
-       f4 = 16777216.5; /* f4 표현할 bit 수 부족 > f3과 동일한 결과 */
-       f5 = 16777217.0; /* f5 표현할 bit 수 부족 > f3과 동일한 결과 */
-       f6 = 16777218.0; /* 1.0000 0000 0000 0000 0000 0010 X 2^24 */
-       f7 = 27.1;       /*  (271 / 10), 10은 2^n 형태로 표현 불가 -> 순환소수 */
-       printf ("A single-precision only has about 7 decimal digits of precision.\n"
-           "before: 9999876.0, after: %10.1f\n"
-           "before: 99998765.0, after: %10.1f\n\n", f1, f2);
-       printf ("16777216.0, 16777216.5, 16777217.0 are represented exactly "
-           "by the same value in the single-precision data type.\n"
-           "before: 16777216.0, after: %10.1f\n"
-           "before: 16777216.5, after: %10.1f\n"
-           "before: 16777217.0, after: %10.1f\n"
-           "before: 16777218.0, after: %10.1f\n\n", f3, f4, f5, f6);
-       printf ("27.1  (may be simply 271/10) cannot be expressed as 2^n.\n"
-           "27.1  (precision is 6): %.6f\n"
-           "27.1  (precision is 8): %.8f\n"
-           "27.1  (precision is 10): %.10f\n\n", f7, f7, f7);
-     
-       return 0;
-     }
- A single-precision only has about 7 decimal digits of precision.
- before:  9999876.0, after:  9999876.0
- before: 99998765.0, after: 99998768.0
- 
- 16777216.0, 16777216.5, 16777217.0 are represented exactly by the same value in the single-precision data type.
- before: 16777216.0, after: 16777216.0
- before: 16777216.5, after: 16777216.0
- before: 16777217.0, after: 16777216.0
- before: 16777218.0, after: 16777218.0
- 
- 27.1  (may be simply 271/10) cannot be expressed as 2^n.
- 27.1  (precision is  6): 27.100000
- 27.1  (precision is  8): 27.10000038
- 27.1  (precision is 10): 27.1000003815


# Data Types and Sizes
- 컴퓨터프로그래밍기초
- 37
- Data Types and Sizes
- The Patriot Missile Failure
- On February 25, 1991, during the Gulf War, an American Patriot Missile battery in Dharan, Saudi Arabia, failed to track and intercept an incoming Iraqi Scud missile.
- The Scud struck an American Army barracks, killing 28 soldiers and injuring around 100 other people.
- It turns out that the cause was an inaccurate calculation of the time since boot due to computer arithmetic errors.
- The Patriot Missile Failure.  (2023, March 20). Retrieved from http://www-users.math.umn.edu/~arnold/disasters/patriot.html


# Data Types and Sizes
- 컴퓨터프로그래밍기초
- 38
- Data Types and Sizes
- The Patriot Missile Failure  (Cont’d)
- 초를 계산하기 위해 내부 시스템 클럭 값에 1/1010을 곱해 사용
- 데이터 표현에 24 비트 고정 소수점형 사용
- 1/1010을 이진수로 표현 시 0.000 1100 1100 1100 ...2,24비트 고정 소수점형으로 표현 시0.000 1100 1100 1100 1100 11002
- 0.000 0000 0000 0000 0000 0000 1100 1100 ...2 오차 발생 (십진수 표현 시 약 0.00000009510)
- 100 시간 경과 시 누적 오차는 약 0.34 초
- 0.00000009510 × 100 (시간) × 60 (시) × 60 (분) × 10 (초) = 0.34 초


# Data Types and Sizes
- 컴퓨터프로그래밍기초
- 39
- Data Types and Sizes
- 메모리에 값을 저장하는 방법 (endianness)
- 빅 엔디언 (big endian)
- MSB가 메모리 앞쪽에 위치
- e.g. 0x1234 5678
- 
- 
- 
- 
- 
- 
- 
- 소프트웨어 디버그 용이
- 리틀 엔디언 (little endian)
- MSB가 메모리 뒤쪽에 위치
- e.g. 0x1234 5678
- 
- 
- 
- 
- 
- 
- 
- 하위 바이트부터 계산하므로 계산 효율 관점에서 빅 엔디언보다 우수


# Data Types and Sizes
- 컴퓨터프로그래밍기초
- 40
- Data Types and Sizes
- 다음 코드의 실행 결과는?
- 실행 환경의 endianness는 little endian이라고 가정
- #include <stdio.h>
-     
-     int main (void)
-     {
-       char *str;
-       char c0, c1, c2, c3;
-       int i;
-       float f;
-     
-       str = "DJU"; /* 'D' (44), 'J' (4A), 'U' (55), '\0' (00) */
-       c0 = str[0];
-       c1 = str[1];
-       c2 = str[2];
-       c3 = str[3];
-       i = * ( (int *) str);
-       f = * ( (float *) str);
-       printf ("1. string: %s\n", str);
-       printf ("2. char: \n"
-           "\tchar str[0] : %1c (%02X), \n"
-           "\tchar str[1] : %1c (%02X), \n"
-           "\tchar str[2] : %1c (%02X), \n"
-           "\tchar str[3] : %2c (%02X), \n",
-           c0, c0, c1, c1, c2, c2, c3, c3);
-       printf ("3. int: %d (%08X)\n", i, i);
-       printf ("4. float: %e\n", f);
-     
-       return 0;
-     }
- 1. string: DJU
- 2. char: 
-         char str[0] : D (44), 
-         char str[1] : J (4A), 
-         char str[2] : U (55), 
-         char str[3] :   (00), 
- 3. int: 5589572 (00554A44)
- 4. float: 7.832659e-39


# Constants
- 컴퓨터프로그래밍기초
- 41
- Constants
- 정수 (integer)
- int
- 1234
- long
- int 형보다 큰 정수형을 표현할 때 사용하며, 정수형 상수에 접미사 l 또는 L 사용
- 123456789L
- unsigned
- 무부호형 정수를 표현할 때 사용하며, 정수형 상수에 접미사 u 또는 U 사용
- 123456789U
- 접미사 ul 또는 UL은 unsigned long 형을 표현할 때 사용


# Constants
- 컴퓨터프로그래밍기초
- 42
- Constants
- 정수 (integer)  (Cont’d)
- 8진수 (octal)
- 정수형 상수에 접두사 0 사용
- e.g. 3110은 037로 표현 가능
- 16진수 (hexadecimal)
- 정수형 상수에 접두사 0x 또는 0X 사용
- e.g. 810은 0x8 또는 0X8로 표현 가능
- e.g. 3110은 0x1f 또는 0X1F로 표현 가능
- 8진수 또는 16진수 상수 표현 시 정수형 접미사 (e.g. l or L, u or U) 사용 가능 
- e.g. 0XFUL은 unsigned long 형이며, 1510를 나타냄


# Constants
- 컴퓨터프로그래밍기초
- 43
- Constants
- 부동 소수점 (floating-point)
- 소수점 (123.4) 또는 지수 (1e-2) 형태로 표현
- 기본 형은 double
- 실수형 상수에 접미사 f 또는 F 사용 시 float 형 표현 가능
- 실수형 상수에 접미사 l 또는 L 사용 시 long double 형 표현 가능


# Constants
- 컴퓨터프로그래밍기초
- 44
- Constants
- 문자 (character)
- 작은따옴표 (single quote) 사용 
- ASCII 문자표에 각 문자 별 고유 정수값으로 정의되어 있음
- e.g. '0'은 정수 값으로 4810
- 숫자 0과 전혀 관련 없음
- 문자 표기 시 반드시 문자 상수를 사용할 것
- 문자 상수는 환경에 독립적임
- e.g. ASCII 코드를 사용하는 환경에서 '0'은 4810이지만, EBCDIC 코드를 사용하는 환경에서 '0'은 24010
- ASCII.  (2023, March 20). Retrieved from https://en.wikipedia.org/wiki/ASCII


# Constants
- 컴퓨터프로그래밍기초
- 45
- Constants
- 문자 (character)  (Cont’d)
- 문자 상수는 정수 연산에 사용될 수 있음
- 
- 
- 이스케이프 문자와 비트 패턴 (bit pattern)을 사용하면 8진수 혹은 16진수로 하나의 문자 상수 표현 가능
- '\ooo' (1-3 octal digits)
- '\xhh' (1-2 hexadecimal digits)
- if  (c >= '0' && c <= '9')
-       ++ndigit[c-'0'];
- #define UPPER_Z '\132'  /* 90 to octal */
- #define VTAB    '\013'  /* ASCII vertical tab */
- #define BELL    '\007'  /* ASCII bell character */
- 
- #define UPPER_Z '\x5A'  /* 90 to hexadecimal */
- #define VTAB    '\xB'   /* ASCII vertical tab */
- #define BELL    '\x7'   /* ASCII vertical tab */


# Constants
- 컴퓨터프로그래밍기초
- 46
- Constants
- 문자 (character)  (Cont’d)
- 이스케이프 시퀀스 (complete set of escape sequence)
- 타자기.  (2023, March 20). Retrieved from https://ko.wikipedia.org/wiki/타자기


# Constants
- 컴퓨터프로그래밍기초
- 47
- Constants
- 상수 수식 (constant expression)
- 상수만으로 구성된 수식
- 컴파일 시 값이 결정되어야 함
- 상수가 사용될 수 있는 곳이라면 어디든지 사용 가능
- #define MAXLINE 1000
-     char line[MAXLINE+1];
- 
-     #define LEAP 1 /* in leap years */
-     int days[31+28+LEAP+31+30+31+30+31+31+30+31+30+31];


# Constants
- 컴퓨터프로그래밍기초
- 48
- Constants
- 문자열 상수 (string constant or string literal)
- 큰따옴표 (double quote) 사이에 문자가 존재하지 않거나 하나 이상의 문자가 구성될 수 있음
- 
- 큰따옴표는 문자열 상수 안에 포함되지 않음
- 문자열 상수임을 알리기 위한 역할 (구분자, delimiter)
- 문자열 상수 내 큰따옴표를 구성하고자 할 때 이스케이프 시퀀스 (\")를 사용해 구분자가 아닌 문자열 상수 내 구성 문자임을 명시해야 함
- 문자열 상수의 나열은 컴파일 시 연결됨
- "I am a string"
-     "" /* the empty string */
- "Hello, " "World!"     /* is equivalent to */
-     "Hello, World!"


# Constants
- 컴퓨터프로그래밍기초
- 49
- Constants
- 문자열 상수 (string constant or string literal)  (Cont’d)
- e.g. 나열된 문자열 상수 연결 예:
- 
- 
- 
- 문자열 상수는 char 형 배열
- 문자열의 끝을 나타내는 기호로 널 (NULL, '\0') 문자가 사용됨
- char 형 배열의 크기는 저장하고자 하는 문자열의 길이보다 1 만큼 더 필요 ('\0')
- printf ("This is useful for splitting up long strings across several source lines.\n");
-   
-     printf ("This is useful "
-         "for splitting up long strings "
-         "across several source lines.\n");


# Constants
- 컴퓨터프로그래밍기초
- 50
- Constants
- 문자열 상수 (string constant or string literal)  (Cont’d)
- 널 (NULL) 문자 사용 예:
- <string.h> 헤더 파일 내에 strlen 함수가 정의되어 있음
- /* strlen: return length of s */
-     int strlen (char s[])
-     {
-       int i;
-       i = 0;
-       while  (s[i] != '\0')
-         ++i;
-       return i;
-     }


# Constants
- 컴퓨터프로그래밍기초
- 51
- Constants
- 문자열 상수 (string constant or string literal)  (Cont’d)
- 문자 상수와 문자열 상수 반드시 구분할 것
- 'x'와 "x"는 같지 않음
- 'x'는 해당 환경에서 사용하는 문자 집합 (character set) 중 'x'를 표현하는 정수
- "x"는 char 형 배열이며, 두 개의 문자 (문자 x와 널 문자 '\0')가 사용된 문자열


# Constants
- 컴퓨터프로그래밍기초
- 52
- Constants
- 열거 상수 (enumeration constant) 
- 정수형 상수 열거
- 값을 따로 지정하지 않은 상수는 이전 상수의 값보다 1 큰 값을 가짐
- 목록 내 첫 번째 상수에 값 지정을 하지 않는다면 0으로 초기화
- 목록 내 상수의 이름은 고유해야 하며, 각 상수는 값은 같을 수 있음
- enum boolean { NO, YES };
-     enum escapes {
-         BELL      = '\a',  
-         BACKSPACE = '\b',  
-         TAB       = '\t', 
-         NEWLINE   = '\n', 
-         VTAB      = '\v',    
-         RETURN    = '\r' };
-     enum months {
-         JAN = 1, FEB, MAR, 
-         APR, MAY, JUN, 
-         JUL, AUG, SEP, 
-         OCT, NOV, DEC }; /* FEB is 2, MAR is 3, etc. */


# Declarations
- 컴퓨터프로그래밍기초
- 53
- Declarations
- 모든 변수는 반드시 사용 전에 선언되어야 함
- 타입과 하나 이상의 변수 명으로 구성됨
- 선언할 변수의 개수만큼 줄을 할당할 경우 공간은 더 많이 차지하지만, 각 변수에 대한 설명을 주석 형태로 남기거나 후에 변수 선언 수정 시 더 편리할 수 있음
- int lower, upper, step;
-     char c, line[1000];
-     
-     int lower;
-     int upper;
-     int step;
-     char c;
-     char line[1000];


# Declarations
- 컴퓨터프로그래밍기초
- 54
- Declarations
- 변수는 선언과 동시에 초기화할 수 있음
- 
- 
- 
- 변수 선언 시 변수명 다음에 = 기호와 표현식 (expressions)이 뒤따르면, 변수는 표현식으로 초기화됨
- char esc = '\\';
-     int i = 0;
-     int limit =  (MAXLINE + 1);
-     float eps = 10e-5;


# Declarations
- 컴퓨터프로그래밍기초
- 55
- Declarations
- 지역변수 (local variable or automatic variable)는 해당 변수를 포함하는 함수가 호출되면 선언 수행
- 선언식에 초기화가 명시되어 있지 않다면, 해당 변수는 쓰레기 값 (undefined value)을 가짐
- 초기화 식에는 아무 표현식이나 올 수 있음
- 전역변수 (global variable or external variable) 또는 정적변수 (static variable)는 프로그램 실행 시 한 번만 선언 및 초기화 수행
- 선언식에 초기화가 명시되어 있지 않다면, 해당 변수는 값 0으로 초기화
- 초기화 식에는 무조건 상수 표현식이 와야 함


# Declarations
- 컴퓨터프로그래밍기초
- 56
- Declarations
- 한정사 const
- 변수 선언 시 해당 변수의 값이 변경되는 것을 방지하기 위해 사용
- 읽기 전용 변수
- 
- 
- 
- const 변수의 값을 수정하려고 할 때, 결과는 각 프로그래밍 언어의 구현 방법에 따라 정의되어 있는 방법을 따름
- 절대 수정 불가, 최초 한 번만 수정 허용, ...
- const double e = 2.71828182845905;
-     const char msg[] = "warning: ";
-     
-     int strlen (const char[]);  /* 매개변수로 받는 값은 고정임 */


# Arithmetic Operators
- 컴퓨터프로그래밍기초
- 57
- Arithmetic Operators
- 덧셈 (+), 뺄셈 (-), 곱셈 (*), 나눗셈 (/), 나머지 (%)
- 
- 정수 나눗셈 연산 결과는 소수점 이하 무시됨
- 
- 나머지 연산 (modulus, %)
- x % y
- x를 y로 나누었을 때의 나머지 값이며, x가 y로 나누어 떨어지면 값은 0
- float 형, double 형에는 % 연산자 적용할 수 없음


# Arithmetic Operators
- 컴퓨터프로그래밍기초
- 58
- Arithmetic Operators
- 음수 나눗셈 연산 결과는 확정할 수 없음
- 기계 종속적
- −111 / 11 결과는 −10 또는 −11
- 
- 음수 나머지 연산 결과는 확정할 수 없음
- 기계 종속적
- −111 % 11 결과는 −1 또는 10
- 나머지 연산은 식 a ==  (a / b) * b + a % b을 만족하도록 구현되어 있음
- e.g.  (a / b)가 -10일 경우, a % b는 -1
- e.g.  (a / b)가 -11일 경우, a % b는 10


# Arithmetic Operators
- 컴퓨터프로그래밍기초
- 59
- Arithmetic Operators
- 윤년 판단하는 프로그램
- 4로 나누어 떨어지지만 100으로 나누어 떨어지지 않아야 한다.
- 400으로 나누어 떨어지는 해는 윤년으로 한다. (예: 2000년, 2400년)
- /* leap year */
-     if  ( (year % 4 == 0 && year % 100 != 0) ||  (year % 400 == 0))
-       printf ("%d is a leap year\n", year);
-     else
-       printf ("%d is not a leap year\n", year);


# Arithmetic Operators
- 컴퓨터프로그래밍기초
- 60
- Arithmetic Operators
- 산술 연산자 (arithmetic operators) 
- 덧셈, 뺄셈 연산은 우선 순위가 같음
- 덧셈, 뺄셈 연산은 곱셈, 나눗셈, 나머지 연산보다 우선 순위가 낮음
- 곱셈, 나눗셈, 나머지 연산은 단항 (unary) 연산보다 우선 순위가 낮음
- 연산 시 좌에서 우로 결합


# Relational and Logical Operators
- 컴퓨터프로그래밍기초
- 61
- Relational and Logical Operators
- 관계 연산자 (relational operators)
- >, >=, <, <=, ==, !=
- 관계 연산자는 산술 연산자보다 우선 순위가 낮음
- if  (i < lim - 1) { ... }  /* i <  (lim - 1) */


# Relational and Logical Operators
- 컴퓨터프로그래밍기초
- 62
- Relational and Logical Operators
- 논리 연산자 (logical operators)
- &&, ||
- 연산 시 좌에서 우로 결합
- 평가할 표현식이 남았음에도 참 또는 거짓이 판정되면 즉시 검사를 마침
- SCE, short circuit evaluation
- 논리 연산자는 관계 연산자보다 우선 순위가 낮음
- if  (i < lim - 1 &&  (c = getchar ()) != '\n' && c != EOF) { ... }


# Relational and Logical Operators
- 컴퓨터프로그래밍기초
- 63
- Relational and Logical Operators
- 관계 연산자 또는 논리 연산자의 평가 결과가 참이면 1, 거짓이면 0으로 평가됨
- 
- 
- valid == 0 형태보다 !valid 형태가 valid가 아니면이라는 의미를 잘 전달함
- valid == 0 형태는 표현식이 길어지거나 복잡해지면 가독성을 해칠 수 있음
- if  (!valid) { ... }
-     
-     if  (valid == 0) { ... }


# Type Conversions
- 컴퓨터프로그래밍기초
- 64
- Type Conversions
- 형이 다른 피연산자끼리 연산 수행 시 형 변환 발생
- 
- 자동 변환 (automatic conversion)
- convert a narrower operand into a wider one without losing information
- 반대의 경우도 형 변환은 가능하지만, 정보 손실이 발생할 수 있음 (컴파일 경고 발생)


# Type Conversions
- 컴퓨터프로그래밍기초
- 65
- Type Conversions
- 문자는 하나의 정수
- char 형은 int 형보다 표현 범위가 좁기 때문에 자동 변환 규칙이 적용됨
- 산술 연산자와 자유롭게 사용 가능한 이유이며, 해당 규칙은 코드 작성 시 엄청난 융통성을 발휘함
- 
- e.g. 문자를 정수로 변환하는 예 1:
- <stdlib.h> 헤더 파일 내에 atoi 함수가 정의되어 있음
- /* atoi: convert s to integer */
-     int atoi (char s[])
-     {
-       int i, n;
-     
-       n = 0;
-       for  (i = 0; s[i] >= '0' && s[i] <= '9'; ++i)
-         n = 10 * n +  (s[i] - '0');
-     
-       return n;
-     }


# Type Conversions
- 컴퓨터프로그래밍기초
- 66
- Type Conversions
- 문자는 하나의 정수  (Cont’d)
- e.g. 문자를 정수로 변환하는 예 2:
- <ctype.h> 헤더 파일 내에 tolower 함수가 정의되어 있음
- ASCII 문자 체계를 사용하는 기계에만 적용 가능하며, EBCDIC 등 다른 문자 체계를 사용하는 환경에서는 사용 불가
- 
- ASCII 문자 체계의 특징을 활용:
- 'A'와 'Z' 사이에 대문자만 등장
- 'a'와 'z' 사이에 소문자만 등장
- 대문자와 소문자 간 차이가 항상 일정
- /* lower: convert c to lower case; ASCII only */
-     int lower (int c)
-     {
-       if  (c >= 'A' && c <= 'Z')
-         return  (c + 'a' - 'A');
-       else
-         return c;
-     }


# Type Conversions
- 컴퓨터프로그래밍기초
- 67
- Type Conversions
- 암묵적인 산술 변환 (implicit arithmetic conversion)
- 서로 다른 두 형 간 연산을 할 때, 무부호형 피연산자가 없다면:
-  표현식 내 long double 형이 있으면 둘 다 long double 형으로 변환
-  Otherwise, 표현식 내 double 형이 있으면 둘 다 double 형으로 변환
-  Otherwise, 표현식 내 float 형이 있으면 둘 다 float 형으로 변환
-  Otherwise, 표현식 내 char 형 또는 short 형을 int 형으로 변환
-  Then, 표현식 내 long 형인 피연산자가 있다면 모두 long 형으로 변환
- 
- 실수 값 표현 시 기본형은 float 형
- 표현식 내 char 형 또는 short 형이 있다면 이는 int 형으로 변환되나, float 형 표현이 있을 경우 double 형으로 형 변환되지 않음
- 저장 공간 또는 계산 시간 절약 목적


# Type Conversions
- 컴퓨터프로그래밍기초
- 68
- Type Conversions
- 암묵적인 산술 변환 (implicit arithmetic conversion)  (Cont’d)
- 서로 다른 두 형 간 연산 시 무부호형 피연산자가 있다면, 기계와 정수형의 크기에 따라 계산 결과가 상이할 수 있음
- 정수형 자료형의 크기는 기계 (혹은 OS)에 따라 결정되며, 따라서 무부호형 정수와 부호형 정수 간 비교는 기계 종속적
- Implicit conversions:
- If the unsigned type has conversion rank greater than or equal to the rank of the signed type, then the operand with the signed type is implicitly converted to the unsigned type.
- e.g. 임의의 환경에서의 int 형 크기는 16-bit, long 형 크기는 32-bit라고 가정:
- −1L < 1U (1U은 signed long 형으로 형 변환)
- −1L > 1UL (−1L은 unsigned long 형으로 형 변환)
- MSB를 부호가 아닌 가중치로 평가함에 따라 -1L은 음수이지만 큰 수처럼 평가됨


# Type Conversions
- 컴퓨터프로그래밍기초
- 69
- Type Conversions
- 암묵적 형 변환 (implicit type conversions)
- 대입 연산 시 두 피연산자의 형이 서로 다를 경우 우측 피연산자 (r-value) 형이 좌측 피연산자 (l-value) 형으로 변환
- 
- 
- 
- 
- 
- 실수 값이 정수형으로 형 변환이 발생하면, 소수점 부분은 무시됨
- 배정도 부동 소수점 형 값이 단정도 부동 소수점 형으로 형 변환이 발생하면, 값이 반올림되거나 잘릴 수 있음
- 구체적인 동작은 구현 방법에 따라 정의
- int i = 256;
-     char c = 'A';    /* ASCII 코드표를 참고하면, 글자로 표현 가능한 문자들은 
-                         부호형이든 무부호형이든 양수로 표현될 수 있는 범위 (0~127)에 할당되어 있음 */
-     float f = 3.14;  /* 실수형 상수의 기본 형은 double이지만, float 형으로 형 변환 발생 */
-     c = i;  /* 0 */
-     i = c;  /* 0 */
-     i = f;  /* 3 */
-     f = i;  /* 3.00 */


# Type Conversions
- 컴퓨터프로그래밍기초
- 70
- Type Conversions
- 명시적 형 변환 (explicit type conversions)
- 
- 단일 연산자와 동일한 우선 순위
- e.g. 명시적 형 변환 사용 예:
- <stdlib.h> 헤더 파일 내에 rand, srand 함수가 정의되어 있음
-  (type-name) expression;
- unsigned long int next = 1;
-     /* rand: return pseudo-random integer on 0 ... 32,767 */
-     int rand (void)
-     {
-       next =  (next * 1103515245) + 12345;
- 
-       /* right shift by 16 bits then reduces the range to 0~32,767 */      return  (unsigned int)  (next / 65536) % 32768;
-     }
-     /* srand: set seed for rand () */
-     void srand (unsigned int seed)
-     {
-       next = seed;
-     }


# Increment and Decrement Operators
- 컴퓨터프로그래밍기초
- 71
- Increment and Decrement Operators
- 증가 연산자 (increment operator)
- 
- 감소 연산자 (decrement operator)
- 
- 전위 (prefix)연산자와 후위 (postfix)연산자의 동작 차이
- ++i;
-     i++;
--i;
-     i--;


# Increment and Decrement Operators
- 컴퓨터프로그래밍기초
- 72
- Increment and Decrement Operators
- 전위 증감 연산자는 증감을 수행하기 전 해당 값 사용
- 
- 
- 후위 증감 연산자는 증감을 수행한 뒤 해당 값 사용
- /* ++i */
-     i = i + 1;
-     return i;
- /* i++ */
-     const int temp = i;
-     i = i + 1;
-     return temp;


# Increment and Decrement Operators
- 컴퓨터프로그래밍기초
- 73
- Increment and Decrement Operators
- 전위 증가 연산자와 후위 증가 연산자의 사용 예:
- b = 3;
-     a = b++; /* a = 3, b = 4 */
-     a = b;   /* a = 4, b = 4 */
-     a = ++b; /* a = 5, b = 5 */


# Increment and Decrement Operators
- 컴퓨터프로그래밍기초
- 74
- Increment and Decrement Operators
- 증감 연산자 사용 예 1:
- squeeze 함수는 사용자 정의 함수
- /* squeeze: delete all c from s */
-     void squeeze (char s[], int c)
-     {
-       int i, j;
-       for  (i = j = 0; s[i] != '\0'; ++i) {
-         if  (s[i] != c)
-           s[j++] = s[i];
-       }
-       s[j] = '\0';
-     }


# Increment and Decrement Operators
- 컴퓨터프로그래밍기초
- 75
- Increment and Decrement Operators
- 증감 연산자 사용 예 2:
- <string.h> 헤더 파일 내에 strcat 함수가 정의되어 있음
- /* strcat: concatenate t to end of s; s must be big enough */
-     void strcat (char s[], char t[])
-     {
-       int i, j;
-       i = j = 0;
-       while  (s[i] != '\0') /* find end of s */
-         ++i;
-       while  ( (s[i++] = t[j++]) != '\0') {} /* copy t */
-     }


# Bitwise Operators
- 컴퓨터프로그래밍기초
- 76
- Bitwise Operators
- 피연산자가 정수형일 때 적용 가능하며, 부호형 피연산자는 시프트 연산 (shift) 시 기계에 따라 결과가 다름
- &   (AND)
- |   (OR)
- ^   (Exclusive OR)
- <<  (Left shift)
- 연산자의 오른쪽 항은 항상 양의 정수여야 하며, 오른쪽 비트는 0으로 채워짐 (logical shift)
- >>  (Right shift)
- 연산자의 오른쪽 항은 항상 양의 정수여야 하며, 왼쪽 비트는 무부호형일 경우 0 (logical shift),부호형일 경우 MSB의 값으로 채워짐 (arithmetic shift)
- ~	   (1’s complement)


# Bitwise Operators
- 컴퓨터프로그래밍기초
- 77
- Bitwise Operators
- 비트 연산자 사용 예 1:
- #include <stdio.h>
-     int main (void)
-     {
-       /* a = 5, 0000 0101,
-          b = 9, 0000 1001 */
-       unsigned char a = 5, b = 9;
- 
-       printf ("a & b = %d\n", a & b);    /* 0000 0001 */
-       printf ("a | b = %d\n", a | b);    /* 0000 1101 */
-       printf ("a ^ b = %d\n", a ^ b);    /* 0000 1100 */
-       printf ("~a = %d\n", a = ~a);      /* 1111 1010 */
-       printf ("b << 1 = %d\n", b << 1);  /* 0001 0010 */
-       printf ("b >> 1 = %d\n", b >> 1);  /* 0000 0100 */
- 
-       return 0;
-     }
- a & b  = 1
- a | b  = 13
- a ^ b  = 12
- ~a     = 250
- b << 1 = 18
- b >> 1 = 4


# Bitwise Operators
- 컴퓨터프로그래밍기초
- 78
- Bitwise Operators
- 비트 연산자 사용 예 2:
- #include <stdio.h>
-     int main (void)
-     {
-       /* x = 248, 1111 1000 */
-       unsigned char x = 248;
-       /* mask operation example */
-       printf ("x & 077 = %d\n", x & 077);    /* 0011 1000 */
-       /* set operation example */
-       printf ("x | 07 = %d\n", x | 07);      /* 1111 1111 */
- 
-       printf ("x & ~077 = %d\n", x & ~077);  /* 1100 0000 */
-       /* 
-        * 0x300, which assumes that x is a 8-bit quantity
-        * ~077 is independent of word length
-        * => better than 0x300
-        */
-       return 0;
-     }
- x & 077  = 56
- x | 07   = 255
- x & ~077 = 192


# Bitwise Operators
- 컴퓨터프로그래밍기초
- 79
- Bitwise Operators
- 비트 연산자 사용 예 3:
- x: 0110 1101
- p: 4
- n: 3
- p + 1 − n = 2
- x >> 2 = 0001 10112
- ~0 << n = ... 1111 10002
- ~ (... 1111 1000) = ... 0000 01112
- /* getbits: get n bits from position p */
-     unsigned getbits (unsigned x, int p, int n)
-     {
-       return  (x >>  (p + 1 - n)) & ~ (~0 << n);
-     }


# Assignment Operators and Expressions
- 컴퓨터프로그래밍기초
- 80
- Assignment Operators and Expressions
- 지정 연산자 (assignment operators)
- 
- 
- 
- op= 형태를 갖는 연산자들
- +, −, *, /, %, <<, >>, &, ^, |
- 부정 (~) 연산자는 사용할 수 없음
- 
- 지정 연산자 사용 시 양변의 수식이 같은지 확인할 필요 없음
- expr1 op= expr2;
-     /* expr1 op= expr2 is equivalent to expr1 = expr1 op expr2 */
-     expr1 = expr1 op expr2;
- 
-     i += 2; /* i = i + 2 */
- yyval[yypv[p3+p4] + yypv[p1]] += 2;
-     yyval[yypv[p3+p4] + yypv[p1]] = yyval[yypv[p3+p4] + yypv[p1]] + 2;


# Assignment Operators and Expressions
- 컴퓨터프로그래밍기초
- 81
- Assignment Operators and Expressions
- 지정 연산자 (assignment operators)  (Cont’d)
- 산술 연산자보다 우선 순위가 낮음
- 
- 
- 
- 관계 연산자보다 우선 순위가 낮음
- x *= y + 1;
-     /* 
-      * 1. x *=  (y + 1)
-      * 2. x = x *  (y + 1)
-      */
- if  (x >>= 3 != 0) { /* do something */ }
-     /* 
-      * 1. x >>=  (3 != 0)
-      * 2. x = x >>  (3 != 0)
-      */


# Assignment Operators and Expressions
- 컴퓨터프로그래밍기초
- 82
- Assignment Operators and Expressions
- 지정 연산자 사용 예 1:
- bitcount 함수는 사용자 정의 함수
- /* bitcount: count 1 bits in x */
-     int bitcount (unsigned x)
-     {
-       int b;
-       for  (b = 0; x != 0; x >>= 1) {
-         if  (x & 01)
-           ++b;
-       }
-       return b;
-     }


# Assignment Operators and Expressions
- 컴퓨터프로그래밍기초
- 83
- Assignment Operators and Expressions
- 지정 연산자 사용 예 2:
- bitcount 함수는 사용자 정의 함수
- #include <stdio.h>
-     /* bitcount: faster version of the bitcount */
-     void bitcount (unsigned x)
-     {
-       int count;
-       for  (count = 0; x; ++count)
-         x &=  (x - 1);
-       printf ("count: %d\n", count);
-     }


# Conditional Expressions
- 컴퓨터프로그래밍기초
- 84
- Conditional Expressions
- 삼항 연산자 (ternary operator)
- 
- 
- 
- 
- 표현식이 사용될 수 있는 곳이라면 어디든 사용 가능
- expr1 ? expr2 : expr3;
-     
-     if  (a > b)
-       c = a;
-     else
-       c = b;                c =  (a > b) ? a : b;


# Conditional Expressions
- 컴퓨터프로그래밍기초
- 85
- Conditional Expressions
- 삼항 연산자 (ternary operator)  (Cont’d)
- 
- expr2와 expr3의 형이 다른 경우, 형 변환 법칙 적용
- 아래 표현식에서 n은 int 형, f는 float 형이라고 가정하면, 해당 식은 조건 결과와 상관 없이 float 형으로 평가됨
- 
- 삼항 연산자의 우선순위는 매우 낮지만, 구조를 명확히 하기 위해 각 표현식에 괄호를 사용하는 것을 추천
-  (n > 0) ? f : n;
- expr1 ? expr2 : expr3;


# Conditional Expressions
- 컴퓨터프로그래밍기초
- 86
- Conditional Expressions
- 삼항 연산자 사용 예 1:
- int n = 24;
-     int i;
- 
-     /*
-     can be replace this for-statement with ternary operator:
-     for  (int i = 1; i <= n; ++i) {
-       if  (! (i % 10) || i == n)
-         printf ("%2d\n", i);
-       else
-         printf ("%2d ", i);
-     }
-     */
-     for  (int i = 1; i <= n; ++i)
-       printf ("%2d%c", i,  (! (i % 10) || i == n) ? '\n' : ' ');
- 1  2  3  4  5  6  7  8  9 10
- 11 12 13 14 15 16 17 18 19 20
- 21 22 23 24


# Conditional Expressions
- 컴퓨터프로그래밍기초
- 87
- Conditional Expressions
- 삼항 연산자 사용 예 2:
- int n = 2;
- 
-     /*
-     can be replace this else-if statement with ternary operator:
-     if  (n == 1)
-       printf ("You have %d item\n", n);
-     else
-       printf ("You have %d items\n", n);
-     */
-     printf ("You have %d item%c\n", n,  (n == 1) ? '\0' : 's');
- You have 2 items


# Precedence and Order of Evaluation
- 컴퓨터프로그래밍기초
- 88
- Precedence and Order of Evaluation
- 평가 순서에 의존하여 프로그래밍하는 것은 권장하지 않음
- 가독성을 해치지 않는 선에서 괄호를 적극적으로 사용할 것
- 
- 자주 사용되는 규칙들
- 산술 연산자는 관계, 논리 연산자보다 우선 순위가 높음
- 지정 연산자는 관계, 논리 연산자보다 우선 순위가 낮음


# Precedence and Order of Evaluation
- 컴퓨터프로그래밍기초
- 89
- Precedence and Order of Evaluation
- Brian W. Kernighan and Dennis M. Ritchie. 1988. The C Programming Language  (2nd. ed.). Prentice Hall Professional Technical Reference, USA.


# Precedence and Order of Evaluation
- 컴퓨터프로그래밍기초
- 90
- Precedence and Order of Evaluation
- 연산의 우선순위와 결합법칙 (associativity)
- 아직 결합되지 않은 표현식 중에서 우선 순위가 높은 연산자가 포함된  표현식을 찾음
- 찾은 표현식을 결합 방향에 맞게 결합
- 아직 결합되지 않은 표현식이 존재하면 (처리해야 할 항의 개수가 2개 이상 존재한다면), 1번 과정으로 돌아감
- 결합된 표현식들에 대한 평가 수행
- x++ * y * z + w++;
-     /*
-      * 1. [1] ++ 연산자 우선순위가 가장 높음 
-      * 2. [2] ++ 연산자의 결합 방향은 오른쪽에서 왼쪽 방향이므로,
-      *        x++ * y * z +  (w++)
-      *         (x++) * y * z +  (w++)
-      * 3. [1] * 연산자의 우선순위가 다음으로 높음
-      * 4. [2] * 연산자의 결합 방향은 왼쪽에서 오른쪽 방향이므로, 
-      *         ( (x++) * y) * z +  (w++)
-      *         ( ( (x++) * y) * z) +  (w++)
-      * 5. [1] + 연산자의 우선순위가 다음으로 높음
-      * 6. [2] + 연산자의 결합 방향은 왼쪽에서 오른쪽 방향이므로, 
-      *         ( ( ( (x++) * y) * z) +  (w++))
-      */


# Precedence and Order of Evaluation
- 컴퓨터프로그래밍기초
- 91
- Precedence and Order of Evaluation
- C언어의 대부분 연산자들은 피연산자를 평가할 때 정해진 순서가 없음 (unsequenced)
- 평가 순서는 컴파일러에 구현된 내용에 따라 결정됨 (unspecified)
- 구현된 내용에 따라 다른 결과 반환
- 평가 순서에 영향을 받는 표현식을 사용하지 않도록 주의해야 함
- 
- 평가 순서가 정해진 연산자들
- 논리 연산자 (&&, ||)
- 쉼표 연산자 (,)
- 삼항 연산자 (?:)


# Precedence and Order of Evaluation
- 컴퓨터프로그래밍기초
- 92
- Precedence and Order of Evaluation
- 평가 순서에 따라 결과가 바뀔 수 있는 표현식
- /* Case 1.
-      * 전역 변수에 대한 side effect가 있는 함수일 경우,     * 결과가 달라질 수 있음
-      * e.g. extern int a = 4, b = 5, c = 6;
-      *   f (): 모든 global variable의 값을 1 더한 뒤,     *        모든 global variable의 값을 더해서 반환
-      *   g (): 모든 global variable의 값을 2 곱한 뒤,
-      *        모든 global variable의 값을 더해서 반환
-      */
-     int x = f () + g ();
-     /* Case 2.
-      * ++n;
-      * printf ("%d %d\n", n, power (2, n));
-      */
-     int n = 5;
-     printf ("%d %d\n", ++n, power (2, n));
- /* Case 3. */
-     int i = 0;
-     a[i] = i++;
-     /* Case 4. */
-     int i = 2;
-     i + i + ++i;  /* 2 + 2 + 3?  3 + 3 + 3? */
-     i + i + i++;  /* 2 + 2 + 2?  3 + 3 + 2? */

