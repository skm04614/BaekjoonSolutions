WITH
frontend AS (
  SELECT
    SUM(code) AS frontend
  FROM skillcodes
  WHERE category = 'Front End'
),
python AS (
  SELECT
    code AS python
  FROM skillcodes
  WHERE name = 'Python'
),
cs AS (
  SELECT
    code AS cs
  FROM skillcodes
  WHERE name = 'C#'
)

SELECT
  *
FROM (
SELECT
  CASE
    WHEN (skill_code & python AND skill_code & frontend) THEN 'A'
    WHEN (skill_code & cs) THEN 'B'
    WHEN (skill_code & frontend) THEN 'C'
  END AS grade,
  id,
  email
FROM developers d
JOIN python
JOIN frontend
JOIN cs
) AS derived
WHERE grade IS NOT NULL
ORDER BY grade, id