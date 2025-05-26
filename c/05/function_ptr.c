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
     * Both styles below are valid in ANSI C:
     *   func_ptr();      -> implicitly dereferenced (decay to (*func_ptr)())
     *   (*func_ptr)();   -> explicitly dereferenced
     * This executes the code located in the .text section where `msg` is
     * stored.
     */
    func_ptr();

    return 0;
}
