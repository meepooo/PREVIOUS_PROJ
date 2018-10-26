#0.预定义
DATE_TODAY=`date +%Y%m%d`
LOG_FILE=${HOME}/log/${DATE_TODAY}/pldf_${DATE_TODAY}.log
LOG_FILE_ERR=${HOME}/log/${DATE_TODAY}/pldf_${DATE_TODAY}_err.log
echo "====================发布开始====================" 1>> ${LOG_FILE} 2>> ${LOG_FILE_ERR}

#1.数据库连接：
db2 connect to $DBALIAS user $DBUSER using $DBPASS

#2.插入基础数据：
echo "====================插入基础数据====================" 1>> ${LOG_FILE} 2>> ${LOG_FILE_ERR}
db2 -tvf  $HOME/app/sql/batch_dsdf_detail.sql 1>> ${LOG_FILE} 2>> ${LOG_FILE_ERR}
db2 -tvf  $HOME/app/sql/batch_dsdf_detail_his.sql 1>> ${LOG_FILE} 2>> ${LOG_FILE_ERR}
db2 -tvf  $HOME/app/sql/agent_batch_info.sql 1>> ${LOG_FILE} 2>> ${LOG_FILE_ERR}
db2 -tvf  $HOME/app/sql/agent_fee_detail.sql 1>> ${LOG_FILE} 2>> ${LOG_FILE_ERR}
db2 -tvf  $HOME/app/sql/agent_batch_clear.sql 1>> ${LOG_FILE} 2>> ${LOG_FILE_ERR}
db2 -tvf  $HOME/app/sql/batch_0042000.sql 1>> ${LOG_FILE} 2>> ${LOG_FILE_ERR}
db2 import from agent_jfxm_pldsdf.txt of del insert into agent_jfxm 1>> ${LOG_FILE} 2>> ${LOG_FILE_ERR}
db2 import from agent_csys_pldsdf.txt of del insert into agent_csys 1>> ${LOG_FILE} 2>> ${LOG_FILE_ERR}
db2 import from app_cpxx_pldsdf.txt of del insert into app_cpxx 1>> ${LOG_FILE} 2>> ${LOG_FILE_ERR}
db2 import from app_cpsxfkz_pldsdf.txt of del insert into app_cpsxfkz 1>> ${LOG_FILE} 2>> ${LOG_FILE_ERR}
db2 "update app_cskz set jdz='1' where csjz='K_BATCH_SJTJ_ITVL'"

db2 connect reset

#3.建目录：
echo "====================建目录====================" 1>> ${LOG_FILE} 2>> ${LOG_FILE_ERR}
mkdir -p $HOME/file/pldsdf 1>> ${LOG_FILE} 2>> ${LOG_FILE_ERR}

echo "====================发布结束====================" 1>> ${LOG_FILE} 2>> ${LOG_FILE_ERR}
