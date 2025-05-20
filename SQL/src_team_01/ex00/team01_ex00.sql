WITH latest_currency AS (
    SELECT 
        currency.id,
        currency.name,
        currency.rate_to_usd,
        currency.updated,
        ROW_NUMBER() OVER (PARTITION BY currency.id ORDER BY currency.updated DESC) AS rn
    FROM currency
)

SELECT
    COALESCE("user".name, 'not defined') AS name,
    COALESCE("user".lastname, 'not defined') AS lastname,
    balance.type,
    SUM(balance.money) AS volume,
    COALESCE(latest_currency.name, 'not defined') AS currency_name,
    COALESCE(latest_currency.rate_to_usd, 1) AS rate_to_usd,
    (SUM(balance.money) * COALESCE(latest_currency.rate_to_usd, 1)) AS total_volume_in_usd
FROM "user"
RIGHT JOIN balance ON "user".id = balance.user_id
LEFT JOIN latest_currency ON balance.currency_id = latest_currency.id AND latest_currency.rn = 1
GROUP BY "user".name, "user".lastname, balance.type, latest_currency.name, latest_currency.rate_to_usd
ORDER BY 1 DESC, 2, 3 ASC;