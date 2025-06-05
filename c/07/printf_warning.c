#include <stdio.h>

int main(void)
{
    char *s = "%d\n";

    printf(s);       /* FAILS if `s` contains `%`, >????? */
    printf("%s", s); /* SAFE                       >%d    */

    return 0;
}
