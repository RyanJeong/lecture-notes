# 컴퓨터프로그래밍기초
- 컴퓨터프로그래밍기초
- Structures


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


# Goals of this Chapter
- 컴퓨터프로그래밍기초
- ‹#›
- Goals of this Chapter
- 구조체 이해
- 구조체 연산
- 구조체 포인터와 구조체 배열
- 구조체와 함수
- 자기참조구조체
- typedef
- Unions
- Bit-fields


# Basics of Structures
- 컴퓨터프로그래밍기초
- ‹#›
- Basics of Structures
- 구조체(structure)는 하나 이상의 변수들의 집합
- 서로 다른 형의 변수들을 묶을 수 있음
- e.g. 직원인사정보
- 
- 
- 
- 
- 
- 규모가 큰 프로그램은 서로 연관된 변수들을 구조체로 처리
- 구조체를 사용하면 각각의 변수들을 하나의 단위로써 처리 가능(convenient handling)
- enum {
-   LEN = 100
- };
- char name[LEN];              /* 이름 */
- char addr[LEN];              /* 주소 */
- int social_security_number;  /* 주민등록번호 */
- double salary;               /* 봉급 */
- /* ... SKIPPED ... */


# Basics of Structures
- 컴퓨터프로그래밍기초
- ‹#›
- Basics of Structures
- 간단한 구조체
- e.g. 좌표 표현
- 정수로 이루어진 x 좌표와 y 좌표의 점 위치를 표현
- 
- 
- 
- struct는 중괄호 안에 선언된 목록들이 구조체로 선언됨을 알림
- 태그(structure tag, point)는 구조체에 이름을 붙이며 선택사항
- 구조체 형 변수 선언 시 태그를 이용하면 중괄호 부분 생략 가능
- struct point {
-   int x;
-   int y;
- };


# Basics of Structures
- 컴퓨터프로그래밍기초
- ‹#›
- Basics of Structures
- 간단한 구조체 (Cont’d)
- e.g. 좌표 표현
- 정수로 이루어진 x 좌표와 y 좌표의 점 위치를 표현
- 
- 
- 
- 구조체 안에 속한 변수들(멤버변수, members)
- 멤버변수 이름, 구조체 이름, 일반 변수 이름은 문맥(context)에 의해 서로 구분되므로 서로 같은 이름 사용 가능
- int name;
- struct name {
-   int name;
- };
- struct point {
-   int x;
-   int y;
- };


# Basics of Structures
- 컴퓨터프로그래밍기초
- ‹#›
- Basics of Structures
- 구조체 선언은 새로운 형(type)을 선언함
- 새로운 구조체 형 선언은 저장공간을 차지하지 않음
- 구조체 선언 뒤에 이름을 나열해 구조체 형 변수들을 선언할 수 있음
- 
- 
- 변수 foo1, foo2는 struct foo 형으로 선언됨과 동시에 메모리에 사용할 수 있는 공간 할당
- 구조체 선언 뒤에 이름이 등장하지 않는다면, 새로운 구조체 형 선언만 수행(describe the shape of a structure)
- 구조체 형 변수를 선언할 경우에만 메모리 할당
- struct foo {
-   int x;
-   int y;
- } foo1, foo2;


# Basics of Structures
- 컴퓨터프로그래밍기초
- ‹#›
- Basics of Structures
- 구조체 선언 시 지정한 구조체 이름(structure tag)은 구조체 형 변수 선언을 간결하게 표현할 수 있음
- 멤버변수 명세 부분을 생략할 수 있음
- struct point {
-   int x;
-   int y;
- };
- /* case 1 */
- struct point pt1;
- /* case 2 */
- struct point {
-   int x;
-   int y;
- } pt2;
- /* case 3 */
- struct {
-   int x;
-   int y;
- } pt3;


# Basics of Structures
- 컴퓨터프로그래밍기초
- ‹#›
- Basics of Structures
- 표현식을 사용해 구조체 변수 선언과 동시에 초기화할 수 있음
- 전역변수는 상수 표현식만 사용 가능
- 지역변수는 상수 표현식과 일반 표현식 둘 다 사용 가능
- Compound literals:
- In C, a compound literal designates an unnamed object with static or automatic storage duration.
- struct point {
-   int x;
-   int y;
- };
- int a = 3;
- int b = 4;
- struct point global1 = { 3, 4 };    /* OK */
- struct point global2 = { a, b };    /* Error */
- struct point global3, global4;
- global3 = { 3, 4 };                 /* Error */
- global4 = (struct point) { 3, 4 };  /* Error */
- int main(void)
- {
-   int a = 5;
-   int b = 6;
-   struct point itnl1 = { 5, 6 };    /* OK */
-   struct point itnl2 = { a, b };    /* OK */
-   struct point itnl3, itnl4;
-   itnl3 = { a, b };                 /* Error */
-   itnl4 = (struct point) { a, b };  /* OK */
-   return 0;
- }


# Basics of Structures
- 컴퓨터프로그래밍기초
- ‹#›
- Basics of Structures
- 구조체 형 변수가 자동변수일 때, 구조체 변수 간 복사 또는 함수의 반환값을 사용해 초기화할 수 있음
- 함수의 반환형은 초기화할 구조체 형 변수의 형과 일치해야 함
- 구조체 형 전역변수는 상수 표현식이 사용되어야 하기 때문에 구조체 변수 간 복사 또는 함수 호출 사용 불가
- struct point {
-   int x;
-   int y;
- };
- struct point maxpt(void)
- {
-   struct point maxpt = { 320, 480 };
-   return maxpt;
- }
- int main(void)
- {
-   struct point p1 = maxpt();
-   struct point p2 = p1;
-   struct point p3, p4;
-   p3 = maxpt();
-   p4 = p2;
-   return 0;
- }


# Basics of Structures
- 컴퓨터프로그래밍기초
- ‹#›
- Basics of Structures
- 구조체의 멤버변수 참조 표현식
- . 연산자는 구조체 형 변수의 멤버변수에 접근함
- e.g. point 형 변수 pt의 멤버변수 출력
- 
- 
- 
- e.g. 좌표 (0, 0)으로부터 좌표 pt까지의 거리를 계산하여 출력
- struct point p1 = { 3, 4 };
-     /* x: 3, y: 4 */
-     printf("x: %d, y: %d\n", p1.x, p1.y);
- struct point pt = { 3, 4 };
-     double dist, sqrt(double);  /* sqrt is declared in math.h */
-     dist = sqrt((double) pt.x * pt.x + (double) pt.y * pt.y);
-     /* dist from (0, 0) to (3, 4) is 5.000000 */
-     printf("dist. from (0, 0) to (%d, %d) is %lf\n",
-         pt.x, pt.y, dist);


