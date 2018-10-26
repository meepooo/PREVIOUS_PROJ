drop table tbl_jzzf_gwkinfo;
create table tbl_jzzf_gwkinfo
(
	czbm varchar(12) not null,
	trandate varchar(10),
	finano varchar(25),
	bankid varchar(20),
	bankname varchar(100),
	bgdeptcode varchar(12),
	bgdeptname varchar(100),
	fiscal varchar(4),
	transtype varchar(2),
	cardusername varchar(60),
	cardno varchar(32) not null,
	oldcardno varchar(32),
	idcardno varchar(18),
	mobilenum varchar(11),
	isused varchar(1),
	opendate varchar(10),
	openbankcode varchar(20),
	openbankname varchar(60),
	acctno varchar(32),
	busitype varchar(2),
	bankserialno varchar(32),
	operator varchar(60),
	billno varchar(20),
	state varchar(1),
	remark1 varchar(40),
	remark2 varchar(40),
	remark3 varchar(40),
	remark4 varchar(40),
	constraint P_K_TBL_JZZF_GWKINFO_1 primary key (CZBM,CARDNO)
);

create unique index index_tbl_jzzf_gwkinfo_1 on tbl_jzzf_gwkinfo( CZBM,CARDNO );
comment on table  tbl_jzzf_gwkinfo  is 'tbl_jzzf_gwkinfo' ;
comment on column tbl_jzzf_gwkinfo.CZBM is '财政局代码' ;
comment on column tbl_jzzf_gwkinfo.TRANDATE is '交易日期' ;
comment on column tbl_jzzf_gwkinfo.FINANO is '财政流水号' ;
comment on column tbl_jzzf_gwkinfo.BANKID is '银行标识号' ;
comment on column tbl_jzzf_gwkinfo.BANKNAME is '银行名称' ;
comment on column tbl_jzzf_gwkinfo.BGDEPTCODE is '预算单位代码' ;
comment on column tbl_jzzf_gwkinfo.BGDEPTNAME is '预算单位名称' ;
comment on column tbl_jzzf_gwkinfo.FISCAL is '年度' ;
comment on column tbl_jzzf_gwkinfo.TRANSTYPE is '业务类型' ;
comment on column tbl_jzzf_gwkinfo.CARDUSERNAME is '卡用户名称' ;
comment on column tbl_jzzf_gwkinfo.CARDNO is '卡号' ;
comment on column tbl_jzzf_gwkinfo.OLDCARDNO is '旧卡号' ;
comment on column tbl_jzzf_gwkinfo.IDCARDNO is '身份证号码' ;
comment on column tbl_jzzf_gwkinfo.MOBILENUM is '手机号码' ;
comment on column tbl_jzzf_gwkinfo.ISUSED is '是否可用' ;
comment on column tbl_jzzf_gwkinfo.OPENDATE is '开卡日期' ;
comment on column tbl_jzzf_gwkinfo.OPENBANKCODE is '开卡行代码' ;
comment on column tbl_jzzf_gwkinfo.OPENBANKNAME is '开卡行名称' ;
comment on column tbl_jzzf_gwkinfo.ACCTNO is '开卡银行帐号' ;
comment on column tbl_jzzf_gwkinfo.BUSITYPE is '业务类别' ;
comment on column tbl_jzzf_gwkinfo.BANKSERIALNO is '银行流水号' ;
comment on column tbl_jzzf_gwkinfo.OPERATOR is '业务人员' ;
comment on column tbl_jzzf_gwkinfo.BILLNO is '单据号' ;
comment on column tbl_jzzf_gwkinfo.STATE is '财政状态' ;
comment on column tbl_jzzf_gwkinfo.REMARK1 is '备注1' ;
comment on column tbl_jzzf_gwkinfo.REMARK2 is '备注2' ;
comment on column tbl_jzzf_gwkinfo.REMARK3 is '备注3' ;
comment on column tbl_jzzf_gwkinfo.REMARK4 is '备注4' ;
