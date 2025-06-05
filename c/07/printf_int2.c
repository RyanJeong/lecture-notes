#include <stdio.h>

int main(void)
{
    int a[] = { 15, 077, 0xFF, 'A', -1 };

    printf("%3d %3o %3x %3X\n", a[0], a[0], a[0], a[0]); /* > 15  17   f   F  */
    printf("%3d %3o %3x %3X\n", a[1], a[1], a[1], a[1]); /* > 63  77  3f  3F  */
    printf("%3d %3o %3x %3X\n", a[2], a[2], a[2], a[2]); /* >255 377  ff  FF  */

    printf("%p %p\n", a, a + 1);     /* >0x08AF53D0 0x08AF53D4                */
    printf("%p %p\n", &a[0], &a[1]); /* >0x08AF53D0 0x08AF53D4                */
    printf("%c\n", a[3]);            /* >A                                    */
    printf("%u\n", a[4]);            /* >4294967295                           */
    printf("%ld\n", (long) 1 << 32); /* >4294967296                           */
    printf("%d\n", (long) 1 << 32);  /* >0                                    */
    printf("%hd\n", 1 << 16);        /* >0                                    */
    printf("%d\n", 1 << 16);         /* >65536                                */

    return 0;
}