# Basics of Structures
- 컴퓨터프로그래밍기초
- ‹#›
- Basics of Structures
- 구조체는 중첩하여 표현할 수 있음
- e.g. 사각형을 표현할 수 있는 구조체
- 
- 
- 
- 
- 좌표 한 쌍은 사각형을 표현할 수 있음
- pt1은 사각형의 좌측 하단 좌표를 기록
- pt2는 사각형의 우측 상단 좌표를 기록
- 이름(tag)을 사용했으므로 struct rect 형 구조체 변수 선언 시 멤버변수 명세 부분 생략 가능
- struct rect {
-   struct point pt1;
-   struct point pt2;
- } screen;
- struct rect screen1;


# Basics of Structures
- 컴퓨터프로그래밍기초
- ‹#›
- Basics of Structures
- 구조체는 중첩하여 표현할 수 있음 (Cont’d)
- e.g. 변수 screen의 멤버변수 pt1의 멤버변수 x 접근
- printf("%d", screen.pt1.x);


# Structures and Functions
- 컴퓨터프로그래밍기초
- ‹#›
- Structures and Functions
- 구조체에 허용되는 연산들
- 동일한 구조체 형 변수 간 복사 또는 대입
- 함수 매개변수로 구조체 복사
- 호출된 함수의 반환값을 다른 구조체 형 변수에 대입
- 구조체 형 변수에 동일한 구조체 형 변수 대입
- 구조체 형 변수의 주소 구하기(&)
- 구조체 형 변수의 멤버변수 참조(.)


# Structures and Functions
- 컴퓨터프로그래밍기초
- ‹#›
- Structures and Functions
- 구조체 형 변수는 관계 연산자로 직접 비교할 수 없음
- struct point pt1, pt2;
- pt1 = pt2;
- /* Compile error: expression must have arithmetic or pointer type but has type
-                   "struct point"C/C++(3360)
-   if (pt1 == pt2)
-     printf("pt1 and pt2 are the same\n");
*/
- if (pt1.x == pt2.x && pt1.y == pt2.y)
-   printf("pt1 and pt2 are the same\n");


# Structures and Functions
- 컴퓨터프로그래밍기초
- ‹#›
- Structures and Functions
- 구조체 형 변수를 함수의 매개변수로 전달하는 방법
- makepoint 함수
- 두 개의 정수를 매개변수로 전달하여 구조체 형 반환
- 매개변수의 이름과 구조체의 멤버변수 이름은 같아도 충돌하지 않음(멤버변수 x, y는 point 구조체에 속해있는 변수)
- struct point {
-   int x;
-   int y;
- };
- struct rect {
-   struct point pt1;
-   struct point pt2;
- } screen;
- /* makepoint: make a point from x and y components */
- struct point makepoint(int x, int y)
- {
-   struct point temp;
-   temp.x = x;
-   temp.y = y;
-   return temp;
- }


# Structures and Functions
- 컴퓨터프로그래밍기초
- ‹#›
- Structures and Functions
- 구조체 형 변수를 함수의 매개변수로 전달하는 방법 (Cont’d)
- makepoint 함수는 동적으로 구조체를 초기화할 수 있는 방법 제공
- 함수의 전달인자에 구조체 멤버변수 사용 가능
- 두 좌표 사이의 중간 좌표를 구하는 공식:
- /* makepoint: make a point from x and y components */
- struct point makepoint(int x, int y)
- {
-   struct point temp;
-   temp.x = x;
-   temp.y = y;
-   return temp;
- }
- 
- /* ... SKIPPED ... */
- struct rect screen;
- struct point middle;
- struct point makepoint(int, int);
- 
- screen.pt1 = makepoint(0, 0);
- screen.pt2 = makepoint(XMAX, YMAX);
- middle = makepoint(
-     (screen.pt1.x + screen.pt2.x) / 2,
-     (screen.pt1.y + screen.pt2.y) / 2);


# Structures and Functions
- 컴퓨터프로그래밍기초
- ‹#›
- Structures and Functions
- 구조체 형 변수를 함수의 매개변수로 전달하는 방법 (Cont’d)
- 구조체 형 변수는 직접 연산을 수행할 수 없으며 멤버변수를 직접 조작해야 함
- addpoint 함수
- 구조체 형 변수 자체를 전달(call by value)
- 매개변수로 구조체 형 변수를 받아와 멤버변수 간 덧셈 연산 수행 후 구조체 형 반환
- 구조체 형 변수는 일반 변수처럼 전달 가능
- /* addpoints: add two points */
- struct point addpoint(struct point p1, struct point p2)
- {
-   p1.x += p2.x;
-   p1.y += p2.y;
-   return p1;
- }


# Structures and Functions
- 컴퓨터프로그래밍기초
- ‹#›
- Structures and Functions
- 구조체 형 변수를 함수의 매개변수로 전달하는 방법 (Cont’d)
- ptinrect 함수
- 매개변수로 구조체 형 변수 복사
- 사각형 내부에 점이 위치하는지 확인 후 결과 반환
- /* ptinrect: return 1 if p in r, 0 if not */
- int ptinrect(struct point p, struct rect r)
- {
-   return p.x >= r.pt1.x &&
-       p.x < r.pt2.x &&
-       p.y >= r.pt1.y &&
-       p.y < r.pt2.y;
- }


# Structures and Functions
- 컴퓨터프로그래밍기초
- ‹#›
- Structures and Functions
- 구조체 형 변수를 함수의 매개변수로 전달하는 방법 (Cont’d)
- canonrect 함수
- 두 좌표를 사용하면 하나의 사각형을 표현할 수 있음
- rect 변수의 멤버변수 pt1은 사각형에서의 좌측 하단 좌표를 표현하도록 정규화(canonicalization)
- rect 변수의 멤버변수 pt2는 사각형에서의 우측 상단 좌표를 표현하도록 정규화
- 모든 rect 변수는 정규화된 값을 가지도록 보장하는 함수
- #define min(a, b) ((a) < (b) ? (a) : (b))
- #define max(a, b) ((a) > (b) ? (a) : (b))
- /* canonrect: canonicalize coordinates of rectangle */
- struct rect canonrect(struct rect r)
- {
-   struct rect temp;
-   temp.pt1.x = min(r.pt1.x, r.pt2.x);
-   temp.pt1.y = min(r.pt1.y, r.pt2.y);
-   temp.pt2.x = max(r.pt1.x, r.pt2.x);
-   temp.pt2.y = max(r.pt1.y, r.pt2.y);
-   return temp;
- }


# Structures and Functions
- 컴퓨터프로그래밍기초
- ‹#›
- Structures and Functions
- 구조체 형 변수를 함수의 매개변수로 전달하는 방법 (Cont’d)
- 구조체 형 변수의 주소를 전달(call by address)
- 구조체 형 변수가 많은 메모리를 차지한다면, 구조체 형 변수를 직접 전달하는 것보다 구조체 형 변수의 주소를 전달하는 것이 훨씬 효율적인 방법
- func1 함수는 총 16 bytes 메모리 사용
- func2 함수는 포인터 변수 크기만큼 메모리 사용
- struct point {
-   int x;
-   int y;
- };
- struct rect {
-   struct point pt1;
-   struct point pt2;
- } screen;
- void call_by_value(struct rect r);
- void call_by_address(struct rect *r);


