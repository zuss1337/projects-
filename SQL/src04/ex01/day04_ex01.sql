select name
from v_person_female 
UNION 
select name 
from v_person_male
ORDER BY name
