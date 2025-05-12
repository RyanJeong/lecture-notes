#include <stdio.h>

/* This function is stored in the .text (code) section of memory. */
void msg(void)
{
    printf("Hello, world!\n");
}

int main(void)
{
    /*
     * Declaration of a function pointer that takes no arguments and returns
     * void. It is initialized to point to the `msg` function.
     */
    void (*func_ptr)(void) = msg;

    /*
     * Call the function through the function pointer.
     * This executes the code located in the .text section where `msg` is
     * stored.
     */
    func_ptr();

    return 0;
}
