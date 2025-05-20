ALTER TABLE person ALTER COLUMN age TYPE numeric;
SELECT address, TRIM_SCALE(ROUND(MAX(age)-(MIN(age)/MAX(AGE)),2)) AS formula,
TRIM_SCALE(ROUND(AVG(AGE),2)) AS average,
TRIM_SCALE(ROUND(MAX(age)-(MIN(age)/MAX(AGE)),2))>=TRIM_SCALE(ROUND(AVG(AGE),2)) AS comparison
FROM person
GROUP BY address
ORDER BY address
