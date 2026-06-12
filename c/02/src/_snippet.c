void snippet1(void)
{
#if 0  /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
    int num_seat;  /* ok */
    float rad_1;   /* ok */
    int 2nd_trial; /* error: invalid suffix "nd_trial" on integer constant */
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */

#if 1                 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
    int _is_modified; /* ok, but don't use it */
#endif                /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */

#if 1         /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
    int a, A; /* ok, `a` and `A` are different variables */
#endif        /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */

    (void) _is_modified; /* Avoid unused variable warning */
    (void) a;            /* Avoid unused variable warning */
    (void) A;            /* Avoid unused variable warning */
}

void snippet2(void)
{
#if 1 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
    /*1*/ char c1 = 'A';
    /*2*/ char c2 = 65; /* In ASCII, 0x41 = 'A' */
#endif                  /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */

    (void) c1; /* Avoid unused variable warning */
    (void) c2; /* Avoid unused variable warning */
}

#if 1                        /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
#define UPPER_Z '\132'       /* Octal 132 = Decimal 90 = 'Z' */
#define QUESTION_MARK '\077' /* Octal 077 = Decimal 63 = '?' */

#define BELL_OCT1 '\007' /* Octal 007 = Decimal  7 = ASCII Bell */
#define BELL_OCT2 '\07'  /* Octal  07 = Decimal  7 = ASCII Bell */
#define VTAB '\13'       /* Octal  13 = Decimal 11 = ASCII Vertical Tab */
#define SOH '\1'         /* Octal   1 = Decimal  1 = ASCII Start of Heading */

#define UPPER_A '\x41' /* Hex 0x41 = Decimal 65 = 'A' */
#define LF '\x0A'      /* Hex 0x0A = Decimal 10 = ASCII Line Feed */
#define BELL_HEX '\x7' /* Hex 0x07 = Decimal  7 = ASCII Bell */
#endif                 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */

#if 1 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
#define MAXLINE 1000
char line[MAXLINE + 1];

#define LEAP 1 /* in leap years */
int days[31 + 28 + LEAP + 31 + 30 + 31 + 30 + 31 + 31 + 30 + 31 + 30 + 31];
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */

#include <stdio.h>

void snippet3(void)
{
#if 1 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
    printf("It's useful for splitting up long strings across several lines");

    printf("It's useful"
           " for splitting up long strings"
           " across several lines");
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
}

#ifdef VTAB
#undef VTAB
#endif

#if 1 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
enum escapes {
    BELL = '\a',
    BACKSPACE = '\b',
    TAB = '\t',
    NEWLINE = '\n',
    VTAB = '\v',
    RETURN = '\r'
};

enum months { JAN = 1, FEB, MAR }; /* FEB is 2, MAR is 3 */

enum boolean { NO, YES };     /* NO is 0, YES is 1 */
enum boolean condition = YES; /* condition can be initialized to YES or NO */
#endif                        /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */

void snippet4(void)
{
#if 1 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
    /* declarations without initialization */
    char c;
    int i;

    /* declarations with initialization */
    char esc = '\\';
    int idx = 0;
    float eps = 10e-5;
    char str[10] = "Hi"; /* It is a short-hand that allows initializing string
                            literals */
#endif                   /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */

    (void) c;   /* Avoid unused variable warning */
    (void) i;   /* Avoid unused variable warning */
    (void) esc; /* Avoid unused variable warning */
    (void) idx; /* Avoid unused variable warning */
    (void) eps; /* Avoid unused variable warning */
    (void) str; /* Avoid unused variable warning */
}

void snippet5(void)
{
#if 1 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
    const double e = 2.71828182845905;

    int strlen(const char[]); /* strlen uses one read-only parameter */
#endif                        /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */

    (void) e;      /* Avoid unused variable warning */
    (void) strlen; /* Avoid unused function warning */
}

