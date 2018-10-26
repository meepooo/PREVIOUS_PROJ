drop table ywty_acctycls;
create table ywty_acctycls
(
CPDM    varchar(16)  ,
YWBH    varchar(16)  ,
PTRQ    varchar(8)   ,
PTLS    varchar(52)   ,
PTSJ    varchar(6)   ,
YPTLS   varchar(52)  ,
TLSQ    varchar(32)  ,
CZSQ    varchar(32)  ,
JYJG    varchar(16)  ,
JYGY    varchar(16)  ,
QDBS    varchar(3)   ,
ZDSBBH  varchar(8)   ,
YYBS    varchar(8)   ,
JYDM    varchar(8)   ,
DWBH    varchar(32)  ,
WKDT    varchar (8)  ,
WKTM    varchar (6)  ,
OPDT    varchar (8)  ,
SRTM    varchar (6)  ,
JDBZ    varchar(1)   ,
ZHLX    varchar(2)   ,
YHZH    varchar(32)  ,
DFZH    varchar(32)  ,
JYJE    decimal(16,2),
SXF     decimal(16,2),
JYZT    varchar(1)   ,
REMARK1 VARCHAR(80)  ,
REMARK2 VARCHAR(80)  ,
REMARK3 VARCHAR(80)  ,
REMARK4 VARCHAR(80)  ,
REMARK5 VARCHAR(80)  
);

comment on table  ywty_acctycls  is 'ywty_acctycls' ;
comment on column ywty_acctycls.CPDM    is'产品代码' ;         
comment on column ywty_acctycls.YWBH    is'业务编号' ;         
comment on column ywty_acctycls.PTRQ    is'平台日期 YYYYMMDD' ;
comment on column ywty_acctycls.PTLS    is'平台流水号' ;       
comment on column ywty_acctycls.PTSJ    is'平台时间 HHMMSS' ;  
comment on column ywty_acctycls.YPTLS   is'原平台流水号' ;     
comment on column ywty_acctycls.TLSQ    is'核心流水号' ;       
comment on column ywty_acctycls.CZSQ    is'核心冲正流水号' ;   
comment on column ywty_acctycls.JYJG    is'交易机构' ;         
comment on column ywty_acctycls.JYGY    is'交易柜员' ;         
comment on column ywty_acctycls.QDBS    is'渠道标识' ;         
comment on column ywty_acctycls.ZDSBBH  is'终端设备编号' ;     
comment on column ywty_acctycls.YYBS    is'应用标识' ;         
comment on column ywty_acctycls.JYDM    is'交易代码' ;         
comment on column ywty_acctycls.DWBH    is'用户编号如手机号' ; 
comment on column ywty_acctycls.WKDT    is'登记日期' ;         
comment on column ywty_acctycls.WKTM    is'登记时间' ;         
comment on column ywty_acctycls.OPDT    is'实际执行日期' ;     
comment on column ywty_acctycls.SRTM    is'实际执行时间' ;     
comment on column ywty_acctycls.JDBZ    is'借贷标志见数据字典KEY=K_JDBZ C 借  D 贷' ;
comment on column ywty_acctycls.ZHLX    is'帐户类型见数据字典KEY=K_ZHLX
01 对公活期
02 对私活期
03 对公定期
04 对私定期
05 保证金
06 贷款
07 内部账
08 表外账' ;
comment on column ywty_acctycls.YHZH    is'银行帐号' ;
comment on column ywty_acctycls.DFZH    is'对方帐号' ;
comment on column ywty_acctycls.JYJE    is'交易金额' ;
comment on column ywty_acctycls.SXF     is'手续费' ;  
comment on column ywty_acctycls.JYZT    is'0 登记
1 处理成功
2 处理失败' ;
comment on column ywty_acctycls.REMARK1 is'扩展1' ;
comment on column ywty_acctycls.REMARK2 is'扩展2' ;
comment on column ywty_acctycls.REMARK3 is'扩展3' ;
comment on column ywty_acctycls.REMARK4 is'扩展4' ;
comment on column ywty_acctycls.REMARK5 is'扩展4' ;
