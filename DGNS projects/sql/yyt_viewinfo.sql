drop table yyt_viewinfo;
create table yyt_viewinfo
(
	khh varchar(32),
	area_id varchar(9),
	uid varchar(30),
	dep_id varchar(30),
	doctor_id varchar(30),
	truename varchar(150),
	score varchar(10),
	review varchar(300),
	eva_date varchar(8),
	grade_time varchar(14),
	review_id varchar(20),
	state varchar(10),
	msg varchar(150),
	remark1 varchar(40),
	remark2 varchar(40)
) IN GAPS_DATA INDEX IN GAPS_INDEX ;

create unique index index_yyt_viewinfo_1 on yyt_viewinfo( KHH,EVA_DATE,REVIEW_ID );
comment on table  yyt_viewinfo  is 'yyt_viewinfo' ;
comment on column yyt_viewinfo.KHH is '客户号' ;
comment on column yyt_viewinfo.AREA_ID is '城市ID' ;
comment on column yyt_viewinfo.UID is '医院ID' ;
comment on column yyt_viewinfo.DEP_ID is '科室ID' ;
comment on column yyt_viewinfo.DOCTOR_ID is '医生ID' ;
comment on column yyt_viewinfo.TRUENAME is '评论人' ;
comment on column yyt_viewinfo.SCORE is '评分' ;
comment on column yyt_viewinfo.REVIEW is '评论' ;
comment on column yyt_viewinfo.EVA_DATE is '评价日期' ;
comment on column yyt_viewinfo.GRADE_TIME is '评分时间' ;
comment on column yyt_viewinfo.REVIEW_ID is '评论ID' ;
comment on column yyt_viewinfo.STATE is '状态' ;
comment on column yyt_viewinfo.MSG is '状态说明' ;
comment on column yyt_viewinfo.REMARK1 is '备注1' ;
comment on column yyt_viewinfo.REMARK2 is '备注2' ;
