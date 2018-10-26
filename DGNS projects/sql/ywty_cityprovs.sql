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
comment on column ywty_cityprovs.CID is '渠道ID' ;
comment on column ywty_cityprovs.CHNAME is '渠道名称' ;
comment on column ywty_cityprovs.PROVSID is '省份ID' ;
comment on column ywty_cityprovs.PROVSNAME is '省份名称' ;
comment on column ywty_cityprovs.CITYID is '城市ID' ;
comment on column ywty_cityprovs.CITYNAME is '城市名称' ;
comment on column ywty_cityprovs.ISHOT is '是否热点城市' ;
comment on column ywty_cityprovs.REMARK1 is '备注1' ;
comment on column ywty_cityprovs.REMARK2 is '备注2' ;
