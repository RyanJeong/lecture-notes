#if 1 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
/* 3 int variables to represent 3 states (12 bytes) */
int flag_keyword = 1;
int flag_external = 1;
int flag_static = 0;
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */

#if 1               /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
#define KEYWORD 01  /* .... 0001 (2^0) */
#define EXTERNAL 02 /* .... 0010 (2^1) */
#define STATIC 04   /* .... 0100 (2^2) */
#endif              /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */

void foo(void)
{
#if 1 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
    unsigned int flags = 0;

    flags |= EXTERNAL | STATIC;    /* Set the EXTERNAL and STATIC flags */
    flags &= ~(EXTERNAL | STATIC); /* Clear the EXTERNAL and STATIC flags */

    if ((flags & (EXTERNAL | STATIC)) == 0) {
        /* Do something when the flags for EXTERNAL and STATIC are not set */
    }
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
}
