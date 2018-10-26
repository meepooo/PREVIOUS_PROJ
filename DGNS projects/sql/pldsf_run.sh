#连接数据库
db2 connect to gapsdb user gapsusr using qwer1234

#建立业务基础表
db2 -tvf ywty_plhz.sql
db2 -tvf ywty_plmx.sql

#导入业务数据
db2 "import from /home/gapsv4/app/sql/app_cpxx.txt of del insert into app_cpxx"
db2 "import from /home/gapsv4/app/sql/app_dwcpxy.txt of del insert into app_dwcpxy"
db2 "import from /home/gapsv4/app/sql/app_dwxx.txt of del insert into app_dwxx"

db2 "commit"

db2 "terminate"

cp esb_field.cfg  /home/gapsv4/etc/
cp pldsf700599.xml /home/gapsv4/tools/systask/

cp DRC_GETMD5-4.0.0.so  /home/gapsv4/shlib/
cp SCOMM_ESB_XMLCOV-4.0.0.so  /home/gapsv4/shlib/
cp SDATA_Datacasecmp-4.0.0.so  /home/gapsv4/shlib/

cd ~/shlib
ln -s DRC_GETMD5-4.0.0.so DRC_GETMD5.so
ln -s SCOMM_ESB_XMLCOV-4.0.0.so SCOMM_ESB_XMLCOV.so
ln -s SDATA_Datacasecmp-4.0.0.so SDATA_Datacasecmp.so

cd ~/file
mkdir pldsf
