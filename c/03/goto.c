#include <stdio.h>

int main(void)
{
    goto jump_before_return_stmt;
    printf("Hello, world!\n");

jump_before_return_stmt:
    printf("Bye\n"); /* labeled-statement: identifier : statement */

    return 0;
}
