#include <stdio.h>

int main(void)
{
    int day, month, year;

    /* Suppose the user inputs: 05/15/21 */
    scanf("%d/%d/%d", &month, &day, &year);
    printf("month: %d, day: %d, year: %d\n", month, day,
           year); /* >month: 5, day: 15, year: 21 */

    return 0;
}
