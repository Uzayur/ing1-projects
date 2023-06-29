#include <stddef.h>
#include <stdlib.h>

int top_left(int *array, int size, int column, size_t *value)
{
    int row = 0;

    if (column != size - 1)
    {
        column++;
        array[column] = *value;
        *value += 1;
    }
    else
        return -1;

    while (column > 0 && row != size - 1)
    {
        row++;
        column--;
        array[row * size + column] = *value;
        *value += 1;
    }
    if (row == size - 1)
        return -2;
    return row;
}

int left_top(int *array, int size, int row, size_t *value)
{
    int column = 0;
    if (row != size - 1)
    {
        row++;
        array[row * size] = *value;
        *value += 1;
    }
    else
        return -2;

    while (row > 0 && column != size - 1)
    {
        row--;
        column++;
        array[row * size + column] = *value;
        *value += 1;
    }
    if (column == size - 1)
        return -1;
    return column;
}

int right_bottom(int *array, int size, int row, size_t *value)
{
    int column = size - 1;
    if (row == size - 1)
        return -1;
    array[row * size + column] = *value;
    *value += 1;

    while (column > 0 && row < size - 1)
    {
        row++;
        column--;
        array[row * size + column] = *value;
        *value += 1;
    }
    if (column == size - 2)
        return -2;
    return column;
}

int bottom_right(int *array, int size, int column, size_t *value)
{
    int row = size - 1;

    if (column == size - 1)
        return -2;

    array[row * size + column] = *value;
    *value += 1;

    while (column < size - 1 && row > 0)
    {
        row--;
        column++;
        array[row * size + column] = *value;
        *value += 1;
    }
    if (row == size - 2)
        return -2;
    return row;
}

int *handle_right_bottom(int *array, size_t *value, size_t size)
{
    size_t n = size;
    int row = 0;
    while (*value <= n * n - 1)
    {
        int tmp = right_bottom(array, n, row + 1, value);
        if (tmp < 0)
            break;
        int tmp2 = bottom_right(array, n, tmp + 1, value);
        if (tmp2 < 0)
            break;
        row = tmp2;
    }
    array[n * n - 1] = n * n - 1;
    return array;
}

int *handle_bottom_right(int *array, size_t *value, size_t size)
{
    size_t n = size;
    int column = 0;
    while (*value <= n * n - 1)
    {
        int tmp2 = bottom_right(array, n, column + 1, value);
        if (tmp2 < 0)
            break;
        int tmp = right_bottom(array, n, tmp2 + 1, value);
        if (tmp < 0)
            break;
        column = tmp;
    }
    array[n * n - 1] = n * n - 1;
    return array;
}

int *zigzag(size_t n)
{
    if (n == 0)
        return NULL;

    int *array = calloc(n * n, sizeof(int));

    int row = 0;
    int column = 0;

    size_t val = 1;
    size_t *value = &val;
    array[0] = 0;

    int next = 0;
    while (*value <= n * n - 1)
    {
        row = top_left(array, n, column, value);
        if (row < 0)
        {
            next = row;
            break;
        }
        column = left_top(array, n, row, value);
        if (column < 0)
        {
            next = column;
            break;
        }
    }

    if (next == -1)
        return handle_right_bottom(array, value, n);
    else
        return handle_bottom_right(array, value, n);
}
