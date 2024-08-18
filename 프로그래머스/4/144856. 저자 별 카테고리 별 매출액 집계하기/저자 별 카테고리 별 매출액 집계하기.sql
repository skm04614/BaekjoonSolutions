-- 코드를 입력하세요
SELECT
  a.author_id,
  a.author_name,
  category,
  SUM(sales * price) AS total_sales
FROM BOOK_SALES bs
JOIN BOOK b
  ON bs.book_id = b.book_id
JOIN AUTHOR a
  ON a.author_id = b.author_id
WHERE YEAR(sales_date) = 2022
  AND MONTH(sales_date) = 1
GROUP BY author_id, category
ORDER BY author_id ASC, category DESC