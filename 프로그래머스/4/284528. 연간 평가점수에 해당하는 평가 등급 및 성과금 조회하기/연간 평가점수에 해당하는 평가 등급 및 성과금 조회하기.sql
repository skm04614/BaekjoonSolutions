WITH emp AS (
SELECT
  hg.emp_no,
  emp_name,
  AVG(score) AS score,
  sal
FROM hr_grade hg
JOIN hr_employees he
  ON hg.emp_no = he.emp_no
GROUP BY emp_no
)

SELECT
  emp_no,
  emp_name,
  CASE
    WHEN score >= 96 THEN 'S'
    WHEN score >= 90 THEN 'A'
    WHEN score >= 80 THEN 'B'
    ELSE 'C'
  END AS grade,
  CASE
    WHEN score >= 96 THEN sal * 0.20
    WHEN score >= 90 THEN sal * 0.15
    WHEN score >= 80 THEN sal * 0.10
    ELSE 0
  END AS bonus
FROM emp
ORDER BY emp_no