SELECT
  fo.product_id,
  fp.product_name,
  SUM(fo.amount * fp.price) AS total_sales
FROM food_product fp
JOIN food_order fo
  ON fo.product_id = fp.product_id
WHERE YEAR(fo.produce_date) = 2022
  AND MONTH(fo.produce_date) = 5
GROUP BY product_id
ORDER BY total_sales DESC, product_id ASC