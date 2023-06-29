#include <stdio.h>
#include <stdlib.h>

void sieve(int n)
{
    if (n <= 2)
        return;

    int count = 1;

    int *arr = calloc(n, sizeof(int));
    count = 0;
    int index = 2;
    while (index < n)
    {
        if (arr[index - 2] == 0)
        {
            arr[index - 2] = index;
            for (int i = index; i <= n; i += index)
                arr[i - 2] = i;
            count++;
        }
        index++;
    }
    printf("%d\n", count);
    free(arr);
}
