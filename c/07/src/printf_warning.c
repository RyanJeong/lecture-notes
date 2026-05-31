#include <stdio.h>

int main(void)
{
#if 1 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
    char *s = "%d\n";

    printf(s);       /* FAILS if `s` contains `%`, >????? */
    printf("%s", s); /* SAFE                       >%d    */
#endif               /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */

    return 0;
}
