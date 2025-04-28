#include <stdio.h>

/* NB: If you omit foo() declaration, compiles in ANSI C, but assumes int foo(),
 * which is fragile and deprecated */
int foo(void); /* Declaration of foo() is provided before use */

int main(void)
{
    /* printf("%d", g); -> ERROR: `g` is not in scope at this point `g` is
     * declared after this function, so it's not visible here */

    printf("%d", foo()); /* -> OK: foo() returns the value of `g` */

    return 0;
}

int g = 42; /* Definition of global variable `g` */

/* foo() can access `g` because `g` is declared before foo()'s body */
int foo(void)
{
    return g; /* -> OK: `g` is in scope here */
}
