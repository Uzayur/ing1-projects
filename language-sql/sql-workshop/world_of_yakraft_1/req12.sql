SELECT DISTINCT t.name
FROM quest q, creature c, creature_template t
WHERE q.creature_start = q.creature_end
AND q.creature_start = c.id
AND c.gid = t.id
ORDER BY t.name;
