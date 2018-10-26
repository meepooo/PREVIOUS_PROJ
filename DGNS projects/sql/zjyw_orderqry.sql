drop table zjyw_orderqry;
create table zjyw_orderqry
(
	tran_date varchar(8),
	ywbh varchar(20),
	order_no varchar(52),
	branch_id varchar(20),
	trantime varchar(14),
	seq_no varchar(32),
	fqflsh varchar(32),
	acct_no varchar(32),
	tran_amt decimal(20,2),
	ywlx varchar(2),
	zflx varchar(1),
	qdbs varchar(10),
	send_num integer,
	state varchar(10),
	remark1 varchar(40),
	remark2 varchar(40),
	remark3 varchar(40),
	remark4 varchar(40)
) IN GAPS_DATA INDEX IN GAPS_INDEX ;

create unique index index_zjyw_orderqry_1 on zjyw_orderqry( TRAN_DATE,YWBH,ORDER_NO );
comment on table  zjyw_orderqry  is 'zjyw_orderqry' ;
comment on column zjyw_orderqry.TRAN_DATE is '��������' ;
comment on column zjyw_orderqry.YWBH is 'ҵ����' ;
comment on column zjyw_orderqry.ORDER_NO is '������' ;
comment on column zjyw_orderqry.BRANCH_ID is '���ͷ�����' ;
comment on column zjyw_orderqry.TRANTIME is '����ʱ��' ;
comment on column zjyw_orderqry.SEQ_NO is '������ˮ��' ;
comment on column zjyw_orderqry.FQFLSH is '������ˮ��' ;
comment on column zjyw_orderqry.ACCT_NO is '�˺�' ;
comment on column zjyw_orderqry.TRAN_AMT is '���׽��' ;
comment on column zjyw_orderqry.YWLX is 'ҵ������' ;
comment on column zjyw_orderqry.ZFLX is '֧������' ;
comment on column zjyw_orderqry.QDBS is '����' ;
comment on column zjyw_orderqry.SEND_NUM is '���ʹ���' ;
comment on column zjyw_orderqry.STATE is '״̬' ;
comment on column zjyw_orderqry.REMARK1 is '��ע1' ;
comment on column zjyw_orderqry.REMARK2 is '��ע2' ;
comment on column zjyw_orderqry.REMARK3 is '��ע3' ;
comment on column zjyw_orderqry.REMARK4 is '��ע4' ;
