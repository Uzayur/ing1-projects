#include <stddef.h>

int my_strlen(const char *s)
{
    int size = 0;
    while (s[size] != '\0')
        size++;
    return size;
}

int my_pow(int a, int b)
{
    int res = 1;
    for (int i = 0; i < b; i++)
        res *= a;
    return res;
}

int find_max_index(int n, int base_number)
{
    int max_ind = 0;
    while (my_pow(base_number, max_ind) < n)
        max_ind++;

    if (my_pow(base_number, max_ind) == n)
        return max_ind;
    else if (max_ind >= base_number)
        return base_number - 1;
    else
        return max_ind;
}

char *my_itoa_base(int n, char *s, const char *base)
{
    int sign = 0;
    if (n < 0)
    {
        sign++;
        n = -n;
    }

    int base_number = my_strlen(base);
    int index_max_base = find_max_index(n, base_number);
    int s_ind = 0;

    while (n > 0)
    {
        int pow = my_pow(base_number, index_max_base);
        int factor = 0;
        while (factor * pow < n && factor <= base_number - 1)
            factor++;

        if (factor == 0)
            s[s_ind] = 0;

        else if (factor == base_number - 1 && factor * pow < n)
        {
            if (base_number >= 10 && factor >= 10)
                s[s_ind] = 'a' + factor - 10;
            else
                s[s_ind] = '0' + factor;
            n = n - factor * pow;
        }
        else
        {
            if (base_number >= 10 && factor - 1 >= 10)
                s[s_ind] = 'a' + factor - 1 - 10;
            else
                s[s_ind] = '0' + factor - 1;
            n = n - (factor - 1) * pow;
        }
        s_ind++;
        index_max_base--;
    }
    s[s_ind] = '\0';
    return s;
}

#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    char *s = malloc(sizeof(char) * 50);
    printf("Exp : 2A   Got : %s\n", my_itoa_base(42, s, "0123456789ABCDEF"));
    // printf("Exp : 20   Got : %s\n", my_itoa_base(32, s, "0123456789abcdef"));
    // printf("Exp : 1100 Got : %s\n", my_itoa_base(12, s, "01"));
    // printf("Exp : 143  Got : %s\n", my_itoa_base(80, s, "0123456"));
    return 0;
}
