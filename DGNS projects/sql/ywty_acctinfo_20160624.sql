drop table ywty_acctinfo;
create table ywty_acctinfo
(
	ywbh varchar(30),
	dwbh varchar(30),
	dwmc varchar(150),
	acctno1 varchar(32),
	acctno2 varchar(32),
	acctno3 varchar(32),
	acctno4 varchar(32),
	coop_account varchar(32),
	oper_name varchar(150),
	tran_date varchar(10),
	flag varchar(1),
	remark1 varchar(40),
	remark2 varchar(40)
);

create unique index index_ywty_acctinfo_1 on ywty_acctinfo( YWBH��DWBH );
alter table ywty_acctinfo add constraint ywty_acctinfo_key primary key(YWBH��DWBH);
comment on table  ywty_acctinfo  is 'ywty_acctinfo' ;
comment on column ywty_acctinfo.YWBH is 'ҵ����' ;
comment on column ywty_acctinfo.DWBH is '��λ���' ;
comment on column ywty_acctinfo.DWMC is '��λ����' ;
comment on column ywty_acctinfo.ACCTNO1 is '�ڲ��˺�1' ;
comment on column ywty_acctinfo.ACCTNO2 is '�ڲ��˺�2' ;
comment on column ywty_acctinfo.ACCTNO3 is '�ڲ��˺�3' ;
comment on column ywty_acctinfo.ACCTNO4 is '�ڲ��˺�4' ;
comment on column ywty_acctinfo.COOP_ACCOUNT is '�Թ��˺�' ;
comment on column ywty_acctinfo.OPER_NAME is 'ά����' ;
comment on column ywty_acctinfo.TRAN_DATE is 'ά������' ;
comment on column ywty_acctinfo.FLAG is '���ո���ʶ' ;
comment on column ywty_acctinfo.REMARK1 is '��ע1' ;
comment on column ywty_acctinfo.REMARK2 is '��ע2' ;
