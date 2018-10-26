drop table ywty_plmx;
create table ywty_plmx
(
	pcbh varchar(32) not null,
	pcnbxh int not null,
	ywls varchar(32),
	ptls varchar(32),
	jyls varchar(32),
	yxj varchar(1),
	ywlx varchar(8),
	ywzl varchar(6),
	yhbj varchar(1),
	hkyl varchar(1),
	tcydbj varchar(1),
	jjbj varchar(1),
	htbh varchar(32),
	qxrq varchar(8),
	khyhzh varchar(32),
	khyhzhmc varchar(70),
	zhkhh varchar(14),
	zhkhhmc varchar(100),
	yjjyje decimal(15,2),
	sxfbj varchar(1),
	sxfzh varchar(32),
	sxfje decimal(15,2),
	sjjyje decimal(15,2),
	sjsxfje decimal(15,2),
	zym varchar(5),
	lrgy varchar(10),
	lrrq varchar(8),
	ptrq varchar(8),
	ptsj varchar(6),
	whrq varchar(8),
	whgy varchar(10),
	fy varchar(62),
	bz varchar(62),
	zjlx varchar(2),
	zjhm varchar(20),
	zjyxrq varchar(10),
	sex varchar(1),
	csrq varchar(10),
	address varchar(70),
	fzjg varchar(22),
	yzbm varchar(7),
	phoneno varchar(15),
	yybj varchar(1),
	yyrq varchar(8),
	yysj varchar(6),
	dsfrq varchar(8),
	dsfls varchar(11),
	dsfjylx varchar(20),
	dsfjym varchar(20),
	dsfxym varchar(12),
	dsfxyxx varchar(150),
	dsfjyzt varchar(1),
	dsfdzbj varchar(1),
	zjjzgy varchar(10),
	zjjzrq varchar(8),
	zjjzls varchar(32),
	zjgyls varchar(32),
	khzfls varchar(32),
	zjxym varchar(12),
	zjxyxx varchar(150),
	zjjyzt varchar(1),
	zjdzbj varchar(1),
	czgy varchar(10),
	czrq varchar(8),
	czls varchar(11),
	fscs int,
	jyxym varchar(12),
	jyxyxx varchar(150),
	jyzt varchar(1),
	by1 varchar(40),
	by2 varchar(40),
	by3 varchar(40),
	by4 varchar(40),
	by5 varchar(255),
	by6 varchar(255),
	constraint P_K_YWTY_PLMX_1 primary key (PCBH, PCNBXH)
);

