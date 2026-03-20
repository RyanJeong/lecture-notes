#include <stdio.h>

int main(void)
{
    unsigned char a = 5; /* a = 5, 0000 0101 */
    unsigned char b = 9; /* b = 9, 0000 1001 */

    printf("a & b = %d\n", a & b);   /* a & b = 1   (0000 0001)               */
    printf("a | b = %d\n", a | b);   /* a | b = 13  (0000 1101)               */
    printf("a ^ b = %d\n", a ^ b);   /* a ^ b = 12  (0000 1100)               */
    printf("~a = %d\n", a = ~a);     /* ~a = 250    (1111 1010), Non-negative */
    printf("b << 1 = %d\n", b << 1); /* b << 1 = 18 (0001 0010)               */
    printf("b >> 1 = %d\n", b >> 1); /* b >> 1 = 4  (0000 0100)               */

    return 0;
}
