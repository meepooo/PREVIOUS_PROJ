drop table yyt_doctorfavo;
create table yyt_doctorfavo
(
	khh varchar(32),
	area_id varchar(9),
	area_name varchar(150),
	uid varchar(30),
	hosp_name varchar(150),
	dep_id varchar(30),
	dep_name varchar(150),
	doctor_id varchar(30),
	doctor_name varchar(150),
	doctor_zc varchar(30),
	doctor_zcname varchar(150),
	sex varchar(30),
	specialty varchar(1024),
	image varchar(150),
	pay_type varchar(10),
	pay_mode varchar(10),
	remark1 varchar(40),
	remark2 varchar(40)
) IN GAPS_DATA INDEX IN GAPS_INDEX ;

create unique index index_yyt_doctorfavo_1 on yyt_doctorfavo( KHH,AREA_ID,UID,DEP_ID,DOCTOR_ID );
comment on table  yyt_doctorfavo  is 'yyt_doctorfavo' ;
comment on column yyt_doctorfavo.KHH is '�ͻ���' ;
comment on column yyt_doctorfavo.AREA_ID is '����ID' ;
comment on column yyt_doctorfavo.AREA_NAME is '��������' ;
comment on column yyt_doctorfavo.UID is 'ҽԺID' ;
comment on column yyt_doctorfavo.HOSP_NAME is 'ҽԺ����' ;
comment on column yyt_doctorfavo.DEP_ID is '����ID' ;
comment on column yyt_doctorfavo.DEP_NAME is '��������' ;
comment on column yyt_doctorfavo.DOCTOR_ID is 'ҽ��ID' ;
comment on column yyt_doctorfavo.DOCTOR_NAME is 'ҽ������' ;
comment on column yyt_doctorfavo.DOCTOR_ZC is 'ҽ��ְ�ƴ���' ;
comment on column yyt_doctorfavo.DOCTOR_ZCNAME is 'ҽ��ְ��' ;
comment on column yyt_doctorfavo.SEX is '�Ա�' ;
comment on column yyt_doctorfavo.SPECIALTY is 'רҵ' ;
comment on column yyt_doctorfavo.IMAGE is 'ͼƬ��ַ' ;
comment on column yyt_doctorfavo.PAY_TYPE is '֧������' ;
comment on column yyt_doctorfavo.PAY_MODE is '֧����ʽ' ;
comment on column yyt_doctorfavo.REMARK1 is '��ע1' ;
comment on column yyt_doctorfavo.REMARK2 is '��ע2' ;
