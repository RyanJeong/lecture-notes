#define NKEYS 100

#if 1 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
char *keyword[NKEYS];
int keycount[NKEYS];
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */

#if 1 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
struct key {
    char *word;
    int count;
} keytab[NKEYS]; /* each element of `keytab` has a pair of `word` and `count` */
#endif           /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */

#if 0  /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
struct key keytab[] = { "auto", 0, "break", 0, "case", 0, "char", 0,
                        /* ... skipped ... */
                        "unsigned", 0, "void", 0, "volatile", 0, "while", 0 };
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */

#if 1 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
/*1*/ const int SIZE1 = sizeof keytab / sizeof(struct key);
/*2*/ const int SIZE2 = sizeof keytab / sizeof(keytab[0]);
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
