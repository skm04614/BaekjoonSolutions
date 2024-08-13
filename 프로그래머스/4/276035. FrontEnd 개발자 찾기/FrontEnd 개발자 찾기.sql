WITH frontend AS (
    SELECT *
    FROM skillcodes
    WHERE category = 'Front End'
)
SELECT DISTINCT id, email, first_name, last_name
FROM frontend f
JOIN developers d
WHERE f.code & d.skill_code
ORDER BY id ASC