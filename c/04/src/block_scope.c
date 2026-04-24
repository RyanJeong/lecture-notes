#include <stdio.h>

int main(void)
{
    int value = 10; /* outer block, `value` is 10 */
    {
        int value = 99; /* inner block(shadows outer `value`), `value` is 99 */
        printf("Inner block: %d\n", value); /* prints 99 */
    }
    printf("Outer block: %d\n", value); /* prints 10 */

    return 0;
}
