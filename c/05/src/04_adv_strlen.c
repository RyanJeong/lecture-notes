/* strlen: return length of string s */
int strlen(char *s)
{
    char *p = s;

    while (*p != '\0')
        p++;

    /* p - s: [s, p), length of the string */
    return p - s;
}
