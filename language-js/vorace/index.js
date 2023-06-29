import cheerio from 'cheerio';
import fetch from 'node-fetch';
import fs from 'fs';

try {
    fs.mkdirSync('results');
} catch(err) {}

try {
    fs.mkdirSync('images');
} catch(err) {}

let global_url = process.env.SERVER_URL;
//let global_url = 'http://127.0.0.1:8080';

async function fetch_url(url) {
    const response = await fetch(url);
    const body = await response.text();
    return cheerio.load(body);
}

export async function first_step() {
    const $ = await fetch_url(global_url);

    let secretText = $('main[class="background"]').children('div.hero')
                                                  .children('div.title')
                                                  .children('div[style="display: none"]')
                                                  .text();

    let text = $('main[class="background"]').children('div.hero')
                                            .children('div.sub-title')[1]
                                            .children[0].data;
    const regex = /Nous répertorions actuellement (?<products>[0-9]*) produits et (?<users>[0-9]*) utilisateurs./gm;
    const regexMatch = regex.exec(text);

    let users = `${regexMatch.groups.users}`;
    let products = `${regexMatch.groups.products}`;

    let info = {
        "productNumber": parseInt(products),
        "userNumber": parseInt(users),
        "secret": secretText
    };

    fs.writeFileSync('./results/index.json', JSON.stringify(info, null, '    '));
}

function monthNumber(str) {
    if (str == 'janvier')
        return 0;
    else if (str == 'février' || str == 'fevrier')
        return 1;
    else if (str == 'mars')
        return 2;
    else if (str == 'avril')
        return 3;
    else if (str == 'mai')
        return 4;
    else if (str == 'juin')
        return 5;
    else if (str == 'juillet')
        return 6;
    else if (str == 'août' || str == 'aout')
        return 7;
    else if (str == 'septembre')
        return 8;
    else if (str == 'octobre')
        return 9;
    else if (str == 'novembre')
        return 10;
    else
        return 11;
}

function compareDate(a, b) {
    if (a.createdAt > b.createdAt)
        return 1;
    else if (a.createdAt < b.createdAt)
        return -1;
    else
        return 0;
}

function compareNumber(a, b) {
    if (a[1] > b[1])
        return -1;
    else if (a[1] < b[1])
        return 1;
    return 0;
}

function compareName(a, b) {
    if (a[0].normalize("NFD").replace(/[\u0300-\u036f]/g, "").toLowerCase() > b[0].normalize("NFD").replace(/[\u0300-\u036f]/g, "").toLowerCase())
        return 1;
    else if (a[0].normalize("NFD").replace(/[\u0300-\u036f]/g, "").toLowerCase() < b[0].normalize("NFD").replace(/[\u0300-\u036f]/g, "").toLowerCase())
        return -1;
    return 0;
}

function addAuthors(authors) {
    let array = [];
    for (let i in authors)
    {
        let test = 0;
        for (let j = 0; j < array.length; j++) {
            if (array[j][0] == authors[i].author)
            {
                test = 1;
                array[j][1] = array[j][1] + 1;
            }
        }
        if (test == 0)
            array[array.length] = [authors[i].author, 1];
    }

    return array;
}

function addCookie(authors) {
    let regex = /(?<![\w\d])(cookies?)(?![\w\d])/gmi;
    let array = [];

    for (let i in authors)
    {
        const count = (authors[i].content.match(regex) || []).length;

        let test = 0;
        for (let j = 0; j < array.length; j++) {
            if (array[j][0] == authors[i].author)
            {
                array[j][1] = array[j][1] + count;
                test = 1;
            }
        }
        if (test == 0)
            array[array.length] = [authors[i].author, count];
    }
    return array;
}

function findMaxCookie(array) {
    let max = 0;
    for (let i = 0; i < array.length; i++)
    {
        if (array[i][1] > max)
            max = i;
    }
    return array[max][0];
}

