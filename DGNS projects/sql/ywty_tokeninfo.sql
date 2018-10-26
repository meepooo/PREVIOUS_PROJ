drop table ywty_tokeninfo;
create table ywty_tokeninfo
(
	ljbs varchar(8),
	tokenid varchar(100),
	cid varchar(16),
	digest varchar(100),
	effecttime varchar(14),
	expiretime varchar(14),
	ljbsname varchar(60),
	remark1 varchar(40),
	remark2 varchar(40)
) IN GAPS_DATA INDEX IN GAPS_INDEX ;

create unique index index_ywty_tokeninfo_1 on ywty_tokeninfo( LJBS,TOKENID );
comment on table  ywty_tokeninfo  is 'ywty_tokeninfo' ;
comment on column ywty_tokeninfo.LJBS is '联机标识' ;
comment on column ywty_tokeninfo.TOKENID is '令牌标识' ;
comment on column ywty_tokeninfo.CID is '渠道ID' ;
comment on column ywty_tokeninfo.DIGEST is '消息摘要' ;
comment on column ywty_tokeninfo.EFFECTTIME is '授权起始时间' ;
comment on column ywty_tokeninfo.EXPIRETIME is '授权结束时间' ;
comment on column ywty_tokeninfo.LJBSNAME is '联机标识名称' ;
comment on column ywty_tokeninfo.REMARK1 is '备注1' ;
comment on column ywty_tokeninfo.REMARK2 is '备注2' ;
