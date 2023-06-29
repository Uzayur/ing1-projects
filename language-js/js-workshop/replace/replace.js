function replace(str)
{
    let re = /([0-9]{2})\/([0-9]{2})\/([0-9]{4})/;

    while (str != str.replace(re, '$3-$1-$2'))
        str = str.replace(re, '$3-$1-$2');

    return str;
}

module.exports = {
    replace,
}
