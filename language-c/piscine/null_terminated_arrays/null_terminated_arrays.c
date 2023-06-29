static int size_list_fun(const char ***matrix)
{
    int index = 0;
    while (matrix[index])
        index++;
    return index;
}

static int size_array_fun(const char ***matrix, int array)
{
    int index = 0;
    while (matrix[array][index])
        index++;
    return index;
}

void reverse_matrix(const char ***matrix)
{
    int size_list = size_list_fun(matrix);
    int begin = 0;
    int end = size_list - 1;

    while (begin < end)
    {
        const char **tmp = matrix[begin];
        matrix[begin++] = matrix[end];
        matrix[end--] = tmp;
    }

    for (int i = 0; i < size_list; ++i)
    {
        int size_array = size_array_fun(matrix, i);

        int begin = 0;
        int end = size_array - 1;
        while (begin < end)
        {
            const char *tmp = matrix[i][begin];
            matrix[i][begin++] = matrix[i][end];
            matrix[i][end--] = tmp;
        }
    }
}
