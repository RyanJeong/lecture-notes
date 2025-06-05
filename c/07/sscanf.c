#include <stdio.h>

int main(void)
{
    char s[] = "1 12.3 12.3 12.3 sscanf";
    int i;
    float f;
    double d;
    long double ld;
    char str[10];

    sscanf(s, "%d %f %lf %Lf %s", &i, &f, &d, &ld, str);
    printf("%d\n", i);               /* >1                             */
    printf("%f %f %Lf\n", f, d, ld); /* >12.300000 12.300000 12.300000 */
    printf("%s\n", str);             /* >sscanf                        */

    return 0;
}
