SELECT
  animal_type,
  COALESCE(name, 'No name') as name,
  sex_upon_intake
FROM animal_ins
ORDER BY animal_id ASC