#include <stdio.h>

int main(void)
{
    double d3 = 1234.56;

    // %e: Always use exponential format
    // Default precision = 6 (6 digits after the decimal point)
    // Output: 1.234560e+03
    printf("%e\n", d3);

    // %.3g: Use either %e or %f depending on exponent and precision
    // Rule: if (exponent < -4 || exponent >= precision) → use %e
    // d3 = 1234.56 → exponent = 3, precision = 3 → 3 >= 3 → use %e
    // Keep 3 significant digits → 1.23e+03
    printf("%.3g\n", d3);

    // %.4g: Same rule applies
    // d3 = 1234.56 → exponent = 3, precision = 4 → 3 < 4 → use %f
    // Keep 4 significant digits → 1234.56 rounds to 1235
    // Trailing decimal point and zeroes are removed
    // Output: 1235
    printf("%.4g\n", d3);

    printf("%8.5f\n", 1.25);       /*  1.25000                                */
    printf("%-8.5f\n", 1.25);      /* 1.25000                                 */
    printf("%9.3f\n", 3.141592);   /*     3.142                               */
    printf("%-9.3f\n", 3.141592);  /* 3.142                                   */
    printf("%9f\n", 3.141592);     /*  3.141592                               */
    printf("%-9f\n", 3.141592);    /* 3.141592                                */
    printf("%10.3e\n", 3.141592);  /*  3.142e+00                              */
    printf("%-10.3E\n", 3.141592); /* 3.142E+00                               */

    return 0;
}
