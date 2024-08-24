WITH best_rest AS
(
SELECT
  food_type,
  MAX(favorites) AS favorites
FROM rest_info
GROUP BY food_type
)

SELECT
  ri.food_type,
  ri.rest_id,
  ri.rest_name,
  ri.favorites
FROM rest_info ri
JOIN best_rest br
  ON ri.food_type = br.food_type
  AND ri.favorites = br.favorites
GROUP BY food_type
ORDER BY food_type DESC