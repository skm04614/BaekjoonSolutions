SELECT
  animal_id,
  name,
  CASE
    WHEN sex_upon_intake LIKE '%neutered%' THEN 'O'
    WHEN sex_upon_intake LIKE '%spayed%' THEN 'O'
    ELSE 'X'
  END AS '중성화'
FROM animal_ins