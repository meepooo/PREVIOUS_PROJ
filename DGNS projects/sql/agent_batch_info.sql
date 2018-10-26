drop table agent_batch_info;
--==============================================================
-- Table: AGENT_BATCH_INFO
--==============================================================
create table AGENT_BATCH_INFO
(
   BATCH_NO             CHAR(32)            not null,
   CPDM                 CHAR(16)            not null,
   DWBH                 CHAR(16)            not null,
   FILE_NAME            VARCHAR(256)        not null,
   ORI_FILE_NAME        VARCHAR(256),
   UP_DATE              CHAR(8),
   UP_SEQ_NO            INTEGER,
   UP_TIME              CHAR(6),
   UP_UNIT              CHAR(16),
   UP_TELLER            CHAR(16),
   UP_CHANNEL           CHAR(3),
   UPLOAD_TYPE          CHAR(2),
   DC_FLAG              CHAR(1),
   PLAT_DATE            CHAR(8),
   SEQ_NO               INTEGER,
   PLAT_TIME            CHAR(6),
   TX_UNIT              CHAR(16),
   TELLER_NO            CHAR(16),
   CHANNEL_NO           CHAR(3),
   EXEC_DATE            CHAR(8),
   WITHDRAW_DATE        CHAR(8),
   WITHDRAW_SEQ         INTEGER,
   WITHDRAW_TIME        CHAR(6),
   WITHDRAW_UNIT        CHAR(16),
   WITHDRAW_TELLER      CHAR(16),
   WITHDRAW_CHANN       CHAR(3),
   BRIEF_CODE           CHAR(6),
   MD5_CODE             CHAR(40),
   STAT                 CHAR(1),
   RESP_CODE            CHAR(7),
   RESP_MSG             VARCHAR(60),
   RET_FILE_NAME        VARCHAR(256),
   TOT_CNT              INTEGER,
   TOT_AMT              DECIMAL(16,2),
   TOT_SUCC_CNT         INTEGER,
   TOT_SUCC_AMT         DECIMAL(16,2),
   TOT_BUSI_AMT         DECIMAL(16,2),
   TOT_AMT1             DECIMAL(16,2),
   TOT_AMT2             DECIMAL(16,2),
   TOT_AMT3             DECIMAL(16,2),
   TOT_AMT4             DECIMAL(16,2),
   TOT_AMT5             DECIMAL(16,2),
   FULL_CNT             INTEGER,
   FULL_AMT             DECIMAL(16,2),
   PART_CNT             INTEGER,
   PART_AMT             DECIMAL(16,2),
   FEE_CNT              INTEGER,
   FEE                  DECIMAL(16,2),
   REAL_FEE_CNT         INTEGER,
   REAL_FEE             DECIMAL(16,2),
   OPEN_SUCC_CNT        INTEGER,
   OPEN_SUCC_AMT        DECIMAL(16,2),
   OPEN_FAIL_CNT        INTEGER,
   OPEN_FAIL_AMT        DECIMAL(16,2),
   ACCT_DATE            CHAR(8),
   EXTFLD1              VARCHAR(80),
   EXTFLD2              VARCHAR(80),
   EXTFLD3              VARCHAR(80),
   EXTFLD4              VARCHAR(80),
   EXTFLD5              VARCHAR(80),
   EXTFLD6              VARCHAR(160),
   constraint P_K_AGENT_BATCH_INFO_1 primary key (BATCH_NO)
);

CREATE UNIQUE INDEX AGENT_BATCH_INFO_IDX1 ON AGENT_BATCH_INFO(CPDM,DWBH,FILE_NAME);
CREATE INDEX AGENT_BATCH_INFO_IDX2 ON AGENT_BATCH_INFO(UP_DATE,UP_UNIT);
CREATE INDEX AGENT_BATCH_INFO_IDX3 ON AGENT_BATCH_INFO(PLAT_DATE,TX_UNIT);
CREATE INDEX AGENT_BATCH_INFO_IDX4 ON AGENT_BATCH_INFO(EXEC_DATE,STAT);

comment on table AGENT_BATCH_INFO is
'批量代收付导入信息登记簿';

comment on column AGENT_BATCH_INFO.BATCH_NO is
'批次号';

comment on column AGENT_BATCH_INFO.CPDM is
'产品代码';

comment on column AGENT_BATCH_INFO.DWBH is
'单位编号';

comment on column AGENT_BATCH_INFO.FILE_NAME is
'文件名';

comment on column AGENT_BATCH_INFO.ORI_FILE_NAME is
'原上传文件名';

comment on column AGENT_BATCH_INFO.UP_DATE is
'上传日期';

comment on column AGENT_BATCH_INFO.UP_SEQ_NO is
'上传流水号';

comment on column AGENT_BATCH_INFO.UP_TIME is
'上传时间';

comment on column AGENT_BATCH_INFO.UP_UNIT is
'上传机构';

comment on column AGENT_BATCH_INFO.UP_TELLER is
'上传柜员';

