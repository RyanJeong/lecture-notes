#include <stdio.h>

int main(void)
{
    unsigned char x = 248; /* x = 248, 1111 1000 */

    /* mask operation */
    printf("x & 077 = %d\n", x & 077); /* The result is 0011 1000 */

    /* set operation */
    printf("x | 07 = %d\n", x | 07); /* The result is 1111 1111 */

    /* advanced mask operation
     *
     * 0x300 assumes that x is an 8-bit value,
     * but ~077 works regardless of the word size.
     * => ~077 is more portable and safer than 0x300
     */
    printf("x & ~077 = %d\n", x & ~077); /* The result is 1100 0000 */

    return 0;
}
