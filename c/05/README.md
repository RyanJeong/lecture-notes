# 컴퓨터프로그래밍기초
- 컴퓨터프로그래밍기초
- Pointers and Arrays


# Contents
- 컴퓨터프로그래밍기초
- 2
- Contents
- Chapter 1 - A Tutorial Introduction
- Chapter 2 - Types, Operators and Expressions
- Chapter 3 - Control Flow
- Chapter 4 - Functions and Program Structure
- Chapter 5 - Pointers and Arrays
- Chapter 6 - Structures
- Chapter 7 - Input and Output
- Chapter 8 - The UNIX System Interface


# Goals of This Chapter
- 컴퓨터프로그래밍기초
- 3
- Goals of This Chapter
- 포인터와 주소의 개념 이해
- 단항 연산자 *, &
- 포인터와 배열의 관계
- 포인터 배열과 2차원 배열의 차이
- 커맨드 라인 전달인자 사용법
- 포인터 함수


# Pointers and Addresses
- 컴퓨터프로그래밍기초
- 4
- Pointers and Addresses
- 메모리의 구성
- 메모리 셀(cell)의 나열
- 셀 하나는 한 바이트를 표현할 수 있음
- 각 셀에는 주소가 있음
- 메모리 셀 하나는 char 형(1 byte)을 표현할 수 있음
- 인접한 메모리 셀 두 개는 short 형(2 bytes)을 표현할 수 있음
- 인접한 메모리 셀 네 개는 int 형(4 bytes)을 표현할 수 있음
- 포인터는 메모리 셀 집합을 가리킴
- 메모리 셀 집합이 두 개 이상의 메모리 셀로 구성되어 있다면, 가장 낮은 번지의 주소를 해당 메모리 셀 집합의 대표 주소로 사용
- 0x08AF53DC
- 0x08AF53DD
- 0x08AF53DE
- 0x08AF53DF
- 0x08AF53E0
- 0x08AF53E1
- 0x08AF53E2
- 0x08AF53E3


# Pointers and Addresses
- 컴퓨터프로그래밍기초
- 5
- Pointers and Addresses
- 메모리의 구성(Cont’d)
- e.g. char 형 변수 c와 char 형 변수의 주소를 가리키는 포인터 p
- 
- 
- 변수 c와 포인터 변수 p는 초기화되지 않음
- 
- 
- 
- 
- 포인터 변수 p는 변수 c를가리킴
- char c;
- char *p;
- 
- 
- 
- 
- 
- 
- 
- 
- /* unary operator & gives the address of an object */p = &c;
- 0x08AF53DC
- 0x08AF53DD
- 0x08AF53DE
- 0x08AF53DF
- 0x08AF53E0
- 0x08AF53E1
- 0x08AF53E2
- 0x08AF53E3
- 0x08AF53DC
- 0x08AF53DD
- 0x08AF53DE
- 0x08AF53DF
- 0x08AF53E0
- 0x08AF53E1
- 0x08AF53E2
- 0x08AF53E3


# Pointers and Addresses
- 컴퓨터프로그래밍기초
- 6
- Pointers and Addresses
- 메모리 셀 집합에 유의미한 값이 기록되면, 해당 셀은 객체(object)
- 객체에 이름을 사용해서 접근이 가능하다면, 해당 객체는 변수
- 단항 연산자 &
- 객체의 주소 반환
- 표현식, 상수, 레지스터 변수에는 사용 불가
- 단항 연산자 *
- 포인터 변수가 가리키는 객체에 간접 참조(indirection or dereferencing)


# Pointers and Addresses
- 컴퓨터프로그래밍기초
- 7
- Pointers and Addresses
- 포인터 선언 방법과 연산자 &, * 사용 방법
- 
- 
- 표현식 *ip는 int 형을 의미
- ip는 int 형을 가리키는 포인터
- 
*dp 변수와 atof 함수는 double 형을 의미
- atof 함수의 매개변수는 char 형을 가리키는 포인터
- int x = 1, y = 2, z[10];
- int *ip;  /* ip is a pointer to int */
- double *dp, atof(char *);


# Pointers and Addresses
- 컴퓨터프로그래밍기초
- 8
- Pointers and Addresses
- 포인터 선언 방법과 연산자 &, * 사용 방법 (Cont’d)
- 
- 
- 포인터는 선언 시 사용된 자료형을 가리킴
- 만약 포인터 변수 ip가 변수 x를 가리키는 포인터라면, *ip는 문법상 x가 등장 가능한 곳에 등장할 수 있음:
- 
- The syntax of the declaration for a variable mimics the syntax of expressions in which the variable might appear:
- int x = 1, y = 2, z[10];
- int *ip;  /* ip is a pointer to int */
- /* x = x + 10 */
*ip = *ip + 10;


# Pointers and Addresses
- 컴퓨터프로그래밍기초
- 9
- Pointers and Addresses
- 포인터 선언 방법과 연산자 &, * 사용 방법 (Cont’d)
- int x = 1, y = 2, z[10];
- int *ip;  /* ip is a pointer to int */


# Pointers and Addresses
- 컴퓨터프로그래밍기초
- 10
- Pointers and Addresses
- 포인터 선언 방법과 연산자 &, * 사용 방법 (Cont’d)
- int x = 1, y = 2, z[10];
- int *ip;  /* ip is a pointer to int */
- ip = &x;  /* ip now points to x */


# Pointers and Addresses
- 컴퓨터프로그래밍기초
- 11
- Pointers and Addresses
- 포인터 선언 방법과 연산자 &, * 사용 방법 (Cont’d)
- int x = 1, y = 2, z[10];
- int *ip;  /* ip is a pointer to int */
- ip = &x;  /* ip now points to x */
- y = *ip;  /* y is now 1 */


# Pointers and Addresses
- 컴퓨터프로그래밍기초
- 12
- Pointers and Addresses
- 포인터 선언 방법과 연산자 &, * 사용 방법 (Cont’d)
- int x = 1, y = 2, z[10];
- int *ip;  /* ip is a pointer to int */
- ip = &x;  /* ip now points to x */
- y = *ip;  /* y is now 1 */
*ip = 0;  /* x is now 0 */


# Pointers and Addresses
- 컴퓨터프로그래밍기초
- 13
- Pointers and Addresses
- 포인터 선언 방법과 연산자 &, * 사용 방법 (Cont’d)
- int x = 1, y = 2, z[10];
- int *ip;  /* ip is a pointer to int */
- ip = &x;  /* ip now points to x */
- y = *ip;  /* y is now 1 */
*ip = 0;  /* x is now 0 */
- ip = &z[0]; /* ip now points to z[0] */


# Pointers and Addresses
- 컴퓨터프로그래밍기초
- 14
- Pointers and Addresses
- 단항 연산자 &와 *의 연산자 우선순위는 산술 연산자보다 더 높음:
- 
- 
- 
- 
- 증감 연산자(++ or --)는 간접참조 연산자(*) 와 연산자 우선순위가 같음
- 결합 방향이 오른쪽에서 왼쪽
- 전위증가연산자를 사용한 표현식은 괄호 필요 없음
- 후위증가연산자는 괄호 필요
- 괄호를 사용하지 않으면 포인터 변수가 저장하고 있는 주소 값을 증가시킴
- 포인터 주소 연산
- int x = 10, y = 20;
- int *ip = &x;
- y = *ip + 1;  /* y is now 11 */
*ip += 1;     /* x is now 11 */
- ++*ip;        /* x is now 12 */
- (*ip)++;      /* x is now 13 */


# Pointers and Addresses
- 컴퓨터프로그래밍기초
- 15
- Pointers and Addresses
- 포인터 변수의 복사:
- 
- 
- 
- 포인터 변수도 값을 보관하는 일종의 변수이며, 간접 참조 연산자(*) 없이 사용할 경우 주소 값을 다루는 변수임
- iq는 엉뚱한 곳을 가리키는 포인터
- 자동 변수이기 때문에 쓰레기 값이 들어 있음
- 대입문 이후에 iq는 ip의 주소값을 보관하고 있는 변수
- iq는 ip을 가리키는 포인터
- int *ip, *iq, i;
- i = 3;
- ip = &i;
- iq = ip;


# Pointers and Function Arguments
- 컴퓨터프로그래밍기초
- 16
- Pointers and Function Arguments
- C 언어는 함수에 전달인자를 넘겨줄 때, 값을 전달함(call by value)
- 호출된(callee) 함수에서 호출한(caller) 함수의 변수를 직접 수정할 수 없음
- 포인터를 사용하면 호출된 함수에서 호출한 함수의 변수를 간접적으로 수정 가능
- /* call by value */
- void swap(int a, int b)
- {
-   int temp;
-   temp = a;
-   a = b;
-   b = temp;
- }
- /* call by address */
- void swap(int *a, int *b)
- {
-   int temp;
-   temp = *a;
-   *a = *b;
-   *b = temp;
- }


# Pointers and Function Arguments
- 컴퓨터프로그래밍기초
- 17
- Pointers and Function Arguments
- Call by value vs. call by address
- 함수 전달인자에 포인터를 넘겨주면 호출된 함수에서 호출한 함수 변수에 간접적으로 접근 가능
- #include <stdio.h>
- /* call by value */
- void swap1(int a, int b)⋯
- /* call by address */
- void swap2(int *a, int *b)⋯
- int main(void)
- {
-   int a, b;
-   a = 3;
-   b = 4;
-   printf("Before calling function swap1, a: %d, b : %d\n", a, b);
-   swap1(a, b);
-   printf("After calling function swap1, a: %d, b : %d\n", a, b);
-   printf("Before calling function swap2, a: %d, b : %d\n", a, b);
-   swap2(&a, &b);
-   printf("After calling function swap2, a: %d, b : %d\n", a, b);
-   return 0;
- }


