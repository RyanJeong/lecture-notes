#if 1 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
/* The simplest way to get input is by reading one character at a time
 * from standard input using the getchar function.
 * Returns the character read, or EOF on error or end of input. */
int getchar(void);
/* The simplest way to produce output is by writing one character at a time
 * to standard output using the putchar function.
 * Returns the character written, or EOF on error. */
int putchar(int c);
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */

#include <stdio.h>

void snippet1(void)
{
#if 1                           /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
    printf(":%d:\n", 100);      /* >:100:     */
    printf(":%6d:\n", 100);     /* >:   100:  */
    printf(":%-6d:\n", 100);    /* >:100   :  */
    printf(":%6d:\n", 1000000); /* >:1000000: */

    printf(":%*d:\n", 3, 1000000);     /* >:1000000:    */
    printf(":%*d:\n", 7, 1000000);     /* >:1000000:    */
    printf(":%*.10d:\n", 10, 1000000); /* >:0001000000: */

    printf(":%.5d:\n", 12);        /* >:00012:     */
    printf(":%5.5d:\n", 1234);     /* >:01234:     */
    printf(":%8.5d:\n", 1234);     /* >:   01234:  */
    printf(":%-8.5d:\n", 1234);    /* >:01234   :  */
    printf(":%8.5d:\n", 123456);   /* >:  123456:  */
    printf(":%-8.5d:\n", 123456);  /* >:123456  :  */
    printf(":%8d:\n", -123456);    /* >: -123456:  */
    printf(":%8.8d:\n", -123456);  /* >:-00123456: */
    printf(":%-8d:\n", -123456);   /* >:-123456 :  */
    printf(":%-8.8d:\n", -123456); /* >:-00123456: */
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
}

void snippet2(void)
{
#if 1 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
    int a[] = { 15, 077, 0xFF, 'A', -1 };

    printf("%3d %3o %3x %3X\n", a[0], a[0], a[0], a[0]); /* > 15  17   f   F  */
    printf("%3d %3o %3x %3X\n", a[1], a[1], a[1], a[1]); /* > 63  77  3f  3F  */
    printf("%3d %3o %3x %3X\n", a[2], a[2], a[2], a[2]); /* >255 377  ff  FF  */

    printf("%p %p\n", a, a + 1);     /* >0x08AF53D0 0x08AF53D4                */
    printf("%p %p\n", &a[0], &a[1]); /* >0x08AF53D0 0x08AF53D4                */
    printf("%c\n", a[3]);            /* >A                                    */
    printf("%u\n", a[4]);            /* >4294967295                           */
    printf("%ld\n", (long) 1 << 32); /* >4294967296                           */
    printf("%d\n", (long) 1 << 32);  /* UB: format mismatch(`%d` expects int) */
    printf("%hd\n", 1 << 16);        /* implementation-defined conversion     */
    printf("%d\n", 1 << 16);         /* >65536                                */
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
}

void snippet3(void)
{
#if 1                           /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
    printf(":%8.5f:\n", 1.25);  /* >: 1.25000: */
    printf(":%-8.5f:\n", 1.25); /* >:1.25000 : */

    printf(":%9.3f:\n", 3.141592);   /* >:    3.142:  */
    printf(":%-9.3f:\n", 3.141592);  /* >:3.142    :  */
    printf(":%9f:\n", 3.141592);     /* >: 3.141592:  */
    printf(":%-9f:\n", 3.141592);    /* >:3.141592 :  */
    printf(":%10.3e:\n", 3.141592);  /* >: 3.142e+00: */
    printf(":%-10.3E:\n", 3.141592); /* >:3.142E+00 : */

    printf("%f %e %g\n", 1.0, 1.0, 1.0); /* >1.000000 1.000000e+00 1 */
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
}

void snippet4(void)
{
#if 1                  /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
    double d1 = 0.125; /* 1 / 8 */
    double d2 = 0.0000152587890625; /* 1 / 65536 */
    double d3 = 1234.56;

    printf("%f\n", d1);   /* >0.125000     */
    printf("%e\n", d1);   /* >1.250000e-01 */
    printf("%g\n", d1);   /* >0.125        */
    printf("%f\n", d2);   /* >0.000015     */
    printf("%E\n", d2);   /* >1.525879E-05 */
    printf("%G\n", d2);   /* >1.52588E-05  */
    printf("%e\n", d3);   /* >1.234560e+03 */
    printf("%.3g\n", d3); /* >1.23e+03     */
    printf("%.4g\n", d3); /* >1235         */
#endif                    /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
}

void snippet5(void)
{
#if 1                         /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
    char *s = "Hello, world"; /* The length of the string is 12 */

    printf(":%s:\n", s);       /* >:Hello, world:                             */
    printf(":%10s:\n", s);     /* >:Hello, world:                             */
    printf(":%.10s:\n", s);    /* >:Hello, wor:                               */
    printf(":%-10s:\n", s);    /* >:Hello, world:                             */
    printf(":%15s:\n", s);     /* >:   Hello, world:                          */
    printf(":%.15s:\n", s);    /* >:Hello, world:                             */
    printf(":%-15s:\n", s);    /* >:Hello, world   :                          */
    printf(":%15.10s:\n", s);  /* >:     Hello, wor:                          */
    printf(":%-15.10s:\n", s); /* >:Hello, wor     :                          */

    printf("100%%\n"); /* >100% */
#endif                 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
}

