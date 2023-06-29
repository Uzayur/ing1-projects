int my_strlen(const char *key)
{
    int size = 0;
    while (key[size] != '\0')
        size++;
    return size;
}

void cipher(const char *key, const char *msg, char *res)
{
    int key_ind = 0;
    int msg_ind = 0;

    while (msg[msg_ind] != '\0')
    {
        if (key_ind == my_strlen(key))
            key_ind = 0;

        char letter = key[key_ind];
        if (letter <= 'z' && letter >= 'a')
            letter = letter - 32;

        if (msg[msg_ind] >= 'A' && msg[msg_ind] <= 'Z')
        {
            res[msg_ind] = ((msg[msg_ind] + letter - 130) % 26) + 65;
            key_ind++;
        }
        else if (msg[msg_ind] >= 'a' && msg[msg_ind] <= 'z')
        {
            res[msg_ind] = ((msg[msg_ind] + letter - 162) % 26) + 65;
            key_ind++;
        }
        else
            res[msg_ind] = msg[msg_ind];
        msg_ind++;
    }
    res[msg_ind] = '\0';
}

void decipher(const char *key, const char *msg, char *res)
{
    int key_ind = 0;
    int msg_ind = 0;

    while (msg[msg_ind] != '\0')
    {
        if (key_ind == my_strlen(key))
            key_ind = 0;

        char letter = key[key_ind];
        if (letter <= 'z' && letter >= 'a')
            letter = letter - 32;

        if (msg[msg_ind] >= 'A' && msg[msg_ind] <= 'Z')
        {
            res[msg_ind] = 'A' + (msg[msg_ind] - letter + 26) % 26;
            key_ind++;
        }
        else if (msg[msg_ind] >= 'a' && msg[msg_ind] <= 'z')
        {
            res[msg_ind] = 'A' + (msg[msg_ind] - letter - 32 + 26) % 26;
            key_ind++;
        }
        else
            res[msg_ind] = msg[msg_ind];
        msg_ind++;
    }
    res[msg_ind] = '\0';
}