# Structures and Functions
- 컴퓨터프로그래밍기초
- ‹#›
- Structures and Functions
- 구조체 포인터
- 구조체 포인터 선언
- 
- 
- 구조체 포인터의 간접 참조
- 
- 
- 
- 연산자 우선순위는 멤버변수를 참조하는 연산자(.)가 간접 참조 연산자(*)보다 높음
- 괄호를 사용하지 않으면 *pp.x 표현식은 *(pp.x) 형태로 처리
- 포인터 pp는 구조체 형 변수의 주소 값을 저장하고 있으며, 구조체 형 변수가 아닌 객체가 멤버변수에 접근을 시도하면 오류 발생
- /* Structure pointers are just like pointers to ordinary variables. */
- struct point *pp;
- struct point origin, *pp;
- pp = &origin;
- printf("origin is (%d ,%d)\n", (*pp).x, (*pp).y);


# Structures and Functions
- 컴퓨터프로그래밍기초
- ‹#›
- Structures and Functions
- 구조체 포인터는 매우 자주 사용되는 표현
- 구조체 포인터가 가리키는 대상의 멤버변수에 간접 참조하고자 할 경우, 축약된 형태의 연산자(->) 사용 가능
- struct point origin, *pp;
- pp = &origin;
- /*
- printf("origin is (%d ,%d)\n", (*pp).x, (*pp).y);
*/
- printf("origin is (%d ,%d)\n", pp->x, pp->y);


# Structures and Functions
- 컴퓨터프로그래밍기초
- ‹#›
- Structures and Functions
- . 연산자와 -> 연산자는 우선순위가 같으며, 연산자 결합 방향은 왼쪽에서 오른쪽 방향
- (), [], ->, . 연산자는 가장 우선순위가 높은 연산자들
- struct point {
-   int x;
-   int y;
- };
- struct rect {
-   struct point pt1;
-   struct point pt2;
- };
- struct rect r, *rp = &r;
- 
- /* these four expressions are equivalent: */
- r.pt1.x;
- rp->pt1.x;
- (r.pt1).x;
- (rp->pt1).x;


# Structures and Functions
- 컴퓨터프로그래밍기초
- ‹#›
- Structures and Functions
- 연산자 우선순위에 따른 표현식 분석
- struct {
-   int len;
-   char *str;
- } *p;
- /* increments len, not p
-     implied parenthesization is ++(p->len) */
- ++p->len;
- /* increments p before accessing len */
- (++p)->len;
- /* increments p afterward
-     set of parentheses is unnecessary. */
- (p++)->len;
- /* fetches whatever str points to */
*p->str;
- /* increments str after accessing whatever it points to */
*p->str++;
- /* increments whatever str points to */
- (*p->str)++;
- /* increments p after accessing whatever str points to */
*p++->str;
- Brian W. Kernighan and Dennis M. Ritchie. 1988.The C Programming Language (2nd. ed.).Prentice Hall Professional Technical Reference, USA.


# Arrays of Structures
- 컴퓨터프로그래밍기초
- ‹#›
- Arrays of Structures
- C 언어에서 사용하는 예약어(keyword) 빈도를 계산하는 프로그램
- 예약어 이름을 보관할 문자 배열과 해당 예약어의 빈도 수를 기록할 변수가 필요함
- 방법 1: 예약어의 수만큼 문자 배열과 정수형 변수를 선언
- 
- 
- 방법 2: 문자열을 가리키는 포인터와 정수형 변수를 구조체 선언을 통해 쌍 (pair)으로 묶은 뒤, 구조체 형 배열로 선언
- 각 배열의 요소는 구조체 형 변수
- char *keyword[NKEYS];
- int keycount[NKEYS];
- struct key {
-   char *word;
-   int count;
- } keytab[NKEYS];


# Arrays of Structures
- 컴퓨터프로그래밍기초
- ‹#›
- Arrays of Structures
- C 언어에서 사용하는 예약어(keyword) 빈도를 계산하는 프로그램 (Cont’d)
- 구조체 형 배열 초기화 시 중괄호 안에 값들이 멤버변수의 형태와 동일하게 쌍을 이루며 목록을 구성함
- 배열 크기가 생략되어 있다면, 컴파일러가 크기를 자동으로 계산
- 배열 초기화 시 괄호를 사용하면 더욱 명확한 초기화를 수행할 수 있음
- struct key {
-   char *word;
-   int count;
- } keytab[] = {
-   "auto", 0,
-   "break", 0,
-   "case", 0,
-   /* ... */
-   "while", 0
- };
- 
- 
- 
- 
- /*
-   It would be more
-   precise to enclose the initializers for  each "row" or structure in braces, as in
*/
- struct key keytab[] = {
-   { "auto", 0 },
-   { "break", 0 },
-   { "case", 0 },
-   /* ... */
-   { "while", 0 }
- };


# Arrays of Structures
- 컴퓨터프로그래밍기초
- ‹#›
- Arrays of Structures
- C 언어에서 사용하는 예약어(keyword) 빈도를 계산하는 프로그램 (Cont’d)
- 키워드 수를 보관하는 NKEYS
- 사용자가 직접 키워드 수를 계산해  입력하는 것보다 sizeof 연산자를 이용해 계산하는 것이 쉽고 안전함
- sizeof 연산자는 단항 연산자이며, 컴파일 시 연산이 이루어짐(a compile-time unary operator)
- sizeof 연산자는 객체의 크기를 반환
- /* key.h */
- #ifndef ___KEYWORD_KEY_H___
- #define ___KEYWORD_KEY_H___
- struct key {
-   char *word;
-   int count;
- };
- extern const int NKEYS;
- extern struct key keytab[];
- #endif  /* __KEYWORD_KEY_H__ */
- 
- /* key.c */
- #include <stdio.h>
- #include "key.h"
- struct key keytab[] = {
-   { "auto", 0 },
-   { "break", 0 },
-   { "case", 0 },
-   /* ... SKIPPED ... */
-   { "while", 0 }
- };
- const int NKEYS = sizeof keytab / sizeof(struct key);


# Arrays of Structures
- 컴퓨터프로그래밍기초
- ‹#›
- Arrays of Structures
- C 언어에서 사용하는 예약어(keyword) 빈도를 계산하는 프로그램 (Cont’d)
- getword 함수는 사용자 정의 함수이며, 사용자로부터 단어를 입력받음
- 더 이상 입력이 없을 경우 EOF 반환
- /* getword.c */
- #include <stdio.h>
- #include <ctype.h>
- /* getword: get next word or character from input */
- int getword(char *word, int lim)
- {
-   int c, getch(void);
-   void ungetch(int);
-   char *w;
-   w = word;
-   while (isspace(c = getch())) { }
-   if (c != EOF)
-     *w++ = c;
-   if (!isalpha(c)) {
-     *w = '\0';
-     return c;
-   }
-   for (; --lim > 0; w++) {
-     if (!isalnum(*w = getch())) {
-       ungetch(*w);
-       break;
-     }
-   }
-   *w = '\0';
-   return word[0];
- }


