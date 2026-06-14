#include <stdio.h>

int main(void)
{
    int n = 24, i;

    for (i = 1; i <= n; ++i) {
        /* Original if-else statement:
        if (!(i % 10) || i == n)
            printf("%2d\n", i);
        else
            printf("%2d ", i);
            */
        printf("%2d%c", i, (!(i % 10) || i == n) ? '\n' : ' ');
    }

    return 0;
}
