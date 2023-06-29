const fs = require('fs');
const path = require('path');

function extract(directoryPath)
{
    if (fs.existsSync(directoryPath))
    {
        let files = fs.readdirSync(directoryPath);
        let emails = [];

        for (let file in files)
        {
            let text = fs.readFileSync(path.join(directoryPath , files[file]), "utf-8");
            const regex = /[a-z0-9-.+_]+@[a-z0-9-.]+\.[a-z0-9.]{2,}/g;

            let mail = text.match(regex);
            if (mail)
                emails = emails.concat(mail);
        }
        return emails;
    }

    else
        throw new Error("The directory does not exist");
}

module.exports = {
    extract
}
