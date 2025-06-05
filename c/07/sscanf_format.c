#include <stdio.h>

/* NB: Reuse previously implemented functions: getline() */
int getline(char *, int);

int main(void)
{
    int month, day, year;
    char monthname[20], line[1000];

    while (getline(line, sizeof(line)) > 0) {
        if (sscanf(line, "%d %s %d", &day, monthname, &year) == 3)
            printf("valid: %s\n", line); /* 25 Dec 1998 form */
        else if (sscanf(line, "%d/%d/%d", &month, &day, &year) == 3)
            printf("valid: %s\n", line); /* mm/dd/yy form */
        else
            printf("invalid: %s\n", line); /* invalid form */
    }

    return 0;
}
