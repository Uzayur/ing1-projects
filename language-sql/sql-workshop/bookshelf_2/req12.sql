SELECT b.title, b.author AS name
FROM books b, authors a
WHERE b.author = a.name
AND b.release >= a.death_date
ORDER BY b.title, b.author;
