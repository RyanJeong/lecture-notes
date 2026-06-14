#include <stdio.h>

/* print Fahrenheit-Celsius table */
int main(void)
{
    int fahr;

#if 1 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
    for (fahr = 0; fahr <= 300; fahr = fahr + 20)
        printf("%3d %6.1f\n", fahr, (5.0 / 9.0) * (fahr - 32));
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */

    return 0;
}
