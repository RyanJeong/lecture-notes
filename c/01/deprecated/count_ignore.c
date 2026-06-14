#include <stdio.h>

/* count characters in input; 1st version */
int main(void)
{
    long nc;

    nc = 0;
    while (getchar() != EOF)
        ++nc;
    printf("%ld\n", nc);

#if 1 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
    int i = 3;
    ++i; /* now i is 4 */
    float f = 3.5;
    ++f; /* now f is 4.5 */
#endif   /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */

    return 0;
}
