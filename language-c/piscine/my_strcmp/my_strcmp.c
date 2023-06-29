int my_strcmp(const char *s1, const char *s2)
{
    int indice = 0;
    while (s1[indice] != '\0')
    {
        if (s1[indice] < s2[indice])
            return -42;
        else if (s1[indice] > s2[indice])
            return 42;
        indice++;
    }
    if (s2[indice] != '\0')
        return -42;
    return 0;
}
