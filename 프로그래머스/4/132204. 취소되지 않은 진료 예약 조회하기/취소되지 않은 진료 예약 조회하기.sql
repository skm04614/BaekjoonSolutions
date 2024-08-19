SELECT
  apnt_no,
  pt_name,
  a.pt_no,
  a.mcdp_cd,
  dr_name,
  apnt_ymd
FROM appointment a
JOIN patient p
  ON a.pt_no = p.pt_no
JOIN doctor d
  ON a.mddr_id = d.dr_id
WHERE apnt_cncl_yn = 'N'
  AND DATE_FORMAT(apnt_ymd, '%Y-%m-%d') = '2022-04-13'
  AND a.mcdp_cd = 'CS'
ORDER BY apnt_ymd
