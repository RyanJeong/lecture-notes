#include <stdio.h>

#define NSYM 100

#if 1 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
struct {
    char *name; /* Identifier name */
    struct {
        unsigned int is_keyword : 1;
        unsigned int is_extern : 1;
        unsigned int is_static : 1;
    } flags;   /* Identifier flags (e.g., extern, static, etc.) */
    int utype; /* Identifier type */
    union {
        int ival;   /* Integer value */
        float fval; /* Float value */
        char *sval; /* String value */
    } u;
} symtab[NSYM];
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */

enum { INT, FLOAT, STRING };

void check_identifiers(int i)
{
    if (symtab[i].flags.is_extern)
        printf("Identifier is extern\n");
    if (symtab[i].flags.is_static)
        printf("Identifier is static\n");

    if (symtab[i].utype == INT)
        printf("%d\n", symtab[i].u.ival);
    else if (symtab[i].utype == FLOAT)
        printf("%f\n", symtab[i].u.fval);
    else if (symtab[i].utype == STRING)
        printf("%s\n", symtab[i].u.sval);
    else
        printf("bad type %d in utype\n", symtab[i].utype);
}
