#include <stdio.h>
#include <stdlib.h>

#define PRINT_BIT_PATTERN(x)                                    \
    do {                                                        \
        const unsigned char *_p = (const unsigned char *) &(x); \
        size_t _i = sizeof(x);                                  \
        while (_i-- > 0) {                                      \
            unsigned char _mask;                                \
            for (_mask = 0x80U; _mask; _mask >>= 1)             \
                putchar((_p[_i] & _mask) ? '1' : '0');          \
        }                                                       \
        putchar('\n');                                          \
    } while (0)

void case1(void)
{
    struct {
        unsigned int a : 1;
        unsigned int b : 2;
        unsigned int c : 4;
        unsigned int : 1;
        unsigned int d : 8;
    } bits = { 0 };

    bits.a = 1;   /*         1 */
    bits.b = 2;   /*        10 */
    bits.c = 15;  /*      1111 */
    bits.d = 128; /* 1000 0000 */

    PRINT_BIT_PATTERN(bits);
}

void case2(void)
{
    struct {
        unsigned int a : 1;
        unsigned int b : 2;
        unsigned int : 0;
        unsigned int c : 1;
        unsigned int d : 8;
    } bits = { 0 };

    bits.a = 1;   /*         1 */
    bits.b = 2;   /*        10 */
    bits.c = 1;   /*         1 */
    bits.d = 128; /* 1000 0000 */

    PRINT_BIT_PATTERN(bits);
}

int main(void)
{
    case1();
    case2();

    return 0;
}
