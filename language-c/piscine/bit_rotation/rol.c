unsigned char rol(unsigned char value, unsigned char roll)
{
    while (roll--)
    {
        if (value >= 128)
            value = (value << 1) + 1;
        else
            value = value << 1;
    }
    return value;
}
