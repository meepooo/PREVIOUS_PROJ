drop table agent_upd_custom;
--==============================================================
-- Table: AGENT_UPD_CUSTOM
--==============================================================
create table AGENT_UPD_CUSTOM
(
   BATCH_NO             VARCHAR(32)            not null,
   CPDM                 VARCHAR(16)            not null,
   DWBH                 VARCHAR(16)            not null,
   FILE_NAME            VARCHAR(256)           not null,
   PLAT_DATE            INTEGER,
   SEQ_NO               VARCHAR(16),
   PLAT_TIME            CHAR(6),
   TX_UNIT              VARCHAR(16),
   TELLER_NO            VARCHAR(16),
   CHANNEL_NO           CHAR(3),
   UPLOAD_TYPE          CHAR(2),
   STAT                 CHAR(1),
   RESP_CODE            CHAR(7),
   RESP_MSG             VARCHAR(60),
   RET_FILE_NAME        VARCHAR(256),
   EXTFLD1              VARCHAR(80),
   EXTFLD2              VARCHAR(80),
   EXTFLD3              VARCHAR(80),
   EXTFLD4              VARCHAR(80),
   EXTFLD5              VARCHAR(80),
   EXTFLD6              VARCHAR(160),
   constraint P_K_AGENT_UPD_CUSTOM_1 primary key (BATCH_NO)
);

CREATE INDEX AGENT_UPD_CUSTOM_IDX1 ON AGENT_UPD_CUSTOM(CPDM,DWBH,FILE_NAME,STAT);
CREATE INDEX AGENT_UPD_CUSTOM_IDX2 ON AGENT_UPD_CUSTOM(PLAT_DATE,STAT);

comment on table AGENT_UPD_CUSTOM is
'批量客户协议信息登记簿';

comment on column AGENT_UPD_CUSTOM.BATCH_NO is
'批次号';

comment on column AGENT_UPD_CUSTOM.CPDM is
'产品代码';

comment on column AGENT_UPD_CUSTOM.DWBH is
'单位编号';

comment on column AGENT_UPD_CUSTOM.FILE_NAME is
'文件名';

comment on column AGENT_UPD_CUSTOM.PLAT_DATE is
'平台日期';

comment on column AGENT_UPD_CUSTOM.SEQ_NO is
'平台流水号';

comment on column AGENT_UPD_CUSTOM.PLAT_TIME is
'平台时间';

comment on column AGENT_UPD_CUSTOM.TX_UNIT is
'交易机构';

comment on column AGENT_UPD_CUSTOM.TELLER_NO is
'交易柜员';

comment on column AGENT_UPD_CUSTOM.CHANNEL_NO is
'渠道标识';

comment on column AGENT_UPD_CUSTOM.UPLOAD_TYPE is
'上传方式 01-缴费平台 02-自有系统 03-线下代理 ';

comment on column AGENT_UPD_CUSTOM.STAT is
'导入状态 1-导入成功 2-导入失败 3-回盘成功 4-提交核心 5-提回文件 9-导入中';

comment on column AGENT_UPD_CUSTOM.RESP_CODE is
'错误码';

comment on column AGENT_UPD_CUSTOM.RESP_MSG is
'错误信息';

comment on column AGENT_UPD_CUSTOM.RET_FILE_NAME is
'回盘文件名';

comment on column AGENT_UPD_CUSTOM.EXTFLD1 is
'扩展字段1';

comment on column AGENT_UPD_CUSTOM.EXTFLD2 is
'扩展字段2';

comment on column AGENT_UPD_CUSTOM.EXTFLD3 is
'扩展字段3';

comment on column AGENT_UPD_CUSTOM.EXTFLD4 is
'扩展字段4';

comment on column AGENT_UPD_CUSTOM.EXTFLD5 is
'扩展字段5';

comment on column AGENT_UPD_CUSTOM.EXTFLD6 is
'扩展字段6';

