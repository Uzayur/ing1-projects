SELECT count(DISTINCT city), country
FROM destination
GROUP BY country
ORDER BY count(DISTINCT city) desc, country;
