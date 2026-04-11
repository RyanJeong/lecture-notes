#include <stdio.h>

int main(void)
{
    switch (1) {
        /* Note that the execution jumps to the matching case label and
         * continues until a break statement or the end of the switch */
    case 1:
        printf("One\n");
    case 2:
        printf("Two\n");
    default:
        printf("Other\n");
    } /* Output: One\nTwo\nOther\n (because of fall-through behavior) */

    return 0;
}
