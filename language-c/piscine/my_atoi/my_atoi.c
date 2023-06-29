#include <stddef.h>

int my_atoi(const char *str)
{
    int res = 0;
    int indice = 0;
    int sign_pos = 0;
    int sign_neg = 1;
    int test = 0;

    while (str[indice] != '\0')
    {
        if (str[indice] >= '0' && str[indice] <= '9')
        {
            res *= 10;
            res += str[indice] - '0';
            test++;
        }
        else if (str[indice] == '+')
        {
            sign_pos += 1;
            test++;
        }
        else if (str[indice] == '-')
        {
            sign_neg += 1;
            test++;
        }
        else if (test != 0 || (str[indice] >= 'a' && str[indice] <= 'z'))
            return 0;
        indice++;
    }
    if (sign_neg + sign_pos > 2)
        return 0;
    else if (sign_neg == 2)
        return -res;
    return res;
}
