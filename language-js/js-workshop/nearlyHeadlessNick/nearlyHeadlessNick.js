const axios = require("axios");
const cheerio = require("cheerio");

async function scrape(url) {
    try {
        const { data } = await axios.get(url);
        const $ = cheerio.load(data);

        const title = $('title').text();
        var infoValue = "";
        if ($('meta[name="description"]').attr('content'))
             infoValue = $('meta[name="description"]').attr('content');

        const tokens = $('meta[name="keywords"]').attr('content').split(', ');

        let dataArray = [];
        if (tokens.includes('Harry'))
        {
            $('tr.row').each((index, element) => {
                let title = $(element).children('td.title').text();
                let year = $(element).children('td.year').text();
                let director = $(element).children('td.director').text();
                let boxOffice = $(element).children('td.box-office').text();

                dataArray[index] = {
                    title : title,
                    year : year,
                    director : director,
                    boxOffice : boxOffice
                }
            })
        }

        else if (tokens.includes('Quotes'))
        {
            $('div[class="quote"]').each( (i, element) => {
                let quote = $(element).children('div.quote-text').text().trim();
                let author = $(element).children('div.quote-author').children('span').text();
                let tags = [];
                $(element).children('div.quote-tags').children('span.tag').each((index, tag) => {
                    tags[index] = $(tag).text();
                })

                dataArray[i] = {
                    quote : quote,
                    author : author,
                    tags : tags
                }
            })
        }

        else if (tokens.includes('Random'))
        {
            $('div.fact').each((i, element) => {
                let fact = $(element).text().trim();

                dataArray[i] = {
                    fact : fact
                }
            })
        }

        let value = $('a');
        let subInfo = await Promise.all($('a').map(async function(element) {
            let obj = $(value[element])
            let array = await scrape(obj.attr('href'));

            return {
                id : obj.attr('id'),
                text : obj.text().trim(),
                href: obj.attr('href'),
                title: array['title'],
                content: array['content']
            }
        }))

        let finalResult = {
            title: title,
            meta : {
                description : infoValue,
                keywords : tokens
            },
            content : dataArray,
            subpages : subInfo
        };

        return finalResult;

    } catch (err)
    {
        console.error(err);
    }
}

module.exports = {
    scrape
}
