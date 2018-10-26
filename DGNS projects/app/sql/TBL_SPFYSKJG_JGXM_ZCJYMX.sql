drop table TBL_SPFYSKJG_JGXM_ZCJYMX;
create table TBL_SPFYSKJG_JGXM_ZCJYMX
(
DETAILID                    varchar(40)               not null,                              
BOOKDATE                    varchar(8)                 not null,
ACCOUNT                     varchar(40)               not null,
TRANDT                      varchar(8)                not null,
TRANSQ                      varchar(20),  
OCCURS                      varchar(2),   
PROTOCOLNO                  varchar(40),  
PROTOCOLVAL                 varchar(20),  
CUSTNO                      varchar(512), 
TRANSTYPE                   varchar(40)               not null,
AMOUNT                      varchar(17)               not null,
AMOUNT2                     varchar(17),  
SMRYTX                      varchar(120), 
TSDATE                      varchar(8),   
MEMO                        varchar(100), 
STATUS                      varchar(2),    
PUSHNO                      DECIMAL(2),     
USERID                      varchar(40),  
ORGID                       varchar(40),  
UPDATEDATE                  varchar(8),   
REMARK1                     varchar(254),  
REMARK2                     varchar(254),  
REMARK3                     varchar(254),  
CONSTRAINT PK_TBL_SPFYSKJG_JGXM_ZCJYMX PRIMARY KEY (DETAILID,BOOKDATE,ACCOUNT,
TRANDT,TRANSTYPE,AMOUNT))IN AGENT_DATA INDEX IN AGENT_INDEX;
COMMENT ON TABLE TBL_SPFYSKJG_JGXM_ZCJYMX IS '预售监管账户支出交易明细登记表';
COMMENT ON COLUMN TBL_SPFYSKJG_JGXM_ZCJYMX.DETAILID IS '银行账户交易记录明细唯一标识码';
COMMENT ON COLUMN TBL_SPFYSKJG_JGXM_ZCJYMX.BOOKDATE IS '登记日期';
COMMENT ON COLUMN TBL_SPFYSKJG_JGXM_ZCJYMX.ACCOUNT IS '监管账号';
COMMENT ON COLUMN TBL_SPFYSKJG_JGXM_ZCJYMX.TRANDT IS '交易日期';
COMMENT ON COLUMN TBL_SPFYSKJG_JGXM_ZCJYMX.TRANSQ IS '交易流水号';
COMMENT ON COLUMN TBL_SPFYSKJG_JGXM_ZCJYMX.OCCURS IS '资金交易方向:D借 C贷';
COMMENT ON COLUMN TBL_SPFYSKJG_JGXM_ZCJYMX.PROTOCOLNO IS '合同编号';
COMMENT ON COLUMN TBL_SPFYSKJG_JGXM_ZCJYMX.PROTOCOLVAL IS '合同金额';
COMMENT ON COLUMN TBL_SPFYSKJG_JGXM_ZCJYMX.CUSTNO IS '房屋编号';
COMMENT ON COLUMN TBL_SPFYSKJG_JGXM_ZCJYMX.TRANSTYPE IS '交易类型';
COMMENT ON COLUMN TBL_SPFYSKJG_JGXM_ZCJYMX.AMOUNT IS '补录金额';
COMMENT ON COLUMN TBL_SPFYSKJG_JGXM_ZCJYMX.AMOUNT2 IS '流水金额';
COMMENT ON COLUMN TBL_SPFYSKJG_JGXM_ZCJYMX.SMRYTX IS '摘要';
COMMENT ON COLUMN TBL_SPFYSKJG_JGXM_ZCJYMX.TSDATE IS '推送日期';
COMMENT ON COLUMN TBL_SPFYSKJG_JGXM_ZCJYMX.MEMO IS '交易结果描述';
COMMENT ON COLUMN TBL_SPFYSKJG_JGXM_ZCJYMX.STATUS IS '推送状态';
COMMENT ON COLUMN TBL_SPFYSKJG_JGXM_ZCJYMX.PUSHNO IS '重推序号';
COMMENT ON COLUMN TBL_SPFYSKJG_JGXM_ZCJYMX.USERID IS '经办人id';
COMMENT ON COLUMN TBL_SPFYSKJG_JGXM_ZCJYMX.ORGID IS '经办人所属机构';
COMMENT ON COLUMN TBL_SPFYSKJG_JGXM_ZCJYMX.UPDATEDATE IS '维护日期';
COMMENT ON COLUMN TBL_SPFYSKJG_JGXM_ZCJYMX.REMARK1 IS '备用字段1';
COMMENT ON COLUMN TBL_SPFYSKJG_JGXM_ZCJYMX.REMARK2 IS '备用字段2';          
COMMENT ON COLUMN TBL_SPFYSKJG_JGXM_ZCJYMX.REMARK3 IS '备用字段3';        
                         

