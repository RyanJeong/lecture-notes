#include <stdio.h>

#if 1                 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
int sum(int a, int b) /* callee */
{
    return a + b; /* return value */
}
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */

void snippet1(void)
{
#if 1                        /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
    int result = sum(5, 10); /* caller (return value is assigned to `result`) */
#endif                       /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */

    (void) result; /* To avoid unused variable warning */
}

#if 1 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
int foo(void)
{
    return 100;
}

double bar(void)
{
    return 3.14;
}
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */

void snippet2(void)
{
#if 1 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
    /* Missing function declaration; both return types are assumed to be int */
    int foo_val = foo();    /* OK: foo() returns 100 */
    double bar_val = bar(); /* Error: bar() returns garbage (not 3.14) */
#endif                      /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */

    (void) foo_val; /* To avoid unused variable warning */
    (void) bar_val; /* To avoid unused variable warning */
}

void snippet3(void)
{
#if 1               /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
    auto int x = 1; /* same as: int x = 1; */
#endif              /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */

    (void) x; /* To avoid unused variable warning */
}

void snippet4(void)
{
#if 1                   /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
    register int x = 1; /* just a hint to the compiler to store `x` in a
                           register; often ignored by modern compilers */
#endif                  /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */

    (void) x; /* To avoid unused variable warning */
}

#if 1 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
int count(void)
{
    static int counter = 0; /* block-scope variable with no linkage */
    return ++counter;       /* `counter` retains its value across function calls
                             * because it is declared as static */
}
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */

#if 1 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
/* file-scope function with internal linkage (not visible to other files) */
static int global_var = 42;

static void set_global_var(int var)
{
    global_var = var; /* modifies the file-scope variable `global_var` */
}
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */

#if 0  /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
/* file1.c */
int g_foo = 10;
static int g_bar = 20; /* `g_bar` has internal linkage and is not visible
                          outside this file */

void func(void)
{
    extern int g_foo; /* `extern` is optional because `g_foo` is already visible
                         (but it clarifies that `g_foo` is defined elsewhere) */
}
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */

#if 1 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
/* file2.c */
extern int g_foo; /* `extern` is required to use `g_foo` defined in file1.c */
extern int g_bar; /* `g_bar` is not visible here because it has internal linkage
                     -> compile error */
#endif            /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */

#if 0  /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
double val[MAXVAL];
char buf[BUFSIZE];
int buf_size = BUFSIZE;
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */

#define MAXVAL 100

#if 1                      /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
extern double val[MAXVAL]; /* MAXVAL must be same as in the file where `val` is
                              defined */
extern char buf[];         /* Size can be omitted for external arrays
                              (`sizeof` is unavailable). */
extern int buf_size;       /* Provides the array size explicitly since
                              `sizeof(buf)` fails. */
#endif                     /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */

#if 1 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
/* my_math.h */
int add(int a, int b); /* a function declaration */
#define PI 3.14159     /* a constant definition */
#endif                 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */

#if 0                /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
/* 1. Include a custom header file using relative paths */
#include "my_math.h" /* include my_math.h from the current directory */

/* 2. Include a custom header file using absolute paths */
#include "/home/docker/workspace/proj_math/include/my_math.h"
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */

#if 0 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
/* my_math.c */
#include "my_math.h"

double get_pi(void)
{
    return PI;
}
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */

#if 1 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
/* my_math.i */
double get_pi(void);
double get_pi(void)
{
    return 3.14;
}
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */

#if 0  /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
/* grandparent.h */
int func()
{
    return 100;
}
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */

#if 0 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
/* parent.h */
#include "grandparent.h"
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */

#if 0 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
/* child.c */
#include "grandparent.h"
#include "parent.h"
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */

#if 1 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
/* grandparent.h */
#ifndef __GRANDPARENT_H__
#define __GRANDPARENT_H__
int func()
{
    return 100;
}
#endif /* __GRANDPARENT_H__ */
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */

#if 0              /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
#include <stdio.h> /* absolute path to a standard header file */

#include "my_proj.h" /* relative path to a user-defined header file */

#define MY_HEADER "my_header.h"
#include MY_HEADER /* using a macro to include a header file */
#endif             /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */

#if 1 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
#define HELLO "Hello, World!"
/* ... */
#undef HELLO /* After this point, the `HELLO` identifier is no longer valid */
#endif       /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */

#if 1 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
#define TOKEN "token"
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */

#define TOKENIZER "tokenizer"

void snippet5(void)
{
#if 1                        /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
    printf("%s", "TOKEN");   /* the string "TOKEN" is not the token `TOKEN` */
    printf("%s", TOKENIZER); /* the token `TOKENIZER` is not the same with the
                                token `TOKEN` */
#endif                       /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
}

#if 1 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define SQUARE(x) (x * x)
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */

void snippet6(int i, int j)
{
#if 1              /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
    MAX(i++, j++); /* ((i++) > (j++) ? (i++) : (j++)) */
    /* -> Due to side effects, the larger value is incremented twice,
          not once. */
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */

#if 0  /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
    SQUARE(x + 1); /* x + 1 * x + 1 */
                   /* -> Missing parentheses cause incorrect evaluation */
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
}

void snippet7(int x)
{
#if 1 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
    /* The two format-specifier strings of `printf` are actually the same */
    printf("Integer variable "
           "x"
           " is %d\n",
           (x));
    printf("Integer variable x is %d\n", (x));
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
}

#if 0 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
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
