WITH
unavailable_car_ids AS (
  SELECT DISTINCT
    car_id
  FROM car_rental_company_rental_history
  WHERE '2022-10-16' BETWEEN start_date and end_date
)

SELECT DISTINCT
  car_id,
  CASE
    WHEN car_id IN (SELECT car_id FROM unavailable_car_ids) THEN '대여중'
    ELSE '대여 가능'
  END AS availability
FROM car_rental_company_rental_history
ORDER BY car_id DESC