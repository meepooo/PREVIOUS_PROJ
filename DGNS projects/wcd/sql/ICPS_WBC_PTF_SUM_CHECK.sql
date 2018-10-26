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
'΢����ƽ̨�ѻ��ܶ��˱�';

comment on column ICPS_WBC_PTF_SUM_CHECK.BUSI_TYPE is
'ҵ������';

comment on column ICPS_WBC_PTF_SUM_CHECK.CHECK_DATE is
'��������';

comment on column ICPS_WBC_PTF_SUM_CHECK.BUSI_DATE is
'ҵ������';

comment on column ICPS_WBC_PTF_SUM_CHECK.DT_CCDA is
'΢����ϸ��_ʵ����Ϣ';

comment on column ICPS_WBC_PTF_SUM_CHECK.ST_CCDA is
'΢�ڻ��ܱ�_ʵ����Ϣ';

comment on column ICPS_WBC_PTF_SUM_CHECK.DRC_CCDA is
'����_ʵ����Ϣ';

comment on column ICPS_WBC_PTF_SUM_CHECK.DT_ST_CCDA_DIFF is
'΢��_ʵ����Ϣ_���';

comment on column ICPS_WBC_PTF_SUM_CHECK.DRC_ST_CCDA_DIFF is
'����_ʵ����Ϣ_���';

comment on column ICPS_WBC_PTF_SUM_CHECK.CCDA_CHECK_STATUS is
'ʵ����Ϣ�˶�״̬';

comment on column ICPS_WBC_PTF_SUM_CHECK.DT_CDA is
'΢����ϸ��_ƽ̨��';

comment on column ICPS_WBC_PTF_SUM_CHECK.ST_CDA is
'΢�ڻ��ܱ�_ƽ̨��';

comment on column ICPS_WBC_PTF_SUM_CHECK.DRC_CDA is
'����_ƽ̨��';

comment on column ICPS_WBC_PTF_SUM_CHECK.DT_ST_CDA_DIFF is
'΢��_ƽ̨��_���';

comment on column ICPS_WBC_PTF_SUM_CHECK.DRC_ST_CDA_DIFF is
'����_ƽ̨��_���';

comment on column ICPS_WBC_PTF_SUM_CHECK.CDA_SUM_CHECK_STATUS is
'ƽ̨���ֺܷ˶�״̬';

comment on column ICPS_WBC_PTF_SUM_CHECK.CDA_DETAIL_CHECK_STATUS is
'ƽ̨����ϸ�˶�״̬';

comment on column ICPS_WBC_PTF_SUM_CHECK.CDA_TRANS_STATUS is
'ƽ̨������״̬';

comment on column ICPS_WBC_PTF_SUM_CHECK.RESP_CODE is
'��Ӧ��';

comment on column ICPS_WBC_PTF_SUM_CHECK.RESP_MESSAGE is
'��Ӧ��Ϣ';

comment on column ICPS_WBC_PTF_SUM_CHECK.EXTEND_PARAM1 is
'��չ1';

comment on column ICPS_WBC_PTF_SUM_CHECK.EXTEND_PARAM2 is
'��չ2';

comment on column ICPS_WBC_PTF_SUM_CHECK.EXTEND_PARAM3 is
'��չ3';