async function make_obj(url) {
    let $ = await fetch_url(global_url + url);
    let newsClass = $('main[class="section"]').children('section[class="article"]');

    let title = $(newsClass).children('div.article-header')
                                .children('h1[class="article-title"]')
                                .text();
    let slug = url.slice(6);
    let content = $(newsClass).children('p[class="article-content"]')
                                  .text();
    let author = $(newsClass).children('div.article-footer')
                                 .children('div.article-author')
                                 .text().substring(10);

    let regex = /Publié le [a-z]+ (?<day>[0-9]{1,}) (?<month>[^ ]+) (?<year>[0-9]{4}), (?<hour>[0-9]{2}):(?<minute>[0-9]{2}):(?<seconde>[0-9]{2})/gm;
    let match = regex.exec($(newsClass).children('div.article-footer')
                                           .children('div.article-date')
                                           .text());

    let date = new Date(`${match.groups.year}`, monthNumber(`${match.groups.month}`), `${match.groups.day}`, `${match.groups.hour}`, `${match.groups.minute}`, `${match.groups.seconde}`);
    let createdAt = date.getTime();

    let news = {
        "title": title,
        "slug": slug,
        "content": content,
        "author": author,
        "createdAt": createdAt
    };

    return news;
}

export async function second_step() {
    let $ = await fetch_url(global_url + '/news?page=1');

    let finalArray = [];
    let authorsArray = [];
    let cookieArray = [];
    let newsArray = [];

    let divRight = $('main[class="section"]').children('div[class="flex article"]')
                                             .children('div.right')
                                             .children('a');

    let count = 2;
    while (true) {
        $('ul li.article-item').each( (i, element) => {
            newsArray[newsArray.length] = $(element).children('a').attr('href');
        })

        if (divRight.length == 1 && divRight[0].children[0].data == 'Page précédente')
            break;

        $ = await fetch_url(global_url + '/news?page=' + `${count}`)
        divRight = $('main[class="section"]').children('div[class="flex article"]')
                                             .children('div.right')
                                             .children('a');
        count++;
    }

    finalArray = await Promise.all(newsArray.map(make_obj));

    authorsArray = addAuthors(finalArray);
    cookieArray = addCookie(finalArray);

    finalArray.sort(compareDate);
    fs.writeFileSync('./results/news.json', JSON.stringify(finalArray, null, '  '));

    authorsArray.sort(compareName).sort(compareNumber);

    let analysis = {
        "authorNews": authorsArray,
        "mostCookieAuthor": findMaxCookie(cookieArray)
    }
    fs.writeFileSync('./results/news_analysis.json', JSON.stringify(analysis, null, '    '));
}

function transformObj($, url) {
    let fast = $('main[class="section"]').children('section[class="product"]')
                                         .children('div[class="product-content"]');

    let description = $(fast).children('div.product-information')
                             .children('div[class="product-content m-width-70"]')
                             .text().trim();

    let price = $(fast).children('div.product-information')
                       .children('div[class="m-width-70"]')
                       .children('div[class="product-price"]').text().trim();
    let regexPrice = /(?<price>[0-9]+(.[0-9]{1,2})?).*/gm;
    let matchPrice = regexPrice.exec(price);

    let stock = $(fast).children('div.product-information')
                       .children('div[class="m-width-70"]')
                       .children('div[class="product-stock"]')
                       .text();
    let regexStock = /Il n’en reste plus que (?<stock>[0-9]+) !.*/gm;
    let matchStock = regexStock.exec(stock);

    let tags = [];
    let tag = $(fast).children('div.product-information').children('div[class="list-tag m-width-70"]').children('div[class="tag"]').each( (i, e) => { tags[tags.length] = $(e).text() });

    let image = $(fast).children('div[class="product-picture"]').children('img').attr('src');
    let regexImage = /\/.*\/.*\/(?<image>.*)/gm;
    let matchImage = regexImage.exec(image);

    let regexCategory = /\/category\/(?<category>[a-zA-Z]+)\/.*/gm;
    let matchCategory = regexCategory.exec(url);

    let obj = {
        "name": $('h1.product-title').text(),
        "description": description,
        "price": Number(`${matchPrice.groups.price}`),
        "stock": Number(`${matchStock.groups.stock}`),
        "tags": tags,
        "image": `${matchImage.groups.image}`,
        "category": `${matchCategory.groups.category}`
    };

    return obj;
}

async function pushObj(url) {
    return transformObj(await fetch_url(global_url + url), url);
}

async function handleTime(objectsURL) {
    let objects = [];
    let index = 1;

    let $ = await fetch(global_url + objectsURL[0]);

    let header = ($).headers;
    let intervalLimit = parseInt(header.get('x-ratelimit-interval'));
    let requestLimit = parseInt(header.get('x-ratelimit-remaining'));
    let resetLimit = (new Date(header.get('x-ratelimit-reset'))).getTime();

    $ = cheerio.load(await $.text());
    objects.push(transformObj($, objectsURL[0]));

    objects.push(await Promise.all(objectsURL.slice(index, index + requestLimit).map(pushObj)));

    index += requestLimit;
    requestLimit += 1;
    let resetTime = resetLimit;

    while (index < objectsURL.length)
    {
        await new Promise(i => setTimeout(i, resetTime - Date.now() + 30));
        objects.push(await Promise.all(objectsURL.slice(index, index + requestLimit).map(pushObj)));
        index += requestLimit;

        resetTime +=  intervalLimit * 1000 + 40;
    }
    return [].concat.apply([], objects);
}

