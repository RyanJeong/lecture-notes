#include <stdio.h>

int main(void)
{
    goto jump_before_return_stmt;
    printf("Hello, world!\n");

jump_before_return_stmt:
    printf("Bye\n"); /* identifier : statement (labeled-statement) */

    return 0;
}
