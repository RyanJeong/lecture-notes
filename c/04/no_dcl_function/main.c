#include <stdio.h>

int main(void)
{
    /* Missing function declaration; both return types are assumed to be int */
    printf("%d %f", foo(), bar()); /* NB: bar() may print garbage! */

    return 0;
}
