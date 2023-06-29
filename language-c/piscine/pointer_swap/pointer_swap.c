void pointer_swap(int **a, int **b)
{
    int *transtion = *a;
    *a = *b;
    *b = transtion;
    return;
}
