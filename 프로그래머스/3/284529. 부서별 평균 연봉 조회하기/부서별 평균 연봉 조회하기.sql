SELECT
  d.dept_id,
  dept_name_en,
  ROUND(AVG(sal), 0) AS avg_sal
FROM hr_department d
JOIN hr_employees e
  ON d.dept_id = e.dept_id
GROUP BY dept_id
ORDER BY avg_sal DESC