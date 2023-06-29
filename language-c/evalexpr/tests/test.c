#include <criterion/criterion.h>

#include "../src/evalexpr.h"

Test(test, simple)
{
    int value = valid_operator('*');
    int exp = 1;
    cr_assert_eq(value, exp);
}
