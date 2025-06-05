#include <stdio.h>

int main(void)
{
    int a, b, ret;
    /* Suppose the user inputs: 10  30  20 */
    while ((ret = scanf("%d %d", &a, &b)) == 2)
        printf("%d + %d = %d (%d)\n", a, b, a + b, ret); /* >10 + 30 = 40 (2) */
    printf("ret: %d\n", ret);                            /* >ret: 1 */
    return 0;
}
