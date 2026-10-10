#include <limits.h> /* a header file for limits of integral types */
#include <stdio.h>

int main(void)
{
    printf("short size\t\t: %20lu\n", (unsigned long) sizeof(short));
    printf("Minimum signed short\t: %20d\n", SHRT_MIN);
    printf("Maximum signed short\t: %20d\n", SHRT_MAX);
    printf("Maximum unsigned short\t: %20u\n", (unsigned) USHRT_MAX);

    return 0;
}
