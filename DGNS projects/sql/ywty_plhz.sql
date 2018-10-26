drop table ywty_plhz;
create table ywty_plhz
(
	stat varchar(1),
	pcbh varchar(32) not null,
	cpdm varchar(20),
	xybh varchar(20),
	sffg varchar(1),
	jyly varchar(4),
	jym varchar(6),
	jyrq varchar(8),
	jyxh varchar(32),
	jysj varchar(6),
	dwkhh varchar(20),
	dwmc varchar(100),
	lrjg varchar(12),
	lrgy varchar(10),
	lrrq varchar(8),
	fhgy varchar(10),
	fhrq varchar(9),
	qrgy varchar(10),
	qrrq varchar(8),
	scgy varchar(10),
	scrq varchar(8),
	dwzh varchar(35),
	dwnbzh varchar(35),
	hbdm varchar(3),
	zzbh varchar(38),
	yjzbs int,
	yjzje decimal(15,2),
	sxfbj varchar(1),
	yssxfje decimal(15,2),
	rzrq varchar(8),
	sjzbs int,
	sjzje decimal(15,2),
	sssxfje decimal(15,2),
	certno varchar(20),
	xmbm varchar(20),
	ywj varchar(60),
	jgwj varchar(60),
	zym varchar(5),
	zynr varchar(60),
	kkrq varchar(8),
	kkls varchar(32),
	tkrq varchar(8),
	tkls varchar(11),
	md5 varchar(32),
	by1 varchar(40),
	by2 varchar(40),
	by3 varchar(40),
	by4 varchar(40),
	by5 varchar(255),
	by6 varchar(255),
	constraint P_K_YWTY_PLHZ_1 primary key (PCBH)
);

comment on table  ywty_plhz  is 'ywty_plhz' ;
comment on column ywty_plhz.STAT is '状态' ;
comment on column ywty_plhz.PCBH is '批次编号' ;
comment on column ywty_plhz.CPDM is '产品代码' ;
comment on column ywty_plhz.XYBH is '协议编号' ;
comment on column ywty_plhz.SFFG is '收付标记' ;
comment on column ywty_plhz.JYLY is '交易来源' ;
comment on column ywty_plhz.JYM is '交易码' ;
comment on column ywty_plhz.JYRQ is '交易日期' ;
comment on column ywty_plhz.JYXH is '交易序号' ;
comment on column ywty_plhz.JYSJ is '交易时间' ;
comment on column ywty_plhz.DWKHH is '单位客户号' ;
comment on column ywty_plhz.DWMC is '单位名称' ;
comment on column ywty_plhz.LRJG is '录入机构' ;
comment on column ywty_plhz.LRGY is '录入柜员' ;
comment on column ywty_plhz.LRRQ is '录入日期' ;
comment on column ywty_plhz.FHGY is '复核柜员' ;
comment on column ywty_plhz.FHRQ is '复核日期' ;
comment on column ywty_plhz.QRGY is '确认柜员' ;
comment on column ywty_plhz.QRRQ is '确认日期' ;
comment on column ywty_plhz.SCGY is '删除柜员' ;
comment on column ywty_plhz.SCRQ is '删除日期' ;
comment on column ywty_plhz.DWZH is '单位账号' ;
comment on column ywty_plhz.DWNBZH is '单位内部账号' ;
comment on column ywty_plhz.HBDM is '货币代码' ;
comment on column ywty_plhz.ZZBH is '子账簿号' ;
comment on column ywty_plhz.YJZBS is '应记总笔数' ;
comment on column ywty_plhz.YJZJE is '应记总金额' ;
comment on column ywty_plhz.SXFBJ is '手续费标记' ;
comment on column ywty_plhz.YSSXFJE is '应收手续费总金额' ;
comment on column ywty_plhz.RZRQ is '入帐日期' ;
comment on column ywty_plhz.SJZBS is '实记总笔数' ;
comment on column ywty_plhz.SJZJE is '实记总金额' ;
comment on column ywty_plhz.SSSXFJE is '实收手续费总金额' ;
comment on column ywty_plhz.CERTNO is '凭证号' ;
comment on column ywty_plhz.XMBM is '项目编号' ;
comment on column ywty_plhz.YWJ is '源文件' ;
comment on column ywty_plhz.JGWJ is '结果文件' ;
comment on column ywty_plhz.ZYM is '摘要代码' ;
comment on column ywty_plhz.ZYNR is '摘要' ;
comment on column ywty_plhz.KKRQ is '扣款日期' ;
comment on column ywty_plhz.KKLS is '扣款流水' ;
comment on column ywty_plhz.TKRQ is '退款日期' ;
comment on column ywty_plhz.TKLS is '退款流水' ;
comment on column ywty_plhz.MD5 is 'MD5校验' ;
comment on column ywty_plhz.BY1 is '备用字段1' ;
comment on column ywty_plhz.BY2 is '备用字段2' ;
comment on column ywty_plhz.BY3 is '备用字段3' ;
comment on column ywty_plhz.BY4 is '备用字段4' ;
comment on column ywty_plhz.BY5 is '备用字段5' ;
comment on column ywty_plhz.BY6 is '备用字段6' ;
