DROP FUNCTION IF EXISTS fnc_persons_female;
DROP FUNCTION IF EXISTS fnc_persons_male;
DROP FUNCTION IF EXISTS fnc_persons;

CREATE OR REPLACE FUNCTION fnc_persons(pgender varchar DEFAULT 'female')
RETURNS TABLE ( id person.id%TYPE, name person.name%TYPE, age person.age%TYPE,
        		gender person.gender%TYPE, address person.address%TYPE) AS $$
SELECT id, name, age, gender, address FROM person WHERE person.gender = pgender;
$$ LANGUAGE sql;


