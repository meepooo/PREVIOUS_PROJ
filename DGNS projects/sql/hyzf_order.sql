drop table hyzf_order;
create table hyzf_order
(
SOURCE_TYPE VARCHAR(10),
BRANCH_ID VARCHAR(20),
order_no VARCHAR(24) not null,
zwrq VARCHAR(8) not null,
TRANTIME VARCHAR(6)not null,
zhqzlsh integer  not null,
BUSS_SEQ_NO char(52)not null,
CONSUMER_SEQ_NO char(52)not null,
ESB_SEQ_NO char(52)not null,
zjlsh VARCHAR(52),
CLIENT_NO VARCHAR(20) not null,
recharge_no VARCHAR(50)not null,
acct_no VARCHAR(50),
ACCT_NAME VARCHAR(150),
FACE_AMT decimal(10,2),
ACT_PAY_AMT decimal(10,2),
SELL_AMT decimal(10,2), 
ORDER_TYPE VARCHAR(5)not null,
settle_date VARCHAR(14)not null,
pay_type VARCHAR(1)not null,
pay_state VARCHAR(1)not null,
ORDER_STATUS VARCHAR(2)not null,
ORDER_STATUS_NAME VARCHAR(20),
up_zhqzlsh integer not null,
up_time char(14) not null
);

alter table hyzf_order add primary key(ORDER_NO);

create unique index index_hyzf_order_1 on hyzf_order(ZWRQ,zhqzlsh );
comment on table  hyzf_order  is 'hyzf_order' ;
comment on column hyzf_order.SOURCE_TYPE is'渠道类型' ;   
comment on column hyzf_order.BRANCH_ID is'发送方机构 ' ; 
comment on column hyzf_order.ORDER_NO is '订单号' ;
comment on column hyzf_order.ZWRQ is '账务日期' ;
comment on column hyzf_order.TRANTIME is '交易时间' ;
comment on column hyzf_order.ZHQZLSH is 'GAPS流水号' ;
comment on column hyzf_order.zjlsh is '主机流水号' ;
comment on column hyzf_order.BUSS_SEQ_NO is'业务流水号 ' ; 
comment on column hyzf_order.CONSUMER_SEQ_NO is'前置流水号  ' ;
comment on column hyzf_order.ESB_SEQ_NO is'ESB流水号 ' ;
comment on column hyzf_order.CLIENT_NO is '客户号' ;
comment on column hyzf_order.RECHARGE_NO is '充值账号' ;
comment on column hyzf_order.ACCT_NO is '付款账号' ;
comment on column hyzf_order.ACCT_NAME is '账号名' ;
comment on column hyzf_order.FACE_AMT is '票面金额' ;
comment on column hyzf_order.ACT_PAY_AMT is '应付金额' ;
comment on column hyzf_order.SELL_AMT is '实付金额' ;
comment on column hyzf_order.ORDER_TYPE is '交易类型' ;
comment on column hyzf_order.settle_date is '订单记账日' ;
comment on column hyzf_order.PAY_TYPE is '支付类型' ;
comment on column hyzf_order.PAY_STATE is '支付状态' ;
comment on column hyzf_order.ORDER_STATUS is '交易状态' ;
comment on column hyzf_order.ORDER_STATUS is '交易状态说明' ;
comment on column hyzf_order.up_zhqzlsh is'更新流水   ' ;
comment on column hyzf_order.up_time is'更新时间   ' ;

