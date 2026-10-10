#ifndef KEYWORD_KEY_H
#define KEYWORD_KEY_H

struct key {
    char *word;
    int count;
};

extern const int NKEYS;
extern struct key keytab[];

#endif /* KEYWORD_KEY_H */
