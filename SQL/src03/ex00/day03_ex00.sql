SELECT pizza_name, price , pizzeria.name AS pizzeria_name , person_visits.visit_date
FROM menu
LEFT JOIN pizzeria ON menu.pizzeria_id = pizzeria.id
LEFT JOIN person_visits ON pizzeria.id = person_visits.pizzeria_id
LEFT JOIN person ON person_visits.person_id = person.id
WHERE person.name = 'Kate' AND menu.price >= 800 AND menu.price <= 1000
ORDER BY pizza_name, price , pizzeria_name