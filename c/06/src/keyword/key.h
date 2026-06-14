#ifndef __KEYWORD_KEY_H__
#define __KEYWORD_KEY_H__

struct key {
    char *word;
    int count;
};

extern const int NKEYS;
extern struct key keytab[];

#endif /* __KEYWORD_KEY_H__ */
