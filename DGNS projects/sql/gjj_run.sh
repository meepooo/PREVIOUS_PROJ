#连接数据库
db2 connect to gapsdb user gapsusr using qwer1234

#建立业务基础表
db2 -tvf GJJ.sql

#导入业务数据
db2 "import from TBL_GJJ_GDZH.txt of del insert into TBL_GJJ_GDZH"


db2 "commit"

db2 "terminate"

cp esb_field.cfg  /home/gapsv4/etc/
