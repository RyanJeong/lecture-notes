#include "table.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *strdup(char *s);

#if 1                            /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
struct nlist *hashtab[HASHSIZE]; /* pointer table */
#endif                           /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */

/* hash: form hash value for string s */
unsigned hash(char *s)
{
    unsigned hashval;

#if 1 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
    for (hashval = 0; *s != '\0'; s++)
        hashval = *s + 31 * hashval;

    return hashval % HASHSIZE;
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
}

#if 1 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
/* lookup: look for s in hashtab */
struct nlist *lookup(char *s)
{
    struct nlist *np;

    for (np = hashtab[hash(s)]; np != NULL; np = np->next) {
        if (!strcmp(s, np->name))
            return np; /* found */
    }

    return NULL; /* not found */
}
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */

/* install: put (name, defn) in hashtab */
struct nlist *install(char *name, char *defn)
{
    struct nlist *np;
    unsigned hashval;

#if 1 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
    if (!(np = lookup(name))) {
        /* not found */
        np = (struct nlist *) malloc(sizeof(*np));
        if (!np || !(np->name = strdup(name)))
            return NULL;
        hashval = hash(name);
        np->next = hashtab[hashval];
        hashtab[hashval] = np;
    } else {
        /* already there */
        free((void *) np->defn); /* free previous defn */
    }
    if (!(np->defn = strdup(defn)))
        return NULL;
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */

    return np;
}
