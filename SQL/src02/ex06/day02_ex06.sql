SELECT pizza_name, pizzeria.name AS pizzeria_name
FROM menu
LEFT JOIN pizzeria ON menu.pizzeria_id = pizzeria.id
LEFT JOIN person_order ON menu.id = person_order.menu_id 
LEFT JOIN person ON person_order.person_id = person.id
WHERE person.name = 'Denis' OR person.name = 'Anna'
ORDER BY pizza_name, pizzeria_name;