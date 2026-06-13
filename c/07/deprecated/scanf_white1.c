#include <stdio.h>

int main(void)
{
#if 1 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
    int n;
    char c;

    /* Suppose the user inputs: 1 d */
    /* The space between 1 and d is consumed by the space in the
     * format string "%d %c" */
    scanf("%d %c", &n, &c);  /* %d: consume '1', %c: consume 'd' */
    printf("%d %c\n", n, c); /* >1 d */
#endif                       /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */

    return 0;
}
