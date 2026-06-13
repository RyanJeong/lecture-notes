#include <stdio.h>

int main(void)
{
#if 1 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
    short s;
    int i;
    long l;
    float f;
    double d;
    long double ld;

    /* integer */
    scanf("%hd %d %ld", &s, &i, &l);
    /* floating-point */
    scanf("%f %lf %Lf", &f, &d, &ld);
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */

    return 0;
}
