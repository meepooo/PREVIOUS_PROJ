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
'���������˻ر�';

comment on column batch_refund.ywbh is
'ҵ����';

comment on column batch_refund.cpdm is
'��Ʒ����';

comment on column batch_refund.cpmc is
'��Ʒ����';

comment on column batch_refund.dwbh is
'��λ���';

comment on column batch_refund.dwmc is
'��λ����';

comment on column batch_refund.thrq is
'�˻�����';

comment on column batch_refund.pkrq is
'��������';

comment on column batch_refund.ptpch is
'ƽ̨���κ�';

comment on column batch_refund.batch_no is
'�̻����κ�';

comment on column batch_refund.file_name is
'�����ļ���';

comment on column batch_refund.zjlsh is
'������ˮ��';

comment on column batch_refund.xym is
'��Ӧ��';

comment on column batch_refund.xyxx is
'��Ӧ��Ϣ';

comment on column batch_refund.tczh is
'�˳��˻�';

comment on column batch_refund.tczhmc is
'�˳��˻�����';

comment on column batch_refund.thzh is
'�˻��˻�';

comment on column batch_refund.thzhmc is
'�˻��˻�����';

comment on column batch_refund.batch_cnt is
'�����ܱ���';

comment on column batch_refund.batch_amt is
'�����ܽ��';

comment on column batch_refund.tot_succ_cnt is
'�ɹ��ܱ���';

comment on column batch_refund.tot_succ_amt is
'�ɹ��ܽ��';

comment on column batch_refund.tot_fail_cnt is
'ʧ���ܱ���';

comment on column batch_refund.tot_fail_amt is
'ʧ���ܽ��';

comment on column batch_refund.stat is
'״̬ 1:�ɹ� 2��ʧ�� 3����ʱ 4����ʼ��';

comment on column batch_refund.sbyy is
'ʧ��ԭ��';














