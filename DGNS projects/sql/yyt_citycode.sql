drop table yyt_citycode;
create table yyt_citycode
(
	area_id varchar(9),
	area_name varchar(40),
	area_level varchar(9),
	is_used varchar(9),
	hot varchar(9),
	parent_id varchar(9),
	remark1 varchar(40),
	remark2 varchar(40)
) IN GAPS_DATA INDEX IN GAPS_INDEX ;

create unique index index_yyt_citycode_1 on yyt_citycode( AREA_ID );
comment on table  yyt_citycode  is 'yyt_citycode' ;
comment on column yyt_citycode.AREA_ID is '区域ID' ;
comment on column yyt_citycode.AREA_NAME is '区域名称' ;
comment on column yyt_citycode.AREA_LEVEL is '区域级别' ;
comment on column yyt_citycode.IS_USED is '是否再用' ;
comment on column yyt_citycode.HOT is '是否热门' ;
comment on column yyt_citycode.PARENT_ID is '上级区域ID' ;
comment on column yyt_citycode.REMARK1 is '备注1' ;
comment on column yyt_citycode.REMARK2 is '备注2' ;
