#include <stdio.h>

double square(int x) /* callee */
{
    return x * x; /* `x * x` is int, but the function's return type is double;
                     implicit conversion occurs here. */
}

int main(void)
{
    int value = 3;

    /* `square(value)` is a caller. It returns a double; %f is needed */
    printf("Square of %d is %.2f\n", value, square(value));

    return 0;
}
