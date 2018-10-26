drop table agent_fee_detail;
--==============================================================
-- Table: AGENT_FEE_DETAIL
--==============================================================
create table AGENT_FEE_DETAIL
(
   PKRQ                 CHAR(8)             not null,
   PTPCH                CHAR(8)             not null,
   CPDM                 CHAR(16),
   YWBH                 CHAR(16)            not null,
   BATCH_NO             CHAR(32)            not null,
   PAY_MONTH            CHAR(8),
   FILE_NAME            VARCHAR(128),
   TOT_SUCC_CNT         INTEGER,
   TOT_SUCC_AMT         DECIMAL(16,2),
   TOT_BUSI_AMT         DECIMAL(16,2),
   TOT_AMT1             DECIMAL(16,2),
   TOT_AMT2             DECIMAL(16,2),
   TOT_AMT3             DECIMAL(16,2),
   TOT_AMT4             DECIMAL(16,2),
   TOT_AMT5             DECIMAL(16,2),
   FEE_FLAG             CHAR(1),
   FEE_OWN_FLAG         CHAR(1),
   FEE_PAY_FLAG         CHAR(1),
   PAY_ACT_NO           CHAR(32),
   PAY_ACT_NAME         VARCHAR(100),
   PAYEE_ACT_NO         CHAR(32),
   PAYEE_ACT_NAME       VARCHAR(100),
   FEE                  DECIMAL(16,2),
   REAL_FEE             DECIMAL(16,2),
   ACCT_DATE            CHAR(8),
   ACCT_TIME            CHAR(6),
   ACCT_SEQ_NO          INTEGER,
   TX_UNIT              VARCHAR(16),
   TELLER_NO            VARCHAR(16),
   CHANNEL_NO           VARCHAR(3),
   STAT                 VARCHAR(1),
   CLEAR_STAT           VARCHAR(1),
   RESP_CODE            VARCHAR(7),
   RESP_MSG             VARCHAR(60),
   SEND_NUM             INTEGER,
   EXTFLD1              VARCHAR(80),
   EXTFLD2              VARCHAR(80),
   EXTFLD3              VARCHAR(80),
   EXTFLD4              VARCHAR(80),
   EXTFLD5              VARCHAR(80),
   EXTFLD6              VARCHAR(160),
   constraint P_K_AGENT_FEE_DETAIL_1 primary key (BATCH_NO)
);

CREATE UNIQUE INDEX AGENT_FEE_DETAIL_IDX1 ON AGENT_FEE_DETAIL(PKRQ,PTPCH);
CREATE INDEX AGENT_FEE_DETAIL_IDX2 ON AGENT_FEE_DETAIL(PKRQ,CPDM,STAT);
CREATE INDEX AGENT_FEE_DETAIL_IDX3 ON AGENT_FEE_DETAIL(PAY_MONTH,CPDM,YWBH);

comment on table AGENT_FEE_DETAIL is
'批量代收付手续费扣费明细登记簿';

comment on column AGENT_FEE_DETAIL.PKRQ is '批扣日期';

comment on column AGENT_FEE_DETAIL.PTPCH is '平台批次号';

comment on column AGENT_FEE_DETAIL.CPDM is '产品代码';

comment on column AGENT_FEE_DETAIL.YWBH is '业务编号';

comment on column AGENT_FEE_DETAIL.BATCH_NO is '商户批次号';

comment on column AGENT_FEE_DETAIL.PAY_MONTH is '费用年月(回盘日期)';

comment on column AGENT_FEE_DETAIL.FILE_NAME is '来盘文件名';

comment on column AGENT_FEE_DETAIL.TOT_SUCC_CNT is '成功总笔数';

comment on column AGENT_FEE_DETAIL.TOT_SUCC_AMT is '成功总金额';

comment on column AGENT_FEE_DETAIL.TOT_BUSI_AMT is '成功总业务金额';

comment on column AGENT_FEE_DETAIL.TOT_AMT1 is '成功总费用1';

comment on column AGENT_FEE_DETAIL.TOT_AMT2 is '成功总费用2';

comment on column AGENT_FEE_DETAIL.TOT_AMT3 is '成功总费用3';

comment on column AGENT_FEE_DETAIL.TOT_AMT4 is '成功总费用4';

comment on column AGENT_FEE_DETAIL.TOT_AMT5 is '成功总费用5';

comment on column AGENT_FEE_DETAIL.FEE_FLAG is '手续费标志 0-收取,1-免收';

comment on column AGENT_FEE_DETAIL.FEE_OWN_FLAG is '手续费归属标志 0-单位,1-其他,2-个人';

comment on column AGENT_FEE_DETAIL.FEE_PAY_FLAG is '手续费扣划方式 0-自动 1-手工';

comment on column AGENT_FEE_DETAIL.PAY_ACT_NO is '手续费付款账号';

comment on column AGENT_FEE_DETAIL.PAY_ACT_NAME is '手续费付款账号名称';

comment on column AGENT_FEE_DETAIL.PAYEE_ACT_NO is '手续费收款账号';

comment on column AGENT_FEE_DETAIL.PAYEE_ACT_NAME is '手续费收款账号名称';

comment on column AGENT_FEE_DETAIL.FEE is '手续费金额';

comment on column AGENT_FEE_DETAIL.REAL_FEE is '实收手续费金额';

comment on column AGENT_FEE_DETAIL.ACCT_DATE is '入账日期';

comment on column AGENT_FEE_DETAIL.ACCT_TIME is '入账时间';

comment on column AGENT_FEE_DETAIL.ACCT_SEQ_NO is '入账流水号';

comment on column AGENT_FEE_DETAIL.TX_UNIT is '交易机构';

comment on column AGENT_FEE_DETAIL.TELLER_NO is '交易柜员';

comment on column AGENT_FEE_DETAIL.CHANNEL_NO is '渠道标识';

comment on column AGENT_FEE_DETAIL.STAT is '状态 0-待记账,1-记账成功,2-记账失败,9-记账处理中';

comment on column AGENT_FEE_DETAIL.CLEAR_STAT is '清算状态 0-待清算,1-清算成功,2-清算失败';

comment on column AGENT_FEE_DETAIL.RESP_CODE is '错误码';

comment on column AGENT_FEE_DETAIL.RESP_MSG is '错误信息';

comment on column AGENT_FEE_DETAIL.SEND_NUM is '发送次数';

comment on column AGENT_FEE_DETAIL.EXTFLD1 is '扩展字段1';

comment on column AGENT_FEE_DETAIL.EXTFLD2 is '扩展字段2';

comment on column AGENT_FEE_DETAIL.EXTFLD3 is '扩展字段3';

comment on column AGENT_FEE_DETAIL.EXTFLD4 is '扩展字段4';

comment on column AGENT_FEE_DETAIL.EXTFLD5 is '扩展字段5';

comment on column AGENT_FEE_DETAIL.EXTFLD6 is '扩展字段6';

