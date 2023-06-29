function armstrongNumber(number) {
    if (typeof number === 'number')
    {
        let size = number.toString().length;
        let numberStr = number.toString();
        let sum = 0;

        for (let i = 0; i < size; i++)
            sum += parseInt(numberStr[i]) ** size;

        return sum == number;
    }
    return false;
}

module.exports = {
    armstrongNumber,
}
