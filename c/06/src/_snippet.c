#if 1 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
/* `point` is the struct tag */
struct point {
    int x;
    int y;
};
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */

void snippet1(void)
{
#if 1 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
    /* `struct point` is the struct type */
    struct point p1;      /* `p1` is a variable of type `struct point` */
    struct point p2 = p1; /* `p2` is a variable of type `struct point`
                             initialized with the value of `p1` */
#endif                    /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */

    (void) p2; /* Suppress unused variable warning */

#if 1        /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
    struct { /* Declare an anonymous structure tpye (not reuseable) */
        int x;
        int y;
    } p3; /* Not reusable: the type has no name */
#endif    /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */

    (void) p3; /* Suppress unused variable warning */

#if 0  /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
    struct { int x; int y; } p_a; /* Type A: anonymous struct 1 */
    struct { int x; int y; } p_b; /* Type B: anonymous struct 2 (new type!) */
    p_a = p_b; /* error: `p_a` and `p_b` have different types(incompatible) */
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
}

#if 1       /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
int id;     /* `id` here is a variable in the ordinary identifier namespace */
struct id { /* `id` here is a tag in the tag namespace */
    int id; /* `id` here is a member in the structure member namespace */
};
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */

#if 1 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
/* The member `x` is initialized to 320. */
/* The member `y` is initialized to 200. */
struct point maxpt = { 320, 200 };
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */

#if 1 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
struct rect {
    struct point pt1;
    struct point pt2;
};

struct rect screen;
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */

#include <stdio.h>

void snippet2(void)
{
#if 1 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
    struct point maxpt = { 10, 20 };
    struct rect screen = { { 0, 0 }, { 30, 40 } };

    /* Accessing member `x` of `maxpt`           (maxpt.x: 10) */
    printf("maxpt.x: %d\n", maxpt.x);
    /* Accessing member `y` of `pt2` of `screen` (screen.pt2.y: 40) */
    printf("screen.pt2.y: %d\n", screen.pt2.y);
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
}

#if 1 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
struct data {
    int id;
    char *str;
};
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */

void snippet3(void)
{
#if 0  /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
    char str[] = "abc def xyz";
    struct data arr[3] = { { 1, str }, { 4, str + 4 }, { 8, str + 8 } };
    struct data *p = arr;

    ++p->id;     /* res: 2, increments `id`, not p -> implied: ++(p->id) */
    (++p)->id;   /* res: 4, increments `p` before accessing `id` */
    (p++)->id;   /* res: 4, increments `p` after accessing `id` */
    *p->str;     /* res: 'x', fetches whatever `str` points to */
    *p->str++;   /* res: 'x', accesses *p->str, then increments `str` */
    (*p->str)++; /* res: 'y', increments the character that `str` points to */
    *p++->str;   /* res: 'z', accesses `str`, then increments `p` */
    /* now `p` points past the last element of the array */
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
}

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

#if 1 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
struct {
    char c1;
    char c2;
    char c3;
} ccc;
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */

#if 1 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
struct {
    short s;
    int i;
    char c;
} sic;

struct {
    short s;
    char c;
    int i;
} sci;
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */

#if 0  /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
/* This is a matter of personal taste; pick the form you like and HOLD to it. */
struct key*
binsearch(char* word, struct key tab[], int n)
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */

#if 1                             /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
#define GREETINGS "Hello, World!" /* install("GREETINGS", "Hello, World!") */
char *str = GREETINGS;            /* lookup("GREETINGS") -> "Hello, World!" */
#endif                            /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */

#include <stdlib.h> /* for malloc() */

#define MAXLINES 1000 /* max #lines to be sorted */

void snippet4(void)
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

void snippet5(void)
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

void snippet6(void)
{
#if 1 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
    typedef int (*PFI)(char *, char *);

    /* #define can't create function pointer types like this */
    PFI strcmp, numcmp;
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */

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

void snippet7(void)
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
