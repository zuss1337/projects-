SELECT visits.name,COALESCE(visits.count,0)
+ COALESCE(orders.count,0) AS total_cost
FROM
(SELECT pizzeria.name, COUNT(*) AS count
FROM person_visits
LEFT JOIN pizzeria ON person_visits.pizzeria_id = pizzeria.id
GROUP BY pizzeria.name
ORDER BY 2 DESC) AS visits
FULL JOIN
(SELECT pizzeria.name, COUNT(*) AS count
FROM person_order
LEFT JOIN menu ON person_order.menu_id = menu.id
LEFT JOIN pizzeria ON menu.pizzeria_id = pizzeria.id
GROUP BY pizzeria.name
ORDER BY 2 DESC) AS orders ON visits.name = orders.name
