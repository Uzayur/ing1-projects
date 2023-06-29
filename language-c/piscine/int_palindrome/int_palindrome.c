int int_palindrome(int n)
{
    int test = n;
    int palindrome = 0;

    while (n != 0)
    {
        palindrome += (n % 10);
        palindrome *= 10;
        n /= 10;
    }
    palindrome /= 10;

    if (test == palindrome)
        return 1;
    else
        return 0;
}
