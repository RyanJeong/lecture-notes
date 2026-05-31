#include <stdio.h>

int main(void)
{
#if 1 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
    int n;
    char c;

    /* Suppose the user inputs: 1 d */
    /* The space between 1 and d remains unread after the first scanf */
    scanf("%d", &n);         /* consume '1' */
    getchar();               /* consume ' ' */
    scanf("%c", &c);         /* consume 'd' */
    printf("%d %c\n", n, c); /* >1 d */
#endif                       /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */

    return 0;
}
