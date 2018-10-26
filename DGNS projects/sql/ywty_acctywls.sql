drop table ywty_acctywls;
create table ywty_acctywls
(
	ptrq varchar(8),
	ptls int,
	zjlsh varchar(32),
	ptsj varchar(6),
	rzbz varchar(1),
	jylx varchar(1),
	yptls int,
	jyjg varchar(16),
	jygy varchar(16),
	qdbs varchar(3),
	zdsbbh varchar(8),
	yybs varchar(8),
	cpdm varchar(16),
	ywbh varchar(16),
	jydm varchar(8),
	dwbh varchar(32),
	mssq varchar(8),
	smsq varchar(8),
	msnm varchar(80),
	mslt varchar(8),
	wkdt varchar(8),
	wktm varchar(6),
	opdt varchar(8),
	srtm varchar(6),
	alcn varchar(7),
	jdbz varchar(1),
	zhlx varchar(2),
	yhzh varchar(32),
	dfzh varchar(32),
	jyje decimal(16,2),
	sxf decimal(16,2),
	pcbh int,
	jyxym varchar(8),
	jyxyxx varchar(60),
	jyzt varchar(1),
	remark1 varchar(40),
	remark2 varchar(40)
);

create unique index index_ywty_acctywls_1 on ywty_acctywls( PTRQ,PTLS );
alter table ywty_acctywls add constraint ywty_acctywls_key primary key(PTRQ,PTLS);
comment on table  ywty_acctywls  is 'ywty_acctywls' ;
comment on column ywty_acctywls.PTRQ is 'ƽ̨����' ;
comment on column ywty_acctywls.PTLS is 'ƽ̨��ˮ��' ;
comment on column ywty_acctywls.ZJLSH is '������ˮ��' ;
comment on column ywty_acctywls.PTSJ is 'ƽ̨ʱ��' ;
comment on column ywty_acctywls.RZBZ is '���ʱ�־' ;
comment on column ywty_acctywls.JYLX is '��������' ;
comment on column ywty_acctywls.YPTLS is 'ԭƽ̨��ˮ��' ;
comment on column ywty_acctywls.JYJG is '���׻���' ;
comment on column ywty_acctywls.JYGY is '���׹�Ա' ;
comment on column ywty_acctywls.QDBS is '������ʶ' ;
comment on column ywty_acctywls.ZDSBBH is '�ն��豸���' ;
comment on column ywty_acctywls.YYBS is 'Ӧ�ñ�ʶ' ;
comment on column ywty_acctywls.CPDM is '��Ʒ����' ;
comment on column ywty_acctywls.YWBH is 'ҵ����' ;
comment on column ywty_acctywls.JYDM is '���״���' ;
comment on column ywty_acctywls.DWBH is '��λ���' ;
comment on column ywty_acctywls.MSSQ is '�������' ;
comment on column ywty_acctywls.SMSQ is '���������' ;
comment on column ywty_acctywls.MSNM is '����������' ;
comment on column ywty_acctywls.MSLT is 'ǰ����������б�' ;
comment on column ywty_acctywls.WKDT is '�ƻ�ִ������' ;
comment on column ywty_acctywls.WKTM is '�ƻ�ִ��ʱ��' ;
comment on column ywty_acctywls.OPDT is 'ʵ��ִ������' ;
comment on column ywty_acctywls.SRTM is 'ʵ��ִ��ʱ��' ;
comment on column ywty_acctywls.ALCN is 'Ԥ������' ;
comment on column ywty_acctywls.JDBZ is '�����־' ;
comment on column ywty_acctywls.ZHLX is '�ʻ�����' ;
comment on column ywty_acctywls.YHZH is '�����ʺ�' ;
comment on column ywty_acctywls.DFZH is '�Է��ʺ�' ;
comment on column ywty_acctywls.JYJE is '���׽��' ;
comment on column ywty_acctywls.SXF is '������' ;
comment on column ywty_acctywls.PCBH is '���α��' ;
comment on column ywty_acctywls.JYXYM is '������Ӧ��' ;
comment on column ywty_acctywls.JYXYXX is '������Ӧ��Ϣ' ;
comment on column ywty_acctywls.JYZT is '����״̬' ;
comment on column ywty_acctywls.REMARK1 is '��ע1' ;
comment on column ywty_acctywls.REMARK2 is '��ע2' ;
