SELECT customer_surname AS "best customers", count(*) AS "number of travels"
FROM booking
GROUP BY customer_surname
ORDER BY count(*) DESC, customer_surname DESC
LIMIT 3;
