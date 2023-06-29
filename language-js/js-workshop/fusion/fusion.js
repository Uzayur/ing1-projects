function fusion(...objs) {
    if (!objs.length)
        return {};

    if (objs.length == 1)
        return objs[0];

    return objs.reduce((previous, current) =>
    {
        for (currentValue in current)
        {
            let count = 0;
            for (previousValue in previous)
            {
                let previousType = typeof previous[previousValue];
                let currentType = typeof current[currentValue];

                if (previousValue == currentValue)
                {
                    count += 1;
                    if (Array.isArray(previous[previousValue]) || Array.isArray(current[currentValue]))
                        previous[previousValue] = previous[previousValue].concat(current[currentValue]);

                    else if (previousType == 'object' && currentType == 'object')
                        previous[previousValue] = fusion(previous[previousValue], current[currentValue]);

                    else if (previousType != currentType || (previousType == 'boolean' && currentType == 'boolean'))
                        previous[previousValue] = current[currentValue];
                    else
                        previous[previousValue] += current[currentValue];
                }
            }

            if (count == 0)
                previous[currentValue] = current[currentValue];
        }
        return previous;
    });
}

module.exports = {
    fusion
}
