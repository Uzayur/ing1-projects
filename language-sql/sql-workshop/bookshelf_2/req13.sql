SELECT b.title, b.author
FROM books b, authors a
WHERE b.author = a.name
GROUP BY title, author
HAVING min(release) IN (
    SELECT min(release)
    FROM books
    GROUP BY author)
ORDER BY b.title, b.author
