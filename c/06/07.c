#include <stdio.h>

int main(void)
{
    union {
        int i;   /* 4 bytes */
        short s; /* 2 bytes */
        char c;  /* 1 byte */
    } u;
    u.i = 0x12345678;
    printf("&u.s: %p, u.s: %x\n", &u.s, u.s); /* &u.s: 0x08AF53DC, u.s: 5678 */

    return 0;
}
