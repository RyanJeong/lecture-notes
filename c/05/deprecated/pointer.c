void foo(void)
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

void bar(void)
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

void qux(void)
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