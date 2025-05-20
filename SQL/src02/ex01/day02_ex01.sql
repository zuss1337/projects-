SELECT missing_date::DATE
FROM generate_series('2022-01-01', '2022-01-10', INTERVAL '1 day') AS missing_date
LEFT JOIN person_visits 
ON missing_date = person_visits.visit_date 
AND (person_visits.person_id = 1 OR person_visits.person_id = 2)
WHERE person_visits.visit_date IS NULL
ORDER BY missing_date ASC;
