drop table tbl_jzzf_gwktmp;
create table tbl_jzzf_gwktmp
(
	czbm varchar(12),
	bgdeptcode varchar(12),
	bgdeptname varchar(100),
	cardusername varchar(60),
	cardno varchar(32),
	idcardno varchar(18),
	mobilenum varchar(11),
	isused varchar(1),
	opendate varchar(10),
	openbankcode varchar(20),
	openbankname varchar(60),
	acctno varchar(32),
	state varchar(1),
	bankcode varchar(40)
);

comment on table  tbl_jzzf_gwktmp  is 'tbl_jzzf_gwktmp' ;
comment on column tbl_jzzf_gwktmp.CZBM is '财政局代码' ;
comment on column tbl_jzzf_gwktmp.BGDEPTCODE is '预算单位代码' ;
comment on column tbl_jzzf_gwktmp.BGDEPTNAME is '预算单位名称' ;
comment on column tbl_jzzf_gwktmp.CARDUSERNAME is '卡用户名称' ;
comment on column tbl_jzzf_gwktmp.CARDNO is '卡号' ;
comment on column tbl_jzzf_gwktmp.IDCARDNO is '身份证号码' ;
comment on column tbl_jzzf_gwktmp.MOBILENUM is '手机号码' ;
comment on column tbl_jzzf_gwktmp.ISUSED is '是否可用' ;
comment on column tbl_jzzf_gwktmp.OPENDATE is '开卡日期' ;
comment on column tbl_jzzf_gwktmp.OPENBANKCODE is '开卡行代码' ;
comment on column tbl_jzzf_gwktmp.OPENBANKNAME is '开卡行名称' ;
comment on column tbl_jzzf_gwktmp.ACCTNO is '开卡银行帐号' ;
comment on column tbl_jzzf_gwktmp.STATE is '财政状态' ;
