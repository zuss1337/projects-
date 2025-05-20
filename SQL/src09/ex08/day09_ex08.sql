CREATE OR REPLACE FUNCTION fnc_fibonacci(pstop INTEGER DEFAULT 10) 
RETURNS TABLE(num BIGINT) 
AS $$
WITH RECURSIVE fib(num1, num2) AS (
    SELECT 0, 1
    UNION ALL
    SELECT num2, num1 + num2 
    FROM fib 
    WHERE num2 < pstop
)
SELECT num1 AS num FROM fib;
$$ 
LANGUAGE SQL;