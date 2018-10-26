#连接数据库
db2 connect to gapsdb user gapsusr using qwer1234

#建立业务基础表
db2 -tvf app_db2.sql
db2 -tvf agent_db2.sql
db2 -tvf tamcx2.1_basic_db2.sql
db2 -tvf tamcx2.1_app_db2.sql
db2 -tvf tamcx2.1_bots_db2.sql
db2 -tvf tamcx2.1_dsf_db2.sql
db2 -tvf tamcx2.1_btoo_db2.sql

#建立业务表
db2 -tvf ywty_xyywzt.sql
db2 -tvf ywty_busi_dz.sql
db2 -tvf ywty_cityprovs.sql
db2 -tvf ywty_tokeninfo.sql
db2 -tvf yxt_order.sql
db2 -tvf yyt_citycode.sql
db2 -tvf yyt_doctorfavo.sql
db2 -tvf yyt_family.sql
db2 -tvf yyt_hospcode.sql
db2 -tvf yyt_hospfavo.sql
db2 -tvf yyt_orderinfo.sql
db2 -tvf yyt_signinfo.sql
db2 -tvf yyt_viewinfo.sql
db2 -tvf yxt_cinemas.sql
db2 -tvf yxt_facilitys.sql
db2 -tvf yxt_tickets.sql
db2 -tvf yxt_order.sql
db2 -tvf zjyw_orderqry.sql

db2 -tvf tamcx2.1_dgtab_20150911.sql

#导入业务数据
db2 "import from /home/gapsv4/app/sql/app_cpxx.txt of del insert into app_cpxx"
db2 "import from /home/gapsv4/app/sql/app_dwcpxy.txt of del insert into app_dwcpxy"
db2 "import from /home/gapsv4/app/sql/app_dwxx.txt of del insert into app_dwxx"
db2 "import from /home/gapsv4/app/sql/app_jyxx.txt of del insert into app_jyxx"
db2 "import from /home/gapsv4/app/sql/app_txaqxx.txt of del insert into app_txaqxx"
db2 "import from /home/gapsv4/app/sql/app_yyxx.txt of del insert into app_yyxx"
db2 "import from /home/gapsv4/app/sql/ywty_tokeninfo.txt of del insert into ywty_tokeninfo"

#db2 -tvf tamcx2.1_dgtab_20150902.sql
#db2 -tvf tamcx2.1_dgyxt_20150902.sql
#db2 -tvf tamcx2.1_dgLsTab_20150907.sql

db2 "delete from t_dict where dict_kind in ('yyt_ywlx', 'yxt_ywlx', 'zflx', 'yyt_state', 'yxt_state')"
db2 "import from /home/gapsv4/app/sql/t_dict.txt of del insert into t_dict"

db2 "delete from t_send_server"
db2 "import from /home/gapsv4/app/sql/t_send_server.txt of del insert into t_send_server"

db2 "delete from app_qdxx"
db2 "import from /home/gapsv4/app/sql/app_qdxx.txt of del insert into app_qdxx"

db2 "delete from t_report"
db2 "import from /home/gapsv4/app/sql/t_report.txt of del insert into t_report"

db2 "delete from t_report_cond"
db2 "import from /home/gapsv4/app/sql/t_report_cond.txt of del insert into t_report_cond"

db2 "delete from t_org"
db2 "import from /home/gapsv4/app/sql/t_org.txt of del insert into t_org"

db2 "delete from yyt_citycode"
db2 "import from /home/gapsv4/app/sql/yyt_citycode.txt of del insert into yyt_citycode"

db2 "commit"
