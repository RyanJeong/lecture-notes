#include <stdio.h>

/* print Fahrenheit-Celsius table
   for fahr = 0, 20, ..., 300 */
int main(void)
{
#if 1 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
    int fahr, celsius;
    int lower, upper, step;
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */

#if 1            /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
    lower = 0;   /* lower limit of temperature table */
    upper = 300; /* upper limit */
    step = 20;   /* step size */
    fahr = lower;
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
#if 1  /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
    while (fahr <= upper) {
#if 1 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
        celsius = 5 * (fahr - 32) / 9;
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
        printf("%d\t%d\n", fahr, celsius);
        fahr = fahr + step;
    }
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */

    return 0;
}
