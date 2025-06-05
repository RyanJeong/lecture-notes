#include <stdio.h>

int main(void)
{
    int n;
    char c;

    /* Suppose the user inputs: 1  d */
    scanf("%d", &n);
    scanf("%c", &c);
    printf("%d %c\n", n, c); /* >1   */

    return 0;
}