# Arrays of Structures
- 컴퓨터프로그래밍기초
- ‹#›
- Arrays of Structures
- C 언어에서 사용하는 예약어(keyword) 빈도를 계산하는 프로그램 (Cont’d)
- getword 함수를 통해 읽어온 단어의 예약어 여부 확인에 3장에서 구현한 binsearch 함수 사용
- 예약어는 반드시 오름차순 형태로 정렬된 상태여야 함
- 입력된 단어가 예약어일 경우 해당 예약어의 빈도수를 1 증가시킴
- /* main.c */
- #include <stdio.h>
- #include <ctype.h>
- #include "key.h"
- #define MAXWORD 100
- struct key *binsearch(char *, struct key [], int);
- int getword(char *, int);
- /* count C keywords; pointer version */
- int main(void)
- {
-   struct key *p;
-   char word[MAXWORD];
-   while (getword(word, MAXWORD) != EOF) {
-     if (isalpha(word[0])) {
-       if ((p = binsearch(word, keytab, NKEYS)) != NULL)
-         p->count++;
-     }
-   }
-   for (p = keytab; p < keytab + NKEYS; p++) {
-     if (p->count > 0)
-       printf("%4d %s\n", p->count, p->word);
-   }
-   return 0;
- }


# Arrays of Structures
- 컴퓨터프로그래밍기초
- ‹#›
- Arrays of Structures
- C 언어에서 사용하는 예약어(keyword) 빈도를 계산하는 프로그램 (Cont’d)
- mid 계산 시 주의할 것
- /* binsearch.c */
- #include <string.h>
- #include "key.h"
- /* binsearch: find word in tab[0]...tab[n-1] */
- struct key *binsearch(char *word, struct key tab[], int n)
- {
-   int cond;
-   struct key *low = &tab[0];
-   struct key *high = &tab[n];
-   struct key *mid;
-   while (low < high) {
-     /* mid = (low + high) / 2, WRONG! */
-     mid = low + (high - low) / 2;  
-     if ((cond = strcmp(word, mid->word)) < 0)
-       high = mid;
-     else if (cond > 0)
-       low = mid + 1;
-     else
-       return mid;
-   }
-   return NULL;
- }


# Pointers to Structures
- 컴퓨터프로그래밍기초
- ‹#›
- Pointers to Structures
- 구조체의 크기는 메모리 정렬 규칙 (memory alignment)에 의해 결정됨
- 구조체는 멤버변수 중 가장 큰 자료형의 크기를 기준으로 메모리 정렬 수행
- 모든 멤버변수의 주소는 자신의 자료형 크기로 나누어질 수 있는 주소를 사용하기 위해 패딩(padding)
- struct {
-   char c1;
-   char c2;
-   char c3;
- } ccc;
- struct {
-   short s;
-   int  i;
-   char c;
- } sic;
- struct {
-   short s;
-   char c;
-   int  i;
- } sci;
- size of ccc is 3
- size of sic is 12
- size of sci is 8


# Pointers to Structures
- 컴퓨터프로그래밍기초
- ‹#›
- Pointers to Structures
- 함수의 반환형이 복잡할 때, 함수 이름을 구분하기가 어려울 수 있음
- e.g. key 구조체 형 변수의 포인터를 반환하는 binsearch 함수
- 
- 복잡한 함수의 반환형과 함수 이름을 구분해 코드를 작성하면 함수 이름 확인이 용이함
- e.g. 함수의 반환형과 함수 이름을 분리한 경우
- 
- 
- This is a matter of personal taste; pick the form you like and hold to it.
- struct key *binsearch(char *word, struct key tab[], int n)⋯
- struct key *
- binsearch(char *word, struct key tab[], int n)⋯


# Self-referential Structures
- 컴퓨터프로그래밍기초
- ‹#›
- Self-referential Structures
- 입력되는 단어의 빈도 수를 계산하는 프로그램
- 대부분의 경우 어떤 단어가 입력될 것인지 알 수 없으며, 입력되는 단어가 사전 순으로 정렬된 상태라는 보장 또한 없음(arbitrary words)
- 새로운 단어가 입력되었을 때, 해당 단어를 찾는 과정이 굉장히 효율적이지 못함
- Its running time is likely to grow quadratically with the number of input words.
- 해결 방안
- 입력된 단어들을 정렬된 상태로 보관하는 것
- 배열을 사용하면 새로 입력된 단어를 순서에 맞게 정렬시키기 위해 기존에 위치한 요소들을 교환해야 하므로 비효율적임
- 자료구조 중 이진 트리(binary tree)를 사용하면 위 문제를 효율적으로 해결할 수 있음


# Self-referential Structures
- 컴퓨터프로그래밍기초
- ‹#›
- Self-referential Structures
- 입력되는 단어의 빈도 수를 계산하는 프로그램 (Cont’d)
- 트리 구조는 노드(node)로 구성됨
- 각 노드는 자식 노드가 없거나 한 개의 자식 노드, 두 개의 자식 노드를 가질 수 있음
- 각 노드는 단어에 대한 정보를 저장
- 해당 단어의 문자열 시작 주소를 가리키는 포인터 (a pointer to the text of the word)
- 해당 단어의 빈도 수  (a count of the number of occurrence)
- 왼쪽 자식 노드에 대한 포인터 (a pointer to the left child node)
- 오른쪽 자식 노드에 대한 포인터 (a pointer to the right child node)


# Self-referential Structures
- 컴퓨터프로그래밍기초
- ‹#›
- Self-referential Structures
- 입력되는 단어의 빈도 수를 계산하는 프로그램 (Cont’d)
- e.g. “now is the time for all good men to come to the aid of their party” 문장을 트리로 표현한 예:


# Self-referential Structures
- 컴퓨터프로그래밍기초
- ‹#›
- Self-referential Structures
- 입력되는 단어의 빈도 수를 계산하는 프로그램 (Cont’d)
- 단어가 입력되면 해당 단어가 이진 트리 구조에 입력된 단어인지 확인
- 입력된 단어가 현재 탐색중인 노드에 기록된 단어보다 사전 순으로 앞에 위치하면, 왼쪽 하위 트리로 이동하여 탐색
- 입력된 단어가 현재 탐색중인 노드에 기록된 단어보다 사전 순으로 뒤에 위치하면, 오른쪽 하위 트리로 이동하여 탐색
- 입력된 단어가 현재 탐색중인 노드에 기록된 단어와 일치한다면, 해당 노드의 빈도수 1 증가
- 입력된 단어가 현재 탐색중인 노드에 기록된 단어와 불일치하여 하위 트리로 이동해야 할 때, 이동해야 할 방향에 노드가 없다면, 해당 위치에 노드 새로 추가
- 단어의 탐색과 출력은 재귀적으로 동작


