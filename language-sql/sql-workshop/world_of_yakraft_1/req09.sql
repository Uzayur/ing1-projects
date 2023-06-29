SELECT t.name
FROM creature c, creature_template t
WHERE c.gid = t.id
AND c.id = 6;
