WITH review_cnt AS
(
SELECT
  mp.member_id,
  member_name,
  COUNT(member_name) AS cnt
FROM member_profile mp
JOIN rest_review rr
  ON mp.member_id = rr.member_id
GROUP BY member_name
)

SELECT
  member_name,
  review_text,
  DATE_FORMAT(review_date, '%Y-%m-%d') AS review_date
FROM review_cnt rc
JOIN rest_review rr
  ON rc.member_id = rr.member_id
WHERE cnt = (SELECT MAX(cnt) FROM review_cnt)
ORDER BY review_date ASC, review_text ASC