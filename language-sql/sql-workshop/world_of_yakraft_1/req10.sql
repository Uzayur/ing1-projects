SELECT c.id
FROM creature c, creature_template t
WHERE c.gid = t.id
AND t.level > 10
ORDER BY c.id;
