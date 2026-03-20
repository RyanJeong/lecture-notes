#include <limits.h> /* a header file for limits of integral types */
#include <stdio.h>

int main(void)
{
    printf("int size\t\t: %20lu\n", sizeof(int));
    printf("Minimum signed int\t: %20d\n", INT_MIN);
    printf("Maximum signed int\t: %20d\n", INT_MAX);
    printf("Maximum unsigned int\t: %20u\n", UINT_MAX);

    return 0;
}
