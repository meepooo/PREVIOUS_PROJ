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
comment on column tbl_jzzf_cz403.CZBM is '�����ִ���' ;
comment on column tbl_jzzf_cz403.TRANDATE is '��������' ;
comment on column tbl_jzzf_cz403.FINANO is '������ˮ��' ;
comment on column tbl_jzzf_cz403.BANKID is '���б�ʶ��' ;
comment on column tbl_jzzf_cz403.BANKNAME is '��������' ;
comment on column tbl_jzzf_cz403.BGDEPTCODE is 'Ԥ�㵥λ����' ;
comment on column tbl_jzzf_cz403.BGDEPTNAME is 'Ԥ�㵥λ����' ;
comment on column tbl_jzzf_cz403.FISCAL is '���' ;
comment on column tbl_jzzf_cz403.TRANSTYPE is 'ҵ������' ;
comment on column tbl_jzzf_cz403.CARDUSERNAME is '���û�����' ;
comment on column tbl_jzzf_cz403.CARDNO is '����' ;
comment on column tbl_jzzf_cz403.OLDCARDNO is '�ɿ���' ;
comment on column tbl_jzzf_cz403.IDCARDNO is '���֤����' ;
comment on column tbl_jzzf_cz403.MOBILENUM is '�ֻ�����' ;
comment on column tbl_jzzf_cz403.ISUSED is '�Ƿ����' ;
comment on column tbl_jzzf_cz403.OPENDATE is '��������' ;
comment on column tbl_jzzf_cz403.OPENBANKCODE is '�����д���' ;
comment on column tbl_jzzf_cz403.OPENBANKNAME is '����������' ;
comment on column tbl_jzzf_cz403.ACCTNO is '���������ʺ�' ;
comment on column tbl_jzzf_cz403.BUSITYPE is 'ҵ�����' ;
comment on column tbl_jzzf_cz403.BANKSERIALNO is '������ˮ��' ;
comment on column tbl_jzzf_cz403.OPERATOR is 'ҵ����Ա' ;
comment on column tbl_jzzf_cz403.BILLNO is '���ݺ�' ;
comment on column tbl_jzzf_cz403.STATE is '����״̬' ;
comment on column tbl_jzzf_cz403.REMARK1 is '��ע1' ;
comment on column tbl_jzzf_cz403.REMARK2 is '��ע2' ;
comment on column tbl_jzzf_cz403.REMARK3 is '��ע3' ;
comment on column tbl_jzzf_cz403.REMARK4 is '��ע4' ;



insert into tbl_jzzf_cz403 select * from  tbl_jzzf_gwkinfo;