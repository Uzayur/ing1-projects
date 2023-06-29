SELECT id,
    CASE WHEN now()::date > end_date THEN 'Done'
         WHEN now()::date < start_date THEN 'Booked'
         ELSE 'Ongoing'
    END AS "trip status"
FROM booking
ORDER BY "trip status", id;
