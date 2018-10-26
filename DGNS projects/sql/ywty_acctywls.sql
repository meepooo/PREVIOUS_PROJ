drop table ywty_acctywls;
create table ywty_acctywls
(
	ptrq varchar(8),
	ptls int,
	zjlsh varchar(32),
	ptsj varchar(6),
	rzbz varchar(1),
	jylx varchar(1),
	yptls int,
	jyjg varchar(16),
	jygy varchar(16),
	qdbs varchar(3),
	zdsbbh varchar(8),
	yybs varchar(8),
	cpdm varchar(16),
	ywbh varchar(16),
	jydm varchar(8),
	dwbh varchar(32),
	mssq varchar(8),
	smsq varchar(8),
	msnm varchar(80),
	mslt varchar(8),
	wkdt varchar(8),
	wktm varchar(6),
	opdt varchar(8),
	srtm varchar(6),
	alcn varchar(7),
	jdbz varchar(1),
	zhlx varchar(2),
	yhzh varchar(32),
	dfzh varchar(32),
	jyje decimal(16,2),
	sxf decimal(16,2),
	pcbh int,
	jyxym varchar(8),
	jyxyxx varchar(60),
	jyzt varchar(1),
	remark1 varchar(40),
	remark2 varchar(40)
);

create unique index index_ywty_acctywls_1 on ywty_acctywls( PTRQ,PTLS );
alter table ywty_acctywls add constraint ywty_acctywls_key primary key(PTRQ,PTLS);
comment on table  ywty_acctywls  is 'ywty_acctywls' ;
comment on column ywty_acctywls.PTRQ is '平台日期' ;
comment on column ywty_acctywls.PTLS is '平台流水号' ;
comment on column ywty_acctywls.ZJLSH is '主机流水号' ;
comment on column ywty_acctywls.PTSJ is '平台时间' ;
comment on column ywty_acctywls.RZBZ is '入帐标志' ;
comment on column ywty_acctywls.JYLX is '交易类型' ;
comment on column ywty_acctywls.YPTLS is '原平台流水号' ;
comment on column ywty_acctywls.JYJG is '交易机构' ;
comment on column ywty_acctywls.JYGY is '交易柜员' ;
comment on column ywty_acctywls.QDBS is '渠道标识' ;
comment on column ywty_acctywls.ZDSBBH is '终端设备编号' ;
comment on column ywty_acctywls.YYBS is '应用标识' ;
comment on column ywty_acctywls.CPDM is '产品代码' ;
comment on column ywty_acctywls.YWBH is '业务编号' ;
comment on column ywty_acctywls.JYDM is '交易代码' ;
comment on column ywty_acctywls.DWBH is '单位编号' ;
comment on column ywty_acctywls.MSSQ is '流程序号' ;
comment on column ywty_acctywls.SMSQ is '子流程序号' ;
comment on column ywty_acctywls.MSNM is '子流程名称' ;
comment on column ywty_acctywls.MSLT is '前置任务序号列表' ;
comment on column ywty_acctywls.WKDT is '计划执行日期' ;
comment on column ywty_acctywls.WKTM is '计划执行时间' ;
comment on column ywty_acctywls.OPDT is '实际执行日期' ;
comment on column ywty_acctywls.SRTM is '实际执行时间' ;
comment on column ywty_acctywls.ALCN is '预警次数' ;
comment on column ywty_acctywls.JDBZ is '借贷标志' ;
comment on column ywty_acctywls.ZHLX is '帐户类型' ;
comment on column ywty_acctywls.YHZH is '银行帐号' ;
comment on column ywty_acctywls.DFZH is '对方帐号' ;
comment on column ywty_acctywls.JYJE is '交易金额' ;
comment on column ywty_acctywls.SXF is '手续费' ;
comment on column ywty_acctywls.PCBH is '批次编号' ;
comment on column ywty_acctywls.JYXYM is '交易响应码' ;
comment on column ywty_acctywls.JYXYXX is '交易响应信息' ;
comment on column ywty_acctywls.JYZT is '交易状态' ;
comment on column ywty_acctywls.REMARK1 is '备注1' ;
comment on column ywty_acctywls.REMARK2 is '备注2' ;
