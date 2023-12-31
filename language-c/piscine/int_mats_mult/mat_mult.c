#include <stddef.h>

void mat_mult(int **mat1, int **mat2, size_t *matrices_size, int **out)
{
    size_t a = matrices_size[0];
    size_t b = matrices_size[1];
    size_t c = matrices_size[2];

    for (size_t i = 0; i < a; i++)
    {
        for (size_t k = 0; k < c; k++)
        {
            for (size_t j = 0; j < b; j++)
                out[i][k] += mat1[i][j] * mat2[j][k];
        }
    }
    return;
}
