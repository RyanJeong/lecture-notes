# 컴퓨터프로그래밍기초
- 컴퓨터프로그래밍기초
- Input and Output


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
- 입출력 재정의 및 파이프 동작
- 가변 인자 함수
- 입출력 함수
- 파일 입출력 함수
- 기타 함수들


# Standard Input and Output
- 컴퓨터프로그래밍기초
- ‹#›
- Standard Input and Output
- C 언어는 입력과 출력을 간단히 처리할 수 있는 모델을 라이브러리 형태로 제공
- 스트림(stream)
- 
- 
- 
- 
- 
- 텍스트 스트림은 연속된 문장들로 구성되어 있으며, 각 문장 끝에는 개행문자 ('\n')가 포함되어 있음
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


# Standard Input and Output
- 컴퓨터프로그래밍기초
- ‹#›
- Standard Input and Output
- 가장 간단한 형태의 입력 동작
- getchar 함수
- 표준 입력(standard input, normally the keyboard)을 통해 데이터가 입력됨
- getchar 함수 호출 시 입력된 데이터 중에서 한 문자를 가져옴
- 더 이상 가져올 데이터가 없을 경우 EOF 반환
- 기호 상수 EOF는 <stdio.h> 안에 보통 -1로 정의되어 있음
- 환경마다 EOF 값이 다를 수 있으므로, -1을 사용하는 것보다 EOF를 사용하는 것을 권장


# Standard Input and Output
- 컴퓨터프로그래밍기초
- ‹#›
- Standard Input and Output
- 가장 간단한 형태의 입력 동작 (Cont’d)
- 표준 입력은 < 로 대치할 수 있음(input redirection)
- 
- 
- 
- 
- 
- 
- 
- < (input redirection), > (output redirection), | (pipe) 
- < infile.txt는 infile.txt 안에 기록된 내용들을 표준 입력으로 전달하며, 커맨드라인 전달인자로 간주하지 않음
- #include <stdio.h>
- /* copy input to output; 2nd version */
- int main(void)
- {
-   int c;  /* instead of char type */
-   while ((c = getchar()) != EOF)
-     putchar(c);
-   return 0;
- }
- $ gcc prog.c –o prog -ansi -Wall
- 
- $ cat infile.txt
- Input redirection
- The '<' symbol is used for input(STDIN) redirection
- 
- $ ./prog <infile.txt
- Input redirection
- The '<' symbol is used for input(STDIN) redirection


# Standard Input and Output
- 컴퓨터프로그래밍기초
- ‹#›
- Standard Input and Output
- 가장 간단한 형태의 입력 동작 (Cont’d)
- | (pipe)는 한 프로그램의 표준 출력을 다른 프로그램의 표준 입력으로 전달할 수 있음
- 
- 
- 
- 
- 
- 두 프로그램을 동시에 실행
- otherprog의 표준 출력을 prog의 표준 입력으로 전달
- #include <stdio.h>
- int main(void)
- {
-   printf("Hello, World\n");
-   return 0;
- }
- $ gcc otherprog.c -o otherprog -ansi -Wall
- 
- $ ./otherprog | prog
- Hello, World
- otherprog.exe:
- writing data to the pipe
- prog.exe:
- reading data from the pipe
- pipe:
- data maintained in the pipe


# Standard Input and Output
- 컴퓨터프로그래밍기초
- ‹#›
- Standard Input and Output
- 가장 간단한 형태의 입력 동작 (Cont’d)
- putchar 함수
- 표준 출력(standard output, which is by default the screen)으로 데이터를 내보냄
- putchar 함수 호출 시 매개변수로 전달된 문자 하나를 출력
- 오류 발생 시 EOF 반환
- 표준 출력은 > 로 대치할 수 있으며, |를 사용해 표준 출력 결과를 다른 프로그램의 표준 입력으로 전달할 수도 있음
- #include <stdio.h>
- int main(void)
- {
-   putchar('A');
-   return 0;
- }
- $ gcc prog.c -o prog -ansi -Wall
- $ ./prog >outfile
- $ cat outfile
- A


# Formatted Output - Printf
- 컴퓨터프로그래밍기초
- ‹#›
- Formatted Output - Printf
- printf 함수
- 입력받은 값들을 문자 형태로 바꾸어 출력하는 함수
- 
- format을 기반으로 전달인자들을 변환하고 형식에 맞게 출력
- 반환값은 출력되는 문자들의 수
- int printf(char *format, arg1, arg2, ⋯)  /* defined in header <stdio.h> */
- #include <stdio.h>
- int main(void)
- {
-   /* Hello world!
-      13 */
-   printf("%d\n", printf("Hello world!\n")); /* 'H' 'e' 'l' 'l' 'o' ' ' 'w' 'o' 'r' 'l' 'd' '!' '\n' */
- 
-   return 0;
- }


# Formatted Output - Printf
- 컴퓨터프로그래밍기초
- ‹#›
- Formatted Output - Printf
- printf 함수 (Cont’d)
- 형식 문자열(format string)
- 일반 문자(ordinary characters)는 그대로 출력되며, 형식 지정자(format specifier, %[flags][width][.precision][length]specifier)는 구성된 형태에 따라 변환된 후 출력
- 지정 문자(specifier)는 d(정수 출력), f(실수 출력), c(문자 출력), s(문자열 출력) 등이 있음
- [flags] 위치에 –(a minus sign) 입력 시 왼쪽 정렬
- printf 함수의 기본 정렬은 오른쪽 정렬
- [width] 값은 해당 형식 지정자 위치에 출력될 최소 문자 수 지정
- 숫자를 사용하거나, * 문자를 사용해 전달인자로부터 값을 대응할 수도 있음
- printf("%6d\n", 100);
-     printf("%-6d\n", 100);
-     printf("%6d\n", 1000000);
-     printf("%*d\n", 10, 1000000);
- ···100
- 100···
- 1000000
- ···1000000


# Formatted Output - Printf
- 컴퓨터프로그래밍기초
- ‹#›
- Formatted Output - Printf
- printf 함수 (Cont’d)
- 문자열(s) 지정자에서의 정밀도([.precision])
- 해당 형식 지정자 위치에 출력될 문자열의 최대 문자 수 지정
- 정밀도가 설정되어 있지 않다면 '\0' 문자를 만날 때까지 출력
- char *s = "Hello, world";  /* 12 */
-     /* string with precision */
- printf(":%s:\n", s);
- printf(":%10s:\n", s);
- printf(":%.10s:\n", s);
- printf(":%-10s:\n", s);
- printf(":%15s:\n", s);
- printf(":%.15s:\n", s);
- printf(":%-15s:\n", s);
- printf(":%15.10s:\n", s);
- printf(":%-15.10s:\n", s);
- :Hello, world:
- :Hello, world:
- :Hello, wor:
- :Hello, world:
- :···Hello, world:
- :Hello, world:
- :Hello, world···:
- :·····Hello, wor:
- :Hello, wor·····:


# Formatted Output - Printf
- 컴퓨터프로그래밍기초
- ‹#›
- Formatted Output - Printf
- printf 함수 (Cont’d)
- 실수(f, e, E) 지정자에서의 정밀도([.precision])
- f는 실수 값을 고정 소수점 형태로, e(or E)는 실수 값을 과학적 표기 형태로 출력
- 해당 형식 지정자 위치에 출력될 소수부의 최대 문자 수를 지정하며, 지정되어 있지 않다면 기본값인 6 사용
- printf("%8.5f\n", 1.25);
- printf("%-8.5f\n", 1.25);
- printf("%9.3f\n", 3.141592);
- printf("%-9.3f\n", 3.141592);
- printf("%9f\n", 3.141592);
- printf("%-9f\n", 3.141592);
- printf("%10.3e\n", 3.141592);
- printf("%-10.3E\n", 3.141592);
- ·1.25000
- 1.25000·
- ····3.142
- 3.142····
- ·3.141592
- 3.141592·
- ·3.142e+00
- 3.142E+00·


