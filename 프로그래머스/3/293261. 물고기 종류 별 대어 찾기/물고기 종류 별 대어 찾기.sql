WITH tmp AS (
SELECT
  fish_info.id,
  fish_type,
  MAX(length) AS length
FROM fish_info
GROUP BY fish_type
)

SELECT
  id,
  fish_name,
  length
FROM tmp t
JOIN fish_name_info fni
  ON t.fish_type = fni.fish_type