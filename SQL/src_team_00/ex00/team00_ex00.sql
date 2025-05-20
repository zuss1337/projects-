-- Удаляем таблицу, если она уже существует
DROP TABLE IF EXISTS paths;

-- Создаем таблицу для хранения путей между узлами
CREATE TABLE IF NOT EXISTS paths (
    point1 VARCHAR(1) NOT NULL, -- Город отправления
    point2 VARCHAR(1) NOT NULL, -- Город назначения
    cost INTEGER NOT NULL       -- Стоимость пути между ними
);

-- Заполняем таблицу данными
INSERT INTO paths (point1, point2, cost) VALUES
    ('a', 'b', 10), ('b', 'a', 10),
    ('a', 'c', 15), ('c', 'a', 15),
    ('a', 'd', 20), ('d', 'a', 20),
    ('b', 'c', 35), ('c', 'b', 35),
    ('b', 'd', 25), ('d', 'b', 25),
    ('c', 'd', 30), ('d', 'c', 30);

-- Поиск минимального тура
WITH RECURSIVE tour_paths (point1, point2, total_cost, tour) AS (
    -- Начальный шаг: пути из 'a' с начальной стоимостью
    SELECT 
        point1, 
        point2, 
        cost AS total_cost, 
        ARRAY[point1, point2]::VARCHAR[] AS tour
    FROM paths
    WHERE point1 = 'a'

    UNION ALL

    -- Рекурсия: добавляем узлы, не возвращаясь в уже посещенные
    SELECT 
        tour_paths.point1,
        paths.point2,
        tour_paths.total_cost + paths.cost AS total_cost,
        tour_paths.tour || paths.point2 AS tour
    FROM tour_paths 
    JOIN paths ON tour_paths.point2 = paths.point1
    WHERE paths.point2 <> ALL(tour_paths.tour) -- Избегаем повторного посещения узлов
), 
complete_tours AS (
    -- Завершаем туры, возвращаясь в 'a'
    SELECT 
        total_cost + paths.cost AS total_cost,
        tour || ARRAY['a'] AS tour
    FROM tour_paths 
    JOIN paths ON tour_paths.point2 = paths.point1
    WHERE paths.point2 = 'a' AND array_length(tour, 1) = 4 -- Все узлы посещены
), 
minimal_cost AS (
    -- Находим минимальную стоимость тура
    SELECT MIN(total_cost) AS min_cost
    FROM complete_tours
)
-- Вывод всего
SELECT 
    total_cost,
    tour
FROM complete_tours
WHERE total_cost = (SELECT min_cost FROM minimal_cost)
ORDER BY tour;