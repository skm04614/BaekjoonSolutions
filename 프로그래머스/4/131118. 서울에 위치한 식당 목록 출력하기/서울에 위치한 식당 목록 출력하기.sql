SELECT
  ri.rest_id,
  rest_name,
  food_type,
  favorites,
  address,
  ROUND(AVG(review_score), 2) AS score
FROM rest_info ri
JOIN rest_review rr
  ON ri.rest_id = rr.rest_id
WHERE address LIKE '서울%'
  AND review_score IS NOT NULL
GROUP BY rest_id
ORDER BY score DESC, favorites DESC