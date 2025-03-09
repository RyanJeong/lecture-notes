# 컴퓨터프로그래밍기초
- 컴퓨터프로그래밍기초
- Functions and Program Structure


# Contents
- 컴퓨터프로그래밍기초
- ‹#›
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
- ‹#›
- Goals of This Chapter
- 함수의 필요성 이해
- 함수 선언의 필요성(implicit function declarations)
- 외부 변수 선언과 정의
- 범위 규칙과 초기화
- 헤더 파일 사용 목적
- 재귀(recursion)
- 전처리 과정


# Basics of Functions
- 컴퓨터프로그래밍기초
- ‹#›
- Basics of Functions
- 프로그램 작성 시 main 함수 하나만 사용하는 것보다 여러 개의 함수를 사용하는 것을 권장
- 단일 영역(main 함수)에서 모든 코드를 관리하는 것보다 서로 연관된 코드를 사용자 정의 함수(독립적인 영역)로 분리해 관리하면 다음과 같은 이점이 있음:
- 불필요한 상호 작용 배제
- 함수 필요 시 언제든지 호출해 사용 가능
- 함수 구현을 더 이상 기억할 필요가 없으며, 코드 개발에 집중할 수 있음
- 프로그램 수정 용이
- 함수 기반 프로그램은 수정이 필요한 함수만 수정하면 됨
- 그렇지 못한 프로그램은 수정이 필요한 지점을 모두 파악해 수정해야 함


# Basics of Functions
- 컴퓨터프로그래밍기초
- ‹#›
- Basics of Functions
- 입력된 문자열 중 특정 패턴이 포함된 줄만 출력하는 프로그램
- Linux 유틸리티 중 grep과 유사한 동작 수행
- e.g. 아래 문자열 중에서 패턴 “ould”가 포함된 문자열 출력
- 
- 
- 
- 출력 결과는 아래와 같음
- Ah Love! could you and I with Fate conspire
-     To grasp this sorry Scheme of Things entire,
-     Would not we shatter it to bits -- and then
-     Re-mould it nearer to the Heart's Desire!
- Ah Love! could you and I with Fate conspire
-     Would not we shatter it to bits -- and then
-     Re-mould it nearer to the Heart's Desire!


