void snippet1(void)
{
#if 1 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
    /* Automatic variables without initialization -> contain garbage values */
    char c;  /* address: 0x08AF53DC */
    char *p; /* address: 0x08AF53E0 */
#endif       /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */

#if 1       /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
    p = &c; /* The unary & operator yields the address of its operand. */
#endif      /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */

    (void) p; /* Avoid unused variable warning. */
}

void snippet2(void)
{
#if 1 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
    int x = 10, y = 20;

    /* `&x` yields the address of `x` (rvalue of type int *) */
    int *ip = &x;

    /* `*ip` is an lvalue (refers to `x`), yields 10 -> `y` becomes 11 */
    y = *ip + 1;

    /* `*ip` reads `x` (10), adds 1, writes back -> `x` becomes 11 */
    *ip += 1;

    /* Pre-increment: `*ip` becomes 12 before value is used */
    ++*ip;

    /* Post-increment: `*ip` yields 12, then increments -> `x` is 13 */
    (*ip)++;
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */

    (void) y; /* Avoid unused variable warning. */
}

void snippet3(void)
{
#if 1                          /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
    int x = 1, y = 2, arr[10]; /* automatic variables */
    int *ip;                   /* Declare `ip` as a pointer to an int */
#endif                         /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */

#if 1        /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
    ip = &x; /* Store the address of `x` in `ip` */
#endif       /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */

#if 1        /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
    y = *ip; /* Assign the value pointed to by `ip` to `y` */
#endif       /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */

#if 1        /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
    *ip = 0; /* Store 0 in the location pointed to by `ip` */
#endif       /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */

#if 1             /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
    ip = &arr[0]; /* Store the address of the first element of `arr` in `ip` */
#endif            /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */

    (void) y; /* Avoid unused variable warning. */
}

void snippet4(void)
{
#if 0  /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
    /* 1. The array-type expression is used with the sizeof operator */
    int a[5];
    sizeof(a); /* `a` is an array object; sizeof(a) yields 20 (not decayed) */
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */

#if 0  /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
    /* 2. The array-type expression is used with the address-of operator */
    &a; /* type: int (*)[5] — address of the entire array */
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */

#if 1 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
    /* 3. The array-type expression is used in an initializer */
    char str[] = "Hello"; /* "Hello" is a string literal; it is not decayed */
#endif                    /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */

    (void) str; /* To avoid unused variable warning */
}

void snippet5(void)
{
#if 1 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
    int a[5] = { 10, 20, 30, 40, 50 };
    int x = a[2]; /* *(a + 2) -> *( (&a[0]) + (2 * sizeof(int)) ) */
#endif            /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */

    (void) x; /* To avoid unused variable warning */
}

void snippet6(void)
{
#if 0  /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
    int a[5] = { 10, 20, 30, 40, 50 };

    a[2] == *(a + 2);  /* True */
    2 [a] == *(2 + a); /* Also true (though rarely written this way) */
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
}

void snippet7(void)
{
#if 1 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
    int a[10];
    int *pa = a; /* a ≡ &a[0] */
#endif           /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */

#if 1                 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
    a[0] = 1;         /*  a[0] ≡ *(a + 0)  */
    *(a + 9) = pa[0]; /* pa[0] ≡ *(pa + 0) */
#endif                /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */

    (void) a;  /* To avoid unused variable warning */
    (void) pa; /* To avoid unused variable warning */
}

#if 0  /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
/*1*/ int strlen(char s[]); /* actually treated as: int strlen(char *s) */
/*2*/ int strlen(char *s);
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */

#include <string.h> /* for strlen() */

void snippet8(void)
{
#if 0  /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
    char arr[] = "abc";
    strlen(arr);
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
}

void snippet9(void)
{
#if 1 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
    int a[10];
    int *p = &a[0]; /* points to first element */
    int *q = &a[2]; /* points to third element */

    int diff = q - p;          /* result: 2 elements apart */
    int p_is_before_q = p < q; /* true, because p comes before q in the array */
    int *end = &a[10];         /* valid pointer, points just past the array */
    while (p++ < end) {
        /* safe iteration from a[0] to a[9] */
    }
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */

    (void) diff;
    (void) p_is_before_q;
}

void snippet10(void)
{
#if 1 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
    char *pmessage = "now is the time"; /* a pointer */
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */

#if 1 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
    char amessage[] = "now is the time"; /* an array */
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */

    (void) pmessage;
    (void) amessage;
}

void snippet11(void)
{
#if 1 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
    int zero_initialized[5] = { 1, 2 }; /* size: 5 */
                                        /* elements: [1, 2, 0, 0, 0] */

    int fully_initialized[3] = { 1, 2, 3 }; /* size: 3 */
                                            /* elements: [1, 2, 3] */

    char inferred_size[] = "abcd"; /* size: 5 (includes null terminator '\0') */
                                   /* elements: ['a', 'b', 'c', 'd', '\0'] */
#endif                        /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
    (void) inferred_size;     /* Avoid unused variable warning. */
    (void) zero_initialized;  /* Avoid unused variable warning. */
    (void) fully_initialized; /* Avoid unused variable warning. */

#if 0  /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
    /* Error: too many initializers for array of size 3 */
    int invalid_array[3] = { 1, 2, 3, 4, 5, 6 };
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
}

void snippet12(void)
{
#if 1 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
    int val = 10;
    int a[5];
    int *p = a;
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */

#if 1           /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
    *p++ = val; /* push val onto stack */
#endif          /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */

#if 1 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
    a[0] = 5;
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */

#if 1           /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
    val = *--p; /* pop top of stack into val */
#endif          /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
}

void snippet13(void)
{
#if 1 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
    int matrix[4][3] = {
        { 10, 20, 30 },   /* Initializes matrix[0] -> row 0 */
        { 40, 50, 60 },   /* Initializes matrix[1] -> row 1 */
        { 70, 80, 90 },   /* Initializes matrix[2] -> row 2 */
        { 100, 110, 120 } /* Initializes matrix[3] -> row 3 */
    };
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */

    (void) matrix;
}

void snippet14(void)
{
#if 1 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
    int matrix[][2] = { { 10, 20 }, { 30, 40 }, { 50, 60 }, { 70, 80 } };
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */

    (void) matrix;
}

void snippet15(void)
{
#if 1 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
    int cube[2][2][3] = {
        {
            { 10, 20, 30 }, /* Initializes cube[0][0] -> depth 0, row 0 */
            { 40, 50, 60 }  /* Initializes cube[0][1] -> depth 0, row 1 */
        },
        {
            { 70, 80, 90 },   /* Initializes cube[1][0] -> depth 1, row 0 */
            { 100, 110, 120 } /* Initializes cube[1][1] -> depth 1, row 1 */
        }
    };
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */

    (void) cube;
}

void snippet16(void)
{
#if 1 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
    char *name[] = { "Illegal month", "Jan", "Feb", "Mar" };
    char aname[][15] = { "Illegal month", "Jan", "Feb", "Mar" };
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */

    (void) aname;
    (void) name;
}

#if 1                    /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
void (*func_ptr1)(void); /* declaration of a pointer to a function taking void
                          * and returning void */
void *func_ptr2(void);   /* declaration of a function taking void and returning
                          * void* (not a pointer to a function) */
#endif                   /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
