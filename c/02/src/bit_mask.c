#include <stdio.h>

int main(void)
{
    unsigned char x = 248; /* x = 248, 1111 1000 */

    /* mask operation, NB: 077 is an integer constant */
    printf("x & 077 = %d\n", x & 077); /* x & 077 = 56   (0011 1000) */

    /* set operation, NB: 07 is an integer constant */
    printf("x | 07 = %d\n", x | 07); /* x | 07 = 255   (1111 1111) */

    /* advanced mask operation
     *
     * 0300 assumes that x is an 8-bit value,
     * but ~077 works regardless of the word size.
     * => ~077 is more portable and safer than 0300
     */
    printf("x & ~077 = %d\n", x & ~077); /* x & ~077 = 192 (1100 0000) */

    return 0;
}
