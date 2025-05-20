SELECT pizza_name, price , pizzeria.name AS pizzeria_name  
FROM menu
LEFT JOIN pizzeria ON menu.pizzeria_id = pizzeria.id
WHERE menu.id NOT IN
(SELECT person_order.menu_id 
FROM person_order)
ORDER BY pizza_name, price, pizzeria_name