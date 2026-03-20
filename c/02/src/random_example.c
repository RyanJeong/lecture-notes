#include <stdio.h>
#include <stdlib.h> /* for rand(), srand() */

int main(void)
{
    srand(123);
    printf("1st trial: %d\n", rand()); /* 1st trial: 128959393  */
    printf("2nd trial: %d\n", rand()); /* 2nd trial: 1692901013 */

    return 0;
}
