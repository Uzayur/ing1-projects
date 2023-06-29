SELECT title, author, extract(year from "release") AS release_year
FROM books
ORDER BY release DESC, title, author
