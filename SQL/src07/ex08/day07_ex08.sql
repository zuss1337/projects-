SELECT person.address,pizzeria.name, COUNT(*) AS count_of_orders
FROM person_order
LEFT JOIN menu ON person_order.menu_id = menu.id
LEFT JOIN person ON person_order.person_id = person.id
LEFT JOIN pizzeria ON menu.pizzeria_id = pizzeria.id
GROUP BY person.address,pizzeria.name
ORDER BY person.address,pizzeria.name