#include <stdio.h>

/* print Fahrenheit-Celsius table
   for fahr = 0, 20, ..., 300 */
int main(void)
{
    int fahr, celsius;
    int lower, upper, step;

    lower = 0;   /* lower limit of temperature table */
    upper = 300; /* upper limit */
    step = 20;   /* step size */
    fahr = lower;

#if 1          /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
    100 = 200; /* This is an impossible assignment because the left-hand side is
                  a constant literal. */
#endif         /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */

#if 1 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
    /*1*/ celsius = 5 * (fahr - 32) / 9;
    /*2*/ celsius = 5 / 9 * (fahr - 32); /* Isn't this more like the formula? */
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */

#if 1 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
    printf("Hello, World\n");
    printf("%d\t%d\n", fahr, celsius);
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */

#if 1 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
    printf("%d + %d = %d\n", 1, 2, 1 + 2);
    printf("PI: %f\n", 3.141592);
    printf("PI: %d\n", 3.141592); /* prints an indeterminate integer value
                                     (implementation-defined), not 3 */
#endif                            /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */

#if 0  /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
    int lower, upper, step; lower = 0; upper = 300; step = 20;
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */

#if 0  /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
    /*1*/ celsius = 5*(fahr-32)/9;
    /*2*/ celsius = 5 * (fahr - 32) / 9;
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */

#if 0  /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
    int i = 0;

    /* Style #1 */
    while (i < 10) { ++i; }

    /* Style #2 */
    while (i >= 0) {
        --i;
    }
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */

    while (fahr <= upper) {
        celsius = 5 * (fahr - 32) / 9;
        printf("%d\t%d\n", fahr, celsius);
        fahr = fahr + step;
    }

    return 0;
}
