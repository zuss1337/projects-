CREATE VIEW v_price_with_discount AS
SELECT person.name, pizza_name, price, ROUND(price-price*0.1) AS discount_price
FROM menu
LEFT JOIN person_order ON menu.id = person_order.menu_id
LEFT JOIN person ON person_order.person_id = person.id
ORDER BY name, pizza_name
