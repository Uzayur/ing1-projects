SELECT c.surname, c.name, d.country || ', ' || d.city AS destination, h.name AS hotel
FROM destination d, customer c, hotel h
WHERE c.top_destination = d.acronym
AND h.id = d.hotel_id
ORDER BY c.surname, c.name, destination, hotel;
