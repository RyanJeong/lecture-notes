/* strlen: return length of string s, 2nd version */
int strlen(char *s)
{
    int n;

    for (n = 0; *s != '\0'; ++s)
        ++n;

    return n;
}
