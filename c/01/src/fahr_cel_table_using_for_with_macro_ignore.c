#include <stdio.h>

#define LOWER 0   /* lower limit of temperature table */
#define UPPER 300 /* upper limit */
#define STEP 20   /* step size */

#if 0            /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
#define STEP 20; /* step size */
#endif           /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */

/* print Fahrenheit-Celsius table */
int main(void)
{
    int fahr;

    for (fahr = LOWER; fahr <= UPPER; fahr = fahr + STEP)
        printf("%3d %6.1f\n", fahr, (5.0 / 9.0) * (fahr - 32));

#if 0  /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
    for (i = 0; i < STEP; ++i) {
        /* ... */
    }
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */

#if 0  /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
    for (i = 0; i < 20;; ++i) { /* Syntax error */
        /* ... */
    }
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */

    return 0;
}
