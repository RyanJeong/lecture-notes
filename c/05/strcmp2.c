/* strcmp: return <0 if s<t, 0 if s==t, >0 if s>t; pointer version */
int strcmp(char *s, char *t)
{
    while (*s == *t) {
        if (*s == '\0')
            return 0;
        ++s, ++t;
    }

    return *s - *t;
}
