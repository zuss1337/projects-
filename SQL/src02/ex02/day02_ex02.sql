SELECT 
COALESCE(person.name, '-') AS person_name,
COALESCE (visit_date::text, 'null') AS visit_date,
COALESCE (pizzeria.name, '-') AS pizzeria_name	
FROM
(SELECT *
FROM person_visits
WHERE visit_date BETWEEN '2022-01-01' AND '2022-01-03') AS dates
FULL JOIN person ON dates.person_id = person.id
FULL JOIN pizzeria ON dates.pizzeria_id = pizzeria.id
ORDER BY person_name, visit_date, pizzeria_name;

