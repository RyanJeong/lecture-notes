union {
    char c;  /* 1 byte */
    short s; /* 2 bytes */
    int i;   /* 4 bytes */
} u;

int main(void)
{
    u.i = 0x12345678;

    &u.s;  /* 0x08AF53DC */
    u.s;   /* 0x5678 */

    return 0;
}
