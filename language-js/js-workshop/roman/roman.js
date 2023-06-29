function number_value(letter)
{
    if (letter == 'I')
        return 1;
    else if (letter == 'V')
        return 5;
    else if (letter == 'X')
        return 10;
    else if (letter == 'L')
        return 50;
    else if (letter == 'C')
        return 100;
    else if (letter == 'D')
        return 500;
    else
        return 1000;
}

function toRoman(number)
{
    let result = "";

    while (number != 0)
    {
        if (number >= 1000)
        {
            result += "M";
            number -= 1000;
        }

        else if (number >= 900)
        {
            result += "CM";
            number -= 900;
        }

        else if (number >= 500)
        {
            result += "D";
            number -= 500;
        }

        else if (number >= 400)
        {
            result += "CD";
            number -= 400;
        }

        else if (number >= 100)
        {
            result += "C";
            number -= 100;
        }

        else if (number >= 90)
        {
            result += "XC";
            number -= 90;
        }

        else if (number >= 50)
        {
            result += "L";
            number -= 50;
        }

        else if (number >= 40)
        {
            result += "XL";
            number -= 40;
        }

        else if (number >= 10)
        {
            result += "X";
            number -= 10;
        }

        else if (number >= 9)
        {
            result += "IX";
            number -= 9;
        }

        else if (number >= 5)
        {
            result += "V";
            number -= 5;
        }

        else if (number >= 4)
        {
            result += "IV";
            number -= 4;
        }

        else if (number >= 1)
        {
            result += "I";
            number -= 1;
        }
    }

    return result;
}

function fromRoman(romanString)
{
    let sum = 0;

    for (let i = romanString.length - 1; i >= 0; i--)
    {
        let value = number_value(romanString[i])
        let j = i
        let shift = 0;

        while (j - 1 >= 0 && number_value(romanString[j - 1]) < number_value(romanString[i])) {
            j--;
            value -= number_value(romanString[j]);
            shift++;
        }

        sum += value;
        i -= shift;
    }

    return sum;
}

module.exports = {
    fromRoman,
    toRoman
}
