void str_revert(char str[])
{
    int size = 0;
    while (str[size] != '\0')
        size++;

    for (int i = 0; i < size / 2; i++)
    {
        char transition = str[i];
        str[i] = str[size - i - 1];
        str[size - i - 1] = transition;
    }
    return;
}
