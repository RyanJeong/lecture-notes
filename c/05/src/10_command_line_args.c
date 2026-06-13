#include <stdio.h>

/* echo command-line arguments; 1st version */
#if 1 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
int main(int argc, char *argv[])
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
{
    int i;

    for (i = 1; i < argc; i++)
        printf("%s%s", argv[i], (i < argc - 1) ? " " : "");
    printf("\n");

    return 0;
}
