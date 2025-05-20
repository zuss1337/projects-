CREATE OR REPLACE FUNCTION fnc_person_visits_and_eats_on_date(
pperson varchar DEFAULT 'Dmitriy',
pprice numeric DEFAULT 500,
pdate date DEFAULT '2022-01-08')
RETURNS TABLE (name varchar) AS $$
BEGIN
RETURN QUERY
SELECT pizzeria.name
FROM person_visits
LEFT JOIN pizzeria ON person_visits.pizzeria_id = pizzeria.id
LEFT JOIN menu ON  pizzeria.id = menu.pizzeria_id
LEFT JOIN person ON person_visits.person_id = person.id 
WHERE person.name = pperson 
AND visit_date = pdate AND price < pprice;
END;
$$ LANGUAGE plpgsql;

