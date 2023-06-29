unsigned long fibo_iter(unsigned long n)
{
    if (n == 0)
        return 0;
    unsigned long transition = 0;
    unsigned long U0 = 0;
    unsigned long U1 = 1;
    unsigned long id = 1;
    for (id = 2; id <= n; id++)
    {
        transition = U1 + U0;
        U0 = U1;
        U1 = transition;
    }
    return U1;
}
