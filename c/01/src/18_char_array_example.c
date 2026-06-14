#include <stdio.h>

void print(char arr[])
{
    printf("%s\n", arr);
}

int main(void)
{
    char arr[100] = "Hello";
    print(arr);

    return 0;
}
