#include <stdio.h>

int main(void)
{
#if 1 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
    union {
        int i;   /* 4 bytes */
        short s; /* 2 bytes */
        char c;  /* 1 byte */
    } u;

    u.i = 0x12345678;
    /* &u.i: 0x08AF53DC, u.i: 12345678 */
    /* &u.s: 0x08AF53DC, u.s: 5678 */
    /* &u.c: 0x08AF53DC, u.c: 78 */
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */

    printf("&u.s: %p\n", (void *) &u.s); /* &u.s: 0x08AF53DC */
    printf("u.s: %x\n", u.s);            /* u.s: 5678 */

    return 0;
}
