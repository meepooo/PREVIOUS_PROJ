echo ���ݿ����ӣ�
db2 connect to $DBALIAS user $DBUSER using $DBPASS

echo �޸ı�
db2 "alter table tips_ssdzmx drop constraint  pk_tips_ssdzmx"
db2 "alter table tips_ssdzmx alter column orientrustdate set NOT NULL"
db2 "reorg table tips_ssdzmx"
db2 "alter table tips_ssdzmx add constraint pk_tips_ssdzmx PRIMARY KEY ( chkdate ,  chkacctord ,  curpackno ,  paybkcode ,  payeebankno ,  oritaxorgcode , orientrustdate, oritrano )"
