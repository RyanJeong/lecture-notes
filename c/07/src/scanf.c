#include <stdio.h>

int main(void)
{
    int a, b;
    /* Suppose the user inputs:  5  7 */
    printf("%d\n", scanf("%d %d", &a, &b)); /* Stores 5, 7, 9 into a, b;
                                             * >2                        */

    return 0;
}
