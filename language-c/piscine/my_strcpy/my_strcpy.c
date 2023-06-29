char *my_strcpy(char *dest, const char *source)
{
    int index = 0;
    while (source[index] != '\0')
    {
        dest[index] = source[index];
        index++;
    }
    dest[index] = '\0';
    return dest;
}
