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
comment on column tbl_jzzf_gwkplhk.CZBM is '�����ִ���' ;
comment on column tbl_jzzf_gwkplhk.TRANDATE is '��������' ;
comment on column tbl_jzzf_gwkplhk.FINANO is '������ˮ��' ;
comment on column tbl_jzzf_gwkplhk.BANKID is '���б�ʶ��' ;
comment on column tbl_jzzf_gwkplhk.BGDEPTCODE is 'Ԥ�㵥λ����' ;
comment on column tbl_jzzf_gwkplhk.TOTALSERIALNUM is '���ܱ��' ;
comment on column tbl_jzzf_gwkplhk.BILLNO is '��Ȩ֧��ƾ֤��' ;
comment on column tbl_jzzf_gwkplhk.TOTALAMT is '��Ȩ֧�����ܽ��' ;
comment on column tbl_jzzf_gwkplhk.COUNT is '���׼�¼����' ;
comment on column tbl_jzzf_gwkplhk.CARDNO is '����' ;
comment on column tbl_jzzf_gwkplhk.CARDNAME is '�û�����' ;
comment on column tbl_jzzf_gwkplhk.PAYMONEY is '���׽��' ;
comment on column tbl_jzzf_gwkplhk.BANKSERIALNO is '������ˮ��' ;
comment on column tbl_jzzf_gwkplhk.OPERATOR is 'ҵ����Ա' ;
comment on column tbl_jzzf_gwkplhk.STATE is '����״̬' ;
comment on column tbl_jzzf_gwkplhk.REMARK1 is '��ע1' ;
comment on column tbl_jzzf_gwkplhk.REMARK2 is '��ע2' ;
comment on column tbl_jzzf_gwkplhk.REMARK3 is '��ע3' ;
comment on column tbl_jzzf_gwkplhk.REMARK4 is '��ע4' ;
