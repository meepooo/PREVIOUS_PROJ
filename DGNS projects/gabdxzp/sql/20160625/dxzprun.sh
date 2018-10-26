db2 connect to gapsdb user gapsusr using qwer1234

db2 -tvf gabdxzp_db2.sql
db2 -tvf gabdxzp_comment.sql
db2 -tvf gabdxzp_InitData1.sql
db2 -tvf gabdxzp_InitData.sql
db2 -tvf gabdxzp_hmhh.sql
db2 -tvf gab_dxzpkhh_hxjyxxjl.sql
db2 -tvf sfck_view.sql
db2 -tvf dxzp_cxjy_view.sql

#db2 "delete from APP_CSKZ where cstj='040' "
#db2 "import from dxzp_cskz.txt of del insert into app_cskz"

db2 "commit"