# Basics of Functions
- 컴퓨터프로그래밍기초
- ‹#›
- Basics of Functions
- 입력된 문자열 중 특정 패턴이 포함된 줄만 출력하는 프로그램 (Cont’d)
- 프로그램 동작 절차
- 
- 
- 함수 사용 시 간단히 구현 가능
- getline 함수 새로 정의
- strindex 함수 새로 정의
- printf 함수 사용
- while (there's another line)            /* getline */
-         if (the line contains the pattern)  /* strindex */
-             print it                        /* printf */


# Basics of Functions
- 컴퓨터프로그래밍기초
- ‹#›
- Basics of Functions
- 입력된 문자열 중 특정 패턴이 포함된 줄만 출력하는 프로그램 (Cont’d)
- 배열 s에 lim 만큼 입력 버퍼에 들어있는 문자를 기록
- 입력 버퍼로부터 읽어온 문자의 개수 반환
- /* getline: get line into s, return length */
-     int getline(char s[], int lim)
-     {
-       int c, i;
-     
-       i = 0;
-       while ((--lim > 0) && ((c = getchar()) != EOF) && (c != '\n'))
-         s[i++] = c;
-       if (c == '\n')
-         s[i++] = c;
-       s[i] = '\0';
-     
-       return i;
-     }


# Basics of Functions
- 컴퓨터프로그래밍기초
- ‹#›
- Basics of Functions
- 입력된 문자열 중 특정 패턴이 포함된 줄만 출력하는 프로그램 (Cont’d)
- 문자열 s 중에서 문자열 t가 시작되는 위치(index) 반환
- 반환 값은 0 또는 양수이며, 문자열 s 내에 문자열 t가 없다면 −1 반환
- 배열의 위치는 0부터 시작하므로 음수 값은 찾고자 하는 문자열을 못 찾았음을 의미
- /* strindex: return index of t in s, -1 if none */
-     int strindex(char s[], char t[])
-     {
-       int i, j, k;
-     
-       for (i = 0; s[i] != '\0'; ++i) {
-         for (j = i, k = 0; (t[k] != '\0') && (s[j] == t[k]); ++j, ++k) {}
-         if (k > 0 && t[k] == '\0')
-           return i;
-       }
-     
-       return -1;
-     }


# Basics of Functions
- 컴퓨터프로그래밍기초
- ‹#›
- Basics of Functions
- 입력된 문자열 중 특정 패턴이 포함된 줄만 출력하는 프로그램 (Cont’d)
- #include <stdio.h>
-     #define MAXLINE 1000 /* maximum input line length */
-     int getline(char line[], int max);
-     int strindex(char source[], char searchfor[]);
-     char pattern[] = "ould"; /* pattern to search for */
-     /* find all lines matching pattern */
-     int main(void)
-     {
-       char line[MAXLINE];
-       int found;
-       found = 0;
-       while (getline(line, MAXLINE) > 0) {
-         if (strindex(line, pattern) >= 0) {
-           printf("%s", line);
-           found++;
-         }
-       }
-       return found;
-     }


# Basics of Functions
- 컴퓨터프로그래밍기초
- ‹#›
- Basics of Functions
- 함수 정의 형태
- 
- 
- 여러 부분이 생략될 수 있음
- e.g. 가장 간결한 형태의 함수
- 
- 자리 표시자(placeholder)로써 많이 사용되는 형태이며, 주석처럼 사용하기도 함
- 함수 반환 형 생략 시 컴파일러는 해당 함수를 int 형으로 간주
- 매개변수 없는 함수는 괄호 안을 비워두거나 void 키워드 사용
- void 키워드 사용 권장
- return-type function-name(argument declarations)
-     {
-         declarations and statements
-     }
- dummy() {}


# Basics of Functions
- 컴퓨터프로그래밍기초
- ‹#›
- Basics of Functions
- 프로그램은 변수와 함수의 정의들을 모아놓은 집합
- 함수 간 값 전달(communication) 방법:
- 함수 호출 시 전달인자를 사용하면 함수 측(callee) 매개변수로 값이 전달(복사)되며, 호출된 함수 종료 시 반환 문(return statement)을 사용하면 함수 호출 측(caller)으로 값이 반환(복사)됨
- 외부변수(전역변수) 사용
- 함수 정의 순서는 프로그램에 아무런 영향을 주지 않음
- 프로그램이 여러 개의 함수를 사용할 때, 함수들은 하나의 소스코드 파일에 위치하거나 여러 개의 소스코드 파일에 위치할 수 있음
- 하나의 함수를 여러 개의 소스코드 파일로 나누는 것은 불가능


# Basics of Functions
- 컴퓨터프로그래밍기초
- ‹#›
- Basics of Functions
- 반환 문(return statement)
- 
- 함수를 종료함과 동시에 함수 호출 측으로 값(반환 문의 표현식 평가 결과)이 전달됨
- 반환 문의 표현식에는 아무 표현식이나 위치할 수 있음
- 
- 반환 문 표현식은 함수 형으로 형 변환(if necessary)
- 반환 문 표현식 주위에 괄호를 사용하기도 함(optional)
- e.g. 강조 표현
- return expression;
- return (-1);


# Basics of Functions
- 컴퓨터프로그래밍기초
- ‹#›
- Basics of Functions
- C 프로그램이 여러 개의 소스코드 파일로 분할된 경우
- main.c


# Basics of Functions
- 컴퓨터프로그래밍기초
- ‹#›
- Basics of Functions
- C 프로그램이 여러 개의 소스코드 파일로 분할된 경우 (Cont’d)
- getline.c


# Basics of Functions
- 컴퓨터프로그래밍기초
- ‹#›
- Basics of Functions
- C 프로그램이 여러 개의 소스코드 파일로 분할된 경우 (Cont’d)
- strindex.c


# Basics of Functions
- 컴퓨터프로그래밍기초
- ‹#›
- Basics of Functions
- C 프로그램이 여러 개의 소스코드 파일로 분할된 경우 (Cont’d)
- 각 소스코드 파일로부터 목적파일을 생성한 뒤에, 생성된 목적파일들을 이용해 하나의 실행파일 생성
- cc -c main.c -o main.o -ansi –Wall
- cc -c getline.c -o getline.o -ansi –Wall
- cc -c strindex.c -o strindex.o -ansi –Wall
- cc main.o getline.o strindex.o -o pattern -ansi –Wall
- 위 명령어들은 명령어 한 줄로 축약할 수 있음
- cc main.c getline.c strindex.c -o pattern -ansi –Wall
- 위 명령어를 와일드카드 문자(*)를 사용하면 일반화할 수 있음
- cc *.c -ansi –Wall


# Basics of Functions
- 컴퓨터프로그래밍기초
- ‹#›
- Basics of Functions
- C 프로그램이 여러 개의 소스코드 파일로 분할된 경우 (Cont’d)
- tasks.json
- // ... Skipped ... 
-       "args": [
-         "-fdiagnostics-color=always",
-         "-g",
-         "${fileDirname}/*.c",
-         "-o",
-         "${PWD##*/}",  // if the current working directory is /home/user/projects/myapp, then "${PWD##*/}" would return "myapp"         
-         "-ansi",
-         "-Wall"
-       ],
-       // ... Skipped ...


# Functions Returning Non-integers
- 컴퓨터프로그래밍기초
- ‹#›
- Functions Returning Non-integers
- 일반적인 함수는 대부분 값을 반환하지 않거나(void) 정수형(int) 값 반환
- 
- 수학 관련 대부분 함수들은 실수형(double) 값 반환
- sqrt, sin, cos, ...
- 
- 복잡한 형 값을 반환하는 함수도 존재
- e.g. 포인터 반환


# Functions Returning Non-integers
- 컴퓨터프로그래밍기초
- ‹#›
- Functions Returning Non-integers
- atof 함수
- <stdlib.h> 헤더 파일 내에 atof 함수가 정의되어 있음
- atoi 함수의 기능이 확장된 함수
- 다음 주어진 코드는 표준 라이브러리에 정의되어 있는 atof 함수보다 간단한 형태
- 과학적 표기법을 따른 문자열(e.g. 1.23e+14)은 처리하지 못 함
- 반환 값이 정수형이 아니므로, 반드시 반환 형을 명시해야 함
- #include <ctype.h>
-     /* atof: convert string s to double */
-     double atof(char s[])
-     {
-       double val, power;
-       int i, sign;
-       for (i = 0; isspace(s[i]); ++i) {} /* skip white space */
-       sign = (s[i] == '-') ? -1 : 1;
-       if (s[i] == '+' || s[i] == '-')
-         ++i;
-       for (val = 0.0; isdigit(s[i]); i++)
-         val = 10.0 * val + (s[i] - '0');
-       if (s[i] == '.')
-         i++;
-       for (power = 1.0; isdigit(s[i]); i++) {
-         val = 10.0 * val + (s[i] - '0');
-         power *= 10;
-       }
-       return sign * val / power;
-     }


# Functions Returning Non-integers
- 컴퓨터프로그래밍기초
- ‹#›
- Functions Returning Non-integers
- 가장 기본적인 계산기 프로그램
- 덧셈만 가능
- 숫자 문자열 입력 시 지금까지의 누적 합을 화면에 출력
- 숫자 문자열에 부호가 포함될 수 있음
- 함수의 선언과 정의는 일관되게 작성
- 반환형, 매개변수의 개수는 항상 일치되어야 하며, 매개변수 이름은 같지 않아도 됨
- #include <stdio.h>
-     #define MAXLINE 100
-     /* rudimentary calculator */
-     int main(void)
-     {
-       double sum, atof(char []);
-       char line[MAXLINE];
-       int getline(char [], int);
-       sum = 0;
-       while (getline(line, MAXLINE) > 0)
-         printf("\t%g\n", sum += atof(line));
-       return 0;
-     }


# Functions Returning Non-integers
- 컴퓨터프로그래밍기초
- ‹#›
- Functions Returning Non-integers
- 가장 기본적인 계산기 프로그램 (Cont’d)
- 만약 atof 함수 선언이 누락되었다면?
- 컴파일러는 atof 함수의 선언을 찾지 못하였으므로 atof 함수의 반환형을 int 형으로 간주
- Implicit function declarations
- atof 함수는 double 형을 반환하지만, 실제로 호출 측으로 반환된 값은 int 형
- #include <stdio.h>
-     #define MAXLINE 100
-     /* rudimentary calculator */
-     int main(void)
-     {
-       double sum, atof(char []);
-       char line[MAXLINE];
-       int getline(char [], int);
-       sum = 0;
-       while (getline(line, MAXLINE) > 0)
-         printf("\t%g\n", sum += atof(line));
-       return 0;
-     }


# Functions Returning Non-integers
- 컴퓨터프로그래밍기초
- ‹#›
- Functions Returning Non-integers
- 가장 기본적인 계산기 프로그램 (Cont’d)
- 표준 라이브러리에서 제공하는 atof 함수를 사용한 예
- <stdlib.h> 헤더 파일 안에 atof 함수의 선언이 포함되어 있음
- 과학적 표기법을 따른 문자열도 처리 가능
- #include <stdio.h>
-     #include <stdlib.h>
-     #define MAXLINE 100
-     /* rudimentary calculator */
-     int main(void)
-     {
-       double sum;
-       char line[MAXLINE];
-       int getline(char [], int);
-       sum = 0;
-       while (getline(line, MAXLINE) > 0)
-         printf("\t%g\n", sum += atof(line));
-       return 0;
-     }


# Functions Returning Non-integers
- 컴퓨터프로그래밍기초
- ‹#›
- Functions Returning Non-integers
- Implicit function declarations
- 표현식 내 사용된 이름 뒤에 괄호가 뒤따르는 경우 컴파일러는 이를 함수의 이름으로 간주 
- 
- 함수 선언이 누락된 채 함수 호출을 시도할 경우, 컴파일러는 다음과 같이 암묵적으로 함수 선언을 수행:
- 함수의 반환형은 int 형으로 간주
- 매개변수에 대한 정보가 없기 때문에 매개변수 검사를 수행하지 않음
- 
- 함수 사용 전에 반드시 함수 선언을 해야 함
- 함수 선언이 누락된 상태에서 함수를 사용할 경우 기대와 다른 결과가 계산될 수 있음


# Functions Returning Non-integers
- 컴퓨터프로그래밍기초
- ‹#›
- Functions Returning Non-integers
- atof 함수를 이용한 atoi 함수 재정의
- 
- 
- 
- 
- 반환 문에서의 표현식 값은 반환 전에 함수 형으로 형 변환(암묵적 형 변환)
- 몇몇 컴파일러는 암묵적(implicit) 형 변환 발생 시 경고 발생
- 명시적(explicit) 형 변환 사용 권장
- /* atoi: convert string s to integer using atof */
-     int atoi(char s[])
-     {
-       double atof(char s[]);
-       return (int) atof(s);
-     }
- return atof(s);        /* some compilers warn of it*/    return (int) atof(s);  /* the return statement is intended and it suppresses any warning*/


# External Variables
- 컴퓨터프로그래밍기초
- ‹#›
- External Variables
- 내부(internal)는 함수 내부에 위치
- 변수, 함수의 선언, 함수의 매개변수
- 외부(external)는 함수 외부에 위치
- 변수, 함수의 선언, 함수의 정의
- 함수는 항상 외부에 정의되어야 함
- 외부에 선언된 이름들은 다른 지역에서 사용 가능
- 다른 파일에 선언 혹은 정의되어 있는 외부 이름은 링커(linker)가 올바른 이름을 참조할 수 있도록 처리(external linkage)


# External Variables
- 컴퓨터프로그래밍기초
- ‹#›
- External Variables
- 외부 변수는 전역에서 사용 가능하므로 함수의 매개변수 대체 가능 
- 함수 호출 시 많은 변수가 필요할 경우, 전역 변수 사용 시 함수 정의 간소화 가능
- 외부 변수 선언 시 초기화가 생략되었다면 0으로 초기화
- 외부 변수 남용은 주의할 것:
- 프로그램 구조(program structure)가 나빠질 수 있음
- 함수 간 데이터 연결이 너무 많아짐(의존 관계 형성)
- problem with modularity and reusing
- 꼭 필요한 경우에만 외부 변수 사용할 것


# External Variables
- 컴퓨터프로그래밍기초
- ‹#›
- External Variables
- 외부 변수의 유용함
- 내부 변수(자동 변수, automatic variables)는 함수 내부에 정의된 변수이므로 함수 시작 시 자동으로 생성되고 함수 종료 시 자동 소멸
- 외부 변수는 프로그램 시작 시 생성되고 프로그램 종료 시 소멸(permanent)
- 값을 보존할 수 있음
- 서로 다른 두 함수가 외부 변수를 통해 값을 공유할 수 있음
- 서로 다른 두 함수가 지역에 종속되어 있는 데이터(지역 변수)를 공유한다면, 이를 동기화할 수 있는 기능이 추가로 구현되어야 함
- 공유될 데이터를 전역 변수로 구현한다면 구현이 훨씬 간결해짐


# External Variables
- 컴퓨터프로그래밍기초
- ‹#›
- External Variables
- 외부 변수를 이용한 계산기
- +, −, *, / 연산 가능
- infix 방법이 아닌 구현하기 쉬운 reverse Polish notation(RPN) 방법 사용
- infix expression:
- 
- reverse Polish notation:
- 
- 괄호 필요 없음
- 각 연산자가 어느 피연산자와 결합되는가를 명확히 표현할 수 있음
- 스택(stack) 자료구조 활용
- (1 - 2) * (4 + 5)
- 1 2 - 4 5 + *


# External Variables
- 컴퓨터프로그래밍기초
- ‹#›
- External Variables
- 외부 변수를 이용한 계산기 (Cont’d)
- 스택(stack)
- Similar to a stack of plates, adding or removing is only possible at the top.
- Stack (abstract data type). (2023, Apr 2). Retrieved from https://en.wikipedia.org/wiki/Stack_(abstract_data_type)


# External Variables
- 컴퓨터프로그래밍기초
- ‹#›
- External Variables
- 외부 변수를 이용한 계산기 (Cont’d)
- 피연산자는 스택에 push
- 연산자 처리 시 두 피연산자를 스택으로부터 pop
- 산술 연산은 두 개의 피연산자 필요
- 두 피연산자의 위치를 고려할 것
- 계산 결과 스택에 push


# External Variables
- 컴퓨터프로그래밍기초
- ‹#›
- External Variables
- 외부 변수를 이용한 계산기 (Cont’d)
- 프로그램 구조
- 
- 
- 
- 
- 
- 
- main 함수 내에 위 내용을 전부 구현한다면 코드가 상당히 길어질 수 있음
- 함수를 사용해 코드 분리 권장
- while (next operator or operand is not end-of-file indicator)
-         if (number)
-             push it
-         else if (operator)
-             pop operands
-             do operation
-             push result
-         else if (newline)
-             pop and print top of stack
-         else
-             error


# External Variables
- 컴퓨터프로그래밍기초
- ‹#›
- External Variables
- 외부 변수를 이용한 계산기 (Cont’d)
- getop 함수
- 사용자 정의 함수
- 사용자가 입력한 문자열로부터 연산자 또는 피연산자를 가져오는 함수
- push 함수
- 사용자 정의 함수
- 스택에 값을 기록하는 함수
- pop 함수
- 사용자 정의 함수
- 스택으로부터 값을 가져오는 함수
- #include <stdio.h>
-     #include <stdlib.h> /* for atof() */
-     #define MAXOP 100  /* max size of operand or operator */
-     #define NUMBER '0' /* signal that a number was found */
-     int getop(char []);
-     void push(double);
-     double pop(void);
- 
-     /* reverse Polish calculator */
-     int main(void)
-     {
-       int type;
-       double op2;
-       char s[MAXOP];
- 
-       while ((type = getop(s)) != EOF) {⋯
- 
-       return 0;
-     }
-     ⋯


# External Variables
- 컴퓨터프로그래밍기초
- ‹#›
- External Variables
- 외부 변수를 이용한 계산기 (Cont’d)
-, / 연산 시 pop 연산한 결과를 변수에 한 번 기록해야 함
- 연산자는 평가 우선순위와 평가 시 결합 방향은 정의되어 있지만 평가 순서는 논리 연산자, 삼항 연산자, 콤마 연산자 외엔 정의되어 있지 않음
-  +, * 연산은 pop 함수의 호출 순서에 독립적인 반면, -, / 연산은 pop 함수의 호출 순서에 의존적임
- while ((type = getop(s)) != EOF) {
-         switch (type) {
-           case NUMBER:
-             push(atof(s));
-             break;
-           case '+':
-             push(pop() + pop());
-             break;
-           case '*':
-             push(pop() * pop());
-             break;
-           case '-':
-             op2 = pop();
-             push(pop() - op2); /* push(pop() – pop()): Error! */
-             break;
-           case '/':
-             op2 = pop();
-             if (op2 != 0.0)
-               push(pop() / op2);
-             else
-               printf("error: zero divisor\n");
-             break;
-           case '\n':
-             printf("\t%.8g\n", pop());
-             break;
-           default:
-             printf("error: unknown command %s\n", s);
-             break;
-           }
-       }


# External Variables
- 컴퓨터프로그래밍기초
- ‹#›
- External Variables
- 외부 변수를 이용한 계산기 (Cont’d)
- 스택(val[MAXVAL])과 스택 포인터 (sp)는 외부 변수(전역 변수)
- 스택과 스택 포인터는 main 함수 이후에 선언
- 감춰진 상태(scope rules)이므로 main 함수에서 접근 불가
- push 함수와 pop 함수 사용 가능
- ⋯  
-     #define MAXVAL 100  /* maximum depth of val stack */
-     int sp = 0;         /* next free stack position */
-     double val[MAXVAL]; /* value stack */
-     /* push: push f onto value stack */
-     void push(double f)
-     {
-       if (sp < MAXVAL)
-         val[sp++] = f;
-       else
-         printf("error: stack full, can't push %g\n", f);
-     }
-     /* pop: pop and return top value from stack */
-     double pop(void)
-     {
-       if (sp > 0)
-         return val[--sp];
-       printf("error: stack empty\n");
-       return 0.0;
-     }
-     ⋯


# External Variables
- 컴퓨터프로그래밍기초
- ‹#›
- External Variables
- 외부 변수를 이용한 계산기 (Cont’d)
- 사용자가 입력한 문자열을 분해해 순차적으로 연산자 또는 피연산자를 반환:
- 사용자가 입력한 문자열로부터 문자 하나씩 읽어옴(사용자 정의 함수 getch)
- 읽어온 문자들을 조합해 연산자 혹은 숫자 문자열 반환
- 아직 입력이 남아있는 경우 이미 읽어온 문자를 다시 읽기 전 상태로 되돌림(사용자 정의 함수 ungetch)
- ⋯
-     #include <ctype.h>
-     int getch(void);
-     void ungetch(int);
-     /* getop: get next character or numeric operand */
-     int getop(char s[])
-     {
-       int i, c;
-       while ((s[0] = c = getch()) == ' ' || c == '\t') {}
-       s[1] = '\0';
-       if (!isdigit(c) && c != '.')
-         return c;     /* not a number */
-       i = 0;
-       if (isdigit(c)) /* collect integer part */
-         while (isdigit(s[++i] = c = getch())) {}
-       if (c == '.')   /* collect fraction part */
-         while (isdigit(s[++i] = c = getch())) {}
-       s[i] = '\0';
-       if (c != EOF)
-         ungetch(c);
-       return NUMBER;
-     }
-     ⋯


# External Variables
- 컴퓨터프로그래밍기초
- ‹#›
- External Variables
- 외부 변수를 이용한 계산기 (Cont’d)
- 사용자가 입력한 문자열로부터 문자를 하나씩 읽어와 연산자 또는 피연산자로 분해하는 과정 중에 문자를 더 읽어올 수 있음
- 프로그램은 문자열로부터 얼마큼의 문자를 읽어와야 하는지 미리 알 수 없음
- e.g. 숫자 문자열 수집 중 숫자 문자가 아닌 문자를 읽은 상태
- ⋯
-     #define BUFSIZE 100
-     char buf[BUFSIZE]; /* buffer for ungetch */
-     int bufp = 0;      /* next free position in buf */
-     int getch(void)    /* get a (possibly pushed-back) character */
-     {
-       return (bufp > 0) ? buf[--bufp] : getchar();
-     }
-     void ungetch(int c) /* push character back on input */
-     {
-       if (bufp >= BUFSIZE)
-         printf("ungetch: too many characters\n");
-       else
-         buf[bufp++] = c;
-     }


# External Variables
- 컴퓨터프로그래밍기초
- ‹#›
- External Variables
- 외부 변수를 이용한 계산기 (Cont’d)
- 문자를 필요한 것보다 더 읽었을 때, 이를 읽기 전 상태로 되돌리는 것처럼 처리할 수 있음
- 버퍼(buf[BUFSIZE])와 버퍼 포인터(bufp)를 외부 변수로 선언해 getch 함수와 ungetch 함수가 사용할 수 있도록 구현
- ⋯
-     #define BUFSIZE 100
-     char buf[BUFSIZE]; /* buffer for ungetch */
-     int bufp = 0;      /* next free position in buf */
-     int getch(void)    /* get a (possibly pushed-back) character */
-     {
-       return (bufp > 0) ? buf[--bufp] : getchar();
-     }
-     void ungetch(int c) /* push character back on input */
-     {
-       if (bufp >= BUFSIZE)
-         printf("ungetch: too many characters\n");
-       else
-         buf[bufp++] = c;
-     }


# Scope Rules
- 컴퓨터프로그래밍기초
- ‹#›
- Scope Rules
- 이름(name)의 범위(scope)는 해당 이름이 프로그램에서 사용될 수 있는 구간을 의미
- 내부 변수(자동 변수)는 해당 변수가 선언된 곳으로부터 함수 끝까지 유효
- 함수의 매개변수도 지역 변수
- 서로 다른 두 함수 내에 같은 이름의 변수를 선언하여도 두 변수는 서로 다른 범위에 속해 있으므로 서로 다른 변수로 간주됨
- #include <stdio.h>
-     void foo(int);
-     int main(void)
-     {
-       int a = 100;
-       foo(a);
-       printf("%d\n", a);  /* 100 */
-       return 0;
-     }
-     void foo(int a)
-     {
-       a += 100;
-       printf("%d\n", a);  /* 200 */
-     }
- main:a
- foo:a


# Scope Rules
- 컴퓨터프로그래밍기초
- ‹#›
- Scope Rules
- 외부 변수 또는 함수의 범위
- 해당 선언 또는 정의 이후부터 컴파일되는 소스코드 파일의 끝까지 유효함
- push 함수와 pop 함수는 외부 변수 sp와 val에 접근 가능하지만, main 함수는 접근 불가
- #include <stdio.h>⋯
-     #define MAXOP 100  /* max size of operand or operator */
-     #define NUMBER '0' /* signal that a number was found */
-     int getop(char []);
-     void push(double);
-     double pop(void);
- 
-     /* reverse Polish calculator */
-     int main(void)⋯
-     #define MAXVAL 100  /* maximum depth of val stack */
-     int sp = 0;         /* next free stack position */
-     double val[MAXVAL]; /* value stack */
-     /* push: push f onto value stack */
-     void push(double f)⋯
-     /* pop: pop and return top value from stack */
-     double pop(void)⋯
-     ⋯
- sp
- val


# Scope Rules
- 컴퓨터프로그래밍기초
- ‹#›
- Scope Rules
- 외부 변수가 다른 파일에 정의되어 있거나, 외부 변수가 정의되기 전에 해당 변수를 사용해야 하는 경우에는 extern 선언 필요
- 외부 변수 선언(external variable declarations)은 외부 변수의 속성을 컴파일러에 알림
- 
- 외부 변수 정의(external variable definitions)는 외부 변수의 속성을 컴파일러에 알리고 해당 변수가 사용될 공간을 메모리에 할당
- extern int sp = 0;         /* next free stack position */
-     extern double val[MAXVAL]; /* value stack */
- int sp = 0;         /* next free stack position */
-     double val[MAXVAL]; /* value stack */


# Scope Rules
- 컴퓨터프로그래밍기초
- ‹#›
- Scope Rules
- 외부 변수 정의는 한 번만 등장해야 함
- 프로그램을 구성하는 파일이 여러 개라면, 외부 변수 정의는 여러 파일 중 한 곳에만 정의되어야 함
- 외부 변수 선언(extern)은 여러 번 등장할 수 있으며, 외부 변수를 정의한 파일 내에 외부 변수의 선언이 등장할 수도 있음(optional)
- 외부 변수를 정의할 때, 배열의 크기는 상수 값으로 지정해야 함
- 외부 변수의 초기화는 프로그램이 시작될 때 한 번 수행되며, 초기화 시 초기화에 사용되는 모든 값들이 확정되어 있어야 함


# Scope Rules
- 컴퓨터프로그래밍기초
- ‹#›
- Scope Rules
- 외부 변수 선언에서는 배열의 크기 생략 가능
- 
- 외부에 함수 선언 시 extern 키워드 사용은 선택 사항:
- all function declarations are considered as "extern" by default
- extern double val[]; /* value stack */


# Scope Rules
- 컴퓨터프로그래밍기초
- ‹#›
- Scope Rules
- 다른 파일에 정의되어 있는 외부 변수 사용 예:
- 외부 변수 선언이 함수 정의보다 위에 있음
- push 함수와 pop 함수에서 외부 변수 sp와 val 사용 가능


# Header Files
- 컴퓨터프로그래밍기초
- ‹#›
- Header Files
- 외부 변수를 이용한 계산기 프로그램을 여러 개의 소스코드 파일로 나누어 보면 아래와 같음


# Header Files
- 컴퓨터프로그래밍기초
- ‹#›
- Header Files
- 공통된 부분은 헤더 파일에 모아서 사용
- 상수, 함수의 선언 등
- 불필요한 코드 중복 줄일 수 있음
- 규모가 큰 프로그램에서는 한 개 이상의 헤더파일을 사용하기도 함


# Header Files
- 컴퓨터프로그래밍기초
- ‹#›
- Header Files
- 헤더 가드(header guard)
- 
- 
- 
- 
- 
- 헤더가 중복 사용되는 것을 방지하기 위함
- 헤더 가드를 사용하지 않으면 헤더 파일이 두 번 이상 프로그램에 포함될 수 있으며, 이는 중복 정의 문제를 일으킬 수 있음(error: redefinition of ...)
- #ifndef를 사용하면 헤더 가드를 구현할 수 있음


# Header Files
- 컴퓨터프로그래밍기초
- ‹#›
- Header Files
- 헤더 가드(header guard) (Cont’d)
- 
- 
- 
- 
- 
- 헤더 파일이 들어있는 폴더의 이름과 헤더 파일의 이름을 조합해 매크로 생성
- #pragma once를 사용하면 헤더 가드를 사용한 것과 동일한 역할 수행
- 몇몇 환경에서는 지원하지 않을 수도 있으므로 직접 #ifndef를 사용해 헤더 가드를 구현하는 것이 더 안전한 방법임
- pragma once: 4. Portability


# Static Variables
- 컴퓨터프로그래밍기초
- ‹#›
- Static Variables
- static 선언을 사용한 외부 변수
- 프로그램이 실행 전에 메모리에 적재(load)될 때, 외부 변수와 정적 변수는 메모리에 사용 공간이 할당됨
- loader가 실행될 프로그램을 저장장치로부터 메모리로 적재할 때, text(code), data(+.bss) 영역 설정
- 외부 정적 변수, 내부 정적 변수
- 
- 정적 변수(static variables) 선언 시 초기화가 생략되었다면 외부 변수처럼 0으로 초기화 됨
- Process Memory Layout. (2023, Apr 2). Retrieved from https://os.cs.luc.edu/processes.html#id1


# Static Variables
- 컴퓨터프로그래밍기초
- ‹#›
- Static Variables
- static으로 선언된 외부 이름은 다른 파일에서 사용 불가
- 외부 정적 함수 혹은 변수를 사용하기 위해 다른 파일에서 extern 선언을 하면 컴파일 오류 발생(invisible)
- 
- 
- 
- 
- 외부 정적 변수 sp, val
- 같은 파일에 있는 push 함수와 pop 함수는 접근 가능
- 다른 파일에서 extern 선언을 통해 sp, val 사용하면 컴파일 오류(invisible)
- static int sp = 0;         /* next free stack position */
-     static double val[MAXVAL]; /* value stack */
-     
-     /* push: push f onto value stack */
-     void push(double f)⋯    
-     /* pop: pop and return top value from stack */
-     double pop(void)⋯
-     ⋯


# Static Variables
- 컴퓨터프로그래밍기초
- ‹#›
- Static Variables
- static으로 선언된 내부 이름
- 해당 구역(함수) 내에서만 사용 가능
- 내부 정적 변수 선언 시 초기화가 생략되었다면 외부 변수처럼 0으로 초기화 됨
- void foo(void)
-     {
-       static int m;
-     }


# Register Variables
- 컴퓨터프로그래밍기초
- ‹#›
- Register Variables
- 컴파일러에게 매우 빈번히 사용되는 변수를 알릴 때 사용
- 
- 
- register 선언을 한 변수는 CPU의 레지스터에서 연산 될 수 있음
- 컴파일러는 register 선언을 따를 수도, 무시할 수도 있음
- 대다수의 최신 컴파일러는 컴파일 과정 중에 빈번히 사용되는 변수를 파악해 알아서 register 선언(automatically)
- Memory Hierarchy. (2023, Apr 2). Retrieved from https://www.cs.swarthmore.edu/~kwebb/cs31/f18/memhierarchy/mem_hierarchy.html
- void f(register int param)
-     {
-       register int exam;
-     }


# Block Structure
- 컴퓨터프로그래밍기초
- ‹#›
- Block Structure
- 블록 구조 내부에 변수를 선언할 수 있음
- 
- 
- 
- 
- 
- 변수의 범위는 블록 구조가 종료될 때까지 유효
- 블록 구조 내부의 자동 변수는 블록이 실행될 때마다 생성과 소멸 반복
- 블록 구조 내부의 정적 변수는 프로그램이 시작될 때 생성되고, 프로그램이 종료될 때까지 소멸되지 않음
- int i;
-     for (i = 0; i < 10; ++i) {
-       char c;
-       c = getchar();
-       /* ... Skipped ... */
-     }


# Block Structure
- 컴퓨터프로그래밍기초
- ‹#›
- Block Structure
- 블록 구조를 이용하면 매개변수를 포함한 자동 변수를 외부로부터 감출 수 있음
- 변수의 이름이 같더라도 서로 다른 영역에 속해 있다면 서로 다른 변수로 간주됨
- 
- 
- 
- 
- 블록 구조는 바깥 블록의 변수 사용을 피하거나 변수를 감출 때 유용하지만, 혼란과 오류를 일으킬 가능성이 높음
- 블록 구조를 이용한 변수 사용은 최대한 지양하고 꼭 필요한 경우에만 사용할 것
- int x;
-     int y;
-     void func(double x)
-     {
-       double y;
-       /* ... Skipped ... */
-     }


# Initialization
- 컴퓨터프로그래밍기초
- ‹#›
- Initialization
- 명시적 초기화(explicit initialization)가 생략된 경우:
- 외부 변수 또는 정적 변수는 0으로 초기화
- 자동 변수 또는 레지스터 변수는 초기화 값이 정해지지 않음(garbage)
- 하나의 값만 보관하는 변수(배열이 아닌 변수, scalar variable)의 이름 다음에 대입 기호(=)와 표현식이 등장하면 해당 변수에 표현식의 평가 값으로 초기화 수행
- int x = 1;
-     char squote = '\'';
-     long day = 1000L * 60L * 60L * 24L; /* milliseconds / day */


# Initialization
- 컴퓨터프로그래밍기초
- ‹#›
- Initialization
- 외부 변수와 정적 변수는 초기화에 상수 표현식만 사용 가능하며, 프로그램이 시작될 때 한 번만 초기화 수행
- 
- 내부 변수와 레지스터 변수는 초기화에 일반 표현식과 상수 표현식 모두 사용 가능하며, 내부 변수 또는 레지스터 변수가 속해있는 블록이 시작될 때마다 초기화 수행
- 일반 표현식에는 함수 호출 등 여러 표현식이 사용될 수 있음


# Initialization
- 컴퓨터프로그래밍기초
- ‹#›
- Initialization
- 외부 변수 또는 정적 변수는 명시적 초기화가 생략되더라도 0으로 초기화
- 자동 변수는 명시적 초기화가 생략되었을 경우 쓰레기 값을 가짐
- 자동 변수의 초기화는 선언과 대입문의 약칭(shorthand)
- 변수 선언 후 대입문을 사용하느냐 초기화를 사용하느냐는 취향 문제
- 보통 변수의 선언과 대입문을 구분함:
- 변수 선언에 초기화가 섞여 있으면 가독성이 떨어짐
- 자동 변수의 선언을 한 뒤에 각 변수들이 실제로 사용되기 전에 명시적으로 대입문을 사용하면 해당 변수의 역할 또는 의미를 나타낼 수 있음
- 자동 변수의 선언과 대입문을 분리할 경우 대입문이 누락되지 않도록 주의할 것


# Initialization
- 컴퓨터프로그래밍기초
- ‹#›
- Initialization
- 배열 초기화
- 중괄호 안에 값들을 입력
- 값 구분에 콤마(,) 사용
- 
- 배열 초기화 시 크기가 생략된 경우:
- 컴파일러가 중괄호 안에 위치한 값들의 개수를 계산하여 크기를 결정함
- 
- 배열 초기화 시 크기가 주어진 경우:
- 중괄호 안에 위치한 값들의 개수가 크기보다 적으면 나머지 요소들의 값을 0으로 초기화
- 중괄호 안에 위치한 값들의 개수가 크기보다 많으면 오류 발생
- int days[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
- int arr[10] = { 0 }; /* 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 */


# Initialization
- 컴퓨터프로그래밍기초
- ‹#›
- Initialization
- 문자열 초기화
- 중괄호나 콤마를 사용하지 않고 문자열을 사용해 초기화할 수 있음
- 
- 
- 문자열 뒤에는 항상 널('\0') 문자가 사용됨
- 
- 배열 초기화 시 반복자를 사용하거나, 앞 요소를 건너뛰고 중간 요소만 초기화할 순 없음
- char pattern[] = "ould";
-     /* is a shorthand for the longer but equivalent */
-     char pattern[] = { 'o', 'u', 'l', 'd', '\0' };


# Recursion
- 컴퓨터프로그래밍기초
- ‹#›
- Recursion
- 임의의 함수가 자기 자신을 재호출하는 형태
- Assign3: Testing and debugging core recursive functions. (2023, Apr 2). Retrieved from https://web.stanford.edu/class/archive/cs/cs106b/cs106b.1208/assignments/assign3/fundamental-warmup


# Recursion
- 컴퓨터프로그래밍기초
- ‹#›
- Recursion
- 3장에서 정의한 itoa 함수는 reverse 함수를 사용해 뒤집힌 순서를 올바르게 출력
- 재귀를 사용하면 뒤집힌 숫자를 올바르게 출력할 수 있음
- /* itoa: convert n to characters in s */
-     void itoa(int n, char s[])
-     {
-       int i, sign;
-       if ((sign = n) < 0) /* record sign */
-         n = (-n); /* make n positive */
-       i = 0;
-       do {
-         s[i++] = (n % 10) + '0'; /* get next digit */
-       } while ((n /= 10) > 0); /* delete it */
-       if (sign < 0)
-         s[i++] = '-';
-       s[i] = '\0';
-       /* not a standard library */
-       reverse(s);
-     }


# Recursion
- 컴퓨터프로그래밍기초
- ‹#›
- Recursion
- 함수가 재귀적으로 호출될 때마다 자동 변수들은 새로 할당됨
- 서로 다른 메모리 구역에 할당
- 이전에 호출된 함수에서의 변수들과는 서로 다른 변수
- #include <stdio.h>
-     /* printd: print n in decimal */
-     void printd(int n)
-     {
-       if (n < 0) {
-         putchar('-');
-         n = -n;
-       }
-       if (n / 10)
-         printd(n / 10);
-       putchar(n % 10 + '0');
-     }
-     int main(void)
-     {
-       printd(123);
-       return 0;
-     }


# Recursion
- 컴퓨터프로그래밍기초
- ‹#›
- Recursion
- 재귀 함수의 동작 흐름


# Recursion
- 컴퓨터프로그래밍기초
- ‹#›
- Recursion
- 퀵 정렬(quicksort)
- a sorting algorithm developed by C. A. R. Hoare in 1962
- <stdlib.h> 헤더 파일 내에 qsort 함수가 정의되어 있음
- 
- 정렬되지 않은 배열을 오름차순 정렬
- 재귀 함수를 이용하여 구현
- #include <stdio.h>
-     enum {
-       SIZE = 9
-     };
-     /* qsort: sort v[left]...v[right] into increasing order */
-     void qsort(int v[], int left, int right);
-     /* swap: interchange v[i] and v[j] */
-     void swap(int v[], int i, int j);
-     int main(void)
-     {
-       int arr[SIZE] = { 16, 4, 12, 9, 13, 15, 1, 8, 11 };
-       int i;
-       printf("Before: ");
-       for (i = 0; i < SIZE; ++i)
-         printf("%2d ", arr[i]);
-       putchar('\n');
-       qsort(arr, 0, SIZE - 1);
-       printf("After : ");
-       for (i = 0; i < SIZE; ++i)
-         printf("%2d ", arr[i]);
-       putchar('\n');
-       return 0;
-     }
-     ⋯


# Recursion
- 컴퓨터프로그래밍기초
- ‹#›
- Recursion
- 퀵 정렬(quicksort) (Cont’d)
- ⋯
-     void qsort(int v[], int left, int right)
-     {
-       int i, last;
-       void swap(int v[], int i, int j);
-       if (left >= right) /* do nothing if array contains */
-         return;          /* fewer than two elements */
-       swap(v, left, (left + right) / 2);  /* move partition elem */
-       last = left; /* to v[0] */
-       for (i = left + 1; i <= right; ++i) { /* partition */
-         if (v[i] < v[left])
-           swap(v, ++last, i);
-       }
-       swap(v, left, last); /* restore partition elem */
-       qsort(v, left, last - 1);
-       qsort(v, last + 1, right);
-     }
-     /* swap: interchange v[i] and v[j] */
-     void swap(int v[], int i, int j)
-     {
-       int temp;
-       temp = v[i];
-       v[i] = v[j];
-       v[j] = temp;
-     }


# Recursion
- 컴퓨터프로그래밍기초
- ‹#›
- Recursion
- 퀵 정렬(quicksort) (Cont’d)
- ⋯
-     void qsort(int v[], int left, int right)
-     {
-       int i, last;
-       void swap(int v[], int i, int j);
-       if (left >= right) /* do nothing if array contains */
-         return;          /* fewer than two elements */
-       swap(v, left, (left + right) / 2);  /* move partition elem */
-       last = left; /* to v[0] */
-       for (i = left + 1; i <= right; ++i) { /* partition */
-         if (v[i] < v[left])
-           swap(v, ++last, i);
-       }
-       swap(v, left, last); /* restore partition elem */
-       qsort(v, left, last - 1);
-       qsort(v, last + 1, right);
-     }
-     /* swap: interchange v[i] and v[j] */
-     void swap(int v[], int i, int j)
-     {
-       int temp;
-       temp = v[i];
-       v[i] = v[j];
-       v[j] = temp;
-     }


# Recursion
- 컴퓨터프로그래밍기초
- ‹#›
- Recursion
- 퀵 정렬(quicksort) (Cont’d)
- ⋯
-     void qsort(int v[], int left, int right)
-     {
-       int i, last;
-       void swap(int v[], int i, int j);
-       if (left >= right) /* do nothing if array contains */
-         return;          /* fewer than two elements */
-       swap(v, left, (left + right) / 2);  /* move partition elem */
-       last = left; /* to v[0] */
-       for (i = left + 1; i <= right; ++i) { /* partition */
-         if (v[i] < v[left])
-           swap(v, ++last, i);
-       }
-       swap(v, left, last); /* restore partition elem */
-       qsort(v, left, last - 1);
-       qsort(v, last + 1, right);
-     }
-     /* swap: interchange v[i] and v[j] */
-     void swap(int v[], int i, int j)
-     {
-       int temp;
-       temp = v[i];
-       v[i] = v[j];
-       v[j] = temp;
-     }


# Recursion
- 컴퓨터프로그래밍기초
- ‹#›
- Recursion
- 몇몇 경우에서는 재귀 함수를 사용하면 코드를 간결하고 명확하게 작성할 수 있지만, 메모리(stack)를 많이 사용하고 동작이 느리다는 단점이 있음


# The C Preprocessor
- 컴퓨터프로그래밍기초
- ‹#›
- The C Preprocessor
- 컴파일 과정 중 제일 먼저 수행
- 전처리 과정
- 전처리 과정에서 수행되는 주요 작업들:
- 파일 삽입(file inclusion)
- 매크로 치환(macro substitution)
- 조건부 포함(conditional inclusion)


# The C Preprocessor
- 컴퓨터프로그래밍기초
- ‹#›
- The C Preprocessor
- 파일 삽입(file inclusion)
- 
- #include 문이 위치한 곳에 filename 내용 삽입
- filename 찾는 순서:
- filename 주위에 쌍따옴표("")가 있으면 소스코드 파일이 위치한 곳에 filename이 있는지 탐색
- filename 주위에 꺽쇠(<>)가 있으면 컴파일러 설치 시 같이 설치된 헤더 파일들이 위치한 곳에 filename이 있는지 탐색
- #include 문은 소스코드 파일 시작 부분에 여러 줄 사용될 수 있음
- #include 문 대상 파일이 수정되었을 경우, 해당 파일을 포함하는 소스코드 파일은 다시 컴파일해야 함
- #include <filename>
-     #include "filename"


# The C Preprocessor
- 컴퓨터프로그래밍기초
- ‹#›
- The C Preprocessor
- 매크로 치환(macro substitution)
- 
- name은 replacement_text로 치환됨
- name은 변수명 규칙을 따르며, 보통 대문자로 작성하는 것이 관례
- 
- 매크로는 #define 문 이후부터 컴파일되는 소스코드 파일의 끝까지 유효
- replacement_text 마지막에 세미콜론을 붙이지 않는 것에 유의
- #define 문 사용 시 이전 매크로 정의 사용 가능
- #define name replacement_text
- #define HELLO WORLD
-     #define HI HELLO  /* HI -> WORLD */
- #define forever for(;;) /* infinite loop; the token forever is possible but not recommended  */


# The C Preprocessor
- 컴퓨터프로그래밍기초
- ‹#›
- The C Preprocessor
- 매크로 치환(macro substitution) (Cont’d)
- replacement_text가 한 줄이 넘어갈 정도로 길어지면 연결 표시를 의미하는 문자인 \를 행 끝에 삽입
- 
- 
- replacement_text를 여러 줄 사용하고자 할 때 주의사항
- 
- 
- stmt1만 if문에 대응되며, 나머지 stmt2, stmt3은 일반 문장으로 처리
- #define foo stmt1; \
-                 stmt2; \
-                 stmt3
- if (expression)
-       foo;
- if (expression)
-       stmt1;
-       stmt2;
-       stmt3;


# The C Preprocessor
- 컴퓨터프로그래밍기초
- ‹#›
- The C Preprocessor
- 매크로 치환(macro substitution) (Cont’d)
- replacement_text를 여러 줄 사용하고자 할 때 do-while 문을 사용하면 안전하게 처리할 수 있음
- 
- 
- 
- 
- 
- 
- do-while 문을 단일문으로 처리
- if (expression)
-       foo;
- if (expression)
-       do {
-         stmt1;
-         stmt2;
-         stmt3;      
-       } while (0);
- #define foo do { \
-       stmt1;         \
-       stmt2;         \
-       stmt3;         \
-     } while (0)      \


# The C Preprocessor
- 컴퓨터프로그래밍기초
- ‹#›
- The C Preprocessor
- 매크로 치환(macro substitution) (Cont’d)
- #define 문에 의해 정의된 이름(token) 양 옆에 큰따옴표를 사용하거나 이름이 정확하지 않으면 치환은 발생하지 않음
- #define TOKEN "token"
- 
-     printf("%s", "TOKEN");  /* the string "TOKEN" is not the token TOKEN
-     printf(“%s”, TOKENIZER);  /* the token TOKENIZER is not the same with the token TOKEN


# The C Preprocessor
- 컴퓨터프로그래밍기초
- ‹#›
- The C Preprocessor
- 매크로 치환(macro substitution) (Cont’d)
- 전달인자를 넘겨줄 수 있음
- 
- 
- 
- 함수와 유사해 보이지만, #define 문에 의해 정의된 이름은 전처리 과정을 거치면 해당 이름에 대응되는 텍스트로 변환됨(in-line code)
- 자료형을 상관하지 않음
- MAX 매크로는 두 전달인자가 int 형이라면 int 형에 대해 대소 비교를 수행하고, 두 전달인자가  double 형이라면 double 형에 대해 대소 비교를 수행
- 잘못된 전달인자를 넘겨주면 오류가 발생할 수 있음
- #define MAX(a, b) ((a > b) ? a : b)
- 
-     int x = 100;
-     int y = 200;
-     printf("%d\n", MAX(x, y)); /* printf("%d\n", ((x > y) ? x : y)) */


# The C Preprocessor
- 컴퓨터프로그래밍기초
- ‹#›
- The C Preprocessor
- 매크로 치환(macro substitution) (Cont’d)
- 매크로는 함수보다 실행시간 측면에서 더 빠름(in-line code)
- <stdio.h> 함수 중 일부는 매크로로 정의해 사용하기도 함
- getchar 함수, putchar 함수
- #undef 문은 #define 문으로 정의되어 있는 매크로 해제 시 사용
- e.g. getchar 매크로를 해제 후 함수로서 사용하고자 할 경우:
- #undef getchar
-     int getchar(void)⋯


# The C Preprocessor
- 컴퓨터프로그래밍기초
- ‹#›
- The C Preprocessor
- 매크로 치환(macro substitution) (Cont’d)
- 부수 효과(side-effect)가 발생하는 경우 주의해야 함
- 
- 
- 본래 의도는 변수 i와 변수 j의 원본 값에 대해 대소 비교를 한 뒤, 두 변수에 대해 1씩 증가하고자 하였음
- 두 변수 i와 j 중에서 큰 값은 ++ 연산이 두 번 수행됨(side-effect)
- 전달인자 사용 시 평가 순서를 올바르게 하기 위해 괄호를 사용해야 하는 경우가 있음
- #define MAX(a, b) ((a > b) ? a : b)
- 
-     MAX(i++, j++);  /* ((i++ > j++) ? i++ : j++) */
- #define SQUARE(x) x * x
- 
-     SQUARE(x + 1);  /* x + 1 * x + 1 */
- #define SQUARE(x) (x) * (x)
- 
-     SQUARE(x + 1);  /* (x + 1) * (x + 1) */


# The C Preprocessor
- 컴퓨터프로그래밍기초
- ‹#›
- The C Preprocessor
- 매크로 치환(macro substitution) (Cont’d)
- 매크로에 전달인자를 넘겨줄 경우 문자열을 사용할 수 없음
- 매크로 전달인자에 큰따옴표(")가 있을 경우 \" 로 대치되며, 역슬래시(\)는 \\로 대치됨
- replacement_text 앞에 # 문자를 사용하면 전처리 과정에서 매크로 전달인자를 문자열로 변환할 수 있음
- 
- 
- dprint(x/y)는 전처리 과정을 거치면 다음과 같이 변환:
- #define dprint(expr) printf(#expr " = %g\n", expr)
- 
-     dprint(x/y);
- printf("x/y" " = &g\n", x/y);
-     /* the strings are concatenated, so the effect is */
-     printf("x/y = &g\n", x/y);


# The C Preprocessor
- 컴퓨터프로그래밍기초
- ‹#›
- The C Preprocessor
- 매크로 치환(macro substitution) (Cont’d)
- 전달인자를 결합하고자 할 때 ## 연산자 사용
- ## 연산자 사용 시 전처리 과정에서 ## 연산자와 그 주변에 있는 공백은 제거됨
- 
- e.g. ## 연산자 사용 예
- /* paste(name, 1) creates the token name1 */
-     #define paste(front, back) front ## back
- #include <stdio.h>
- #define decode(s,t,u,m,p,e,d) m ## s ## u ## t
- #define begin decode(a,n,i,m,a,t,e)
- int begin()
- {
-     printf("Stumped?\n");
- }


# The C Preprocessor
- 컴퓨터프로그래밍기초
- ‹#›
- The C Preprocessor
- 조건부 포함(conditional inclusion)
- 전처리 단계에서 코드를 선택적으로 포함시키는 방법
- 조건을 만족하지 않는 구간은 전처리 시 마치 없는 코드인 것처럼 무시됨
- #if
- 상수 표현식을 평가한 결과가 0이 아니면 참으로 간주
- 표현식 평가 결과가 참일 경우 #endif, #elif, #else 이전까지의 문장들을 포함시킴
- #if SYSTEM == SYSV
-         #define HDR "sysv.h"
-     #elif SYSTEM == BSD
-         #define HDR "bsd.h"
-     #elif SYSTEM == MSDOS
-         #define HDR "msdos.h"
-     #else
-         #define HDR "default.h"
-     #endif
-     #include HDR


# The C Preprocessor
- 컴퓨터프로그래밍기초
- ‹#›
- The C Preprocessor
- 조건부 포함(conditional inclusion)
- #if defined(name), #ifdef
- name이 정의되었다면 참(1), 정의되지 않았다면 거짓(0)
- #if !defined(name), #ifndef
- name이 정의되지 않았다면 참(1), 정의되었다면 거짓(0)
- e.g. 파일을 여러 번 포함하는 것을 방지하는 코드(헤더 가드)
- #ifndef HDR
- #define HDR
- /* contents of hdr.h go here */
- #endif
- #if !defined(HDR)
-     #define HDR
-     /* contents of hdr.h go here */
-     #endif

