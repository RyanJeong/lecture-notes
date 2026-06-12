#include <stdio.h>

int main(void)
{
    goto jump_before_return_stmt;
    printf("Hello, world!\n"); /* Not executed because of the goto statement */

jump_before_return_stmt:
    return 0; /* identifier : statement (labeled-statement) */
}
