unsigned int digit(int n, int k)
{
    if (n <= 0 || k <= 0)
        return 0;
    else
    {
        int indice = 1;
        while (n != 0)
        {
            if (indice == k)
                return n % 10;
            else
            {
                n /= 10;
                indice++;
            }
        }
        return 0;
    }
}
