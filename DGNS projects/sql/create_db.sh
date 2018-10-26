
cd sql

db2set DB2CODEPAGE=1386
db2set DB2TERRITORY=CN
db2set DB2AUTOSTART=YES

#���ݿ����Ա��64λdb2ʵ��db2inst9
db2set db2codepage=1386 -I gapsinst
db2 terminate

export DBNAME=gapsdb
export DBPATH=/home/gapsinst/gapsdata

mkdir $DBPATH
echo "db2 CREATE db $DBNAME ON $DBPATH USING CODESET GBK TERRITORY CN COLLATE USING SYSTEM DFT_EXTENT_SZ 64"

db2 CREATE db $DBNAME ON $DBPATH USING CODESET GBK TERRITORY CN COLLATE USING SYSTEM DFT_EXTENT_SZ 64 

#������ռ�
db2 connect to gapsdb

db2 -td@ -vf ./create_tablespace.sql -z ./create_tablespace.log

#��gapsusr�û������ռ����Ȩ��
db2 "GRANT USE OF TABLESPACE AGENT_DATA TO USER gapsusr"
db2 "GRANT USE OF TABLESPACE AGENT_INDEX TO USER gapsusr"
db2 "GRANT USE OF TABLESPACE APP_DATA TO USER gapsusr"
db2 "GRANT USE OF TABLESPACE APP_INDEX TO USER gapsusr"

db2 connect reset

db2 terminate
