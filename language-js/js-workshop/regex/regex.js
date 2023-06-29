function toInt(str)
{
    let result = 0;
    let power = 0;

    for (let i = str.length - 1; i >= 0; i--)
    {
        result += (str[i] - '0') * 10 ** power
        power++;
    }

    return result;
}

function loginEasy(str)
{
    let index = 0;

    if (str[0] == '.')
        return false;

    while (str[index] == '-' || (str[index] >= 'a' && str[index] <= 'z'))
        index++;

    if (str[index] != '.' || index + 1 == str.length)
        return false;

    index++;
    while (str[index] == '-' || (str[index] >= 'a' && str[index] <= 'z'))
        index++;

    return index == str.length;
}

function loginMedium(str)
{
    if (loginEasy(str))
        return true;

    let index = 0;

    while ((str[index] >= 'a' && str[index] <= 'z') || str[index] == '-')
        index++;

    if (str[index] > '9' || str[index] < '1' || str[index] == '\0')
        return false;

    index++;
    if (str[index] != '.')
        return false;

    index++;
    while ((str[index] >= 'a' && str[index] <= 'z') || str[index] == '-')
        index++;

    return index == str.length;
}

function loginHard(str)
{
    if (loginMedium(str))
        return true;

    let index = 0;

    while (str[index] >= 'a' && str[index] <= 'z')
        index++;

    if (str[index] != '_')
        return false;

    index++;
    if (str[index] != '-' && (str[index] < '0' || str[index] > '9') && (str[index] < 'a' || str[index] > 'z'))
        return false;

    return index + 1 == str.length;
}

function isDate(str)
{
    let day = "";
    let month = "";
    let year = "";

    let index = 0;

    while (str[index] >= '0' && str[index] <= '9')
    {
        day += str[index];
        index++;
    }

    if (str[index] != '/' || (toInt(day) < 1 || toInt(day) > 31))
        return false;

    index++;
    while (str[index] >= '0' && str[index] <= '9')
    {
        month += str[index];
        index++;
    }

    if (str[index] != '/' || (toInt(month) < 1 || toInt(month) > 12))
        return false;


    index++;
    while (str[index] >= '0' && str[index] <= '9')
    {
        year += str[index];
        index++;
    }

    if (toInt(year) < 0)
        return false;

    return index == str.length;
}

module.exports = {
    isDate,
    loginHard,
    loginMedium,
    loginEasy,
}
