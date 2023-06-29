SELECT title
FROM quest
WHERE (creature_start = creature_end
OR gold > 100) AND level_min BETWEEN 8 AND 10
ORDER BY title;