async function extract_products(category) {
    let $ = await fetch_url(global_url + category);
    let objectsArray = [];

    let pages = $('main[class="section"]').children('div[class="flex product"]')
                                          .children('div.right')
                                          .children('a');

    while (true)
    {
        let objectsURL = [];
        $('ul li.product-item').each( (i, e) => {
            objectsArray[objectsArray.length] = $(e).children('a').attr('href');
        })

        if (pages.length == 1 && pages[0].children[0].data == 'Page précédente')
            break;

        let page_link = 0;
        if (pages.length == 1)
        {
            page_link = $('main[class="section"]').children('div[class="flex product"]')
                                                  .children('div.right')
                                                  .children('a')
                                                  .attr('href');
        }
        else
        {
            page_link = $('div.right a.page-link:contains("Page suivante")').attr('href');

        }
        $ = await fetch_url(global_url + page_link);
        pages = $('main[class="section"]').children('div[class="flex product"]')
                                          .children('div.right')
                                          .children('a');
    }
    return objectsArray;
}

function productName(a, b) {
    if (a.name > b.name)
        return 1;
    else if (a.name < b.name)
        return -1;
    return 0;
}

function productCategory(a, b) {
    if (a.category > b.category)
        return 1;
    else if (a.category < b.category)
        return -1;
    return 0;
}

function totalSumFun(array) {
    let sum = 0;
    for (let i = 0; i < array.length; i++)
        sum += array[i].stock * array[i].price;
    return sum;
}

function totalMeanFun(array) {
    let number = 0;
    for (let i in array)
        number += array[i].price;
    return number / array.length;
}

function createMeanCategory(array) {
    let obj = {};
    for (let k in array)
    {
        let sum = 0;
        for (let i in array[k])
            sum += array[k][i].price;

        let category = array[k][0].category;
        obj[category] = sum / array[k].length;
    }
    return obj;
}

async function downloadImage(e) {
    let $ = await fetch(global_url + '/public/product-images/' + e.image);
    let img = await $.arrayBuffer();

    let buff = Buffer.from(img);
    fs.writeFileSync('./images/' + e.image, buff);

    let obj = {
        "name": e.name,
        "image": e.image
    };
    return obj;
}

function lookingForDuplicate(imageArray) {
    let duplicate = [];
    for (let i in imageArray)
    {
        for (let j in imageArray)
        {
            let iBuff = fs.readFileSync('./images/' + imageArray[i].image);
            let jBuff = fs.readFileSync('./images/' + imageArray[j].image);

            if (i != j && iBuff.equals(jBuff) && !duplicate.includes(imageArray[j].name))
                duplicate.push(imageArray[j].name);
        }
    }
    return duplicate;
}

export async function third_step() {
    let $ = await fetch_url(global_url);

    let regex_category = /\/category\/.*/;
    let categories = [];
    let products = [];


    $('div[class="h-left"]').children('div[class="h-action"]')
                            .children('a.h-link')
                            .each((i, e) => { categories[categories.length] = $(e).attr('href') });

    categories = categories.filter(element => regex_category.test(element));

    products = await Promise.all(categories.map(extract_products));
    products = await Promise.all(products.map(handleTime));

    let meanPriceCategory = createMeanCategory(products);

    products = [].concat.apply([], products);
    products.sort(productName).sort(productCategory);

    let imageArray = await Promise.all(products.map(downloadImage));
    let duplicateImage = lookingForDuplicate(imageArray);

    let totalSum = totalSumFun(products);
    let meanSum = totalMeanFun(products);

    let analys = {
        "productsWithDuplicateImage": duplicateImage,
        "meanPrice": meanSum,
        "meanPricePerCategory": meanPriceCategory,
        "totalValueOfStock": totalSum
    };

    fs.writeFileSync('./results/products_analysis.json', JSON.stringify(analys, null, '    '));
    fs.writeFileSync('./results/products.json', JSON.stringify(products, null, '    '));
}

first_step();
second_step();
third_step();
