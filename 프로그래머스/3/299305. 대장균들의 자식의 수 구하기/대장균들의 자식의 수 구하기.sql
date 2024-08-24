SELECT
  p.id AS id,
  COUNT(c.id) AS child_count
FROM ecoli_data p
LEFT JOIN ecoli_data c
  ON p.id = c.parent_id
GROUP BY id