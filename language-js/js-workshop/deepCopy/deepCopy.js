function deepCopy(x)
{
    let type = typeof x;

    if (!x || type == 'number' || type == 'boolean' || type == 'string')
        return x;

    else if (type == 'object')
    {
        if (x instanceof Date)
            return new Date(x.getTime());

        else if (Array.isArray(x))
        {
            let copy = []
            for (i in x)
                copy[i] = deepCopy(x[i]);

            return copy;
        }

        else
        {
            let newObject = {};
            for (attribut in x)
                newObject[attribut] = deepCopy(x[attribut]);

            return newObject;
        }
    }
    return x;
}

module.exports = {
    deepCopy
}
