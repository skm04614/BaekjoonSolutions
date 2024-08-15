WITH
flavor_orders AS
(
SELECT * FROM july
UNION ALL
SELECT * FROM first_half
GROUP BY flavor
)

SELECT
  flavor
FROM flavor_orders
GROUP BY flavor
ORDER BY SUM(total_order) DESC
LIMIT 3