void snippet6(void)
{
#if 1 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
    char *s = "%d\n";

    printf(s);       /* FAILS if `s` contains `%`, >????? */
    printf("%s", s); /* SAFE                       >%d    */
#endif               /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
}

void snippet7(void)
{
#if 1 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
    int i, o, h;
    unsigned u;

    /* Suppose the user inputs: 100 077 0xFF */
    scanf("%d %o %x", &i, &o, &h);
    printf("%d %d %d\n", i, o, h); /* >100 63 255 */

    /* Suppose the user inputs: 100 077 0xFF */
    scanf("%i %i %i", &i, &o, &h);
    printf("%d %d %d\n", i, o, h); /* >100 63 255 */

    /* Suppose the user inputs: 2147483648 */
    scanf("%u", &u);
    printf("%u\n", u); /* >2147483648 */

    /* Suppose the user inputs: %4 */
    scanf("%%%d", &i);
    printf("%d\n", i); /* >4 */
#endif                 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
}

void snippet8(void)
{
#if 1 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
    float f1, f2;

    /* Suppose the user inputs: 3.14 1.23e1 */
    scanf("%f %f", &f1, &f2);
    printf("%.2f %.2f\n", f1, f2); /* >3.14 12.30 */

    /* Suppose the user inputs: 3.14 1.23e-1 */
    scanf("%e %e", &f1, &f2);
    printf("%.2f %.2f\n", f1, f2); /* >3.14 0.12 */

    /* Suppose the user inputs: 3.14 1.23e0 */
    scanf("%g %g", &f1, &f2);
    printf("%.2f %.2f\n", f1, f2); /* >3.14 1.23 */
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
}

void snippet9(void)
{
#if 1 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
    int n;
    char c;

    /* Suppose the user inputs: 1 d */
    /* The space between 1 and d remains unread after the first scanf */
    scanf("%d", &n);         /* consume '1' */
    scanf("%c", &c);         /* consume ' ' and leave 'd' in the buffer */
    printf("%d %c\n", n, c); /* >1 */
#endif                       /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
}

void snippet10(void)
{
#if 1 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
    int n;
    char c;

    /* Suppose the user inputs: 1 d */
    /* The space between 1 and d is consumed by the space in the
     * format string "%d %c" */
    scanf("%d %c", &n, &c);  /* %d: consume '1', %c: consume 'd' */
    printf("%d %c\n", n, c); /* >1 d */
#endif                       /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
}

void snippet11(void)
{
#if 1 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
    int n;
    char c;

    /* Suppose the user inputs: 1 d */
    /* The space between 1 and d remains unread after the first scanf */
    scanf("%d", &n);         /* consume '1' */
    getchar();               /* consume ' ' */
    scanf("%c", &c);         /* consume 'd' */
    printf("%d %c\n", n, c); /* >1 d */
#endif                       /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
}

void snippet12(void)
{
#if 1 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
    int d, m, y;

    /* Suppose the user inputs: 05/15/21 */
    scanf("%d/%d/%d", &m, &d, &y);
    printf("m: %d, d: %d, y: %d\n", m, d, y); /* >m: 5, d: 15, y: 21 */
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */

#if 1 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
    /* Suppose the user inputs: 05 15 21 */
    scanf("%d/%d/%d", &m, &d, &y);
    printf("m: %d, d: %d, y: %d\n", m, d, y); /* >m: 5, d: ???, y: ??? */
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
}

void snippet13(void)
{
#if 1 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
    char str1[2], str2[10], str3[10];
    int a, b, c;

    /* Suppose the user inputs: suppression */
    scanf("%2c %*2c %4s %6s", str1, str2, str3);
    printf("%c%c %s %s\n", str1[0], str1[1], str2, str3); /* >su ress ion */

    /* Suppose the user inputs: 123 456789 */
    scanf("%2d %d %*4d %d", &a, &b, &c);
    printf("%d %d %d\n", a, b, c); /* >12 3 89 */
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
}

void snippet14(void)
{
#if 1 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
    short s;
    int i;
    long l;
    float f;
    double d;
    long double ld;

    /* integer */
    scanf("%hd %d %ld", &s, &i, &l);
    /* floating-point */
    scanf("%f %lf %Lf", &f, &d, &ld);
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
}

void snippet15(void)
{
#if 1 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
    double sum, v;

    sum = 0;
    /* Suppose the user inputs: +1  -2  3.0  4.5e1  s */
    while (scanf("%lf", &v) == 1)
        printf("\t%.2f\n", sum += v); /* >1.00
                                         >-1.00
                                         >2.00
                                         >47.00 */
    /* Expected numbers but encountered a non-numeric input (`s`), terminate the
     * loop and `s` still in the input buffer */
    putchar(getchar()); /* >s     */
#endif                  /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
}

void snippet16(void)
{
#if 1 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
    int a, b, ret;
    /* Suppose the user inputs: 10  30  20 */
    while ((ret = scanf("%d %d", &a, &b)) == 2)
        printf("%d + %d = %d (%d)\n", a, b, a + b, ret); /* >10 + 30 = 40 (2) */
    printf("ret: %d\n", ret);                            /* >ret: 1 */
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */

#if 1 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
    /* Suppose the user inputs: 10  30  20 */
    while ((ret = scanf("%d %d", &a, &b)) != EOF)
        printf("%d + %d = %d (%d)\n", a, b, a + b, ret); /* >10 + 30 = 40 (2)
                                                          * >20 + 30 = 50 (1) */
    printf("ret: %d\n", ret);                            /* >ret: -1 */
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
}
