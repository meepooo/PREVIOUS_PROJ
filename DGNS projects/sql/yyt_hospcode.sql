drop table yyt_hospcode;
create table yyt_hospcode
(
	unit_alias varchar(150),
	unit_id varchar(30),
	unit_name varchar(150),
	image varchar(150),
	address varchar(150),
	area_id varchar(9),
	unit_level varchar(9),
	unit_spell varchar(150),
	phone varchar(30),
	payment varchar(10),
	remark1 varchar(40),
	remark2 varchar(40)
) IN GAPS_DATA INDEX IN GAPS_INDEX ;

create unique index index_yyt_hospcode_1 on yyt_hospcode( UNIT_ID );
comment on table  yyt_hospcode  is 'yyt_hospcode' ;
comment on column yyt_hospcode.UNIT_ALIAS is '��λ����' ;
comment on column yyt_hospcode.UNIT_ID is '��λ���' ;
comment on column yyt_hospcode.UNIT_NAME is '��λ����' ;
comment on column yyt_hospcode.IMAGE is 'ͼƬ��ַ' ;
comment on column yyt_hospcode.ADDRESS is '��λ��ַ' ;
comment on column yyt_hospcode.AREA_ID is '���д���' ;
comment on column yyt_hospcode.UNIT_LEVEL is 'ҽԺ����' ;
comment on column yyt_hospcode.UNIT_SPELL is '��λƴд' ;
comment on column yyt_hospcode.PHONE is '��ϵ�绰' ;
comment on column yyt_hospcode.PAYMENT is '֧����ʶ' ;
comment on column yyt_hospcode.REMARK1 is '��ע1' ;
comment on column yyt_hospcode.REMARK2 is '��ע2' ;
