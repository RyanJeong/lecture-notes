#include <stdio.h>

int main(void)
{
#if 1 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
    struct {
        unsigned int a : 4;
        int b : 4;
    } bits;

    bits.a = bits.b = 0x0F;            /* 1111 */
    printf("%d %d\n", bits.a, bits.b); /* 15 -1 */
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */

    return 0;
}
