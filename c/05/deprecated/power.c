#include <stdio.h>

int power(int base, int n)
{
    int i, p = 1;

    for (i = 1; i <= n; ++i)
        p *= base;

    return p;
}

int main(void)
{
    int base = 2, n = 3;

    printf("%d ^ %d = %d\n", base, n, power(base, n));

    return 0;
}
