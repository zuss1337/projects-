WITH fem AS (
	SELECT pizzeria.name AS pizzeria_name
	FROM pizzeria
	LEFT JOIN person_visits ON pizzeria.id = person_visits.pizzeria_id
	LEFT JOIN person ON person_visits.person_id = person.id
	WHERE person.gender = 'female'
),
men AS (
	SELECT pizzeria.name AS pizzeria_name
	FROM pizzeria
	LEFT JOIN person_visits ON pizzeria.id = person_visits.pizzeria_id
	LEFT JOIN person ON person_visits.person_id = person.id
	WHERE person.gender = 'male'
)
SELECT * 
FROM (
    (SELECT * FROM fem EXCEPT ALL SELECT * FROM men)
    UNION ALL
    (SELECT * FROM men EXCEPT ALL SELECT * FROM fem))
ORDER BY pizzeria_name;