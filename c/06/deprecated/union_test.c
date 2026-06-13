#include <stdio.h>

int main(void)
{
    union {
        int i;   /* 4 bytes */
        short s; /* 2 bytes */
        char c;  /* 1 byte */
    } u;
    u.i = 0x12345678;

    printf("&u.i: %p, u.i: %x\n", (void *) &u.i, u.i);
    printf("&u.s: %p, u.s: %x\n", (void *) &u.s, u.s);
    printf("&u.c: %p, u.c: %x\n", (void *) &u.c, u.c);

    return 0;
}
