#include <stdio.h>

int main(void)
{
    int a[3] = { 1, 5, 9 };
    int(*p)[2] = &a;
    int **pp = &a;

    printf("%d %d %d %d\n", a[-1], a[0], a[1], a[2]);
    printf("%d %d %d %d\n", -1 [a], 0 [a], 1 [a], 2 [a]);
    printf("%d %d %d\n", (*p)[0], (*p)[1], (*p)[2]);
    printf("%d %d %d\n", (*pp)[0], (*pp)[1], (*pp)[2]);

    return 0;
}
