#include <stdio.h>
#include <stdlib.h> /* for rand(), srand() */
#include <time.h>   /* for time() */

#define frand() ((double) rand() / (RAND_MAX + 1.0)) /* [0, 1) */

int main(void)
{
    int i;

    /* You can get different random numbers each time you run the program */
    srand((unsigned) time(NULL)); /* seed random number generator */

    for (i = 0; i < 10; ++i)
        printf("%d\n", rand()); /* print random integer */
    for (i = 0; i < 10; ++i)
        printf("%f\n", frand()); /* print random floating-point number */

    return 0;
}
