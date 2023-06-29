void swap(int *tab, int i, int j)
{
    int index_i = tab[i];
    int index_j = tab[j];

    tab[i] = index_j;
    tab[j] = index_i;
}

void quicksort_improve(int *tab, int begin, int end)
{
    int pivot = 0;
    int ind_begin = 0;
    int ind_end = 0;

    if (begin < end)
    {
        pivot = tab[begin];
        ind_begin = begin;
        ind_end = end;

        while (42)
        {
            while (tab[ind_begin] <= pivot && ind_begin < end)
                ind_begin++;
            while (tab[ind_end] > pivot)
                ind_end--;

            if (ind_begin < ind_end)
                swap(tab, ind_begin, ind_end);
            else
                break;
        }

        swap(tab, begin, ind_end);

        quicksort_improve(tab, begin, ind_end - 1);
        quicksort_improve(tab, ind_end + 1, end);
    }
}

void quicksort(int *tab, int len)
{
    quicksort_improve(tab, 0, len - 1);
}
