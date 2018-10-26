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
comment on column yyt_orderinfo.KHH is '�ͻ���' ;
comment on column yyt_orderinfo.TRAN_DATE is '��������' ;
comment on column yyt_orderinfo.ZFLX is '֧������' ;
comment on column yyt_orderinfo.QDBS is '������ʶ' ;
comment on column yyt_orderinfo.YWLX is 'ҵ������' ;
comment on column yyt_orderinfo.ACCT_NO is '�˺�' ;
comment on column yyt_orderinfo.TRAN_AMT is '���׽��' ;
comment on column yyt_orderinfo.PAY_AMT is 'ʵ�����' ;
comment on column yyt_orderinfo.DISCOUNT_MSG is '�Ż�˵��' ;
comment on column yyt_orderinfo.SEQ_NO is '������ˮ��' ;
comment on column yyt_orderinfo.UID is 'ҽԺID' ;
comment on column yyt_orderinfo.HOSP_NAME is 'ҽԺ����' ;
comment on column yyt_orderinfo.DEP_ID is '����ID' ;
comment on column yyt_orderinfo.DEP_NAME is '��������' ;
comment on column yyt_orderinfo.DOCTOR_ID is 'ҽ��ID' ;
comment on column yyt_orderinfo.DOCTOR_NAME is 'ҽ������' ;
comment on column yyt_orderinfo.DOCTOR_ZCNAME is 'ҽ��ְ��' ;
comment on column yyt_orderinfo.PHONE is '�ֻ�����' ;
comment on column yyt_orderinfo.CARD is '֤������' ;
comment on column yyt_orderinfo.CARD_TYPE is '֤������' ;
comment on column yyt_orderinfo.TRUENAME is '����' ;
comment on column yyt_orderinfo.SEX is '�Ա�' ;
comment on column yyt_orderinfo.BIRTH is '��������' ;
comment on column yyt_orderinfo.SOCIAL_CARD is '�籣����' ;
comment on column yyt_orderinfo.DETLID is '��ԴID' ;
comment on column yyt_orderinfo.CLINIC_NO is '���￨��/������' ;
comment on column yyt_orderinfo.YUYUE_ID is 'ԤԼID' ;
comment on column yyt_orderinfo.ORDER_NO is '�������' ;
comment on column yyt_orderinfo.HIS_TAKE_NO is 'ȡ������' ;
comment on column yyt_orderinfo.TO_DATE is '��������' ;
comment on column yyt_orderinfo.TO_TIME is '����ʱ��' ;
comment on column yyt_orderinfo.BEGIN_TIME is '���￪ʼʱ��' ;
comment on column yyt_orderinfo.END_TIME is '�������ʱ��' ;
comment on column yyt_orderinfo.STATE is '״̬' ;
comment on column yyt_orderinfo.MSG is '״̬˵��' ;
comment on column yyt_orderinfo.PAY_FLAG is '֧����ʶ' ;
comment on column yyt_orderinfo.REMARK1 is '��ע1' ;
comment on column yyt_orderinfo.REMARK2 is '��ע2' ;
