SELECT title
FROM books
WHERE genre = 'Poem' OR (author = 'JK Rowling' AND genre = 'Fantasy')
ORDER BY title;
