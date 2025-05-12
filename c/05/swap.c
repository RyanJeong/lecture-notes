#include <stdio.h>

#define DPRINT(var) printf(#var ": %d\n", (var))

void swap(int *px, int *py)
{
    int temp = *px;
    *px = *py;
    *py = temp;
}

int main(void)
{
    int a = 10, b = -200;

    swap(&a, &b);
    DPRINT(a);
    DPRINT(b);

    return 0;
}
