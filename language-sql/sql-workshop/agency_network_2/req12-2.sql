SELECT substring(acronym from '..') ||  lpad(regexp_replace(substring(acronym from '..$'), '[a-zA-Z]', '', 'g'), 2, '0') AS acronym
FROM destination
ORDER BY acronym;
