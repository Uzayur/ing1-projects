#include "variant.h"

#include <stdbool.h>
#include <stdio.h>
#include <string.h>

void variant_display(const struct variant *e)
{
    if (e->type == 0)
    {
        int value = e->value.int_v;
        printf("%d\n", value);
    }
    else if (e->type == 1)
    {
        float value = e->value.float_v;
        printf("%f\n", value);
    }
    else if (e->type == 2)
    {
        char value = e->value.char_v;
        printf("%c\n", value);
    }
    else
    {
        printf("%s\n", e->value.str_v);
    }
}

bool variant_equal(const struct variant *left, const struct variant *right)
{
    if (!left && !right)
        return true;

    if (left->type != right->type)
        return false;

    if (left->type == 0 && left->value.int_v == right->value.int_v)
        return true;

    else if (left->type == 1 && left->value.float_v == right->value.float_v)
        return true;

    else if (left->type == 2 && left->value.char_v == right->value.char_v)
        return true;

    else if (left->type == 3 && !strcmp(left->value.str_v, right->value.str_v))
        return true;

    return false;
}

int variant_find(const struct variant *array, size_t len, enum type type,
                 union type_any value)
{
    for (size_t i = 0; i < len; i++)
    {
        if (array[i].type == type)
        {
            if (type == 0 && array[i].value.int_v == value.int_v)
                return i;

            else if (type == 1 && array[i].value.float_v == value.float_v)
                return i;

            else if (type == 2 && array[i].value.char_v == value.char_v)
                return i;

            else if (type == 3 && !strcmp(array[i].value.str_v, value.str_v))
                return i;
        }
    }
    return -1;
}

float variant_sum(const struct variant *array, size_t len)
{
    float res = 0;
    for (size_t i = 0; i < len; i++)
    {
        if (array[i].type == 0)
            res += array[i].value.int_v;
        else if (array[i].type == 1)
            res += array[i].value.float_v;
    }

    return res;
}
