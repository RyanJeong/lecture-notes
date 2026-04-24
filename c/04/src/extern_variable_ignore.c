#define MAXVAL 100
#define BUFSIZE 100

#if 1 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
double val[MAXVAL];
char buf[BUFSIZE];
int buf_size = BUFSIZE;
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */

#if 1                      /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
extern double val[MAXVAL]; /* MAXVAL must be same as in the file where `val` is
                              defined */
extern char buf[];         /* Size can be omitted for external arrays
                              (`sizeof` is unavailable). */
extern int buf_size;       /* Provides the array size explicitly since
                              `sizeof(buf)` fails. */
#endif                     /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
