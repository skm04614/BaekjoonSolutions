SELECT
  p.product_code,
  SUM(price * sales_amount) as sales
FROM product p
JOIN offline_sale os
  ON p.product_id = os.product_id
GROUP BY product_code
ORDER BY sales DESC, product_code ASC