# Pointers and Function Arguments
- 컴퓨터프로그래밍기초
- 18
- Pointers and Function Arguments
- getint 함수
- 사용자 정의 함수
- 사용자로부터 입력 받은 숫자 문자열을 정수 값으로 바꾸어 반환
- 함수는 문자열로부터 정수를 발견하면 해당 정수 값을 반환하고, 사용자로부터 입력된 문자열이 없다면 EOF 반환
- 정수 반환 경로와 EOF 반환 경로는 구분되어야 함
- 정수와 EOF의 반환 경로를 구분하지 않는다면, 사용자가 EOF를 의미하는 정수(e.g. −1)를 입력했을 때 올바른 값 입력임에도 불구하고 해당 값을 EOF로 간주할 수 있음(대부분의 환경에서 EOF는 −1로 정의되어 있는 상수)
- 포인터를 사용해 정수는 포인터로 간접 참조하고 EOF는 반환문을 사용하면 반환 경로를 서로 구분할 수 있음


# Pointers and Function Arguments
- 컴퓨터프로그래밍기초
- 19
- Pointers and Function Arguments
- getint 함수 (Cont’d)
- getint 함수는 scanf 함수와비슷한 형태를 가짐
- 7장에서 자세히 다룰 예정
- 경우에 따른 반환값
- EOF 입력 시 EOF 반환
- 숫자 아닌 값 입력 시 0 반환
- 유효한 숫자 값 입력 시 양수 반환
- #include <ctype.h>
- #include <stdio.h>
- /* getint: get next integer from input into *pn */
- int getint(int *pn)
- {
-   int c, sign, getch(void);
-   void ungetch(int);
-   /* skip white space */
-   while (isspace(c = getch())) {}
-   if (!isdigit(c) && c != EOF && c != '+' && c != '-') {
-     ungetch(c); /* it is not a number */
- 
-     return 0;
-   }
-   sign = (c == '-') ? -1 : 1;
-   if (c == '+' || c == '-')
-     c = getch();
-   for (*pn = 0; isdigit(c); c = getch())
-     *pn = 10 * *pn + (c - '0');
-   *pn *= sign;
-   if (c != EOF)
-     ungetch(c);
-   return c;
- }


# Pointers and Arrays
- 컴퓨터프로그래밍기초
- 20
- Pointers and Arrays
- C 언어에서의 포인터와 배열은 서로 밀접한 관련이 있음
- 배열 첨자 연산을 통해 얻을 수 있는 값은 포인터 연산을 통해서도 얻을 수 있음
- 보통 포인터 연산이 배열 첨자 연산에 비해 빠르지만, 초심자 입장에서 포인터 연산을 사용하기가 쉽지 않음
- 
- 
- 
- 
- 크기가 10인 int 형 배열 정의
- 메모리 상에 연속적으로 10개의 객체를 사용할 수 있는 상태
- 각 객체의 이름은 a[0], a[1], ..., a[9]
- a[i] 형태로 표현하면 배열의 i번째 요소 참조
- int a[10];


# Pointers and Arrays
- 컴퓨터프로그래밍기초
- 21
- Pointers and Arrays
- C 언어에서의 포인터와 배열은 서로 밀접한 관련이 있음 (Cont’d)
- int *pa;
- pa = &a[0];
- 
- 
- 
- 
- 
- a[0] = 1;
- a[9] = *pa;


# Pointers and Arrays
- 컴퓨터프로그래밍기초
- 22
- Pointers and Arrays
- C 언어에서의 포인터와 배열은 서로 밀접한 관련이 있음 (Cont’d)
- 포인터 변수 pa가 배열의 특정 요소를 가리키는 경우:
- pa + i는 pa가 가리키는 요소로부터 i번째 뒤(높은 메모리 주소 방향으로)에 있는 요소를 가리킴
- pa − i는 pa가 가리키는 요소로부터 i번째 앞에 있는 요소를 가리킴
- pa가 배열의 0번 요소를 가리킨다면, pa + i가 가리키는 주소값은 a[i]의 주소값과 일치
- 배열의 형(type) 또는 크기(size)와 상관 없이 항상 동일하게 동작됨을 보장(consistency)


# Pointers and Arrays
- 컴퓨터프로그래밍기초
- 23
- Pointers and Arrays
- C 언어에서의 포인터와 배열은 서로 밀접한 관련이 있음 (Cont’d)
*pa, *(pa + 1), *(pa + 2)
- 
- 
- 
- 
- 
- pa + 1은 pa가 가리키는 요소의 다음 요소를 가리킴
- pa + i는 pa가 가리키는 요소로부터 i번째 뒤에 있는 요소를 가리킴


# Pointers and Arrays
- 컴퓨터프로그래밍기초
- 24
- Pointers and Arrays
- C 언어에서의 포인터와 배열은 서로 밀접한 관련이 있음 (Cont’d)
- 배열 이름은 배열에서의 0번째 요소를 가리킴
- 
- 배열 이름을 활용하면 배열 첨자 연산을 포인터 연산 행태로 바꿀 수 있음:
- 
- C 언어는 a[i] 식을 계산할 때 즉시 *(a + i) 형태로 바꿈
- 두 형태는 동일한 표현
- a[i]와 *(a + i)에 각각 & 연산자를 사용하면 서로 동일한 주소 출력:
- &a[i]의 결과는 a + i와 동일
- &*(a + i)의 결과는 a + i와 동일
- pa = a;  /* pa = &a[0]; */
*(a + i);  /* a[i] */


# Pointers and Arrays
- 컴퓨터프로그래밍기초
- 25
- Pointers and Arrays
- 배열 이름을 전달인자로 넘겨주면, 배열 0번째 요소의 주소값을 넘겨주는 것과 동일
- strlen 함수의 char 형을 가리키는 포인터 변수 s에 배열 이름의 주소가 복사됨
- /* strlen: return length of s */
-     int strlen(char s[])
-     {
-       int i;
-       i = 0;
-       while (s[i] != '\0')
-         ++i;
-       return i;
-     }
- 
- strlen("hello, world");    /* string constant */
- strlen(array);             /* char array[100]; */
- strlen(ptr);               /* char *ptr; */


# Pointers and Arrays
- 컴퓨터프로그래밍기초
- 26
- Pointers and Arrays
- 다음 두 매개변수 형태는 동일한 표현
- 
- 두 표현 모두 포인터 매개변수를 사용하겠다는 의미
- 두 번째 표현을 더 선호:
- 배열 이름을 전달인자로 사용하면 매개변수로 복사되는 값은 배열 원본이 아닌 배열의 0번째 요소의 주소값임
- 매개변수가 포인터임을 더 명확히 표현한 표현식은 두 번째 표현식
- 함수 내에서 배열 첨자 연산을 주로 사용한다면 주로 첫 번째 표현식을 사용함
- void foo(char s[]);
- void foo(char *s);


# Pointers and Arrays
- 컴퓨터프로그래밍기초
- 27
- Pointers and Arrays
- 배열 첨자 값에 음수를 사용하면 해당 요소를 기준으로 뒤로 참조
- 배열의 경계를 넘어가면 결과값 알 수 없음
- #include <stdio.h>
- int main(void)
- {
-   int a[] = {1, 2, 3};
-   int *p = a + 2;
-   /* 2 1 ???? */
-   printf("%d %d %d\n", p[-1], p[-2], p[-3]);
-   return 0;
- }


# Address Arithmetic
- 컴퓨터프로그래밍기초
- 28
- Address Arithmetic
- 기본적인 주소 연산(포인터) 형태
- 포인터 변수 p가 배열의 한 요소를 가리키는 상태일 때:
- p++ 또는 ++p 식은 포인터 변수 p가 현재 요소를 기준으로 다음 요소를 가리킴
- p += i 식은 포인터 변수 p가 현재 요소를 기준으로 i번째 다음 요소를 가리킴
- 빼기 연산은 포인터 변수가 가리키는 특정 요소를 기준으로 이전 요소를 가리킴
- 요소 하나가 증가될 때마다 포인터 변수 선언 시 사용한 자료형의 크기만큼 주소 번지가 증가함(주소 연산의 일관성(consistency)를 지키는 중요한 규칙)
- 포인터, 배열, 주소 연산의 통합은 C 언어의 가장 큰 강점 중 하나


# Address Arithmetic
- 컴퓨터프로그래밍기초
- 29
- Address Arithmetic
- 기초적인 저장소 할당기
- alloc 함수
- 사용자 정의 함수
- n개의 문자를 연속적으로 저장할 수 있는 주소를 가리키는 포인터 주소 반환
- 함수를 호출하면 함수 호출 측은 n개의 문자를 저장할 수 있는 공간 할당
- afree 함수
- 사용자 정의 함수
- alloc 함수에서 할당한 공간을 해제해 나중에 재사용할 수 있도록 함
- afree 함수는 반드시 alloc 함수 호출의 역순으로 수행되어야 함(rudimentary)
- alloc 함수와 afree 함수는 스택(stack, or first-in, first-out)을 통해 관리됨
- 표준 라이브러리 함수에서 유사한 기능을 수행하는 함수 제공:
- malloc 함수와 free 함수(<stdlib.h> 헤더 파일 필요)