# Formatted Output - Printf
- 컴퓨터프로그래밍기초
- ‹#›
- Formatted Output - Printf
- printf 함수 (Cont’d)
- 실수(g, G) 지정자에서의 정밀도([.precision])
- 출력할 실수값을 과학적 표기 형태로 표현했을 때, 지수 값이 -4보다 작거나 소수부의 정밀도가 precision의 값보다 크거나 같다면 지정자 e, E 사용
- 그 외의 경우에는 지정자 f 사용 
- 해당 형식 지정자 위치에 출력될 실수값의 최대 문자 수를 지정하며, 지정되어 있지 않다면 기본값인 6 사용
- 출력될 실수값의 소수부 정밀도 값이 사용자가 지정한 정밀도 값보다 낮다면, 뒤따르는 소수부의 0은 제거됨
- double d1 = 0.125;               /* 1 ÷ 8 */
- double d2 = 0.0000152587890625;  /* 1 ÷ 65,536 */
- double d3 = 1234.56;
- printf("%f\n", d1);
- printf("%e\n", d1);
- printf("%g\n", d1);
- printf("%f\n", d2);
- printf("%E\n", d2);
- printf("%G\n", d2);
- printf("%e\n", d3);
- printf("%.3g\n", d3);
- printf("%.4g\n", d3);
- 0.125000
- 1.250000e-01
- 0.125
- 
- 0.000015
- 1.525879E-05
- 1.52588E-05
- 
- 1.234560e+03 1.23e+03
- 1235


# Formatted Output - Printf
- 컴퓨터프로그래밍기초
- ‹#›
- Formatted Output - Printf
- printf 함수 (Cont’d)
- 정수(d, i, o, x, X) 지정자에서의 정밀도([.precision])
- 해당 형식 지정자 위치에 출력될 정수의 최소 문자 수 지정
- 출력될 정수의 정밀도 값이 사용자가 지정한 정밀도 값보다 작다면 빈 공간을 0으로 채워 출력
- printf("%.5d\n",  12);
- printf("%5.5d\n", 1234);
- printf("%8.5d\n", 1234);
- printf("%-8.5d\n", 1234);
- printf("%8.5d\n", 123456);
- printf("%-8.5d\n", 123456);
- 00012
- 01234
- ···01234
- 01234···   
- ··123456
- 123456··


# Formatted Output - Printf
- 컴퓨터프로그래밍기초
- ‹#›
- Formatted Output - Printf
- printf 함수 (Cont’d)
- 정수(d, i) 지정자에서의 길이([length])
- 길이가 생략되었다면 형식 지정자의 출력 결과는 int 형
- 길이가 h일 경우 형식 지정자의 출력 결과는 short 형
- 길이가 l일 경우 형식 지정자의 출력 결과는 long 형
- printf("%d\n", 1 << 16);
- printf("%hd\n", 1 << 16);
- printf("%6hd\n", 1 << 16);
- printf("%d\n", (long) 1 << 32);
- printf("%ld\n", (long) 1 << 32);
- printf("%-12ld\n", (long) 1 << 32);
- 65536
- 0
- ·····0
- 
- 0
- 4294967296
- 4294967296··


# Formatted Output - Printf
- 컴퓨터프로그래밍기초
- ‹#›
- Formatted Output - Printf
- printf 함수 (Cont’d)
- 지정자(specifier)
- Brian W. Kernighan and Dennis M. Ritchie. 1988. The C Programming Language (2nd. ed.). Prentice Hall Professional Technical Reference, USA.


# Formatted Output - Printf
- 컴퓨터프로그래밍기초
- ‹#›
- Formatted Output - Printf
- printf 함수 (Cont’d)
- 지정자(specifier)
- o는 정수를 8진수로 출력
- h는 정수를 16진수로 출력
- u는 정수를 무부호형으로 출력
- p는 전달인자의 객체 주소 출력
- %는 % 문자 출력
- printf("%3d %3o %3x %3X\n",
-     i, i, i, i);
- printf("%3d %3o %3x %3X\n",
-     o, o, o, o);
- printf("%3d %3o %3x %3X\n",
-     h, h, h, h);
- printf("%u\n", u);
- printf("%3c %3d %3x %3X\n",
-     c, c, c, c);
- printf("%p\n", &d3);
- printf("%%\n");
- ·15 ·17 ··f ··F
- 
- ·63 ·77 ·3f ·3F
- 
- 255 377 ·ff ·FF
- 
- 2147483648
- ··Z ·90 ·5a ·5A
- 
- 0x7ffff59b4910
- %


# Formatted Output - Printf
- 컴퓨터프로그래밍기초
- ‹#›
- Formatted Output - Printf
- printf 함수 (Cont’d)
- printf 함수의 첫 번째 전달인자는 형식 문자열이 위치하며, 해당 형식 문자열 내에 형식 지정자가 n개 구성된다면, printf 함수의 전달인자의 개수는 n + 1
- n: 형식 지정자와 대응되어야 할 전달인자의 개수
- 1: 형식 문자열
- 
- 다음 경우에서는 잘못된 결과를 출력:
- 형식 문자열 내 형식 지정자의 수가 n개일 때, printf 함수의 전달인자의 개수가 n + 1이 아닐 경우
- 형식 지정자에서의 지정자 형과 해당 형식 지정자와 대응되는 전달인자의 형이 서로 일치하지 않는 경우
- printf(s);          /* Fail if s contains '%' */
- printf("%s\n", s);  /* Safe */


# Formatted Output - Printf
- 컴퓨터프로그래밍기초
- ‹#›
- Formatted Output - Printf
- sprintf 함수
- 동작은 printf 함수와 동일하나, 매개변수들을 형식에 맞게 변환한 결과 문자열을 표준 출력이 아닌 문자 배열에 기록
- 
- 
- 포인터 s는 문자 배열의 시작 주소이며, 문자 배열은 결과를 저장할 수 있도록 저장공간이 충분해야 함
- /* defined in header <stdio.h> */ 
- int sprintf(char *s, char *format, arg1, arg2, ⋯)
- #include <stdio.h>
- int main(void)
- {
-   char s[100];
-   int len, a, b;
-   a = 3, b = 5;
-   len = sprintf(s, "%d + %d = %d", a, b, a + b);
-   /* 3 + 5 = 8, return value of sprintf() : 9 */
-   printf("%s, return value of sprintf(): %d\n", s, len);
-   return 0;
- }


# Variable-length Argument Lists
- 컴퓨터프로그래밍기초
- ‹#›
- Variable-length Argument Lists
- 가변 인자 매개변수 목록과 가변 인자 함수
- printf 함수는 가변 인자 함수
- 
- ...(가변 인자 매개변수 목록, variable-length argument lists)은 해당 함수의 매개변수가 결정되지 않은 상태임을 의미
- 함수의 매개변수 목록 중 마지막 위치에만 사용 가능
- <stdarg.h> 헤더 파일에 정의되어 있는 인터페이스를 사용하면 가변 인자 매개변수 목록을 활용한 가변 인자 함수를 사용할 수 있음
- int printf(char *format, ...)


# Variable-length Argument Lists
- 컴퓨터프로그래밍기초
- ‹#›
- Variable-length Argument Lists
- va_list 형
- 가변 인자를 한 번에 하나씩 참조할 수 있는 포인터
- va_start 매크로
- va_list 형 변수가 첫 번째 가변 인자를 가리키며, va_list 형 변수 사용 전 반드시 호출되어야 함
- 가변 인자 함수는 적어도 한 개 이상의 이름이 사용된 매개변수가 있어야 하며, 이름이 있는 마지막 매개변수를 사용해야 함
- #include <stdio.h>   /* printf */
- #include <stdarg.h>  /* va_list, va_start, va_arg, va_end */
- int findmax(int, ...);
- int main(void)
- {
-   int max;
-   max = findmax(5, 23, 1, 52, -3, 7);
-   printf("The largest value is %d.\n", max);
-   return 0;
- }
- int findmax(int n, ...)
- {
-   va_list ap;  /* points to each unnamed arg in turn */
-   int i, val, largest;
-   va_start(ap, n);  /* make ap point to 1st unnamed arg */
-   largest = va_arg(ap, int);
-   for (i = 1; i < n; ++i) {
-     val = va_arg(ap, int);
-     largest = (val > largest) ? val : largest;
-   }
-   va_end(ap); /* clean up when done */
-   return largest;
- }


