#include <stdio.h>

void sieve(int n)
{
    if (n <= 1)
        return;

    int arr[1000] = { 0 };
    int index = 2;
    while (index <= n)
    {
        if (arr[index - 2] == 0)
        {
            arr[index - 2] = index;
            for (int i = index; i <= n; i += index)
                arr[i - 2] = i;
            printf("%d\n", index);
        }
        index++;
    }
}
