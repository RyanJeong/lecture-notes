/* Simplified example; not actual implementation(s). */
/* strlen: return length of string s */
int strlen(char *s)
{
    char *p = s;

    while (*p != '\0')
        ++p;

    return p - s;
}
