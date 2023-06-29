SELECT q.title, c.name
FROM quest q, character c, character_quests cq
WHERE cq.character_id = c.id
AND cq.quest_id = q.id
AND cq.complete = 0
ORDER BY q.title, c.name;
