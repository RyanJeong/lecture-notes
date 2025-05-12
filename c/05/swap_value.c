#include <stdio.h>

#define DPRINT(var) printf(#var ": %d\n", (var))

void swap(int x, int y)
{
    int temp = x;
    x = y;
    y = temp;
}

int main(void)
{
    int a = 10, b = -200;

    swap(a, b);
    DPRINT(a);
    DPRINT(b);

    return 0;
}