# Address Arithmetic
- 컴퓨터프로그래밍기초
- 30
- Address Arithmetic
- 기초적인 저장소 할당기 (Cont’d)
- alloc 함수는 allocbuf 배열로부터 공간 할당 후 해당 공간을 가리키는 주소 반환
- allocbuf 배열은 alloc 함수와 afree 함수에서만 사용 가능(private):
- 저장 공간을 할당받을 때, 해당 공간을 가리키는 주소만 받으면 되므로 allocbuf 배열은 다른 곳에서 접근할 필요가 없음
- static 선언을 사용하면 다른 곳에서 안 보이게 감출 수 있음
- 실제 malloc 함수를 사용하거나 운영체제에 공간 할당을 요청하면 사용 가능한 메모리 공간의 주소만을 전달받음


# Address Arithmetic
- 컴퓨터프로그래밍기초
- 31
- Address Arithmetic
- 기초적인 저장소 할당기 (Cont’d)
- allocp 포인터는 allocbuf 배열에서 할당 요청 시 반환할 공간의 시작 주소를 가리키는 포인터
- alloc 함수가 호출되면 allocp 포인터가 가리키는 위치를 기준으로 allocbuf 배열 안에 새로 할당되어야 할 공간이 충분한지 확인
- 공간이 충분하면, allocp가 가리키는 주소를 그대로 반환한 뒤, 새로 할당한 공간 크기만큼 allocp에 더함
- 공간이 부족하면 0 반환
- afree 함수는 전달받은 매개변수의 주소값이 유효하다면 allocp 값으로 대치 (rudimentary)


# Address Arithmetic
- 컴퓨터프로그래밍기초
- 32
- Address Arithmetic
- 기초적인 저장소 할당기 (Cont’d)
- 0x08AF1EE8
- 0x08AF1EE9
- 0x08AF1EEA
- 0x08AF1EEB
- 0x08AF1EEC
- 0x08AF1EED
- 0x08AF1EEE
- 0x08AF1EEF
- 0x08AFB888


# Address Arithmetic
- 0x08AF1EE8
- 0x08AF1EE9
- 0x08AF1EEA
- 0x08AF1EEB
- 0x08AF1EEC
- 0x08AF1EED
- 0x08AF1EEE
- 0x08AF1EEF
- 0x08AFB888
- 컴퓨터프로그래밍기초
- 33
- Address Arithmetic
- 기초적인 저장소 할당기 (Cont’d)
- p = alloc(7);


# Address Arithmetic
- 0x08AF1EE8
- 0x08AF1EE9
- 0x08AF1EEA
- 0x08AF1EEB
- 0x08AF1EEC
- 0x08AF1EED
- 0x08AF1EEE
- 0x08AF1EEF
- 0x08AFB888
- 컴퓨터프로그래밍기초
- 34
- Address Arithmetic
- 기초적인 저장소 할당기 (Cont’d)
- afree(p + 2);


# Address Arithmetic
- 컴퓨터프로그래밍기초
- 35
- Address Arithmetic
- 기초적인 저장소 할당기 (Cont’d)
- allocp 포인터 변수는 allocpbuf 배열의 시작 주소를 가리킴
- allocbuf 배열의 공간 여부에 따라사용할 수 있는 공간 주소 또는0을 반환
- 포인터에서의 0은 C 언어에서유효하지 않은 주소임을 의미
- <stdio.h> 헤더 파일 안에 NULL정의되어 있음
- NULL = '\0' = 0
- #define ALLOCSIZE 10000  /* size of available space */
- static char allocbuf[ALLOCSIZE];  /* storage for alloc */
- static char *allocp = allocbuf;   /* next free position */
- /* return pointer to n characters */
- char *alloc(int n) 
- {
-   /* it fits */
-   if (allocbuf + ALLOCSIZE - allocp >= n) { 
-     allocp += n;
-     /* old p */
-     return allocp - n; 
-   } else {
-     /* not enough room */
-     return 0;
-   }
- }
- /* free storage pointed to by p */
- void afree(char *p) 
- {
-   if (p >= allocbuf && p < allocbuf + ALLOCSIZE)
-     allocp = p;
- }


# Address Arithmetic
- 컴퓨터프로그래밍기초
- 36
- Address Arithmetic
- 기초적인 저장소 할당기 (Cont’d)
- 포인터 변수 p와 q가 동일한 배열을가리키고 있을 때, 두 포인터는서로 비교할 수 있음:
- 포인터 p가 포인터 q보다 배열의 앞쪽 요소를 가리킬 경우, 표현식 p < q의 결과는 참(p의 주소 번지가 더 낮음)
- 서로 다른 대상을 가리키는포인터 변수 간 비교는 결과를 알 수 없음
- #define ALLOCSIZE 10000  /* size of available space */
- static char allocbuf[ALLOCSIZE];  /* storage for alloc */
- static char *allocp = allocbuf;   /* next free position */
- /* return pointer to n characters */
- char *alloc(int n) 
- {
-   /* it fits */
-   if (allocbuf + ALLOCSIZE - allocp >= n) { 
-     allocp += n;
-     /* old p */
-     return allocp - n; 
-   } else {
-     /* not enough room */
-     return 0;
-   }
- }
- /* free storage pointed to by p */
- void afree(char *p) 
- {
-   if (p >= allocbuf && p < allocbuf + ALLOCSIZE)
-     allocp = p;
- }


# Address Arithmetic
- 컴퓨터프로그래밍기초
- 37
- Address Arithmetic
- 포인터 뺄셈
- 포인터 변수 p와 q가 같은 배열을 가리키면서 관계 p < q가 성립할 때, q - p + 1은 포인터 변수 p가 가리키는 요소부터 포인터 변수 q가 가리키는 요소까지의 요소들의 개수를 계산할 수 있음
- p
- q


# Address Arithmetic
- 컴퓨터프로그래밍기초
- 38
- Address Arithmetic
- 포인터 뺄셈을 적용한 strlen 함수
- 포인터 변수 p는 널('\0') 문자를 만날 때까지 반복문 수행
- 반복문이 끝나면 포인터 변수 p는 널 문자가 위치한 주소 번지를 가리킴
- 포인터 변수 p에 문자열 시작 주소 번지를 가리키는 포인터 변수 s를 빼면 널 문자를 제외한 문자열의 실제 길이를 구할 수 있음
- /* strlen: return length of string s */
- int strlen(char *s)
- {
-   char *p = s;
-   while (*p != '\0')
-     p++;
-   return p - s;
- }
- /* strlen: return length of s */
-     int strlen(char s[])
-     {
-       int i;
-       i = 0;
-       while (s[i] != '\0')
-         ++i;
-       return i;
-     }


# Address Arithmetic
- 컴퓨터프로그래밍기초
- 39
- Address Arithmetic
- 유효한 포인터 연산들
- 같은 형으로 선언된 포인터 간 대입(assignment)
- 포인터에 정수 덧셈 또는 뺄셈
- 같은 배열을 가리키는 두 포인터 변수 간 뺄셈 또는 비교
- 포인터 변수에 0(NULL, '\0')으로 대입 또는 비교
- 위 연산들을 제외한 모든 포인터 연산은 유효하지 않음(illegal)


# Character Pointers and Functions
- 컴퓨터프로그래밍기초
- 40
- Character Pointers and Functions
- C 언어에서 문자열을 함수의 전달인자로 넘겨줄 때 문자열 전체를 넘겨주는 것이 아닌 포인터를 넘겨줌
- 
- printf 함수는 전달인자의 시작 주소를 전달받음
- 문자열 "Hello, World!"는 문자 배열
- 문자열 마지막에는 끝을 의미하는 널 문자가 포함됨
- 프로그램은 널 문자를 통해 해당 문자열이 어디에서 끝나는지 구분할 수 있음
- 순수 문자열 길이보다 1만큼 큰 메모리 공간 필요
- printf("Hello, World");


# Character Pointers and Functions
- 컴퓨터프로그래밍기초
- 41
- Character Pointers and Functions
- 보통 문자열 상수를 함수 전달인자로 바로 사용하지 않고, 포인터 변수를 하나 선언해서 사용
- 
- pmessage 변수는 문자열을 복사 대입하는 것이 아닌, 문자열 상수의 시작 주소를 보관
- C 언어는 문자열을 처리하는 연산자 제공하지 않음
- char *pmessage;
- pmessage = "now is the time";


# Character Pointers and Functions
- 컴퓨터프로그래밍기초
- 42
- Character Pointers and Functions
- 아래 두 선언식은 매우 큰 차이가 있음
- 
- 
- 
- 
- amessage는 배열
- 문자열과 널 문자를 보관할 수 있는 공간이 할당되며, 문자열의 일부를 수정할 수 있지만 크기는 변경할 수 없음
- pmessage는 문자열 상수를 가리키는 포인터
- 값 변경에 대한 동작은 정의되어 있지 않음
- char *pmessage = "now is the time";
- char amessage[] = "now is the time";


