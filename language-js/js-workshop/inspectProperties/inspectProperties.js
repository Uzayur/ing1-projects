function getNumberFields(inputObject)
{
    if (!inputObject)
        return [];

    let final = [];
    for (let x in inputObject)
    {
        if (typeof inputObject[x] == 'number')
            final.push(x);
    }
    return final;
}

function incrementCounters(inputObject)
{
    let numbers = getNumberFields(inputObject);
    if (!numbers.length)
        return;

    let regex = /.*[Cc][Oo][Uu][Nn][Tt][Ee][Rr].*/
    for (x in numbers)
    {
        if (regex.test(numbers[x]))
            inputObject[numbers[x]] += 1;
    }
}

function deleteUppercaseProperties(inputObject)
{
    if (!inputObject)
        return;

    for (element in inputObject)
    {
        if (element == element.toUpperCase())
            delete inputObject[element];
        else
            deleteUppercaseProperties(inputObject[element]);
    }
}

module.exports = {
    getNumberFields,
    incrementCounters,
    deleteUppercaseProperties,
}
