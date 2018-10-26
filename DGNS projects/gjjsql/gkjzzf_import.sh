#连接数据库
db2 connect to gapsdb user gapsusr using qwer1234

#导入业务数据
#db2 "import from /home/gapsv4/app/gksql/tbl_jzzf_xtcsb.txt of del insert into tbl_jzzf_xtcsb"

db2 "ALTER TABLE TBL_JZZF_HXLS ADD COLUMN SEQNO VARCHAR(20) NOT NULL DEFAULT '00000000'"
db2 "ALTER TABLE TBL_JZZF_HXLS DROP primary key"
db2 "ALTER TABLE TBL_JZZF_HXLS ADD primary key(RZRQ, RZGYLSH, SEQNO)"

db2 "commit"