# Character Pointers and Functions
- 컴퓨터프로그래밍기초
- 43
- Character Pointers and Functions
- 문자열을 복사하는 strcpy 함수
- C 언어는 문자열을 처리하는 연산자 제공하지 않음
- 반복문을 사용해 각 문자들을 일일이 복사해야 함
- /* strcpy: copy t to s; array subscript version */
- void strcpy(char *s, char *t)
- {
-   int i;
-   i = 0;
-   while ((s[i] = t[i]) != '\0')
-     i++;
- }


# Character Pointers and Functions
- 컴퓨터프로그래밍기초
- 44
- Character Pointers and Functions
- 문자열을 복사하는 strcpy 함수 (Cont’d)
- 매개변수가 전달받는 값은 각 배열의 주소 값
- 주소 값은 포인터 연산과 배열 첨자 연산 둘 다 사용 가능
- /* strcpy: copy t to s; pointer version */
- void strcpy(char *s, char *t)
- {
-   int i;
-   i = 0;
-   while ((*s = *t) != '\0') {
-     s++;
-     t++;
-   }
- }


# Character Pointers and Functions
- 컴퓨터프로그래밍기초
- 45
- Character Pointers and Functions
- 문자열을 복사하는 strcpy 함수 (Cont’d)
- C 언어에 숙련된 사람은 이전과 같은 형태의 포인터를 사용하지 않음
- C 프로그래머가 선호하는 형태의 코드는 아래와 같음
- 
- 
- 
- 
- 표준 라이브러리에 정의되어 있는 strcpy 함수는 s의 주소를 반환
- <string.h> 헤더 파일 필요
- /* strcpy: copy t to s; pointer version 2 */
- void strcpy(char *s, char *t)
- {
-   while ((*s++ = *t++) != '\0') { }
- }
- /* strcpy: copy t to s; pointer version 3 */
- void strcpy(char *s, char *t)
- {
-   while (*s++ = *t++) { }
- }


# Character Pointers and Functions
- 컴퓨터프로그래밍기초
- 46
- Character Pointers and Functions
- 문자열을 비교하는 strcmp 함수
- 사전 순으로(lexicographically) 첫 번째 매개변수가 두 번째 매개변수보다 먼저 등장할 경우 음수(-1), 같으면 0, 나중에 등장할 경우 양수(1) 반환
- /* strcmp: return <0 if s<t, 0 if s==t, >0 if s>t */
- int strcmp(char *s, char *t)
- {
-   int i;
-   for (i = 0; s[i] == t[i]; i++) {
-     if (s[i] == '\0')
-       return 0;
-   }
-   return s[i] - t[i];
- }
- int strcmp(char *s, char *t)
- {
-   while (*s == *t) {
-     if (*s == '\0')
-       return 0;
-     ++s, ++t;
-   }
-   return *s - *t;
- }


# Character Pointers and Functions
- 컴퓨터프로그래밍기초
- 47
- Character Pointers and Functions
- 포인터 변수에 간접 참조 연산자(*) 와 단항 증감 연산자(++ 또는 −−)가 같이 사용되는 경우도 있음
- 스택 연산에서 자주 사용되는 관용적인 표현
- 
- 
- 간접 참조 연산자와 단항 증감 연산자의 우선 순위는 동일하며, 결합 방향은 오른쪽에서 왼쪽
*p++ = val;  /* push val onto stack */
- val = *--p;  /* pop top of stack into val */


# Character Pointers and Functions
- 컴퓨터프로그래밍기초
- 48
- Character Pointers and Functions
- 포인터 변수에 간접 참조 연산자(*) 와 단항 증감 연산자(++ 또는 −−)가 같이 사용되는 경우도 있음 (Cont’d)
- Push
- int val = 10;
- int a[5];
- int *p = a;
- 
- 
- 
- 
- 
*p++ = val;


# Character Pointers and Functions
- 컴퓨터프로그래밍기초
- 49
- Character Pointers and Functions
- 포인터 변수에 간접 참조 연산자(*) 와 단항 증감 연산자(++ 또는 −−)가 같이 사용되는 경우도 있음 (Cont’d)
- Pop
- a[0] = 5;
- 
- 
- 
- 
- 
- 
- val = *--p;


# Pointer Arrays; Pointers to Pointers
- 컴퓨터프로그래밍기초
- 50
- Pointer Arrays; Pointers to Pointers
- 문자열을 사전 순으로 정렬하는 프로그램
- 
- 
- 
- 
- 각 행마다 문자열이 기록되어 있으며, 각 문자열의 길이는 서로 다름
- 문자열은 정수처럼 한 번에 이동하거나 비교할 수 없음
- 문자열을 구성하는 문자 수만큼 교환(swap)해야 하며, 문자열을 보관하는 문자 배열의 크기도 주어진 문자열 중에서 가장 긴 문자열 길이로 통일해야 함
- 포인터 배열을 사용하면 위 문제들을 효율적으로 해결할 수 있음
- 포인터 변수도 일종의 변수이며, 포인터 변수들로 구성된 배열을 사용할 수 있음


# Pointer Arrays; Pointers to Pointers
- 컴퓨터프로그래밍기초
- 51
- Pointer Arrays; Pointers to Pointers
- 문자열을 사전 순으로 정렬하는 프로그램 (Cont’d)
- 
- 
- 
- 
- 각 포인터에는 문자열이 저장되어 있는 문자 배열의 주소를 저장
- 문자 배열의 0번째 주소
- 문자열의 비교는 전달할 두 문자열의 주소를 strcmp 함수의 전달인자로 전달함
- 문자열의 교환은 교환할 두 문자열의 주소를 서로 교환하면 됨(swap)
- 교환할 문자 배열의 문자들을 직접 교환할 필요 없이 주소를 교환함으로써 간접적으로 교환 가능


# Pointer Arrays; Pointers to Pointers
- 컴퓨터프로그래밍기초
- 52
- Pointer Arrays; Pointers to Pointers
- 문자열을 사전 순으로 정렬하는 프로그램 (Cont’d)
- 정렬 과정
- read all the lines of input
- sort them
- print them in order
- 프로그램 작성 시 권장하는 방법은 main 함수에서 주요 동작을 수행하는 부분을 함수 단위로 분리한 뒤, 각 함수들을 main 함수에서 제어(호출)하는 것
- #include <stdio.h>
- #include <string.h>
- #define MAXLINES 5000 /* max #lines to be sorted */
- char *lineptr[MAXLINES]; /* pointers to text lines */
- int readlines(char *lineptr[], int nlines);
- void writelines(char *lineptr[], int nlines);
- void qsort(char *lineptr[], int left, int right);
- /* sort input lines */
- int main(void)
- {
-   int nlines; /* number of input lines read */
-   if ((nlines = readlines(lineptr, MAXLINES)) >= 0) {
-     qsort(lineptr, 0, nlines - 1);
-     writelines(lineptr, nlines);
-     return 0;
-   } else {
-     printf("error: input too big to sort\n");
-     return 1;
-   }
- }


# Pointer Arrays; Pointers to Pointers
- 컴퓨터프로그래밍기초
- 53
- Pointer Arrays; Pointers to Pointers
- 문자열을 사전 순으로 정렬하는 프로그램 (Cont’d)
- readlines 함수는 사용자 정의 함수이며, 사용자로부터 입력된 문자열을 줄 단위로 구분해 저장
- 문자열을 저장하면 해당 문자열의 주소를 포인터 배열 lineptr에 기록
- 문자열의 길이를 계산해 반환하며, 이 값은 정렬과 출력 연산 시 활용됨
- readlines 함수는 유한한(finite) 수의 문자를 저장할 수 있으며, 저장 공간이 부족할 경우 -1 반환
- #include <stdio.h>
- #include <string.h>
- #define MAXLINES 5000 /* max #lines to be sorted */
- char *lineptr[MAXLINES]; /* pointers to text lines */
- int readlines(char *lineptr[], int nlines);
- void writelines(char *lineptr[], int nlines);
- void qsort(char *lineptr[], int left, int right);
- /* sort input lines */
- int main(void)
- {
-   int nlines; /* number of input lines read */
-   if ((nlines = readlines(lineptr, MAXLINES)) >= 0) {
-     qsort(lineptr, 0, nlines - 1);
-     writelines(lineptr, nlines);
-     return 0;
-   } else {
-     printf("error: input too big to sort\n");
-     return 1;
-   }
- }


# Pointer Arrays; Pointers to Pointers
- 컴퓨터프로그래밍기초
- 54
- Pointer Arrays; Pointers to Pointers
- 문자열을 사전 순으로 정렬하는 프로그램 (Cont’d)
- lineptr 포인터 변수는 MAXLINES 개의 포인터 배열을 요소로 갖는 배열의 시작 주소 저장
- 각 요소는 문자열을 가리키는 포인터 변수이며, 문자열의 시작 주소를 보관함
- #include <stdio.h>
- #include <string.h>
- #define MAXLEN 1000 /* max length of any input line */
- int getline(char *, int);
- char *alloc(int);
- /* readlines: read input lines */
- int readlines(char *lineptr[], int maxlines)⋯
- /* writelines can be written instead as */
- void writelines(char *lineptr[], int nlines)⋯


