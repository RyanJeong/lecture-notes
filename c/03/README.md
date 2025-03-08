# 컴퓨터프로그래밍기초
- 컴퓨터프로그래밍기초
- Control Flow


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


# Goals of this Chapter
- 컴퓨터프로그래밍기초
- 3
- Goals of this Chapter
- 문장과 블록
- 제어흐름
- if 문
- switch 문
- for 반복문
- while 반복문
- do-while 반복문
- break 문
- continue 문
- goto 문과 레이블


# Statements and Blocks
- 컴퓨터프로그래밍기초
- 4
- Statements and Blocks
- 문장(statement)
- 문장의 끝에는 항상 세미콜론(;)이 위치하며, 표현식(expression) + ; 형태로 표현
- 
- 
- 복합문(compound statement or block) 
- 중괄호({})를 사용해 여러 개의 선언문 또는 문장을 묶는 데 사용
- 함수의 내용, while, for, if-else, ...
- 컴파일러는 코드 분석 시 복합문을 단일 문장(single statement)으로 간주하며, 복합문 뒤에는 세미콜론을 사용하지 않음
- x = 0;
-     ++i;
-     printf("Hello, world!");


# If-Else
- 컴퓨터프로그래밍기초
- 5
- If-Else
- 조건 표현에 사용
- 
- 
- 조건부(표현식)의 평가 결과가 0인지 아닌지를 검사
- expression 평가 결과가 0이면 거짓(false), 0이 아니면 참(true)으로 간주
- 복잡한 조건부는 가독성(readability)이 좋지 못하므로, 간결하게 표현할 것
- 
- 
- else는 선택사항(optional)이며, expression 평가 결과가 참이면 statement1, expression 평가 결과가 거짓이면서 else가 존재한다면 statement2 수행
- expression이 거짓이면서 else가 존재하지 않는다면 아무런 동작을 수행하지 않음
- if (expression)
-       statement1
-     else
-       statement2
- /* if (expression != 0) */
-     if (expression)


# If-Else
- 컴퓨터프로그래밍기초
- 6
- If-Else
- if 문의 평가 결과는 단일문
- 
- 
- statement에는 하나의 단일 문장 또는 복합문이 사용될 수 있음
- statement가 단일문일 경우 괄호 생략 가능
- statement가 복합문일 경우 괄호 필수
- if (expression)
-       statement1
-     else
-       statement2
- if (expression) /* if the expression is true */
-       statement1
-     else
-       statement2
- if (expression) /* if the expression is false */
-       statement1
-     else
-       statement2


# If-Else
- 컴퓨터프로그래밍기초
- 7
- If-Else
- 모호성(ambiguity)
- 중첩된(nested) if 문에서 else가 생략됨에 따라 발생하는 문제
- 
- 
- 
- else는 사용된 if 문 중에서 가장 가까운 if 문과 대응
- if (n > 0)
-       if (a > b)
-         z = a;
-       else
-         z = b;


# If-Else
- 컴퓨터프로그래밍기초
- 8
- If-Else
- 모호성(ambiguity) (Cont’d)
- 다음 코드에서 else는 어느 if 문에 대응될 것인가?
- 
- 
- 
- else가 바깥 if 문과 대응되어야 한다면 괄호를 사용해 if 문의 범위를 명확하게 표현해야 함
- if (n > 0)
-       if (a > b)
-         z = a;
-     else
-       z = b;
- if (n > 0) {
-       if (a > b) 
-         z = a;
-     } else {
-       z = b;
-     }