# Variable-length Argument Lists
- 컴퓨터프로그래밍기초
- ‹#›
- Variable-length Argument Lists
- va_arg 매크로
- va_list 포인터가 가리키는 요소를 지정한 형으로 가져옴
- va_arg 매크로를 사용하면 va_list 포인터는 다음 요소를 가리킴
- va_end 매크로
- 가변 인자를 처리하기 위해 사용한 자원들을 반환(cleanup)
- va_end 매크로를 사용해 사용한 자원들을 반환하지 않은 상태로  va_start 매크로 사용 시 결과는 알 수 없음(undefined behavior)
- #include <stdio.h>   /* printf */
- #include <stdarg.h>  /* va_list, va_start, va_arg, va_end */
- int findmax(int, ...);
- int main(void)
- {
-   int max;
-   max = findmax(5, 23, 1, 52, -3, 7);
-   printf("The largest value is %d.\n", max);
-   return 0;
- }
- int findmax(int n, ...)
- {
-   va_list ap;  /* points to each unnamed arg in turn */
-   int i, val, largest;
-   va_start(ap, n);  /* make ap point to 1st unnamed arg */
-   largest = va_arg(ap, int);
-   for (i = 1; i < n; ++i) {
-     val = va_arg(ap, int);
-     largest = (val > largest) ? val : largest;
-   }
-   va_end(ap); /* clean up when done */
-   return largest;
- }


