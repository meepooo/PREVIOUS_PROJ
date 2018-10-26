drop table yyt_family;
create table yyt_family
(
	khh varchar(32),
	phone varchar(30),
	card varchar(30),
	card_type varchar(2),
	family_member_id varchar(30),
	truename varchar(150),
	sex varchar(30),
	birth varchar(10),
	social_card varchar(30),
	remark1 varchar(40),
	remark2 varchar(40)
);

create unique index index_yyt_family_1 on yyt_family( KHH,CARD,CARD_TYPE );
comment on table  yyt_family  is 'yyt_family' ;
comment on column yyt_family.KHH is '银行客户号' ;
comment on column yyt_family.PHONE is '手机号码' ;
comment on column yyt_family.CARD is '证件号码' ;
comment on column yyt_family.CARD_TYPE is '证件类型' ;
comment on column yyt_family.FAMILY_MEMBER_ID is '家庭成员ID' ;
comment on column yyt_family.TRUENAME is '客户名称' ;
comment on column yyt_family.SEX is '性别' ;
comment on column yyt_family.BIRTH is '出生日期' ;
comment on column yyt_family.SOCIAL_CARD is '社保卡号' ;
comment on column yyt_family.REMARK1 is '备注1' ;
comment on column yyt_family.REMARK2 is '备注2' ;
