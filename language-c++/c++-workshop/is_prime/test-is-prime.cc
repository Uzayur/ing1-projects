#include "is-prime.hh"

int main()
{
    static_assert(!is_prime<1>());
    static_assert(is_prime<2>());
    static_assert(is_prime<3>());
    static_assert(is_prime<5>());
    static_assert(is_prime<101>());
    static_assert(is_prime<449>());
    static_assert(is_prime<3457>());

    return 0;
}
