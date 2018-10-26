drop table yyt_orderinfo;
create table yyt_orderinfo
(
	khh varchar(32),
	tran_date varchar(8),
	zflx varchar(1),
	qdbs varchar(10),
	ywlx varchar(10),
	acct_no varchar(32),
	tran_amt decimal(20,2),
	pay_amt decimal(20,2),
	discount_msg varchar(150),
	seq_no varchar(30),
	uid varchar(30),
	hosp_name varchar(150),
	dep_id varchar(30),
	dep_name varchar(150),
	doctor_id varchar(30),
	doctor_name varchar(150),
	doctor_zcname varchar(150),
	phone varchar(30),
	card varchar(30),
	card_type varchar(2),
	truename varchar(150),
	sex varchar(30),
	birth varchar(10),
	social_card varchar(30),
	detlid varchar(30),
	clinic_no varchar(30),
	yuyue_id varchar(30),
	order_no varchar(30),
	his_take_no varchar(30),
	to_date varchar(10),
	to_time varchar(40),
	begin_time varchar(10),
	end_time varchar(10),
	state varchar(10),
	msg varchar(150),
	pay_flag varchar(10),
	remark1 varchar(40),
	remark2 varchar(40)
) IN GAPS_DATA INDEX IN GAPS_INDEX ;

create unique index index_yyt_orderinfo_1 on yyt_orderinfo( ORDER_NO );
comment on table  yyt_orderinfo  is 'yyt_orderinfo' ;
comment on column yyt_orderinfo.KHH is '客户号' ;
comment on column yyt_orderinfo.TRAN_DATE is '交易日期' ;
comment on column yyt_orderinfo.ZFLX is '支付类型' ;
comment on column yyt_orderinfo.QDBS is '渠道标识' ;
comment on column yyt_orderinfo.YWLX is '业务类型' ;
comment on column yyt_orderinfo.ACCT_NO is '账号' ;
comment on column yyt_orderinfo.TRAN_AMT is '交易金额' ;
comment on column yyt_orderinfo.PAY_AMT is '实付金额' ;
comment on column yyt_orderinfo.DISCOUNT_MSG is '优惠说明' ;
comment on column yyt_orderinfo.SEQ_NO is '记账流水号' ;
comment on column yyt_orderinfo.UID is '医院ID' ;
comment on column yyt_orderinfo.HOSP_NAME is '医院名称' ;
comment on column yyt_orderinfo.DEP_ID is '科室ID' ;
comment on column yyt_orderinfo.DEP_NAME is '科室名称' ;
comment on column yyt_orderinfo.DOCTOR_ID is '医生ID' ;
comment on column yyt_orderinfo.DOCTOR_NAME is '医生名称' ;
comment on column yyt_orderinfo.DOCTOR_ZCNAME is '医生职称' ;
comment on column yyt_orderinfo.PHONE is '手机号码' ;
comment on column yyt_orderinfo.CARD is '证件号码' ;
comment on column yyt_orderinfo.CARD_TYPE is '证件类型' ;
comment on column yyt_orderinfo.TRUENAME is '姓名' ;
comment on column yyt_orderinfo.SEX is '性别' ;
comment on column yyt_orderinfo.BIRTH is '出生日期' ;
comment on column yyt_orderinfo.SOCIAL_CARD is '社保卡号' ;
comment on column yyt_orderinfo.DETLID is '号源ID' ;
comment on column yyt_orderinfo.CLINIC_NO is '就诊卡号/门诊编号' ;
comment on column yyt_orderinfo.YUYUE_ID is '预约ID' ;
comment on column yyt_orderinfo.ORDER_NO is '订单编号' ;
comment on column yyt_orderinfo.HIS_TAKE_NO is '取号密码' ;
comment on column yyt_orderinfo.TO_DATE is '就诊日期' ;
comment on column yyt_orderinfo.TO_TIME is '就诊时段' ;
comment on column yyt_orderinfo.BEGIN_TIME is '就诊开始时间' ;
comment on column yyt_orderinfo.END_TIME is '就诊结束时间' ;
comment on column yyt_orderinfo.STATE is '状态' ;
comment on column yyt_orderinfo.MSG is '状态说明' ;
comment on column yyt_orderinfo.PAY_FLAG is '支付标识' ;
comment on column yyt_orderinfo.REMARK1 is '备注1' ;
comment on column yyt_orderinfo.REMARK2 is '备注2' ;
