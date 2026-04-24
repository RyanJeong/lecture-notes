#include <stdio.h>

#define dprint(x) printf("Integer variable " #x " is %d\n", (x))
#define fprint(x) printf("Floating point variable " #x " is %f\n", (x))

int main(void)
{
    int i = 100;
    double pi = 3.14;

    dprint(i);  /* printf("Integer variable " "i" " is %d\n", (i)); */
    fprint(pi); /* printf("Floating point variable " "pi" " is %f\n", (pi)) */

    return 0;
}
