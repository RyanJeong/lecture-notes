int sum(int a, int b); /* `a` and `b` have prototype scope */

int sum(int x, int y) /* Different names can be used in definition */
{
    return x + y; /* `a` and `b` are block-scope variables inside the function
                     body */
}
