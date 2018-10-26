drop table yyt_family_card;
create table yyt_family_card
(
	khh varchar(32),
	card varchar(30),
	card_type varchar(2),
	truename varchar(150),
	client_card varchar(30),
	client_card_name varchar(150),
	client_card_id varchar(30),
	unit_id varchar(30),
	unit_name varchar(150),
	city_code varchar(9),
	area_id varchar(9),
	is_check varchar(1),
	remark1 varchar(40),
	remark2 varchar(40)
);

create unique index index_yyt_family_card_1 on yyt_family_card( KHH, CARD, CARD_TYPE, UNIT_ID);
comment on table  yyt_family_card  is 'yyt_family_card' ;
comment on column yyt_family_card.KHH is '���пͻ���' ;
comment on column yyt_family_card.CARD is '֤������' ;
comment on column yyt_family_card.CARD_TYPE is '֤������' ;
comment on column yyt_family_card.TRUENAME is '�ͻ�����' ;
comment on column yyt_family_card.CLIENT_CARD is '���￨��' ;
comment on column yyt_family_card.CLIENT_CARD_NAME is '���￨����' ;
comment on column yyt_family_card.CLIENT_CARD_ID is '���￨ID' ;
comment on column yyt_family_card.UNIT_ID is 'ҽԺID' ;
comment on column yyt_family_card.UNIT_NAME is 'ҽԺ����' ;
comment on column yyt_family_card.CITY_CODE is '���д���' ;
comment on column yyt_family_card.AREA_ID is '����ID' ;
comment on column yyt_family_card.IS_CHECK is '�Ƿ�ǿ��' ;
comment on column yyt_family_card.REMARK1 is '��ע1' ;
comment on column yyt_family_card.REMARK2 is '��ע2' ;
