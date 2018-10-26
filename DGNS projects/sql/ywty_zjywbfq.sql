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
comment on column ywty_zjywbfq.TBLNAME is '����' ;
comment on column ywty_zjywbfq.ISHISTBL is '��ʷ���ʶ' ;
comment on column ywty_zjywbfq.FQBZ is '������ʶ' ;
comment on column ywty_zjywbfq.FQNAME is '��������' ;
comment on column ywty_zjywbfq.RQBZ is '�����ֶ���' ;
comment on column ywty_zjywbfq.TBSNAME is '��ռ���' ;
comment on column ywty_zjywbfq.INDEXNAME is '�����ռ���' ;
comment on column ywty_zjywbfq.LASTDEALDATE is '�ϴδ�������' ;
comment on column ywty_zjywbfq.LASTFQSTARTDATE is '�ϴη�����ʼ����' ;
comment on column ywty_zjywbfq.LASTFQENDDATE is '�ϴη�����������' ;
comment on column ywty_zjywbfq.HISTBLNAME is '��Ӧ��ʷ����' ;
comment on column ywty_zjywbfq.LASTMVDATE is '�ϴ������ƶ�����' ;
comment on column ywty_zjywbfq.HISMVBZ is '����Ǩ�Ʊ�ʶ' ;
comment on column ywty_zjywbfq.HISMVDAY is '����Ǩ��ʱ����' ;
comment on column ywty_zjywbfq.YXBZ is '��Ч��ʶ' ;
comment on column ywty_zjywbfq.REMARK1 is '��ע1' ;
comment on column ywty_zjywbfq.REMARK2 is '��ע2' ;
comment on column ywty_zjywbfq.REMARK3 is '��ע3' ;
comment on column ywty_zjywbfq.REMARK4 is '��ע4' ;

insert into ywty_zjywbfq values ( 'AGENT_DRLS_TMP', '0', 'month', '201710', 'PTRQ', 'AGENT_DATA', 'AGENT_INDEX', '20170101', '19991201', '19991231', 'AGENT_HIS_DRLS', '19991231', 'month', 3, '1', '', '', '', '' ) ;
