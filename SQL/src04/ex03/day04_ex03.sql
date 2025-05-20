SELECT missing_date
FROM (SELECT generated_date FROM v_generated_dates
EXCEPT
SELECT visit_date FROM person_visits) as missing_date
ORDER BY missing_date;