void snippet6(void)
{
    int valid = 1;

#if 1              /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
    if (!valid) {} /* preferred style */

    if (valid == 0) {} /* also correct, but less readable */
#endif                 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */

    (void) valid; /* Avoid unused variable warning */
}

int snippet7(int i)
{
#if 1 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
    /* ++i: Increments the value first */
    i = i + 1;
    return i;
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
}

int snippet8(int i)
{
#if 1 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
    /* i++: Uses the value first, then increments */
    int temp = i;
    i = i + 1;
    return temp;
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
}

void snippet9(void)
{
#if 1 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
    int a, b;

    b = 3;
    a = b++; /* a = 3, b = 4 */
    a = b;   /* a = 4, b = 4 */
    a = ++b; /* a = 5, b = 5 */
#endif       /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */

    (void) a; /* Avoid unused variable warning */
    (void) b; /* Avoid unused variable warning */
}

void snippet10(void)
{
    int yyval[100];
    int yypv[100];
    int p1, p2, p3, p4;

#if 1 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
    yyval[yypv[p3 + p4] + yypv[p1]] = yyval[yypv[p3 + p4] + yypv[p1]] + 2;
    yyval[yypv[p3 + p4] + yypv[p1]] += 2;
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */

    (void) yyval; /* Avoid unused variable warning */
    (void) yypv;  /* Avoid unused variable warning */
    (void) p1;    /* Avoid unused variable warning */
    (void) p2;    /* Avoid unused variable warning */
    (void) p3;    /* Avoid unused variable warning */
    (void) p4;    /* Avoid unused variable warning */
}

void snippet11(void)
{
    int x, y;

#if 1 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
    x *= y + 1;
    /*
     * 1. x *= (y + 1)
     * 2. x = x * (y + 1)
     */
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */

#if 0  /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
    if (x >>= y != 0) { /* do something */ }
    /*
     * 1. x >>= (y != 0)
     * 2. x = x >> (y != 0)
     */
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */

    (void) x; /* Avoid unused variable warning */
    (void) y; /* Avoid unused variable warning */
}

void snippet12(void)
{
#if 1 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
    /* Case #1 */
    char a = 127;
    char b = 127;
    short c = a + b; /* 1. a + b -> (int) a + (int) b = 254(to prevent overflow)
                        2. short c = (short) 254 */

    /* Case #2 (NB: assume that both short and int are 2-byte data types) */
    unsigned short x = 65535; /* USHRT_MAX */
    int i = x; /* `i` cannot represent `x`; `x` converts to an unsigned int */
#endif         /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */

    (void) a; /* Avoid unused variable warning */
    (void) b; /* Avoid unused variable warning */
    (void) c; /* Avoid unused variable warning */
    (void) x; /* Avoid unused variable warning */
    (void) i; /* Avoid unused variable warning */
}

void snippet13(void)
{
#if 1 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
    float f = 3.14f;
    double d = 2.718;

    /* Although `f` is float, when passed to printf (a variadic function),
       it is promoted to double */
    printf("float promoted to double: %f\n", f);

    printf("double remains double: %f\n", d); /* use %f for double, not %lf */
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */

    (void) f; /* Avoid unused variable warning */
    (void) d; /* Avoid unused variable warning */
}

void snippet14(void)
{
#if 0  /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
    int a = 'A';    /* Converting a narrower operand into a wider one is ok */
    char c = 12345; /* Converting a wider operand into a narrower one like this
                       could cause information to be lost (Warning) */
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
}

void snippet15(void)
{
#if 1 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
    float pi = (float) 3.14;
    int area =
        (int) (3 * 3 * pi); /* decimal dropped, but warning is suppressed */
#endif                      /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */

    (void) pi;   /* Avoid unused variable warning */
    (void) area; /* Avoid unused variable warning */
}

