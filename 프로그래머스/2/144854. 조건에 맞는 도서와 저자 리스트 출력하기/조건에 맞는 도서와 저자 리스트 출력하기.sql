SELECT
  book_id,
  author_name,
  DATE_FORMAT(published_date, "%Y-%m-%d") as published_date
FROM book
JOIN author
  ON book.author_id = author.author_id
WHERE category = '경제'
ORDER BY published_date ASC