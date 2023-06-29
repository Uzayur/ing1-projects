SELECT name,
    CASE WHEN death_date IS NULL THEN '2000-01-01' - birth_date
    ELSE death_date - birth_date
    END AS days
FROM authors
WHERE birth_date < '2000-01-01'::date
ORDER BY name;