void snippet16(void)
{
#if 1 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
    int i = 256;
    char c = 'A'; /* ASCII 'A' = 65 */
    float f = 3.14;

    c = i; /* c = 0 (overflow) */
    i = c; /* i = 0 */
    i = f; /* i = 3 (decimal dropped) */
    f = i; /* f = 3.0 */
#endif     /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */

    (void) i; /* Avoid unused variable warning */
    (void) c; /* Avoid unused variable warning */
    (void) f; /* Avoid unused variable warning */
}

void snippet17(void)
{
#if 0  /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
    int n = 100;
    float f = 3.14;

    (n > 0) ? f : n; /* the evaluated type is float */
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */

#if 1 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
    int n = 2;

    /* You can replace this if-else statement with ternary operator:
       if (n == 1)
           printf("You have %d item\n", n);
       else
           printf("You have %d items\n", n); */
    printf("You have %d item%c\n", n, (n == 1) ? '\0' : 's');
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */

    (void) n; /* Avoid unused variable warning */
}

void snippet18(void)
{
    int x, y, z, w;

#if 0  /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
    x++ *y *z + w++;

/*
 - 1. [1] '++' has the highest precedence
 - 2. [2] '++' is right-to-left associative:
 -     => x++ * y * z + (w++)
 -     => (x++) * y * z + (w++)
 - 3. [1] '*' has the next highest precedence
 - 4. [2] '*' is left-to-right associative:
 -     => ((x++) * y) * z + (w++)
 -     => (((x++) * y) * z) + (w++)
 - 5. [1] '+' has the next precedence
 - 6. [2] '+' is left-to-right associative:
 -     => ((((x++) * y) * z) + (w++)) */
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */

    (void) x; /* Avoid unused variable warning */
    (void) y; /* Avoid unused variable warning */
    (void) z; /* Avoid unused variable warning */
    (void) w; /* Avoid unused variable warning */
}

void snippet19(void)
{
#if 1 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
    int i = 2;
    ++i; /* side effect: i + 1 */
#endif   /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */

    (void) i; /* Avoid unused variable warning */
}

int f(void)
{
    return 1;
}

int g(void)
{
    return 2;
}

void snippet20(void)
{
#if 1 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
      /* Case 1: If both functions f() and g() have side effects on global
       * variables, the result of f() + g() may vary depending on which function
       * is evaluated first.
       *   e.g., extern int a = 4, b = 5, c = 6;
       *         f(): increment all global variables by 1, return their sum.
       *         g(): multiply all global variables by 2, return their sum. */
    int res = f() + g();
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */

    (void) res; /* Avoid unused variable warning */
}

int power(int base, int exp)
{
    int result = 1;
    int i;

    for (i = 0; i < exp; i++)
        result *= base;
    return result;
}

void snippet21(void)
{
#if 0  /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
    /* Case 2: The value of `i2` is incremented before being printed, but the
     * order of evaluation between arguments is unspecified. Depending on
     * whether ++i2 or power(2, i2) is evaluated first, the printed values may
     * differ. */
    int i2 = 5;
    printf("%d %d\n", ++i2, power(2, i2));
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
}

void snippet22(void)
{
    int a[100];
#if 0  /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
    /* Case 3: This causes undefined behavior. The variable `i3` is modified
     * (`i3++`) and read (`a[i3]`) in the same expression without an intervening
     * sequence point. */
    int i3 = 0;
    a[i3] = i3++;
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */

    (void) a; /* Avoid unused variable warning */
}

void snippet23(void)
{
#if 0  /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
    /* Case 4: These expressions are also undefined behavior. Because `i4` is
     * both modified and accessed multiple times in the same expression without
     * a sequence point, the result is unpredictable. */
    int i4 = 2;
    i4 + i4 + ++i4; /* Could be 2 + 2 + 3 or 3 + 3 + 3, etc. */
    i4 + i4 + i4++; /* Could be 2 + 2 + 2 or 3 + 3 + 2, etc. */
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
}