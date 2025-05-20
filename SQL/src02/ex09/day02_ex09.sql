SELECT name 
FROM person 
LEFT JOIN person_order ON person.id = person_order.person_id  
LEFT JOIN menu ON person_order.menu_id = menu.id
WHERE (person.gender = 'female') 
AND menu.pizza_name IN ('pepperoni pizza', 'cheese pizza')
GROUP BY name HAVING COUNT(DISTINCT menu.pizza_name) = 2
ORDER BY name;