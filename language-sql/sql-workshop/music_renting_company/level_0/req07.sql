DELETE FROM album
WHERE
    length(name) - length(replace(name, 'P', '')) = 2
    OR length(name) - length(regexp_replace(name, 'mm', 'g')) != 0
    OR MOD(length(name), 7) = 0
    OR length(name) - length(regexp_replace(name, '&', '', 'g')) != 0;
