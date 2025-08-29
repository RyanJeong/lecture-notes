#include <stdio.h>
#include <stdlib.h> /* for atoi() */

int main(void)
{
    char digit1[20] = "  +23dummy";
    char digit2[20] = "  -13  dummy";

    printf("%d\n", atoi(digit1) + atoi(digit2));

    return 0;
}
