SELECT q.title
FROM quest q, character c, character_quests cq
WHERE c.id = cq.character_id
AND cq.quest_id = q.id
AND cq.complete = 1
AND c.name = 'Kuro'
ORDER BY q.title;
