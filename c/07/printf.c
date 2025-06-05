#include <stdio.h>

int main(void)
{
    char *s = "Hello, world"; /* The length of the string is 12 */

    printf(":%s:\n", s);       /* >:Hello, world:                             */
    printf(":%10s:\n", s);     /* >:Hello, world:                             */
    printf(":%.10s:\n", s);    /* >:Hello, wor:                               */
    printf(":%-10s:\n", s);    /* >:Hello, world:                             */
    printf(":%15s:\n", s);     /* >:   Hello, world:                          */
    printf(":%.15s:\n", s);    /* >:Hello, world:                             */
    printf(":%-15s:\n", s);    /* >:Hello, world   :                          */
    printf(":%15.10s:\n", s);  /* >:     Hello, wor:                          */
    printf(":%-15.10s:\n", s); /* >:Hello, wor     :                          */

    printf("100%%\n"); /* >100%                                       */

    return 0;
}
