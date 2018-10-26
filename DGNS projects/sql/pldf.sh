#0.预定义
DATE_TODAY=`date +%Y%m%d`
LOG_FILE=${HOME}/log/${DATE_TODAY}/pldf_${DATE_TODAY}.log
LOG_FILE_ERR=${HOME}/log/${DATE_TODAY}/pldf_${DATE_TODAY}_err.log
echo "======================beg======================="

#1.数据库连接
db2 connect to $DBALIAS user $DBUSER using $DBPASS

#2.插入数据
echo "======================insert===================="
db2 -tvf  $HOME/app/sql/batch_dsdf_detail.sql
db2 -tvf  $HOME/app/sql/batch_dsdf_detail_his.sql
db2 -tvf  $HOME/app/sql/agent_batch_info.sql
db2 -tvf  $HOME/app/sql/agent_fee_detail.sql
db2 -tvf  $HOME/app/sql/agent_batch_clear.sql
db2 -tvf  $HOME/app/sql/batch_0042000.sql
db2 -tvf  $HOME/app/sql/pldf.sql

db2 connect reset;
db2 terminate;

echo "======================end======================="
