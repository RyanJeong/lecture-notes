#include <stdio.h>

int main(void)
{
    double d1 = 0.125;              /* 1 / 8     */
    double d2 = 0.0000152587890625; /* 1 / 65536 */
    double d3 = 1234.56;

    printf("%f\n", d1);   /* >0.125000                                        */
    printf("%e\n", d1);   /* >1.250000e-01                                    */
    printf("%g\n", d1);   /* >0.125                                           */
    printf("%f\n", d2);   /* >0.000015                                        */
    printf("%E\n", d2);   /* >1.525879E-05                                    */
    printf("%G\n", d2);   /* >1.52588E-05                                     */
    printf("%e\n", d3);   /* >1.234560e+03                                    */
    printf("%.3g\n", d3); /* >1.23e+03                                        */
    printf("%.4g\n", d3); /* >1235                                            */

    return 0;
}
