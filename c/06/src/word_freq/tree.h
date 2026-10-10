#ifndef WORD_FREQ_TREE_H
#define WORD_FREQ_TREE_H

#if 1                    /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
struct tnode {           /* the tree node: */
    char *word;          /* points to the text */
    int count;           /* number of occurrences */
    struct tnode *left;  /* left child */
    struct tnode *right; /* right child */
};
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */

struct tnode *addtree(struct tnode *, char *);
void treeprint(struct tnode *);
struct tnode *talloc(void);

#endif /* WORD_FREQ_TREE_H */
