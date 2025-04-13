#include <stdio.h>

int main(void)
{
    switch (1) {
    case 1:
        printf("One\n");
    case 2:
        printf("Two\n");
    default:
        printf("Other\n");
    }

    return 0;
}
