#include <stddef.h>

void my_xor_crypt(void *data, size_t data_len, const void *key, size_t key_len)
{
    size_t data_index = 0;
    size_t key_index = 0;

    while (data_index != data_len)
    {
        if (key_index == key_len)
            key_index = 0;

        key_index++;
        data_index++;
    }
}

#include <stdio.h>
int main(void)
{
    char *text = "Example";
    my_xor_crypt(text, 7, "KEY", 3);

    printf("%s\n", text);
    return 0;
}
