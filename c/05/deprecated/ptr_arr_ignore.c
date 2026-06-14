void foo(void)
{
#if 1 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
    /* 1. The array-type expression is used with the sizeof operator */
    int a[5];
    sizeof(a); /* `a` is an array object; sizeof(a) yields 20 (not decayed) */
#endif         /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */

#if 1 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
    /* 2. The array-type expression is used with the address-of operator */
    &a; /* type: int (*)[5] — address of the entire array */
#endif  /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */

#if 1 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
    /* 3. The array-type expression is used in an initializer */
    char str[] = "Hello"; /* "Hello" is a string literal; it is not decayed */
#endif                    /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
}

void bar(void)
{
#if 1 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
    int a[5] = { 10, 20, 30, 40, 50 };
    int x = a[2]; /* *(a + 2) -> *( (&a[0]) + (2 * sizeof(int)) ) */
#endif            /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
}

void qux(void)
{
#if 0  /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
    int a[5] = { 10, 20, 30, 40, 50 };

    a[2] == *(a + 2); /* True */
    2[a] == *(2 + a); /* Also true (though rarely written this way) */
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
}

void quz(void)
{
#if 1 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
    int a[10];
    int *pa = a; /* a ≡ &a[0] */
#endif           /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */

#if 1                 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
    a[0] = 1;         /*  a[0] ≡ *(a + 0)  */
    *(a + 9) = pa[0]; /* pa[0] ≡ *(pa + 0) */
#endif                /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
}

#if 1                       /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
/*1*/ int strlen(char s[]); /* actually treated as: int strlen(char *s) */
/*2*/ int strlen(char *s);
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */

#include <string.h> /* for strlen() */

void foobar(void)
{
#if 1 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
    char arr[] = "abc";
    strlen(arr);
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
}