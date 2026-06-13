#include <stdio.h>

#define NSYM 100

struct {
    char *name; /* Identifier name */
    int flags;  /* Identifier flags (e.g., extern, static, etc.) */
    int utype;  /* Identifier type */
    union {
        int ival;   /* Integer value */
        float fval; /* Float value */
        char *sval; /* String value */
    } u;
} symtab[NSYM];

enum { INT, FLOAT, STRING };

void check_identifiers(int i)
{
    if (symtab[i].utype == INT)
        printf("%d\n", symtab[i].u.ival);
    else if (symtab[i].utype == FLOAT)
        printf("%f\n", symtab[i].u.fval);
    else if (symtab[i].utype == STRING)
        printf("%s\n", symtab[i].u.sval);
    else
        printf("bad type %d in utype\n", symtab[i].utype);
}
