#ifndef __TABLE_TABLE_H__
#define __TABLE_TABLE_H__

#if 1                   /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
struct nlist {          /* table entry: */
    struct nlist *next; /* next entry in chain */
    char *name;         /* defined name */
    char *defn;         /* replacement text */
};
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */

#define HASHSIZE 101

unsigned hash(char *s);
struct nlist *lookup(char *s);
struct nlist *install(char *name, char *defn);

#endif /* __TABLE_TABLE_H__ */
