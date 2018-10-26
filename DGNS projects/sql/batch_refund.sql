drop table batch_refund;

create table batch_refund
(
	ywbh		VARCHAR(16),
	cpdm		VARCHAR(16)		not null,
	cpmc		VARCHAR(40),
	dwbh		VARCHAR(16),
	dwmc		VARCHAR(80),
	thrq		CHAR(8)			not null,
	pkrq		CHAR(8)			not null,
	ptpch		CHAR(8)			not null,
	batch_no	VARCHAR(32)		not null,
	file_name	VARCHAR(128),
	zjlsh		CHAR(32),
	tczh		VARCHAR(32),
	tczhmc		VARCHAR(80),
	thzh		VARCHAR(32),
	thzhmc		VARCHAR(80),		
	batch_cnt	INTEGER,
	batch_amt	DECIMAL(15,2),
	tot_succ_cnt	INTEGER,
	tot_succ_amt	DECIMAL(15,2),
	tot_fail_cnt	INTEGER,
	tot_fail_amt	DECIMAL(15,2),
	stat		CHAR(1),
	sbyy		CHAR(200),
	constraint P_BATCH_REFUND primary key (batch_no)
);

CREATE INDEX BATCH_REFUND_IDX1 ON BATCH_REFUND(pkrq);

comment on table batch_refund is
'批量代付退回表';

comment on column batch_refund.ywbh is
'业务编号';

comment on column batch_refund.cpdm is
'产品代码';

comment on column batch_refund.cpmc is
'产品名称';

comment on column batch_refund.dwbh is
'单位编号';

comment on column batch_refund.dwmc is
'单位名称';

comment on column batch_refund.thrq is
'退回日期';

comment on column batch_refund.pkrq is
'批扣日期';

comment on column batch_refund.ptpch is
'平台批次号';

comment on column batch_refund.batch_no is
'商户批次号';

comment on column batch_refund.file_name is
'来盘文件名';

comment on column batch_refund.zjlsh is
'主机流水号';

comment on column batch_refund.xym is
'响应码';

comment on column batch_refund.xyxx is
'响应信息';

comment on column batch_refund.tczh is
'退出账户';

comment on column batch_refund.tczhmc is
'退出账户名称';

comment on column batch_refund.thzh is
'退回账户';

comment on column batch_refund.thzhmc is
'退回账户名称';

comment on column batch_refund.batch_cnt is
'批次总笔数';

comment on column batch_refund.batch_amt is
'批次总金额';

comment on column batch_refund.tot_succ_cnt is
'成功总笔数';

comment on column batch_refund.tot_succ_amt is
'成功总金额';

comment on column batch_refund.tot_fail_cnt is
'失败总笔数';

comment on column batch_refund.tot_fail_amt is
'失败总金额';

comment on column batch_refund.stat is
'状态 1:成功 2：失败 3：超时 4：初始化';

comment on column batch_refund.sbyy is
'失败原因';














