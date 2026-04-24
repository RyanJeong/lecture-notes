#if 1 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
#define MAX(a, b) ((a) > (b) ? (a) : (b))
MAX(i++, j++); /* ((i++) > (j++) ? (i++) : (j++)) */
               /* -> Due to side effects, the larger value is incremented twice,
                     not once. */
#endif         /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */

#if 1 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
#define SQUARE(x) x *x
SQUARE(x + 1); /* x + 1 * x + 1 */
               /* -> Missing parentheses cause incorrect evaluation */
#endif         /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */

#if 1 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
void foo(void)
{
    /* The two format-specifier strings of `printf` are actually the same */
    printf("Integer variable "
           "x"
           " is %d\n",
           (x));
    printf("Integer variable x is %d\n", (x));
}
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */

#if 1 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
#define SYSTEM MSDOS

#if SYSTEM == SYSV
#define HDR "sysv.h"
#elif SYSTEM == BSD
#define HDR "bsd.h"
#elif SYSTEM == MSDOS
#define HDR "msdos.h"
#else
#define HDR "default.h"
#endif

#include HDR /* #include "msdos.h" */
#endif       /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */

#if 1 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
#ifdef MACRO
/* If MACRO is defined */
#endif

#ifndef MACRO
/* If MACRO is not defined */
#endif

#if defined(A) && defined(B)
/* If both A and B are defined */
#endif

#if defined(A) || defined(B)
/* If either A or B is defined */
#endif

#if !defined(A)
/* If A is not defined */
#endif
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */

#if 1 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
#if !defined(HDR)
#define HDR
/* contents of hdr.h go here */
#endif
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */

#if 1 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
#ifndef HDR
#define HDR
/* contents of hdr.h go here */
#endif
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */