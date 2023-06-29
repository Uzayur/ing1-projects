SELECT author AS name, count(title) ||
regexp_replace(rpad(' book', CAST (4 + count(title) AS INTEGER), 's'), 's+', 's') AS stocks
FROM books
GROUP BY author
ORDER BY author;
