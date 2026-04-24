#include <stdio.h>

int foo(void); /* Declaration of foo() is provided before use */

int main(void) /* `foo` is in scope, but `g` is not */
{
    printf("%d", foo());

    return 0;
}

int g = 42; /* Definition of global variable `g` */

int foo(void) /* `foo` and `g` are in scope here */
{
    return g;
}
