SELECT *
FROM transaction
WHERE timestamp = (SELECT max(timestamp) FROM transaction);
