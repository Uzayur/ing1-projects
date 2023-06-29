int int_sqrt(int n)
{
    if (n < 0)
        return -1;
    else
    {
        for (int i = 0; i <= n; i++)
        {
            if (i * i == n)
                return i;
            else if (i * i > n)
                return i - 1;
        }
    }
    return -1;
}
