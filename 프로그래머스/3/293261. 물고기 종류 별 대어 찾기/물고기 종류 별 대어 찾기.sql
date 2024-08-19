WITH fish AS (
  SELECT
    id,
    fni.fish_type,
    fish_name,
    length
  FROM fish_name_info fni
  JOIN fish_info fi
    ON fni.fish_type = fi.fish_type
)

SELECT
  id,
  fish_name,
  f.length
FROM fish f
JOIN (
  SELECT
    fish_type,
    MAX(length) AS length
  FROM fish
  GROUP BY fish_type
  ) derived
  ON derived.fish_type = f.fish_type
    AND derived.length = f.length
