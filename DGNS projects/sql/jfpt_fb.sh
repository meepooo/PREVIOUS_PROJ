#1.	建表&修改表：
db2 -tvf  jfpt_create_alter.sql

#2.	插入基础数据：
db2 –tvf  jfpt_insert.sql

#3.	拷贝报文配置文件：
mv $HOME/etc/esb_field.cfg $HOME/etc/esb_field.cfg_`date +%Y%m%d%H%M%S`
cp esb_field.cfg   $HOME/etc/

#4.	拷贝动态连接库：
mv $HOME/shlib/AGT_PTGL-4.0.0.so $HOME/shlib/AGT_PTGL-4.0.0.so_`date +%Y%m%d%H%M%S`
mv $HOME/shlib/APP_COMPANY-4.0.0.so $HOME/shlib/APP_COMPANY-4.0.0.so_`date +%Y%m%d%H%M%S`
cp AGT_PTGL-4.0.0.so $HOME/shlib
cp APP_COMPANY-4.0.0.so $HOME/shlib
cp APP_SXF-4.0.0.so $HOME/shlib

#5.	建立动态库链接：
cd  $HOME/shlib
ln -s -f  AGT_PTGL-4.0.0.so  AGT_PTGL.so
ln -s -f  APP_COMPANY-4.0.0.so  APP_COMPANY.so
ln -s -f  APP_SXF-4.0.0.so  APP_SXF.so
SOAtool upd AGT_PTGL.so
SOAtool upd APP_COMPANY.so 
SOAtool upd APP_SXF.so
cd -

#6.	拷贝定时任务基础文件
cp jfpt700675.xml   $HOME/tools/systask
cp jfpt700679.xml   $HOME/tools/systask

#7.	在GAPS工具箱手动添加定时任务
#增加700675（对账）定时任务
#增加700679（清算）定时任务

#8.	建目录：
mkdir –p $HOME/file/jfpt/recv/jfxx

#9.	发布程序资源：
loadres.pl –f  GAPS20160713.tar.gz  -m 0 -t 60 –b

#10.	拷贝"GAPS日志查询服务"配置文件：
#mv $HOME/cfg/query.htm $HOME/cfg/query.htm_`date +%Y%m%d%H%M%S`
#cp query.htm $HOME/cfg

#11.	拷贝&启动cs_KKGLTJR服务程序：
cp cs_KKGLTJR.ini $HOME/etc
cp cs_KKGLTJR $HOME/bin
chmod +x $HOME/bin/cs_KKGLTJR
startcs KKGLTJR