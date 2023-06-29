#include <stddef.h>

void apply_lut(unsigned int mat[4][4], const unsigned int *lut)
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (mat[i][j] < 0)
                return;
            mat[i][j] = lut[mat[i][j]];
        }
    }
}
