drop table ywty_zjywbfq;
create table ywty_zjywbfq
(
	tblname varchar(30),
	ishistbl varchar(1),
	fqbz varchar(16),
	fqname varchar(30),
	rqbz varchar(16),
	tbsname varchar(30),
	indexname varchar(30),
	lastdealdate varchar(10),
	lastfqstartdate varchar(10),
	lastfqenddate varchar(10),
	histblname varchar(30),
	lastmvdate varchar(10),
	hismvbz varchar(16),
	hismvday int,
	yxbz varchar(1),
	remark1 varchar(80),
	remark2 varchar(80),
	remark3 varchar(80),
	remark4 varchar(80)
);

create unique index index_ywty_zjywbfq_1 on ywty_zjywbfq( TBLNAME );
comment on table  ywty_zjywbfq  is 'ywty_zjywbfq' ;
comment on column ywty_zjywbfq.TBLNAME is '表名' ;
comment on column ywty_zjywbfq.ISHISTBL is '历史表标识' ;
comment on column ywty_zjywbfq.FQBZ is '分区标识' ;
comment on column ywty_zjywbfq.FQNAME is '分区名称' ;
comment on column ywty_zjywbfq.RQBZ is '日期字段名' ;
comment on column ywty_zjywbfq.TBSNAME is '表空间名' ;
comment on column ywty_zjywbfq.INDEXNAME is '索引空间名' ;
comment on column ywty_zjywbfq.LASTDEALDATE is '上次处理日期' ;
comment on column ywty_zjywbfq.LASTFQSTARTDATE is '上次分区起始日期' ;
comment on column ywty_zjywbfq.LASTFQENDDATE is '上次分区结束日期' ;
comment on column ywty_zjywbfq.HISTBLNAME is '对应历史表名' ;
comment on column ywty_zjywbfq.LASTMVDATE is '上次数据移动日期' ;
comment on column ywty_zjywbfq.HISMVBZ is '数据迁移标识' ;
comment on column ywty_zjywbfq.HISMVDAY is '数据迁移时间间隔' ;
comment on column ywty_zjywbfq.YXBZ is '有效标识' ;
comment on column ywty_zjywbfq.REMARK1 is '备注1' ;
comment on column ywty_zjywbfq.REMARK2 is '备注2' ;
comment on column ywty_zjywbfq.REMARK3 is '备注3' ;
comment on column ywty_zjywbfq.REMARK4 is '备注4' ;

insert into ywty_zjywbfq values ( 'AGENT_DRLS_TMP', '0', 'month', '201710', 'PTRQ', 'AGENT_DATA', 'AGENT_INDEX', '20170101', '19991201', '19991231', 'AGENT_HIS_DRLS', '19991231', 'month', 3, '1', '', '', '', '' ) ;
