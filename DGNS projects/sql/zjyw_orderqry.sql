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
comment on column zjyw_orderqry.TRAN_DATE is '交易日期' ;
comment on column zjyw_orderqry.YWBH is '业务编号' ;
comment on column zjyw_orderqry.ORDER_NO is '订单号' ;
comment on column zjyw_orderqry.BRANCH_ID is '发送方机构' ;
comment on column zjyw_orderqry.TRANTIME is '交易时间' ;
comment on column zjyw_orderqry.SEQ_NO is '交易流水号' ;
comment on column zjyw_orderqry.FQFLSH is '发起方流水号' ;
comment on column zjyw_orderqry.ACCT_NO is '账号' ;
comment on column zjyw_orderqry.TRAN_AMT is '交易金额' ;
comment on column zjyw_orderqry.YWLX is '业务类型' ;
comment on column zjyw_orderqry.ZFLX is '支付类型' ;
comment on column zjyw_orderqry.QDBS is '渠道' ;
comment on column zjyw_orderqry.SEND_NUM is '发送次数' ;
comment on column zjyw_orderqry.STATE is '状态' ;
comment on column zjyw_orderqry.REMARK1 is '备注1' ;
comment on column zjyw_orderqry.REMARK2 is '备注2' ;
comment on column zjyw_orderqry.REMARK3 is '备注3' ;
comment on column zjyw_orderqry.REMARK4 is '备注4' ;
