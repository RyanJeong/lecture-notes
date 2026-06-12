#include <stdio.h>

int main(void)
{
    float f3, f4, f5, f6;

    f3 = 16777216.0; /* 1.0000 0000 0000 0000 0000 0000 X 2^24 */
    f4 = 16777216.5; /* Same result as f3, not enough bits to represent f4 */
    f5 = 16777217.0; /* Same result as f3, not enough bits to represent f5 */
    f6 = 16777218.0; /* 1.0000 0000 0000 0000 0000 0010 X 2^24 */
    printf("Float type's mantissa has 24 bits (including the hidden bit).\n"
           "f3: %10.1f, f4: %10.1f, f5: %10.1f, f6: %10.1f\n",
           f3, f4, f5, f6);

    return 0;
}
