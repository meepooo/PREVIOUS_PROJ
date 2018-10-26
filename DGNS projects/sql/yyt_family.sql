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
comment on column yyt_family.KHH is '���пͻ���' ;
comment on column yyt_family.PHONE is '�ֻ�����' ;
comment on column yyt_family.CARD is '֤������' ;
comment on column yyt_family.CARD_TYPE is '֤������' ;
comment on column yyt_family.FAMILY_MEMBER_ID is '��ͥ��ԱID' ;
comment on column yyt_family.TRUENAME is '�ͻ�����' ;
comment on column yyt_family.SEX is '�Ա�' ;
comment on column yyt_family.BIRTH is '��������' ;
comment on column yyt_family.SOCIAL_CARD is '�籣����' ;
comment on column yyt_family.REMARK1 is '��ע1' ;
comment on column yyt_family.REMARK2 is '��ע2' ;
