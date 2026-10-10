#include <limits.h> /* a header file for limits of integral types */
#include <stdio.h>

int main(void)
{
    printf("char size\t\t: %20lu\n", (unsigned long) sizeof(char));
    printf("Minimum signed char\t: %20d\n", SCHAR_MIN);
    printf("Maximum signed char\t: %20d\n", SCHAR_MAX);
    printf("Maximum unsigned char\t: %20u\n", (unsigned) UCHAR_MAX);

    return 0;
}
