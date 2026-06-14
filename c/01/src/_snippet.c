void snippet1(void)
{
    int fahr, celsius;

#if 1 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
    /*1*/ celsius = 5 * (fahr - 32) / 9;
    /*2*/ celsius = 5 / 9 * (fahr - 32); /* Isn't this more like the formula? */
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */

    (void) fahr;    /* Avoid unused variable warning */
    (void) celsius; /* Avoid unused variable warning */
}

#include <stdio.h>

void snippet2(void)
{
    int fahr, celsius;

#if 1 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
    printf("Hello, World\n");
    printf("%d\t%d\n", fahr, celsius);
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */

#if 1 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
    printf("%d + %d = %d\n", 1, 2, 1 + 2);
    printf("PI: %f\n", 3.141592);
    printf("PI: %d\n", 3.141592); /* prints an indeterminate integer value
                                     (implementation-defined), not 3 */
#endif                            /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
    (void) fahr;                  /* Avoid unused variable warning */
    (void) celsius;               /* Avoid unused variable warning */
}

void snippet3(void)
{
#if 0  /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
    int lower, upper, step; lower = 0; upper = 300; step = 20;
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
}

void snippet4(void)
{
#if 0  /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
    /*1*/ celsius = 5*(fahr-32)/9;
    /*2*/ celsius = 5 * (fahr - 32) / 9;
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */

#if 0  /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
    int i = 0;

    /* Style #1 */
    while (i < 10) { ++i; }

    /* Style #2 */
    while (i >= 0) {
        --i;
    }
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
}

void snippet5(void)
{
#if 0            /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
#define STEP 20; /* step size */
#endif           /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */

#if 0  /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
    for (i = 0; i < STEP; ++i) {
        /* ... */
    }
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */

#if 0  /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
    for (i = 0; i < 20;; ++i) { /* Syntax error */
        /* ... */
    }
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
}

void snippet6(void)
{
#if 1 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
    int i = 3;
    ++i; /* now i is 4 */
    float f = 3.5;
    ++f; /* now f is 4.5 */
#endif   /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
}

void snippet7(void)
{
    int c, nl, nw, nc, cond1, cond2, state;

    state = cond1 = cond2 = nl = nw = nc = 0;
#if 1 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
    /*1*/ nl = nw = (nc = 0);
    /*2*/ nl = (nw = (nc = 0));
    /*3*/ (nl = (nw = (nc = 0)));
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */

#if 1 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
    if ((c == ' ') || (c == '\n') || (c == '\t')) {
        /* ... */
    }
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */

#ifndef OUT
#define OUT 0
#endif
#if 1 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
    if ((c == ' ') || (c == '\n') || (c == '\t')) {
        /* ... */
    } else {
        if (state == OUT) {
            /* ... */
        }
    }
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
}

void snippet8(void)
{
#if 1 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
    int student_score1, student_score2, /* ... */ student_score100;
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */

#if 1 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
    int student_score[100];
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */

#if 1 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
    student_score[0] = 100;
    student_score[1] = 75;
    /* ... */
    student_score[99] = 25;
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */

    (void) student_score1;   /* Avoid unused variable warning */
    (void) student_score2;   /* Avoid unused variable warning */
    (void) student_score100; /* Avoid unused variable warning */
    (void) student_score;    /* Avoid unused variable warning */
}

#if 0  /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
int main(void)
{
    int i;
    /* ... */
}

int power(int base, int n)
{
    int i, p;
    /* ... */
}
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
