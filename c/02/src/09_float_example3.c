#include <stdio.h>

int main(void)
{
    float f7;

    f7 = 27.1; /* 271 / 10 is not representable as 2^n -> repeating decimal */
    printf("27.1 (may be simply 271/10) cannot be expressed as 2^n.\n"
           "With precision 6: %.6f, with precision 8: %.8f\n",
           f7, f7);

    return 0;
}
