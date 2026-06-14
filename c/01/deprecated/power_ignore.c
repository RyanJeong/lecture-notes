#include <stdio.h>

int power(int m, int n);

int main(void)
{
    int i;
    /* ... */
}

int power(int base, int n)
{
    int i, p;
    /* ... */
}

/* test power function */
int main(void)
{
    int i;

    for (i = 0; i < 10; ++i)
        printf("%d %d %d\n", i, power(2, i), power(-3, i));

#if 1 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
    printf("%d %d %d\n", i, power(2, i), power(-3, i));
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */

#if 1            /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
    power(4, i); /* return value (int) will be ignored */
#endif           /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */

    return 0;
}

int power(int base, int n)
{
    int i, p;

    p = 1;
    for (i = 1; i <= n; ++i)
        p = p * base;

    return p;
}
