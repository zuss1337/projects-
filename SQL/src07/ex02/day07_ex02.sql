(SELECT pizzeria.name, COUNT(*) AS count,'visit' AS action_type
FROM person_visits
LEFT JOIN pizzeria ON person_visits.pizzeria_id = pizzeria.id
GROUP BY pizzeria.name
ORDER BY 2 DESC
LIMIT 3)
UNION
(SELECT pizzeria.name, COUNT(*) AS count,'order' AS action_type
FROM person_order
LEFT JOIN menu ON person_order.menu_id = menu.id
LEFT JOIN pizzeria ON menu.pizzeria_id = pizzeria.id
GROUP BY pizzeria.name
ORDER BY 2 DESC
LIMIT 3)
ORDER BY 3 ASC, 2 desc