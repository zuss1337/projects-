SELECT person.name, menu.pizza_name, menu.price, 
TRIM_SCALE(((100-person_discounts.discount) * menu.price)/100) AS discount_price,
pizzeria.name AS pizzeria_name
FROM person_order 
LEFT JOIN person ON person_order.person_id = person.id
LEFT JOIN menu ON person_order.menu_id = menu.id
LEFT JOIN pizzeria ON menu.pizzeria_id = pizzeria.id
LEFT JOIN person_discounts ON person.id = 
person_discounts.person_id AND 
pizzeria.id = person_discounts.pizzeria_id
ORDER BY person.name,menu.pizza_name