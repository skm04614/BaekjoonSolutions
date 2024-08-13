WITH unavailable_cars AS (
SELECT
  DISTINCT car_id
FROM car_rental_company_rental_history
WHERE NOT (end_date < '2022-11-01' OR start_date > '2022-11-30')
)

SELECT
  c.car_id,
  c.car_type,
  ROUND(30 * c.daily_fee * (100 - discount_rate) / 100) AS fee
FROM car_rental_company_car c
LEFT JOIN unavailable_cars uc
  ON c.car_id = uc.car_id
JOIN car_rental_company_discount_plan dp
  ON dp.car_type = c.car_type
WHERE c.car_type IN ('SUV', '세단')
  AND duration_type = '30일 이상'
  AND uc.car_id IS NULL
HAVING fee BETWEEN 500000 AND 1999999
ORDER BY
  fee DESC,
  car_type ASC,
  car_id DESC