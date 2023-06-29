SELECT name
FROM creature_template
WHERE id NOT IN (SELECT gid FROM creature)
ORDER BY name;
