-- Удаляем таблицу
DROP TABLE IF EXISTS paths;

-- Создаем таблицу для хранения путей между узлами
CREATE TABLE paths (
    point1 VARCHAR(1) NOT NULL, -- Город отправления
    point2 VARCHAR(1) NOT NULL, -- Город назначения
    cost INTEGER NOT NULL       -- Стоимость пути между ними
);

-- Заполняем таблицу 
INSERT INTO paths (point1, point2, cost) 
VALUES ('a', 'b', 10), ('b', 'a', 10),
    ('a', 'c', 15), ('c', 'a', 15),
    ('a', 'd', 20), ('d', 'a', 20),
    ('b', 'c', 35), ('c', 'b', 35),
    ('b', 'd', 25), ('d', 'b', 25),
    ('c', 'd', 30), ('d', 'c', 30);
	
-- Поиск всех туров с их стоимостью
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
    WHERE paths.point2 <> ALL(tour_paths.tour)
), complete_tours AS (
    -- Завершаем туры, возвращаясь в 'a'
    SELECT 
        total_cost + paths.cost AS total_cost,
        tour || ARRAY['a'] AS tour
    FROM tour_paths
    JOIN paths ON tour_paths.point2 = paths.point1
    WHERE paths.point2 = 'a' AND array_length(tour, 1) = 4
)
-- Вывод всех маршрутов, отсортированных по стоимости и маршруту
SELECT total_cost,tour
FROM complete_tours
ORDER BY total_cost, tour;
