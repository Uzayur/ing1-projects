const fs = require('fs');

function getCleanData(inputPath)
{
    let file = fs.readFileSync(inputPath, {encoding:'utf8',flag:'r'});
    let stationText = file.split(/^;$/gm);

    let final = [];

    // cut the input file with each fuel station
    for (let station in stationText)
    {
        if (!stationText[station].length)
            break;

        let stationInfo = {name: "", baseAddress: "", postalCode: "", city: "", availableFuelTypes: [], averagePrices:{}, prices:{} }

        let step = stationText[station].split('\n');
        // match the line and change parameter of stationInfo
        for (let index in step)
        {
            // match the fuel station name line
            if (/name=(?<name>.*)/gm.test(step[index]))
            {
                let stationName = /name=(?<name>.*)/gm;
                stationName.lastIndex = 0;
                let stationNameMatch = stationName.exec(step[index]);
                stationInfo.name = `${stationNameMatch.groups.name}` ;
            }

            // match the fuel name line
            else if (/start_(?<fuel>.*)/gm.test(step[index]))
            {
                let fuelName = /start_(?<fuel>.*)/gm;
                fuelName.lastIndex=0;
                let fuelNameMatch = fuelName.exec(step[index++]);

                let fuel = `${fuelNameMatch.groups.fuel}`;
                stationInfo.availableFuelTypes.push(`${fuelNameMatch.groups.fuel}`);

                let fuelDatePrice = step[index].split(';')
                // add each price with each date
                for (let i in fuelDatePrice)
                {
                    if (fuelDatePrice[i].length == 0)
                        continue;

                    let fuelPrice = /(?<date>.*)=(?<price>.*)/gm;
                    fuelPrice.lastIndex = 0;
                    let fuelDatePriceMatch = fuelPrice.exec(fuelDatePrice[i]);

                    let date = (new Date(`${fuelDatePriceMatch.groups.date}` * 1000)).toISOString();
                    let price = `${fuelDatePriceMatch.groups.price}` / 100;

                    if (stationInfo.prices[date])
                        Object.assign(stationInfo.prices[date], {[fuel]: price});

                    else
                        Object.assign(stationInfo.prices, {[date]: {[fuel]:price}});

                }
                index += 2;
            }

            // match the fuel station address line
            else if (/address=(?<baseAddress>.*), (?<postalCode>.*) (?<city>.*)/gm.test(step[index]))
            {
                let stationAddress = /address=(?<baseAddress>.*), (?<postalCode>[0-9]*) (?<city>.*)/gm;
                stationAddress.lastIndex=0;
                let stationAddressMatch = stationAddress.exec(step[index]);

                stationInfo.baseAddress = `${stationAddressMatch.groups.baseAddress}`;
                stationInfo.postalCode = `${stationAddressMatch.groups.postalCode}`;

                if (stationInfo.postalCode.length != 5)
                    stationInfo.postalCode = "0" + stationInfo.postalCode;

                stationInfo.city = `${stationAddressMatch.groups.city}`;
            }
        }

        // make the average price
        if (stationInfo.name != "")
        {
            for (let i in stationInfo.availableFuelTypes)
            {
                let fuel = stationInfo.availableFuelTypes[i];

                let sum = 0;
                let count = 0;
                for (let i in stationInfo.prices)
                {
                    for (let j in stationInfo.prices[i])
                    {
                        if (j == fuel)
                        {
                            sum +=stationInfo.prices[i][j];
                            count++;
                        }
                    }
                }

                mean = Math.round(((sum / count) * 100)) / 100;
                Object.assign(stationInfo.averagePrices, {[fuel]: mean});
            }
            final.push(stationInfo);
        }
    }
    return JSON.stringify(final, null, "    ");
}

module.exports = {
    getCleanData
}
