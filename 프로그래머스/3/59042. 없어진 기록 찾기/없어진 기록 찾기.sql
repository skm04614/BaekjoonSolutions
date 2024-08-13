SELECT
  o.animal_id,
  o.name
FROM animal_ins i
RIGHT OUTER JOIN animal_outs o
  ON i.animal_id = o.animal_id
WHERE i.animal_id IS NULL
ORDER BY o.animal_id