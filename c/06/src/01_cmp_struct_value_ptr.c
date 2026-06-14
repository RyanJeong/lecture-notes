#include <stdio.h>

struct iarray {
    int arr[256];
};

struct complex {
    double re; /* real part */
    double im; /* imaginary part */
};

void cmp_iarray(struct iarray arr, struct iarray *parr)
{
    printf("[value] size: %d\n", (int) sizeof(arr)); /* [value] size: 1024 */
    printf("[ptr] size: %d\n", (int) sizeof(parr));  /* [ptr] size: 8 (or 4) */
}

void cmp_complex(struct complex c, struct complex *pc)
{
    printf("[value] size: %d\n", (int) sizeof(c)); /* [value] size: 16 */
    printf("[ptr] size: %d\n", (int) sizeof(pc));  /* [ptr] size: 8 (or 4) */
}
