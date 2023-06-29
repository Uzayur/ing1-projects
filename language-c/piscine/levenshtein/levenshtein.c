#include <stddef.h>

size_t my_strlen(const char *s)
{
    size_t size = 0;
    while (s[size] != '\0')
        size++;
    return size;
}

size_t min(size_t above, size_t behind, size_t diag)
{
    if (above <= behind && above <= diag)
        return above;
    else if (behind <= above && behind <= diag)
        return behind;
    return diag;
}

size_t levenshtein(const char *s1, const char *s2)
{
    int row = my_strlen(s1);
    int colomn = my_strlen(s2);

    if (row == 0)
        return colomn;
    else if (colomn == 0)
        return row;

    unsigned int matrix[row + 1][colomn + 1];

    int index = 0;
    while (index < colomn + 1)
    {
        matrix[0][index] = index;
        index++;
    }
    index = 0;
    while (index < row + 1)
    {
        matrix[index][0] = index;
        index++;
    }

    for (int i = 1; i < row + 1; i++)
        for (int j = 1; j < colomn + 1; j++)
        {
            size_t above = matrix[i - 1][j] + 1;
            size_t behind = matrix[i][j - 1] + 1;

            size_t cmp = 1;
            if (s1[i - 1] == s2[j - 1])
                cmp = 0;
            size_t diag = matrix[i - 1][j - 1] + cmp;

            matrix[i][j] = min(above, behind, diag);
        }
    return matrix[row][colomn];
}
