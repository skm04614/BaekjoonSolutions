SELECT
  COUNT(fish_type) AS fish_count,
  MAX(length) AS max_length,
  fish_type
FROM fish_info fi
GROUP BY fish_type
HAVING AVG(COALESCE(length, 10)) >= 33
ORDER BY fish_type