comment on table  ywty_plmx  is 'ywty_plmx' ;
comment on column ywty_plmx.PCBH is '批次编号' ;
comment on column ywty_plmx.PCNBXH is '批次内部序号' ;
comment on column ywty_plmx.YWLS is '业务流水号' ;
comment on column ywty_plmx.PTLS is '平台流水号' ;
comment on column ywty_plmx.JYLS is '交易流水' ;
comment on column ywty_plmx.YXJ is '优先级' ;
comment on column ywty_plmx.YWLX is '业务类型' ;
comment on column ywty_plmx.YWZL is '业务子类' ;
comment on column ywty_plmx.YHBJ is '银行标记' ;
comment on column ywty_plmx.HKYL is '汇款邮路' ;
comment on column ywty_plmx.TCYDBJ is '同城异地标记' ;
comment on column ywty_plmx.JJBJ is '加急标记' ;
comment on column ywty_plmx.HTBH is '合同编号' ;
comment on column ywty_plmx.QXRQ is '款项日期' ;
comment on column ywty_plmx.KHYHZH is '客户银行账号' ;
comment on column ywty_plmx.KHYHZHMC is '客户银行账号户名' ;
comment on column ywty_plmx.ZHKHH is '客户银行账号开户行号' ;
comment on column ywty_plmx.ZHKHHMC is '客户银行账号开户行行名' ;
comment on column ywty_plmx.YJJYJE is '应记交易金额' ;
comment on column ywty_plmx.SXFBJ is '手续费标记' ;
comment on column ywty_plmx.SXFZH is '手续费账号' ;
comment on column ywty_plmx.SXFJE is '手续费金额' ;
comment on column ywty_plmx.SJJYJE is '实记交易金额' ;
comment on column ywty_plmx.SJSXFJE is '实收手续费金额' ;
comment on column ywty_plmx.ZYM is '摘要代码' ;
comment on column ywty_plmx.LRGY is '录入柜员' ;
comment on column ywty_plmx.LRRQ is '录入日期' ;
comment on column ywty_plmx.PTRQ is '平台日期' ;
comment on column ywty_plmx.PTSJ is '平台时间' ;
comment on column ywty_plmx.WHRQ is '维护日期' ;
comment on column ywty_plmx.WHGY is '维护柜员' ;
comment on column ywty_plmx.FY is '附言' ;
comment on column ywty_plmx.BZ is '备注' ;
comment on column ywty_plmx.ZJLX is '证件种类' ;
comment on column ywty_plmx.ZJHM is '证件号码' ;
comment on column ywty_plmx.ZJYXRQ is '有效日期' ;
comment on column ywty_plmx.SEX is '性别' ;
comment on column ywty_plmx.CSRQ is '出生日期' ;
comment on column ywty_plmx.ADDRESS is '地址' ;
comment on column ywty_plmx.FZJG is '发证机关' ;
comment on column ywty_plmx.YZBM is '邮政编码' ;
comment on column ywty_plmx.PHONENO is '电话号码' ;
comment on column ywty_plmx.YYBJ is '预约标记' ;
comment on column ywty_plmx.YYRQ is '预约日期' ;
comment on column ywty_plmx.YYSJ is '预约时间' ;
comment on column ywty_plmx.DSFRQ is '第三方日期' ;
comment on column ywty_plmx.DSFLS is '第三方流水号' ;
comment on column ywty_plmx.DSFJYLX is '第三方交易类型' ;
comment on column ywty_plmx.DSFJYM is '第三方交易代码' ;
comment on column ywty_plmx.DSFXYM is '第三方响应码' ;
comment on column ywty_plmx.DSFXYXX is '第三方响应信息' ;
comment on column ywty_plmx.DSFJYZT is '第三方交易状态' ;
comment on column ywty_plmx.DSFDZBJ is '第三方对账标志' ;
comment on column ywty_plmx.ZJJZGY is '主机记账柜员' ;
comment on column ywty_plmx.ZJJZRQ is '主机记账日期' ;
comment on column ywty_plmx.ZJJZLS is '主机记账流水' ;
comment on column ywty_plmx.ZJGYLS is '主机柜员流水' ;
comment on column ywty_plmx.KHZFLS is '跨行支付流水' ;
comment on column ywty_plmx.ZJXYM is '主机响应码' ;
comment on column ywty_plmx.ZJXYXX is '主机响应信息' ;
comment on column ywty_plmx.ZJJYZT is '第三方交易状态' ;
comment on column ywty_plmx.ZJDZBJ is '主机对账标志' ;
comment on column ywty_plmx.CZGY is '冲正柜员' ;
comment on column ywty_plmx.CZRQ is '冲正日期' ;
comment on column ywty_plmx.CZLS is '冲正流水' ;
comment on column ywty_plmx.FSCS is '发送次数' ;
comment on column ywty_plmx.JYXYM is '交易响应码' ;
comment on column ywty_plmx.JYXYXX is '交易响应信息' ;
comment on column ywty_plmx.JYZT is '交易状态' ;
comment on column ywty_plmx.BY1 is '备用1' ;
comment on column ywty_plmx.BY2 is '备用2' ;
comment on column ywty_plmx.BY3 is '备用3' ;
comment on column ywty_plmx.BY4 is '备用4' ;
comment on column ywty_plmx.BY5 is '备用5' ;
comment on column ywty_plmx.BY6 is '备用6' ;
