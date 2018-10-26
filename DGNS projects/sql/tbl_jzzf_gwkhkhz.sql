drop table tbl_jzzf_gwkhkhz;
create table tbl_jzzf_gwkhkhz
(
        czbm varchar(12) not null,
        trandate varchar(10),
        finano varchar(25),
        bankid varchar(20),
        bgdeptcode varchar(12),
        totalserialnum varchar(20)not null,
        billno varchar(20)not null,
        totalamt decimal(20,2),
        count INTEGER,
        state varchar(1),
        sendflag varchar(1),
constraint P_YWTY_ZFWG_DZ primary key (CZBM,TOTALSERIALNUM)
)--IN GAPS_DATA INDEX IN GAPS_INDEX
 ;

create index index_tbl_jzzf_gwkhkhz_1 on tbl_jzzf_gwkhkhz( CZBM,BILLNO );
comment on table  tbl_jzzf_gwkhkhz  is '国库集中支付还款汇总表' ;
comment on column tbl_jzzf_gwkhkhz.CZBM is '财政局代码' ;
comment on column tbl_jzzf_gwkhkhz.TRANDATE is '交易日期' ;
comment on column tbl_jzzf_gwkhkhz.FINANO is '财政流水号' ;
comment on column tbl_jzzf_gwkhkhz.BANKID is '银行标识号' ;
comment on column tbl_jzzf_gwkhkhz.BGDEPTCODE is '预算单位代码' ;
comment on column tbl_jzzf_gwkhkhz.TOTALSERIALNUM is '汇总编号' ;
comment on column tbl_jzzf_gwkhkhz.BILLNO is '授权支付凭证号' ;
comment on column tbl_jzzf_gwkhkhz.TOTALAMT is '授权支付令总金额' ;
comment on column tbl_jzzf_gwkhkhz.COUNT is '交易记录笔数' ;
comment on column tbl_jzzf_gwkhkhz.STATE is '
0:初始
1:已还款
2:已退回
3:还款失败
4:退回失败
5:更改后还款' ;
comment on column tbl_jzzf_gwkhkhz.SENDFLAG is '反馈标识 0：未反馈 1：已反馈' ;
