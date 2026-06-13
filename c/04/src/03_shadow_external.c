#include <stdio.h>

int data = 12;

int main(void)
{
    int data = 34; /* local variable(34) shadows external variable(12) */

    printf("%d\n", data); /* prints 34, not 12 */

    return 0;
}
