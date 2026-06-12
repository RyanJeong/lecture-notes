#include <stdio.h>

int main(void)
{
    int x, y, z, w;
#if 1 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
    x++ *y *z + w++;

/*
 - 1. [1] '++' has the highest precedence
 - 2. [2] '++' is right-to-left associative:
 -     => x++ * y * z + (w++)
 -     => (x++) * y * z + (w++)
 - 3. [1] '*' has the next highest precedence
 - 4. [2] '*' is left-to-right associative:
 -     => ((x++) * y) * z + (w++)
 -     => (((x++) * y) * z) + (w++)
 - 5. [1] '+' has the next precedence
 - 6. [2] '+' is left-to-right associative:
 -     => ((((x++) * y) * z) + (w++)) */
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */

#if 1 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
    int i = 2;
    ++i; /* side effect: i + 1 */
#endif   /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */

    int f(), g();
#if 1 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
      /* Case 1: If both functions f() and g() have side effects on global
       * variables, the result of f() + g() may vary depending on which function
       * is evaluated first.
       *   e.g., extern int a = 4, b = 5, c = 6;
       *         f(): increment all global variables by 1, return their sum.
       *         g(): multiply all global variables by 2, return their sum. */
    int i1 = f() + g();
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */

    int power(int, int);
#if 1 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
    /* Case 2: The value of `i2` is incremented before being printed, but the
     * order of evaluation between arguments is unspecified. Depending on
     * whether ++i2 or power(2, i2) is evaluated first, the printed values may
     * differ. */
    int i2 = 5;
    printf("%d %d\n", ++i2, power(2, i2));
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */

    int a[100];
#if 1 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
    /* Case 3: This causes undefined behavior. The variable `i3` is modified
     * (`i3++`) and read (`a[i3]`) in the same expression without an intervening
     * sequence point. */
    int i3 = 0;
    a[i3] = i3++;
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */

#if 1 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
    /* Case 4: These expressions are also undefined behavior. Because `i4` is
     * both modified and accessed multiple times in the same expression without
     * a sequence point, the result is unpredictable. */
    int i4 = 2;
    i4 + i4 + ++i4; /* Could be 2 + 2 + 3 or 3 + 3 + 3, etc. */
    i4 + i4 + i4++; /* Could be 2 + 2 + 2 or 3 + 3 + 2, etc. */
#endif              /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
}

int f()
{
    return 100;
}

int g()
{
    return 200;
}

int power()
{
    return 300;
}
