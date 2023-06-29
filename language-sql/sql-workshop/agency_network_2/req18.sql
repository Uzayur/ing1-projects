SELECT e.surname, e.name, e.email
FROM employee e, agency a
WHERE e.agency_code = a.code
AND a.ratings > 6
ORDER BY e.surname, e.name, e.email;
