SELECT
  user_id,
  nickname,
  CONCAT(
    city,
    ' ',
    street_address1,
    ' ',
    street_address2
  ) AS '전체주소',
  CONCAT(
    SUBSTR(tlno, 1, 3),
    '-',
    SUBSTR(tlno, 4, 4),
    '-',
    SUBSTR(tlno, 8, 4)
  ) AS '전화번호'
FROM used_goods_board b
JOIN used_goods_user u
  ON writer_id = user_id
GROUP BY user_id
HAVING COUNT(*) >= 3
ORDER BY user_id DESC