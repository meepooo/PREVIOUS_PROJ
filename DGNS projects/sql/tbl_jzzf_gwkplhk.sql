drop table tbl_jzzf_gwkplhk;
create table tbl_jzzf_gwkplhk
(
	czbm varchar(12),
	trandate varchar(10),
	finano varchar(25),
	bankid varchar(20),
	bgdeptcode varchar(12),
	totalserialnum varchar(20),
	billno varchar(20),
	totalamt decimal(16,2),
	count int,
	cardno varchar(32),
	cardname varchar(60),
	paymoney decimal(16,2),
	bankserialno varchar(32),
	operator varchar(60),
	state varchar(1),
	remark1 varchar(40),
	remark2 varchar(40),
	remark3 varchar(40),
	remark4 varchar(40)
);

create index index_tbl_jzzf_gwkplhk_1 on tbl_jzzf_gwkplhk( CZBM,BILLNO );
comment on table  tbl_jzzf_gwkplhk  is 'tbl_jzzf_gwkplhk' ;
comment on column tbl_jzzf_gwkplhk.CZBM is '财政局代码' ;
comment on column tbl_jzzf_gwkplhk.TRANDATE is '交易日期' ;
comment on column tbl_jzzf_gwkplhk.FINANO is '财政流水号' ;
comment on column tbl_jzzf_gwkplhk.BANKID is '银行标识号' ;
comment on column tbl_jzzf_gwkplhk.BGDEPTCODE is '预算单位代码' ;
comment on column tbl_jzzf_gwkplhk.TOTALSERIALNUM is '汇总编号' ;
comment on column tbl_jzzf_gwkplhk.BILLNO is '授权支付凭证号' ;
comment on column tbl_jzzf_gwkplhk.TOTALAMT is '授权支付令总金额' ;
comment on column tbl_jzzf_gwkplhk.COUNT is '交易记录笔数' ;
comment on column tbl_jzzf_gwkplhk.CARDNO is '卡号' ;
comment on column tbl_jzzf_gwkplhk.CARDNAME is '用户名称' ;
comment on column tbl_jzzf_gwkplhk.PAYMONEY is '交易金额' ;
comment on column tbl_jzzf_gwkplhk.BANKSERIALNO is '银行流水号' ;
comment on column tbl_jzzf_gwkplhk.OPERATOR is '业务人员' ;
comment on column tbl_jzzf_gwkplhk.STATE is '财政状态' ;
comment on column tbl_jzzf_gwkplhk.REMARK1 is '备注1' ;
comment on column tbl_jzzf_gwkplhk.REMARK2 is '备注2' ;
comment on column tbl_jzzf_gwkplhk.REMARK3 is '备注3' ;
comment on column tbl_jzzf_gwkplhk.REMARK4 is '备注4' ;
