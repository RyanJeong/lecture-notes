#include <stdio.h>

int main(void)
{
    int n;
    char c;

    /* Suppose the user inputs: 1  d */
    scanf("%d", &n);
    /* Call getchar() as many times as you need to remove whitespace characters
     */
    getchar();
    getchar();
    scanf("%c", &c);
    printf("%d %c\n", n, c); /* >1 d */

    return 0;
}
