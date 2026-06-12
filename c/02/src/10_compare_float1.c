#include <stdio.h>

int main(void)
{
    float a = 0.3f + 0.4f;
    float b = 0.7f;

    if (a == b)
        printf("a == b (same)\n");
    else
        printf("a != b (different)\n");

    return 0;
}
