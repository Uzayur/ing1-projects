#include <criterion/criterion.h>

Test(basic, simple)
{
    int value = 1;
    int exp = 1;
    cr_assert_eq(value, exp);
}