# Self-referential Structures
- 컴퓨터프로그래밍기초
- ‹#›
- Self-referential Structures
- 입력되는 단어의 빈도 수를 계산하는 프로그램 (Cont’d)
- 노드를 표현하기 위한 구조체
- 
- 
- 
- 
- 자기 자신을 선언하는 형태(recursive declaration)
- 구조체 안에 자기 자신을 직접 선언하는 것은 문법적으로 틀린 표현이므로, 포인터를 이용해 자기 자신을 간접 참조하는 형태로 선언해야 함
- struct tnode {          /* the tree node: */
-   char *word;           /* points to the text */
-   int count;            /* number of occurrences */
-   struct tnode *left;   /* left child */
-   struct tnode *right;  /* right child */
- };


# Self-referentialStructures
- 컴퓨터프로그래밍기초
- ‹#›
- Self-referentialStructures
- 입력되는 단어의 빈도 수를 계산하는 프로그램 (Cont’d)
- /* tree.h */
- #ifndef __WORD_TREE_H__
- #define __WORD_TREE_H__
- struct tnode {          /* the tree node: */
-   char *word;           /* points to the text */
-   int count;            /* number of occurrences */
-   struct tnode *left;   /* left child */
-   struct tnode *right;  /* right child */
- };
- struct tnode *addtree(struct tnode *, char *);
- void treeprint(struct tnode *);
- struct tnode *talloc(void);
- #endif  /* __WORD_TREE_H__ */
- 
- /* tree.c */
- #include <stdio.h>
- #include <stdlib.h>
- #include <string.h>
- #include "tree.h"
- char *strdup(char *);
- /* addtree: add a node with w, at or below p */
- struct tnode *addtree(struct tnode *p, char *w)⋯/* treeprint: in-order print of tree p */
- void treeprint(struct tnode *p)⋯/* talloc: make a tnode */
- struct tnode *talloc(void)⋯


# Self-referentialStructures
- 컴퓨터프로그래밍기초
- ‹#›
- Self-referentialStructures
- 입력되는 단어의 빈도 수를 계산하는 프로그램 (Cont’d)
- 단어가 입력되면 해당 단어가 이진 트리 구조에 입력된 단어인지 확인
- 입력된 단어라면 해당 단어가 기록되어 있는 노드의 빈도수 1 증가
- 입력된 단어가 아니라면 트리 구조에 해당 단어를 표현하는 새로운 노드 등록
- 재귀적으로 동작
- /* addtree: add a node with w, at or below p */
- struct tnode *addtree(struct tnode *p, char *w)
- {
-   int cond;
-   if (!p) {
-     /* p == NULL, a new word has arrived */
-     p = talloc();  /* make a new node */
-     p->word = strdup(w);
-     p->count = 1;
-     p->left = p->right = NULL;
-   } else if ((cond = strcmp(w, p->word)) > 0) {
-     /* greater than into right subtree */
-     p->right = addtree(p->right, w);
-   } else if (cond < 0) {
-     /* less than into left subtree */
-     p->left = addtree(p->left, w);
-   } else {
-     /* repeated word */
-     p->count++;
-   }
-   return p;
- }


# Self-referentialStructures
- 컴퓨터프로그래밍기초
- ‹#›
- Self-referentialStructures
- 입력되는 단어의 빈도 수를 계산하는 프로그램 (Cont’d)
- 트리 구조에 입력되어 있는 단어들을 정렬된 상태로 출력
- 재귀적으로 동작
- /* treeprint: in-order print of tree p */
- void treeprint(struct tnode *p)
- {
-   if (p) {  /* p != NULL */
-     treeprint(p->left);
-     printf("%4d %s\n", p->count, p->word);
-     treeprint(p->right);
-   }
- }


# Self-referentialStructures
- 컴퓨터프로그래밍기초
- ‹#›
- Self-referentialStructures
- 입력되는 단어의 빈도 수를 계산하는 프로그램 (Cont’d)
- malloc 함수를 사용해 동적으로 노드 하나를 기록할 수 있는 메모리를 할당 받음
- malloc 함수를 사용하기 위해서는 <stdlib.h> 헤더 파일 필요
- Heap 영역에 메모리를 할당하며, 할당 성공 시 메모리에 접근 가능한 주소를, 할당 실패 시 NULL 반환
- malloc 함수 사용 시 NULL 주소 반환에 대한 오류 처리 사용 권장
- /* talloc: make a tnode */
- struct tnode *talloc(void)
- {
-   return (struct tnode *) malloc(sizeof(struct tnode));
- }


# Self-referentialStructures
- 컴퓨터프로그래밍기초
- ‹#›
- Self-referentialStructures
- 입력되는 단어의 빈도 수를 계산하는 프로그램 (Cont’d)
- 새로운 노드 등록 시 단어를 기록할 수 있는 공간을 동적으로 할당
- 새로 할당 된 공간에 새로 등록될 단어를 복사
- 메모리 할당 실패 시 단어 복사 과정은 무시됨
- /* strdup.c */
- #include <stdlib.h>
- #include <string.h>
- char *strdup(char *s)
- {
-   char *p;
-   /* make a duplicate of s */
-   p = (char *) malloc(strlen(s) + 1); /* +1 for '\0' */
-   if (p)  /* p != NULL */
-     strcpy(p, s);
-   return p;
- }


# Self-referentialStructures
- 컴퓨터프로그래밍기초
- ‹#›
- Self-referentialStructures
- 입력되는 단어의 빈도 수를 계산하는 프로그램 (Cont’d)
- /* main.c */
- #include <stdio.h>
- #include <ctype.h>
- #include "tree.h"
- #define MAXWORD 100
- int getword(char *, int);
- /* word frequency count */
- int main(void)
- {
-   struct tnode *root;
-   char word[MAXWORD];
-   root = NULL;
-   while (getword(word, MAXWORD) != EOF) {
-     if (isalpha(word[0]))
-       root = addtree(root, word);
-   }
-   treeprint(root);
-   return 0;
- }


# Table Lookup
- 컴퓨터프로그래밍기초
- ‹#›
- Table Lookup
- 테이블 조사(table-lookup) 기능은 여러 분야에서 활용되고 있음
- 매크로 처리기, 컴파일러, 데이터베이스, ...
- e.g. 매크로 처리기에서의 테이블 조사
- 
- 
- 이름 IN을 대체 문자(replacement text) 1로 대치하는 매크로
- 전처리기의 매크로 처리기는 위 정보를 테이블 안에 기록
- 전처리기가 코드를 분석하는 과정 중에 이름이 등장하면 테이블 조사 수행
- 테이블에 해당 이름이 있다면, 해당 이름의 대체 문자로 대치
- #define IN 1
- int state = IN;


# Table Lookup
- 컴퓨터프로그래밍기초
- ‹#›
- Table Lookup
- 테이블 조사 기능의 주요 기능
- install 함수
- 매개변수 s와 t는 문자열
- 이름 s와 대체 문자 t를 테이블에 기록
- lookup 함수
- 매개변수 s가 테이블에 기록되어 있는지 탐색
- 매개변수 s가 테이블에 존재한다면 테이블에서의 s 주소 반환
- 매개변수 s가 테이블에 존재하지 않다면 NULL 반환


