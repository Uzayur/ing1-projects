SELECT t.assistant, sum(c.price) AS price
FROM transaction t, can c
WHERE c.name = t.can
GROUP BY t.assistant
ORDER BY price DESC
LIMIT 3;

