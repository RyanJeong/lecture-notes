#include <stdio.h>

int main(void)
{
    int num = 50000; /* 50'000 (5 * 10^4) */

    printf("%d\n", num * num); /* Maybe 2'500'000'000 (2.5 * 10 ^ 9)? */

    /* But the result is -1794967296 because of overflow (undefined behavior) */
    return 0;
}
