SELECT b.title, b.author
FROM books b, authors a
WHERE b.genre = 'Poem' AND a.country = 'France'
AND b.author = a.name
ORDER BY b.title, b.author;
