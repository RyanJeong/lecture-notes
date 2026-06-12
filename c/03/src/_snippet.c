#include <stdio.h>

void snippet1(void)
{
#if 0  /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
  a = 10 /* Assignment expression: evaluates to 10 (the assigned value) */
  b + c  /* Addition expression: evaluates to the sum of `b` and `c` */
  x++    /* Post-increment expression: evaluates to the current value of `x`,
            then increments `x` by 1 */
  f(x)   /* Function call expression: evaluates to the return value of function
            `f` with argument `x` */
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
}

void snippet2(void)
{
    int x, i;
#if 1 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
    /* A statement = <expression(opt)> + ; */
    x = 0;                   /* assignment expression + ; */
    ++i;                     /* pre-increment expression + ; */
    printf("Hello, world!"); /* function call expression + ; */

    /* Following statements are also valid (use empty expressions) */
    ;  /* (empty expression) + ; */
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */

    (void) x; /* To avoid "unused variable" warning */
    (void) i; /* To avoid "unused variable" warning */
}

void snippet3(void)
{
    int x, y, z, a, b, n;

#if 1          /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
    if (x > 0) /* statement -> expression-statement */
        y = 1;

    if (x > 0) /* statement -> compound-statement */ {
        int y = 10;
        y += 5;
    }

    if (x > 0) /* statement -> selection-statement */
        if (y > 0)
            z = 1;
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */

#if 0  /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
    if (n > 0)
        if (a > b)
            z = a;
    else
        z = b;
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */

#if 0  /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
    if (n > 0)
        if (a > b)
            z = a;
        else
            z = b;
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */

#if 1 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
    if (n > 0) {
        if (a > b)
            z = a;
    } else
        z = b;
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */

#if 1 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
    switch (100)
    case 200: /* `case` determines where the execution jumps to when the switch
                 expression matches the case label */
        printf("switch statement with case label");

    switch (300)
    default: /* `default` determines where the execution jumps to when no case
                label matches */
        printf("switch statement with default label");
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */

    (void) x; /* To avoid "unused variable" warning */
    (void) y; /* To avoid "unused variable" warning */
    (void) z; /* To avoid "unused variable" warning */
    (void) a; /* To avoid "unused variable" warning */
    (void) b; /* To avoid "unused variable" warning */
    (void) n; /* To avoid "unused variable" warning */
}

void snippet4(void)
{
#if 1 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
    /*   switch (expression) compound-statement */
    switch (1) {
    case 1:
        putchar('A'); /* case constant-expression : expression-statement */
        break;        /* jump-statement */
    case 2:
        putchar('B'); /* case constant-expression : expression-statement */
        break;        /* jump-statement */
    default:
        putchar('-'); /* default : expression-statement */
    }                 /* -> Compound-statement has 5 statements */
#endif                /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */

    switch (1) {
#if 0  /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
    case 1:
        int x = 10; /* Invalid: declarations are not statements */
        break;
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */

#if 0  /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
    case 1: {
        int x = 10; /* Valid: compound statement can contain declarations */
        break;
    }
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
    }
}

void snippet5(void)
{
#if 0  /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
    /* You can replace the following phrase with `switch`:
    if (c >= '0' && c <= '9')
        ++ndigit[c - '0'];
    else if ((c == ' ') || (c == '\n') || (c == '\t'))
        ++nwhite;
    else
        ++nother; */

    switch (c) {
    case '0': case '1': case '2': case '3': case '4':
    case '5': case '6': case '7': case '8': case '9':
        ++ndigit[c - '0'];
        break;
    case ' ': case '\n': case '\t':
        ++nwhite;
        break;
    default:
        ++nother;
    }
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
}

void snippet6(void)
{
#if 1 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
    int num = 3;

    switch (num) {
    case 1:
        printf("num is 1.\n");
        break;
    default:
        printf("No matching number. (Default)\n");
        /* What happens if there's no break here? */
    case 2:
        printf("num is 2.\n");
        break;
    }  /* Output: No matching number. (Default)\nnum is 2. (fall-through) */
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */

    (void) num; /* To avoid "unused variable" warning */
}

void snippet7(void)
{
    int i, a[100];

#if 1 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
    for (i = 0; i < 100; ++i) {
        if (a[i] >= 0) {
            /* only positive elements present here. */
        }
    }
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */

#if 1 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
    for (i = 0; i < 100; ++i) {
        if (a[i] < 0)
            continue; /* skip negative elements */

        /* only positive elements present here. */
    }
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */

    (void) i; /* To avoid "unused variable" warning */
    (void) a; /* To avoid "unused variable" warning */
}

void snippet8(void)
{
    int a[100], b[100], n, m, i, j, found;

#if 1 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
    /*
     * Goto could be replaced with a sentinel variable or with a function call.
     */
    for (i = 0; i < n; ++i) {
        for (j = 0; j < m; ++j) {
            if (a[i] == b[j])
                goto found;
        }
    }
    return; /* didn't find any common elements */
found:
    printf("got one: a[i] == b[j]\n");
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */

    (void) a;     /* To avoid "unused variable" warning */
    (void) b;     /* To avoid "unused variable" warning */
    (void) n;     /* To avoid "unused variable" warning */
    (void) m;     /* To avoid "unused variable" warning */
    (void) i;     /* To avoid "unused variable" warning */
    (void) j;     /* To avoid "unused variable" warning */
    (void) found; /* To avoid "unused variable" warning */
}

void snippet9(void)
{
    char s[1024];
    int i = 0;
    int n = 123;

#if 1 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
    /* do-while loop using a single statement */
    do
        s[i++] = (n % 10) + '0';
    while ((n /= 10) > 0); /* It can be confused with a while without a body */
#endif                     /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */

#if 1 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
    /* do-while loop using a compound statement */
    do {
        s[i++] = (n % 10) + '0';
    } while ((n /= 10) > 0);
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */

    (void) s; /* To avoid "unused variable" warning */
    (void) i; /* To avoid "unused variable" warning */
    (void) n; /* To avoid "unused variable" warning */
}

void foo(int a, int b, int c)
{
    (void) a; /* To avoid "unused variable" warning */
    (void) b; /* To avoid "unused variable" warning */
    (void) c; /* To avoid "unused variable" warning */
}

void snippet10(void)
{
    int a, b, c;
    a = b = c = 100;

#if 1 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
    /* The function `foo` takes three arguments, with the second argument set
       to 5. */
    foo(a, (b = 3, b + 2), c);
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */

    (void) a; /* To avoid "unused variable" warning */
    (void) b; /* To avoid "unused variable" warning */
    (void) c; /* To avoid "unused variable" warning */
}
