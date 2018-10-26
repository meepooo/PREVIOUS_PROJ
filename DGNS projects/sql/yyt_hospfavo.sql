drop table yyt_hospfavo;
create table yyt_hospfavo
(
	khh varchar(32),
	area_id varchar(9),
	uid varchar(30),
	remark1 varchar(40),
	remark2 varchar(40)
) IN GAPS_DATA INDEX IN GAPS_INDEX ;

create unique index index_yyt_hospfavo_1 on yyt_hospfavo( KHH,AREA_ID,UID );
comment on table  yyt_hospfavo  is 'yyt_hospfavo' ;
comment on column yyt_hospfavo.KHH is '�ͻ���' ;
comment on column yyt_hospfavo.AREA_ID is '����ID' ;
comment on column yyt_hospfavo.UID is 'ҽԺID' ;
comment on column yyt_hospfavo.REMARK1 is '��ע1' ;
comment on column yyt_hospfavo.REMARK2 is '��ע2' ;
