#include <stdio.h>

int main(void)
{
    int x = 0;

loop:
    ++x;
    goto loop_test; /* Jump to the label defined later in the function */
    printf("This line is never reached.\n");

loop_test:
    if (x < 5)
        goto loop; /* Loop again if `x` is less than 5 */
    printf("Loop finished with x = %d\n", x);

    return 0;
}
