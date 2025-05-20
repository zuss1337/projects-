INSERT INTO person_order(id,person_id,menu_id,order_date)
SELECT 
((select MAX(id) from person_order) + generated_id) AS id,person.id AS person_id,
(select id from menu where pizza_name = 'greek pizza') AS menu_id, 
'2022-02-25' AS order_date
FROM person
INNER JOIN generate_series
((select MIN(id) from person) ,(select MAX(id) from person)) AS generated_id
ON person.id = generated_id


