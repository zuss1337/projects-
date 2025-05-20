WITH date_gen AS (
    SELECT generate_series('2022-01-01', '2022-01-10', INTERVAL '1 day')::DATE AS missing_date
)

SELECT date_gen.missing_date
FROM date_gen
LEFT JOIN person_visits
ON date_gen.missing_date = person_visits.visit_date
AND (person_visits.person_id = 1 OR person_visits.person_id = 2)
WHERE person_visits.visit_date IS NULL
ORDER BY date_gen.missing_date ASC;
