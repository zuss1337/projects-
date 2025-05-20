INSERT INTO currency VALUES (100, 'EUR', 0.85, '2022-01-01 13:29');
INSERT INTO currency VALUES (100, 'EUR', 0.79, '2022-01-08 13:29');

SELECT
    COALESCE("user".name, 'not defined') AS name,
    COALESCE("user".lastname, 'not defined') AS lastname,
    agg_data.name AS currency_name,
    TRIM_SCALE(agg_data.money * COALESCE(agg_data.rate_min, agg_data.rate_max)) AS currency_in_usd
FROM (
    SELECT 	balance.user_id, currency.id, currency.name, balance.money,
			( SELECT currency.rate_to_usd 
			  FROM currency
			  WHERE currency.id = balance.currency_id
			  AND currency.updated < balance.updated
			  ORDER BY currency.updated DESC 
			  LIMIT 1
			) AS rate_min,
			(SELECT currency.rate_to_usd 
			 FROM currency
			 WHERE currency.id = balance.currency_id
			 AND currency.updated > balance.updated
			 ORDER BY currency.updated
			 LIMIT 1
			) AS rate_max
    FROM 
        currency
    JOIN 
        balance ON currency.id = balance.currency_id
    GROUP BY
		balance.updated,
		balance.money,
        balance.currency_id,
        balance.user_id,
	    currency.name,
	    currency.id
    ORDER BY rate_min DESC, rate_max
) AS agg_data
LEFT JOIN 
    "user" ON agg_data.user_id = "user".id
ORDER BY  name DESC,  lastname, currency_name;
