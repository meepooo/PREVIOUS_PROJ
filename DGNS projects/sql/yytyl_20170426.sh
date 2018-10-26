#连接数据库
db2 connect to gapsdb user gapsusr using qwer1234

#1.	插入基础数据：
db2 –tvf  yytyl_20170426.sql

db2 connect reset

#2.	拷贝动态连接库：
mv $HOME/shlib/AGT_PTGL-4.0.0.so $HOME/shlib/AGT_PTGL-4.0.0.so_`date +%Y%m%d%H%M%S`
cp ./shlib/AGT_PTGL-4.0.0.so $HOME/shlib

#3.	刷新态库链接库：
cd  $HOME/shlib
SOAtool upd AGT_PTGL.so
cd -

#4.	拷贝定时任务基础文件
cp ./tools/systask/yytyl700296_276.xml   $HOME/tools/systask

#5.	发布程序资源：
loadres.pl –f  GAPS20170426.tar.gz  -m 0 -t 60 –b
