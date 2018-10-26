#连接数据库
db2 connect to gapsdb user gapsusr

#导入业务数据
db2 "import from app_cpxx.txt of del insert into app_cpxx"
db2 "import from app_dwcpxy.txt of del insert into app_dwcpxy"
db2 "import from app_dwxx.txt of del insert into app_dwxx"

db2 "commit"
