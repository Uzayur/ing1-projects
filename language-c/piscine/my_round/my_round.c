int my_round(float n)
{
    if (n < 0)
    {
        for (float i = 0; i < (-1) * n + 2; i++)
        {
            if ((-1) * n - i > -0.5 && (-1) * n - i < 0.5)
                return -i;
            else if ((-1) * n - i == 0.5)
                return -(i + 1);
        }
    }
    else
    {
        for (float i = 0; i < n + 2; i++)
        {
            if (n - i > -0.5 && n - i < 0.5)
                return i;
            else if (n - i == 0.5)
                return i + 1;
        }
    }
    return 0;
}
