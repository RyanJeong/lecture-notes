#include <stdlib.h> /* for malloc() */

#define MAXLINES 1000 /* max #lines to be sorted */

void foo(void)
{
#if 1 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
    /* `typedef` is used to create a new type name (alias) for an existing type:
    typedef Type Identifier; */

    typedef int Length;   /* Now `Length` is synonymous with `int` */
    typedef char *String; /* Now `String` is synonymous with `char *` */
#endif                    /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */

#if 1 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
    Length len, maxlen;
    Length lengths[] = { 1, 10, 100 };

    String p, lineptr[MAXLINES], alloc(int);
    int strcmp(String, String);
    p = (String) malloc(100);
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */

    (void) len;     /* Suppress unused variable warning */
    (void) maxlen;  /* Suppress unused variable warning */
    (void) lengths; /* Suppress unused variable warning */
    (void) p;       /* Suppress unused variable warning */
    (void) lineptr; /* Suppress unused variable warning */
}

void bar(void)
{
#if 1 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
    /* storage-class-specifiers: auto, register, static, extern, typedef */
    extern int g_var;   /* `g_var` is an external variable declaration */
    typedef int Length; /* `Length` is a type alias for `int` */
#endif                  /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
    Length len;
    (void) g_var; /* Suppress unused variable warning */
    (void) len;   /* Suppress unused variable warning */
}

#if 1 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
typedef struct tnode *Treeptr;
typedef struct tnode { /* the tree node: */
    char *word;        /* points to the text */
    int count;         /* number of occurrences */
    Treeptr left;      /* left child */
    Treeptr right;     /* right child */
} Treenode;

Treeptr talloc(void)
{
    return (Treeptr) malloc(sizeof(Treenode));
}
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */

#include <stdlib.h> /* for atof() */

int numcmp(char *s, char *t)
{
    double v1, v2;

    v1 = atof(s);
    v2 = atof(t);

    if (v1 < v2)
        return -1;
    else if (v1 > v2)
        return 1;
    else
        return 0;
}

void qux(void)
{
#if 1 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
    typedef int (*PFI)(char *, char *);

    /* #define can't create function pointer types like this */
    PFI strcmp, numcmp;
#endif             /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
    (void) strcmp; /* Suppress unused variable warning */
    (void) numcmp; /* Suppress unused variable warning */
}

#if 1 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
/* ImU64: machine-independent 64-bit unsigned integer type using typedef */
#ifdef _MSC_VER
/* 64-bit unsigned integer for Microsoft compilers */
typedef unsigned __int64 ImU64;
#else
/* 64-bit unsigned integer for other compilers */
typedef unsigned long long ImU64;
#endif
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */