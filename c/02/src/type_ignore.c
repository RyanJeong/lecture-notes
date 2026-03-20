#include <stdio.h>

#if 1 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
/* Case #1 */
char a = 127;
char b = 127;
short c = a + b; /* 1. a + b -> (int) a + (int) b = 254 (to prevent overflow) */
                 /* 2. short c = (short) 254 */

/* Case #2 (NB: assume that both short and int are 2-byte data types) */
unsigned short x = 65535; /* USHRT_MAX */
int i = x; /* An int can't represent `x`; it's converted to an unsigned int */
#endif     /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */

int main(void)
{
#if 1 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
    float f = 3.14;
    /* Although `f` is a float, when passed to printf (a variadic function),
       it is promoted to double. So we must use %f, not %lf. */
    printf("float promoted to double: %f\n", f);

    /* double type variables work the same way here */
    double d = 2.718;
    printf("double remains double: %f\n", d);
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */

#if 1               /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
    int a = 'A';    /* Converting a narrower operand into a wider one is ok */
    char c = 12345; /* Convertint a wider operand into a narrower one like this
                       could cause information to be lost (Warning) */
#endif              /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */

#if 1 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
    float pi = (float) 3.14;
    int area =
        (int) (11 * 11 * pi); /* decimal dropped, but warning is suppressed */
#endif                        /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */

#if 1 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
    int i = 256;
    char c = 'A'; /* ASCII 'A' = 65 */
    float f = 3.14;

    c = i; /* c = 0 (overflow) */
    i = c; /* i = 0 */
    i = f; /* i = 3 (decimal dropped) */
    f = i; /* f = 3.0 */
#endif     /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
    return 0;
}
