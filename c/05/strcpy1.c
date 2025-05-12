/* Simplified example; not actual implementation(s). */
/* strcpy: copy t to s; pointer version */
void strcpy(char *s, char *t)
{
    int i;

    i = 0;
    while ((*s = *t) != '\0') {
        ++s;
        ++t;
    }
}