# Table Lookup
- 컴퓨터프로그래밍기초
- ‹#›
- Table Lookup
- 해시 탐색(hash search)
- 테이블 조사 기능에 사용되는 알고리즘
- 입력되는 이름을 작은 양의 정수 값(hash)으로 변환
- 해당 정수 값은 포인터 배열에서의 인덱스(index)로 사용
- 포인터 배열의 각 요소는 연결 리스트(linked list)의 시작 주소를 가리킴
- 포인터 배열의 요소에 저장되어 있는 주소가 NULL이 아니라면, 해시의 재료가 된 이름이 기록되어 있는 상태
- 포인터 배열의 요소에 저장되어 있는 주소가 NULL이라면, 해당 해시의 재료가 된 이름이 아직 기록되지 않은 상태
- 테이블 조사에서 사용하는 해시 크기는 101이며, 이름을 재료로 했을 때 0부터 100 사이의 정수로 변환됨


# Table Lookup
- 컴퓨터프로그래밍기초
- ‹#›
- Table Lookup
- 연결 리스트의 블록 구조
- 테이블 조사 기능에 사용되는 자료구조
- 세 가지 정보를 갖는 노드들을 포인터를 이용해 연결하게 됨:
- 다음 노드를 가리키는 포인터
- 해당 노드에 기록되어 있는 이름 문자열의 시작 주소를 가리키는 포인터
- 해당 노드에 기록되어 있는 이름의 대체 문자열 시작 주소를 가리키는 포인터
- struct nlist {         /* table entry: */
-   struct nlist *next;  /* next entry in chain */
-   char *name;          /* defined name */
-   char *defn;          /* replacement text */
- };


# Table Lookup
- 컴퓨터프로그래밍기초
- ‹#›
- Table Lookup
- 테이블 조사 프로그램
- /* table.h */
- #ifndef __TABLE_TABLE_H__
- #define __TABLE_TABLE_H__
- struct nlist {         /* table entry: */
-   struct nlist *next;  /* next entry in chain */
-   char *name;          /* defined name */
-   char *defn;          /* replacement text */
- };
- #define HASHSIZE 101
- unsigned hash(char *s);
- struct nlist *lookup(char *s);
- struct nlist *install(char *name, char *defn);
- #endif /* __TABLE_TABLE_H__ */


# Table Lookup
- 컴퓨터프로그래밍기초
- ‹#›
- Table Lookup
- 테이블 조사 프로그램 (Cont’d)
- /* table.c */
- #include <stdio.h>
- #include <stdlib.h>
- #include <string.h>
- #include "table.h"
- char *strdup(char *s);
- struct nlist *hashtab[HASHSIZE];  /* pointer table */
- /* hash: form hash value for string s */
- unsigned hash(char *s)⋯/* lookup: look for s in hashtab */
- struct nlist *lookup(char *s)⋯/* install: put (name, defn) in hashtab */
- struct nlist *install(char *name, char *defn)⋯


# Table Lookup
- 컴퓨터프로그래밍기초
- ‹#›
- Table Lookup
- 테이블 조사 프로그램 (Cont’d)
- lookup 함수와 install 함수에서 사용
- 무작위로 수를 조합한 뒤에 해시 크기로 나머지 연산
- 결과는 0부터 해시 크기보다 1 작은 수로 제한됨
- unsigned 반환형
- 해시 값이 음수가 아님을 보장
- /* hash: form hash value for string s */
- unsigned hash(char *s)
- {
-   unsigned hashval;
-   for (hashval = 0; *s != '\0'; s++)
-     hashval = *s + 31 * hashval;
-   return hashval % HASHSIZE;
- }


# Table Lookup
- 컴퓨터프로그래밍기초
- ‹#›
- Table Lookup
- 테이블 조사 프로그램 (Cont’d)
- 찾고자 하는 이름으로부터 해시 계산
- 계산한 해시를 인덱스로 사용
- 다음 과정을 반복:
- 테이블에 이름이 존재한다면 해당 위치 주소를 반환
- 테이블에 이름이 존재하지 않는다면, 다음 노드 탐색
- 테이블에 이름이 존재하지 않는다면 NULL 반환
- /* lookup: look for s in hashtab */
- struct nlist *lookup(char *s)
- {
-   struct nlist *np;
-   for (np = hashtab[hash(s)]; np != NULL; np = np->next) {
-     if (!strcmp(s, np->name))
-       return np; /* found */
-   }
-   return NULL;  /* not found */
- }


# Table Lookup
- 컴퓨터프로그래밍기초
- ‹#›
- Table Lookup
- 테이블 조사 프로그램 (Cont’d)
- lookup 함수 호출 결과가 NULL이 아니면, 새로운 정의로 대치 (supersede)
- 이미 존재하는 대체 문자열은 free 함수를 호출해 할당 해제
- strdup 함수 사용해 새로운 대체 문자열 등록
- lookup 함수 호출 결과가 NULL이면, 새로운 블록 생성 후 테이블에 등록
- 새로운 블록의 저장 공간이 부족하다면 install 함수는 NULL 반환
- /* install: put (name, defn) in hashtab */
- struct nlist *install(char *name, char *defn)
- {
-   struct nlist *np;
-   unsigned hashval;
-   if (!(np = lookup(name))) {
-     /* not found */
-     np = (struct nlist *) malloc(sizeof(*np));
-     if (!np || !(np->name = strdup(name)))
-       return NULL;
-     hashval = hash(name);
-     np->next = hashtab[hashval];
-     hashtab[hashval] = np;
-   } else {
-     /* already there */
-     free((void *) np->defn);  /* free previous defn */
-   }
-   if (!(np->defn = strdup(defn)))
-     return NULL;
-   return np;
- }


# Table Lookup
- 컴퓨터프로그래밍기초
- ‹#›
- Table Lookup
- 테이블 조사 프로그램 (Cont’d)
- /* main.c */
- #include <stdio.h>
- #include "table.h"
- void itoa(int n, char s[]);
- extern struct nlist *hashtab[HASHSIZE]; /* pointer table */
- int main(int argc, char *argv[])
- {
-   char *str[] = { "OFF", "ON", "ERROR" };
-   char buf[10];
-   struct nlist *temp;
-   int i, size;
-   size = sizeof str / sizeof(char *);
-   for (i = 0; i < size; ++i) {
-     itoa(i, buf);
-     /* return NULL if for any reason there is no room for a new        entry */
-     if (!install(str[i], buf))
-       return -1;
-   }
-   for (i = 0; i < size; ++i) {
-     /* if the string is to be found anywhere */
-     if ((temp = lookup(str[i])))
-       printf("%6s: %2s\n", temp->name, temp->defn);
-   }
-   return 0;
- }


