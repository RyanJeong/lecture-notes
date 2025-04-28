#include <stdio.h>

int main(void)
{
    int value = 10; /* outer block: value = 10 */

    {
        int value = 99; /* inner block: new variable shadows outer `value` */
        printf("Inner block: %d\n", value); /* prints 99 */
    }

    printf("Outer block: %d\n", value); /* prints 10 */

    return 0;
}
