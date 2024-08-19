SELECT
  YEAR(sales_date) AS year,
  MONTH(sales_date) AS month,
  gender,
  COUNT(DISTINCT ui.user_id) AS users
FROM user_info ui
JOIN online_sale os
  ON ui.user_id = os.user_id
WHERE gender IS NOT NULL
GROUP BY year, month, gender
ORDER BY year, month, gender
