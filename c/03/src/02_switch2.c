#include <stdio.h>

int main(void)
{
    switch (1) {
    case 1:
        printf("One\n");
        break; /* prevent fall-through */
    case 2:
        printf("Two\n");
        break; /* prevent fall-through */
    default:
        printf("Other\n");
    } /* Output: One\n (because of break statements preventing fall-through) */

    return 0;
}
