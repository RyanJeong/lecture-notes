#include <stdio.h>

struct iarray {
    int arr[256];
};

void value(struct iarray arr)
{
    printf("[value] size: %ld\n", sizeof(arr)); /* [value] size: 1024 */
}

void ptr(struct iarray *parr)
{
    printf("[ptr] size: %ld\n", sizeof(parr)); /* [ptr] size: 8 (or 4) */
}
