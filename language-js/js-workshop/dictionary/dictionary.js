function getAllWordsFromLanguage(words, language) {
    words = words.filter(word => word.language == language);

    if (words.length == 0)
        return [];
    return words;
}

function getConjunctions(words, count) {
    words = words.filter(word => word.partOfSpeech == "conjunction");

    if (words.length > count)
        words = words.slice(0, count);

    return words;
}

function averageLength(words)
{
    if (words.length == 0)
        return null;

    let reducer = (sum, current) => sum + current.literal;
    let huge_word = words.reduce(reducer, "");
    return Math.round(huge_word.length / words.length);
}

function compare_a(a, b) {
    if (a.literal.normalize("NFD").replace(/[\u0300-\u036f]/g, "") > b.literal.normalize("NFD").replace(/[\u0300-\u036f]/g, ""))
        return 1;
    else if (a.literal.normalize("NFD").replace(/[\u0300-\u036f]/g, "") < b.literal.normalize("NFD").replace(/[\u0300-\u036f]/g, ""))
        return -1;
    else
        return 0;
}

function getWordsSorted(words) {
    return words.sort(compare_a);
}

function compare_language(a, b) {
    if (a.language > b.language)
        return 1;
    else if (a.language < b.language)
        return -1;
    else
        return 0;
}

function getTranslations(words, word) {
    let our_word = words.filter(x => x.literal == word);
    if (our_word.length == 0)
        return null;

    let translation = [{ language: our_word[0].language, translation: word }];

    if (our_word[0].englishTranslation == null && our_word[0].language != "English")
        return translation;


    let final = [];
    let all_translation = [];
    if (our_word[0].language == "English")
    {
        all_translation = words.filter(x => x.englishTranslation == our_word[0].literal);
        final = [{ language: our_word[0].language, translation: word }];
    }
    else
        all_translation = words.filter(x => x.englishTranslation == our_word[0].englishTranslation || x.literal == our_word[0].englishTranslation);

    all_translation.map(function(e) {final.push({language: e.language, translation: e.literal})})


    return final.sort(compare_language);
}

function getLongWordDefinitions(words, threshold) {
    let array = words.filter(x => x.literal.length >= threshold);

    let final = [];
    array.map(function(e) { final.push( {
        length: e.literal.length,
        word: e.literal,
        language: e.language,
        definition: e.definition
    }) });

    return final.sort((a, b) => a.word.normalize("NFD").replace(/[\u0300-\u036f]/g, "") > b.word.normalize("NFD").replace(/[\u0300-\u036f]/g, "") ? 1 : -1).sort((a, b) => a.length > b.length ? -1 : 1);
}

module.exports = {
    getAllWordsFromLanguage,
    getConjunctions,
    averageLength,
    getWordsSorted,
    getTranslations,
    getLongWordDefinitions,
}
