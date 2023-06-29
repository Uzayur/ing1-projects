SELECT title, author, release
FROM books
WHERE release < '1900-01-01' OR release >= '2000-01-01'
ORDER BY release DESC, title, author;
