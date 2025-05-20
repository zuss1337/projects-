SELECT pizzeria.name AS pizzeria_name 
FROM pizzeria
JOIN person_visits ON pizzeria.id = person_visits.pizzeria_id
JOIN person ON person_visits.person_id = person.id
WHERE person.name = 'Andrey'
EXCEPT
SELECT pizzeria.name AS pizzeria_name 
FROM menu
JOIN pizzeria ON menu.pizzeria_id = pizzeria.id
JOIN person_order ON menu.id = person_order.menu_id
JOIN person ON person_order.person_id = person.id
WHERE person.name = 'Andrey'
ORDER BY pizzeria_name;