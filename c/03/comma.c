#include <stdio.h>

int main(void)
{
    int x, y, z;

    z = (x = 1, y = 2, x + y);
    printf("%d\n", z); /* 3 */

    return 0;
}
