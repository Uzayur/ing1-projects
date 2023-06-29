function deepEquality(var1, var2) {
    if (var1 == null && var2 == null)
        return var1 === var2;

    else if ((var1 == null && var2 != null) || (var1 != null && var2 == null))
        return false;

    else if (typeof var1 == 'boolean')
        return var1 == var2;

    else if (typeof var1 == 'number' || typeof var1 == 'string')
        return var1 === var2;

    else if (Array.isArray(var1))
    {
        if (!Array.isArray(var2) || var1.length != var2.length)
            return false;

        for (i in var1)
        {
            if (var1[i] != var2[i])
                return false
        }
        return true;
    }
    else
    {
        if (!deepEquality(Object.keys(var1), Object.keys(var2)))
            return false;

        for (i in var1)
        {
            if (!deepEquality(var1[i], var2[i]))
                return false;
        }
        return true;
    }
}

module.exports = {
    deepEquality
}
