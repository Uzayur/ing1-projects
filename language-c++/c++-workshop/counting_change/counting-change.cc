constexpr long long count_change_index(const long long amount, int index)
{
    constexpr int array[8] = { 1, 2, 5, 10, 20, 50, 100, 200 };

    if (amount < 0)
        return 0;

    else if (amount == 0)
        return 1;

    int change = 0;
    change += count_change_index(amount - array[index], index);

    if (index != 0)
        change += count_change_index(amount, index - 1);

    return change;
}

constexpr long long count_change(const long long amount)
{
    constexpr int array[8] = { 1, 2, 5, 10, 20, 50, 100, 200 };
    int index = 7;

    if (amount < 0)
        return 0;

    else if (amount == 0)
        return 1;

    int change = 0;
    change += count_change_index(amount - array[index], index)
        + count_change_index(amount, index - 1);

    return change;
}
