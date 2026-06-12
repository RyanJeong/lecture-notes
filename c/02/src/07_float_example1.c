#include <stdio.h>

int main(void)
{
    float f1, f2;

    f1 = 9999876.0;  /* 7 digits, value can be represented accurately */
    f2 = 99998765.0; /* 8 digits, value may not be represented accurately */
    printf("A single-precision only has about 7 decimal digits of precision.\n"
           "f1: %10.1f, f2: %10.1f\n",
           f1, f2);

    return 0;
}