# If-Else
- 컴퓨터프로그래밍기초
- 9
- If-Else
- 모호성(ambiguity) (Cont’d)
- 모호성 문제는 컴파일 시 오류를 발생하지 않으며, 이러한 유형의 오류 발견은 쉽지 않음
- 프로그램의 오동작(논리 오류, logical error) 초래
- if (n >= 0)
-       for (i = 0; i < n; ++i) 
-         if (s[i] > 0) {
-           printf("positive number found\n");
-           return i;
-         }
-     else /* WRONG */
-       printf(“error – n is negative\n");


# If-Else
- 컴퓨터프로그래밍기초
- 10
- If-Else
- 모호성(ambiguity) (Cont’d)
- 컴파일러는 들여쓰기 수준을 고려해 코드를 분석하는 것이 아닌 정해진 문법 규칙에 따라 코드를 분석
- 중괄호를 사용해 if 문의 범위를 명확히 표현하면 모호성 문제를 해결할 수 있음
- if (n >= 0) {
-       for (i = 0; i < n; ++i) 
-         if (s[i] > 0) {
-           printf("positive number found\n");
-           return i;
-         }
-     } else {  /* WRONG */
-       printf(“error – n is negative\n");
-     }


# If-Else
- 컴퓨터프로그래밍기초
- 11
- If-Else
- 다중 조건 검사를 할 수 있는 구조(construction) 1
- 
- 
- 
- 
- 여러 개의 if 문이 중첩된 형태 
- e.g. expression2가 참이면 statement2 수행
- 마지막 else는 해당 구조의 모든 표현식이 거짓일 경우 가리킴
- 열거된 조건들을 만족하지 못하는 예외를 처리하기 위한 목적으로 사용됨
- 마지막 else 생략 가능
- if (expression1)
-       statement1
-     else if (expression2)
-       statement2
-     else if (expression3)
-       statement3
-     else
-       statement4


# If-Else
- 컴퓨터프로그래밍기초
- 12
- If-Else
- 이진 탐색(binary search)
- 이미 정렬되어 있는 배열 안에 찾고자 하는 값이 있는지 탐색하는 알고리즘 
- 세 가지 조건 검사를 통해 탐색 수행
- Binary search algorithm. (2023, March 25). Retrieved from https://en.wikipedia.org/wiki/Binary_search_algorithm


# If-Else
- 컴퓨터프로그래밍기초
- 13
- If-Else
- 이진 탐색(binary search) (cont’d)
- <stdlib.h> 헤더 파일 내에 bsearch 함수가 정의되어 있음
- e.g. 4를 찾고자 하는 경우:
- /* binsearch: find x in v[O] <= v[1] <= ... <= v[n-1] */
-     int binsearch(int x, int v[], int n)
-     {
-       int low, high, mid;
-       low = 0;
-       high = n - 1;
-       while (low <= high) {
-         mid = (low + high) / 2;
-         if (x < v[mid])
-           high = mid - 1;
-         else if (x > v[mid])
-           low = mid + 1;
-         else
-           return mid; /* found match */
-       }
-       return -1; /* no match */
-     }
- low
- high
- mid
- low
- high
- mid
- low
- high
- mid


# Switch
- 컴퓨터프로그래밍기초
- 14
- Switch
- 다중 조건 검사를 할 수 있는 구조 2
- 
- 
- switch 문의 표현식 평가 결과와 case 레이블의 상수 표현식의 값을 서로 비교해 switch 문의 시작 위치를 결정
- e.g. expression의 평가 결과와 const-expr2의 값이 서로 일치한다면, statement2 문장부터 계산 시작(statement1 문장은 무시됨)
- 모든 case 레이블의 상수 표현식은 서로 달라야 함
- default 레이블은 일반적으로 switch 문의 가장 아래에 위치하며, 생략 가능
- switch 문의 표현식 평가 결과가 주어진 case 레이블의 상수 표현식의 값과 모두 다르고, default 레이블이 생략되었다면 아무런 동작을 수행하지 않음
- switch (expression) {
-       case const-expr1: statement1
-       case const-expr2: statement2
-       defaults: statement
-     }
- switch (expression) { /* == const-expr1 */
-       case const-expr1: statement1
-       case const-expr2: statement2
-       defaults: statement
-     }
- switch (expression) { /* == const-expr2 */
-       case const-expr1: statement1
-       case const-expr2: statement2
-       defaults: statement
-     }


# Switch
- 컴퓨터프로그래밍기초
- 15
- Switch
- Else-if 구조를 switch 문으로 바꾼 예:
- #include <stdio.h>
-     /* count digits, white space, others */
-     int main(void)
-     {
-       int c, i, nwhite, nother, ndigit[10];
-       nwhite = nother = 0;
-       for (i = 0; i < 10; ++i)
-         ndigit[i] = 0;
-       while ((c = getchar()) != EOF) {
-         switch (c) {
-           case '0': case '1': case '2': case '3': case '4':
-           case '5': case '6': case '7': case '8': case '9':
-             ++ndigit[c-'0'];
-             break;
-           case ' ': case '\n': case '\t':
-             ++nwhite;
-             break;
-           default:
-             ++nother;
-             break;
-         }
-       }      /* ... skipped ... */      return 0;
-     }
- if (c >= '0' && c <= '9')
-       ++ndigit[c-'0'];
-     else if ((c == ' ') || (c == '\n') || (c == '\t'))
-       ++nwhite;
-     else
-       ++nother;


# Switch
- 컴퓨터프로그래밍기초
- 16
- Switch
- Else-if 구조를 switch 문으로 바꾼 예: (Cont’d)
- break 문
- switch 문을 벗어날 때 사용
- #include <stdio.h>
-     /* count digits, white space, others */
-     int main(void)
-     {
-       int c, i, nwhite, nother, ndigit[10];
-       nwhite = nother = 0;
-       for (i = 0; i < 10; ++i)
-         ndigit[i] = 0;
-       while ((c = getchar()) != EOF) {
-         switch (c) {
-           case '0': case '1': case '2': case '3': case '4':
-           case '5': case '6': case '7': case '8': case '9':
-             ++ndigit[c-'0'];
-             break;
-           case ' ': case '\n': case '\t':
-             ++nwhite;
-             break;
-           default:
-             ++nother;
-             break;
-         }
-       }      /* ... skipped ... */      return 0;
-     }


# Loops - While and For
- 컴퓨터프로그래밍기초
- 17
- Loops - While and For
- while 반복문
- 
- expression 평가:
- 참일 경우, statement 수행 후 expression 재평가
- 거짓일 경우, 반복문 종료
- while (expression)
-       statement


# Loops - While and For
- 컴퓨터프로그래밍기초
- 18
- Loops - While and For
- for 반복문
- 
- 
- for 문은 세 개의 항이 필요하며, 각 항은 세미콜론(;)으로 구분됨
- for 문의 각 항에는 표현식을 사용하며, 일반적으로 expr1에는 초기식, expr2에는 관계식, expr3에는 expr2 평가 결과에 영향을 주는 증감식 사용
- for 문의 각 항은 생략 가능하나, 세미콜론은 남겨두어야 함
- expr2 생략 시 for 문의 관계식은 항상 참인 상태가 됨
- 
- for 문 문장 내에 특별한 지시(e.g. break 문)가 없는 한 무한 반복
- expr1 
-     while (expr2) {
-       statement
-       expr3
-     }
- for (expr1; expr2; expr3)
-       statement
- for (;;)
-       statement


# Loops - While and For
- 컴퓨터프로그래밍기초
- 19
- Loops - While and For
- while 문과 for 문 중 어느 반복문을 써야 할까?
- largely a matter of personal preference
- 초기식과 증감식이 필요 없는 경우
- 
- 초기식과 증감식이 필요한 경우
- 
- 초기식, 증감식 등을 사용한다면, for 문 사용 권장
- for 문 헤더에 초기식, 관계식, 증감식을 한 번에 확인할 수 있으며, 이는 가독성을 높임
- while ((c = getchar()) != EOF) {}
- for (i = 0; s[i] >= '0' && s[i] <= '9'; ++i) {}


# Loops - While and For
- 컴퓨터프로그래밍기초
- 20
- Loops - While and For
- <stdlib.h> 헤더 파일 내에 atoi 함수가 정의되어 있음
- #include <ctype.h>
-     /* atoi: convert s to integer; version 2 */
-     int atoi(char s[])
-     {
-       int i, n, sign;
-       /* skip white space */
-       for (i = 0; isspace(s[i]); ++i) {}
-       sign = (s[i] == '-') ? (-1) : 1;
-       /* skip sign */
-       if ((s[i] == '+') || (s[i] == '-'))
-         ++i;
-       for (n = 0; isdigit(s[i]); ++i)
-         n = (n * 10) + (s[i] - '0');
-       return sign * n;
-     }


# Loops - While and For
- 컴퓨터프로그래밍기초
- 21
- Loops - While and For
- Shellsort algorithm
- 배열 안에 있는 값들을 정렬
- shellsort 함수는 사용자 정의 함수
- e.g. 11개의 정수 정렬 예:
- /* shellsort: sort v[0] ... v[n-1] into increasing order */
-     void shellsort(int v[], int n)
-     {
-       int gap, i, j, temp;
-       for (gap = (n / 2); gap > 0; gap /= 2) {
-         for (i = gap; i < n; ++i) {
-           for (j = i - gap; j >= 0 && v[j] > v[j+gap]; j -= gap) {
-             temp = v[j];
-             v[j] = v[j+gap];
-             v[j+gap] = temp;
-           }
-         }
-       }
-     }


# Loops - While and For
- 컴퓨터프로그래밍기초
- 22
- Loops - While and For
- 쉼표(,) 연산자
- 쉼표 연산자를 사용해 표현식들을 열거했다면, 열거된 표현식들은 왼쪽에서 오른쪽 방향으로 평가됨
- 쉼표 연산자를 사용해 열거된 표현식들의 평가 결과는 가장 오른쪽에 있는 표현식의 형과 값


# Loops - While and For
- 컴퓨터프로그래밍기초
- 23
- Loops - While and For
- reverse 함수는 사용자 정의 함수
- #include <string.h>
-     /*reverse: reverse string s in place*/
-     void reverse(char s[])
-     {
-       int c, i, j;
-       for (i = 0, j = (strlen(s) - 1); i < j; ++i, --j) {
-         c = s[i];
-         s[i] = s[j];
-         s[j] = c;
-       }
-     }


# Loops - While and For
- 컴퓨터프로그래밍기초
- 24
- Loops - While and For
- 쉼표 연산자와 표기는 같지만 쉼표 연산자가 아닌 경우:
- 왼쪽에서 오른쪽으로 평가됨을 보장하지 않음
- separate function arguments, variables in declarations, etc.
- 쉼표 연산자를 무분별하게 사용하면 가독성에 좋지 않음
- 쉼표 연산자가 유용한 경우:
- 문장들을 한 줄로 표현해야 할 때
- 
- 서로 연관된 표현식들이 짧게 표현된 경우
- #define TEST_MALLOC(x) ((x) = malloc(sizeof(*x)), assert(x))
- for (i = 0, j = (strlen(s) - 1); i < j; ++i, --j)
-       c = s[i], s[i] = s[j], s[j] = c;


# Loops - Do-While
- 컴퓨터프로그래밍기초
- 25
- Loops - Do-While
- 문장을 먼저 수행한 후에 조건 검사
- 
- 
- 조건의 참 거짓 여부와 관계 없이 statement가 무조건 한 번은 수행됨을 보장
- statement 수행 후, expression 평가:
- 참일 경우, statement 수행 후 expression 재평가
- 거짓일 경우, 반복문 종료
- 세미콜론이 사용됨에 주의할 것
- do-while 문의 문장이 단일 문장일 경우에도 중괄호를 사용할 것을 권장
- 
- 
- do-while 문을 while 문으로 착각할 수 있음
- do
-       statement
-     while (expression);
- do
-       s[i++] = (n % 10) + '0'; /* get next digit */
-     while ((n /= 10) > 0); /* delete it */


# Loops - Do-While
- 컴퓨터프로그래밍기초
- 26
- Loops - Do-While
- itoa 함수는 사용자 정의 함수
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
-       /* reverse function is not a standard library */
-       reverse(s);
-     }


# Break and Continue
- 컴퓨터프로그래밍기초
- 27
- Break and Continue
- break 문
- 구조를 벗어나는 데 사용되는 특별한 지시 중 하나
- switch 문, for 반복문, while 반복문, do-while 반복문을 벗어나고자 할 때 사용
- 
- trim 함수는 사용자 정의 함수
- #include <string.h>
-     /* trim: remove trailing blanks, tabs, newlines */
-     int trim(char s[])
-     {
-       int n;
-       for (n = (strlen(s) - 1); n >= 0; --n) {
-         if (s[n] != ' ' && s[n] != '\t' && s[n] != '\n')
-           break;
-       }
-       s[n+1] = '\0';
-       return n;
-     }


# Break and Continue
- 컴퓨터프로그래밍기초
- 28
- Break and Continue
- continue 문
- 반복문에서만 사용 가능
- 반복문 수행 중 continue 문을 만나면 뒤따르는 문장들 무시 가능:
- for 반복문은 증감식 부분으로 이동
- while, do-while 반복문은 조건부로 이동
- 반복문 내에 switch 문이 사용됐다면 switch 문 내에서도 사용 가능
- continue 문은 불필요한 코드 작성을 피하거나 들여쓰기 수준을 낮출 수 있음
- for (i = 0; i < n; ++i) {
-       if (a[i] < 0) /* skip negative elements */
-         continue;
-       /* do positive elements */
-     }


# Goto and Labels
- 컴퓨터프로그래밍기초
- 29
- Goto and Labels
- goto 문은 이론적으로 전혀 필요하지 않으며, goto 문은 충분히 다른 문법으로 대체할 수 있음
- 제어변수 사용, 사용자 정의 함수, etc.
- TCPL 책에서는 goto 문을 사용하지 않음
- 몇몇 경우에서는 goto 문이 상당히 유용함
- 중첩된 반복문 내부에서 오류 혹은 특별한 경우가 발생함에 따라 중첩된 반복문 구조를 한 번에 벗어나야 하는 경우
- break 문은 한 번에 한 개의 구조만 벗어날 수 있음
- 오류 처리 코드가 간단하지 않고(non-trivial), 오류가 여러 곳에서 발생할 가능성이 있는 경우


# Goto and Labels
- 컴퓨터프로그래밍기초
- 30
- Goto and Labels
- 레이블(labels)은 변수 이름과 동일한 형식을 가지며, 레이블 뒤에 콜론(:)이 사용됨
- 
- 레이블은 goto 문이 사용된 함수 내에 위치해야 함
- 레이블의 적용 범위는 레이블이 위치한 함수(지역) 전체
- 
- 레이블은 문장이 등장할 수 있는 위치에 어디든지 사용 가능


# Goto and Labels
- 컴퓨터프로그래밍기초
- 31
- Goto and Labels
- goto 문 사용 예:
- for (i = 0; i < n; ++i) {
-         for (j = 0; j < m; ++j) {
-           if (a[i] == b[j])
-             goto found;
-         }
-       }
-       /* didn't find any common elements */
- 
-     found:
-       /* got one: a[i] == b[j]*/
- int found = 0;
-     for (i = 0; (i < n) && !found; ++i) {
-       for (j = 0; (j < m) && !found; ++j) {
-         if (a[i] == b[j])
-           found = 1;
-       }
-     }
-     if (found)
-       /* got one: a[i] == b[j] */
-     else
-       /* didn't find any common element */

