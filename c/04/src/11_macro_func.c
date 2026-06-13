#include <stdio.h>

#define ABS(x) ((x) * ((x > 0) - (x < 0)))
#define MAX(a, b) ((a > b) ? (a) : (b))
#define MIN(a, b) ((a < b) ? (a) : (b))

int main(void)
{
    int a = -100, b = 3, c = 30;

    printf("ABS(%d) is %d\n", a, ABS(a));
    printf("%d is bigger than %d\n", MAX(b, c), MIN(b, c));

    return 0;
}
