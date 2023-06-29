#include "dlist.h"
#include "dlist_basics.h"

static size_t min(size_t above, size_t behind, size_t diag)
{
    if (above <= behind && above <= diag)
        return above;
    else if (behind <= above && behind <= diag)
        return behind;
    return diag;
}

unsigned int dlist_levenshtein(struct dlist *list1, struct dlist *list2)
{
    size_t row = list1->size;
    size_t colomn = list2->size;

    if (row == 0)
        return colomn;
    else if (colomn == 0)
        return row;

    unsigned int matrix[row + 1][colomn + 1];

    size_t index = 0;
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
    for (size_t i = 1; i < row + 1; i++)
        for (size_t j = 1; j < colomn + 1; ++j)
        {
            size_t above = matrix[i - 1][j] + 1;
            size_t behind = matrix[i][j - 1] + 1;

            size_t cmp = 1;
            if (dlist_get(list1, i - 1) == dlist_get(list2, j - 1))
                cmp = 0;
            size_t diag = matrix[i - 1][j - 1] + cmp;

            matrix[i][j] = min(above, behind, diag);
        }
    return matrix[row][colomn];
}
