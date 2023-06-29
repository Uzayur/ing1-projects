int my_pow(int a, int b)
{
    if (b == 0)
        return 1;
    else
    {
        int pow = 1;
        if (b % 2 == 0)
        {
            for (int i = 0; i < b / 2; i++)
                pow = pow * a * a;
        }
        else
        {
            pow = pow * a;
            for (int i = 0; i < (b - 1) / 2; i++)
                pow = pow * a * a;
        }
        return pow;
    }
}