comment on column AGENT_BATCH_INFO.UP_CHANNEL is
'上传渠道标识';

comment on column AGENT_BATCH_INFO.UPLOAD_TYPE is
'上传方式 01-缴费平台 02-自有系统 03-线下代理 ';

comment on column AGENT_BATCH_INFO.DC_FLAG is
'收付标志 1-收 2-付';

comment on column AGENT_BATCH_INFO.PLAT_DATE is
'入账申请日期';

comment on column AGENT_BATCH_INFO.SEQ_NO is
'入账申请流水号';

comment on column AGENT_BATCH_INFO.PLAT_TIME is
'入账申请时间';

comment on column AGENT_BATCH_INFO.TX_UNIT is
'入账申请机构';

comment on column AGENT_BATCH_INFO.TELLER_NO is
'入账申请柜员';

comment on column AGENT_BATCH_INFO.CHANNEL_NO is
'入账申请渠道标识';

comment on column AGENT_BATCH_INFO.EXEC_DATE is
'入账运行日期';

comment on column AGENT_BATCH_INFO.WITHDRAW_DATE is
'撤销日期';

comment on column AGENT_BATCH_INFO.WITHDRAW_SEQ is
'撤销流水号';

comment on column AGENT_BATCH_INFO.WITHDRAW_TIME is
'撤销时间';

comment on column AGENT_BATCH_INFO.WITHDRAW_UNIT is
'撤销机构';

comment on column AGENT_BATCH_INFO.WITHDRAW_TELLER is
'撤销柜员';

comment on column AGENT_BATCH_INFO.WITHDRAW_CHANN is
'撤销渠道标识';

comment on column AGENT_BATCH_INFO.BRIEF_CODE is
'摘要代码';

comment on column AGENT_BATCH_INFO.MD5_CODE is
'文件md5码';

comment on column AGENT_BATCH_INFO.STAT is
'导入状态 1-导入成功 2-导入失败 3-回盘成功 4-已撤销 8-待入账申请 9-导入中';

comment on column AGENT_BATCH_INFO.RESP_CODE is
'错误码';

comment on column AGENT_BATCH_INFO.RESP_MSG is
'错误信息';

comment on column AGENT_BATCH_INFO.RET_FILE_NAME is
'回盘文件名';

comment on column AGENT_BATCH_INFO.TOT_CNT is
'总笔数';

comment on column AGENT_BATCH_INFO.TOT_AMT is
'总金额';

comment on column AGENT_BATCH_INFO.TOT_SUCC_CNT is
'成功总笔数';

comment on column AGENT_BATCH_INFO.TOT_SUCC_AMT is
'成功总金额';

comment on column AGENT_BATCH_INFO.TOT_BUSI_AMT is
'成功总业务金额';

comment on column AGENT_BATCH_INFO.TOT_AMT1 is
'成功总费用1';

comment on column AGENT_BATCH_INFO.TOT_AMT2 is
'成功总费用2';

comment on column AGENT_BATCH_INFO.TOT_AMT3 is
'成功总费用3';

comment on column AGENT_BATCH_INFO.TOT_AMT4 is
'成功总费用4';

comment on column AGENT_BATCH_INFO.TOT_AMT5 is
'成功总费用5';

comment on column AGENT_BATCH_INFO.FULL_CNT is
'足额支付总户数';

comment on column AGENT_BATCH_INFO.FULL_AMT is
'足额支付总金额';

comment on column AGENT_BATCH_INFO.PART_CNT is
'部分支付总户数';

comment on column AGENT_BATCH_INFO.PART_AMT is
'部分支付总金额';

comment on column AGENT_BATCH_INFO.FEE_CNT is
'应收手续费总笔数';

comment on column AGENT_BATCH_INFO.FEE is
'应收手续费总金额';

comment on column AGENT_BATCH_INFO.REAL_FEE_CNT is
'实收手续费总笔数';

comment on column AGENT_BATCH_INFO.REAL_FEE is
'实收手续费总金额';

comment on column AGENT_BATCH_INFO.OPEN_SUCC_CNT is
'开户成功总户数';

comment on column AGENT_BATCH_INFO.OPEN_SUCC_AMT is
'开户成功总金额';

comment on column AGENT_BATCH_INFO.OPEN_FAIL_CNT is
'开户失败总户数';

comment on column AGENT_BATCH_INFO.OPEN_FAIL_AMT is
'开户失败总金额';

comment on column AGENT_BATCH_INFO.ACCT_DATE is
'主机记账日期(回盘日期)';

comment on column AGENT_BATCH_INFO.EXTFLD1 is
'扩展字段1';

comment on column AGENT_BATCH_INFO.EXTFLD2 is
'扩展字段2';

comment on column AGENT_BATCH_INFO.EXTFLD3 is
'扩展字段3';

comment on column AGENT_BATCH_INFO.EXTFLD4 is
'扩展字段4';

comment on column AGENT_BATCH_INFO.EXTFLD5 is
'扩展字段5';

comment on column AGENT_BATCH_INFO.EXTFLD6 is
'扩展字段6';

