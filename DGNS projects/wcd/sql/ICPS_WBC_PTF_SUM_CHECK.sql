DROP TABLE ICPS_WBC_PTF_SUM_CHECK;
--==============================================================
-- Table: ICPS_WBC_PTF_SUM_CHECK
--==============================================================
create table ICPS_WBC_PTF_SUM_CHECK
(
   BUSI_TYPE                 VARCHAR(10)            not null,
   CHECK_DATE                VARCHAR(8)             not null,
   BUSI_DATE                 VARCHAR(8)             not null,
   DT_CCDA                   DECIMAL(17,2),
   ST_CCDA                   DECIMAL(17,2),
   DRC_CCDA                  DECIMAL(17,2),
   DT_ST_CCDA_DIFF           DECIMAL(17,2),
   DRC_ST_CCDA_DIFF          DECIMAL(17,2),
   CCDA_CHECK_STATUS         VARCHAR(1),
   DT_CDA                    DECIMAL(17,2),
   ST_CDA                    DECIMAL(17,2),
   DRC_CDA                   DECIMAL(17,2),
   DT_ST_CDA_DIFF            DECIMAL(17,2),
   DRC_ST_CDA_DIFF           DECIMAL(17,2),
   CDA_SUM_CHECK_STATUS      VARCHAR(1),
   CDA_DETAIL_CHECK_STATUS   VARCHAR(1),
   CDA_TRANS_STATUS          VARCHAR(1),
   RESP_CODE                 VARCHAR(8),
   RESP_MESSAGE              VARCHAR(250),
   EXTEND_PARAM1             VARCHAR(100),
   EXTEND_PARAM2             VARCHAR(250),
   EXTEND_PARAM3             VARCHAR(40),
   constraint PK_ICPS_WBC_PTF_SUM_CHECK primary key (BUSI_TYPE, CHECK_DATE, BUSI_DATE)
);

comment on table ICPS_WBC_PTF_SUM_CHECK is
'微车贷平台费汇总对账表';

comment on column ICPS_WBC_PTF_SUM_CHECK.BUSI_TYPE is
'业务类型';

comment on column ICPS_WBC_PTF_SUM_CHECK.CHECK_DATE is
'对账日期';

comment on column ICPS_WBC_PTF_SUM_CHECK.BUSI_DATE is
'业务日期';

comment on column ICPS_WBC_PTF_SUM_CHECK.DT_CCDA is
'微众明细表_实收利息';

comment on column ICPS_WBC_PTF_SUM_CHECK.ST_CCDA is
'微众汇总表_实收利息';

comment on column ICPS_WBC_PTF_SUM_CHECK.DRC_CCDA is
'本行_实收利息';

comment on column ICPS_WBC_PTF_SUM_CHECK.DT_ST_CCDA_DIFF is
'微众_实收利息_差额';

comment on column ICPS_WBC_PTF_SUM_CHECK.DRC_ST_CCDA_DIFF is
'本行_实收利息_差额';

comment on column ICPS_WBC_PTF_SUM_CHECK.CCDA_CHECK_STATUS is
'实收利息核对状态';

comment on column ICPS_WBC_PTF_SUM_CHECK.DT_CDA is
'微众明细表_平台费';

comment on column ICPS_WBC_PTF_SUM_CHECK.ST_CDA is
'微众汇总表_平台费';

comment on column ICPS_WBC_PTF_SUM_CHECK.DRC_CDA is
'本行_平台费';

comment on column ICPS_WBC_PTF_SUM_CHECK.DT_ST_CDA_DIFF is
'微众_平台费_差额';

comment on column ICPS_WBC_PTF_SUM_CHECK.DRC_ST_CDA_DIFF is
'本行_平台费_差额';

comment on column ICPS_WBC_PTF_SUM_CHECK.CDA_SUM_CHECK_STATUS is
'平台费总分核对状态';

comment on column ICPS_WBC_PTF_SUM_CHECK.CDA_DETAIL_CHECK_STATUS is
'平台费明细核对状态';

comment on column ICPS_WBC_PTF_SUM_CHECK.CDA_TRANS_STATUS is
'平台费入账状态';

comment on column ICPS_WBC_PTF_SUM_CHECK.RESP_CODE is
'响应码';

comment on column ICPS_WBC_PTF_SUM_CHECK.RESP_MESSAGE is
'响应信息';

comment on column ICPS_WBC_PTF_SUM_CHECK.EXTEND_PARAM1 is
'扩展1';

comment on column ICPS_WBC_PTF_SUM_CHECK.EXTEND_PARAM2 is
'扩展2';

comment on column ICPS_WBC_PTF_SUM_CHECK.EXTEND_PARAM3 is
'扩展3';