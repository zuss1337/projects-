-- Session #1
BEGIN;

-- Session #2
BEGIN;

-- Session #1
UPDATE pizzeria SET rating = 100 WHERE id = 10;

-- Session #2
UPDATE pizzeria SET rating = 1 WHERE id = 11;

-- Session #1
UPDATE pizzeria SET rating = 100 WHERE id = 11;

-- Session #2
UPDATE pizzeria SET rating = 1 WHERE id = 10;

-- Session #1
COMMIT;

-- Session #2
COMMIT;
