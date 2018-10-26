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
comment on column tbl_jzzf_gwktmp.CZBM is '�����ִ���' ;
comment on column tbl_jzzf_gwktmp.BGDEPTCODE is 'Ԥ�㵥λ����' ;
comment on column tbl_jzzf_gwktmp.BGDEPTNAME is 'Ԥ�㵥λ����' ;
comment on column tbl_jzzf_gwktmp.CARDUSERNAME is '���û�����' ;
comment on column tbl_jzzf_gwktmp.CARDNO is '����' ;
comment on column tbl_jzzf_gwktmp.IDCARDNO is '���֤����' ;
comment on column tbl_jzzf_gwktmp.MOBILENUM is '�ֻ�����' ;
comment on column tbl_jzzf_gwktmp.ISUSED is '�Ƿ����' ;
comment on column tbl_jzzf_gwktmp.OPENDATE is '��������' ;
comment on column tbl_jzzf_gwktmp.OPENBANKCODE is '�����д���' ;
comment on column tbl_jzzf_gwktmp.OPENBANKNAME is '����������' ;
comment on column tbl_jzzf_gwktmp.ACCTNO is '���������ʺ�' ;
comment on column tbl_jzzf_gwktmp.STATE is '����״̬' ;
