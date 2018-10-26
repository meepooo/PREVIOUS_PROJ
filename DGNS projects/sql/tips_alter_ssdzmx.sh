echo 数据库连接：
db2 connect to $DBALIAS user $DBUSER using $DBPASS

echo 修改表：
db2 "alter table tips_ssdzmx drop constraint  pk_tips_ssdzmx"
db2 "alter table tips_ssdzmx alter column orientrustdate set NOT NULL"
db2 "reorg table tips_ssdzmx"
db2 "alter table tips_ssdzmx add constraint pk_tips_ssdzmx PRIMARY KEY ( chkdate ,  chkacctord ,  curpackno ,  paybkcode ,  payeebankno ,  oritaxorgcode , orientrustdate, oritrano )"
