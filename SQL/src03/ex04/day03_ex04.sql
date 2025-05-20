WITH fem AS
(SELECT pizzeria.name AS pizzeria_name
        	FROM menu
            JOIN pizzeria ON menu.pizzeria_id = pizzeria.id
            JOIN person_order ON person_order.menu_id = menu.id
            JOIN person ON person_order.person_id = person.id
        	WHERE person.gender = 'female'),
men AS( SELECT pizzeria.name AS pizzeria_name
        	FROM menu
            JOIN pizzeria ON menu.pizzeria_id = pizzeria.id
            JOIN person_order ON person_order.menu_id = menu.id
            JOIN person ON person_order.person_id = person.id
       		WHERE person.gender = 'male') 
SELECT * 
FROM (
    (SELECT * FROM fem EXCEPT SELECT * FROM men)
    UNION 
    (SELECT * FROM men EXCEPT SELECT * FROM fem))
ORDER BY pizzeria_name;