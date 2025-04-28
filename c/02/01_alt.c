#include <limits.h>
#include <stdio.h>

int main(void)
{
    printf("%10s %4s %43s %24s\n", "Type", "Size", "Signed Range",
           "Unsigned Range");
    printf("%10s %4zu %+20d ~ %+20d %u ~ %20u\n", "char", sizeof(char),
           SCHAR_MIN, SCHAR_MAX, 0, UCHAR_MAX);
    printf("%10s %4zu %+20d ~ %+20d %u ~ %20u\n", "short", sizeof(short),
           SHRT_MIN, SHRT_MAX, 0, USHRT_MAX);
    printf("%10s %4zu %+20d ~ %+20d %u ~ %20u\n", "int", sizeof(int), INT_MIN,
           INT_MAX, 0, UINT_MAX);
    printf("%10s %4zu %+20ld ~ %+20ld %lu ~ %20lu\n", "long", sizeof(long),
           LONG_MIN, LONG_MAX, 0UL, ULONG_MAX);

    return 0;
}
