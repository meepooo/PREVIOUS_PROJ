#连接数据库
db2 connect to gapsdb user gapsusr using qwer1234

db2 "update t_org set inner_org_id=trim('100')||trim(org_id) where org_level = '1' "
db2 "update t_org set inner_org_id=trim('100')||trim(above_org_id)||trim(org_id) where org_level = '2'"
db2 "commit"
