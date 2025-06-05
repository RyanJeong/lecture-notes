#include <stdio.h>

int main(void)
{
    int i, o, h;
    unsigned u;

    /* Suppose the user inputs: 100 077 0xFF */
    scanf("%d %o %x", &i, &o, &h);
    printf("%d %d %d\n", i, o, h); /* >100 63 255 */

    /* Suppose the user inputs: 100 077 0xFF */
    scanf("%i %i %i", &i, &o, &h);
    printf("%d %d %d\n", i, o, h); /* >100 63 255 */

    /* Suppose the user inputs: 2147483648 */
    scanf("%u", &u);
    printf("%u\n", u); /* >2147483648 */

    /* Suppose the user inputs: %4 */
    scanf("%%%d", &i);
    printf("%d\n", i); /* >4 */

    return 0;
}
