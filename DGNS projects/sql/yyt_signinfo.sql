drop table yyt_signinfo;
create table yyt_signinfo
(
	khh varchar(32),
	phone varchar(30),
	card varchar(30),
	card_type varchar(2),
	truename varchar(150),
	social_card varchar(150),
	date varchar(10),
	qdbs varchar(10),
	remark1 varchar(40),
	remark2 varchar(40)
) IN GAPS_DATA INDEX IN GAPS_INDEX ;

create unique index index_yyt_signinfo_1 on yyt_signinfo( KHH );
comment on table  yyt_signinfo  is 'yyt_signinfo' ;
comment on column yyt_signinfo.KHH is '银行客户号' ;
comment on column yyt_signinfo.PHONE is '手机号码' ;
comment on column yyt_signinfo.CARD is '证件号码' ;
comment on column yyt_signinfo.CARD_TYPE is '证件类型' ;
comment on column yyt_signinfo.TRUENAME is '客户名称' ;
comment on column yyt_signinfo.SOCIAL_CARD is '社保号' ;
comment on column yyt_signinfo.DATE is '注册日期' ;
comment on column yyt_signinfo.QDBS is '渠道标识' ;
comment on column yyt_signinfo.REMARK1 is '备注1' ;
comment on column yyt_signinfo.REMARK2 is '备注2' ;
