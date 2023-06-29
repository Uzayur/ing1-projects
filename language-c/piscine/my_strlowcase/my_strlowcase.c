void my_strlowcase(char *str)
{
    int indice = 0;

    while (str[indice] != '\0')
    {
        if (str[indice] < 91 && str[indice] > 64)
            str[indice] = str[indice] + 32;
        indice++;
    }
    return;
}