# Pointer Arrays; Pointers to Pointers
- 컴퓨터프로그래밍기초
- 55
- Pointer Arrays; Pointers to Pointers
- 문자열을 사전 순으로 정렬하는 프로그램 (Cont’d)
- writelines 함수의 포인터 변수 lineptr는 앞에서 배웠던 방법을 응용해 표현할 수 있음
- /* readlines: read input lines */
- int readlines(char *lineptr[], int maxlines)
- {
-   int len, nlines;
-   char *p, line[MAXLEN];
-   nlines = 0;
-   while ((len = getline(line, MAXLEN)) > 0) {
-     if (nlines >= maxlines || (p = alloc(len)) == NULL) {
-       return -1;
-     } else {
-       line[len-1] = '\0'; /* delete newline */
-       strcpy(p, line);
-       lineptr[nlines++] = p;
-     }
-   }
-   return nlines;
- }
- /* writelines can be written instead as */
- void writelines(char *lineptr[], int nlines)
- {
-   while (nlines-- > 0)
-     printf("%s\n", *lineptr++);
- }


# Pointer Arrays;Pointers to Pointers
- 컴퓨터프로그래밍기초
- 56
- Pointer Arrays;Pointers to Pointers
- 문자열을 사전 순으로 정렬하는 프로그램 (Cont’d)
- qsort 함수와 swap 함수는 이전 시간에 사용했던 함수의 일부를 수정하여 사용
- #include <string.h>
- /* qsort: sort v[left]...v[right] into increasing order */
- void qsort(char *v[], int left, int right)
- {
-   int i, last;
-   void swap(char *v[], int i, int j);
-   if (left >= right)  /* do nothing if array contains */
-     return; /* fewer than two elements */
-   swap(v, left, (left + right) / 2);
-   last = left;
-   for (i = left + 1; i <= right; i++) {
-     if (strcmp(v[i], v[left]) < 0)
-       swap(v, ++last, i);
-   }
-   swap(v, left, last);
-   qsort(v, left, last - 1);
-   qsort(v, last + 1, right);
- }
- 
- /* swap: interchange v[i] and v[j] */
- void swap(char *v[], int i, int j)
- {
-   char *temp;
-   temp = v[i];
-   v[i] = v[j];
-   v[j] = temp;
- }


# Multi-dimensional Arrays
- 컴퓨터프로그래밍기초
- 57
- Multi-dimensional Arrays
- 날짜 변환 프로그램
- day_of_year 함수는 월별 날짜를 년별 날짜로 바꾸는 함수
- month_day 함수는 년별 날짜를 월별 날짜로 바꾸는 함수
- month_day 함수는 두 값을 계산해서 반환해야 하므로(month, day), 매개변수에 포인터를 사용해 간접 참조로 값을 전달
- 
- m은 2, d는 29가 됨
- 두 함수는 윤년 여부에 따른 월별 날짜 정보가 필요함
- 2차원 배열을 사용해 두 개의 행을 사용하면 정보 기록을 편리하게 할 수 있음
- month_day(1988, 60, &m, &d);


