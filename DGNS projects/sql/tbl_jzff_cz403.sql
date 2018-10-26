drop table tbl_jzzf_cz403;
create table tbl_jzzf_cz403
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
	constraint P_K_tbl_jzzf_cz403_1 primary key (CZBM,CARDNO)
);

create unique index index_tbl_jzzf_cz403_1 on tbl_jzzf_cz403( CZBM,CARDNO );
comment on table  tbl_jzzf_cz403  is 'tbl_jzzf_cz403' ;
comment on column tbl_jzzf_cz403.CZBM is '财政局代码' ;
comment on column tbl_jzzf_cz403.TRANDATE is '交易日期' ;
comment on column tbl_jzzf_cz403.FINANO is '财政流水号' ;
comment on column tbl_jzzf_cz403.BANKID is '银行标识号' ;
comment on column tbl_jzzf_cz403.BANKNAME is '银行名称' ;
comment on column tbl_jzzf_cz403.BGDEPTCODE is '预算单位代码' ;
comment on column tbl_jzzf_cz403.BGDEPTNAME is '预算单位名称' ;
comment on column tbl_jzzf_cz403.FISCAL is '年度' ;
comment on column tbl_jzzf_cz403.TRANSTYPE is '业务类型' ;
comment on column tbl_jzzf_cz403.CARDUSERNAME is '卡用户名称' ;
comment on column tbl_jzzf_cz403.CARDNO is '卡号' ;
comment on column tbl_jzzf_cz403.OLDCARDNO is '旧卡号' ;
comment on column tbl_jzzf_cz403.IDCARDNO is '身份证号码' ;
comment on column tbl_jzzf_cz403.MOBILENUM is '手机号码' ;
comment on column tbl_jzzf_cz403.ISUSED is '是否可用' ;
comment on column tbl_jzzf_cz403.OPENDATE is '开卡日期' ;
comment on column tbl_jzzf_cz403.OPENBANKCODE is '开卡行代码' ;
comment on column tbl_jzzf_cz403.OPENBANKNAME is '开卡行名称' ;
comment on column tbl_jzzf_cz403.ACCTNO is '开卡银行帐号' ;
comment on column tbl_jzzf_cz403.BUSITYPE is '业务类别' ;
comment on column tbl_jzzf_cz403.BANKSERIALNO is '银行流水号' ;
comment on column tbl_jzzf_cz403.OPERATOR is '业务人员' ;
comment on column tbl_jzzf_cz403.BILLNO is '单据号' ;
comment on column tbl_jzzf_cz403.STATE is '财政状态' ;
comment on column tbl_jzzf_cz403.REMARK1 is '备注1' ;
comment on column tbl_jzzf_cz403.REMARK2 is '备注2' ;
comment on column tbl_jzzf_cz403.REMARK3 is '备注3' ;
comment on column tbl_jzzf_cz403.REMARK4 is '备注4' ;



insert into tbl_jzzf_cz403 select * from  tbl_jzzf_gwkinfo;