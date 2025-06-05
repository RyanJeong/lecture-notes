#include <stdio.h>

int main(void)
{
    int n;
    char c;

    /* Suppose the user inputs: 1  d */
    scanf("%d %c", &n, &c);
    printf("%d %c\n", n, c); /* >1 c */

    return 0;
}