# Typedef
- 컴퓨터프로그래밍기초
- ‹#›
- Typedef
- 일반 형에 새로운 이름(별명)을 붙임
- e.g. int 형에 새로운 이름 Length 사용
- 
- typedef 선언은 이름 Length를 int 형으로 사용하겠다는 의미
- 이름 Length는 변수 선언, 형 변환 등 형이 위치할 수 있는 자리에 사용 가능
- e.g. Length 형을 사용한 변수 선언
- 
- 
- e.g. char 변수를 가리키는 포인터 형에 새로운 이름 String 사용
- typedef int Length;
- Length len, maxlen;
- Length *lengths[];
- typedef char *String;
- String p, lineptr[MAXLINES], alloc(int);
- int strcmp(String, String);
- p = (String) malloc(100);


# Typedef
- 컴퓨터프로그래밍기초
- ‹#›
- Typedef
- typedef 선언을 통해 새로운 형 이름을 만들 때, 일반 형들과 구분하기 위해 이름 맨 앞 글자를 대문자로 표시
- e.g. struct tnode 형에 typedef를 사용한 예
- typedef struct tnode *Treeptr;
- typedef struct tnode {  /* the tree node: */
-   char  *word;          /* points to the text */
-   int   count;          /* number of occurrences */
-   Treeptr left;         /* left child */
-   Treeptr right;        /* right child */
- } Treenode;
- Treeptr talloc(void)
- {
-   return (Treeptr) malloc(sizeof(Treenode));
- }


# Typedef
- 컴퓨터프로그래밍기초
- ‹#›
- Typedef
- typedef 선언은 새로운 형을 만드는 것이 아닌, 기존 형에 새로운 이름을 붙여 사용하는 것
- typedef 선언은 #define 선언처럼 사용할 수 있음
- #define 선언에서 처리하지 못하는 문자열 대치(textual substitutions)를 typedef 선언을 통해 처리할 수 있음
- e.g. 두 개의 char 형을 가리키는 포인터 매개변수를 사용하는 int 형을 반환하는 함수의 포인터를 typedef 선언을 사용한 예
- 
- 
- #define은 전처리기에 의해 처리되지만, typedef 선언은 컴파일러에 의해 처리된다는 차이가 있음
- typedef int (*PFI)(char *, char *);
- PFI strcmp, numcmp;


# Typedef
- 컴퓨터프로그래밍기초
- ‹#›
- Typedef
- typedef 선언 사용 시 장점
- 이식성 문제 해결(to parameterize a program against portability problems)
- 프로그램이 동작하는 사용 환경에 따라 특정 형의 크기가 다를 수 있음
- 사용 환경이 바뀔 때마다 프로그램 코드를 매번 수정해야 함
- typedef 선언을 통해 사용 환경에 따라 변하는 특정 형에 새로운 이름을 붙여 사용하면, typedef 선언 부분만 수정해주면 됨
- e.g. 환경에 따른 64-bit 정수형 처리
- #ifdef _MSC_VER
- typedef unsigned __int64 ImU64;  /* 64-bit unsigned integer */
- #else
- typedef unsigned long long ImU64;  /* 64-bit unsigned integer */
- #endif


# Typedef
- 컴퓨터프로그래밍기초
- ‹#›
- Typedef
- typedef 선언 사용 시 장점 (Cont’d)
- 이식성 향상을 위해 사용되는 자료형
- size_t is an unsigned integer type used to represent the size of any object (including arrays) in the particular implementation.
- ptrdiff_t is a signed integer type used to represent the difference between pointers.
- e.g. size_t 사용 예:
- Twice the bits, twice the trouble: vulnerabilities induced by migrating to 64-bit platforms[Website]. (2022, May 15). Retrieved from https://blog.acolyer.org/2016/11/17/twice-the-bits-twice-the-trouble-vulnerabilities-induced-by-migrating-to-64-bit-platforms/


# Typedef
- 컴퓨터프로그래밍기초
- ‹#›
- Typedef
- typedef 선언 사용 시 장점 (Cont’d)
- 소스코드 가독성 향상(to provide better documentation for a program)
- 복잡한 자료형을 축약하거나 명확하게 표현할 수 있음
- e.g. struct tnode 형을 가리키는 포인터에 Treeptr 이름을 붙인 예:
- struct tnode {          /* the tree node: */
-   char *word;           /* points to the text */
-   int count;            /* number of occurrences */
-   struct tnode *left;   /* left child */
-   struct tnode *right;  /* right child */
- };
- struct tnode *talloc(void)
- {
-   return (struct tnode *) malloc(sizeof(struct tnode));
- }
- typedef struct tnode *Treeptr;
- typedef struct tnode {  /* the tree node: */
-   char *word;           /* points to the text */
-   int count;            /* number of occurrences */
-   Treeptr left;         /* left child */
-   Treeptr right;        /* right child */
- } Treenode;
- Treeptr talloc(void)
- {
-   return (Treeptr) malloc(sizeof(Treenode));
- }


# Unions
- 컴퓨터프로그래밍기초
- ‹#›
- Unions
- 다른 형과 크기를 가지는 객체를 같은 저장 공간에서 처리
- 공용체는 구조체와 비슷한 성격을 갖고 있음
- 변수 간 복사(=), 변수의 주소 반환(&), 변수의 멤버변수 참조(. or ->) 등 구조체 형 변수에서 사용 가능한 연산자를 공용체 형 변수에서도 동일하게 사용 가능


# Unions
- 컴퓨터프로그래밍기초
- ‹#›
- Unions
- 공용체는 구조체처럼 멤버변수를 가짐
- 공용체 형 변수의 멤버변수들은 하나의 저장공간을 공유
- 저장공간은 멤버변수 중에서 가장 큰 자료형으로 할당
- e.g. 저장공간 사용 예:
- union {
-   int i;    /* 4 bytes */
-   short s;  /* 2 bytes */
-   char c;   /* 1 byte */
- } u = 0x12345678;
- &u;    /* 0x08AF53DC */
- &u.i;  /* 0x08AF53DC */
- &u.s;  /* 0x08AF53DC */
- &u.c;  /* 0x08AF53DC */
- 
- u.i;  /* 0x12345678 */
- u.s;  /* 0x5678 */
- u.c;  /* 0x78 */
- 0x08AF53DC
- 0x08AF53DD
- 0x08AF53DE
- 0x08AF53DF


# Unions
- 컴퓨터프로그래밍기초
- ‹#›
- Unions
- 공용체 초기화
- 공용체 형 변수는 첫 번째 멤버변수의 형으로 초기화할 수 있음
- e.g. 세 개의 멤버변수를 갖는 공용체 형 변수 u
- 
- 
- 
- 공용체 형 변수 u는 int 형 값으로 초기화 가능
- union u_tag {
-   int ival;
-   float fval;
-   char *sval;
- } u;