# Variable-length Argument Lists
- 컴퓨터프로그래밍기초
- ‹#›
- Variable-length Argument Lists
- minprintf 함수
- 사용자 정의 함수
- 가변 인자 함수
- printf 함수의 최소 기능만을 구현
- #include <stdio.h>
- #include <stdarg.h>  /* va_list, va_start, va_arg, va_end */
- /* minprintf: minimal printf with variable argument list */
- void minprintf(char *fmt, ...)
- {
-   va_list ap;  /* points to each unnamed arg in turn */
-   char *p, *sval;
-   int ival;
-   double dval;
-   /* make ap point to 1st unnamed arg */
-   va_start(ap, fmt);
-   for (p = fmt; *p; ++p) { ⋯
-   va_end(ap); /* clean up when done */
- }


# Variable-length Argument Lists
- 컴퓨터프로그래밍기초
- ‹#›
- Variable-length Argument Lists
- minprintf 함수 (Cont’d)
- 형식 문자열 분석
- 형식 지정자가 아니라면 해당 문자를 그대로 출력
- 형식 지정자라면 변환 문자에 따라 적절한 형태로 변환한 뒤 출력
- for (p = fmt; *p; ++p) { ⋯
-     if (*p != '%') {  /* ordinary characters */
-       putchar(*p);
-       continue;
-     }
-     switch (*++p) {  /* conversion specifications */
-     case 'd':
-       ival = va_arg(ap, int);
-       printf("%d", ival);
-       break;
-     case 'f':
-       dval = va_arg(ap, double);
-       printf("%f", dval);
-       break;
-     case 's':
-       for (sval = va_arg(ap, char *); *sval; ++sval)
-         putchar(*sval);
-       break;
-     default:
-       putchar(*p);
-       break;
-     }
-   }


# Formatted Input - Scanf
- 컴퓨터프로그래밍기초
- ‹#›
- Formatted Input - Scanf
- scanf 함수
- 표준 입력으로부터 문자열을 읽어와 형식 문자열에 따라 입력된 문자열 처리
- 
- 형식 문자열 내 형식 지정자의 개수가 n 개라면, 뒤따르는 전달인자의 수 또한 n개여야 함
- 반환값은 형식 문자열에 따라 변환된 결과들의 수를 의미
- #include <stdio.h>
- int main(void)
- {
-   int a, b, c;
-   printf("%d\n", scanf("%d %d %d", &a, &b, &c));   /* > 3 */
-   return 0;
- }
- int scanf(char *format, ...)  /* defined in header <stdio.h> */


# Formatted Input - Scanf
- 컴퓨터프로그래밍기초
- ‹#›
- Formatted Input - Scanf
- scanf 함수 (Cont’d)
- 형식 지정자 형태: %[*][width][length]specifier
- printf 함수와 상당히 유사함
- 두 함수 모두 가변 인자 함수이며, 형식 문자열을 사용함
- 형식 문자열 내 형식 지정자의 수가 n개라면, 형식 문자열 뒤에 등장하는 전달인자의 수 또한 n개여야 함
- scanf 함수는 표준 입력으로부터 데이터를 가져옴
- printf 함수는 표준 출력으로 데이터를 내보냄
- 각 매개변수는 반드시 포인터여야 함
- scanf 함수 호출 시 변환 결과를 저장할 변수들의 주소 전달
- scanf 함수 내에서 형식 문자열에 따라 처리가 완료된 결과는 이와 대응되는 매개변수의 주소를 간접 참조해 값을 간접적으로 전달


# Formatted Input - Scanf
- 컴퓨터프로그래밍기초
- ‹#›
- Formatted Input - Scanf
- scanf 함수 (Cont’d)
- 형식 문자열 내 형식 지정자를 모두 처리했거나, 입력된 문자열과 형식 문자열 간 대응에 실패하면 scanf 함수는 중지됨
- #include <stdio.h>
- int main(void) /* rudimentary calculator */
- {
-   double sum, v;
-   sum = 0;
-   /* warning: the arguments to scanf and sscanf
-      must be pointers. */
-   /* > +1 -2 3.0 4.5e1 s */
-   while (scanf("%lf", &v) == 1)
-     printf("\t%.2f\n", sum += v);
-   /*
-         1.00
-         -1.00
-         2.00
-         47.00
-   */
-   return 0;
- }


# Formatted Input - Scanf
- 컴퓨터프로그래밍기초
- ‹#›
- Formatted Input - Scanf
- scanf 함수 (Cont’d)
- 반환값은 입력 데이터가 성공적으로 형식 지정자와 대응된 개수이며, 더 이상 입력이 없는 경우 EOF 반환
- 반환값이 0인 경우와 EOF인 경우를 구분해야 함
- 반환값이 0인 경우는 형식 문자열 내에 입력된 데이터와 대응되는 형식 지정자가 없었음을 의미
- 반환값이 EOF인 경우는 표준 입력으로부터 가져올 수 있는 데이터가 더 이상 없음을 의미
- #include <stdio.h>
- int main(void)
- {
-   int a, b;
-   /* 
-      $ gcc test_scanf.c -o test_scanf -ansi -Wall
-      Case #1
-      $ cat in1
-      1 3 2 4
-      $ ./test_scanf.c < in1
-      1 + 3 = 4
-      2 + 4 = 6
-      Case #2
-      $ cat in2
-      100 200 300
-      $ ./test_scanf.c < in1
-      100 + 200 = 300
-      300 + 200 = 500
-   */
-   /* while (scanf("%d %d", &a, &b) != 2) */
-   while (scanf("%d %d", &a, &b) != EOF)
-     printf("%d + %d = %d\n", a, b, a + b);
-   return 0;
- }


# Formatted Input - Scanf
- 컴퓨터프로그래밍기초
- ‹#›
- Formatted Input - Scanf
- scanf 함수 (Cont’d)
- 형식 지정자 뒤에 빈칸이 존재하면 뒤따르는 공백문자 무시:
- C89, 7.9.6.2.A directive composed of white-space character(s) is executed by reading input up to thefirst non-white-space character(which remains unread), or until nomore characters can be read.
- #include <stdio.h>
- int main(void)
- {
-   int n;
-   char c;
-   /* > 1 d */
-   scanf("%d", &n);
-   scanf("%c", &c);
-   /* int: 1, char: */
-   printf("int: %d, char: %c\n", n, c);
-   return 0;
- }
- 
-   /* Solution #1 */  /* A directive composed of ' ' will be ignore
-      following while-spaces */
-   scanf("%d %c", &n, &c);
-   
-   /* Solution #2 */  scanf("%d", &n);
-   getchar();  /* use getchar() to consume a white-space */
-   scanf("%c", &c);


# Formatted Input - Scanf
- 컴퓨터프로그래밍기초
- ‹#›
- Formatted Input - Scanf
- scanf 함수 (Cont’d)
- 형식 문자열 내 형식 지정자를 제외한 일반 문자(ordinary characters)는 입력 스트림으로부터 읽어온 문자열의 문자와 순서가 서로 일치해야 함
- 형식 문자열의 문자와 입력 받은 문자열의 문자가 서로 일치하지 않으면 scanf 함수는 중지됨
- #include <stdio.h>
- int main(void)
- {
-   int day, month, year;
-   /* 
-      case #1
-      > 05/15/21
-      3
-      month: 5, day: 15, year: 21
-      case #2
-      > 05 15 21
-      1
-      month: 5, day: ??, year: ?? 
-   */
-   printf("%d\n", scanf("%d/%d/%d", &month, &day, &year));
-   printf("month: %d, day: %d, year: %d\n", month, day, year);
-   return 0;
- }


# Formatted Input - Scanf
- 컴퓨터프로그래밍기초
- ‹#›
- Formatted Input - Scanf
- scanf 함수 (Cont’d)
- 형식 지정자에 억제 문자(suppressing character, *) 사용 시 해당 형식 지정자로부터 처리된 데이터는 무시됨
- 형식 지정자에서 [width]를 설정하면 입력 받은 문자열로부터 [width] 값만큼 가져와 변환 문자 형으로 처리
- 형식 지정자 처리 도중에 공백 문자가 등장하면 처리 종료
- #include <stdio.h>
- int main(void)
- {
-   char str1[2], str2[10], str3[10];
-   int a, b, c;
-   /* > suppression */
-   scanf("%2c %*2c %4s %6s", str1, str2, str3);
- 
-   /* su ress ion */
-   printf("%c%c %s %s\n", str1[0], str1[1], str2, str3);
- 
-   /* > 123 456789 */
-   scanf("%2d %d %*4d %d", &a, &b, &c);
- 
-   /* 12 3 89 */
-   printf("%d %d %d\n", a, b, c);
-   return 0;
- }


# Formatted Input - Scanf
- 컴퓨터프로그래밍기초
- ‹#›
- Formatted Input - Scanf
- scanf 함수 (Cont’d)
- 정수(d, i) 지정자에서의 길이([length])
- 길이가 생략되었다면 형식 지정자의 처리 결과는 int 형
- 길이가 h일 경우 형식 지정자의 처리 결과는 short 형
- 길이가 l일 경우 형식 지정자의 처리 결과는 short 형
- #include <stdio.h>
- int main(void)
- {
-   short s;
-   int i;
-   long l;
- 
-   scanf("%hd %d %ld", &s, &i, &l);
-   return 0;
- }


# Formatted Input - Scanf
- 컴퓨터프로그래밍기초
- ‹#›
- Formatted Input - Scanf
- scanf 함수 (Cont’d)
- 실수(f , e , g) 지정자에서의 길이([length])
- 길이가 생략되었다면 형식 지정자의 처리 결과는 float 형
- 길이가 l일 경우 형식 지정자의 처리 결과는 double 형
- 길이가 L일 경우 형식 지정자의 처리 결과는 long double 형
- #include <stdio.h>
- int main(void)
- {
-   float f, f1, f2;
-   double d;
-   long double ld;
- 
-   /* > 3.14 1.23e1 */
-   scanf("%f %f", &f1, &f2);
-   printf("%.2f %.2f\n", f1, f2);
-   /* > 3.14 1.23e-1 */
-   scanf("%e %e", &f1, &f2);
-   printf("%.2f %.2f\n", f1, f2);
-   /* > 3.14 1.23e0 */
-   scanf("%g %g", &f1, &f2);
-   printf("%.2f %.2f\n", f1, f2);
- 
-   scanf("%f %lf %Lf", &f, &d, &ld);
-   return 0;
- }
- 3.14 12.30
- 
- 
- 3.14 0.12
- 
- 
- 3.14 1.23


# Formatted Input - Scanf
- 컴퓨터프로그래밍기초
- ‹#›
- Formatted Input - Scanf
- scanf 함수 (Cont’d)
- 지정자(specifier)
- Brian W. Kernighan and Dennis M. Ritchie. 1988. The C Programming Language (2nd. ed.). Prentice Hall Professional Technical Reference, USA.


# Formatted Input - Scanf
- 컴퓨터프로그래밍기초
- ‹#›
- Formatted Input - Scanf
- scanf 함수 (Cont’d)
- 지정자(specifier)
- d는 정수를 10진수로 처리
- o는 정수를 8진수로 처리
- h는 정수를 16진수로 처리
- i는 정수를 입력 받은 문자열의 형태에 따라 유연하게 처리
- u는 정수를 무부호형으로 처리
- %는 입력받은 문자열 중 하나의 % 문자 처리
- #include <stdio.h>
- int main(void)
- {
-   int i, o, h;
-   unsigned u;
-   /* > 100 077 0xFF */
-   scanf("%d %o %x", &i, &o, &h);
-   printf("%d %d %d\n", i, o, h);
-   /* > 100 077 0xFF */
-   scanf("%i %i %i", &i, &o, &h);
-   printf("%d %d %d\n", i, o, h);
-   /* > 2147483648 */
-   scanf("%u", &u);
-   printf("%u\n", u);
-   /* > %4 */
-   scanf("%%%d", &i);
-   printf("%d\n", i);
-   return 0;
- }
- 100 63 255
- 
- 
- 
- 100 63 255
- 
- 
- 
- 2147483648
- 
- 
- 
- 4


# Formatted Input - Scanf
- 컴퓨터프로그래밍기초
- ‹#›
- Formatted Input - Scanf
- sscanf 함수
- 동작은 scanf 함수와 동일하나, 표준 입력으로부터 문자열을 읽어오는 것이 아닌, 문자 배열로부터 문자열을 읽어옴
- 
- 
- 포인터 s는 읽어올 문자열을 가리키는 포인터
- 실수 값을 다룰 때 scanf 함수와 printf 함수의 변환 문자에 차이가 있음에 유의할 것
- /* defined in header <stdio.h> */ 
- int sscanf(char *s, char *format, arg1, arg2, ⋯)
- #include <stdio.h>
- int main(void)
- {
-   char s[] = "1 12.3 12.3 12.3 sscanf";
-   int i;
-   float f;
-   double d;
-   long double ld;
-   char str[10];
-   sscanf(s, "%d %f %lf %Lf %s", &i, &f, &d, &ld, str);
-   /* 1 12.300000 12.300000 12.300000 sscanf */
-   printf("%d %f %f %Lf %s\n", i, f, d, ld, str);
-   return 0;
- }


# Formatted Input - Scanf
- 컴퓨터프로그래밍기초
- ‹#›
- Formatted Input - Scanf
- sscanf 함수 (Cont’d)
- 형식 문자열 내에 일반 문자가 사용될 수 있음을 활용해 날짜 문자열을 받아오는 예:
- int month, day, year;
- char monthname[20];
- while (getline(line, sizeof(line)) > 0) {
-   if (sscanf(line, "%d %s %d", &day, monthname, &year) == 3)
-     printf("valid: %s\n", line);  /* 25 Dec 1998 form */
-       else if (sscanf(line, "%d/%d/%d", &month, &day, &year) == 3)
-     printf("valid: %s\n", line);  /* mm/dd/yy form */
-   else
-     printf("invalid: %s\n", line);  /* invalid form */
- }


# Formatted Input - Scanf
- 컴퓨터프로그래밍기초
- ‹#›
- Formatted Input - Scanf
- scanf 함수와 sscanf 함수 사용 시 주의사항
- scanf 함수와 sscanf 함수의 가변 인자들은 기록될 대상을 가리키는 주소값이어야 함
- 변수 자체를 전달하는 것이 아닌 주소를 가리키는 포인터를 전달인자로 넘겨주어야 함
- 
- 
- 가변 인자에 주소값이 아닌 값을 전달인자로 넘겨주어도 컴파일 시 오류가 발생하지 않으므로 주의해서 사용해야 함
- scanf("%d", n);   /* ERROR! */
-  scanf("%d", &n);  /* OK */


# File Access
- 컴퓨터프로그래밍기초
- ‹#›
- File Access
- 프로그램이 파일을 읽거나 파일에 쓰기 위해서는 먼저 fopen 함수를 사용해 열어야 함(be opened)
- 운영체제에 해당 파일을 사용하겠다고 알림
- 운영체제는 파일로부터 데이터를 읽거나 파일에 데이터를 쓸 수 있도록 파일에 접근 가능한 포인터(file pointer) 반환
- 파일 포인터는 프로그램과 외부 파일을 연결해주는 객체를 가리킴


# File Access
- 컴퓨터프로그래밍기초
- ‹#›
- File Access
- 파일 포인터
- 파일과 관련된 정보들이 들어있는 구조체를 가리키는 포인터
- 스트림 인터페이스가 사용하는 임시 저장 공간(buffer)
- 버퍼에서 현재 가리키고 있는 문자
- 다른 프로그램에서의 해당 파일 사용 여부
- 파일 사용 도중 파일의 끝에 도달했거나(end of file) 오류 발생에 대한 여부
- 표준 라이브러리는 사용자가 간편히 파일을 사용할 수 있도록 인터페이스 제공
- <stdio.h> 헤더 파일 내에 파일 구조체 선언이 포함되어 있으며, 사용자는 더 이상 파일 관련 세부 정보들을 알 필요가 없음


# File Access
- 컴퓨터프로그래밍기초
- ‹#›
- File Access
- 파일 포인터 사용 예
- 
- 
- FILE 형은 파일 관련된 정보들을 보관하고 있는 구조체에 typedef 키워드를 사용해 해당 구조체 형을 FILE로 지정한 것
- fp는 FILE 형을 가리키는 포인터 변수
- fopen은 파일에 접근 가능한 포인터를 반환하는 함수
- 프로그램과 외부 파일 간 연결 정보를 기록하고 있는 FILE 형 객체를 가리킴
- /* defined in header <stdio.h> */ 
- FILE *fp;
- FILE *fopen(char *name, char *mode);


# File Access
- 컴퓨터프로그래밍기초
- ‹#›
- File Access
- fopen 함수
- 
- 첫 번째 매개변수에는 사용할 파일의 경로를 문자열 형태로 전달
- 두 번째 매개변수에는 파일을 어떻게 사용할 것인지를 문자열 형태로 전달
- r : 읽기(read)
- w : 쓰기(write)
- a : 추가(append)
- 몇몇 환경에서는 ASCII 코드들로 작성된 텍스트 파일과 2진 코드들로 작성된 바이너리 파일을 구분함(e.g. Microsoft Windows)
- 텍스트 파일과 바이너리 파일을 구분해 처리하는 운영체제에서 바이너리 파일을 대상으로 할 경우, 문자 b를 추가해야 함
- e.g. rb, wb, ab
- fp = fopen(name, mode);


# File Access
- 컴퓨터프로그래밍기초
- ‹#›
- File Access
- fopen 함수 (Cont’d)
- 파일을 쓰기(w) 또는 추가(a) 목적으로 열고자 할 때, 열고자 하는 파일이 존재하지 않을 경우 파일을 새로 생성함(if possible)
- 파일을 쓰기(w) 목적으로 열고자 할 때, 열고자 하는 파일이 존재한다면 해당 파일에 있는 내용은 모두 삭제됨
- 열고자 하는 파일이 존재하고, 해당 파일의 내용을 유지하고 싶다면 추가(a) 목적으로 파일을 열어야 함
- 파일을 읽기(r) 목적으로 열고자 할 때, 파일이 존재하지 않거나 열고자 하는 파일에 대한 접근 권한이 없을 경우 오류 발생
- fopen 함수 호출 시 오류가 발생한다면, NULL 반환


# File Access
- 컴퓨터프로그래밍기초
- ‹#›
- File Access
- getc 함수
- fopen 함수를 호출해 열린 파일로부터 문자를 하나씩 읽어옴
- 
- 전달인자로 열린 파일을 가리키는 파일 포인터를 넘겨줌
- 파일 포인터는 fopen 함수를 통해 열어놓은 파일 관련 정보들을 저장하고 있는 객체를 가리킴
- 객체에는 입력 스트림 정보가 포함되어 있으며, 입력 스트림은 가져올 문자를 가리키고 있음
- 함수가 호출되면 스트림으로부터 문자 하나를 읽어옴
- 문자 하나를 성공적으로 읽어왔다면 getc 함수는 읽어온 문자를 반환하고, 스트림은 방금 읽어온 문자의 다음 문자를 가리킴
- 파일 포인터가 가리키는 대상이 EOF이거나 스트림 버퍼로부터 읽어오는 과정 중에 오류 발생 시 EOF 반환
- int getc(FILE *fp)  /* defined in header <stdio.h> */


# File Access
- 컴퓨터프로그래밍기초
- ‹#›
- File Access
- putc 함수
- fopen 함수를 호출해 열린 파일에 문자를 하나씩 내보냄
- 
- 전달인자로 출력할 문자와 열린 파일을 가리키는 파일 포인터를 넘겨줌
- 파일 포인터는 fopen 함수를 통해 열어놓은 파일 관련 정보들을 저장하고 있는 객체를 가리킴
- 객체에는 출력 스트림 정보가 포함되어 있으며, 출력 스트림은 문자가 기록될 위치를 가리키고 있음
- 함수가 호출되면 스트림이 가리키고 있는 위치에 문자를 내보냄
- 문자 하나를 성공적으로 내보냈다면 putc 함수는 내보낸 문자를 반환하고, 스트림은 방금 문자가 기록된 위치의 다음을 가리킴
- 오류 발생 시 EOF 반환
- int putc(int c, FILE *fp)  /* defined in header <stdio.h> */


# File Access
- 컴퓨터프로그래밍기초
- ‹#›
- File Access
- C 프로그램이 실행되면 세 개의 파일은 자동으로 열리며, 각 열린 파일들을 이용할 수 있는 포인터 제공
- <stdio.h> 헤더 파일 내에 정의되어 있음
- 표준 입력(standard input, stdin)
- 표준 출력(standard output, stdout)
- 표준 오류(standard error, stderr)
- 
- 일반적으로 파일 포인터 stdin은 키보드와 연결되며, 파일 포인터 stdout과 stderr는 모니터와 연결됨


# File Access
- 컴퓨터프로그래밍기초
- ‹#›
- File Access
- 파일 포인터 stdin, stdout, stderr는 FILE 형 객체를 가리키는 상수 포인터
- 해당 식별자들은 다른 값으로 바뀔 수 없으며, 다른 용도로 사용하고자 할 경우에는 freopen 함수를 사용해야 함
- 
- 두 파일 포인터 stdin, stdout은 입출력 재정의 또는 파이프 동작을 통해 표준 입력을 파일로부터 읽어오거나 표준 출력을 파일로 출력 가능
- 파일 포인터 strerr는 출력이 재정의되어도 화면 상에 오류 출력됨을 보장함


# File Access
- 컴퓨터프로그래밍기초
- ‹#›
- File Access
- getchar 함수와 putchar 함수는 <stdio.h> 헤더 파일 안에 매크로 형태로 정의되어 있음
- getchar 함수는 getc 함수에 파일 포인터 stdin를 전달인자로 넘겨준 형태
- putchar 함수는 putc 함수에 문자 하나와 파일 포인터 stdout을 전달인자로 넘겨준 형태
- /* defined in header <stdio.h> */ 
- #define getchar() getc(stdin)
- #define putchar(c) putc((c), stdout)


# File Access
- 컴퓨터프로그래밍기초
- ‹#›
- File Access
- fscanf 함수
- 동작은 scanf 함수와 동일하나, 파일 포인터를 전달인자로 넘겨받아 어느 객체로부터 데이터를 읽어올 것인지 결정
- 
- 
- fscanf 함수에 파일 포인터 stdin을 사용하면 scanf 함수와 동일한 동작 수행
- /* defined in header <stdio.h> */ 
- int fscanf(FILE *fp, char *format, ...);
- char arr[100];
- 
- fscanf(stdin, "%s", arr);  /* scanf("%s", arr); */


# File Access
- 컴퓨터프로그래밍기초
- ‹#›
- File Access
- fprintf 함수
- 동작은 printf 함수와 동일하나, 파일 포인터를 전달인자로 넘겨받아 어느 객체로 데이터를 내보낼 것인지 결정
- 
- 
- fprintf 함수에 파일 포인터 stdout을 사용하면 printf 함수와 동일한 동작 수행
- /* defined in header <stdio.h> */ 
- int fprintf(FILE *fp, char *format, ...);
- char arr[100];
- 
- fprintf(stdout, "%s", arr);  /* printf("%s", arr); */


# File Access
- 컴퓨터프로그래밍기초
- ‹#›
- File Access
- 파일의 내용을 연결해 출력하는 프로그램 cat(concatenate)
- 입력된 커맨드 라인 매개변수가 없다면 키보드로 입력된 문자열을 화면에 그대로 출력
- 입력된 커맨드 라인 매개변수가 있다면 각 매개변수를 이름으로 하는 파일을 열어 해당 파일 내용을 화면에 그대로 출력
- #include <stdio.h>
- /* cat: concatenate files, version 1 */
- int main(int argc, char *argv[])
- {
-   FILE *fp;
-   void filecopy(FILE *, FILE *);
-   /* no args; copy standard input */
-   if (argc == 1) {
-     filecopy(stdin, stdout);
-   } else { 
-     while (--argc > 0) { ⋯
-   }
-   return 0;
- }
- /* filecopy: copy file ifp to file ofp */
- void filecopy(FILE *ifp, FILE *ofp)
- {
-   int c;
-   while ((c = getc(ifp)) != EOF)
-     putc(c, ofp);
- }


# File Access
- 컴퓨터프로그래밍기초
- ‹#›
- File Access
- 파일의 내용을 연결해 출력하는 프로그램 cat(concatenate) (Cont’d)
- fclose 함수는 fopen 함수를 호출해 열어놓은 파일을 닫는 함수
- 대부분의 운영체제는 한 프로그램 당 열 수 있는 파일의 수가 정해져 있음
- 더 이상 사용하지 않는 파일은 반드시 fclose 함수를 호출해 열려있는 파일을 닫을 것
- while (--argc > 0) {
-       if ((fp = fopen(*++argv, "r")) == NULL) {
-         printf("cat: can't open %s\n", *argv);
-         return 1;
-       } else {
-         filecopy(fp, stdout);
-         fclose(fp);
-       }
-     }


# File Access
- 컴퓨터프로그래밍기초
- ‹#›
- File Access
- fclose 함수를 호출하면 출력 스트림을 비워줌
- 출력 스트림에 있는 내용들은 아직 대상에 기록되지 않는 상태
- fclose 함수를 호출하면 출력 스트림에 남아있는 모든 데이터를 사용중인 파일로 내보냄(flush)
- 
- fclose 함수는 프로그램 종료 시 자동으로 호출됨
- 각각 열려있는 파일마다 fclose 함수 호출


# Error Handling - Stderr and Exit
- 컴퓨터프로그래밍기초
- ‹#›
- Error Handling - Stderr and Exit
- 오류 처리가 추가된 파일의 내용을 연결해 출력하는 프로그램 cat
- 이전 cat 프로그램은 표준 출력을 재정의하면 오류 내용을 화면에 출력하지 못하는 문제점이 있음
- > (output redirection)
- | (pipe)
- 파일 포인터 stderr는 오류 정보를 출력하는 스트림이며, 출력이 재정의되어도 화면에 출력됨을 보장
- #include <stdio.h>
- #include <stdlib.h>
- /* cat: concatenate files, version 2 */
- int main(int argc, char *argv[])
- {
-   FILE *fp;
-   void filecopy(FILE *, FILE *);
-   char *prog = argv[0];  /* program name for errors */
-   /* no args; copy standard input */
-   if (argc == 1) {
-     filecopy(stdin, stdout);
-   } else {
-     while (--argc > 0) {
-       if ((fp = fopen(*++argv, "r")) == NULL) {
-         fprintf(stderr, "%s: can't open %s\n", prog, *argv);        exit(1);
-       } else {
-         filecopy(fp, stdout);
-         fclose(fp);
-       }
-     }
-   }
-   if (ferror(stdout)) {
-     fprintf(stderr, "%s: error writing stdout\n", prog);
-     exit(2);
-   }  exit(0);
- }
- ⋯


# Error Handling - Stderr and Exit
- 컴퓨터프로그래밍기초
- ‹#›
- Error Handling - Stderr and Exit
- 오류 처리가 추가된 파일의 내용을 연결해 출력하는 프로그램 cat (Cont’d)
- 오류 발생 시 실행파일 이름을 같이 출력하면 디버깅 시 용이
- #include <stdio.h>
- #include <stdlib.h>
- /* cat: concatenate files, version 2 */
- int main(int argc, char *argv[])
- {
-   FILE *fp;
-   void filecopy(FILE *, FILE *);
-   char *prog = argv[0];  /* program name for errors */
-   /* no args; copy standard input */
-   if (argc == 1) {
-     filecopy(stdin, stdout);
-   } else {
-     while (--argc > 0) {
-       if ((fp = fopen(*++argv, "r")) == NULL) {
-         fprintf(stderr, "%s: can't open %s\n", prog, *argv);        exit(1);
-       } else {
-         filecopy(fp, stdout);
-         fclose(fp);
-       }
-     }
-   }
-   if (ferror(stdout)) {
-     fprintf(stderr, "%s: error writing stdout\n", prog);
-     exit(2);
-   }  exit(0);
- }
- ⋯


# Error Handling - Stderr and Exit
- 컴퓨터프로그래밍기초
- ‹#›
- Error Handling - Stderr and Exit
- 오류 처리가 추가된 파일의 내용을 연결해 출력하는 프로그램 cat (Cont’d)
- exit 함수는 프로그램을 즉시 종료시킴
- exit 함수 호출 시 프로그램에서 열어놓은 각 파일들에 대해 fclose 함수 호출
- 출력 스트림에 남아있는 내용을 모두 목적지로 출력
- #include <stdio.h>
- #include <stdlib.h>
- /* cat: concatenate files, version 2 */
- int main(int argc, char *argv[])
- {
-   FILE *fp;
-   void filecopy(FILE *, FILE *);
-   char *prog = argv[0];  /* program name for errors */
-   /* no args; copy standard input */
-   if (argc == 1) {
-     filecopy(stdin, stdout);
-   } else {
-     while (--argc > 0) {
-       if ((fp = fopen(*++argv, "r")) == NULL) {
-         fprintf(stderr, "%s: can't open %s\n", prog, *argv);        exit(1);
-       } else {
-         filecopy(fp, stdout);
-         fclose(fp);
-       }
-     }
-   }
-   if (ferror(stdout)) {
-     fprintf(stderr, "%s: error writing stdout\n", prog);
-     exit(2);
-   }  exit(0);
- }
- ⋯


# Error Handling - Stderr and Exit
- 컴퓨터프로그래밍기초
- ‹#›
- Error Handling - Stderr and Exit
- 오류 처리가 추가된 파일의 내용을 연결해 출력하는 프로그램 cat (Cont’d)
- exit 함수는 main 함수에서의 반환문과 동일한 동작을 수행
- 
- exit 함수는 main 함수 뿐 아니라 호출된 다른 함수에서 사용해도 해당 프로그램을 즉각 종료시킬 수 있음
- bar 함수 내의 exit 함수를 호출하자마자 해당 프로그램은 종료됨
- /* defined in header <stdlib.h> */ 
- exit(0);  /* return 0; */
- #include <stdio.h>
- void bar(void)
- {
-   exit(127);
- }
- void foo(void)
- {
-   printf("Before bar()\n");
-   bar();
-   printf("After bar()\n");
- }
- int main(void)
- {
-   printf("Before foo()\n");
-   foo();
-   printf("After foo()\n");
-   return 0;
- }


# Error Handling - Stderr and Exit
- 컴퓨터프로그래밍기초
- ‹#›
- Error Handling - Stderr and Exit
- ferror 함수
- 파일 포인터가 가리키는 객체의 스트림에 오류가 발생한 경우 0이 아닌 값 반환
- 
- 출력 스트림은 오류가 거의 발생하지 않지만, 종종 오류를 일으킴(e.g. 저장 공간 부족, 권한 문제)
- 프로그램은 ferror 함수를 통해 입력, 출력 스트림의 오류 발생 여부를 필히 확인해야 함
- 
- feof 함수
- 파일 포인터가 가리키는 객체의 대상 EOF가 등장하면 0이 아닌 값 반환
- int ferror(FILE *fp)  /* defined in header <stdio.h> */
- int feof(FILE *fp)  /* defined in header <stdio.h> */


# Error Handling - Stderr and Exit
- 컴퓨터프로그래밍기초
- ‹#›
- Error Handling - Stderr and Exit
- ferror 함수와 feof 함수를 사용한 파일 복사 시 오류 처리
- fopen 함수를 읽기 목적으로 호출할 경우, 파일이 존재하지 않거나 권한이 없는 경우 NULL 반환
- fopen 함수를 쓰기 또는 추가 목적으로 호출할 경우, 저장 공간이 부족하거나 권한이 없는 경우 NULL 반환
- fopen 함수를 사용해 열어놓은 파일은 fclose 함수를 사용해 닫는 것을 권장
- #include <stdio.h>
- #include <stdlib.h> /* exit() function declared here */
- void filecopy(FILE *, FILE *);
- int main(void)
- {
-   FILE *src, *dst;
-   src = fopen("source.txt", "r");
-   dst = fopen("destination.txt", "w");
-   /* check error */
-   if (src == NULL || dst == NULL) {
-     printf("Unable to open file\n");
-     exit(1);
-   }
-   filecopy(src, dst);
-   fclose(src);
-   fclose(dst);
-   exit(0);
- }
- /* filecopy: copy file ifp to file ofp */
- void filecopy(FILE *ifp, FILE *ofp) ⋯


# Error Handling - Stderr and Exit
- 컴퓨터프로그래밍기초
- ‹#›
- Error Handling - Stderr and Exit
- ferror 함수와 feof 함수를 사용한 파일 복사 시 오류 처리 (Cont’d)
- getc 함수는 입력 스트림이 가리키는 다음에 가져올 문자가 EOF이거나 스트림에 오류가 발생했을 때 EOF 반환
- putc 함수는 출력 스트림에 오류가 발생했을 때 EOF 반환
- 출력 스트림에서 발생 가능한 대표적인 오류는 저장 공간 부족
- /* filecopy: copy file ifp to file ofp */
- void filecopy(FILE *ifp, FILE *ofp)
- {
-   int c;
-   while ((c = getc(ifp)) != EOF) {
-     /* The putc function normally return a copy of the byte that              
-        is has written - as confirmation of success.
-        If there is an error it returns EOF instead. */
-     if (putc(c, ofp) == EOF) {
-       printf("Error in writing to file\n");
-       exit(1);
-     }
-   }
-   /* normal */
-   if (feof(ifp))
-     printf("End of file\n");
-   /* abnormal */
-   if (ferror(ifp)) {
-     printf("Error in reading from file\n");
-     exit(1);
-   }
- }


# Line Input and Output
- 컴퓨터프로그래밍기초
- ‹#›
- Line Input and Output
- fgets 함수
- 문자열을 줄 단위로 읽어오는 함수
- 
- 파일 포인터가 가리키는 대상으로부터 줄 단위로 문자열을 읽어와 line 포인터 변수가 가리키는 배열에 기록
- 문자열에 개행문자('\n')가 포함되어 있다면 이를 포함해서 읽어옴
- 최대 maxline - 1개의 문자를 읽어올 수 있음
- 읽어온 문자열의 마지막에는 널문자('\0')가 위치해야 하므로 문자 배열 line에 최대 maxline - 1개의 문자를 기록할 수 있음
- 파일 포인터가 가리키는 대상으로부터 줄 단위의 문자열을 성공적으로 읽었다면 문자 배열 line 포인터 변수의 값(주소)를 반환하고, 문자열을 읽는 도중 EOF를 만나거나 오류 발생 시 NULL 반환
- char *fgets(char *line, int maxline, FILE *fp)  /* defined in header <stdio.h> */


# Line Input and Output
- 컴퓨터프로그래밍기초
- ‹#›
- Line Input and Output
- fgets 함수 (Cont’d)
- #include <stdio.h>
- /* fgets: get at most n chars from iop */
- char *fgets(char *s, int n, FILE *iop)
- {
-   register int c;
-   register char *cs;
-   cs = s;
-   /* 
-   1. n-1 characters will be read
-   2. returns EOF for end of file or error 
-   */
-   while (--n > 0 && (c = getc(iop)) != EOF) {
-     /* reads the next input line
-        (including the newline) from file iop */
-     if ((*cs++ = c) == '\n')
-       break;
-   }
-   *cs = '\0';
-   /* normally fgets returns s(pointer);
-      on end of file or error it returns NULL */
-   return (c == EOF && cs == s) ? NULL : s;
- }


# Line Input and Output
- 컴퓨터프로그래밍기초
- ‹#›
- Line Input and Output
- fgets 함수 (Cont’d)
- fgets 함수를 사용하면 getline 함수를 간결하게 구현할 수 있음
- fgets 함수는 데이터가 저장될 배열의 주소를 반환하거나 NULL을 반환
- getline 함수는 입력 받은 문자열의 길이를 반환하거나 0을 반환하므로 fgets 함수만 사용했을 때보다 유용한 정보를 얻을 수 있음
- #include <stdio.h>
- /* getline: read a line, return length */
- int getline(char *line, int max)
- {
-   if (fgets(line, max, stdin) == NULL)
-     return 0;
-   else
-     return strlen(line);
- }


# Line Input and Output
- 컴퓨터프로그래밍기초
- ‹#›
- Line Input and Output
- fputs 함수
- 문자열을 줄 단위로 내보내는 함수
- 
- line 포인터 변수를 간접 참조해 줄 단위로 문자열을 읽어와 파일 포인터가 가리키는 대상에 기록
- 문자열에 개행문자('\n')가 포함되어 있다면 이를 포함해서 내보냄
- 파일 포인터가 가리키는 대상에 성공적으로 문자열을 기록했다면 음수가 아닌 값(e.g. 0) 반환
- 문자열을 파일 포인터가 가리키는 스트림으로 내보내는 도중 오류 발생 시 EOF 반환
- int fputs(char *line, FILE *fp)  /* defined in header <stdio.h> */


# Line Input and Output
- 컴퓨터프로그래밍기초
- ‹#›
- Line Input and Output
- fputs 함수 (Cont’d)
- #include <stdio.h>
- /* fputs: put string s on file iop */
- /* fputs is already included in stdio.h */
- /* int fputs(char *s, FILE *iop) */
- int knr_fputs(char *s, FILE *iop)
- {
-   int c;
-   while (c = *s++)
-     putc(c, iop);
-   /* returns EOF if an error occurs, and non-negative otherwise */
-   return ferror(iop) ? EOF : 0;
- }


# Line Input and Output
- 컴퓨터프로그래밍기초
- ‹#›
- Line Input and Output
- gets 함수
- fgets 함수에 파일 포인터 stdin을 사용하는 것처럼 동작함
- 
- 표준 입력으로부터 문자열을 줄 단위로 읽어올 때, 문자열에 개행문자('\n')가 포함되어 있다면 이를 제거함
- line 포인터 변수가 가리키는 배열의 크기를 함수 측으로 전달하지 않으므로 배열의 크기보다 긴 문자열이 입력될 경우 다른 메모리 영역을 침범할 수 있음
- gets 함수보다는 fgets 함수 사용을 적극 권장
- char *gets(char *line)  /* defined in header <stdio.h> */


# Line Input and Output
- 컴퓨터프로그래밍기초
- ‹#›
- Line Input and Output
- puts 함수
- fputs 함수에 파일 포인터 stdout을 사용하는 것처럼 동작함
- 
- 표준 출력으로 문자열을 출력할 때, 문자열에 개행문자('\n')를 추가해서 내보냄
- 출력할 문자열 내에 개행문자가 포함되어 있더라도 개행문자를 추가함
- int puts(char *line)  /* defined in header <stdio.h> */


# Miscellaneous Functions
- 컴퓨터프로그래밍기초
- ‹#›
- Miscellaneous Functions
- 문자열 연산
- <string.h> 헤더 파일 필요
- 매개변수 s와 t는 char 형을 가리키는 포인터
- 매개변수 c와 n은 int 형
- strcat(s, t);      /* concatenate t to end of s */
- strncat(s, t, n);  /* concatenate n characters of t to end of s */
- strcmp(s, t);      /* return negative, zero, or positive for s < t, s == t, or
-                       s > t */
- strncmp(s, t, n);  /* same as strcmp but only in first n characters */
- strcpy(s, t);      /* copy t to s */
- strncpy(s, t, n);  /* copy at most n characters of t to s */
- strlen(s);         /* return length of s */
- strchr(s, c);      /* return pointer to first c in s, or
-                       NULL if not present */
- strrchr(s, c);     /* return pointer to last c in s, or
-                       NULL if not present */


# Miscellaneous Functions
- 컴퓨터프로그래밍기초
- ‹#›
- Miscellaneous Functions
- 형 검사 및 변환
- <ctype.h> 헤더 파일 필요
- 매개변수 c는 int 형
- isalpha(c); /* non-zero if c is alphabetic, 0 if not */
- isupper(c); /* non-zero if c is upper case, 0 if not */
- islower(c); /* non-zero if c is lower case, 0 if not */
- isdigit(c); /* non-zero if c is digit, 0 if not */
- isalnum(c); /* non-zero if isalpha(c) or isdigit(c), 0 if not */
- isspace(c); /* non-zero if c is blank, tab, newline, return, formfeed,
-                vertical tab */
- toupper(c); /* return c converted to upper case */
- tolower(c); /* return c converted to lower case */


# Miscellaneous Functions
- 컴퓨터프로그래밍기초
- ‹#›
- Miscellaneous Functions
- getc 함수와 ungetc 함수
- <stdio.h> 헤더 파일 필요
- 파일 포인터가 가리키는 대상으로부터 문자 하나를 읽어오거나 내보내는 역할 수행
- getc 함수는 스트림으로부터 문자 하나를 성공적으로 읽어왔다면 해당 문자를 반환하고, 더 이상 가져올 데이터가 없다면 EOF 반환
- ungetc 함수는 스트림으로 문자 하나를 성공적으로 내보냈다면 해당 문자를 반환하고, 내보내는 과정 중에 오류가 발생했다면  EOF 반환
- #include <stdio.h>
- int skipwhite(FILE *f)
- {
-   int c;
-   do {
-     c = getc(f);
-   } while (isspace(c));
-   return ungetc(c, f);
- }


# Miscellaneous Functions
- 컴퓨터프로그래밍기초
- ‹#›
- Miscellaneous Functions
- system 함수
- <stdlib.h> 헤더 파일 필요
- 터미널에서 실행 가능한 유틸리티들을 프로그램에서 실행할 수 있음
- 유틸리티의 종류는 운영체제의 종류에 따라 다름에 주의할 것
- #include <stdlib.h>
- int main(void)
- {
-   system("date");
-   system("ls");
-   return 0;
- }


# Miscellaneous Functions
- 컴퓨터프로그래밍기초
- ‹#›
- Miscellaneous Functions
- 저장공간 동적 할당
- malloc 함수
- 
- size 바이트 공간의 메모리를 힙(heap) 영역에 동적으로 할당
- 반환형은 void 형 포인터이며, 반환 받은 주소는 사용하고자 하는 형으로 형 변환을 해주어야 함
- 
- 
- 
- 할당 받은 공간은 초기화되지 않음
- malloc 함수 호출에 의해 동적으로 공간이 할당되었다면 해당 공간에 접근할 수 있는 주소를 반환하고, 할당 실패 시 NULL 반환
- void *malloc(size_t size)  /* defined in header <stdlib.h> */
- int n, *ip;
- n = 5;
- ip = (int *) malloc(n * sizeof(int));


# Miscellaneous Functions
- 컴퓨터프로그래밍기초
- ‹#›
- Miscellaneous Functions
- 저장공간 동적 할당 (Cont’d)
- calloc 함수
- 
- size 크기의 객체를 n개 힙 영역에 동적으로 할당(size x n 바이트)
- 반환형은 void 형 포인터이며, 반환 받은 주소는 사용하고자 하는 형으로 형 변환을 해주어야 함
- 
- 
- 
- 할당 받은 size 크기의 객체 n개는 모두 0으로 초기화됨
- calloc 함수 호출에 의해 동적으로 공간이 할당되었다면 해당 공간에 접근할 수 있는 주소를 반환하고, 할당 실패 시 NULL 반환
- void *calloc(size_t n, size_t size)  /* defined in header <stdlib.h> */
- int n, *ip;
- n = 5;
- ip = (int *) calloc(n, sizeof(int));


# Miscellaneous Functions
- 컴퓨터프로그래밍기초
- ‹#›
- Miscellaneous Functions
- 저장공간 동적 할당 (Cont’d)
- free 함수
- 
- malloc 함수 또는 calloc 함수를 호출해 동적으로 할당 받은 메모리 반환
- free 함수는 메모리 반환 시 메모리 할당 순서를 지킬 필요가 없음
- malloc 함수 또는 calloc 함수를 호출해 전달받은 주소를 free 함수의 매개변수로 넘겨주어야 함
- void free(void *ptr)  /* defined in header <stdlib.h> */


# Miscellaneous Functions
- 컴퓨터프로그래밍기초
- ‹#›
- Miscellaneous Functions
- 저장공간 동적 할당 (Cont’d)
- free 함수에 전달된 주소가 동적 할당 함수를 호출해 넘겨받은 주소가 아닐 경우 오류가 발생할 수 있음(undefined behavior)
- 이미 반환된 주소를 사용할 경우 오류가 발생할 수 있음(undefined behavior)
- 이미 반환된 주소를 다시 반환할 경우 오류가 발생할 수 있음(undefined behavior)
- /* WRONG */
- for (p = head; p != NULL; p = p->next)
-   free(p);
- /* OK! */
- for (p = head; p != NULL; p = q) {
-   q = p->next;
-   free(p);
- }


# Miscellaneous Functions
- 컴퓨터프로그래밍기초
- ‹#›
- Miscellaneous Functions
- 수학 연산
- <math.h> 헤더 파일 필요
- 매개변수 x와 y 는 double 형
- 아래 함수들의 반환형은 double 형
- sin(x);      /* sine of x, x in radians */
- cos(x);      /* cosine of x, x in radians */
- atan2(y, x); /* arctangent of y/x, in radians */
- exp(x);      /* exponential function ex */
- log(x);      /* natural (base e) logarithm of x (x > 0) */
- log10(x);    /* common (base 10) logarithm of x (x > 0) */
- pow(x, y);   /* xy */
- sqrt(x);     /* square root of x (x ≥ O) */
- fabs(x);     /* absolute value of x */


# Miscellaneous Functions
- 컴퓨터프로그래밍기초
- ‹#›
- Miscellaneous Functions
- 수학 연산 (Cont’d)
- gcc 컴파일러는 컴파일 시 <math.h> 헤더 파일을 기본으로 연결(linking)하지 않음
- <math.h> 헤더 파일을 사용할 수 있도록 컴파일 시 별도로 지시를 해야 함
-llibrary 옵션은 링커가 라이브러리(liblibrary)를 연결하도록 요청하는 옵션
- <math.h> 헤더 파일을 사용하기 위해서는 링커가 libm 라이브러리를 연결해주어야 함
- tasks.json 파일의 tasks 부분에서 args 부분에 -lm을 추가하면 링커는 연결(linking) 과정에서 libm 라이브러리를 연결


# Miscellaneous Functions
- 컴퓨터프로그래밍기초
- ‹#›
- Miscellaneous Functions
- 수학 연산 (Cont’d)
- 올바르게 tasks.json 파일을 수정했다면, 수학 관련 함수들을 사용할 수 있음
- "args": [
-         "-fdiagnostics-color=always",
-         "-g",
-         "${file}",
-         "-o",
-         "${fileDirname}/${fileBasenameNoExtension}",
-         "-ansi",
-         "-Wall",
-         "-lm"
-       ],
- #include <stdio.h>
- #include <math.h>
- int main(void)
- {
-   double theta;
-   /* sin2(t) + cos2(t) = 1 */
-   for (theta = 0.0; theta <= 180.0; theta += 30.0)
-     printf("%f\n", pow(sin(theta), 2) + pow(cos(theta), 2));
-   return 0;
- }


# Miscellaneous Functions
- 컴퓨터프로그래밍기초
- ‹#›
- Miscellaneous Functions
- 난수 생성
- rand 함수
- 
- 규칙성 없는 난수 생성
- srand 함수
- 
- 난수 생성에 필요한 변수를 새로운 값으로 대치
- void srand(unsigned int __seed)  /* defined in header <stdlib.h> */
- int rand(void)  /* defined in header <stdlib.h> */


# Miscellaneous Functions
- 컴퓨터프로그래밍기초
- ‹#›
- Miscellaneous Functions
- 난수 생성 (Cont’d)
- 
- 
- 
- 
- 
- 0보다 같거나 크고 1보다 작은 실수 난수 생성 방법:
- 
- RAND_MAX는 <stdlib.h>에 정의되어 있는 상수(0x7fff)이며, int 형이 표현할 수 있는 양수의 최대값을 표현
- #define frand() ((double) rand() / (RAND_MAX + 1.0))
- /* The template of random number generation */
- #include <stdio.h>
- #include <stdlib.h>  /* srand(), rand() */
- #include <time.h>    /* time() */
- int main(void)
- {
-   srand(time(NULL));
-   printf("Random Number: %d\n", rand());
-   return 0;
- }


# Wrap Up
- 컴퓨터프로그래밍기초
- ‹#›
- Wrap Up
- Chapter 1 - A Tutorial Introduction
- Chapter 2 - Types, Operators and Expressions
- Chapter 3 - Control Flow
- Chapter 4 - Functions and Program Structure
- Chapter 5 - Pointers and Arrays
- Chapter 6 - Structures
- Chapter 7 - Input and Output
- Chapter 8 - The UNIX System Interface


# Wrap Up
- 컴퓨터프로그래밍기초
- ‹#›
- Wrap Up
- 책 추천
- C Programming: A Modern Approach, 2nd Edition
- Code: The Hidden Language of Computer Hardware and Software
- Programming: Principles and Practice Using C++ (2nd Edition)


# Wrap Up
- 컴퓨터프로그래밍기초
- ‹#›
- Wrap Up
- 프로그래밍 및 코딩테스트 연습 사이트 추천
- Codeforces
- HackerRank
- Baekjoon Online Judge
- 프로그래머스
- 유용한 도구 추천
- GDB: The GNU Project Debugger
- GNU make
- CMake
- GitHub

