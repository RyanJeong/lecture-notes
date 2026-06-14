#include <limits.h> /* a header file for limits of integral types */
#include <stdio.h>

int main(void)
{
    printf("long size\t\t: %20lu\n", sizeof(long));
#if 1 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
    printf("Minimum signed long\t: %20ld\n", LONG_MIN);
    printf("Maximum signed long\t: %20ld\n", LONG_MAX);
    printf("Maximum unsigned long\t: %20lu\n", ULONG_MAX);
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */

    return 0;
}
