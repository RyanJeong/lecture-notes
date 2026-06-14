#include <stdio.h>

int main(void)
{
#if 1                         /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
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

    printf("100%%\n"); /* >100% */
#endif                 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */

    return 0;
}
