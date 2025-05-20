SELECT pizza_name, name AS pizzeria_name 
FROM menu AS m
JOIN pizzeria ON pizzeria.id = pizzeria_id;

SET ENABLE_SEQSCAN TO OFF;
EXPLAIN ANALYZE
SELECT pizza_name, name AS pizzeria_name
FROM menu AS m
JOIN pizzeria ON pizzeria.id = pizzeria_id;