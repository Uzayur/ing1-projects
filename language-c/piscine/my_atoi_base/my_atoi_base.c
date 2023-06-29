#include <stddef.h>

int my_pow(int a, int b)
{
    int res = 1;
    for (int i = 0; i < b; i++)
        res *= a;
    return res;
}

int my_strlen(const char *s)
{
    int size = 0;
    while (s[size] != '\0')
        size++;
    return size;
}

int inside_base(char s, const char *base)
{
    int index = 0;
    while (base[index] != '\0')
    {
        if (base[index] == s)
            return 1;
        index++;
    }
    return 0;
}

int valid_str(const char *str, const char *base)
{
    int str_size = my_strlen(str);
    if (str_size == 0)
        return -300;

    int str_ind = 0;
    int test = 0;

    int neg_sign = 0;
    int pos_sign = 0;

    while (str[str_ind] != '\0')
    {
        char letter = str[str_ind];
        if (inside_base(letter, base) == 1)
            test++;

        else if (letter == '-')
            neg_sign++;
        else if (letter == '+')
            pos_sign++;

        else if (test != 0 || neg_sign + pos_sign != 0)
            return -300;
        str_ind++;
    }
    str_ind = my_strlen(str) - test;
    if (neg_sign + pos_sign > 1)
        return -300;
    else if (neg_sign == 1)
        return -str_ind;
    return str_ind;
}

int find_index(char s, const char *base)
{
    int index = 0;
    while (base[index] != s)
        index++;
    return index;
}

int my_atoi_base(const char *str, const char *base)
{
    if (valid_str(str, base) == -300)
        return 0;

    int str_end = valid_str(str, base);
    int sign = 0;
    if (str_end < 0)
    {
        sign++;
        str_end = -str_end;
    }

    int base_number = my_strlen(base);
    int str_ind = my_strlen(str) - 1;
    int power = 0;
    int res = 0;

    while (str_ind >= str_end)
    {
        res += my_pow(base_number, power) * find_index(str[str_ind], base);
        power++;
        str_ind--;
    }
    if (sign == 1)
        return -res;
    return res;
}