# Unions
- 컴퓨터프로그래밍기초
- ‹#›
- Unions
- 컴파일러 이름(symbol) 정보를 저장하는 테이블 관리 프로그램
- 각 이름은 상수 값을 가지며, 상수는 정수형, 실수형, 또는 문자열 시작 주소를 가리키는 포인터 중 하나가 될 수 있음
- 상수 값을 변수에 저장하고자 할 때, 해당 변수는 상수 값을 담을 수 있는 적절한 형으로 선언되어야 함
- 일반적인 방법으로는 형에 따른 값을 적절히 보관하기 위해 세 종류의 변수 필요
- 공용체 형 변수를 사용하면 위 문제를 편리하게 해결할 수 있음
- 공용체 형 변수는 멤버변수 간에 저장공간을 공유한다는 특징이 있음
- 이 특징을 활용해 하나의 공용체 형 변수를 사용해 여러 형의 값을 보관할 수 있음
- union u_tag {
-   int ival;
-   float fval;
-   char *sval;
- } u;


# Unions
- 컴퓨터프로그래밍기초
- ‹#›
- Unions
- 컴파일러 이름(symbol) 정보를 저장하는 테이블 관리 프로그램 (Cont’d)
- 공용체 형 변수에 기록된 값은 기록할 때의 형 형태로 참조해야 함
- 만약 값이 int 형이라면 참조 시 int 형 형태로 참조해야 함
- 다른 형으로 참조 시 결과는 알 수 없음 (implementation-dependent)
- 이름 등록 시 값과 해당 값의 형을 같이 등록해야 함
- #define NSYM 100
- struct {
-   char *name;
-   int flags;
-   int utype;
-   union {
-     int  ival;
-     float fval;
-     char *sval;
-   } u;
- } symtab[NSYM];
- enum {
-   INT,
-   FLOAT,
-   STRING
- };
- 
- /* ... SKIPPED ... */
- 
- if (symtab[i].utype == INT)
-   printf("%d\n", symtab[i].u.ival);
- else if (symtab[i].utype == FLOAT)
-   printf("%f\n", symtab[i].u.fval);
- else if (symtab[i].utype == STRING)
-   printf("%s\n", symtab[i].u.sval);
- else
-   printf("bad type %d in utype\n", symtab[i].utype);


# Bit-fields
- 컴퓨터프로그래밍기초
- ‹#›
- Bit-fields
- 특정 환경에서는 메모리 공간의 제약이 따를 수 있음
- 하나의 객체를 비트 단위로 나누어 값을 저장해야 함
- e.g. 일반적인 방법으로 비트 단위 값을 저장하는 예:
- 
- 
- 
- 
- 
- 각 비트 별로 의미를 부여해야 하기 때문에, 2의 제곱 형태로 상수를 정의해야 함
- #define KEYWORD 01
- #define EXTERNAL 02
- #define STATIC  04
- 
- /* ... SKIPPED ... */
- unsigned int flags;
- flags |= EXTERNAL | STATIC;
- flags &= ~(EXTERNAL | STATIC);
- if ((flags & (EXTERNAL | STATIC)) == 0)⋯


# Bit-fields
- 컴퓨터프로그래밍기초
- ‹#›
- Bit-fields
- 비트 필드는 객체를 비트 단위로 나누어 값을 저장할 수 있는 방법을 제공
- e.g. 비트 필드를 이용한 비트 단위로 값을 저장하는 예:
- 비트 필드의 콜론 옆 숫자는 사용할 비트 수를 나타냄
- 변수 flags는 세 개의 비트 필드를 사용하며, 각 비트 필드는 1 비트 사용
- 비트 필드 사용 방법은 구조체 멤버변수 접근 방법과 동일
- struct {
-   char *name;
-   struct {
-     unsigned int is_keyword : 1;
-     unsigned int is_extern : 1;
-     unsigned int is_static : 1;
-   } flags;
-   int utype;
-   union {
-     int  ival;
-     float fval;
-     char *sval;
-   } u;
- } symtab[NSYM];
- 
- /* ... SKIPPED ... */
- 
- symtab[i].flags.is_extern = 1;
- symtab[i].flags.is_keyword = symtab[i].flags.is_static = 0;
- if (!(symtab[i].flags.is_extern || symtab[i].flags.is_static))⋯


# Bit-fields
- 컴퓨터프로그래밍기초
- ‹#›
- Bit-fields
- 주의사항
- 비트 필드는 int 형으로 정의하는 것이 표준이며, 비트 필드 사용 시 unsigned int형을 주로 사용
- unsigned 형과 signed 형은 서로 값을 다르게 처리함
- #include <stdio.h>
- struct{
-   int a : 4;
-   unsigned b : 4;
- } bits;
- int main(void)
- {
-   bits.a = bits.b = 0x0F;  /* 1111 */
-   printf("%d %u\n", bits.a, bits.b);  /* -1 15 */
-   return 0;
- }


# Bit-fields
- 컴퓨터프로그래밍기초
- ‹#›
- Bit-fields
- 주의사항 (Cont’d)
- 이름이 없는 비트 필드는 메모리 정렬을 위해 사용(padding)
- struct {
-   unsigned int a : 1;
-   unsigned int b : 2;
-   unsigned int c : 4;
-   unsigned int : 1;
-   unsigned int d : 8;
- } bits;
- int main(void)
- {
-   bits.a = 1;    /*         1 */
-   bits.b = 2;    /*        10 */
-   bits.c = 15;   /*      1111 */
-   bits.d = 128;  /* 1000 0000 */
-   return 0;
- }
- 0x08AF53A0
- 0x08AF53A1
- 0x08AF53A2
- 0x08AF53A3


# Bit-fields
- 컴퓨터프로그래밍기초
- ‹#›
- Bit-fields
- 주의사항 (Cont’d)
- 비트 수가 0으로 설정된 비트 필드는 강제로 메모리 정렬 수행(다음 경계로 이동)
- struct {
-   unsigned int a : 1;
-   unsigned int b : 2;
-   unsigned int : 0;
-   unsigned int c : 1;
-   unsigned int d : 8;
- } bits;
- int main(void)
- {
-   bits.a = 1;    /*         1 */
-   bits.b = 2;    /*        10 */
-   bits.c = 1;    /*         1 */
-   bits.d = 128;  /* 1000 0000 */
-   return 0;
- }
- 0x08AF53A0
- 0x08AF53A1
- 0x08AF53A2
- 0x08AF53A3
- 0x08AF53A4
- 0x08AF53A5
- 0x08AF53A6
- 0x08AF53A7


# Bit-fields
- 컴퓨터프로그래밍기초
- ‹#›
- Bit-fields
- 주의사항 (Cont’d)
- 비트 필드의 비트 수를 초과하는 값을 저장하면, 결과는 알 수 없음(implementation-defined)
- 비트 필드는 컴퓨터의 메모리 표현 방법에 따라 비트 필드의 값 저장 시작 부분이 다름
- Little Endian? Big Endian?
- 비트 필드를 사용한 프로그램을 다른 환경에서 사용하고자 할 때, 해당 환경에서의 메모리 표현 방법이 무엇인지 확인 후 사용해야 함
- 비트 필드는 배열로 선언할 수 없음
- 비트 필드는 주소가 없음
- & 연산자를 적용할 수 없음

