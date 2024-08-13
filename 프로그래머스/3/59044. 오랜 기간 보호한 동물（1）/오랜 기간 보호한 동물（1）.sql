SELECT
  ai.name,
  ai.datetime
FROM animal_ins ai
LEFT OUTER JOIN animal_outs o
  ON ai.animal_id = o.animal_id
WHERE o.animal_id is NULL
ORDER BY ai.datetime ASC
LIMIT 3