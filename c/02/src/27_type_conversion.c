#include <stdio.h>

int main(void)
{
    /* Assume: int = 4 bytes (32-bit), long = 4 bytes (32-bit)
       unsigned int: range              0 to 4,294,967,295
       long        : range -2,147,483,648 to 2,147,483,647 */

    unsigned int u = 3000000000U; /* 3 billion, unsigned int (4 bytes) */
    long s = -1L;                 /* signed long (4 bytes) */

    /* Case 3-2: unsigned int + long
      - long has higher rank than unsigned int
      - but long cannot represent all values of unsigned int
        -> Both operands are converted to unsigned long (Case 3-3 is applied)
        -> `s` becomes 4294967295 (wrap-around, MSB is used as a weight) */
    if (s < u)
        printf("s < u\n");
    else
        printf("s >= u\n"); /* This line will be printed */

    return 0;
}
