#include <stdio.h>

int main(void)
{
    int d, m, y;

    /* Suppose the user inputs: 05/15/21 */
    scanf("%d/%d/%d", &m, &d, &y);
    printf("m: %d, d: %d, y: %d\n", m, d, y); /* >m: 5, d: 15, y: 21 */

    return 0;
}
