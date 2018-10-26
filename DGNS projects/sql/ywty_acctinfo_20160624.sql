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

create unique index index_ywty_acctinfo_1 on ywty_acctinfo( YWBH，DWBH );
alter table ywty_acctinfo add constraint ywty_acctinfo_key primary key(YWBH，DWBH);
comment on table  ywty_acctinfo  is 'ywty_acctinfo' ;
comment on column ywty_acctinfo.YWBH is '业务编号' ;
comment on column ywty_acctinfo.DWBH is '单位编号' ;
comment on column ywty_acctinfo.DWMC is '单位名称' ;
comment on column ywty_acctinfo.ACCTNO1 is '内部账号1' ;
comment on column ywty_acctinfo.ACCTNO2 is '内部账号2' ;
comment on column ywty_acctinfo.ACCTNO3 is '内部账号3' ;
comment on column ywty_acctinfo.ACCTNO4 is '内部账号4' ;
comment on column ywty_acctinfo.COOP_ACCOUNT is '对公账号' ;
comment on column ywty_acctinfo.OPER_NAME is '维护人' ;
comment on column ywty_acctinfo.TRAN_DATE is '维护日期' ;
comment on column ywty_acctinfo.FLAG is '代收付标识' ;
comment on column ywty_acctinfo.REMARK1 is '备注1' ;
comment on column ywty_acctinfo.REMARK2 is '备注2' ;
