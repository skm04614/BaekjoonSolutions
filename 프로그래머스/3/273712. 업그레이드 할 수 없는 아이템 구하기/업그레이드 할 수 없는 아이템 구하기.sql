SELECT
  src.item_id,
  i.item_name,
  i.rarity
FROM item_tree src
LEFT JOIN item_tree tgt
  ON src.item_id = tgt.parent_item_id
JOIN item_info i
  ON i.item_id = src.item_id
WHERE tgt.item_id IS NULL
ORDER BY item_id DESC