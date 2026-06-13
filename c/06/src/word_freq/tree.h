#ifndef __WORD_TREE_H__
#define __WORD_TREE_H__

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

#endif /* __WORD_TREE_H__ */
