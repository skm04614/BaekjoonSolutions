WITH
RECURSIVE hours AS (
  SELECT 0 as hour
  UNION ALL
  SELECT hour + 1 FROM hours
  WHERE hour < 23
),
out_hours AS (
SELECT
  HOUR(datetime) AS hour,
  COUNT(*) AS count
FROM animal_outs o
GROUP BY hour
)

SELECT
  h.hour,
  COALESCE(count, 0) AS count
FROM out_hours o
RIGHT JOIN hours h
  ON h.hour = o.hour