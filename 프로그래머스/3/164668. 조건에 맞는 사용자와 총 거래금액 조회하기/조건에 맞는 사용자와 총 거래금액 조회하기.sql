-- 코드를 입력하세요
SELECT
  user_id,
  nickname,
  SUM(price) AS total_sales
FROM used_goods_board b
JOIN used_goods_user u
  ON writer_id = user_id
WHERE status = 'DONE'
GROUP BY user_id
HAVING total_sales >= 700000
ORDER BY total_sales