# Multi-dimensional Arrays
- 컴퓨터프로그래밍기초
- 58
- Multi-dimensional Arrays
- 날짜 변환 프로그램 (Cont’d)
- 각 행에서 0번째 요소는 사용하지 않음
- 1번째 요소부터 사용
- 가독성 향상
- 논리 표현식에서의 값은0(false) 또는 1(true)
- 윤년이 아닐 경우에는 첫 번째 행(0번째 행)을 가리킴
- 윤년일 경우에는 두 번째 행(1번째 행)을 가리킴
- static char daytab[2][13] = {
-   {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
-   {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}
- };
- /* day_of_year: set day of year from month & day */
- int day_of_year(int year, int month, int day)
- {
-   int i, leap;
-   
-   leap = (year % 4) == 0 && (year % 100) != 0 || (year % 400) == 0;
-   for (i = 1; i < month; i++)
-     day += daytab[leap][i];
-   return day;
- }
- /* month_day: set month, day from day of year */
- void month_day(int year, int yearday, int *pmonth, int *pday)
- {
-   int i, leap;
-   leap = (year % 4) == 0 && (year % 100) != 0 || (year % 400) == 0;
-   for (i = 1; yearday > daytab[leap][i]; i++)
-     yearday -= daytab[leap][i];
-   *pmonth = i;
-   *pday = yearday;
- }


# Multi-dimensional Arrays
- 컴퓨터프로그래밍기초
- 59
- Multi-dimensional Arrays
- 2차원 배열은 각 요소를 1차원 배열로 취급
- 아래와 같이 첨자를 표현해야 함
- 
- 
- 
- 
- 
- 2차원 배열의 초기화는 중괄호 속에 각 행에 대한 초기화 값을 중괄호로 묶어서 작성
- 중괄호 안에 중괄호
- static char daytab[2][13] = {
-   {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
-   {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}
- };
- daytab[i, j];  /* WRONG! */
- daytab[i][j];  /* [row][col] */


# Multi-dimensional Arrays
- 컴퓨터프로그래밍기초
- 60
- Multi-dimensional Arrays
- 2차원 배열을 함수의 매개변수로 사용할 때의 선언식
- 
- 
- 
- 세 함수 선언은 모두 동일한 표현
- 13개의 정수형 요소를 보관하는 배열을 가리키는 포인터
- 세 번째 선언같은 경우에는 [] 표현의 우선순위가 * 표현의 우선순위보다 높으므로 괄호를 사용해야 함
- 괄호를 쓰지 않으면 전혀 다른 선언이 됨
- static char daytab[2][13] = {
-   {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
-   {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}
- };f(int daytab[2][13]);
- f(int daytab[][13]);
- f(int *(daytab)[13]);
- int *daytab[13];  /* an array of 13 pointers to integers */


# Initialization of Pointer Arrays
- 컴퓨터프로그래밍기초
- 61
- Initialization of Pointer Arrays
- month_name 함수
- 사용자 정의 함수
- 매개변수 n을 사용해 n번째 달에 해당하는 이름이 저장되어 있는 문자 배열의 시작 주소를 반환
- 함수 내부에 문자열의 시작 주소를 가리키는 포인터들의 배열 선언
- 문자열은 어딘가에 저장되어 있으며, 포인터 배열은 각 문자열들의 시작 주소를 보관
- static 키워드를 사용해 함수가 매번 선언되더라도 포인터 배열은 메모리에 유지되도록 함
- /* month_name: return name of n-th month */
- char *month_name(int n)
- {
-   static char *name[] = {
-     "Illegal month",
-     "January", "February", "March",
-     "April", "May", "June",
-     "July", "August", "September",
-     "October", "November", "December"
-   };
-   return (n < 1 || n > 12) ? name[0] : name[n];
- }


# Pointers vs. Multi-dimensional Arrays
- 컴퓨터프로그래밍기초
- 62
- Pointers vs. Multi-dimensional Arrays
- 2차원 배열과 포인터 배열을 구분하는 방법
- 
- 
- 위와 같이 두 선언이 주어졌을 때, a[3][0]와 b[3][0] 둘 다 사용 가능한 문장
- 하나의 정수형 값 참조
- 2차원 배열 a는 메모리상에 200 개의 int 형 크기의 값을 기록할 수 있는 공간 필요:
- int 형 크기가 4 bytes라면, 총 800 bytes 메모리 사용
- a[row][col]의 위치는 2차원 배열 a의 시작 주소를 기준으로 20 × row + col번째에 위치
- int a[10][20];
- int *b[10];


# Pointers vs. Multi-dimensional Arrays
- 컴퓨터프로그래밍기초
- 63
- Pointers vs. Multi-dimensional Arrays
- 2차원 배열과 포인터 배열을 구분하는 방법 (Cont’d)
- 
- 
- 포인터 배열 b는 메모리 상에 10개의 포인터를 보관할 수 있는 공간이 필요함
- 각 포인터가 20 개의 정수형 요소를 보관하는 배열을 가리킨다면, 배열들을 보관할 수 있는 공간 외에 포인터를 보관할 수 있는 공간 추가로 필요
- int 형을 가리키는 포인터 변수의 크기가 4 bytes라면, 포인터 배열 b가 사용하는 메모리 공간은 총 40 bytes
- int 형 크기가 4 bytes라면, 포인터들이 가리키는 배열들의 총 메모리 공간은 800 bytes
- int a[10][20];
- int *b[10];


# Pointers vs. Multi-dimensional Arrays
- 컴퓨터프로그래밍기초
- 64
- Pointers vs. Multi-dimensional Arrays
- 2차원 배열과 포인터 배열을 구분하는 방법 (Cont’d)
- 
- 
- 포인터 배열을 쓰는 이유
- 2차원 배열은 각 행의 길이가 고정
- 포인터 배열은 각 행의 길이를 다르게 할 수 있음
- 2차원 배열 a는 각 행의 길이가 20으로 동일해야 하지만, 포인터 배열 b는 행의 길이가 동일하지 않아도 됨
- 포인터 배열 b의 0번째 요소는 길이가 10인 정수형 배열, 1번째 요소는 길이가 50인 정수형 배열, ...
- int a[10][20];
- int *b[10];


# Pointers vs. Multi-dimensional Arrays
- 컴퓨터프로그래밍기초
- 65
- Pointers vs. Multi-dimensional Arrays
- 서로 다른 길이의 문자열을 가리키는 포인터 배열
- char *name[] = { "Illegal month", "Jan", "Feb", "Mar" };
- 0x08AF53D0
- 0x08AF53D1
- 0x08AF53D2
- 0x08AF53D3
- 0x08AF53E0
- 0x08AF53E1
- 0x08AF53E2
- 0x08AF53E3
- 0x08AF53E4
- 0x08AF53E5
- 0x08AF53E6
- 0x08AF53E7
- 0x08AF53E8
- 0x08AF53E9
- 0x08AF53EA
- 0x08AF53EB


# Pointers vs. Multi-dimensional Arrays
- 컴퓨터프로그래밍기초
- 66
- Pointers vs. Multi-dimensional Arrays
- 서로 다른 길이의 문자열을 가리키는 2차원 배열
- 
- 
- 
- 
- 
- 각 행의 길이가 15로 동일
- 서로 다른 길이의 문자열을 보관할 때, 보관할 문자열 중 가장 긴 문자열의 길이로 통일해야 함
- 불필요한 메모리 낭비 발생할 수 있음(비효율)
- char aname[][15] = { "Illegal month", "Jan", "Feb", "Mar" };
- 0x08AF9B90
- 0x08AF9B91
- 0x08AF9B92
- 0x08AF9B93
- 0x08AF9B9F
- 0x08AF9BA0
- 0x08AF9BA1
- 0x08AF9BA2
- 0x08AF9BAE
- 0x08AF9BAF
- 0x08AF9BB0
- 0x08AF9BB1
- 0x08AF9BBD
- 0x08AF9BBE
- 0x08AF9BBF
- 0x08AF9BC0
- 0x08AF9BCC


# Command-line Arguments
- 컴퓨터프로그래밍기초
- 67
- Command-line Arguments
- C 프로그램 실행 시, 커맨드 라인에서 전달인자를 넘겨줄 수 있음
- 전달인자는 main 함수의 매개변수로 전달
- 
- 
- main 함수의 첫 번째 매개변수(argc, for argument count)에는 커맨드 라인에 입력된 전달인자의 개수 저장
- main 함수의 두 번째 매개변수(argv, for argument vector)에는 문자열 형태로 입력된 전달인자의 시작 주소를 가리키는 포인터 저장
- 전달인자는 선택사항(optional)
- /* to pass command line arguments, we typically define main() with two arguments */
- int main(int argc, char *argv[])⋯
- /* if you do not intend to process command line arguments */
- int main(void)⋯


# Command-line Arguments
- 컴퓨터프로그래밍기초
- 68
- Command-line Arguments
- 프로그램 실행 시 전달한 전달인자를 출력하는 프로그램 echo
- 실행할 프로그램의 이름이 echo인 경우:
- 커맨드 라인(터미널)에 ./echo hello, world 입력 시 argc의 값은 3, argv[0]은 "echo"의 시작 주소, argv[1]은 "hello," 의 시작 주소, argv[2]는 "world"의 시작 주소가 저장됨


# Command-line Arguments
- 컴퓨터프로그래밍기초
- 69
- Command-line Arguments
- 프로그램 실행 시 전달한 전달인자를 출력하는 프로그램 echo (Cont’d)
- argv[0]은 실행 프로그램의 이름을 가리킴
- argc는 적어도 1의 값을 가짐
- argc의 값이 1이라면, 해당 프로그램에 전달된 전달인자는 없음
- argc의 값이 1이 아니라면, 해당 프로그램에 전달된 전달인자가 존재
- 사용자가 전달한 전달인자는 argv[1]부터 차례대로 저장되며, 마지막 전달인자는 argv[argc-1](argv[argc]는 널 포인터가 저장되어 있음)


# Command-line Arguments
- 컴퓨터프로그래밍기초
- 70
- Command-line Arguments
- 프로그램 실행 시 전달한 전달인자를 출력하는 프로그램 echo (Cont’d)
- argv 포인터 배열을 배열로 처리한 예:
- #include <stdio.h>
- /* echo command-line arguments; 1st version */
- int main(int argc, char *argv[])
- {
-   int i;
-   for (i = 1; i < argc; i++)
-     printf("%s%c", argv[i], (i < argc – 1) ? ' ' : '\n');
-   printf("\n");
-   return 0;
- }


# Command-line Arguments
- 컴퓨터프로그래밍기초
- 71
- Command-line Arguments
- 프로그램 실행 시 전달한 전달인자를 출력하는 프로그램 echo (Cont’d)
- argv 포인터 배열을 포인터로 처리한 예:
- #include <stdio.h>
- /* echo command-line arguments; 2nd version */
- int main(int argc, char *argv[])
- {
-   while (--argc > 0)
-     printf("%s%c", *++argv, (argc > 1) ? ' ' : '\n');
-   printf("\n");
-   return 0;
- }


# Command-line Arguments
- 컴퓨터프로그래밍기초
- 72
- Command-line Arguments
- 프로그램 실행 시 전달한 전달인자를 출력하는 프로그램 echo (Cont’d)
- argv 포인터 배열을 포인터로 처리하고 printf 함수를 응용한 예:
- #include <stdio.h>
- /* echo command-line arguments; 3rd version */
- int main(int argc, char *argv[])
- {
-   while (--argc > 0)
-     printf((argc > 1) ? "%s " : "%s", *++argv);
-   printf("\n");
-   return 0;
- }


# Command-line Arguments
- 컴퓨터프로그래밍기초
- 73
- Command-line Arguments
- 입력된 문자열 중 특정 패턴이 포함된 줄만 출력하는 프로그램 find
- 이전에 배웠던 입력된 문자열 중 특정 패턴이 포함된 줄만 출력하는 프로그램을 커맨드 라인 전달인자를 사용해 개선할 수 있음:
- 이전 프로그램은 프로그램 내부에 찾고자 하는 패턴을 기록
- 패턴을 수정하고자 할 경우 코드를 고친 뒤 새로 컴파일해야 함
- 새로 작성할 프로그램은 패턴을 전달인자로 넘겨줌
- #include <stdio.h>
- #include <string.h>
- #define MAXLINE 1000
- int getline(char *, int);
- /* find: print lines that match pattern from 1st arg */
- int main(int argc, char *argv[])
- {
-   char line[MAXLINE];
-   int found = 0;
-   if (argc != 2) {
-     printf("Usage: find pattern\n");
-   } else {
-     while (getline(line, MAXLINE) > 0) {
-       if (strstr(line, argv[1]) != NULL) {
-         printf("%s", line);
-         found++;
-       }
-     }
-   }
-   return found;
- }


# Command-line Arguments
- 컴퓨터프로그래밍기초
- 74
- Command-line Arguments
- 입력된 문자열 중 특정 패턴이 포함된 줄만 출력하는 프로그램 find (Cont’d)
- <string.h> 헤더 파일 내에 strstr 함수가 정의되어 있음
- 포인터 line이 가리키는 문자열 내에 포인터 argv[1]이 가리키는 문자열이 처음 발견된 위치의 주소 반환
- 발견 못할 시 NULL 반환
- #include <stdio.h>
- #include <string.h>
- #define MAXLINE 1000
- int getline(char *, int);
- /* find: print lines that match pattern from 1st arg */
- int main(int argc, char *argv[])
- {
-   char line[MAXLINE];
-   int found = 0;
-   if (argc != 2) {
-     printf("Usage: find pattern\n");
-   } else {
-     while (getline(line, MAXLINE) > 0) {
-       if (strstr(line, argv[1]) != NULL) {
-         printf("%s", line);
-         found++;
-       }
-     }
-   }
-   return found;
- }


# Command-line Arguments
- 컴퓨터프로그래밍기초
- 75
- Command-line Arguments
- 선택사항이 추가된 프로그램 find
- 프로그램의 전달인자 중 선택사항(optional flag)임을 나타낼 때 일반적으로 '-' 기호 사용
-x (for "except")
- 패턴이 포함된 문자열을 제외한 모든 문자열 출력
-n (for "number")
- 행 번호를 출력 문자열 앞에 출력
- ./find -x -n pattern 형태로 사용한다면, 패턴이 포함되지 않은 문자열을 출력하되, 출력 문자열 앞에 행 번호를 출력
- '-' 기호가 붙은 전달인자는 순서에 상관없이 사용할 수 있어야 하며, 사용자의 편의를 위해 묶어서 사용할 수 있어야 함
- e.g. ./find -nx pattern


# Command-line Arguments
- 컴퓨터프로그래밍기초
- 76
- Command-line Arguments
- 선택사항이 추가된 프로그램 find (Cont’d)
- 선택사항은 프로그램 실행에독립적이어야 함:
- 선택사항이 올바르게 처리되어야 함
- 선택사항을 처리하는 과정 중에 오류가 발생해서는 안 됨
- #include <stdio.h>
- #include <string.h>
- #define MAXLINE 1000
- int getline(char *, int);
- /* find: print lines that match pattern from 1st arg  */
- int main(int argc, char *argv[])
- {
-   char line[MAXLINE];
-   long lineno = 0;
-   int c, except = 0, number = 0, found = 0;
-   while (--argc > 0 && (*++argv)[0] == '-') {⋯
-   
-   if (argc != 1) {⋯
-   } else {⋯
-      return found;
- }


# Command-line Arguments
- 컴퓨터프로그래밍기초
- 77
- Command-line Arguments
- 선택사항이 추가된 프로그램 find (Cont’d)
*++argv는 전달인자를 가리키는 포인터이며, (*++argv)[0]은 *++argv가 가리키는전달인자의 0번째 요소인 문자상수를 가리킴
- 첨자 연산([])이 간접 참조 연산(*) 또는단항 증감 연산자(++ or --)보다 우선순위 높음
- 괄호가 생략된다면 *++(argv[0])으로 계산(argv[0]이 가리키는 포인터의 주소 값을 증가한 후 간접 참조)
- ⋯
-   while (--argc > 0 && (*++argv)[0] == '-') {
-     while ((c = *++argv[0])) {
-       switch (c) {
-         case 'x':
-           except = 1;
-           break;
-         case 'n':
-           number = 1;
-           break;
-         default:
-           printf("find: illegal option %c\n", c);
-           argc = 0;
-           found = -1;
-           break;
-       }
-     }
-   }
- ⋯


# Command-line Arguments
- 컴퓨터프로그래밍기초
- 78
- Command-line Arguments
- 선택사항이 추가된 프로그램 find (Cont’d)
- 선택사항이 올바르게 처리되었다면 argc의 값은 1
- 그 외의 값을 가진 경우는 올바르게 처리된 경우가 아니므로 프로그램 종료
- 선택사항에 맞게 결과 출력
- ⋯
-   if (argc != 1) {
-     printf("Usage: find -x -n pattern\n");
-   } else {
-     while (getline(line, MAXLINE) > 0) {
-       ++lineno;
-       if ((strstr(line, *argv) != NULL) != except) {
-         if (number)
-           printf("%ld:", lineno);
-         printf("%s", line);
-         found++;
-       }
-     }
-   }
- ⋯


# Pointers to Functions
- 컴퓨터프로그래밍기초
- 79
- Pointers to Functions
- 함수는 변수가 아니지만 함수 포인터를 사용해 함수를 가리킬 수 있음
- 함수 포인터는 대입문, 배열의 첨자 안, 함수의 전달인자, 함수의 반환값 등 표현식이 등장할 수 있는 자리에 사용될 수 있음
- 숫자 정렬 프로그램
- 문자열을 사전 순으로 정렬하는 프로그램을 숫자를 대상으로 정렬할 수 있도록 일부 수정
- 숫자 정렬 시 크기를 기준으로 오름차순 정렬


# Pointers to Functions
- 컴퓨터프로그래밍기초
- 80
- Pointers to Functions
- 숫자 정렬 프로그램 (Cont’d)
- 정렬 알고리즘은 비교 및 교환 연산과 독립되어야 함
- 특정 형에 대한 비교 연산 및 교환 연산을 수행하는 함수를 전달한다면, 해당 형에 대한 정렬 작업을 수행할 수 있음:
- 문자열(char *)에 대한 교환 및 비교 연산을 수행하는 함수를 전달하면 문자열을 정렬하는 프로그램으로 동작
- 숫자(int, long, …)에 대한 교환 및 비교 연산을 수행하는 함수를 전달하면 숫자를 정렬하는 프로그램으로 동작
- 함수 포인터를 이용하면 여러 형에 대한 정렬을 수행할 수 있는 유연한 프로그램을 만들 수 있음


# Pointers to Functions
- 컴퓨터프로그래밍기초
- 81
- Pointers to Functions
- 숫자 정렬 프로그램 (Cont’d)
- 커맨드 라인 전달인자 여부에 따라 비교 함수를 다르게 전달
- 함수 포인터를 사용하려면 두 비교 함수의 출력 형식이 같아야 함
- 두 비교 함수 numcmp와 strcmp는 비교에 따른 결과 값이 일치함:
- 첫 번째 매개변수가 두 번째 매개변수보다 작으면 -1 반환
- 첫 번째 매개변수와 두 번째 매개변수가 같으면 0 반환
- 첫 번째 매개변수가 두 번째 매개변수보다 크면 1 반환
- #include <stdio.h>
- #include <string.h>
- #define MAXLINES 5000    /* max #lines to be sorted */
- char *lineptr[MAXLINES]; /* pointers to text lines */
- int readlines(char *lineptr[], int nlines);
- void writelines(char *lineptr[], int nlines);
- void qsort(void *lineptr[], int left, int right,
-     int (*comp)(void *, void *));
- int numcmp(const char *, const char *);
- /* sort input lines */
- int main(int argc, char *argv[])
- {
-   int nlines;       /* number of input lines read */
-   int numeric = 0;  /* 1 if numeric sort */
-   if (argc > 1 && strcmp(argv[1], "-n") == 0)
-     numeric = 1;
-   if ((nlines = readlines(lineptr, MAXLINES)) >= 0) {
-     qsort((void **) lineptr, 0, nlines - 1,
-         (int (*)(void *, void *))(numeric ? numcmp : strcmp));
-     writelines(lineptr, nlines);
-     return 0;
-   }
-   printf("input too big to sort\n");
-   return 1;
- }


# Pointers to Functions
- 컴퓨터프로그래밍기초
- 82
- Pointers to Functions
- 숫자 정렬 프로그램 (Cont’d)
- qsort 함수의 전달인자로 함수 포인터 사용
- qsort 함수는 numcmp 함수와 strcmp 함수의 주소값을 전달받아 처리
- 함수의 주소를 전달할 때 & 연산자는 필요하지 않음
- 배열의 이름도 & 연산자 불필요
- #include <stdio.h>
- #include <string.h>
- #define MAXLINES 5000    /* max #lines to be sorted */
- char *lineptr[MAXLINES]; /* pointers to text lines */
- int readlines(char *lineptr[], int nlines);
- void writelines(char *lineptr[], int nlines);
- void qsort(void *lineptr[], int left, int right,
-     int (*comp)(void *, void *));
- int numcmp(const char *, const char *);
- /* sort input lines */
- int main(int argc, char *argv[])
- {
-   int nlines;       /* number of input lines read */
-   int numeric = 0;  /* 1 if numeric sort */
-   if (argc > 1 && strcmp(argv[1], "-n") == 0)
-     numeric = 1;
-   if ((nlines = readlines(lineptr, MAXLINES)) >= 0) {
-     qsort((void **) lineptr, 0, nlines - 1,
-         (int (*)(void *, void *))(numeric ? numcmp : strcmp));
-     writelines(lineptr, nlines);
-     return 0;
-   }
-   printf("input too big to sort\n");
-   return 1;
- }


# Pointers to Functions
- 컴퓨터프로그래밍기초
- 83
- Pointers to Functions
- 숫자 정렬 프로그램 (Cont’d)
- qsort 함수는 비교 함수의 주소값을 전달받기 때문에, 문자열 비교뿐만 아닌 숫자 비교도 가능해짐
- void * 형
- 포인터 변수는 void * 형으로 형 변환이 일어날 수 있으며, void * 형 포인터는 다른 형으로 형 변환을 할 수 있음(generic pointer)
- void * 형 포인터는 어떠한 형의 포인터도 처리할 수 있으며, 주로 주소 값을 임시로 보관하고자 할 때 사용됨
- /* qsort: sort v[left]...v[right] into increasing order */
- void qsort(void *v[], int left, int right,
-     int (*comp)(void *, void *))
- {
-   int i, last;
-   void swap(void *v[], int, int);
-   /* do nothing if array contains */
-   if (left >= right)
-     return; /* fewer than two elements */
-   swap(v, left, (left + right) / 2);
-   last = left;
-   for (i = left + 1; i <= right; ++i) {
-     if ((*comp)(v[i], v[left]) < 0)
-       swap(v, ++last, i);
-   }
-   swap(v, left, last);
-   qsort(v, left, last - 1, comp);
-   qsort(v, last + 1, right, comp);
- }
- /* swap: interchange v[i] and v[j] */
- void swap(void *v[], int i, int j)
- {
-   void *temp;
-   temp = v[i];
-   v[i] = v[j];
-   v[j] = temp;
- }


# Pointers to Functions
- 컴퓨터프로그래밍기초
- 84
- Pointers to Functions
- 숫자 정렬 프로그램 (Cont’d)
- comp 함수는 함수 포인터이며, *comp는 전달받은 함수의 실체를 가리킴
- (*comp)(v[i], v[left])는 함수 포인터가 가리키는 함수를 호출함
- 함수 포인터를 올바르게 사용하려면 괄호를 꼭 사용해야 함
- 
- 괄호 생략 시 해당 표현은 정수형 포인터를 반환하는 함수
- int (*comp)(void *, void *)
- /* qsort: sort v[left]...v[right] into increasing order */
- void qsort(void *v[], int left, int right,
-     int (*comp)(void *, void *))
- {
-   int i, last;
-   void swap(void *v[], int, int);
-   /* do nothing if array contains */
-   if (left >= right)
-     return; /* fewer than two elements */
-   swap(v, left, (left + right) / 2);
-   last = left;
-   for (i = left + 1; i <= right; ++i) {
-     if ((*comp)(v[i], v[left]) < 0)
-       swap(v, ++last, i);
-   }
-   swap(v, left, last);
-   qsort(v, left, last - 1, comp);
-   qsort(v, last + 1, right, comp);
- }
- /* swap: interchange v[i] and v[j] */
- void swap(void *v[], int i, int j)
- {
-   void *temp;
-   temp = v[i];
-   v[i] = v[j];
-   v[j] = temp;
- }


# Pointers to Functions
- 컴퓨터프로그래밍기초
- 85
- Pointers to Functions
- 숫자 정렬 프로그램 (Cont’d)
- 문자열 비교 함수는 표준 라이브러리 함수 strcmp 사용
- numcmp 함수는 strcmp 함수와 비교에 따른 결과값이 일치하도록 구현
- numcmp 함수와 strcmp 함수를 사용하면 둘 다 오름차순 형태로 정렬을 수행할 수 있음
- #include <stdlib.h>
- /* numcmp: compare s1 and s2 numerically */
- int numcmp(const char *s1, const char *s2)
- {
-   double v1, v2;
-   v1 = atof(s1);
-   v2 = atof(s2);
-   if (v1 < v2)
-     return -1;
-   else if (v1 > v2)
-     return 1;
-   else
-     return 0;
- }


# Complicated Declarations
- 컴퓨터프로그래밍기초
- 86
- Complicated Declarations
- 복잡한 선언문을 설명하는 프로그램(dcl)
- 복잡한 선언문을 사람이 이해할 수 있는 형태로 분석
- C 선언을 설명문으로 변환:
- char **argv  argv:  pointer to pointer to char			
- int (*daytab)[13]  daytab: pointer to array[13] of int
- int *daytab[13]  daytab: array[13] of pointer to int
- void *comp()  comp: function returning pointer to void
- void (*comp)()  comp: pointer to function returning void
- char (*(*x())[])()
-   x: function returning pointer to array[] of       pointer to function returning char	
- char (*(*x[3])())[5]  x: array[3] of pointer to function   returning pointer to array[5] of char


# Complicated Declarations
- 컴퓨터프로그래밍기초
- 87
- Complicated Declarations
- 복잡한 선언문을 설명하는 프로그램(dcl) (Cont’d)
- 선언에 관련된 C 언어 문법(grammer)을 기반으로 작성
- 선언문의 구문(syntax) 구조를 간단히 표현하면 아래와 같음:
- 
- 
- 
- 
- 
- dcl은 direct-dcl이며, 앞에 간접 참조 연산자(*)가 올 수도 있음
- direct-dcl은 이름, 양 옆에 괄호가 붙은 dcl, 뒤에 괄호가 붙은 direct-dcl, 또는 뒤에 대괄호(크기는 생략 가능)가 붙은 direct-dcl을 의미
- dcl:		optional *'s direct-dcl		direct-dcl	name
- 				(dcl)				direct-dcl()				direct-dcl[optional size]


# Complicated Declarations
- 컴퓨터프로그래밍기초
- 88
- Complicated Declarations
- 복잡한 선언문을 설명하는 프로그램(dcl) (Cont’d)
- 문법을 이용한 선언문 분석
- 
- 
- 
- 
- 
- e.g. (*pfa[])()1.  pfa는 이름으로 식별되며, 이름은 direct-dcl임2.  pfa[]은 direct-dcl임3.  direct-dcl 앞에는 * 연산자가 올 수 있기 때문에 *pfa[]는 dcl임4.  dcl 양 옆에 괄호가 붙으면 direct-dcl이기 때문에 (*pfa[])는 direct-dcl임5.  direct-dcl 뒤에는 괄호가 올 수 있기 때문에 (*pfa[])()는 direct-dcl임6.  direct-dcl은 dcl임
- dcl:		optional *'s direct-dcl		direct-dcl	name
- 				(dcl)				direct-dcl()				direct-dcl[optional size]


# Complicated Declarations
- 컴퓨터프로그래밍기초
- 89
- Complicated Declarations
- 복잡한 선언문을 설명하는 프로그램(dcl) (Cont’d)
- dcl 프로그램의 핵심은 dcl 함수와 dirdcl(direct-dcl) 함수
- 두 함수는 선언문을 C 언어 선언 관련 문법 기반으로 분석
- 문법은 재귀 기반으로 정의되어 있음
- 두 함수가 재귀적으로 호출되면서 선언문을 차례로 분석(recursive-descent parser)
- 큰 덩어리(선언문)로부터 가장 작은 단위에 이를 때까지 분석


# ComplicatedDeclarations
- 컴퓨터프로그래밍기초
- 90
- ComplicatedDeclarations
- 복잡한 선언문을 설명하는 프로그램(dcl) (Cont’d)
- 간단한 자료형만 처리 가능
- int, char, etc.
- 함수의 매개변수 형이나 const 선언 등의 한정자는 처리하지 못함
- 기초적인 기능만을 수행
- 오류 회복(error recovery) 기능이 포함되어 있지 않음
- 올바른 선언식만 입력해야 함
- #include <stdio.h>
- #include <string.h>
- #include <ctype.h>
- #include "dcl.h"
- #include "gettoken.h"
- #define MAXTOKEN 100
- int tokentype;            /* type of last token */
- char token[MAXTOKEN];     /* last token string */
- char name[MAXTOKEN];      /* identifier name */
- char datatype[MAXTOKEN];  /* data type = char, int, etc. */
- char out[1000];           /* output string */
- /* convert declaration to words */
- int main(void)
- {
-   while (gettoken() != EOF) {  /* 1st token on line */
-     strcpy(datatype, token);   /* is the datatype */
-     out[0] = '\0';
-     dcl();  /* parse rest of line */
-     if (tokentype != '\n')
-       printf("syntax error\n");
-     printf("%s: %s %s\n", name, out, datatype);
-   }
-   return 0;
- }


# ComplicatedDeclarations
- 컴퓨터프로그래밍기초
- 91
- ComplicatedDeclarations
- 복잡한 선언문을 설명하는 프로그램(dcl) (Cont’d)
- gettoken 함수는 공백 문자들을 무시한 뒤, 입력으로부터 토큰(유의미한 이름)을 찾음
- 선언문 분석에 사용되는 이름, 한 쌍의 괄호, 한 쌍의 대괄호, 숫자가 포함된 한 쌍의 대괄호 등을 의미함
- #include <ctype.h>
- #include <string.h>
- #include "gettoken.h"
- extern int  tokentype;  /* main.c */
- extern char token[];    /* main.c */
- int gettoken(void) /* return next token */
- {
-   int c, getch(void);
-   void ungetch(int);
-   char *p = token;
-   while ((c = getch()) == ' ' || c == '\t') { }
-   if (c == '(') {⋯
-   } else if (c == '[') {⋯
-   } else if (isalpha(c)) {⋯
-   } else {⋯
- }


# ComplicatedDeclarations
- 컴퓨터프로그래밍기초
- 92
- ComplicatedDeclarations
- 복잡한 선언문을 설명하는 프로그램(dcl) (Cont’d)
- gettoken 함수는 공백 문자들을 무시한 뒤, 입력으로부터 토큰(유의미한 이름)을 찾음
- 선언문 분석에 사용되는 이름, 한 쌍의 괄호, 한 쌍의 대괄호, 숫자가 포함된 한 쌍의 대괄호 등을 의미함
- ⋯
-   if (c == '(') {
-     if ((c = getch()) == ')') {
-       strcpy(token, "()");
-       return tokentype = PARENS;
-     } else {
-       ungetch(c);
-       return tokentype = '(';
-     }
-   } else if (c == '[') {
-     for (*p++ = c; (*p++ = getch()) != ']'; ) { }
-     *p = '\0';
-     return tokentype = BRACKETS;
-   } else if (isalpha(c)) {
-     for (*p++ = c; isalnum(c = getch()); )
-       *p++ = c;
-     *p = '\0';
-     ungetch(c);
-     return tokentype = NAME;
-   } else {
-     return tokentype = c;
-   }
- ⋯


# ComplicatedDeclarations
- 컴퓨터프로그래밍기초
- 93
- ComplicatedDeclarations
- 복잡한 선언문을 설명하는 프로그램(dcl) (Cont’d)
- #include <stdio.h>
- #include <string.h>
- #include "dcl.h"
- #include "gettoken.h"
- extern int tokentype;  /* main.c */
- extern char token[];   /* main.c */
- extern char name[];    /* main.c */
- extern char out[];     /* main.c */
- /* dcl: parse a declarator */
- void dcl(void)
- {
-   int ns;
-   /* count *'s */
-   for (ns = 0; gettoken() == '*'; ++ns) { }
-   dirdcl();
-   while (ns-- > 0)
-     strcat(out, " pointer to");
- }
- /* dirdcl: parse a direct declarator */
- void dirdcl(void)⋯
- dcl:		optional *'s direct-dcl	direct-dcl	name
- 			(dcl)			direct-dcl()			direct-dcl[optional size]


# ComplicatedDeclarations
- 컴퓨터프로그래밍기초
- 94
- ComplicatedDeclarations
- 복잡한 선언문을 설명하는 프로그램(dcl) (Cont’d)
- ⋯/* dirdcl: parse a direct declarator */
- void dirdcl(void)
- {
-   int type;
-   if (tokentype == '(') {  /* ( dcl ) */
-     dcl();
-     if (tokentype != ')')
-       printf("error: missing )\n");
-   } else if (tokentype == NAME) {  /* variable name */
-     strcpy(name, token);
-   } else {
-     printf("error: expected name or (dcl)\n");
-   }
-   while ((type=gettoken()) == PARENS || type == BRACKETS) {
-     if (type == PARENS) {
-       strcat(out, " function returning");
-     } else {
-       strcat(out, " array");
-       strcat(out, token);
-       strcat(out, " of");
-     }
-   }
- }
- dcl:		optional *'s direct-dcl	direct-dcl	name
- 			(dcl)			direct-dcl()			direct-dcl[optional size]

