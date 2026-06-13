#include <stdio.h>
#include <stdlib.h> /* for system() */

int main(void)
{
    printf("Return %d\n", system("date"));

    return 0;
}
