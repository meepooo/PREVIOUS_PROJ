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
comment on column tbl_jzzf_gwkinfo.CZBM is '�����ִ���' ;
comment on column tbl_jzzf_gwkinfo.TRANDATE is '��������' ;
comment on column tbl_jzzf_gwkinfo.FINANO is '������ˮ��' ;
comment on column tbl_jzzf_gwkinfo.BANKID is '���б�ʶ��' ;
comment on column tbl_jzzf_gwkinfo.BANKNAME is '��������' ;
comment on column tbl_jzzf_gwkinfo.BGDEPTCODE is 'Ԥ�㵥λ����' ;
comment on column tbl_jzzf_gwkinfo.BGDEPTNAME is 'Ԥ�㵥λ����' ;
comment on column tbl_jzzf_gwkinfo.FISCAL is '���' ;
comment on column tbl_jzzf_gwkinfo.TRANSTYPE is 'ҵ������' ;
comment on column tbl_jzzf_gwkinfo.CARDUSERNAME is '���û�����' ;
comment on column tbl_jzzf_gwkinfo.CARDNO is '����' ;
comment on column tbl_jzzf_gwkinfo.OLDCARDNO is '�ɿ���' ;
comment on column tbl_jzzf_gwkinfo.IDCARDNO is '���֤����' ;
comment on column tbl_jzzf_gwkinfo.MOBILENUM is '�ֻ�����' ;
comment on column tbl_jzzf_gwkinfo.ISUSED is '�Ƿ����' ;
comment on column tbl_jzzf_gwkinfo.OPENDATE is '��������' ;
comment on column tbl_jzzf_gwkinfo.OPENBANKCODE is '�����д���' ;
comment on column tbl_jzzf_gwkinfo.OPENBANKNAME is '����������' ;
comment on column tbl_jzzf_gwkinfo.ACCTNO is '���������ʺ�' ;
comment on column tbl_jzzf_gwkinfo.BUSITYPE is 'ҵ�����' ;
comment on column tbl_jzzf_gwkinfo.BANKSERIALNO is '������ˮ��' ;
comment on column tbl_jzzf_gwkinfo.OPERATOR is 'ҵ����Ա' ;
comment on column tbl_jzzf_gwkinfo.BILLNO is '���ݺ�' ;
comment on column tbl_jzzf_gwkinfo.STATE is '����״̬' ;
comment on column tbl_jzzf_gwkinfo.REMARK1 is '��ע1' ;
comment on column tbl_jzzf_gwkinfo.REMARK2 is '��ע2' ;
comment on column tbl_jzzf_gwkinfo.REMARK3 is '��ע3' ;
comment on column tbl_jzzf_gwkinfo.REMARK4 is '��ע4' ;
