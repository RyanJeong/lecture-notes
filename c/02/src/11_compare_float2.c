#include <stdio.h>

#define ABS(x) ((x) * (((x) > 0) - ((x) < 0)))

int main(void)
{
    float a = 0.3f + 0.4f;
    float b = 0.7f;

    if (ABS(a - b) < 1e-5f)
        printf("ABS(a - b) < 1e-5 (same)\n");
    else
        printf("ABS(a - b) >= 1e-5 (different)\n");

    return 0;
}
