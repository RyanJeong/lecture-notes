#include <stdio.h>

int main(void)
{
#if 1 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
    /*1*/ char c1 = 'A';
    /*2*/ char c2 = 65; /* In ASCII, 0x41 = 'A' */
#endif                  /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */

#if 1                        /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
#define UPPER_Z '\132'       /* Octal 132 = Decimal 90 = 'Z' */
#define QUESTION_MARK '\077' /* Octal 077 = Decimal 63 = '?' */

#define BELL_OCT1 '\007' /* Octal 007 = Decimal  7 = ASCII Bell */
#define BELL_OCT2 '\07'  /* Octal  07 = Decimal  7 = ASCII Bell */
#define VTAB '\13'       /* Octal  13 = Decimal 11 = ASCII Vertical Tab */
#define SOH '\1'         /* Octal   1 = Decimal  1 = ASCII Start of Heading */

#define UPPER_A '\x41' /* Hex 0x41 = Decimal 65 = 'A' */
#define LF '\x0A'      /* Hex 0x0A = Decimal 10 = ASCII Line Feed */
#define BELL_HEX '\x7' /* Hex 0x07 = Decimal  7 = ASCII Bell */
#endif                 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */

    return 0;
}

#if 1 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
#define MAXLINE 1000
char line[MAXLINE + 1];

#define LEAP 1 /* in leap years */
int days[31 + 28 + LEAP + 31 + 30 + 31 + 30 + 31 + 31 + 30 + 31 + 30 + 31];
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */

void foo(void)
{
#if 1 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
    printf("It's useful for splitting up long strings across several lines");

    printf("It's useful"
           " for splitting up long strings"
           " across several lines");
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
}

#if 1 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
enum escapes {
    BELL = '\a',
    BACKSPACE = '\b',
    TAB = '\t',
    NEWLINE = '\n',
    VTAB = '\v',
    RETURN = '\r'
};

enum months { JAN = 1, FEB, MAR }; /* FEB is 2, MAR is 3 */

enum boolean { NO, YES };     /* NO is 0, YES is 1 */
enum boolean condition = YES; /* condition can be initialized to YES or NO */
#endif                        /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
