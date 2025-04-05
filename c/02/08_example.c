#include <stdio.h>
#include <stdlib.h> /* to use atoi() */

int main(void)
{
    char digit[100] = "12345";

    printf("%d", atoi(digit)); /* 12345 */

    return 0;
}
