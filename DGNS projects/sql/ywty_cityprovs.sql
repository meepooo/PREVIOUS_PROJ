drop table ywty_cityprovs;
create table ywty_cityprovs
(
	cid varchar(9),
	chname varchar(40),
	provsid varchar(6),
	provsname varchar(40),
	cityid varchar(6),
	cityname varchar(40),
	ishot varchar(1),
	remark1 varchar(40),
	remark2 varchar(40)
) IN GAPS_DATA INDEX IN GAPS_INDEX ;

create unique index index_ywty_cityprovs_1 on ywty_cityprovs( CID,PROVSID,CITYID );
comment on table  ywty_cityprovs  is 'ywty_cityprovs' ;
comment on column ywty_cityprovs.CID is '����ID' ;
comment on column ywty_cityprovs.CHNAME is '��������' ;
comment on column ywty_cityprovs.PROVSID is 'ʡ��ID' ;
comment on column ywty_cityprovs.PROVSNAME is 'ʡ������' ;
comment on column ywty_cityprovs.CITYID is '����ID' ;
comment on column ywty_cityprovs.CITYNAME is '��������' ;
comment on column ywty_cityprovs.ISHOT is '�Ƿ��ȵ����' ;
comment on column ywty_cityprovs.REMARK1 is '��ע1' ;
comment on column ywty_cityprovs.REMARK2 is '��ע2' ;
