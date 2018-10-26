--==============================================================
-- DBMS name:      IBM DB2 UDB 9.5 Common Server
-- Created on:     2018/8/24 10:16:51
--==============================================================
DROP TABLE ICPS_WBC_TM_APP_MAIN;
DROP TABLE ICPS_WBC_TM_APP_PRIM_APPLICANT_INFO;
DROP TABLE ICPS_WBC_TM_ACCOUNT;
DROP TABLE ICPS_WBC_TM_CUSTOMER;
DROP TABLE ICPS_WBC_TM_PLAN;
DROP TABLE ICPS_WBC_TT_TXN_POST;
DROP TABLE ICPS_WBC_TM_LOAN;
DROP TABLE ICPS_WBC_TM_SCHEDULE;
DROP TABLE ICPS_WBC_TM_CUST_LIMIT_O;
DROP TABLE ICPS_WBC_TM_AUTH_HST;
DROP TABLE ICPS_WBC_TM_AUTH_BANK_COST;
DROP TABLE ICPS_WBC_TM_AUTH_BANK_COST_DTL;
DROP TABLE ICPS_WBC_TM_TXN_CD;
DROP TABLE ICPS_WBC_TM_LOAN_RECEIPT_LIST;
DROP TABLE ICPS_WBC_TM_GL_BAL;
DROP TABLE ICPS_WBC_TM_ACCOUNTING_FLOW;
DROP TABLE ICPS_WBC_TM_LOAN_VMS;
DROP TABLE ICPS_WBC_TM_NBS_CUST;
DROP TABLE ICPS_WBC_TM_MERCHANT_CUST;
DROP TABLE ICPS_WBC_TM_MERCHANT_PRODUCT_CUST;
DROP TABLE ICPS_WBC_TM_AGREEMENT;
DROP TABLE ICPS_WBC_TM_AGREEMENT_CAR;
DROP TABLE ICPS_WBC_TM_AGREEMENT_NO_MAP;
DROP TABLE ICPS_WBC_TM_LOAN_YX;
DROP TABLE ICPS_WBC_TM_NBS_CUST_EXT_INFO;
DROP TABLE ICPS_WBC_KDPL_ZHMINX;
DROP TABLE ICPS_WBC_TM_PSB_CHECK_INFO;
DROP TABLE ICPS_WBC_TM_PSB_PERSONAL_INFO;
DROP TABLE ICPS_WBC_TM_BANK_CREDIT_RESULT;
DROP TABLE ICPS_WBC_TM_BANK;
DROP TABLE ICPS_WBC_TM_BANK_GROUP_MEMBER;
DROP TABLE ICPS_WBC_RRS_BDM_UDF_CLEAR_TOT;
DROP TABLE ICPS_WBC_RRS_BDM_UDF_CLEAR_DETAIL;
DROP TABLE ICPS_WBC_RRS_BDM_UDF_CLEAR_OTHER_DETAIL;
DROP TABLE ICPS_WBC_BANK_GROUP_DFQ_SPLIT_DIFF;
DROP TABLE ICPS_WBC_REPORT_CBS_PTJR_CAR_DATA_PAID_DETAIL_DAY_COOP;
DROP TABLE ICPS_WBC_REPORT_CBS_PTJR_CAR_DATA_PAID_SUM_DAY_COOP;
DROP TABLE ICPS_WBC_DAILY_DIFF;

--==============================================================
-- Table: ICPS_WBC_BANK_GROUP_DFQ_SPLIT_DIFF
--==============================================================
create table GAPSUSR.ICPS_WBC_BANK_GROUP_DFQ_SPLIT_DIFF
(
   BUSI_DATE            CHARACTER(8)           not null,
   FILE_ORDER           INTEGER                not null,
   PARTITION_DATE       VARCHAR(8),
   PRODUCT_CD           VARCHAR(6),
   ERROR_TYPE           VARCHAR(40),
   BANK_GROUP_ID        VARCHAR(10),
   BANK_NO              VARCHAR(20),
   CONSUMER_TRANS_ID    VARCHAR(40),
   REG_TYPE             VARCHAR(10),
   NAME               VARCHAR(80),
   LOGICAL_CARD_NO      VARCHAR(19),
   BF_AMT               DECIMAL(15,2),
   ACCOUNT_AMT          DECIMAL(15,2),
   ERROR_AMT            DECIMAL(15,2),
   IS_CHECK_FLAG        CHARACTER,
   EXTEND_PARAM1        VARCHAR(100),
   EXTEND_PARAM2        VARCHAR(250),
   EXTEND_PARAM3        VARCHAR(40),
   constraint PK_ICPS_WBC_BANK_GROUP_DFQ_SPLIT_DIFF primary key (BUSI_DATE, FILE_ORDER)
) IN GAPS_DATA INDEX IN GAPS_INDEX
;

comment on table GAPSUSR.ICPS_WBC_BANK_GROUP_DFQ_SPLIT_DIFF is
'β�������';

comment on column GAPSUSR.ICPS_WBC_BANK_GROUP_DFQ_SPLIT_DIFF.BUSI_DATE is
'ҵ������';

comment on column GAPSUSR.ICPS_WBC_BANK_GROUP_DFQ_SPLIT_DIFF.FILE_ORDER is
'�ļ����';

comment on column GAPSUSR.ICPS_WBC_BANK_GROUP_DFQ_SPLIT_DIFF.PARTITION_DATE is
'��������';

comment on column GAPSUSR.ICPS_WBC_BANK_GROUP_DFQ_SPLIT_DIFF.PRODUCT_CD is
'��Ʒ���';

comment on column GAPSUSR.ICPS_WBC_BANK_GROUP_DFQ_SPLIT_DIFF.ERROR_TYPE is
'�쳣����';

comment on column GAPSUSR.ICPS_WBC_BANK_GROUP_DFQ_SPLIT_DIFF.BANK_GROUP_ID is
'���ű��';

comment on column GAPSUSR.ICPS_WBC_BANK_GROUP_DFQ_SPLIT_DIFF.BANK_NO is
'���б��';

comment on column GAPSUSR.ICPS_WBC_BANK_GROUP_DFQ_SPLIT_DIFF.CONSUMER_TRANS_ID is
'ҵ����ˮ��';

comment on column GAPSUSR.ICPS_WBC_BANK_GROUP_DFQ_SPLIT_DIFF.REG_TYPE is
'��������';

comment on column GAPSUSR.ICPS_WBC_BANK_GROUP_DFQ_SPLIT_DIFF."NAME" is
'����';

comment on column GAPSUSR.ICPS_WBC_BANK_GROUP_DFQ_SPLIT_DIFF.LOGICAL_CARD_NO is
'�߼�����';

comment on column GAPSUSR.ICPS_WBC_BANK_GROUP_DFQ_SPLIT_DIFF.BF_AMT is
'������������';

comment on column GAPSUSR.ICPS_WBC_BANK_GROUP_DFQ_SPLIT_DIFF.ACCOUNT_AMT is
'CNC���˽��';

comment on column GAPSUSR.ICPS_WBC_BANK_GROUP_DFQ_SPLIT_DIFF.ERROR_AMT is
'Ӧ�������';

comment on column GAPSUSR.ICPS_WBC_BANK_GROUP_DFQ_SPLIT_DIFF.IS_CHECK_FLAG is
'������˱�ʶ';

comment on column GAPSUSR.ICPS_WBC_BANK_GROUP_DFQ_SPLIT_DIFF.EXTEND_PARAM1 is
'��չ1';

comment on column GAPSUSR.ICPS_WBC_BANK_GROUP_DFQ_SPLIT_DIFF.EXTEND_PARAM2 is
'��չ2';

comment on column GAPSUSR.ICPS_WBC_BANK_GROUP_DFQ_SPLIT_DIFF.EXTEND_PARAM3 is
'��չ3';

--==============================================================
-- Table: ICPS_WBC_DAILY_DIFF
--==============================================================
create table ICPS_WBC_DAILY_DIFF
(
   BUSI_TYPE            VARCHAR(10)            not null,
   CHECK_DATE           VARCHAR(8)             not null,
   CHECK_STATUS         VARCHAR(1),
   BUSI_DATE            VARCHAR(8)             not null,
   DRC_BAL              DECIMAL(17,2),
   WB_BAL               DECIMAL(17,2),
   DIFF_CZ              DECIMAL(17,2),
   DIFF_A01             DECIMAL(17,2),
   DIFF_A02             DECIMAL(17,2),
   DIFF_B01             DECIMAL(17,2),
   DIFF_C01             DECIMAL(17,2),
   DIFF_C02             DECIMAL(17,2),
   CLEARING_DAY_AMT     DECIMAL(17,2),
   CLEAR_AMT            DECIMAL(17,2),
   EXTEND_PARAM1        VARCHAR(100),
   EXTEND_PARAM2        VARCHAR(250),
   EXTEND_PARAM3        VARCHAR(40),
   constraint PK_ICPS_WBC_DAILY_DIFF primary key (BUSI_TYPE, CHECK_DATE, BUSI_DATE)
)  IN GAPS_DATA INDEX IN GAPS_INDEX ;

comment on table ICPS_WBC_DAILY_DIFF is
'΢������������˱�';

comment on column ICPS_WBC_DAILY_DIFF.BUSI_TYPE is
'ҵ������';

comment on column ICPS_WBC_DAILY_DIFF.CHECK_DATE is
'��������';

comment on column ICPS_WBC_DAILY_DIFF.CHECK_STATUS is
'����״̬';

comment on column ICPS_WBC_DAILY_DIFF.BUSI_DATE is
'ҵ������';

comment on column ICPS_WBC_DAILY_DIFF.DRC_BAL is
'Ӱ���˻����';

comment on column ICPS_WBC_DAILY_DIFF.WB_BAL is
'���������';

comment on column ICPS_WBC_DAILY_DIFF.DIFF_CZ is
'����';

comment on column ICPS_WBC_DAILY_DIFF.DIFF_A01 is
'A01β��';

comment on column ICPS_WBC_DAILY_DIFF.DIFF_A02 is
'A02β��';

comment on column ICPS_WBC_DAILY_DIFF.DIFF_B01 is
'B01β��';

comment on column ICPS_WBC_DAILY_DIFF.DIFF_C01 is
'C01β��';

comment on column ICPS_WBC_DAILY_DIFF.DIFF_C02 is
'C02β��';

comment on column ICPS_WBC_DAILY_DIFF.CLEARING_DAY_AMT is
'ƽ̨��';

comment on column ICPS_WBC_DAILY_DIFF.CLEAR_AMT is
'������';

comment on column ICPS_WBC_DAILY_DIFF.EXTEND_PARAM1 is
'��չ1';

comment on column ICPS_WBC_DAILY_DIFF.EXTEND_PARAM2 is
'��չ2';

comment on column ICPS_WBC_DAILY_DIFF.EXTEND_PARAM3 is
'��չ3';

--==============================================================
-- Table: ICPS_WBC_KDPL_ZHMINX
--==============================================================
create table GAPSUSR.ICPS_WBC_KDPL_ZHMINX
(
   BUSI_DATE            CHARACTER(8)           not null,
   FILE_ORDER           INTEGER                not null,
   ZHANGHAO             VARCHAR(40),
   MXIXUHAO             DECIMAL(19),
   JIAOYIRQ             VARCHAR(8),
   KHJYMXLB             VARCHAR(1),
   JYYYJIGO             VARCHAR(10),
   KAIHJIGO             VARCHAR(10),
   ZHHUZWMC             VARCHAR(100),
   JIEDAIBZ             VARCHAR(1),
   JIAOYBIZ             VARCHAR(2),
   CHAOHUBZ             VARCHAR(1),
   JIAOYIJE             DECIMAL(21,2),
   ZHANGHYE             DECIMAL(21,2),
   KAHAOOOO             VARCHAR(35),
   KEHUZHAO             VARCHAR(35),
   ZHHAOXUH             VARCHAR(8),
   PNGZZLEI             VARCHAR(4),
   PNGZXHAO             VARCHAR(22),
   ZHAIYODM             VARCHAR(10),
   ZHAIYOMS             VARCHAR(80),
   DUIFJGDM             VARCHAR(20),
   DUIFJGMC             VARCHAR(60),
   DUIFKHZH             VARCHAR(35),
   DUIFMINC             VARCHAR(100),
   DUIFBEZH             VARCHAR(200),
   BEIZHUUU             VARCHAR(200),
   QIXIRIQI             VARCHAR(8),
   QDAOLEIX             VARCHAR(3),
   WAIBCLMA             VARCHAR(20),
   NBJOYIMA             VARCHAR(10),
   XIANZZBZ             VARCHAR(1),
   GUIYLIUS             VARCHAR(32),
   CAOZGUIY             VARCHAR(8),
   ZHUJRIQI             VARCHAR(8),
   ZJYILUSH             VARCHAR(32),
   YEWULUSH             VARCHAR(32),
   JIAOYISJ             VARCHAR(16),
   BCHONGBZ             VARCHAR(1),
   CUOZRIQI             VARCHAR(8),
   CUOZLIUS             VARCHAR(32),
   YSZJYLSH             VARCHAR(32),
   YSYEWUSH             VARCHAR(32),
   CZCZFLEI             VARCHAR(1),
   MOZHANBZ             VARCHAR(1),
   TOKENNNN             VARCHAR(35),
   DSFTOKEN             VARCHAR(35),
   LILVLILV             DECIMAL(11,6),
   JIOYSHIJ             VARCHAR(10),
   HUIDXHAO             VARCHAR(80),
   FARENDMA             VARCHAR(20),
   WEIHGUIY             VARCHAR(8),
   WEIHJIGO             VARCHAR(10),
   WEIHRIQI             VARCHAR(8),
   SHIJCHUO             DECIMAL(19),
   IS_CHECK_FLAG        CHARACTER,
   EXTEND_PARAM1        VARCHAR(100),
   EXTEND_PARAM2        VARCHAR(250),
   EXTEND_PARAM3        VARCHAR(40),
   constraint PK_ICPS_WBC_KDPL_ZHMINX primary key (BUSI_DATE, FILE_ORDER)
) IN GAPS_DATA INDEX IN GAPS_INDEX ;

comment on table GAPSUSR.ICPS_WBC_KDPL_ZHMINX is
'���պ��������˺ţ����˺���������д�����ϸ��';

comment on column GAPSUSR.ICPS_WBC_KDPL_ZHMINX.BUSI_DATE is
'ҵ������';

comment on column GAPSUSR.ICPS_WBC_KDPL_ZHMINX.FILE_ORDER is
'�ļ����';

comment on column GAPSUSR.ICPS_WBC_KDPL_ZHMINX.ZHANGHAO is
'��ծ�˺�';

comment on column GAPSUSR.ICPS_WBC_KDPL_ZHMINX.MXIXUHAO is
'��ϸ���';

comment on column GAPSUSR.ICPS_WBC_KDPL_ZHMINX.JIAOYIRQ is
'��������';

comment on column GAPSUSR.ICPS_WBC_KDPL_ZHMINX.KHJYMXLB is
'�ͻ�������ϸ���';

comment on column GAPSUSR.ICPS_WBC_KDPL_ZHMINX.JYYYJIGO is
'����Ӫҵ����';

comment on column GAPSUSR.ICPS_WBC_KDPL_ZHMINX.KAIHJIGO is
'�˻���������';

comment on column GAPSUSR.ICPS_WBC_KDPL_ZHMINX.ZHHUZWMC is
'�˻�����';

comment on column GAPSUSR.ICPS_WBC_KDPL_ZHMINX.JIEDAIBZ is
'�����־';

comment on column GAPSUSR.ICPS_WBC_KDPL_ZHMINX.JIAOYBIZ is
'���ױ���';

comment on column GAPSUSR.ICPS_WBC_KDPL_ZHMINX.CHAOHUBZ is
'�˻������־';

comment on column GAPSUSR.ICPS_WBC_KDPL_ZHMINX.JIAOYIJE is
'���׽��';

comment on column GAPSUSR.ICPS_WBC_KDPL_ZHMINX.ZHANGHYE is
'�˻����';

comment on column GAPSUSR.ICPS_WBC_KDPL_ZHMINX.KAHAOOOO is
'����';

comment on column GAPSUSR.ICPS_WBC_KDPL_ZHMINX.KEHUZHAO is
'�ͻ��˺�';

comment on column GAPSUSR.ICPS_WBC_KDPL_ZHMINX.ZHHAOXUH is
'���˻����';

comment on column GAPSUSR.ICPS_WBC_KDPL_ZHMINX.PNGZZLEI is
'ƾ֤����';

comment on column GAPSUSR.ICPS_WBC_KDPL_ZHMINX.PNGZXHAO is
'ƾ֤��';

comment on column GAPSUSR.ICPS_WBC_KDPL_ZHMINX.ZHAIYODM is
'ժҪ����';

comment on column GAPSUSR.ICPS_WBC_KDPL_ZHMINX.ZHAIYOMS is
'ժҪ����';

comment on column GAPSUSR.ICPS_WBC_KDPL_ZHMINX.DUIFJGDM is
'�Է����ڻ���';

comment on column GAPSUSR.ICPS_WBC_KDPL_ZHMINX.DUIFJGMC is
'�Է����ڻ�������';

comment on column GAPSUSR.ICPS_WBC_KDPL_ZHMINX.DUIFKHZH is
'�Է��ͻ��˺�';

comment on column GAPSUSR.ICPS_WBC_KDPL_ZHMINX.DUIFMINC is
'�Է�����';

comment on column GAPSUSR.ICPS_WBC_KDPL_ZHMINX.DUIFBEZH is
'�Է���ע';

comment on column GAPSUSR.ICPS_WBC_KDPL_ZHMINX.BEIZHUUU is
'��ע';

comment on column GAPSUSR.ICPS_WBC_KDPL_ZHMINX.QIXIRIQI is
'��Ϣ����';

comment on column GAPSUSR.ICPS_WBC_KDPL_ZHMINX.QDAOLEIX is
'��������';

comment on column GAPSUSR.ICPS_WBC_KDPL_ZHMINX.WAIBCLMA is
'���˴���';

comment on column GAPSUSR.ICPS_WBC_KDPL_ZHMINX.NBJOYIMA is
'�ڲ�������';

comment on column GAPSUSR.ICPS_WBC_KDPL_ZHMINX.XIANZZBZ is
'��ת��־';

comment on column GAPSUSR.ICPS_WBC_KDPL_ZHMINX.GUIYLIUS is
'��Ա��ˮ(��������ˮ)';

comment on column GAPSUSR.ICPS_WBC_KDPL_ZHMINX.CAOZGUIY is
'������Ա';

comment on column GAPSUSR.ICPS_WBC_KDPL_ZHMINX.ZHUJRIQI is
'��������';

comment on column GAPSUSR.ICPS_WBC_KDPL_ZHMINX.ZJYILUSH is
'��������ˮ';

comment on column GAPSUSR.ICPS_WBC_KDPL_ZHMINX.YEWULUSH is
'ҵ����ˮ';

comment on column GAPSUSR.ICPS_WBC_KDPL_ZHMINX.JIAOYISJ is
'����ʱ��';

comment on column GAPSUSR.ICPS_WBC_KDPL_ZHMINX.BCHONGBZ is
'������ϸ״̬';

comment on column GAPSUSR.ICPS_WBC_KDPL_ZHMINX.CUOZRIQI is
'ԭ��������';

comment on column GAPSUSR.ICPS_WBC_KDPL_ZHMINX.CUOZLIUS is
'ԭ���˽�����ˮ';

comment on column GAPSUSR.ICPS_WBC_KDPL_ZHMINX.YSZJYLSH is
'ԭʼ��������ˮ';

comment on column GAPSUSR.ICPS_WBC_KDPL_ZHMINX.YSYEWUSH is
'ԭʼҵ����ˮ';

comment on column GAPSUSR.ICPS_WBC_KDPL_ZHMINX.CZCZFLEI is
'�������˷���';

comment on column GAPSUSR.ICPS_WBC_KDPL_ZHMINX.MOZHANBZ is
'Ĩ�˱�־';

comment on column GAPSUSR.ICPS_WBC_KDPL_ZHMINX.TOKENNNN is
'token';

comment on column GAPSUSR.ICPS_WBC_KDPL_ZHMINX.DSFTOKEN is
'���ַ�token';

comment on column GAPSUSR.ICPS_WBC_KDPL_ZHMINX.LILVLILV is
'����';

comment on column GAPSUSR.ICPS_WBC_KDPL_ZHMINX.JIOYSHIJ is
'�����¼�';

comment on column GAPSUSR.ICPS_WBC_KDPL_ZHMINX.HUIDXHAO is
'�ص����';

comment on column GAPSUSR.ICPS_WBC_KDPL_ZHMINX.FARENDMA is
'���˴���';

comment on column GAPSUSR.ICPS_WBC_KDPL_ZHMINX.WEIHGUIY is
'ά����Ա';

comment on column GAPSUSR.ICPS_WBC_KDPL_ZHMINX.WEIHJIGO is
'ά������';

comment on column GAPSUSR.ICPS_WBC_KDPL_ZHMINX.WEIHRIQI is
'ά������';

comment on column GAPSUSR.ICPS_WBC_KDPL_ZHMINX.SHIJCHUO is
'ʱ���';

comment on column GAPSUSR.ICPS_WBC_KDPL_ZHMINX.IS_CHECK_FLAG is
'������˱�ʶ';

comment on column GAPSUSR.ICPS_WBC_KDPL_ZHMINX.EXTEND_PARAM1 is
'��չ1';

comment on column GAPSUSR.ICPS_WBC_KDPL_ZHMINX.EXTEND_PARAM2 is
'��չ2';

comment on column GAPSUSR.ICPS_WBC_KDPL_ZHMINX.EXTEND_PARAM3 is
'��չ3';

--===============================================================
-- Table: ICPS_WBC_REPORT_CBS_PTJR_CAR_DATA_PAID_DETAIL_DAY_COOP
--===============================================================
create table GAPSUSR.ICPS_WBC_REPORT_CBS_PTJR_CAR_DATA_PAID_DETAIL_DAY_COOP
(
   BUSI_DATE            CHARACTER(8)           not null,
   FILE_ORDER           INTEGER                not null,
   PARTITION_DATE       VARCHAR(10),
   BANK_GROUP_ID        VARCHAR(32),
   ORG_NO               VARCHAR(32),
   FEE_NAME             VARCHAR(260),
   LOAN_RECEIPT_NBR     VARCHAR(32),
   TXN_DATE             VARCHAR(30),
   CLEARING_CALC_DAY_AMT DECIMAL(15,2),
   CLEARING_DAY_AMT     DECIMAL(15,2),
   CLEARING_DAY_NO_VAT_AMT DECIMAL(15,2),
   CLEARING_DAY_VAT_AMT DECIMAL(15,2),
   INTEREST_RATE        DECIMAL(12,4),
   FUND_RATIO           DECIMAL(15,8),
   IS_CHECK_FLAG        CHARACTER,
   EXTEND_PARAM1        VARCHAR(100),
   EXTEND_PARAM2        VARCHAR(250),
   EXTEND_PARAM3        VARCHAR(40),
   constraint PK_ICPS_WBC_REPORT_CBS_PTJR_CAR_DATA_PAID_DETAIL_DAY_COOP primary key (BUSI_DATE, FILE_ORDER)
)  IN GAPS_DATA INDEX IN GAPS_INDEX ;

comment on table GAPSUSR.ICPS_WBC_REPORT_CBS_PTJR_CAR_DATA_PAID_DETAIL_DAY_COOP is
'CBS�������ϸ����';

comment on column GAPSUSR.ICPS_WBC_REPORT_CBS_PTJR_CAR_DATA_PAID_DETAIL_DAY_COOP.BUSI_DATE is
'ҵ������';

comment on column GAPSUSR.ICPS_WBC_REPORT_CBS_PTJR_CAR_DATA_PAID_DETAIL_DAY_COOP.FILE_ORDER is
'�ļ����';

comment on column GAPSUSR.ICPS_WBC_REPORT_CBS_PTJR_CAR_DATA_PAID_DETAIL_DAY_COOP.PARTITION_DATE is
'��������';

comment on column GAPSUSR.ICPS_WBC_REPORT_CBS_PTJR_CAR_DATA_PAID_DETAIL_DAY_COOP.BANK_GROUP_ID is
'���ű��';

comment on column GAPSUSR.ICPS_WBC_REPORT_CBS_PTJR_CAR_DATA_PAID_DETAIL_DAY_COOP.ORG_NO is
'������������';

comment on column GAPSUSR.ICPS_WBC_REPORT_CBS_PTJR_CAR_DATA_PAID_DETAIL_DAY_COOP.FEE_NAME is
'��������';

comment on column GAPSUSR.ICPS_WBC_REPORT_CBS_PTJR_CAR_DATA_PAID_DETAIL_DAY_COOP.LOAN_RECEIPT_NBR is
'��ݺ�';

comment on column GAPSUSR.ICPS_WBC_REPORT_CBS_PTJR_CAR_DATA_PAID_DETAIL_DAY_COOP.TXN_DATE is
'���׷�����������';

comment on column GAPSUSR.ICPS_WBC_REPORT_CBS_PTJR_CAR_DATA_PAID_DETAIL_DAY_COOP.CLEARING_CALC_DAY_AMT is
'ʵ����Ϣ';

comment on column GAPSUSR.ICPS_WBC_REPORT_CBS_PTJR_CAR_DATA_PAID_DETAIL_DAY_COOP.CLEARING_DAY_AMT is
'ƽ̨��';

comment on column GAPSUSR.ICPS_WBC_REPORT_CBS_PTJR_CAR_DATA_PAID_DETAIL_DAY_COOP.CLEARING_DAY_NO_VAT_AMT is
'����ƽ̨�ѣ�����˰��';

comment on column GAPSUSR.ICPS_WBC_REPORT_CBS_PTJR_CAR_DATA_PAID_DETAIL_DAY_COOP.CLEARING_DAY_VAT_AMT is
'����ƽ̨�ѣ�˰��';

comment on column GAPSUSR.ICPS_WBC_REPORT_CBS_PTJR_CAR_DATA_PAID_DETAIL_DAY_COOP.INTEREST_RATE is
'����';

comment on column GAPSUSR.ICPS_WBC_REPORT_CBS_PTJR_CAR_DATA_PAID_DETAIL_DAY_COOP.FUND_RATIO is
'�ʽ𶨼�';

comment on column GAPSUSR.ICPS_WBC_REPORT_CBS_PTJR_CAR_DATA_PAID_DETAIL_DAY_COOP.IS_CHECK_FLAG is
'������˱�ʶ';

comment on column GAPSUSR.ICPS_WBC_REPORT_CBS_PTJR_CAR_DATA_PAID_DETAIL_DAY_COOP.EXTEND_PARAM1 is
'��չ1';

comment on column GAPSUSR.ICPS_WBC_REPORT_CBS_PTJR_CAR_DATA_PAID_DETAIL_DAY_COOP.EXTEND_PARAM2 is
'��չ2';

comment on column GAPSUSR.ICPS_WBC_REPORT_CBS_PTJR_CAR_DATA_PAID_DETAIL_DAY_COOP.EXTEND_PARAM3 is
'��չ3';

--==============================================================
-- Table: ICPS_WBC_REPORT_CBS_PTJR_CAR_DATA_PAID_SUM_DAY_COOP
--==============================================================
create table GAPSUSR.ICPS_WBC_REPORT_CBS_PTJR_CAR_DATA_PAID_SUM_DAY_COOP
(
   BUSI_DATE            CHARACTER(8)           not null,
   FILE_ORDER           INTEGER                not null,
   PARTITION_DATE       VARCHAR(10),
   BANK_GROUP_ID        VARCHAR(32),
   CLEARING_CALC_DAY_AMT DECIMAL(15,2),
   CLEARING_DAY_NO_VAT_AMT DECIMAL(15,2),
   CLEARING_DAY_VAT_AMT DECIMAL(15,2),
   TXN_NUM              INTEGER,
   CLEARING_DAY_AMT     DECIMAL(15,2),
   IS_CHECK_FLAG        CHARACTER,
   EXTEND_PARAM1        VARCHAR(100),
   EXTEND_PARAM2        VARCHAR(250),
   EXTEND_PARAM3        VARCHAR(40),
   constraint PK_ICPS_WBC_REPORT_CBS_PTJR_CAR_DATA_PAID_SUM_DAY_COOP primary key (BUSI_DATE, FILE_ORDER)
)  IN GAPS_DATA INDEX IN GAPS_INDEX ;

comment on table GAPSUSR.ICPS_WBC_REPORT_CBS_PTJR_CAR_DATA_PAID_SUM_DAY_COOP is
'CBS�������ܱ���';

comment on column GAPSUSR.ICPS_WBC_REPORT_CBS_PTJR_CAR_DATA_PAID_SUM_DAY_COOP.BUSI_DATE is
'ҵ������';

comment on column GAPSUSR.ICPS_WBC_REPORT_CBS_PTJR_CAR_DATA_PAID_SUM_DAY_COOP.FILE_ORDER is
'�ļ����';

comment on column GAPSUSR.ICPS_WBC_REPORT_CBS_PTJR_CAR_DATA_PAID_SUM_DAY_COOP.PARTITION_DATE is
'��������';

comment on column GAPSUSR.ICPS_WBC_REPORT_CBS_PTJR_CAR_DATA_PAID_SUM_DAY_COOP.BANK_GROUP_ID is
'���ű��';

comment on column GAPSUSR.ICPS_WBC_REPORT_CBS_PTJR_CAR_DATA_PAID_SUM_DAY_COOP.CLEARING_CALC_DAY_AMT is
'ʵ����Ϣ';

comment on column GAPSUSR.ICPS_WBC_REPORT_CBS_PTJR_CAR_DATA_PAID_SUM_DAY_COOP.CLEARING_DAY_NO_VAT_AMT is
'����ƽ̨�ѣ�����˰��';

comment on column GAPSUSR.ICPS_WBC_REPORT_CBS_PTJR_CAR_DATA_PAID_SUM_DAY_COOP.CLEARING_DAY_VAT_AMT is
'����ƽ̨�ѣ�˰��';

comment on column GAPSUSR.ICPS_WBC_REPORT_CBS_PTJR_CAR_DATA_PAID_SUM_DAY_COOP.TXN_NUM is
'������';

comment on column GAPSUSR.ICPS_WBC_REPORT_CBS_PTJR_CAR_DATA_PAID_SUM_DAY_COOP.CLEARING_DAY_AMT is
'ƽ̨��';

comment on column GAPSUSR.ICPS_WBC_REPORT_CBS_PTJR_CAR_DATA_PAID_SUM_DAY_COOP.IS_CHECK_FLAG is
'������˱�ʶ';

comment on column GAPSUSR.ICPS_WBC_REPORT_CBS_PTJR_CAR_DATA_PAID_SUM_DAY_COOP.EXTEND_PARAM1 is
'��չ1';

comment on column GAPSUSR.ICPS_WBC_REPORT_CBS_PTJR_CAR_DATA_PAID_SUM_DAY_COOP.EXTEND_PARAM2 is
'��չ2';

comment on column GAPSUSR.ICPS_WBC_REPORT_CBS_PTJR_CAR_DATA_PAID_SUM_DAY_COOP.EXTEND_PARAM3 is
'��չ3';

--==============================================================
-- Table: ICPS_WBC_RRS_BDM_UDF_CLEAR_DETAIL
--==============================================================
create table GAPSUSR.ICPS_WBC_RRS_BDM_UDF_CLEAR_DETAIL
(
   BUSI_DATE            CHARACTER(8)           not null,
   FILE_ORDER           INTEGER                not null,
   DATA_DT              VARCHAR(10),
   ACCT_NO              VARCHAR(40),
   CCY                  VARCHAR(3),
   BANK_GROUP_CODE      VARCHAR(5),
   DATA_TYPE            VARCHAR(6),
   AMOUNT               DECIMAL(20,4),
   DS                   VARCHAR(10),
   IS_CHECK_FLAG        CHARACTER,
   EXTEND_PARAM1        VARCHAR(100),
   EXTEND_PARAM2        VARCHAR(250),
   EXTEND_PARAM3        VARCHAR(40),
   constraint PK_ICPS_WBC_RRS_BDM_UDF_CLEAR_DETAIL primary key (BUSI_DATE, FILE_ORDER)
)  IN GAPS_DATA INDEX IN GAPS_INDEX ;

comment on table GAPSUSR.ICPS_WBC_RRS_BDM_UDF_CLEAR_DETAIL is
'�������ʽ�������ϸ';

comment on column GAPSUSR.ICPS_WBC_RRS_BDM_UDF_CLEAR_DETAIL.BUSI_DATE is
'ҵ������';

comment on column GAPSUSR.ICPS_WBC_RRS_BDM_UDF_CLEAR_DETAIL.FILE_ORDER is
'�ļ����';

comment on column GAPSUSR.ICPS_WBC_RRS_BDM_UDF_CLEAR_DETAIL.DATA_DT is
'��������';

comment on column GAPSUSR.ICPS_WBC_RRS_BDM_UDF_CLEAR_DETAIL.ACCT_NO is
'�������ʺ�';

comment on column GAPSUSR.ICPS_WBC_RRS_BDM_UDF_CLEAR_DETAIL.CCY is
'����';

comment on column GAPSUSR.ICPS_WBC_RRS_BDM_UDF_CLEAR_DETAIL.BANK_GROUP_CODE is
'���ű��';

comment on column GAPSUSR.ICPS_WBC_RRS_BDM_UDF_CLEAR_DETAIL.DATA_TYPE is
'��������';

comment on column GAPSUSR.ICPS_WBC_RRS_BDM_UDF_CLEAR_DETAIL.AMOUNT is
'������';

comment on column GAPSUSR.ICPS_WBC_RRS_BDM_UDF_CLEAR_DETAIL.DS is
'���ڷ���';

comment on column GAPSUSR.ICPS_WBC_RRS_BDM_UDF_CLEAR_DETAIL.IS_CHECK_FLAG is
'������˱�ʶ';

comment on column GAPSUSR.ICPS_WBC_RRS_BDM_UDF_CLEAR_DETAIL.EXTEND_PARAM1 is
'��չ1';

comment on column GAPSUSR.ICPS_WBC_RRS_BDM_UDF_CLEAR_DETAIL.EXTEND_PARAM2 is
'��չ2';

comment on column GAPSUSR.ICPS_WBC_RRS_BDM_UDF_CLEAR_DETAIL.EXTEND_PARAM3 is
'��չ3';

--==============================================================
-- Table: ICPS_WBC_RRS_BDM_UDF_CLEAR_OTHER_DETAIL
--==============================================================
create table GAPSUSR.ICPS_WBC_RRS_BDM_UDF_CLEAR_OTHER_DETAIL
(
   BUSI_DATE            CHARACTER(8)           not null,
   FILE_ORDER           INTEGER                not null,
   DATA_DT              VARCHAR(10),
   ACCT_NO              VARCHAR(40),
   CCY                  VARCHAR(3),
   BANK_GROUP_CODE      VARCHAR(5),
   DATA_TYPE            VARCHAR(6),
   SER_NO               VARCHAR(20),
   AMOUNT               DECIMAL(20,4),
   MEMO                 VARCHAR(200),
   DS                   VARCHAR(10),
   IS_CHECK_FLAG        CHARACTER,
   EXTEND_PARAM1        VARCHAR(100),
   EXTEND_PARAM2        VARCHAR(250),
   EXTEND_PARAM3        VARCHAR(40),
   constraint PK_ICPS_WBC_RRS_BDM_UDF_CLEAR_OTHER_DETAIL primary key (BUSI_DATE, FILE_ORDER)
)  IN GAPS_DATA INDEX IN GAPS_INDEX ;

comment on table GAPSUSR.ICPS_WBC_RRS_BDM_UDF_CLEAR_OTHER_DETAIL is
'���������������ʽ���ϸ';

comment on column GAPSUSR.ICPS_WBC_RRS_BDM_UDF_CLEAR_OTHER_DETAIL.BUSI_DATE is
'ҵ������';

comment on column GAPSUSR.ICPS_WBC_RRS_BDM_UDF_CLEAR_OTHER_DETAIL.FILE_ORDER is
'�ļ����';

comment on column GAPSUSR.ICPS_WBC_RRS_BDM_UDF_CLEAR_OTHER_DETAIL.DATA_DT is
'��������';

comment on column GAPSUSR.ICPS_WBC_RRS_BDM_UDF_CLEAR_OTHER_DETAIL.ACCT_NO is
'�������ʺ�';

comment on column GAPSUSR.ICPS_WBC_RRS_BDM_UDF_CLEAR_OTHER_DETAIL.CCY is
'����';

comment on column GAPSUSR.ICPS_WBC_RRS_BDM_UDF_CLEAR_OTHER_DETAIL.BANK_GROUP_CODE is
'���ű��';

comment on column GAPSUSR.ICPS_WBC_RRS_BDM_UDF_CLEAR_OTHER_DETAIL.DATA_TYPE is
'��������';

comment on column GAPSUSR.ICPS_WBC_RRS_BDM_UDF_CLEAR_OTHER_DETAIL.SER_NO is
'��ϸ���';

comment on column GAPSUSR.ICPS_WBC_RRS_BDM_UDF_CLEAR_OTHER_DETAIL.AMOUNT is
'������';

comment on column GAPSUSR.ICPS_WBC_RRS_BDM_UDF_CLEAR_OTHER_DETAIL.MEMO is
'��ע';

comment on column GAPSUSR.ICPS_WBC_RRS_BDM_UDF_CLEAR_OTHER_DETAIL.DS is
'���ڷ���';

comment on column GAPSUSR.ICPS_WBC_RRS_BDM_UDF_CLEAR_OTHER_DETAIL.IS_CHECK_FLAG is
'������˱�ʶ';

comment on column GAPSUSR.ICPS_WBC_RRS_BDM_UDF_CLEAR_OTHER_DETAIL.EXTEND_PARAM1 is
'��չ1';

comment on column GAPSUSR.ICPS_WBC_RRS_BDM_UDF_CLEAR_OTHER_DETAIL.EXTEND_PARAM2 is
'��չ2';

comment on column GAPSUSR.ICPS_WBC_RRS_BDM_UDF_CLEAR_OTHER_DETAIL.EXTEND_PARAM3 is
'��չ3';

--==============================================================
-- Table: ICPS_WBC_RRS_BDM_UDF_CLEAR_TOT
--==============================================================
create table GAPSUSR.ICPS_WBC_RRS_BDM_UDF_CLEAR_TOT
(
   BUSI_DATE            CHARACTER(8)           not null,
   FILE_ORDER           INTEGER                not null,
   DATA_DT              VARCHAR(10),
   ACCT_NO              VARCHAR(40),
   CCY                  VARCHAR(3),
   ACCT_NAME            VARCHAR(100),
   LAST_BALANCE         DECIMAL(20,4),
   BALANCE              DECIMAL(20,4),
   PAYMENT_AMT          DECIMAL(20,4),
   REPAYMENT_AMT        DECIMAL(20,4),
   OTHER_CREDIT_AMT     DECIMAL(20,4),
   OTHER_DEBIT_AMT      DECIMAL(20,4),
   DS                   VARCHAR(10),
   IS_CHECK_FLAG        CHARACTER,
   EXTEND_PARAM1        VARCHAR(100),
   EXTEND_PARAM2        VARCHAR(250),
   EXTEND_PARAM3        VARCHAR(40),
   constraint PK_ICPS_WBC_RRS_BDM_UDF_CLEAR_TOT primary key (BUSI_DATE, FILE_ORDER)
)  IN GAPS_DATA INDEX IN GAPS_INDEX ;

comment on table GAPSUSR.ICPS_WBC_RRS_BDM_UDF_CLEAR_TOT is
'�������ʽ��������';

comment on column GAPSUSR.ICPS_WBC_RRS_BDM_UDF_CLEAR_TOT.BUSI_DATE is
'ҵ������';

comment on column GAPSUSR.ICPS_WBC_RRS_BDM_UDF_CLEAR_TOT.FILE_ORDER is
'�ļ����';

comment on column GAPSUSR.ICPS_WBC_RRS_BDM_UDF_CLEAR_TOT.DATA_DT is
'��������';

comment on column GAPSUSR.ICPS_WBC_RRS_BDM_UDF_CLEAR_TOT.ACCT_NO is
'�������ʺ�';

comment on column GAPSUSR.ICPS_WBC_RRS_BDM_UDF_CLEAR_TOT.CCY is
'����';

comment on column GAPSUSR.ICPS_WBC_RRS_BDM_UDF_CLEAR_TOT.ACCT_NAME is
'����';

comment on column GAPSUSR.ICPS_WBC_RRS_BDM_UDF_CLEAR_TOT.LAST_BALANCE is
'�����˻����';

comment on column GAPSUSR.ICPS_WBC_RRS_BDM_UDF_CLEAR_TOT.BALANCE is
'�����˻����';

comment on column GAPSUSR.ICPS_WBC_RRS_BDM_UDF_CLEAR_TOT.PAYMENT_AMT is
'���շſ��ܽ��';

comment on column GAPSUSR.ICPS_WBC_RRS_BDM_UDF_CLEAR_TOT.REPAYMENT_AMT is
'���ջ����ܽ��';

comment on column GAPSUSR.ICPS_WBC_RRS_BDM_UDF_CLEAR_TOT.OTHER_CREDIT_AMT is
'���������������';

comment on column GAPSUSR.ICPS_WBC_RRS_BDM_UDF_CLEAR_TOT.OTHER_DEBIT_AMT is
'����������������';

comment on column GAPSUSR.ICPS_WBC_RRS_BDM_UDF_CLEAR_TOT.DS is
'���ڷ���';

comment on column GAPSUSR.ICPS_WBC_RRS_BDM_UDF_CLEAR_TOT.IS_CHECK_FLAG is
'������˱�ʶ';

comment on column GAPSUSR.ICPS_WBC_RRS_BDM_UDF_CLEAR_TOT.EXTEND_PARAM1 is
'��չ1';

comment on column GAPSUSR.ICPS_WBC_RRS_BDM_UDF_CLEAR_TOT.EXTEND_PARAM2 is
'��չ2';

comment on column GAPSUSR.ICPS_WBC_RRS_BDM_UDF_CLEAR_TOT.EXTEND_PARAM3 is
'��չ3';

--==============================================================
-- Table: ICPS_WBC_TM_ACCOUNT
--==============================================================
create table GAPSUSR.ICPS_WBC_TM_ACCOUNT
(
   BUSI_DATE            CHARACTER(8)           not null,
   FILE_ORDER           INTEGER                not null,
   ORG                  CHARACTER(12),
   ACCT_NO              VARCHAR(20),
   ACCT_TYPE            CHARACTER,
   CUST_ID              VARCHAR(20),
   CUST_LIMIT_ID        VARCHAR(20),
   PRODUCT_CD           CHARACTER(6),
   DEFAULT_LOGICAL_CARD_NO VARCHAR(19),
   CURR_CD              CHARACTER(3),
   CREDIT_LIMIT         DECIMAL(13,2),
   TEMP_LIMIT           DECIMAL(13,2),
   TEMP_LIMIT_BEGIN_DATE VARCHAR(8),
   TEMP_LIMIT_END_DATE  VARCHAR(8),
   CASH_LIMIT_RT        DECIMAL(5,2),
   OVRLMT_RATE          DECIMAL(5,2),
   LOAN_LIMIT_RT        DECIMAL(5,2),
   CURR_BAL             DECIMAL(15,2),
   CASH_BAL             DECIMAL(15,2),
   PRINCIPAL_BAL        DECIMAL(15,2),
   LOAN_BAL             DECIMAL(15,2),
   DISPUTE_AMT          DECIMAL(15,2),
   BEGIN_BAL            DECIMAL(15,2),
   PMT_DUE_DAY_BAL      DECIMAL(15,2),
   QUAL_GRACE_BAL       DECIMAL(15,2),
   GRACE_DAYS_FULL_IND  CHARACTER,
   POINT_BEGIN_BAL      DECIMAL(13,2),
   CTD_EARNED_POINTS    DECIMAL(13,2),
   CTD_DISB_POINTS      DECIMAL(13,2),
   CTD_ADJ_POINTS       DECIMAL(13,2),
   POINT_BAL            DECIMAL(13,2),
   SETUP_DATE           VARCHAR(8),
   DORMENT_DATE         VARCHAR(8),
   REINSTATE_DATE       VARCHAR(8),
   OVRLMT_DATE          VARCHAR(8),
   OVRLMT_NBR_OF_CYC    INTEGER,
   "NAME"               VARCHAR(80),
   GENDER               CHARACTER,
   OWNING_BRANCH        VARCHAR(9),
   MOBILE_NO            VARCHAR(20),
   CORP_NAME            VARCHAR(200),
   BILLING_CYCLE        CHARACTER(2),
   STMT_FLAG            CHARACTER,
   STMT_MAIL_ADDR_IND   CHARACTER,
   STMT_MEDIA_TYPE      CHARACTER,
   STMT_COUNTRY_CD      CHARACTER(3),
   STMT_STATE           VARCHAR(40),
   STMT_CITY            VARCHAR(40),
   STMT_DISTRICT        VARCHAR(40),
   STMT_ADDRESS         VARCHAR(200),
   STMT_ZIP             VARCHAR(10),
   EMAIL                VARCHAR(80),
   BLOCK_CODE           VARCHAR(27),
   AGE_CD               CHARACTER,
   GL_AGE_CD            CHARACTER,
   UNMATCH_DB           DECIMAL(15,2),
   UNMATCH_CASH         DECIMAL(15,2),
   UNMATCH_CR           DECIMAL(15,2),
   DD_IND               CHARACTER,
   DD_BANK_NAME         VARCHAR(80),
   DD_BANK_BRANCH       VARCHAR(14),
   DD_BANK_ACCT_NO      VARCHAR(40),
   DD_BANK_ACCT_NAME    VARCHAR(80),
   LAST_DD_AMT          DECIMAL(15,2),
   LAST_DD_DATE         VARCHAR(14),
   DUAL_BILLING_FLAG    CHARACTER,
   LAST_PMT_AMT         DECIMAL(15,2),
   LAST_PMT_DATE        VARCHAR(14),
   LAST_STMT_DATE       VARCHAR(14),
   LAST_PMT_DUE_DATE    VARCHAR(14),
   LAST_AGING_DATE      VARCHAR(14),
   COLLECT_DATE         VARCHAR(14),
   COLLECT_OUT_DATE     VARCHAR(14),
   NEXT_STMT_DATE       VARCHAR(14),
   PMT_DUE_DATE         VARCHAR(14),
   DD_DATE              VARCHAR(14),
   GRACE_DATE           VARCHAR(14),
   DLBL_DATE            VARCHAR(14),
   CLOSED_DATE          VARCHAR(14),
   FIRST_STMT_DATE      VARCHAR(14),
   CANCEL_DATE          VARCHAR(14),
   CHARGE_OFF_DATE      VARCHAR(14),
   FIRST_PURCHASE_DATE  VARCHAR(14),
   FIRST_PURCHASE_AMT   DECIMAL(15,2),
   TOT_DUE_AMT          DECIMAL(15,2),
   CURR_DUE_AMT         DECIMAL(15,2),
   PAST_DUE_AMT1        DECIMAL(15,2),
   PAST_DUE_AMT2        DECIMAL(15,2),
   PAST_DUE_AMT3        DECIMAL(15,2),
   PAST_DUE_AMT4        DECIMAL(15,2),
   PAST_DUE_AMT5        DECIMAL(15,2),
   PAST_DUE_AMT6        DECIMAL(15,2),
   PAST_DUE_AMT7        DECIMAL(15,2),
   PAST_DUE_AMT8        DECIMAL(15,2),
   CTD_CASH_AMT         DECIMAL(15,2),
   CTD_CASH_CNT         INTEGER,
   CTD_RETAIL_AMT       DECIMAL(15,2),
   CTD_RETAIL_CNT       INTEGER,
   CTD_PAYMENT_AMT      DECIMAL(15,2),
   CTD_PAYMENT_CNT      INTEGER,
   CTD_DB_ADJ_AMT       DECIMAL(15,2),
   CTD_DB_ADJ_CNT       INTEGER,
   CTD_CR_ADJ_AMT       INTEGER,
   CTD_CR_ADJ_CNT       DECIMAL(15,2),
   CTD_FEE_AMT          DECIMAL(15,2),
   CTD_FEE_CNT          INTEGER,
   CTD_INTEREST_AMT     DECIMAL(15,2),
   CTD_INTEREST_CNT     INTEGER,
   CTD_REFUND_AMT       DECIMAL(15,2),
   CTD_REFUND_CNT       INTEGER,
   CTD_HI_OVRLMT_AMT    DECIMAL(15,2),
   MTD_RETAIL_AMT       DECIMAL(15,2),
   MTD_RETAIL_CNT       INTEGER,
   MTD_CASH_AMT         DECIMAL(15,2),
   MTD_CASH_CNT         INTEGER,
   MTD_REFUND_AMT       DECIMAL(15,2),
   MTD_REFUND_CNT       INTEGER,
   YTD_RETAIL_AMT       DECIMAL(15,2),
   YTD_RETAIL_CNT       INTEGER,
   YTD_CASH_AMT         DECIMAL(15,2),
   YTD_CASH_CNT         INTEGER,
   YTD_REFUND_AMT       DECIMAL(15,2),
   YTD_REFUND_CNT       INTEGER,
   YTD_OVRLMT_FEE_AMT   DECIMAL(15,2),
   YTD_OVRLMT_FEE_CNT   INTEGER,
   YTD_LPC_AMT          DECIMAL(15,2),
   YTD_LPC_CNT          INTEGER,
   LTD_RETAIL_AMT       DECIMAL(15,2),
   LTD_RETAIL_CNT       INTEGER,
   LTD_CASH_AMT         DECIMAL(15,2),
   LTD_CASH_CNT         INTEGER,
   LTD_REFUND_AMT       DECIMAL(15,2),
   LTD_REFUND_CNT       INTEGER,
   LTD_HIGHEST_PRINCIPAL DECIMAL(15,2),
   LTD_HIGHEST_CR_BAL   DECIMAL(15,2),
   LTD_HIGHEST_BAL      DECIMAL(15,2),
   COLLECT_TIMES        DECIMAL(15,2),
   COLLECT_COLR         VARCHAR(8),
   COLLECT_REASON       CHARACTER(2),
   AGE_HIST             VARCHAR(24),
   PAYMENT_HIST         VARCHAR(24),
   WAIVE_OVLFEE_IND     CHARACTER,
   WAIVE_CARDFEE_IND    CHARACTER,
   WAIVE_LATEFEE_IND    CHARACTER,
   WAIVE_SVCFEE_IND     CHARACTER,
   USER_CODE1           VARCHAR(4),
   USER_CODE2           VARCHAR(4),
   USER_CODE3           VARCHAR(4),
   USER_CODE4           VARCHAR(4),
   USER_CODE5           VARCHAR(4),
   USER_CODE6           VARCHAR(4),
   USER_DATE1           VARCHAR(14),
   USER_DATE2           VARCHAR(14),
   USER_DATE3           VARCHAR(14),
   USER_DATE4           VARCHAR(14),
   USER_DATE5           VARCHAR(14),
   USER_DATE6           VARCHAR(14),
   USER_NUMBER1         INTEGER,
   USER_NUMBER2         INTEGER,
   USER_NUMBER3         INTEGER,
   USER_NUMBER4         INTEGER,
   USER_NUMBER5         INTEGER,
   USER_NUMBER6         INTEGER,
   USER_FIELD1          VARCHAR(40),
   USER_FIELD2          VARCHAR(40),
   USER_FIELD3          VARCHAR(40),
   USER_FIELD4          VARCHAR(40),
   USER_FIELD5          VARCHAR(40),
   USER_FIELD6          VARCHAR(40),
   USER_AMT1            DECIMAL(15,2),
   USER_AMT2            DECIMAL(15,2),
   USER_AMT3            DECIMAL(15,2),
   USER_AMT4            DECIMAL(15,2),
   USER_AMT5            DECIMAL(15,2),
   USER_AMT6            DECIMAL(15,2),
   JPA_VERSION          INTEGER,
   MTD_PAYMENT_AMT      DECIMAL(15,2),
   MTD_PAYMENT_CNT      INTEGER,
   YTD_PAYMENT_AMT      DECIMAL(15,2),
   YTD_PAYMENT_CNT      INTEGER,
   LTD_PAYMENT_AMT      DECIMAL(15,2),
   LTD_PAYMENT_CNT      INTEGER,
   SMS_IND              CHARACTER,
   USER_SMS_AMT         DECIMAL(15,2),
   YTD_CYCLE_CHAG_CNT   INTEGER,
   LAST_POST_DATE       VARCHAR(8),
   LAST_MODIFIED_DATETIME VARCHAR(14),
   LOCK_DATE            VARCHAR(8),
   LAST_SYNC_DATE       VARCHAR(8),
   CREATED_DATETIME     VARCHAR(14),
   DELAY_BAL            DECIMAL(15,2),
   BANK_GROUP_ID        VARCHAR(5),
   CUSTOMER_TYPE        VARCHAR(3),
   IS_CHECK_FLAG        CHARACTER,
   EXTEND_PARAM1        VARCHAR(100),
   EXTEND_PARAM2        VARCHAR(250),
   EXTEND_PARAM3        VARCHAR(40),
   constraint PK_ICPS_WBC_TM_ACCOUNT primary key (BUSI_DATE, FILE_ORDER)
)  IN GAPS_DATA INDEX IN GAPS_INDEX ;

comment on table GAPSUSR.ICPS_WBC_TM_ACCOUNT is
'�˻���Ϣ��-��������';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.BUSI_DATE is
'ҵ������';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.FILE_ORDER is
'�ļ����';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.ORG is
'������';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.ACCT_NO is
'�˻����';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.ACCT_TYPE is
'�˻�����';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.CUST_ID is
'�ͻ����';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.CUST_LIMIT_ID is
'�ͻ����ID';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.PRODUCT_CD is
'��Ʒ����';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.DEFAULT_LOGICAL_CARD_NO is
'Ĭ���߼�����';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.CURR_CD is
'����';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.CREDIT_LIMIT is
'���ö��';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.TEMP_LIMIT is
'��ʱ���';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.TEMP_LIMIT_BEGIN_DATE is
'��ʱ��ȿ�ʼ����';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.TEMP_LIMIT_END_DATE is
'��ʱ��Ƚ�������';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.CASH_LIMIT_RT is
'ȡ�ֶ�ȱ���';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.OVRLMT_RATE is
'��Ȩ���ޱ���';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.LOAN_LIMIT_RT is
'����ڷ��ڶ�ȱ���';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.CURR_BAL is
'��ǰ���';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.CASH_BAL is
'ȡ�����';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.PRINCIPAL_BAL is
'�������';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.LOAN_BAL is
'����ڷ������';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.DISPUTE_AMT is
'������';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.BEGIN_BAL is
'�ڳ����';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.PMT_DUE_DAY_BAL is
'���ڻ��������';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.QUAL_GRACE_BAL is
'ȫ��Ӧ�����';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.GRACE_DAYS_FULL_IND is
'�Ƿ���ȫ���';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.POINT_BEGIN_BAL is
'�ڳ��������';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.CTD_EARNED_POINTS is
'������������';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.CTD_DISB_POINTS is
'���ڶһ�����';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.CTD_ADJ_POINTS is
'���ڵ�������';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.POINT_BAL is
'�������';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.SETUP_DATE is
'��������';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.DORMENT_DATE is
'�˻�˯������';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.REINSTATE_DATE is
'�˻��ָ������';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.OVRLMT_DATE is
'��������';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.OVRLMT_NBR_OF_CYC is
'������������';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT."NAME" is
'����';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.GENDER is
'�Ա�';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.OWNING_BRANCH is
'��������';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.MOBILE_NO is
'�ƶ��绰';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.CORP_NAME is
'��˾����';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.BILLING_CYCLE is
'�˵�����';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.STMT_FLAG is
'�˵���־';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.STMT_MAIL_ADDR_IND is
'�˵����͵�ַ��־';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.STMT_MEDIA_TYPE is
'�˵���������';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.STMT_COUNTRY_CD is
'�˵���ַ���Ҵ���';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.STMT_STATE is
'�˵���ַʡ��';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.STMT_CITY is
'�˵���ַ����';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.STMT_DISTRICT is
'�˵���ַ������';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.STMT_ADDRESS is
'�˵���ַ';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.STMT_ZIP is
'�˵���ַ��������';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.EMAIL is
'��������';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.BLOCK_CODE is
'������';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.AGE_CD is
'����';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.GL_AGE_CD is
'��������';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.UNMATCH_DB is
'δƥ���ǽ��';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.UNMATCH_CASH is
'δƥ��ȡ�ֽ��';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.UNMATCH_CR is
'δƥ����ǽ��';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.DD_IND is
'Լ����������';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.DD_BANK_NAME is
'Լ��������������';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.DD_BANK_BRANCH is
'Լ��������к�';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.DD_BANK_ACCT_NO is
'Լ������ۿ��˺�';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.DD_BANK_ACCT_NAME is
'Լ������ۿ��˻�����';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.LAST_DD_AMT is
'����Լ��������';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.LAST_DD_DATE is
'����Լ����������';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.DUAL_BILLING_FLAG is
'������ɿ���ָʾ';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.LAST_PMT_AMT is
'�ϱʻ�����';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.LAST_PMT_DATE is
'�ϸ���������';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.LAST_STMT_DATE is
'�ϸ��˵�����';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.LAST_PMT_DUE_DATE is
'�ϸ����ڻ�������';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.LAST_AGING_DATE is
'�ϸ�������������';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.COLLECT_DATE is
'�������';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.COLLECT_OUT_DATE is
'�����ն�������';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.NEXT_STMT_DATE is
'�¸��˵�����';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.PMT_DUE_DATE is
'���ڻ�������';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.DD_DATE is
'Լ����������';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.GRACE_DATE is
'��������';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.DLBL_DATE is
'���һ��������';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.CLOSED_DATE is
'������������';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.FIRST_STMT_DATE is
'�׸��˵�����';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.CANCEL_DATE is
'������������';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.CHARGE_OFF_DATE is
'ת��������';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.FIRST_PURCHASE_DATE is
'�״���������';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.FIRST_PURCHASE_AMT is
'�״����ѽ��';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.TOT_DUE_AMT is
'��С�����';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.CURR_DUE_AMT is
'������С�����';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.PAST_DUE_AMT1 is
'�ϸ�����С�����';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.PAST_DUE_AMT2 is
'��2������С�����';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.PAST_DUE_AMT3 is
'��3������С�����';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.PAST_DUE_AMT4 is
'��4������С�����';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.PAST_DUE_AMT5 is
'��5������С�����';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.PAST_DUE_AMT6 is
'��6������С�����';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.PAST_DUE_AMT7 is
'��7������С�����';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.PAST_DUE_AMT8 is
'��8������С�����';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.CTD_CASH_AMT is
'����ȡ�ֽ��';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.CTD_CASH_CNT is
'����ȡ�ֱ���';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.CTD_RETAIL_AMT is
'�������ѽ��';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.CTD_RETAIL_CNT is
'�������ѱ���';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.CTD_PAYMENT_AMT is
'���ڻ�����';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.CTD_PAYMENT_CNT is
'���ڻ������';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.CTD_DB_ADJ_AMT is
'���ڽ�ǵ������';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.CTD_DB_ADJ_CNT is
'���ڽ�ǵ�������';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.CTD_CR_ADJ_AMT is
'���ڴ��ǵ������';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.CTD_CR_ADJ_CNT is
'���ڴ��ǵ�������';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.CTD_FEE_AMT is
'���ڷ��ý��';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.CTD_FEE_CNT is
'���ڷ��ñ���';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.CTD_INTEREST_AMT is
'������Ϣ���';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.CTD_INTEREST_CNT is
'������Ϣ����';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.CTD_REFUND_AMT is
'�����˻����';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.CTD_REFUND_CNT is
'�����˻�����';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.CTD_HI_OVRLMT_AMT is
'������߳��޽��';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.MTD_RETAIL_AMT is
'�������ѽ��';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.MTD_RETAIL_CNT is
'�������ѱ���';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.MTD_CASH_AMT is
'����ȡ�ֽ��';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.MTD_CASH_CNT is
'����ȡ�ֱ���';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.MTD_REFUND_AMT is
'�����˻����';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.MTD_REFUND_CNT is
'�����˻�����';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.YTD_RETAIL_AMT is
'�������ѽ��';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.YTD_RETAIL_CNT is
'�������ѱ���';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.YTD_CASH_AMT is
'����ȡ�ֽ��';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.YTD_CASH_CNT is
'����ȡ�ֱ���';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.YTD_REFUND_AMT is
'�����˻����';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.YTD_REFUND_CNT is
'�����˻�����';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.YTD_OVRLMT_FEE_AMT is
'���곬�޷���ȡ���';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.YTD_OVRLMT_FEE_CNT is
'���곬�޷���ȡ����';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.YTD_LPC_AMT is
'�������ɽ���ȡ���';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.YTD_LPC_CNT is
'�������ɽ���ȡ����';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.LTD_RETAIL_AMT is
'��ʷ���ѽ��';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.LTD_RETAIL_CNT is
'��ʷ���ѱ���';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.LTD_CASH_AMT is
'��ʷȡ�ֽ��';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.LTD_CASH_CNT is
'��ʷȡ�ֱ���';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.LTD_REFUND_AMT is
'��ʷ�˻����';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.LTD_REFUND_CNT is
'��ʷ�˻�����';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.LTD_HIGHEST_PRINCIPAL is
'��ʷ��߱���Ƿ��';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.LTD_HIGHEST_CR_BAL is
'��ʷ�����ɿ�';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.LTD_HIGHEST_BAL is
'��ʷ������';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.COLLECT_TIMES is
'��ߴ���';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.COLLECT_COLR is
'����Ա����';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.COLLECT_REASON is
'���ԭ��';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.AGE_HIST is
'������ʷ��Ϣ';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.PAYMENT_HIST is
'������ʷ��Ϣ';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.WAIVE_OVLFEE_IND is
'�Ƿ�������޷�';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.WAIVE_CARDFEE_IND is
'�Ƿ�������';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.WAIVE_LATEFEE_IND is
'�Ƿ�������ɽ�';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.WAIVE_SVCFEE_IND is
'�Ƿ���������';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.USER_CODE1 is
'�û��Զ������1';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.USER_CODE2 is
'�û��Զ������2';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.USER_CODE3 is
'�û��Զ������3';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.USER_CODE4 is
'�û��Զ������4';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.USER_CODE5 is
'�û��Զ������5';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.USER_CODE6 is
'�û��Զ������6';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.USER_DATE1 is
'�û��Զ�������1';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.USER_DATE2 is
'�ϴε�������';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.USER_DATE3 is
'�û��Զ�������3';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.USER_DATE4 is
'�û��Զ�������4';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.USER_DATE5 is
'�û��Զ�������5';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.USER_DATE6 is
'�û��Զ�������6';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.USER_NUMBER1 is
'�û��Զ������1';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.USER_NUMBER2 is
'�û��Զ������2';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.USER_NUMBER3 is
'�û��Զ������3';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.USER_NUMBER4 is
'�û��Զ������4';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.USER_NUMBER5 is
'�û��Զ������5';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.USER_NUMBER6 is
'�û��Զ������6';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.USER_FIELD1 is
'�û��Զ�����1';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.USER_FIELD2 is
'�û��Զ�����2';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.USER_FIELD3 is
'�û��Զ�����3';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.USER_FIELD4 is
'�û��Զ�����4';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.USER_FIELD5 is
'�û��Զ�����5';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.USER_FIELD6 is
'�û��Զ�����6';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.USER_AMT1 is
'�û��Զ�����1';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.USER_AMT2 is
'�û��Զ�����2';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.USER_AMT3 is
'�û��Զ�����3';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.USER_AMT4 is
'�û��Զ�����4';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.USER_AMT5 is
'�û��Զ�����5';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.USER_AMT6 is
'���մ��ǿ���ŵ���';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.JPA_VERSION is
'�ֹ����汾��';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.MTD_PAYMENT_AMT is
'���»�����';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.MTD_PAYMENT_CNT is
'���»������';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.YTD_PAYMENT_AMT is
'���껹����';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.YTD_PAYMENT_CNT is
'���껹�����';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.LTD_PAYMENT_AMT is
'��ʷ������';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.LTD_PAYMENT_CNT is
'��ʷ�������';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.SMS_IND is
'���ŷ��ͱ�ʶ';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.USER_SMS_AMT is
'���Ի����˶��ŷ�����ֵ';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.YTD_CYCLE_CHAG_CNT is
'������˵����޸Ĵ���';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.LAST_POST_DATE is
'�ϸ���������';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.LAST_MODIFIED_DATETIME is
'�޸�ʱ��';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.LOCK_DATE is
'�Զ�������';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.LAST_SYNC_DATE is
'��һ�����˵���������';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.CREATED_DATETIME is
'����ʱ��';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.DELAY_BAL is
'�˻����ڽ��';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.BANK_GROUP_ID is
'���ű��';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.CUSTOMER_TYPE is
'��Ⱥ����';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.IS_CHECK_FLAG is
'������˱�ʶ';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.EXTEND_PARAM1 is
'��չ1';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.EXTEND_PARAM2 is
'��չ2';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.EXTEND_PARAM3 is
'��չ3';

--==============================================================
-- Table: ICPS_WBC_TM_ACCOUNTING_FLOW
--==============================================================
create table GAPSUSR.ICPS_WBC_TM_ACCOUNTING_FLOW
(
   BUSI_DATE            CHARACTER(8)           not null,
   FILE_ORDER           INTEGER                not null,
   ORG                  CHARACTER(12),
   CPS_TXN_SEQ          VARCHAR(36),
   CARD_NO              VARCHAR(19),
   CURR_CD              CHARACTER(3),
   TXN_CODE             CHARACTER(4),
   TXN_DESC             VARCHAR(80),
   DB_CR_IND            CHARACTER,
   POST_AMT             DECIMAL(15,2),
   POST_GL_IND          CHARACTER,
   OWNING_BRANCH        VARCHAR(9),
   SUBJECT              VARCHAR(40),
   RED_FLAG             CHARACTER,
   QUEUE                VARCHAR(20),
   PRODUCT_CD           VARCHAR(6),
   REF_NBR              VARCHAR(23),
   AGE_GROUP            VARCHAR(1),
   PLAN_NBR             VARCHAR(6),
   BNP_GROUP            VARCHAR(2),
   BANK_GROUP_ID        VARCHAR(5),
   BANK_NO              VARCHAR(10),
   TERM                 INTEGER,
   BATCHDATE            VARCHAR(14),
   IS_CHECK_FLAG        CHARACTER,
   EXTEND_PARAM1        VARCHAR(100),
   EXTEND_PARAM2        VARCHAR(250),
   EXTEND_PARAM3        VARCHAR(40),
   constraint PK_ICPS_WBC_TM_ACCOUNTING_FLOW primary key (BUSI_DATE, FILE_ORDER)
)  IN GAPS_DATA INDEX IN GAPS_INDEX ;

comment on table GAPSUSR.ICPS_WBC_TM_ACCOUNTING_FLOW is
'��Ʒ�¼�ձ���';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNTING_FLOW.BUSI_DATE is
'ҵ������';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNTING_FLOW.FILE_ORDER is
'�ļ����';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNTING_FLOW.ORG is
'�ڲ�������';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNTING_FLOW.CPS_TXN_SEQ is
'���Ľ�����ˮ';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNTING_FLOW.CARD_NO is
'����';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNTING_FLOW.CURR_CD is
'����';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNTING_FLOW.TXN_CODE is
'������';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNTING_FLOW.TXN_DESC is
'��������';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNTING_FLOW.DB_CR_IND is
'������';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNTING_FLOW.POST_AMT is
'���˽��';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNTING_FLOW.POST_GL_IND is
'���˷�ʽ';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNTING_FLOW.OWNING_BRANCH is
'֧��';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNTING_FLOW.SUBJECT is
'��Ŀ';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNTING_FLOW.RED_FLAG is
'�����ֱ�ʶ';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNTING_FLOW.QUEUE is
'����';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNTING_FLOW.PRODUCT_CD is
'��Ʒ��';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNTING_FLOW.REF_NBR is
'��ݺ�';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNTING_FLOW.AGE_GROUP is
'������';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNTING_FLOW.PLAN_NBR is
'���üƻ���';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNTING_FLOW.BNP_GROUP is
'���ɷ���';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNTING_FLOW.BANK_GROUP_ID is
'���Ŵ���';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNTING_FLOW.BANK_NO is
'���д���';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNTING_FLOW.TERM is
'����';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNTING_FLOW.BATCHDATE is
'����';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNTING_FLOW.IS_CHECK_FLAG is
'������˱�ʶ';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNTING_FLOW.EXTEND_PARAM1 is
'��չ1';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNTING_FLOW.EXTEND_PARAM2 is
'��չ2';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNTING_FLOW.EXTEND_PARAM3 is
'��չ3';

--==============================================================
-- Table: ICPS_WBC_TM_AGREEMENT
--==============================================================
create table GAPSUSR.ICPS_WBC_TM_AGREEMENT
(
   BUSI_DATE            CHARACTER(8)           not null,
   FILE_ORDER           INTEGER                not null,
   AGREEMENT_NO         VARCHAR(50),
   MERCHANT_ID          VARCHAR(20),
   PRODUCT_CD           CHARACTER(6),
   PRODUCT_STCODE       VARCHAR(8),
   NBS_CUST_ID          VARCHAR(20),
   USER_ID              VARCHAR(32),
   CNC_CARD_NO          VARCHAR(20),
   DEBIT_CARD_NO        VARCHAR(19),
   WB_DEBIT_CARD_NO     VARCHAR(19),
   LAST_TXN_STATUS      CHARACTER(4),
   TXN_STATUS           CHARACTER(4),
   LAST_NATIVE_STAUS    CHARACTER,
   NATIVE_STAUS         CHARACTER,
   BILLING_CYCLE        CHARACTER(2),
   FIRST_STMT_DATE      VARCHAR(8),
   AGREEMENT_AMT        DECIMAL(15,2),
   PCT_ID               VARCHAR(32),
   FEE_RATE             DECIMAL(12,6),
   INTEREST_RATE        DECIMAL(12,6),
   PENALTY_RATE         DECIMAL(12,6),
   LIQUIDATED_DAMAGES   DECIMAL(15,2),
   CURR_TERM            INTEGER,
   CURR_DEDUCT_STAGE    CHARACTER,
   DEDUCT_STAGE_HST     VARCHAR(50),
   CREDIT_INTEREST_RATE DECIMAL(12,6),
   CREDIT_PENALTY_RATE  DECIMAL(12,6),
   CREDIT_CURR_DEDUCT_STAGE CHARACTER,
   CREDIT_DEDUCT_STAGE_HST VARCHAR(5),
   MASTER_CARD_FLAG     VARCHAR(20),
   RESERVE1             VARCHAR(20),
   RESERVE2             VARCHAR(50),
   RESERVE3             VARCHAR(50),
   BIZ_DATE             VARCHAR(8),
   CREATED_DATETIME     VARCHAR(14),
   LAST_MODIFIED_DATETIME VARCHAR(14),
   LOAN_INIT_TERM       INTEGER,
   ORDER_TYPE           VARCHAR(2),
   FUND_STATUS          VARCHAR(20),
   FEE_CURR_DEDUCT_STAGE CHARACTER,
   PROFIT_RATIO         DECIMAL(15,8),
   PRODUCT_CATEGORY     VARCHAR(6),
   FEE_DEDUCT_STAGE_HST VARCHAR(50),
   RESERVE4             VARCHAR(50),
   RESERVE5             VARCHAR(50),
   RESERVE6             VARCHAR(50),
   RESERVE7             VARCHAR(50),
   RESERVE8             VARCHAR(50),
   RESERVE9             VARCHAR(50),
   RESERVE10            VARCHAR(50),
   IS_CHECK_FLAG        CHARACTER,
   EXTEND_PARAM1        VARCHAR(100),
   EXTEND_PARAM2        VARCHAR(250),
   EXTEND_PARAM3        VARCHAR(40),
   constraint PK_ICPS_WBC_TM_AGREEMENT primary key (BUSI_DATE, FILE_ORDER)
)  IN GAPS_DATA INDEX IN GAPS_INDEX ;

comment on table GAPSUSR.ICPS_WBC_TM_AGREEMENT is
'Э���';

comment on column GAPSUSR.ICPS_WBC_TM_AGREEMENT.BUSI_DATE is
'ҵ������';

comment on column GAPSUSR.ICPS_WBC_TM_AGREEMENT.FILE_ORDER is
'�ļ����';

comment on column GAPSUSR.ICPS_WBC_TM_AGREEMENT.AGREEMENT_NO is
'ƽ̨������';

comment on column GAPSUSR.ICPS_WBC_TM_AGREEMENT.MERCHANT_ID is
'ƽ̨ID';

comment on column GAPSUSR.ICPS_WBC_TM_AGREEMENT.PRODUCT_CD is
'��ƷCD';

comment on column GAPSUSR.ICPS_WBC_TM_AGREEMENT.PRODUCT_STCODE is
'��Ʒ�ṹ����';

comment on column GAPSUSR.ICPS_WBC_TM_AGREEMENT.NBS_CUST_ID is
'NBS�ͻ�ID';

comment on column GAPSUSR.ICPS_WBC_TM_AGREEMENT.USER_ID is
'ƽ̨�Ŀͻ�ID';

comment on column GAPSUSR.ICPS_WBC_TM_AGREEMENT.CNC_CARD_NO is
'�����';

comment on column GAPSUSR.ICPS_WBC_TM_AGREEMENT.DEBIT_CARD_NO is
'���н�ǿ���';

comment on column GAPSUSR.ICPS_WBC_TM_AGREEMENT.WB_DEBIT_CARD_NO is
'���н�ǿ���';

comment on column GAPSUSR.ICPS_WBC_TM_AGREEMENT.LAST_TXN_STATUS is
'��һ��ҵ��״̬';

comment on column GAPSUSR.ICPS_WBC_TM_AGREEMENT.TXN_STATUS is
'��ǰҵ��״̬';

comment on column GAPSUSR.ICPS_WBC_TM_AGREEMENT.LAST_NATIVE_STAUS is
'��һ����״̬';

comment on column GAPSUSR.ICPS_WBC_TM_AGREEMENT.NATIVE_STAUS is
'��ǰ����״̬';

comment on column GAPSUSR.ICPS_WBC_TM_AGREEMENT.BILLING_CYCLE is
'�˵�����';

comment on column GAPSUSR.ICPS_WBC_TM_AGREEMENT.FIRST_STMT_DATE is
'�׸��˵���';

comment on column GAPSUSR.ICPS_WBC_TM_AGREEMENT.AGREEMENT_AMT is
'Э����';

comment on column GAPSUSR.ICPS_WBC_TM_AGREEMENT.PCT_ID is
'���ۿ��Ʊ��';

comment on column GAPSUSR.ICPS_WBC_TM_AGREEMENT.FEE_RATE is
'��������';

comment on column GAPSUSR.ICPS_WBC_TM_AGREEMENT.INTEREST_RATE is
'��Ϣ����';

comment on column GAPSUSR.ICPS_WBC_TM_AGREEMENT.PENALTY_RATE is
'��Ϣ����';

comment on column GAPSUSR.ICPS_WBC_TM_AGREEMENT.LIQUIDATED_DAMAGES is
'ΥԼ��';

comment on column GAPSUSR.ICPS_WBC_TM_AGREEMENT.CURR_TERM is
'��������';

comment on column GAPSUSR.ICPS_WBC_TM_AGREEMENT.CURR_DEDUCT_STAGE is
'��ǰ�ۿ�׶�';

comment on column GAPSUSR.ICPS_WBC_TM_AGREEMENT.DEDUCT_STAGE_HST is
'�ۿ�׶���ʷ��¼';

comment on column GAPSUSR.ICPS_WBC_TM_AGREEMENT.CREDIT_INTEREST_RATE is
'���ô�����';

comment on column GAPSUSR.ICPS_WBC_TM_AGREEMENT.CREDIT_PENALTY_RATE is
'���ô���Ϣ����';

comment on column GAPSUSR.ICPS_WBC_TM_AGREEMENT.CREDIT_CURR_DEDUCT_STAGE is
'���ô���ǰ�ۿ�׶�';

comment on column GAPSUSR.ICPS_WBC_TM_AGREEMENT.CREDIT_DEDUCT_STAGE_HST is
'���ô��ۿ�׶���ʷ��¼';

comment on column GAPSUSR.ICPS_WBC_TM_AGREEMENT.MASTER_CARD_FLAG is
'�������ʶ';

comment on column GAPSUSR.ICPS_WBC_TM_AGREEMENT.RESERVE1 is
'�����ֶ�1';

comment on column GAPSUSR.ICPS_WBC_TM_AGREEMENT.RESERVE2 is
'�����ֶ�2';

comment on column GAPSUSR.ICPS_WBC_TM_AGREEMENT.RESERVE3 is
'�����ֶ�3';

comment on column GAPSUSR.ICPS_WBC_TM_AGREEMENT.BIZ_DATE is
'ҵ������';

comment on column GAPSUSR.ICPS_WBC_TM_AGREEMENT.CREATED_DATETIME is
'����ʱ������';

comment on column GAPSUSR.ICPS_WBC_TM_AGREEMENT.LAST_MODIFIED_DATETIME is
'����ʱ������';

comment on column GAPSUSR.ICPS_WBC_TM_AGREEMENT.LOAN_INIT_TERM is
'������';

comment on column GAPSUSR.ICPS_WBC_TM_AGREEMENT.ORDER_TYPE is
'��������';

comment on column GAPSUSR.ICPS_WBC_TM_AGREEMENT.FUND_STATUS is
'�ʽ�ռѹ״̬';

comment on column GAPSUSR.ICPS_WBC_TM_AGREEMENT.FEE_CURR_DEDUCT_STAGE is
'���ô���ǰ�ۿ�׶�';

comment on column GAPSUSR.ICPS_WBC_TM_AGREEMENT.PROFIT_RATIO is
'�������';

comment on column GAPSUSR.ICPS_WBC_TM_AGREEMENT.PRODUCT_CATEGORY is
'��Ʒ����';

comment on column GAPSUSR.ICPS_WBC_TM_AGREEMENT.FEE_DEDUCT_STAGE_HST is
'���ô��ۿ�׶���ʷ��¼';

comment on column GAPSUSR.ICPS_WBC_TM_AGREEMENT.RESERVE4 is
'�����ֶ�4';

comment on column GAPSUSR.ICPS_WBC_TM_AGREEMENT.RESERVE5 is
'�����ֶ�5';

comment on column GAPSUSR.ICPS_WBC_TM_AGREEMENT.RESERVE6 is
'�����ֶ�6';

comment on column GAPSUSR.ICPS_WBC_TM_AGREEMENT.RESERVE7 is
'�����ֶ�7';

comment on column GAPSUSR.ICPS_WBC_TM_AGREEMENT.RESERVE8 is
'�����ֶ�8';

comment on column GAPSUSR.ICPS_WBC_TM_AGREEMENT.RESERVE9 is
'�����ֶ�9';

comment on column GAPSUSR.ICPS_WBC_TM_AGREEMENT.RESERVE10 is
'�����ֶ�10';

comment on column GAPSUSR.ICPS_WBC_TM_AGREEMENT.IS_CHECK_FLAG is
'������˱�ʶ';

comment on column GAPSUSR.ICPS_WBC_TM_AGREEMENT.EXTEND_PARAM1 is
'��չ1';

comment on column GAPSUSR.ICPS_WBC_TM_AGREEMENT.EXTEND_PARAM2 is
'��չ2';

comment on column GAPSUSR.ICPS_WBC_TM_AGREEMENT.EXTEND_PARAM3 is
'��չ3';

--==============================================================
-- Table: ICPS_WBC_TM_AGREEMENT_CAR
--==============================================================
create table GAPSUSR.ICPS_WBC_TM_AGREEMENT_CAR
(
   BUSI_DATE            CHARACTER(8)           not null,
   FILE_ORDER           INTEGER                not null,
   AGREEMENT_NO         VARCHAR(50),
   MERCHANT_ID          VARCHAR(20),
   PRODUCT_CD           VARCHAR(50),
   MER_ORDER_NO         VARCHAR(50),
   IS_NEW_CAR           CHARACTER,
   CAR_ID               VARCHAR(21),
   CAR_PRICE            DECIMAL(13,2),
   CAR_INQUIRY_PRICE    DECIMAL(13,2),
   ASSESS_AMOUNT        DECIMAL(13,2),
   ASSESS_TIME          VARCHAR(8),
   ASSESS_CLASS         VARCHAR(5),
   REGISTRATE_TIME      VARCHAR(14),
   VEHICLE_ID           VARCHAR(32),
   ENGINE_NO            VARCHAR(32),
   MILEAGE              VARCHAR(20),
   XFR_TIMES            VARCHAR(20),
   COTY                 VARCHAR(20),
   MOTORCYCLE_TYPE      VARCHAR(30),
   INS_EXPIRE_DATE      VARCHAR(14),
   DEALER_ID            VARCHAR(32),
   DEALER_NAME          VARCHAR(32),
   IS_STAGE_GUARANTEE_DEALER CHARACTER,
   CAR_NAME             VARCHAR(20),
   IS_SECOND_HAND_CAR   CHARACTER,
   CAR_ACTUAL_PRICE     DECIMAL(13,2),
   DOWN_PAYMENT         DECIMAL(13,2),
   CAR_CONTEXT          VARCHAR(3000),
   DRIVER_LICENSE       VARCHAR(30),
   HOME_PHONE           VARCHAR(20),
   OCCUPATION           VARCHAR(60),
   SS_AVE_AMT_MTLY      DECIMAL(13,2),
   SALARY_AVE_MTLY      DECIMAL(13,2),
   IS_HOME_VISITED      CHARACTER,
   HOUSE_INFO           VARCHAR(80),
   MER_APPLY_RESULT     CHARACTER,
   MER_APPLY_VIEW       VARCHAR(80),
   MER_REFUSE_REASON    VARCHAR(10),
   BIZ_DATE             VARCHAR(8),
   CREATED_DATETIME     VARCHAR(14),
   LAST_MODIFIED_DATETIME VARCHAR(14),
   IS_CHECK_FLAG        CHARACTER,
   EXTEND_PARAM1        VARCHAR(100),
   EXTEND_PARAM2        VARCHAR(250),
   EXTEND_PARAM3        VARCHAR(40),
   constraint PK_ICPS_WBC_TM_AGREEMENT_CAR primary key (BUSI_DATE, FILE_ORDER)
)  IN GAPS_DATA INDEX IN GAPS_INDEX ;

comment on table GAPSUSR.ICPS_WBC_TM_AGREEMENT_CAR is
'Э�鸽�ӱ�(��)';

comment on column GAPSUSR.ICPS_WBC_TM_AGREEMENT_CAR.BUSI_DATE is
'ҵ������';

comment on column GAPSUSR.ICPS_WBC_TM_AGREEMENT_CAR.FILE_ORDER is
'�ļ����';

comment on column GAPSUSR.ICPS_WBC_TM_AGREEMENT_CAR.AGREEMENT_NO is
'ƽ̨������';

comment on column GAPSUSR.ICPS_WBC_TM_AGREEMENT_CAR.MERCHANT_ID is
'ƽ̨ID��';

comment on column GAPSUSR.ICPS_WBC_TM_AGREEMENT_CAR.PRODUCT_CD is
'��Ʒ��';

comment on column GAPSUSR.ICPS_WBC_TM_AGREEMENT_CAR.MER_ORDER_NO is
'ƽ̨Э���';

comment on column GAPSUSR.ICPS_WBC_TM_AGREEMENT_CAR.IS_NEW_CAR is
'�Ƿ��³�';

comment on column GAPSUSR.ICPS_WBC_TM_AGREEMENT_CAR.CAR_ID is
'����ID';

comment on column GAPSUSR.ICPS_WBC_TM_AGREEMENT_CAR.CAR_PRICE is
'�������ۼ�';

comment on column GAPSUSR.ICPS_WBC_TM_AGREEMENT_CAR.CAR_INQUIRY_PRICE is
'�ⲿ����Դ��ѯ��';

comment on column GAPSUSR.ICPS_WBC_TM_AGREEMENT_CAR.ASSESS_AMOUNT is
'������ֵ';

comment on column GAPSUSR.ICPS_WBC_TM_AGREEMENT_CAR.ASSESS_TIME is
'��������ʱ��';

comment on column GAPSUSR.ICPS_WBC_TM_AGREEMENT_CAR.ASSESS_CLASS is
'������⼶��';

comment on column GAPSUSR.ICPS_WBC_TM_AGREEMENT_CAR.REGISTRATE_TIME is
'��������';

comment on column GAPSUSR.ICPS_WBC_TM_AGREEMENT_CAR.VEHICLE_ID is
'�������ܺ�';

comment on column GAPSUSR.ICPS_WBC_TM_AGREEMENT_CAR.ENGINE_NO is
'��������';

comment on column GAPSUSR.ICPS_WBC_TM_AGREEMENT_CAR.MILEAGE is
'��ʻ���';

comment on column GAPSUSR.ICPS_WBC_TM_AGREEMENT_CAR.XFR_TIMES is
'��������';

comment on column GAPSUSR.ICPS_WBC_TM_AGREEMENT_CAR.COTY is
'����';

comment on column GAPSUSR.ICPS_WBC_TM_AGREEMENT_CAR.MOTORCYCLE_TYPE is
'��������';

comment on column GAPSUSR.ICPS_WBC_TM_AGREEMENT_CAR.INS_EXPIRE_DATE is
'���յ�����';

comment on column GAPSUSR.ICPS_WBC_TM_AGREEMENT_CAR.DEALER_ID is
'����ID';

comment on column GAPSUSR.ICPS_WBC_TM_AGREEMENT_CAR.DEALER_NAME is
'����';

comment on column GAPSUSR.ICPS_WBC_TM_AGREEMENT_CAR.IS_STAGE_GUARANTEE_DEALER is
'�Ƿ�׶��Ե�������';

comment on column GAPSUSR.ICPS_WBC_TM_AGREEMENT_CAR.CAR_NAME is
'��������';

comment on column GAPSUSR.ICPS_WBC_TM_AGREEMENT_CAR.IS_SECOND_HAND_CAR is
'�Ƿ���ֳ�';

comment on column GAPSUSR.ICPS_WBC_TM_AGREEMENT_CAR.CAR_ACTUAL_PRICE is
'����ʵ�ʳɽ���';

comment on column GAPSUSR.ICPS_WBC_TM_AGREEMENT_CAR.DOWN_PAYMENT is
'�׸��ܽ��';

comment on column GAPSUSR.ICPS_WBC_TM_AGREEMENT_CAR.CAR_CONTEXT is
'������Ϣ';

comment on column GAPSUSR.ICPS_WBC_TM_AGREEMENT_CAR.DRIVER_LICENSE is
'��ʻ֤����';

comment on column GAPSUSR.ICPS_WBC_TM_AGREEMENT_CAR.HOME_PHONE is
'��ͥ�̻�����';

comment on column GAPSUSR.ICPS_WBC_TM_AGREEMENT_CAR.OCCUPATION is
'ְҵ';

comment on column GAPSUSR.ICPS_WBC_TM_AGREEMENT_CAR.SS_AVE_AMT_MTLY is
'ÿ���籣ƽ���ɽ����';

comment on column GAPSUSR.ICPS_WBC_TM_AGREEMENT_CAR.SALARY_AVE_MTLY is
'ÿ��ƽ�����ʽ�����ˮ';

comment on column GAPSUSR.ICPS_WBC_TM_AGREEMENT_CAR.IS_HOME_VISITED is
'���޼ҷ�';

comment on column GAPSUSR.ICPS_WBC_TM_AGREEMENT_CAR.HOUSE_INFO is
'������Ϣ';

comment on column GAPSUSR.ICPS_WBC_TM_AGREEMENT_CAR.MER_APPLY_RESULT is
'�������';

comment on column GAPSUSR.ICPS_WBC_TM_AGREEMENT_CAR.MER_APPLY_VIEW is
'�������';

comment on column GAPSUSR.ICPS_WBC_TM_AGREEMENT_CAR.MER_REFUSE_REASON is
'�ܾ�ԭ�����';

comment on column GAPSUSR.ICPS_WBC_TM_AGREEMENT_CAR.BIZ_DATE is
'ҵ������';

comment on column GAPSUSR.ICPS_WBC_TM_AGREEMENT_CAR.CREATED_DATETIME is
'����ʱ��';

comment on column GAPSUSR.ICPS_WBC_TM_AGREEMENT_CAR.LAST_MODIFIED_DATETIME is
'����ʱ��';

comment on column GAPSUSR.ICPS_WBC_TM_AGREEMENT_CAR.IS_CHECK_FLAG is
'������˱�ʶ';

comment on column GAPSUSR.ICPS_WBC_TM_AGREEMENT_CAR.EXTEND_PARAM1 is
'��չ1';

comment on column GAPSUSR.ICPS_WBC_TM_AGREEMENT_CAR.EXTEND_PARAM2 is
'��չ2';

comment on column GAPSUSR.ICPS_WBC_TM_AGREEMENT_CAR.EXTEND_PARAM3 is
'��չ3';

--==============================================================
-- Table: ICPS_WBC_TM_AGREEMENT_NO_MAP
--==============================================================
create table GAPSUSR.ICPS_WBC_TM_AGREEMENT_NO_MAP
(
   BUSI_DATE            CHARACTER(8)           not null,
   FILE_ORDER           INTEGER                not null,
   AGREEMENT_NO         VARCHAR(50),
   MERCHANT_ID          VARCHAR(20),
   MER_ORDER_NO         VARCHAR(50),
   TXN_STATUS           CHARACTER(4),
   BIZ_DATA             VARCHAR(8),
   CREATED_DATETIME     VARCHAR(14),
   LAST_MODIFIED_DATETIME VARCHAR(14),
   IS_CHECK_FLAG        CHARACTER,
   EXTEND_PARAM1        VARCHAR(100),
   EXTEND_PARAM2        VARCHAR(250),
   EXTEND_PARAM3        VARCHAR(40),
   constraint PK_ICPS_WBC_TM_AGREEMENT_NO_MAP primary key (BUSI_DATE, FILE_ORDER)
)  IN GAPS_DATA INDEX IN GAPS_INDEX ;

comment on table GAPSUSR.ICPS_WBC_TM_AGREEMENT_NO_MAP is
'������ӳ���';

comment on column GAPSUSR.ICPS_WBC_TM_AGREEMENT_NO_MAP.BUSI_DATE is
'ҵ������';

comment on column GAPSUSR.ICPS_WBC_TM_AGREEMENT_NO_MAP.FILE_ORDER is
'�ļ����';

comment on column GAPSUSR.ICPS_WBC_TM_AGREEMENT_NO_MAP.AGREEMENT_NO is
'NBS������';

comment on column GAPSUSR.ICPS_WBC_TM_AGREEMENT_NO_MAP.MERCHANT_ID is
'ƽ̨ID��';

comment on column GAPSUSR.ICPS_WBC_TM_AGREEMENT_NO_MAP.MER_ORDER_NO is
'ƽ̨������';

comment on column GAPSUSR.ICPS_WBC_TM_AGREEMENT_NO_MAP.TXN_STATUS is
'ƽ̨Э��״̬';

comment on column GAPSUSR.ICPS_WBC_TM_AGREEMENT_NO_MAP.BIZ_DATA is
'ҵ������';

comment on column GAPSUSR.ICPS_WBC_TM_AGREEMENT_NO_MAP.CREATED_DATETIME is
'����ʱ��';

comment on column GAPSUSR.ICPS_WBC_TM_AGREEMENT_NO_MAP.LAST_MODIFIED_DATETIME is
'�޸�ʱ��';

comment on column GAPSUSR.ICPS_WBC_TM_AGREEMENT_NO_MAP.IS_CHECK_FLAG is
'������˱�ʶ';

comment on column GAPSUSR.ICPS_WBC_TM_AGREEMENT_NO_MAP.EXTEND_PARAM1 is
'��չ1';

comment on column GAPSUSR.ICPS_WBC_TM_AGREEMENT_NO_MAP.EXTEND_PARAM2 is
'��չ2';

comment on column GAPSUSR.ICPS_WBC_TM_AGREEMENT_NO_MAP.EXTEND_PARAM3 is
'��չ3';

--==============================================================
-- Table: ICPS_WBC_TM_APP_MAIN
--==============================================================
create table GAPSUSR.ICPS_WBC_TM_APP_MAIN
(
   BUSI_DATE            CHARACTER(8)           not null,
   FILE_ORDER           INTEGER                not null,
   ORG                  CHARACTER(12),
   APP_NO               VARCHAR(20),
   APP_TYPE             CHARACTER,
   APP_LMT              DECIMAL(13,2),
   SUG_LMT              DECIMAL(13,2),
   ACC_LMT              DECIMAL(13,2),
   PRODUCT_CD           VARCHAR(6),
   BUSINESS_LIMIT       DECIMAL(13,2),
   MICRO_LOAN_LIMIT     DECIMAL(13,2),
   VEHICLE_LOAN         DECIMAL(13,2),
   HOUSE_LOAN           DECIMAL(13,2),
   RENOVATION_LOAN      DECIMAL(13,2),
   TRAVEL_LOAN          DECIMAL(13,2),
   WEDDING_LOAN         DECIMAL(13,2),
   DURABLE_LOAN         DECIMAL(13,2),
   PRIORITY             CHARACTER,
   CLIENT_TYPE          CHARACTER(3),
   APPROVE_QUICK_FLAG   CHARACTER,
   BUSNS_NUM            VARCHAR(20),
   RTF_STATE            CHARACTER(3),
   POINT_RESULT         INTEGER,
   CUST_RATE_DISCOUNT   DECIMAL(5,4),
   PRO_NUM              VARCHAR(20),
   PRO_NAME             VARCHAR(400),
   REFUSE_CODE          VARCHAR(1000),
   ANSWER_ERR_CNT       INTEGER,
   IS_CLT               CHARACTER,
   SPREADER_NUM         VARCHAR(20),
   SPREADER_ORG         VARCHAR(20),
   SPREADER_BANK        VARCHAR(9),
   SPREADER_WAY         VARCHAR(20),
   SPREADER_TYPE        CHARACTER,
   SPREADER_NAME        VARCHAR(80),
   SPREADER_NUM_PRE     VARCHAR(20),
   SPREADER_PHONE       VARCHAR(20),
   SALES_IND            CHARACTER,
   OWNING_BRANCH        VARCHAR(9),
   APP_PROMOTION_CD     VARCHAR(15),
   APP_SOURCE           VARCHAR(20),
   BANK_CUSTOMER_ID     VARCHAR(32),
   DD_FLAG              CHARACTER,
   DEDUCT_DEAL_NO       VARCHAR(40),
   IF_REFUSE            CHARACTER,
   IF_END               CHARACTER,
   APPLY_FROM_TYPE      CHARACTER,
   APPNO_EXTERNAL       VARCHAR(20),
   APPNO_ATTACH_EXTERNAL VARCHAR(20),
   REMARK               VARCHAR(400),
   CREATE_USER          VARCHAR(40),
   UPDATE_USER          VARCHAR(40),
   BIZ_NO               VARCHAR(32),
   TRACE_NO             VARCHAR(32),
   CALLED_NO            VARCHAR(32),
   RESULT_CODE          VARCHAR(10),
   CREATED_DATETIME     VARCHAR(14),
   LAST_MODIFIED_DATETIME VARCHAR(14),
   JPA_VERSION          INTEGER,
   IS_SHARED_CREDIT_LIMIT CHARACTER,
   APPROVAL_DATETIME    VARCHAR(14),
   IS_CHECK_FLAG        CHARACTER,
   EXTEND_PARAM1        VARCHAR(100),
   EXTEND_PARAM2        VARCHAR(250),
   EXTEND_PARAM3        VARCHAR(40),
   constraint PK_ICPS_WBC_TM_APP_MAIN primary key (BUSI_DATE, FILE_ORDER)
)  IN GAPS_DATA INDEX IN GAPS_INDEX ;

comment on table GAPSUSR.ICPS_WBC_TM_APP_MAIN is
'��������';

comment on column GAPSUSR.ICPS_WBC_TM_APP_MAIN.BUSI_DATE is
'ҵ������';

comment on column GAPSUSR.ICPS_WBC_TM_APP_MAIN.FILE_ORDER is
'�ļ����';

comment on column GAPSUSR.ICPS_WBC_TM_APP_MAIN.ORG is
'������';

comment on column GAPSUSR.ICPS_WBC_TM_APP_MAIN.APP_NO is
'��������';

comment on column GAPSUSR.ICPS_WBC_TM_APP_MAIN.APP_TYPE is
'��������';

comment on column GAPSUSR.ICPS_WBC_TM_APP_MAIN.APP_LMT is
'������';

comment on column GAPSUSR.ICPS_WBC_TM_APP_MAIN.SUG_LMT is
'ϵͳ������';

comment on column GAPSUSR.ICPS_WBC_TM_APP_MAIN.ACC_LMT is
'��׼���';

comment on column GAPSUSR.ICPS_WBC_TM_APP_MAIN.PRODUCT_CD is
'����Ʒ����';

comment on column GAPSUSR.ICPS_WBC_TM_APP_MAIN.BUSINESS_LIMIT is
'���񿨶��';

comment on column GAPSUSR.ICPS_WBC_TM_APP_MAIN.MICRO_LOAN_LIMIT is
'С�������';

comment on column GAPSUSR.ICPS_WBC_TM_APP_MAIN.VEHICLE_LOAN is
'ר���ȳ���';

comment on column GAPSUSR.ICPS_WBC_TM_APP_MAIN.HOUSE_LOAN is
'ר���ȷ���';

comment on column GAPSUSR.ICPS_WBC_TM_APP_MAIN.RENOVATION_LOAN is
'ר����װ�޴�';

comment on column GAPSUSR.ICPS_WBC_TM_APP_MAIN.TRAVEL_LOAN is
'ר�������δ�';

comment on column GAPSUSR.ICPS_WBC_TM_APP_MAIN.WEDDING_LOAN is
'ר���Ȼ����';

comment on column GAPSUSR.ICPS_WBC_TM_APP_MAIN.DURABLE_LOAN is
'ר����������';

comment on column GAPSUSR.ICPS_WBC_TM_APP_MAIN.PRIORITY is
'�ͻ��ȼ�';

comment on column GAPSUSR.ICPS_WBC_TM_APP_MAIN.CLIENT_TYPE is
'�ͻ�����';

comment on column GAPSUSR.ICPS_WBC_TM_APP_MAIN.APPROVE_QUICK_FLAG is
'����������־';

comment on column GAPSUSR.ICPS_WBC_TM_APP_MAIN.BUSNS_NUM is
'��˾���';

comment on column GAPSUSR.ICPS_WBC_TM_APP_MAIN.RTF_STATE is
'����״̬';

comment on column GAPSUSR.ICPS_WBC_TM_APP_MAIN.POINT_RESULT is
'����ֵ';

comment on column GAPSUSR.ICPS_WBC_TM_APP_MAIN.CUST_RATE_DISCOUNT is
'�ͻ����ʸ�������';

comment on column GAPSUSR.ICPS_WBC_TM_APP_MAIN.PRO_NUM is
'����ʵ����';

comment on column GAPSUSR.ICPS_WBC_TM_APP_MAIN.PRO_NAME is
'���̽ڵ�����';

comment on column GAPSUSR.ICPS_WBC_TM_APP_MAIN.REFUSE_CODE is
'�ܾ�ԭ����';

comment on column GAPSUSR.ICPS_WBC_TM_APP_MAIN.ANSWER_ERR_CNT is
'����ش�������';

comment on column GAPSUSR.ICPS_WBC_TM_APP_MAIN.IS_CLT is
'�Ƿ����';

comment on column GAPSUSR.ICPS_WBC_TM_APP_MAIN.SPREADER_NUM is
'�ƹ��˱��';

comment on column GAPSUSR.ICPS_WBC_TM_APP_MAIN.SPREADER_ORG is
'�ƹ����';

comment on column GAPSUSR.ICPS_WBC_TM_APP_MAIN.SPREADER_BANK is
'�ƹ�����������';

comment on column GAPSUSR.ICPS_WBC_TM_APP_MAIN.SPREADER_WAY is
'�ƹ㷽ʽ';

comment on column GAPSUSR.ICPS_WBC_TM_APP_MAIN.SPREADER_TYPE is
'�ƹ�����';

comment on column GAPSUSR.ICPS_WBC_TM_APP_MAIN.SPREADER_NAME is
'�ƹ�������';

comment on column GAPSUSR.ICPS_WBC_TM_APP_MAIN.SPREADER_NUM_PRE is
'�ƹ㵥λԤ���˱��';

comment on column GAPSUSR.ICPS_WBC_TM_APP_MAIN.SPREADER_PHONE is
'�ƹ����ֻ�����';

comment on column GAPSUSR.ICPS_WBC_TM_APP_MAIN.SALES_IND is
'�Ƿ�����ƹ��ʼ�';

comment on column GAPSUSR.ICPS_WBC_TM_APP_MAIN.OWNING_BRANCH is
'��������';

comment on column GAPSUSR.ICPS_WBC_TM_APP_MAIN.APP_PROMOTION_CD is
'������';

comment on column GAPSUSR.ICPS_WBC_TM_APP_MAIN.APP_SOURCE is
'������Դ';

comment on column GAPSUSR.ICPS_WBC_TM_APP_MAIN.BANK_CUSTOMER_ID is
'���ڿͻ���';

comment on column GAPSUSR.ICPS_WBC_TM_APP_MAIN.DD_FLAG is
'Լ���ۿ��Ƿ�ͨ��ʶ';

comment on column GAPSUSR.ICPS_WBC_TM_APP_MAIN.DEDUCT_DEAL_NO is
'�Կ�Э���';

comment on column GAPSUSR.ICPS_WBC_TM_APP_MAIN.IF_REFUSE is
'�Ƿ�ܾ�';

comment on column GAPSUSR.ICPS_WBC_TM_APP_MAIN.IF_END is
'�Ƿ�����ɼ�';

comment on column GAPSUSR.ICPS_WBC_TM_APP_MAIN.APPLY_FROM_TYPE is
'������Դ���';

comment on column GAPSUSR.ICPS_WBC_TM_APP_MAIN.APPNO_EXTERNAL is
'������_�ⲿ����';

comment on column GAPSUSR.ICPS_WBC_TM_APP_MAIN.APPNO_ATTACH_EXTERNAL is
'����������_�ⲿ����';

comment on column GAPSUSR.ICPS_WBC_TM_APP_MAIN.REMARK is
'��ע';

comment on column GAPSUSR.ICPS_WBC_TM_APP_MAIN.CREATE_USER is
'������';

comment on column GAPSUSR.ICPS_WBC_TM_APP_MAIN.UPDATE_USER is
'�޸���';

comment on column GAPSUSR.ICPS_WBC_TM_APP_MAIN.BIZ_NO is
'ҵ����ˮ��';

comment on column GAPSUSR.ICPS_WBC_TM_APP_MAIN.TRACE_NO is
'������ˮ��';

comment on column GAPSUSR.ICPS_WBC_TM_APP_MAIN.CALLED_NO is
'��������ˮ��';

comment on column GAPSUSR.ICPS_WBC_TM_APP_MAIN.RESULT_CODE is
'���������';

comment on column GAPSUSR.ICPS_WBC_TM_APP_MAIN.CREATED_DATETIME is
'����ʱ��';

comment on column GAPSUSR.ICPS_WBC_TM_APP_MAIN.LAST_MODIFIED_DATETIME is
'����޸�ʱ��';

comment on column GAPSUSR.ICPS_WBC_TM_APP_MAIN.JPA_VERSION is
'�ֹ���';

comment on column GAPSUSR.ICPS_WBC_TM_APP_MAIN.IS_SHARED_CREDIT_LIMIT is
'�Ƿ�����';

comment on column GAPSUSR.ICPS_WBC_TM_APP_MAIN.APPROVAL_DATETIME is
'����ͨ��ʱ��';

comment on column GAPSUSR.ICPS_WBC_TM_APP_MAIN.IS_CHECK_FLAG is
'������˱�ʶ';

comment on column GAPSUSR.ICPS_WBC_TM_APP_MAIN.EXTEND_PARAM1 is
'��չ1';

comment on column GAPSUSR.ICPS_WBC_TM_APP_MAIN.EXTEND_PARAM2 is
'��չ2';

comment on column GAPSUSR.ICPS_WBC_TM_APP_MAIN.EXTEND_PARAM3 is
'��չ3';

--==============================================================
-- Table: ICPS_WBC_TM_APP_PRIM_APPLICANT_INFO
--==============================================================
create table GAPSUSR.ICPS_WBC_TM_APP_PRIM_APPLICANT_INFO
(
   BUSI_DATE            CHARACTER(8)           not null,
   FILE_ORDER           INTEGER                not null,
   ID                   VARCHAR(19),
   ORG                  CHARACTER(12),
   APP_NO               VARCHAR(20),
   IF_SELECTED_CARD     CHARACTER,
   CARD_NO              VARCHAR(19),
   "NAME"               VARCHAR(80),
   EMB_LOGO             VARCHAR(30),
   GENDER               VARCHAR(2),
   NATIONALITY          VARCHAR(3),
   RESIDENCY_COUNTRY_CD CHARACTER(3),
   ID_TYPE              CHARACTER,
   ID_NO                VARCHAR(18),
   ID_LAST_DATE         VARCHAR(8),
   ID_ISSUER_ADDRESS    VARCHAR(200),
   BIRTHDAY             VARCHAR(8),
   LIQUID_ASSET         CHARACTER,
   YEAR_INCOME          DECIMAL(15,2),
   QUALIFICATION        CHARACTER,
   MARITAL_STATUS       CHARACTER,
   HOME_ADDR_CTRY_CD    VARCHAR(3),
   HOME_STATE           VARCHAR(40),
   HOME_CITY            VARCHAR(40),
   HOME_ZONE            VARCHAR(40),
   HOUSE_OWNERSHIP      CHARACTER,
   HOME_ADD             VARCHAR(200),
   HOME_POSTCODE        VARCHAR(10),
   HOME_PHONE           VARCHAR(20),
   HOME_STAND_FROM      VARCHAR(8),
   CELLPHONE            VARCHAR(20),
   EMAIL                VARCHAR(80),
   QQ_ACCT              VARCHAR(40),
   OPEN_ID              VARCHAR(40),
   HOUSE_TYPE           CHARACTER,
   FAMILY_MEMBER        VARCHAR(2),
   FAMILY_AVGE_VENUE    DECIMAL(15,2),
   BANKMEM_FLAG         CHARACTER,
   BANKMEMBER_NO        VARCHAR(20),
   CORP_NAME            VARCHAR(200),
   EMP_ADDR_CTRY_CD     VARCHAR(3),
   EMP_PROVINCE         VARCHAR(40),
   EMP_CITY             VARCHAR(40),
   EMP_ZONE             VARCHAR(40),
   EMP_ADD              VARCHAR(200),
   EMP_POSTCODE         VARCHAR(10),
   EMP_PHONE            VARCHAR(20),
   EMP_DEPAPMENT        VARCHAR(80),
   EMP_POST             CHARACTER,
   EMP_STRUCTURE        CHARACTER,
   EMP_TYPE             CHARACTER,
   EMP_WORKYEARS        DECIMAL(2,2),
   CORP_FAX             VARCHAR(20),
   OCCUPATION           CHARACTER,
   TITLE_OF_TECHNICAL   CHARACTER,
   EMP_STAND_FROM       VARCHAR(8),
   POS_PIN_VERIFY_IND   CHARACTER,
   PHOTO_USE_FLAG       CHARACTER,
   GROUP_NUM            VARCHAR(10),
   EMP_STABILITY        CHARACTER,
   EMP_STATUS           CHARACTER,
   PR_OF_COUNTRY        CHARACTER,
   OTHER_ASK            VARCHAR(80),
   OTHER_ANSWER         VARCHAR(80),
   PRI_NAME             VARCHAR(80),
   PRI_CARD_NUM         VARCHAR(19),
   APPNO_EXTERNAL       VARCHAR(20),
   BANK_CUSTOMER_ID     VARCHAR(32),
   REF_CONTACT_ID       VARCHAR(40),
   REF_CONTACT_TYPE     CHARACTER,
   PLEDEG_TYPE          VARCHAR(2),
   UPDATE_USER          VARCHAR(40),
   CREATE_USER          VARCHAR(40),
   CREATED_DATETIME     VARCHAR(14),
   LAST_MODIFIED_DATETIME VARCHAR(14),
   JPA_VERSION          INTEGER,
   CUST_NO              VARCHAR(19),
   ACCT_NO              VARCHAR(19),
   PRODUCT_CD           VARCHAR(6),
   OPEN_ACC_DATETIME    VARCHAR(14),
   IS_CHECK_FLAG        CHARACTER,
   EXTEND_PARAM1        VARCHAR(100),
   EXTEND_PARAM2        VARCHAR(250),
   EXTEND_PARAM3        VARCHAR(40),
   constraint PK_ICPS_WBC_TM_APP_PRIM_APPLICANT_INFO primary key (BUSI_DATE, FILE_ORDER)
)  IN GAPS_DATA INDEX IN GAPS_INDEX ;

comment on table GAPSUSR.ICPS_WBC_TM_APP_PRIM_APPLICANT_INFO is
'������������Ϣ��';

comment on column GAPSUSR.ICPS_WBC_TM_APP_PRIM_APPLICANT_INFO.BUSI_DATE is
'ҵ������';

comment on column GAPSUSR.ICPS_WBC_TM_APP_PRIM_APPLICANT_INFO.FILE_ORDER is
'�ļ����';

comment on column GAPSUSR.ICPS_WBC_TM_APP_PRIM_APPLICANT_INFO.ID is
'��ʶ';

comment on column GAPSUSR.ICPS_WBC_TM_APP_PRIM_APPLICANT_INFO.ORG is
'������';

comment on column GAPSUSR.ICPS_WBC_TM_APP_PRIM_APPLICANT_INFO.APP_NO is
'��������';

comment on column GAPSUSR.ICPS_WBC_TM_APP_PRIM_APPLICANT_INFO.IF_SELECTED_CARD is
'�Ƿ���ѡ����';

comment on column GAPSUSR.ICPS_WBC_TM_APP_PRIM_APPLICANT_INFO.CARD_NO is
'����';

comment on column GAPSUSR.ICPS_WBC_TM_APP_PRIM_APPLICANT_INFO."NAME" is
'����';

comment on column GAPSUSR.ICPS_WBC_TM_APP_PRIM_APPLICANT_INFO.EMB_LOGO is
'͹ӡ����';

comment on column GAPSUSR.ICPS_WBC_TM_APP_PRIM_APPLICANT_INFO.GENDER is
'�Ա�';

comment on column GAPSUSR.ICPS_WBC_TM_APP_PRIM_APPLICANT_INFO.NATIONALITY is
'����';

comment on column GAPSUSR.ICPS_WBC_TM_APP_PRIM_APPLICANT_INFO.RESIDENCY_COUNTRY_CD is
'���þ�ס�ع��Ҵ���';

comment on column GAPSUSR.ICPS_WBC_TM_APP_PRIM_APPLICANT_INFO.ID_TYPE is
'֤������';

comment on column GAPSUSR.ICPS_WBC_TM_APP_PRIM_APPLICANT_INFO.ID_NO is
'֤������';

comment on column GAPSUSR.ICPS_WBC_TM_APP_PRIM_APPLICANT_INFO.ID_LAST_DATE is
'֤��������';

comment on column GAPSUSR.ICPS_WBC_TM_APP_PRIM_APPLICANT_INFO.ID_ISSUER_ADDRESS is
'��֤�������ڵ�ַ';

comment on column GAPSUSR.ICPS_WBC_TM_APP_PRIM_APPLICANT_INFO.BIRTHDAY is
'����';

comment on column GAPSUSR.ICPS_WBC_TM_APP_PRIM_APPLICANT_INFO.LIQUID_ASSET is
'�����ʲ�����';

comment on column GAPSUSR.ICPS_WBC_TM_APP_PRIM_APPLICANT_INFO.YEAR_INCOME is
'������';

comment on column GAPSUSR.ICPS_WBC_TM_APP_PRIM_APPLICANT_INFO.QUALIFICATION is
'����״��';

comment on column GAPSUSR.ICPS_WBC_TM_APP_PRIM_APPLICANT_INFO.MARITAL_STATUS is
'����״��';

comment on column GAPSUSR.ICPS_WBC_TM_APP_PRIM_APPLICANT_INFO.HOME_ADDR_CTRY_CD is
'��ͥ���Ҵ���';

comment on column GAPSUSR.ICPS_WBC_TM_APP_PRIM_APPLICANT_INFO.HOME_STATE is
'��ͥ����ʡ';

comment on column GAPSUSR.ICPS_WBC_TM_APP_PRIM_APPLICANT_INFO.HOME_CITY is
'��ͥ������';

comment on column GAPSUSR.ICPS_WBC_TM_APP_PRIM_APPLICANT_INFO.HOME_ZONE is
'��ͥ��������';

comment on column GAPSUSR.ICPS_WBC_TM_APP_PRIM_APPLICANT_INFO.HOUSE_OWNERSHIP is
'���ݳ�������';

comment on column GAPSUSR.ICPS_WBC_TM_APP_PRIM_APPLICANT_INFO.HOME_ADD is
'��ͥ��ַ';

comment on column GAPSUSR.ICPS_WBC_TM_APP_PRIM_APPLICANT_INFO.HOME_POSTCODE is
'��ͥסլ�ʱ�';

comment on column GAPSUSR.ICPS_WBC_TM_APP_PRIM_APPLICANT_INFO.HOME_PHONE is
'��ͥ�绰';

comment on column GAPSUSR.ICPS_WBC_TM_APP_PRIM_APPLICANT_INFO.HOME_STAND_FROM is
'��סַ��ס��ʼ����';

comment on column GAPSUSR.ICPS_WBC_TM_APP_PRIM_APPLICANT_INFO.CELLPHONE is
'�ƶ��绰';

comment on column GAPSUSR.ICPS_WBC_TM_APP_PRIM_APPLICANT_INFO.EMAIL is
'��������';

comment on column GAPSUSR.ICPS_WBC_TM_APP_PRIM_APPLICANT_INFO.QQ_ACCT is
'QQ�˺�';

comment on column GAPSUSR.ICPS_WBC_TM_APP_PRIM_APPLICANT_INFO.OPEN_ID is
'���ں�';

comment on column GAPSUSR.ICPS_WBC_TM_APP_PRIM_APPLICANT_INFO.HOUSE_TYPE is
'סլ����';

comment on column GAPSUSR.ICPS_WBC_TM_APP_PRIM_APPLICANT_INFO.FAMILY_MEMBER is
'��ͥ�˿�';

comment on column GAPSUSR.ICPS_WBC_TM_APP_PRIM_APPLICANT_INFO.FAMILY_AVGE_VENUE is
'��ͥ�˾�������';

comment on column GAPSUSR.ICPS_WBC_TM_APP_PRIM_APPLICANT_INFO.BANKMEM_FLAG is
'�Ƿ�����Ա��';

comment on column GAPSUSR.ICPS_WBC_TM_APP_PRIM_APPLICANT_INFO.BANKMEMBER_NO is
'����Ա����';

comment on column GAPSUSR.ICPS_WBC_TM_APP_PRIM_APPLICANT_INFO.CORP_NAME is
'��˾����';

comment on column GAPSUSR.ICPS_WBC_TM_APP_PRIM_APPLICANT_INFO.EMP_ADDR_CTRY_CD is
'��˾���Ҵ���';

comment on column GAPSUSR.ICPS_WBC_TM_APP_PRIM_APPLICANT_INFO.EMP_PROVINCE is
'��˾����ʡ';

comment on column GAPSUSR.ICPS_WBC_TM_APP_PRIM_APPLICANT_INFO.EMP_CITY is
'��˾������';

comment on column GAPSUSR.ICPS_WBC_TM_APP_PRIM_APPLICANT_INFO.EMP_ZONE is
'��˾������/��';

comment on column GAPSUSR.ICPS_WBC_TM_APP_PRIM_APPLICANT_INFO.EMP_ADD is
'��˾��ַ';

comment on column GAPSUSR.ICPS_WBC_TM_APP_PRIM_APPLICANT_INFO.EMP_POSTCODE is
'��˾�ʱ�';

comment on column GAPSUSR.ICPS_WBC_TM_APP_PRIM_APPLICANT_INFO.EMP_PHONE is
'��˾�绰';

comment on column GAPSUSR.ICPS_WBC_TM_APP_PRIM_APPLICANT_INFO.EMP_DEPAPMENT is
'��ְ����';

comment on column GAPSUSR.ICPS_WBC_TM_APP_PRIM_APPLICANT_INFO.EMP_POST is
'ְ��';

comment on column GAPSUSR.ICPS_WBC_TM_APP_PRIM_APPLICANT_INFO.EMP_STRUCTURE is
'��˾����';

comment on column GAPSUSR.ICPS_WBC_TM_APP_PRIM_APPLICANT_INFO.EMP_TYPE is
'��˾��ҵ���';

comment on column GAPSUSR.ICPS_WBC_TM_APP_PRIM_APPLICANT_INFO.EMP_WORKYEARS is
'����˾��������';

comment on column GAPSUSR.ICPS_WBC_TM_APP_PRIM_APPLICANT_INFO.CORP_FAX is
'��˾����';

comment on column GAPSUSR.ICPS_WBC_TM_APP_PRIM_APPLICANT_INFO.OCCUPATION is
'ְҵ';

comment on column GAPSUSR.ICPS_WBC_TM_APP_PRIM_APPLICANT_INFO.TITLE_OF_TECHNICAL is
'ְ��';

comment on column GAPSUSR.ICPS_WBC_TM_APP_PRIM_APPLICANT_INFO.EMP_STAND_FROM is
'�ֵ�λ������ʼ����';

comment on column GAPSUSR.ICPS_WBC_TM_APP_PRIM_APPLICANT_INFO.POS_PIN_VERIFY_IND is
'�Ƿ�����ƾ��';

comment on column GAPSUSR.ICPS_WBC_TM_APP_PRIM_APPLICANT_INFO.PHOTO_USE_FLAG is
'�Ƿ���տ�';

comment on column GAPSUSR.ICPS_WBC_TM_APP_PRIM_APPLICANT_INFO.GROUP_NUM is
'�����Ű���';

comment on column GAPSUSR.ICPS_WBC_TM_APP_PRIM_APPLICANT_INFO.EMP_STABILITY is
'�����ȶ���';

comment on column GAPSUSR.ICPS_WBC_TM_APP_PRIM_APPLICANT_INFO.EMP_STATUS is
'�Ƿ���ְ';

comment on column GAPSUSR.ICPS_WBC_TM_APP_PRIM_APPLICANT_INFO.PR_OF_COUNTRY is
'�Ƿ����þ�ס';

comment on column GAPSUSR.ICPS_WBC_TM_APP_PRIM_APPLICANT_INFO.OTHER_ASK is
'Ԥ������';

comment on column GAPSUSR.ICPS_WBC_TM_APP_PRIM_APPLICANT_INFO.OTHER_ANSWER is
'Ԥ����';

comment on column GAPSUSR.ICPS_WBC_TM_APP_PRIM_APPLICANT_INFO.PRI_NAME is
'�Ƽ�������';

comment on column GAPSUSR.ICPS_WBC_TM_APP_PRIM_APPLICANT_INFO.PRI_CARD_NUM is
'�Ƽ��˿���';

comment on column GAPSUSR.ICPS_WBC_TM_APP_PRIM_APPLICANT_INFO.APPNO_EXTERNAL is
'������_�ⲿ����';

comment on column GAPSUSR.ICPS_WBC_TM_APP_PRIM_APPLICANT_INFO.BANK_CUSTOMER_ID is
'���ڿͻ���';

comment on column GAPSUSR.ICPS_WBC_TM_APP_PRIM_APPLICANT_INFO.REF_CONTACT_ID is
'�Ƽ�����ϵ����';

comment on column GAPSUSR.ICPS_WBC_TM_APP_PRIM_APPLICANT_INFO.REF_CONTACT_TYPE is
'�Ƽ�����ϵ��������';

comment on column GAPSUSR.ICPS_WBC_TM_APP_PRIM_APPLICANT_INFO.PLEDEG_TYPE is
'ѺƷ����';

comment on column GAPSUSR.ICPS_WBC_TM_APP_PRIM_APPLICANT_INFO.UPDATE_USER is
'�޸���';

comment on column GAPSUSR.ICPS_WBC_TM_APP_PRIM_APPLICANT_INFO.CREATE_USER is
'������';

comment on column GAPSUSR.ICPS_WBC_TM_APP_PRIM_APPLICANT_INFO.CREATED_DATETIME is
'����ʱ��';

comment on column GAPSUSR.ICPS_WBC_TM_APP_PRIM_APPLICANT_INFO.LAST_MODIFIED_DATETIME is
'����޸�ʱ��';

comment on column GAPSUSR.ICPS_WBC_TM_APP_PRIM_APPLICANT_INFO.JPA_VERSION is
'�ֹ���';

comment on column GAPSUSR.ICPS_WBC_TM_APP_PRIM_APPLICANT_INFO.CUST_NO is
'�ͻ���';

comment on column GAPSUSR.ICPS_WBC_TM_APP_PRIM_APPLICANT_INFO.ACCT_NO is
'�˻���';

comment on column GAPSUSR.ICPS_WBC_TM_APP_PRIM_APPLICANT_INFO.PRODUCT_CD is
'��Ʒ���';

comment on column GAPSUSR.ICPS_WBC_TM_APP_PRIM_APPLICANT_INFO.OPEN_ACC_DATETIME is
'����ʱ��';

comment on column GAPSUSR.ICPS_WBC_TM_APP_PRIM_APPLICANT_INFO.IS_CHECK_FLAG is
'������˱�ʶ';

comment on column GAPSUSR.ICPS_WBC_TM_APP_PRIM_APPLICANT_INFO.EXTEND_PARAM1 is
'��չ1';

comment on column GAPSUSR.ICPS_WBC_TM_APP_PRIM_APPLICANT_INFO.EXTEND_PARAM2 is
'��չ2';

comment on column GAPSUSR.ICPS_WBC_TM_APP_PRIM_APPLICANT_INFO.EXTEND_PARAM3 is
'��չ3';

--==============================================================
-- Table: ICPS_WBC_TM_AUTH_BANK_COST
--==============================================================
create table GAPSUSR.ICPS_WBC_TM_AUTH_BANK_COST
(
   BUSI_DATE            CHARACTER(8)           not null,
   FILE_ORDER           INTEGER                not null,
   CONSUMER_TRANS_ID    VARCHAR(32),
   BANK_GROUP_ID        VARCHAR(5),
   BANK_NO              VARCHAR(10),
   REG_TYPE             VARCHAR(50),
   REG_AMT              DECIMAL(15,2),
   REG_STATUS           VARCHAR(10),
   BIZ_DATE             VARCHAR(8),
   REG_SYS_ID           VARCHAR(32),
   REG_DATE             VARCHAR(8),
   REG_TIME             VARCHAR(14),
   RECON_CODE           VARCHAR(20),
   ORI_SYS_ID           VARCHAR(32),
   CUST_ID              VARCHAR(20),
   ACCT_NO              VARCHAR(20),
   ACCT_TYPE            CHARACTER,
   RETRY                INTEGER,
   CREATED_DATETIME     VARCHAR(14),
   LAST_MODIFIED_DATETIME VARCHAR(14),
   JPA_VERSION          INTEGER,
   CARD_NO              VARCHAR(19),
   IS_CHECK_FLAG        CHARACTER,
   EXTEND_PARAM1        VARCHAR(100),
   EXTEND_PARAM2        VARCHAR(250),
   EXTEND_PARAM3        VARCHAR(40),
   constraint PK_ICPS_WBC_TM_AUTH_BANK_COST primary key (FILE_ORDER, BUSI_DATE)
)  IN GAPS_DATA INDEX IN GAPS_INDEX ;

comment on table GAPSUSR.ICPS_WBC_TM_AUTH_BANK_COST is
'��Ȩ��ˮ���Ų�ֱ�';

comment on column GAPSUSR.ICPS_WBC_TM_AUTH_BANK_COST.BUSI_DATE is
'ҵ������';

comment on column GAPSUSR.ICPS_WBC_TM_AUTH_BANK_COST.FILE_ORDER is
'�ļ����';

comment on column GAPSUSR.ICPS_WBC_TM_AUTH_BANK_COST.CONSUMER_TRANS_ID is
'ҵ����ˮ��';

comment on column GAPSUSR.ICPS_WBC_TM_AUTH_BANK_COST.BANK_GROUP_ID is
'���ű��';

comment on column GAPSUSR.ICPS_WBC_TM_AUTH_BANK_COST.BANK_NO is
'���к�';

comment on column GAPSUSR.ICPS_WBC_TM_AUTH_BANK_COST.REG_TYPE is
'�Ǽ�����';

comment on column GAPSUSR.ICPS_WBC_TM_AUTH_BANK_COST.REG_AMT is
'�Ǽǽ��';

comment on column GAPSUSR.ICPS_WBC_TM_AUTH_BANK_COST.REG_STATUS is
'�Ǽ�״̬';

comment on column GAPSUSR.ICPS_WBC_TM_AUTH_BANK_COST.BIZ_DATE is
'ҵ������';

comment on column GAPSUSR.ICPS_WBC_TM_AUTH_BANK_COST.REG_SYS_ID is
'������ˮ��';

comment on column GAPSUSR.ICPS_WBC_TM_AUTH_BANK_COST.REG_DATE is
'��������';

comment on column GAPSUSR.ICPS_WBC_TM_AUTH_BANK_COST.REG_TIME is
'��������ʱ��';

comment on column GAPSUSR.ICPS_WBC_TM_AUTH_BANK_COST.RECON_CODE is
'������';

comment on column GAPSUSR.ICPS_WBC_TM_AUTH_BANK_COST.ORI_SYS_ID is
'ԭ������ˮ��';

comment on column GAPSUSR.ICPS_WBC_TM_AUTH_BANK_COST.CUST_ID is
'�ͻ����';

comment on column GAPSUSR.ICPS_WBC_TM_AUTH_BANK_COST.ACCT_NO is
'�˻����';

comment on column GAPSUSR.ICPS_WBC_TM_AUTH_BANK_COST.ACCT_TYPE is
'�˻�����';

comment on column GAPSUSR.ICPS_WBC_TM_AUTH_BANK_COST.RETRY is
'���Դ���';

comment on column GAPSUSR.ICPS_WBC_TM_AUTH_BANK_COST.CREATED_DATETIME is
'����ʱ��';

comment on column GAPSUSR.ICPS_WBC_TM_AUTH_BANK_COST.LAST_MODIFIED_DATETIME is
'ʱ���';

comment on column GAPSUSR.ICPS_WBC_TM_AUTH_BANK_COST.JPA_VERSION is
'�ֹ����汾��';

comment on column GAPSUSR.ICPS_WBC_TM_AUTH_BANK_COST.CARD_NO is
'����';

comment on column GAPSUSR.ICPS_WBC_TM_AUTH_BANK_COST.IS_CHECK_FLAG is
'������˱�ʶ';

comment on column GAPSUSR.ICPS_WBC_TM_AUTH_BANK_COST.EXTEND_PARAM1 is
'��չ1';

comment on column GAPSUSR.ICPS_WBC_TM_AUTH_BANK_COST.EXTEND_PARAM2 is
'��չ2';

comment on column GAPSUSR.ICPS_WBC_TM_AUTH_BANK_COST.EXTEND_PARAM3 is
'��չ3';

--==============================================================
-- Table: ICPS_WBC_TM_AUTH_BANK_COST_DTL
--==============================================================
create table GAPSUSR.ICPS_WBC_TM_AUTH_BANK_COST_DTL
(
   BUSI_DATE            CHARACTER(8)           not null,
   FILE_ORDER           INTEGER                not null,
   CONSUMER_TRANS_ID    VARCHAR(32),
   BANK_GROUP_ID        VARCHAR(5),
   BANK_NO              VARCHAR(10),
   LOAN_RECEIPT_NBR     VARCHAR(20),
   REG_TYPE             VARCHAR(10),
   REG_AMT              DECIMAL(15,2),
   BIZ_DATE             VARCHAR(8),
   CUST_ID              VARCHAR(20),
   ACCT_NO              VARCHAR(20),
   ACCT_TYPE            CHARACTER,
   CREATED_DATETIME     VARCHAR(14),
   LAST_MODIFIED_DATETIME VARCHAR(14),
   CARD_NO              VARCHAR(19),
   IS_CHECK_FLAG        CHARACTER,
   EXTEND_PARAM1        VARCHAR(100),
   EXTEND_PARAM2        VARCHAR(250),
   EXTEND_PARAM3        VARCHAR(40),
   constraint PK_ICPS_WBC_TM_AUTH_BANK_COST_DTL primary key (BUSI_DATE, FILE_ORDER)
)  IN GAPS_DATA INDEX IN GAPS_INDEX ;

comment on table GAPSUSR.ICPS_WBC_TM_AUTH_BANK_COST_DTL is
'��Ȩ��ˮ���Ų����ϸ��';

comment on column GAPSUSR.ICPS_WBC_TM_AUTH_BANK_COST_DTL.BUSI_DATE is
'ҵ������';

comment on column GAPSUSR.ICPS_WBC_TM_AUTH_BANK_COST_DTL.FILE_ORDER is
'�ļ����';

comment on column GAPSUSR.ICPS_WBC_TM_AUTH_BANK_COST_DTL.CONSUMER_TRANS_ID is
'ҵ����ˮ��';

comment on column GAPSUSR.ICPS_WBC_TM_AUTH_BANK_COST_DTL.BANK_GROUP_ID is
'���ű��';

comment on column GAPSUSR.ICPS_WBC_TM_AUTH_BANK_COST_DTL.BANK_NO is
'���к�';

comment on column GAPSUSR.ICPS_WBC_TM_AUTH_BANK_COST_DTL.LOAN_RECEIPT_NBR is
'��ݺ�';

comment on column GAPSUSR.ICPS_WBC_TM_AUTH_BANK_COST_DTL.REG_TYPE is
'�Ǽ�����';

comment on column GAPSUSR.ICPS_WBC_TM_AUTH_BANK_COST_DTL.REG_AMT is
'�Ǽǽ��';

comment on column GAPSUSR.ICPS_WBC_TM_AUTH_BANK_COST_DTL.BIZ_DATE is
'ҵ������';

comment on column GAPSUSR.ICPS_WBC_TM_AUTH_BANK_COST_DTL.CUST_ID is
'�ͻ����';

comment on column GAPSUSR.ICPS_WBC_TM_AUTH_BANK_COST_DTL.ACCT_NO is
'�˻����';

comment on column GAPSUSR.ICPS_WBC_TM_AUTH_BANK_COST_DTL.ACCT_TYPE is
'�˻�����';

comment on column GAPSUSR.ICPS_WBC_TM_AUTH_BANK_COST_DTL.CREATED_DATETIME is
'����ʱ��';

comment on column GAPSUSR.ICPS_WBC_TM_AUTH_BANK_COST_DTL.LAST_MODIFIED_DATETIME is
'ʱ���';

comment on column GAPSUSR.ICPS_WBC_TM_AUTH_BANK_COST_DTL.CARD_NO is
'����';

comment on column GAPSUSR.ICPS_WBC_TM_AUTH_BANK_COST_DTL.IS_CHECK_FLAG is
'������˱�ʶ';

comment on column GAPSUSR.ICPS_WBC_TM_AUTH_BANK_COST_DTL.EXTEND_PARAM1 is
'��չ1';

comment on column GAPSUSR.ICPS_WBC_TM_AUTH_BANK_COST_DTL.EXTEND_PARAM2 is
'��չ2';

comment on column GAPSUSR.ICPS_WBC_TM_AUTH_BANK_COST_DTL.EXTEND_PARAM3 is
'��չ3';

--==============================================================
-- Table: ICPS_WBC_TM_AUTH_HST
--==============================================================
create table GAPSUSR.ICPS_WBC_TM_AUTH_HST
(
   BUSI_DATE            CHARACTER(8)           not null,
   FILE_ORDER           INTEGER                not null,
   ORG                  CHARACTER(12),
   LOG_KV               VARCHAR(20),
   ACCT_NO              VARCHAR(20),
   ACCT_TYPE            CHARACTER,
   LOGICAL_CARD_NO      VARCHAR(19),
   ACQ_REF_NO           INTEGER,
   TXN_AMT              DECIMAL(15,2),
   TXN_CURR_CD          CHARACTER(3),
   AUTH_CODE            CHARACTER(6),
   ACQ_NAME_ADDR        VARCHAR(40),
   CHB_TXN_AMT          DECIMAL(15,2),
   CHB_CURR_CD          CHARACTER(3),
   CHANNEL              VARCHAR(15),
   MCC                  CHARACTER(4),
   ACQ_BRANCH_ID        CHARACTER(9),
   FWD_INST_ID          VARCHAR(11),
   TRANSMISSION_TIMESTAMP VARCHAR(10),
   SETTLE_DATE          CHARACTER(4),
   TXN_DIRECTION        VARCHAR(20),
   TXN_TERMINAL         VARCHAR(40),
   TXN_STATUS           CHARACTER,
   TXN_TYPE             VARCHAR(20),
   LOG_OL_TIME          VARCHAR(14),
   LOG_BIZ_DATE         VARCHAR(8),
   MTI                  CHARACTER(4),
   ORIG_TXN_TYPE        VARCHAR(20),
   ORIG_FWD_INST_ID     VARCHAR(11),
   ORIG_ACQ_INST_ID     VARCHAR(11),
   ORIG_MTI             VARCHAR(4),
   ORIG_TRANS_DATE      VARCHAR(8),
   ORIG_TRACE_NO        INTEGER,
   ORIG_TXN_PROC        CHARACTER(6),
   ORIG_TXN_AMT         DECIMAL(15,2),
   ORIG_LOG_KV          VARCHAR(20),
   ORIG_TXN_VAL_1       VARCHAR(38),
   ORIG_TXN_VAL_2       VARCHAR(40),
   ORIG_CHB_TXN_AMT     DECIMAL(15,2),
   ORIG_BIZ_DATE        VARCHAR(8),
   LAST_REVERSAL_DATE   VARCHAR(14),
   VOID_COUNT           INTEGER,
   MANUAL_AUTH_FLAG     CHARACTER,
   OPERA_ID             VARCHAR(40),
   BRAND                VARCHAR(2),
   PRODUCT_CD           CHARACTER(6),
   MCC_TYPE             CHARACTER(2),
   FINAL_REASON         CHARACTER(4),
   FINAL_ACTION         CHARACTER,
   COMP_AMT             DECIMAL(15,2),
   FINAL_UPD_DIRECTION  CHARACTER,
   FINAL_UPD_AMT        DECIMAL(15,2),
   IC_IND               CHARACTER,
   THE_3DSECURE_TYPE    CHARACTER,
   VIP_STATUS           CHARACTER,
   CURR_BAL             DECIMAL(15,2),
   CASH_AMT             DECIMAL(15,2),
   OTB                  DECIMAL(15,2),
   CASH_OTB             DECIMAL(15,2),
   CUST_OTB             DECIMAL(15,2),
   CARD_BLACK_FLAG      VARCHAR(20),
   MERCHANT_BLACK_FLAG  VARCHAR(20),
   EXPIRE_DATE          VARCHAR(4),
   TRACK_ONE_RESULT     VARCHAR(20),
   TRACK_TWO_RESULT     VARCHAR(20),
   TRACK_THREE_RESULT   VARCHAR(20),
   PWD_TYPE             CHARACTER,
   CHECK_PWD_RESULT     VARCHAR(20),
   PAY_PWD_ERR_NUM      INTEGER,
   CHECK_CVV_RESULT     VARCHAR(20),
   CHECK_CVV2_RESULT    VARCHAR(20),
   CHECK_ICVN_RESULT    VARCHAR(20),
   CHECK_ARQC_RESULT    VARCHAR(20),
   CHECK_ATC_RESULT     VARCHAR(20),
   CHECK_CVR_RESULT     VARCHAR(20),
   CHECK_TVR_RESULT     VARCHAR(20),
   REJ_REASON           VARCHAR(40),
   UNMATCH_CR           DECIMAL(15,2),
   UNMATCH_DB           DECIMAL(15,2),
   B002                 VARCHAR(20),
   B003                 VARCHAR(6),
   B007                 VARCHAR(10),
   B011                 CHARACTER(6),
   B022                 VARCHAR(3),
   B025                 VARCHAR(4),
   B032                 VARCHAR(15),
   B033                 VARCHAR(40),
   B039                 VARCHAR(2),
   B042                 VARCHAR(15),
   B060                 VARCHAR(103),
   B061                 VARCHAR(400),
   B090                 VARCHAR(42),
   OPERA_TERM_ID        VARCHAR(20),
   JPA_VERSION          INTEGER,
   B004                 DECIMAL(13),
   B006                 DECIMAL(13),
   B049                 CHARACTER(3),
   B051                 CHARACTER(3),
   B037                 CHARACTER(23),
   B028                 DECIMAL(13),
   B048                 VARCHAR(999),
   B054                 VARCHAR(60),
   CARD_BLOCK_CODE      VARCHAR(27),
   ACCOUNT_BLOCK_CODE   VARCHAR(27),
   MEDIUM_BLOCK_CODE    VARCHAR(27),
   CONSUMER_TRANS_ID    VARCHAR(32),
   SYS_TRANS_ID         VARCHAR(32),
   QCHANNEL_ID          VARCHAR(15),
   SUB_TERMINAL_TYPE    VARCHAR(15),
   SUB_MERCH_ID         VARCHAR(40),
   SUB_MERCH_NAME       VARCHAR(60),
   WARES_DESC           VARCHAR(60),
   LAST_MODIFIED_DATETIME VARCHAR(14),
   PART_MONTH           INTEGER,
   PAID_STMT_DATE       VARCHAR(8),
   REPAY_AMT            DECIMAL(15,2),
   TRANSFER_TYPE        CHARACTER(8),
   IS_CHECK_FLAG        CHARACTER,
   EXTEND_PARAM1        VARCHAR(100),
   EXTEND_PARAM2        VARCHAR(250),
   EXTEND_PARAM3        VARCHAR(40),
   constraint PK_ICPS_WBC_TM_AUTH_HST primary key (BUSI_DATE, FILE_ORDER)
)  IN GAPS_DATA INDEX IN GAPS_INDEX ;

comment on table GAPSUSR.ICPS_WBC_TM_AUTH_HST is
'��Ȩ������ʷ';

comment on column GAPSUSR.ICPS_WBC_TM_AUTH_HST.BUSI_DATE is
'ҵ������';

comment on column GAPSUSR.ICPS_WBC_TM_AUTH_HST.FILE_ORDER is
'�ļ����';

comment on column GAPSUSR.ICPS_WBC_TM_AUTH_HST.ORG is
'������';

comment on column GAPSUSR.ICPS_WBC_TM_AUTH_HST.LOG_KV is
'LOG�ļ�ֵ';

comment on column GAPSUSR.ICPS_WBC_TM_AUTH_HST.ACCT_NO is
'�˻����';

comment on column GAPSUSR.ICPS_WBC_TM_AUTH_HST.ACCT_TYPE is
'�˻�����';

comment on column GAPSUSR.ICPS_WBC_TM_AUTH_HST.LOGICAL_CARD_NO is
'�߼�����';

comment on column GAPSUSR.ICPS_WBC_TM_AUTH_HST.ACQ_REF_NO is
'����������ױ���';

comment on column GAPSUSR.ICPS_WBC_TM_AUTH_HST.TXN_AMT is
'���׽��';

comment on column GAPSUSR.ICPS_WBC_TM_AUTH_HST.TXN_CURR_CD is
'���ױ��ִ���';

comment on column GAPSUSR.ICPS_WBC_TM_AUTH_HST.AUTH_CODE is
'��Ȩ��';

comment on column GAPSUSR.ICPS_WBC_TM_AUTH_HST.ACQ_NAME_ADDR is
'����������Ƶ�ַ';

comment on column GAPSUSR.ICPS_WBC_TM_AUTH_HST.CHB_TXN_AMT is
'�ֿ����˻����ֽ��';

comment on column GAPSUSR.ICPS_WBC_TM_AUTH_HST.CHB_CURR_CD is
'�ֿ����˻�����';

comment on column GAPSUSR.ICPS_WBC_TM_AUTH_HST.CHANNEL is
'��������';

comment on column GAPSUSR.ICPS_WBC_TM_AUTH_HST.MCC is
'�̻�������';

comment on column GAPSUSR.ICPS_WBC_TM_AUTH_HST.ACQ_BRANCH_ID is
'������д���';

comment on column GAPSUSR.ICPS_WBC_TM_AUTH_HST.FWD_INST_ID is
'ת��������';

comment on column GAPSUSR.ICPS_WBC_TM_AUTH_HST.TRANSMISSION_TIMESTAMP is
'��������';

comment on column GAPSUSR.ICPS_WBC_TM_AUTH_HST.SETTLE_DATE is
'��������';

comment on column GAPSUSR.ICPS_WBC_TM_AUTH_HST.TXN_DIRECTION is
'���׷���';

comment on column GAPSUSR.ICPS_WBC_TM_AUTH_HST.TXN_TERMINAL is
'�����ն�';

comment on column GAPSUSR.ICPS_WBC_TM_AUTH_HST.TXN_STATUS is
'����״̬';

comment on column GAPSUSR.ICPS_WBC_TM_AUTH_HST.TXN_TYPE is
'��������';

comment on column GAPSUSR.ICPS_WBC_TM_AUTH_HST.LOG_OL_TIME is
'LOG����ʱ��';

comment on column GAPSUSR.ICPS_WBC_TM_AUTH_HST.LOG_BIZ_DATE is
'����ҵ������';

comment on column GAPSUSR.ICPS_WBC_TM_AUTH_HST.MTI is
'�������ͱ�ʶ';

comment on column GAPSUSR.ICPS_WBC_TM_AUTH_HST.ORIG_TXN_TYPE is
'ԭ��������';

comment on column GAPSUSR.ICPS_WBC_TM_AUTH_HST.ORIG_FWD_INST_ID is
'ԭʼת��������';

comment on column GAPSUSR.ICPS_WBC_TM_AUTH_HST.ORIG_ACQ_INST_ID is
'ԭʼ���������';

comment on column GAPSUSR.ICPS_WBC_TM_AUTH_HST.ORIG_MTI is
'ԭ����MTI';

comment on column GAPSUSR.ICPS_WBC_TM_AUTH_HST.ORIG_TRANS_DATE is
'ԭʼ��������';

comment on column GAPSUSR.ICPS_WBC_TM_AUTH_HST.ORIG_TRACE_NO is
'ԭʼϵͳ���ٺ�';

comment on column GAPSUSR.ICPS_WBC_TM_AUTH_HST.ORIG_TXN_PROC is
'ԭ���״�����';

comment on column GAPSUSR.ICPS_WBC_TM_AUTH_HST.ORIG_TXN_AMT is
'ԭʼ���ױ��ֽ��';

comment on column GAPSUSR.ICPS_WBC_TM_AUTH_HST.ORIG_LOG_KV is
'ԭ����LOG��ֵ';

comment on column GAPSUSR.ICPS_WBC_TM_AUTH_HST.ORIG_TXN_VAL_1 is
'ԭ���׼�ֵ1';

comment on column GAPSUSR.ICPS_WBC_TM_AUTH_HST.ORIG_TXN_VAL_2 is
'ԭ���׼�ֵ2';

comment on column GAPSUSR.ICPS_WBC_TM_AUTH_HST.ORIG_CHB_TXN_AMT is
'ԭʼ���˱��ֽ��';

comment on column GAPSUSR.ICPS_WBC_TM_AUTH_HST.ORIG_BIZ_DATE is
'ԭ���׵�����ҵ��������';

comment on column GAPSUSR.ICPS_WBC_TM_AUTH_HST.LAST_REVERSAL_DATE is
'���һ�γ峷ʱ��';

comment on column GAPSUSR.ICPS_WBC_TM_AUTH_HST.VOID_COUNT is
'��������';

comment on column GAPSUSR.ICPS_WBC_TM_AUTH_HST.MANUAL_AUTH_FLAG is
'�˹���Ȩ��־';

comment on column GAPSUSR.ICPS_WBC_TM_AUTH_HST.OPERA_ID is
'����ԱID';

comment on column GAPSUSR.ICPS_WBC_TM_AUTH_HST.BRAND is
'Ʒ��';

comment on column GAPSUSR.ICPS_WBC_TM_AUTH_HST.PRODUCT_CD is
'��Ʒ����';

comment on column GAPSUSR.ICPS_WBC_TM_AUTH_HST.MCC_TYPE is
'�̻����ͷ���';

comment on column GAPSUSR.ICPS_WBC_TM_AUTH_HST.FINAL_REASON is
'��Ȩԭ��';

comment on column GAPSUSR.ICPS_WBC_TM_AUTH_HST.FINAL_ACTION is
'�����ж�';

comment on column GAPSUSR.ICPS_WBC_TM_AUTH_HST.COMP_AMT is
'������Ȩ���';

comment on column GAPSUSR.ICPS_WBC_TM_AUTH_HST.FINAL_UPD_DIRECTION is
'���ո��·���';

comment on column GAPSUSR.ICPS_WBC_TM_AUTH_HST.FINAL_UPD_AMT is
'���ո��½��';

comment on column GAPSUSR.ICPS_WBC_TM_AUTH_HST.IC_IND is
'�Ƿ�IC��';

comment on column GAPSUSR.ICPS_WBC_TM_AUTH_HST.THE_3DSECURE_TYPE is
'�Ƿ�3D���Ӱ�ȫ����';

comment on column GAPSUSR.ICPS_WBC_TM_AUTH_HST.VIP_STATUS is
'VIP״̬';

comment on column GAPSUSR.ICPS_WBC_TM_AUTH_HST.CURR_BAL is
'��ǰ���';

comment on column GAPSUSR.ICPS_WBC_TM_AUTH_HST.CASH_AMT is
'ȡ�ֽ��';

comment on column GAPSUSR.ICPS_WBC_TM_AUTH_HST.OTB is
'���ö��';

comment on column GAPSUSR.ICPS_WBC_TM_AUTH_HST.CASH_OTB is
'ȡ�ֿ��ö��';

comment on column GAPSUSR.ICPS_WBC_TM_AUTH_HST.CUST_OTB is
'�ͻ����ö��';

comment on column GAPSUSR.ICPS_WBC_TM_AUTH_HST.CARD_BLACK_FLAG is
'�Ƿ��˻�������';

comment on column GAPSUSR.ICPS_WBC_TM_AUTH_HST.MERCHANT_BLACK_FLAG is
'�Ƿ��̻�������';

comment on column GAPSUSR.ICPS_WBC_TM_AUTH_HST.EXPIRE_DATE is
'��Ч����';

comment on column GAPSUSR.ICPS_WBC_TM_AUTH_HST.TRACK_ONE_RESULT is
'һ�ŵ������Խ��';

comment on column GAPSUSR.ICPS_WBC_TM_AUTH_HST.TRACK_TWO_RESULT is
'���ŵ������Խ��';

comment on column GAPSUSR.ICPS_WBC_TM_AUTH_HST.TRACK_THREE_RESULT is
'���ŵ������Խ��';

comment on column GAPSUSR.ICPS_WBC_TM_AUTH_HST.PWD_TYPE is
'��������';

comment on column GAPSUSR.ICPS_WBC_TM_AUTH_HST.CHECK_PWD_RESULT is
'��֤������';

comment on column GAPSUSR.ICPS_WBC_TM_AUTH_HST.PAY_PWD_ERR_NUM is
'֧������������';

comment on column GAPSUSR.ICPS_WBC_TM_AUTH_HST.CHECK_CVV_RESULT is
'CVV��֤���';

comment on column GAPSUSR.ICPS_WBC_TM_AUTH_HST.CHECK_CVV2_RESULT is
'CVV2��֤���';

comment on column GAPSUSR.ICPS_WBC_TM_AUTH_HST.CHECK_ICVN_RESULT is
'ICVN��֤���';

comment on column GAPSUSR.ICPS_WBC_TM_AUTH_HST.CHECK_ARQC_RESULT is
'ARQC��֤���';

comment on column GAPSUSR.ICPS_WBC_TM_AUTH_HST.CHECK_ATC_RESULT is
'ATC��֤���';

comment on column GAPSUSR.ICPS_WBC_TM_AUTH_HST.CHECK_CVR_RESULT is
'CVR��֤���';

comment on column GAPSUSR.ICPS_WBC_TM_AUTH_HST.CHECK_TVR_RESULT is
'TVR��֤���';

comment on column GAPSUSR.ICPS_WBC_TM_AUTH_HST.REJ_REASON is
'�ܾ�ԭ��';

comment on column GAPSUSR.ICPS_WBC_TM_AUTH_HST.UNMATCH_CR is
'δƥ����ǽ��';

comment on column GAPSUSR.ICPS_WBC_TM_AUTH_HST.UNMATCH_DB is
'δƥ���ǽ��';

comment on column GAPSUSR.ICPS_WBC_TM_AUTH_HST.B002 is
'���ʿ���-B002';

comment on column GAPSUSR.ICPS_WBC_TM_AUTH_HST.B003 is
'���״�����-B003';

comment on column GAPSUSR.ICPS_WBC_TM_AUTH_HST.B007 is
'���״���ʱ��-B007';

comment on column GAPSUSR.ICPS_WBC_TM_AUTH_HST.B011 is
'ϵͳ���ٺ�-B011';

comment on column GAPSUSR.ICPS_WBC_TM_AUTH_HST.B022 is
'�����PIN��ȡ��-B022';

comment on column GAPSUSR.ICPS_WBC_TM_AUTH_HST.B025 is
'�����������-B025';

comment on column GAPSUSR.ICPS_WBC_TM_AUTH_HST.B032 is
'���������ʶ��-B032';

comment on column GAPSUSR.ICPS_WBC_TM_AUTH_HST.B033 is
'����������Ƶ�ַ-B033';

comment on column GAPSUSR.ICPS_WBC_TM_AUTH_HST.B039 is
'������-B039';

comment on column GAPSUSR.ICPS_WBC_TM_AUTH_HST.B042 is
'�ܿ���(�̻�)��ʶ��-B042';

comment on column GAPSUSR.ICPS_WBC_TM_AUTH_HST.B060 is
'�Զ�����-B060';

comment on column GAPSUSR.ICPS_WBC_TM_AUTH_HST.B061 is
'�ֿ��������֤��Ϣ-B061';

comment on column GAPSUSR.ICPS_WBC_TM_AUTH_HST.B090 is
'ԭʼ����Ԫ';

comment on column GAPSUSR.ICPS_WBC_TM_AUTH_HST.OPERA_TERM_ID is
'�����û��ն˱��';

comment on column GAPSUSR.ICPS_WBC_TM_AUTH_HST.JPA_VERSION is
'�ֹ����汾��';

comment on column GAPSUSR.ICPS_WBC_TM_AUTH_HST.B004 is
'���׻��ҽ��-B004';

comment on column GAPSUSR.ICPS_WBC_TM_AUTH_HST.B006 is
'�˻����ҽ��-B006';

comment on column GAPSUSR.ICPS_WBC_TM_AUTH_HST.B049 is
'���׻��Ҵ���-B049';

comment on column GAPSUSR.ICPS_WBC_TM_AUTH_HST.B051 is
'�˻����Ҵ���-B051';

comment on column GAPSUSR.ICPS_WBC_TM_AUTH_HST.B037 is
'�����ο���-B037';

comment on column GAPSUSR.ICPS_WBC_TM_AUTH_HST.B028 is
'������-B028';

comment on column GAPSUSR.ICPS_WBC_TM_AUTH_HST.B048 is
'��������-B048';

comment on column GAPSUSR.ICPS_WBC_TM_AUTH_HST.B054 is
'�����������-B054';

comment on column GAPSUSR.ICPS_WBC_TM_AUTH_HST.CARD_BLOCK_CODE is
'��Ƭ������';

comment on column GAPSUSR.ICPS_WBC_TM_AUTH_HST.ACCOUNT_BLOCK_CODE is
'�ʻ�������';

comment on column GAPSUSR.ICPS_WBC_TM_AUTH_HST.MEDIUM_BLOCK_CODE is
'����������';

comment on column GAPSUSR.ICPS_WBC_TM_AUTH_HST.CONSUMER_TRANS_ID is
'ҵ����ˮ��';

comment on column GAPSUSR.ICPS_WBC_TM_AUTH_HST.SYS_TRANS_ID is
'ϵͳ������ˮ��';

comment on column GAPSUSR.ICPS_WBC_TM_AUTH_HST.QCHANNEL_ID is
'�������';

comment on column GAPSUSR.ICPS_WBC_TM_AUTH_HST.SUB_TERMINAL_TYPE is
'�ն�����';

comment on column GAPSUSR.ICPS_WBC_TM_AUTH_HST.SUB_MERCH_ID is
'�����̻�����';

comment on column GAPSUSR.ICPS_WBC_TM_AUTH_HST.SUB_MERCH_NAME is
'�����̻�����';

comment on column GAPSUSR.ICPS_WBC_TM_AUTH_HST.WARES_DESC is
'��Ʒ��Ϣ';

comment on column GAPSUSR.ICPS_WBC_TM_AUTH_HST.LAST_MODIFIED_DATETIME is
'�޸�ʱ��';

comment on column GAPSUSR.ICPS_WBC_TM_AUTH_HST.PART_MONTH is
'�����õ��·�';

comment on column GAPSUSR.ICPS_WBC_TM_AUTH_HST.PAID_STMT_DATE is
'�����˵���';

comment on column GAPSUSR.ICPS_WBC_TM_AUTH_HST.REPAY_AMT is
'Ӧ�����';

comment on column GAPSUSR.ICPS_WBC_TM_AUTH_HST.TRANSFER_TYPE is
'ת������';

comment on column GAPSUSR.ICPS_WBC_TM_AUTH_HST.IS_CHECK_FLAG is
'������˱�ʶ';

comment on column GAPSUSR.ICPS_WBC_TM_AUTH_HST.EXTEND_PARAM1 is
'��չ1';

comment on column GAPSUSR.ICPS_WBC_TM_AUTH_HST.EXTEND_PARAM2 is
'��չ2';

comment on column GAPSUSR.ICPS_WBC_TM_AUTH_HST.EXTEND_PARAM3 is
'��չ3';

--==============================================================
-- Table: ICPS_WBC_TM_BANK
--==============================================================
create table GAPSUSR.ICPS_WBC_TM_BANK
(
   BUSI_DATE            CHARACTER(8)           not null,
   FILE_ORDER           INTEGER                not null,
   BANK_NO              VARCHAR(10),
   BANK_NAME            VARCHAR(40),
   PAYING_ACCT          VARCHAR(100),
   IS_CHECK_FLAG        CHARACTER,
   EXTEND_PARAM1        VARCHAR(100),
   EXTEND_PARAM2        VARCHAR(250),
   EXTEND_PARAM3        VARCHAR(40),
   constraint PK_ICPS_WBC_TM_BANK primary key (BUSI_DATE, FILE_ORDER)
)  IN GAPS_DATA INDEX IN GAPS_INDEX ;

comment on table GAPSUSR.ICPS_WBC_TM_BANK is
'���б�';

comment on column GAPSUSR.ICPS_WBC_TM_BANK.BUSI_DATE is
'ҵ������';

comment on column GAPSUSR.ICPS_WBC_TM_BANK.FILE_ORDER is
'�ļ����';

comment on column GAPSUSR.ICPS_WBC_TM_BANK.BANK_NO is
'���к�';

comment on column GAPSUSR.ICPS_WBC_TM_BANK.BANK_NAME is
'��������';

comment on column GAPSUSR.ICPS_WBC_TM_BANK.PAYING_ACCT is
'�������˻���';

comment on column GAPSUSR.ICPS_WBC_TM_BANK.IS_CHECK_FLAG is
'������˱�ʶ';

comment on column GAPSUSR.ICPS_WBC_TM_BANK.EXTEND_PARAM1 is
'��չ1';

comment on column GAPSUSR.ICPS_WBC_TM_BANK.EXTEND_PARAM2 is
'��չ2';

comment on column GAPSUSR.ICPS_WBC_TM_BANK.EXTEND_PARAM3 is
'��չ3';

--==============================================================
-- Table: ICPS_WBC_TM_BANK_CREDIT_RESULT
--==============================================================
create table GAPSUSR.ICPS_WBC_TM_BANK_CREDIT_RESULT
(
   BUSI_DATE            CHARACTER(8)           not null,
   FILE_ORDER           INTEGER                not null,
   SEQ_NO               VARCHAR(32),
   BANK_NO              VARCHAR(20),
   BANK_NAME            VARCHAR(80),
   ID_NO                VARCHAR(30),
   ID_TYPE              VARCHAR(2),
   "NAME"               VARCHAR(80),
   NBS_ORDER_NO         VARCHAR(32),
   CREDIT_INFO          VARCHAR(1024),
   RULE_ACTION_TYPE     VARCHAR(2),
   RULE_CODE            VARCHAR(50),
   RUILE_DESC           VARCHAR(500),
   IS_BL_REJ            VARCHAR(2),
   BL_REJ_CODE          VARCHAR(50),
   BL_REJ_DESC          VARCHAR(500),
   CREDIT_DATETIME      VARCHAR(14),
   RESULT_CODE          VARCHAR(9),
   RESULT_DESC          VARCHAR(100),
   CREATED_DATETIME     VARCHAR(14),
   LAST_MODIFIED_DATETIME VARCHAR(14),
   IS_CHECK_FLAG        CHARACTER,
   EXTEND_PARAM1        VARCHAR(100),
   EXTEND_PARAM2        VARCHAR(250),
   EXTEND_PARAM3        VARCHAR(40),
   constraint PK_ICPS_WBC_TM_BANK_CREDIT_RESULT primary key (BUSI_DATE, FILE_ORDER)
)  IN GAPS_DATA INDEX IN GAPS_INDEX ;

comment on table GAPSUSR.ICPS_WBC_TM_BANK_CREDIT_RESULT is
'���о��߽����';

comment on column GAPSUSR.ICPS_WBC_TM_BANK_CREDIT_RESULT.BUSI_DATE is
'ҵ������';

comment on column GAPSUSR.ICPS_WBC_TM_BANK_CREDIT_RESULT.FILE_ORDER is
'�ļ����';

comment on column GAPSUSR.ICPS_WBC_TM_BANK_CREDIT_RESULT.SEQ_NO is
'������ˮ';

comment on column GAPSUSR.ICPS_WBC_TM_BANK_CREDIT_RESULT.BANK_NO is
'���б��';

comment on column GAPSUSR.ICPS_WBC_TM_BANK_CREDIT_RESULT.BANK_NAME is
'������';

comment on column GAPSUSR.ICPS_WBC_TM_BANK_CREDIT_RESULT.ID_NO is
'֤����';

comment on column GAPSUSR.ICPS_WBC_TM_BANK_CREDIT_RESULT.ID_TYPE is
'֤������';

comment on column GAPSUSR.ICPS_WBC_TM_BANK_CREDIT_RESULT."NAME" is
'����';

comment on column GAPSUSR.ICPS_WBC_TM_BANK_CREDIT_RESULT.NBS_ORDER_NO is
'������';

comment on column GAPSUSR.ICPS_WBC_TM_BANK_CREDIT_RESULT.CREDIT_INFO is
'������Ϣ';

comment on column GAPSUSR.ICPS_WBC_TM_BANK_CREDIT_RESULT.RULE_ACTION_TYPE is
'���Ź�������״̬';

comment on column GAPSUSR.ICPS_WBC_TM_BANK_CREDIT_RESULT.RULE_CODE is
'���Ź������ܾ���';

comment on column GAPSUSR.ICPS_WBC_TM_BANK_CREDIT_RESULT.RUILE_DESC is
'���������߾ܾ�����';

comment on column GAPSUSR.ICPS_WBC_TM_BANK_CREDIT_RESULT.IS_BL_REJ is
'����������״̬';

comment on column GAPSUSR.ICPS_WBC_TM_BANK_CREDIT_RESULT.BL_REJ_CODE is
'�������ܾ�����';

comment on column GAPSUSR.ICPS_WBC_TM_BANK_CREDIT_RESULT.BL_REJ_DESC is
'�������ܾ�����';

comment on column GAPSUSR.ICPS_WBC_TM_BANK_CREDIT_RESULT.CREDIT_DATETIME is
'�����ж�ʱ��';

comment on column GAPSUSR.ICPS_WBC_TM_BANK_CREDIT_RESULT.RESULT_CODE is
'���߽��';

comment on column GAPSUSR.ICPS_WBC_TM_BANK_CREDIT_RESULT.RESULT_DESC is
'���߽������';

comment on column GAPSUSR.ICPS_WBC_TM_BANK_CREDIT_RESULT.CREATED_DATETIME is
'����ʱ��';

comment on column GAPSUSR.ICPS_WBC_TM_BANK_CREDIT_RESULT.LAST_MODIFIED_DATETIME is
'����ʱ��';

comment on column GAPSUSR.ICPS_WBC_TM_BANK_CREDIT_RESULT.IS_CHECK_FLAG is
'������˱�ʶ';

comment on column GAPSUSR.ICPS_WBC_TM_BANK_CREDIT_RESULT.EXTEND_PARAM1 is
'��չ1';

comment on column GAPSUSR.ICPS_WBC_TM_BANK_CREDIT_RESULT.EXTEND_PARAM2 is
'��չ2';

comment on column GAPSUSR.ICPS_WBC_TM_BANK_CREDIT_RESULT.EXTEND_PARAM3 is
'��չ3';

--==============================================================
-- Table: ICPS_WBC_TM_BANK_GROUP_MEMBER
--==============================================================
create table GAPSUSR.ICPS_WBC_TM_BANK_GROUP_MEMBER
(
   BUSI_DATE            CHARACTER(8)           not null,
   FILE_ORDER           INTEGER                not null,
   MEMBER_ID            VARCHAR(20),
   BANK_GROUP_ID        VARCHAR(5),
   BANK_NO              VARCHAR(10),
   BANK_PROPORTION      DECIMAL(5,2),
   PRODUCT_CATEGORY     VARCHAR(6),
   PRIORITY             INTEGER,
   IS_CHECK_FLAG        CHARACTER,
   EXTEND_PARAM1        VARCHAR(100),
   EXTEND_PARAM2        VARCHAR(250),
   EXTEND_PARAM3        VARCHAR(40),
   constraint PK_ICPS_WBC_TM_BANK_GROUP_MEMBER primary key (BUSI_DATE, FILE_ORDER)
)  IN GAPS_DATA INDEX IN GAPS_INDEX ;

comment on table GAPSUSR.ICPS_WBC_TM_BANK_GROUP_MEMBER is
'���ų�Ա��';

comment on column GAPSUSR.ICPS_WBC_TM_BANK_GROUP_MEMBER.BUSI_DATE is
'ҵ������';

comment on column GAPSUSR.ICPS_WBC_TM_BANK_GROUP_MEMBER.FILE_ORDER is
'�ļ����';

comment on column GAPSUSR.ICPS_WBC_TM_BANK_GROUP_MEMBER.MEMBER_ID is
'˳���';

comment on column GAPSUSR.ICPS_WBC_TM_BANK_GROUP_MEMBER.BANK_GROUP_ID is
'���ű��';

comment on column GAPSUSR.ICPS_WBC_TM_BANK_GROUP_MEMBER.BANK_NO is
'���к�';

comment on column GAPSUSR.ICPS_WBC_TM_BANK_GROUP_MEMBER.BANK_PROPORTION is
'���г��ʱ���';

comment on column GAPSUSR.ICPS_WBC_TM_BANK_GROUP_MEMBER.PRODUCT_CATEGORY is
'��Ʒ����';

comment on column GAPSUSR.ICPS_WBC_TM_BANK_GROUP_MEMBER.PRIORITY is
'�������ȼ�';

comment on column GAPSUSR.ICPS_WBC_TM_BANK_GROUP_MEMBER.IS_CHECK_FLAG is
'������˱�ʶ';

comment on column GAPSUSR.ICPS_WBC_TM_BANK_GROUP_MEMBER.EXTEND_PARAM1 is
'��չ1';

comment on column GAPSUSR.ICPS_WBC_TM_BANK_GROUP_MEMBER.EXTEND_PARAM2 is
'��չ2';

comment on column GAPSUSR.ICPS_WBC_TM_BANK_GROUP_MEMBER.EXTEND_PARAM3 is
'��չ3';

--==============================================================
-- Table: ICPS_WBC_TM_CUSTOMER
--==============================================================
create table GAPSUSR.ICPS_WBC_TM_CUSTOMER
(
   BUSI_DATE            CHARACTER(8)           not null,
   FILE_ORDER           INTEGER                not null,
   ORG                  CHARACTER(12),
   CUST_ID              VARCHAR(20),
   ID_NO                VARCHAR(30),
   ID_TYPE              CHARACTER,
   TITLE                CHARACTER,
   "NAME"               VARCHAR(80),
   GENDER               CHARACTER,
   BIRTHDAY             VARCHAR(8),
   OCCUPATION           CHARACTER,
   BANKMEMBER_NO        VARCHAR(20),
   NATIONALITY          CHARACTER(3),
   PR_OF_COUNTRY        CHARACTER,
   RESIDENCY_COUNTRY_CD CHARACTER(3),
   MARITAL_STATUS       CHARACTER,
   QUALIFICATION        CHARACTER,
   SOCIAL_STATUS        CHARACTER,
   ID_ISSUER_ADDRESS    VARCHAR(200),
   HOME_PHONE           VARCHAR(20),
   HOUSE_OWNERSHIP      CHARACTER,
   HOUSE_TYPE           CHARACTER,
   HOME_STAND_FROM      VARCHAR(8),
   LIQUID_ASSET         CHARACTER,
   MOBILE_NO            VARCHAR(20),
   EMAIL                VARCHAR(80),
   EMP_STATUS           CHARACTER,
   NBR_OF_DEPENDENTS    INTEGER,
   LANGUAGE_IND         VARCHAR(4),
   SETUP_DATE           VARCHAR(8),
   SOCIAL_INS_AMT       DECIMAL(15,2),
   DRIVE_LICENSE_ID     VARCHAR(20),
   DRIVE_LIC_REG_DATE   VARCHAR(8),
   OBLIGATE_QUESTION    VARCHAR(80),
   OBLIGATE_ANSWER      VARCHAR(80),
   EMP_STABILITY        CHARACTER,
   CORP_NAME            VARCHAR(200),
   USER_CODE1           VARCHAR(4),
   USER_CODE2           VARCHAR(4),
   USER_CODE3           VARCHAR(4),
   USER_CODE4           VARCHAR(4),
   USER_CODE5           VARCHAR(4),
   USER_CODE6           VARCHAR(4),
   USER_DATE1           VARCHAR(8),
   USER_DATE2           VARCHAR(8),
   USER_DATE3           VARCHAR(8),
   USER_DATE4           VARCHAR(8),
   USER_DATE5           VARCHAR(8),
   USER_DATE6           VARCHAR(8),
   USER_NUMBER1         INTEGER,
   USER_NUMBER2         INTEGER,
   USER_NUMBER3         INTEGER,
   USER_NUMBER4         INTEGER,
   USER_NUMBER5         INTEGER,
   USER_NUMBER6         INTEGER,
   USER_FIELD1          VARCHAR(40),
   USER_FIELD2          VARCHAR(40),
   USER_FIELD3          VARCHAR(40),
   USER_FIELD4          VARCHAR(40),
   USER_FIELD5          VARCHAR(40),
   USER_FIELD6          VARCHAR(40),
   USER_AMT1            DECIMAL(15,2),
   USER_AMT2            DECIMAL(15,2),
   USER_AMT3            DECIMAL(15,2),
   USER_AMT4            DECIMAL(15,2),
   USER_AMT5            DECIMAL(15,2),
   USER_AMT6            DECIMAL(15,2),
   BANK_CUSTOMER_ID     VARCHAR(20),
   EMB_NAME             VARCHAR(26),
   JPA_VERSION          INTEGER,
   CUST_LIMIT_ID        VARCHAR(20),
   LAST_MODIFIED_DATETIME VARCHAR(14),
   CUST_LEVEL           VARCHAR(10),
   PLEDEG_TYPE          VARCHAR(2),
   SURNAME              VARCHAR(20),
   CREATED_DATETIME     VARCHAR(14),
   CUSTOMER_TYPE        VARCHAR(3),
   BLOCK_CODE           CHARACTER(53),
   IS_CHECK_FLAG        CHARACTER,
   EXTEND_PARAM1        VARCHAR(100),
   EXTEND_PARAM2        VARCHAR(250),
   EXTEND_PARAM3        VARCHAR(40),
   constraint PK_ICPS_WBC_TM_CUSTOMER primary key (BUSI_DATE, FILE_ORDER)
)  IN GAPS_DATA INDEX IN GAPS_INDEX ;

comment on table GAPSUSR.ICPS_WBC_TM_CUSTOMER is
'�ͻ���Ϣ��';

comment on column GAPSUSR.ICPS_WBC_TM_CUSTOMER.BUSI_DATE is
'ҵ������';

comment on column GAPSUSR.ICPS_WBC_TM_CUSTOMER.FILE_ORDER is
'�ļ����';

comment on column GAPSUSR.ICPS_WBC_TM_CUSTOMER.ORG is
'������';

comment on column GAPSUSR.ICPS_WBC_TM_CUSTOMER.CUST_ID is
'�ͻ����';

comment on column GAPSUSR.ICPS_WBC_TM_CUSTOMER.ID_NO is
'֤������';

comment on column GAPSUSR.ICPS_WBC_TM_CUSTOMER.ID_TYPE is
'֤������';

comment on column GAPSUSR.ICPS_WBC_TM_CUSTOMER.TITLE is
'��ν';

comment on column GAPSUSR.ICPS_WBC_TM_CUSTOMER."NAME" is
'����';

comment on column GAPSUSR.ICPS_WBC_TM_CUSTOMER.GENDER is
'�Ա�';

comment on column GAPSUSR.ICPS_WBC_TM_CUSTOMER.BIRTHDAY is
'����';

comment on column GAPSUSR.ICPS_WBC_TM_CUSTOMER.OCCUPATION is
'ְҵ';

comment on column GAPSUSR.ICPS_WBC_TM_CUSTOMER.BANKMEMBER_NO is
'����Ա����';

comment on column GAPSUSR.ICPS_WBC_TM_CUSTOMER.NATIONALITY is
'����';

comment on column GAPSUSR.ICPS_WBC_TM_CUSTOMER.PR_OF_COUNTRY is
'�Ƿ����þ�ס';

comment on column GAPSUSR.ICPS_WBC_TM_CUSTOMER.RESIDENCY_COUNTRY_CD is
'���þ�ס�ع��Ҵ���';

comment on column GAPSUSR.ICPS_WBC_TM_CUSTOMER.MARITAL_STATUS is
'����״��';

comment on column GAPSUSR.ICPS_WBC_TM_CUSTOMER.QUALIFICATION is
'����״��';

comment on column GAPSUSR.ICPS_WBC_TM_CUSTOMER.SOCIAL_STATUS is
'�������';

comment on column GAPSUSR.ICPS_WBC_TM_CUSTOMER.ID_ISSUER_ADDRESS is
'��֤�������ڵ�ַ';

comment on column GAPSUSR.ICPS_WBC_TM_CUSTOMER.HOME_PHONE is
'��ͥ�绰';

comment on column GAPSUSR.ICPS_WBC_TM_CUSTOMER.HOUSE_OWNERSHIP is
'���ݳ�������';

comment on column GAPSUSR.ICPS_WBC_TM_CUSTOMER.HOUSE_TYPE is
'סլ����';

comment on column GAPSUSR.ICPS_WBC_TM_CUSTOMER.HOME_STAND_FROM is
'��סַ��ס��ʼ����';

comment on column GAPSUSR.ICPS_WBC_TM_CUSTOMER.LIQUID_ASSET is
'�����ʲ�����';

comment on column GAPSUSR.ICPS_WBC_TM_CUSTOMER.MOBILE_NO is
'�ƶ��绰';

comment on column GAPSUSR.ICPS_WBC_TM_CUSTOMER.EMAIL is
'��������';

comment on column GAPSUSR.ICPS_WBC_TM_CUSTOMER.EMP_STATUS is
'��ҵ״̬';

comment on column GAPSUSR.ICPS_WBC_TM_CUSTOMER.NBR_OF_DEPENDENTS is
'��������';

comment on column GAPSUSR.ICPS_WBC_TM_CUSTOMER.LANGUAGE_IND is
'���Դ���';

comment on column GAPSUSR.ICPS_WBC_TM_CUSTOMER.SETUP_DATE is
'��������';

comment on column GAPSUSR.ICPS_WBC_TM_CUSTOMER.SOCIAL_INS_AMT is
'�籣�ɴ���';

comment on column GAPSUSR.ICPS_WBC_TM_CUSTOMER.DRIVE_LICENSE_ID is
'��ʻ֤����';

comment on column GAPSUSR.ICPS_WBC_TM_CUSTOMER.DRIVE_LIC_REG_DATE is
'��ʻ֤�Ǽ�����';

comment on column GAPSUSR.ICPS_WBC_TM_CUSTOMER.OBLIGATE_QUESTION is
'Ԥ������';

comment on column GAPSUSR.ICPS_WBC_TM_CUSTOMER.OBLIGATE_ANSWER is
'Ԥ����';

comment on column GAPSUSR.ICPS_WBC_TM_CUSTOMER.EMP_STABILITY is
'�����ȶ���';

comment on column GAPSUSR.ICPS_WBC_TM_CUSTOMER.CORP_NAME is
'��˾����';

comment on column GAPSUSR.ICPS_WBC_TM_CUSTOMER.USER_CODE1 is
'�û��Զ������1';

comment on column GAPSUSR.ICPS_WBC_TM_CUSTOMER.USER_CODE2 is
'�û��Զ������2';

comment on column GAPSUSR.ICPS_WBC_TM_CUSTOMER.USER_CODE3 is
'�û��Զ������3';

comment on column GAPSUSR.ICPS_WBC_TM_CUSTOMER.USER_CODE4 is
'�û��Զ������4';

comment on column GAPSUSR.ICPS_WBC_TM_CUSTOMER.USER_CODE5 is
'�û��Զ������5';

comment on column GAPSUSR.ICPS_WBC_TM_CUSTOMER.USER_CODE6 is
'�û��Զ������6';

comment on column GAPSUSR.ICPS_WBC_TM_CUSTOMER.USER_DATE1 is
'�û��Զ�������1';

comment on column GAPSUSR.ICPS_WBC_TM_CUSTOMER.USER_DATE2 is
'�û��Զ�������2';

comment on column GAPSUSR.ICPS_WBC_TM_CUSTOMER.USER_DATE3 is
'�û��Զ�������3';

comment on column GAPSUSR.ICPS_WBC_TM_CUSTOMER.USER_DATE4 is
'�û��Զ�������4';

comment on column GAPSUSR.ICPS_WBC_TM_CUSTOMER.USER_DATE5 is
'�û��Զ�������5';

comment on column GAPSUSR.ICPS_WBC_TM_CUSTOMER.USER_DATE6 is
'�û��Զ�������6';

comment on column GAPSUSR.ICPS_WBC_TM_CUSTOMER.USER_NUMBER1 is
'�û��Զ������1';

comment on column GAPSUSR.ICPS_WBC_TM_CUSTOMER.USER_NUMBER2 is
'�û��Զ������2';

comment on column GAPSUSR.ICPS_WBC_TM_CUSTOMER.USER_NUMBER3 is
'�û��Զ������3';

comment on column GAPSUSR.ICPS_WBC_TM_CUSTOMER.USER_NUMBER4 is
'�û��Զ������4';

comment on column GAPSUSR.ICPS_WBC_TM_CUSTOMER.USER_NUMBER5 is
'�û��Զ������5';

comment on column GAPSUSR.ICPS_WBC_TM_CUSTOMER.USER_NUMBER6 is
'�û��Զ������6';

comment on column GAPSUSR.ICPS_WBC_TM_CUSTOMER.USER_FIELD1 is
'�û��Զ�����1';

comment on column GAPSUSR.ICPS_WBC_TM_CUSTOMER.USER_FIELD2 is
'�û��Զ�����2';

comment on column GAPSUSR.ICPS_WBC_TM_CUSTOMER.USER_FIELD3 is
'�û��Զ�����3';

comment on column GAPSUSR.ICPS_WBC_TM_CUSTOMER.USER_FIELD4 is
'�û��Զ�����4';

comment on column GAPSUSR.ICPS_WBC_TM_CUSTOMER.USER_FIELD5 is
'�û��Զ�����5';

comment on column GAPSUSR.ICPS_WBC_TM_CUSTOMER.USER_FIELD6 is
'�û��Զ�����6';

comment on column GAPSUSR.ICPS_WBC_TM_CUSTOMER.USER_AMT1 is
'�û��Զ�����1';

comment on column GAPSUSR.ICPS_WBC_TM_CUSTOMER.USER_AMT2 is
'�û��Զ�����2';

comment on column GAPSUSR.ICPS_WBC_TM_CUSTOMER.USER_AMT3 is
'�û��Զ�����3';

comment on column GAPSUSR.ICPS_WBC_TM_CUSTOMER.USER_AMT4 is
'�û��Զ�����4';

comment on column GAPSUSR.ICPS_WBC_TM_CUSTOMER.USER_AMT5 is
'�û��Զ�����5';

comment on column GAPSUSR.ICPS_WBC_TM_CUSTOMER.USER_AMT6 is
'���մ��ǿ���ŵ���';

comment on column GAPSUSR.ICPS_WBC_TM_CUSTOMER.BANK_CUSTOMER_ID is
'����ͳһ�û���';

comment on column GAPSUSR.ICPS_WBC_TM_CUSTOMER.EMB_NAME is
'͹ӡ����';

comment on column GAPSUSR.ICPS_WBC_TM_CUSTOMER.JPA_VERSION is
'�ֹ����汾��';

comment on column GAPSUSR.ICPS_WBC_TM_CUSTOMER.CUST_LIMIT_ID is
'�ͻ����ID';

comment on column GAPSUSR.ICPS_WBC_TM_CUSTOMER.LAST_MODIFIED_DATETIME is
'�޸�ʱ��';

comment on column GAPSUSR.ICPS_WBC_TM_CUSTOMER.CUST_LEVEL is
'�ͻ��ȼ�';

comment on column GAPSUSR.ICPS_WBC_TM_CUSTOMER.PLEDEG_TYPE is
'ѺƷ����';

comment on column GAPSUSR.ICPS_WBC_TM_CUSTOMER.SURNAME is
'����';

comment on column GAPSUSR.ICPS_WBC_TM_CUSTOMER.CREATED_DATETIME is
'����ʱ��';

comment on column GAPSUSR.ICPS_WBC_TM_CUSTOMER.CUSTOMER_TYPE is
'��Ⱥ����';

comment on column GAPSUSR.ICPS_WBC_TM_CUSTOMER.BLOCK_CODE is
'������';

comment on column GAPSUSR.ICPS_WBC_TM_CUSTOMER.IS_CHECK_FLAG is
'������˱�ʶ';

comment on column GAPSUSR.ICPS_WBC_TM_CUSTOMER.EXTEND_PARAM1 is
'��չ1';

comment on column GAPSUSR.ICPS_WBC_TM_CUSTOMER.EXTEND_PARAM2 is
'��չ2';

comment on column GAPSUSR.ICPS_WBC_TM_CUSTOMER.EXTEND_PARAM3 is
'��չ3';

--==============================================================
-- Table: ICPS_WBC_TM_CUST_LIMIT_O
--==============================================================
create table GAPSUSR.ICPS_WBC_TM_CUST_LIMIT_O
(
   BUSI_DATE            CHARACTER(8)           not null,
   FILE_ORDER           INTEGER                not null,
   ORG                  CHARACTER(12),
   CUST_LIMIT_ID        VARCHAR(20),
   LIMIT_CATEGORY       VARCHAR(20),
   LIMIT_TYPE           CHARACTER,
   CREDIT_LIMIT         DECIMAL(13,2),
   JPA_VERSION          INTEGER,
   LAST_MODIFIED_DATETIME VARCHAR(14),
   CREATED_DATETIME     VARCHAR(14),
   IS_CHECK_FLAG        CHARACTER,
   EXTEND_PARAM1        VARCHAR(100),
   EXTEND_PARAM2        VARCHAR(250),
   EXTEND_PARAM3        VARCHAR(40),
   constraint PK_ICPS_WBC_TM_CUST_LIMIT_O primary key (BUSI_DATE, FILE_ORDER)
)  IN GAPS_DATA INDEX IN GAPS_INDEX ;

comment on table GAPSUSR.ICPS_WBC_TM_CUST_LIMIT_O is
'�Զ�������Ϣ��-��Ȩ';

comment on column GAPSUSR.ICPS_WBC_TM_CUST_LIMIT_O.BUSI_DATE is
'ҵ������';

comment on column GAPSUSR.ICPS_WBC_TM_CUST_LIMIT_O.FILE_ORDER is
'�ļ����';

comment on column GAPSUSR.ICPS_WBC_TM_CUST_LIMIT_O.ORG is
'������';

comment on column GAPSUSR.ICPS_WBC_TM_CUST_LIMIT_O.CUST_LIMIT_ID is
'�ͻ����ID';

comment on column GAPSUSR.ICPS_WBC_TM_CUST_LIMIT_O.LIMIT_CATEGORY is
'�������';

comment on column GAPSUSR.ICPS_WBC_TM_CUST_LIMIT_O.LIMIT_TYPE is
'�������';

comment on column GAPSUSR.ICPS_WBC_TM_CUST_LIMIT_O.CREDIT_LIMIT is
'���ö��';

comment on column GAPSUSR.ICPS_WBC_TM_CUST_LIMIT_O.JPA_VERSION is
'�ֹ����汾��';

comment on column GAPSUSR.ICPS_WBC_TM_CUST_LIMIT_O.LAST_MODIFIED_DATETIME is
'�޸�ʱ��';

comment on column GAPSUSR.ICPS_WBC_TM_CUST_LIMIT_O.CREATED_DATETIME is
'����ʱ��';

comment on column GAPSUSR.ICPS_WBC_TM_CUST_LIMIT_O.IS_CHECK_FLAG is
'������˱�ʶ';

comment on column GAPSUSR.ICPS_WBC_TM_CUST_LIMIT_O.EXTEND_PARAM1 is
'��չ1';

comment on column GAPSUSR.ICPS_WBC_TM_CUST_LIMIT_O.EXTEND_PARAM2 is
'��չ2';

comment on column GAPSUSR.ICPS_WBC_TM_CUST_LIMIT_O.EXTEND_PARAM3 is
'��չ3';

--==============================================================
-- Table: ICPS_WBC_TM_GL_BAL
--==============================================================
create table GAPSUSR.ICPS_WBC_TM_GL_BAL
(
   BUSI_DATE            CHARACTER(8)           not null,
   FILE_ORDER           INTEGER                not null,
   ORG                  CHARACTER(12),
   SUBJECT              VARCHAR(40),
   BRANCH_ID            VARCHAR(9),
   DB_BAL               DECIMAL(15,2),
   CR_BAL               DECIMAL(15,2),
   DB_AMT               DECIMAL(15,2),
   DB_COUNT             INTEGER,
   CR_AMT               DECIMAL(15,2),
   CR_COUNT             INTEGER,
   LAST_DB_BAL          DECIMAL(15,2),
   LAST_CR_BAL          DECIMAL(15,2),
   LAST_MTH_DB_BAL      DECIMAL(15,2),
   LAST_MTH_CR_BAL      DECIMAL(15,2),
   LAST_QTR_DB_BAL      DECIMAL(15,2),
   LAST_QTR_CR_BAL      DECIMAL(15,2),
   LAST_YR_DB_BAL       DECIMAL(15,2),
   LAST_YR_CR_BAL       DECIMAL(15,2),
   JPA_VERSION          INTEGER,
   PRODUCT_CD           VARCHAR(6),
   BAL_ID               VARCHAR(20),
   BANK_NO              VARCHAR(10),
   BANK_GROUP_ID        VARCHAR(5),
   IS_CHECK_FLAG        CHARACTER,
   EXTEND_PARAM1        VARCHAR(100),
   EXTEND_PARAM2        VARCHAR(250),
   EXTEND_PARAM3        VARCHAR(40),
   constraint PK_ICPS_WBC_TM_GL_BAL primary key (BUSI_DATE, FILE_ORDER)
)  IN GAPS_DATA INDEX IN GAPS_INDEX ;

comment on table GAPSUSR.ICPS_WBC_TM_GL_BAL is
'���˻�ƿ�Ŀ��';

comment on column GAPSUSR.ICPS_WBC_TM_GL_BAL.BUSI_DATE is
'ҵ������';

comment on column GAPSUSR.ICPS_WBC_TM_GL_BAL.FILE_ORDER is
'�ļ����';

comment on column GAPSUSR.ICPS_WBC_TM_GL_BAL.ORG is
'������';

comment on column GAPSUSR.ICPS_WBC_TM_GL_BAL.SUBJECT is
'��Ŀ';

comment on column GAPSUSR.ICPS_WBC_TM_GL_BAL.BRANCH_ID is
'��֧�к�';

comment on column GAPSUSR.ICPS_WBC_TM_GL_BAL.DB_BAL is
'�跽���';

comment on column GAPSUSR.ICPS_WBC_TM_GL_BAL.CR_BAL is
'�������';

comment on column GAPSUSR.ICPS_WBC_TM_GL_BAL.DB_AMT is
'�跽������';

comment on column GAPSUSR.ICPS_WBC_TM_GL_BAL.DB_COUNT is
'�跽����';

comment on column GAPSUSR.ICPS_WBC_TM_GL_BAL.CR_AMT is
'����������';

comment on column GAPSUSR.ICPS_WBC_TM_GL_BAL.CR_COUNT is
'��������';

comment on column GAPSUSR.ICPS_WBC_TM_GL_BAL.LAST_DB_BAL is
'���ս跽���';

comment on column GAPSUSR.ICPS_WBC_TM_GL_BAL.LAST_CR_BAL is
'���մ������';

comment on column GAPSUSR.ICPS_WBC_TM_GL_BAL.LAST_MTH_DB_BAL is
'����ĩ�跽���';

comment on column GAPSUSR.ICPS_WBC_TM_GL_BAL.LAST_MTH_CR_BAL is
'����ĩ�������';

comment on column GAPSUSR.ICPS_WBC_TM_GL_BAL.LAST_QTR_DB_BAL is
'�ϼ�ĩ�跽���';

comment on column GAPSUSR.ICPS_WBC_TM_GL_BAL.LAST_QTR_CR_BAL is
'�ϼ�ĩ�������';

comment on column GAPSUSR.ICPS_WBC_TM_GL_BAL.LAST_YR_DB_BAL is
'����ĩ�跽���';

comment on column GAPSUSR.ICPS_WBC_TM_GL_BAL.LAST_YR_CR_BAL is
'����ĩ�������';

comment on column GAPSUSR.ICPS_WBC_TM_GL_BAL.JPA_VERSION is
'�ֹ����汾��';

comment on column GAPSUSR.ICPS_WBC_TM_GL_BAL.PRODUCT_CD is
'��Ʒ���';

comment on column GAPSUSR.ICPS_WBC_TM_GL_BAL.BAL_ID is
'˳���';

comment on column GAPSUSR.ICPS_WBC_TM_GL_BAL.BANK_NO is
'���д���';

comment on column GAPSUSR.ICPS_WBC_TM_GL_BAL.BANK_GROUP_ID is
'���Ŵ���';

comment on column GAPSUSR.ICPS_WBC_TM_GL_BAL.IS_CHECK_FLAG is
'������˱�ʶ';

comment on column GAPSUSR.ICPS_WBC_TM_GL_BAL.EXTEND_PARAM1 is
'��չ1';

comment on column GAPSUSR.ICPS_WBC_TM_GL_BAL.EXTEND_PARAM2 is
'��չ2';

comment on column GAPSUSR.ICPS_WBC_TM_GL_BAL.EXTEND_PARAM3 is
'��չ3';

--==============================================================
-- Table: ICPS_WBC_TM_LOAN
--==============================================================
create table GAPSUSR.ICPS_WBC_TM_LOAN
(
   BUSI_DATE            CHARACTER(8)           not null,
   FILE_ORDER           INTEGER                not null,
   ORG                  CHARACTER(12),
   LOAN_ID              VARCHAR(20),
   ACCT_NO              VARCHAR(20),
   ACCT_TYPE            CHARACTER,
   REF_NBR              VARCHAR(23),
   LOGICAL_CARD_NO      VARCHAR(19),
   CARD_NO              VARCHAR(19),
   REGISTER_DATE        VARCHAR(8),
   REQUEST_TIME         VARCHAR(14),
   LOAN_TYPE            VARCHAR(5),
   LOAN_STATUS          CHARACTER,
   LAST_LOAN_STATUS     CHARACTER,
   LOAN_INIT_TERM       INTEGER,
   CURR_TERM            INTEGER,
   REMAIN_TERM          INTEGER,
   LOAN_INIT_PRIN       DECIMAL(15,2),
   LOAN_FIXED_PMT_PRIN  DECIMAL(15,2),
   LOAN_FIRST_TERM_PRIN DECIMAL(15,2),
   LOAN_FINAL_TERM_PRIN DECIMAL(15,2),
   LOAN_INIT_FEE1       DECIMAL(15,2),
   LOAN_FIXED_FEE1      DECIMAL(15,2),
   LOAN_FIRST_TERM_FEE1 DECIMAL(15,2),
   LOAN_FINAL_TERM_FEE1 DECIMAL(15,2),
   UNEARNED_PRIN        DECIMAL(15,2),
   UNEARNED_FEE1        DECIMAL(15,2),
   PAID_OUT_DATE        VARCHAR(8),
   TERMINATE_DATE       VARCHAR(8),
   TERMINATE_REASON_CD  CHARACTER,
   PRIN_PAID            DECIMAL(15,2),
   INT_PAID             DECIMAL(15,2),
   FEE_PAID             DECIMAL(15,2),
   LOAN_CURR_BAL        DECIMAL(15,2),
   LOAN_BAL_XFROUT      DECIMAL(15,2),
   LOAN_BAL_XFRIN       DECIMAL(15,2),
   LOAN_BAL_PRINCIPAL   DECIMAL(15,2),
   LOAN_BAL_INTEREST    DECIMAL(15,2),
   LOAN_BAL_PENALTY     DECIMAL(15,2),
   LOAN_PRIN_XFROUT     DECIMAL(15,2),
   LOAN_PRIN_XFRIN      DECIMAL(15,2),
   LOAN_FEE1_XFROUT     DECIMAL(15,2),
   LOAN_FEE1_XFRIN      DECIMAL(15,2),
   ORIG_TXN_AMT         DECIMAL(15,2),
   ORIG_TRANS_DATE      VARCHAR(8),
   ORIG_AUTH_CODE       CHARACTER(6),
   JPA_VERSION          INTEGER,
   LOAN_CODE            VARCHAR(4),
   REGISTER_ID          VARCHAR(20),
   RESCH_INIT_PRIN      DECIMAL(15,2),
   RESCH_DATE           VARCHAR(8),
   BEF_RESCH_FIXED_PMT_PRIN DECIMAL(15,2),
   BEF_RESCH_INIT_TERM  INTEGER,
   BEF_RESCH_FIRST_TERM_PRIN DECIMAL(15,2),
   BEF_RESCH_FINAL_TERM_PRIN DECIMAL(15,2),
   BEF_RESCH_INIT_FEE1  DECIMAL(15,2),
   BEF_RESCH_FIXED_FEE1 DECIMAL(15,2),
   BEF_RESCH_FIRST_TERM_FEE1 DECIMAL(15,2),
   BEF_RESCH_FINAL_TERM_FEE1 DECIMAL(15,2),
   RESCH_FIRST_TERM_FEE1 DECIMAL(15,2),
   LOAN_FEE_METHOD      CHARACTER,
   INTEREST_RATE        DECIMAL(12,4),
   PENALTY_RATE         DECIMAL(12,4),
   COMPOUND_RATE        DECIMAL(12,4),
   FLOAT_RATE           DECIMAL(5,2),
   LOAN_RECEIPT_NBR     VARCHAR(20),
   LOAN_EXPIRE_DATE     VARCHAR(8),
   LOAN_CD              VARCHAR(2),
   PAYMENT_HIST         VARCHAR(24),
   CTD_PAYMENT_AMT      DECIMAL(15,2),
   PAST_RESCH_CNT       INTEGER,
   PAST_SHORTED_CNT     INTEGER,
   ADV_PMT_AMT          DECIMAL(15,2),
   LAST_ACTION_DATE     VARCHAR(8),
   LAST_ACTION_TYPE     CHARACTER,
   LAST_MODIFIED_DATETIME VARCHAR(14),
   ACTIVATE_DATE        VARCHAR(8),
   INTEREST_CALC_BASE   CHARACTER,
   FIRST_BILL_DATE      VARCHAR(8),
   AGE_CD               CHARACTER,
   RECALC_IND           CHARACTER,
   RECALC_DATE          VARCHAR(8),
   GRACE_DATE           VARCHAR(8),
   CANCEL_DATE          VARCHAR(8),
   CANCEL_REASON        VARCHAR(100),
   BANK_GROUP_ID        VARCHAR(5),
   DUE_DAYS             INTEGER,
   CONTRACT_VER         VARCHAR(200),
   LOAN_INIT_INTEREST   DECIMAL(15,2),
   BEF_INIT_INTEREST    DECIMAL(15,2),
   PENALTY_PAID         DECIMAL(15,2),
   COMPOUND_PAID        DECIMAL(15,2),
   LATE_CHARGE_PAID     DECIMAL(15,2),
   LOAN_BAL_LATE_CHARGE DECIMAL(15,2),
   NEXT_XFR_DATE        VARCHAR(8),
   NEXT_LATE_CHARGE_DATE VARCHAR(8),
   FEE_RATE             DECIMAL(12,7),
   LATE_CHARGE_FEE_RATE DECIMAL(12,7),
   ADV_PMT_FEE_RATE     DECIMAL(12,7),
   LOAN_BAL_ADV_PMT_FEE DECIMAL(15,2),
   ADV_PMT_FEE_PAID     DECIMAL(15,2),
   LAST_XFR_DATE        VARCHAR(8),
   LOAN_BAL_FEE         DECIMAL(15,2),
   PAYEE_CARD_NO        VARCHAR(40),
   PAYEE_BANK_NAME      VARCHAR(60),
   BILLING_CYCLE        VARCHAR(2),
   LAST_STMT_DATE       VARCHAR(8),
   NEXT_STMT_DATE       VARCHAR(8),
   IS_CHECK_FLAG        CHARACTER,
   EXTEND_PARAM1        VARCHAR(100),
   EXTEND_PARAM2        VARCHAR(250),
   EXTEND_PARAM3        VARCHAR(40),
   constraint PK_ICPS_WBC_TM_LOAN primary key (BUSI_DATE, FILE_ORDER)
)  IN GAPS_DATA INDEX IN GAPS_INDEX ;

comment on table GAPSUSR.ICPS_WBC_TM_LOAN is
'������Ϣ��';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN.BUSI_DATE is
'ҵ������';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN.FILE_ORDER is
'�ļ����';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN.ORG is
'������';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN.LOAN_ID is
'���ڼƻ�ID';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN.ACCT_NO is
'�˻����';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN.ACCT_TYPE is
'�˻�����';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN.REF_NBR is
'���ײο���';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN.LOGICAL_CARD_NO is
'�߼�����';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN.CARD_NO is
'����';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN.REGISTER_DATE is
'����ע������';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN.REQUEST_TIME is
'��������ʱ��';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN.LOAN_TYPE is
'��������';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN.LOAN_STATUS is
'����״̬';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN.LAST_LOAN_STATUS is
'�����ϴ�״̬';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN.LOAN_INIT_TERM is
'����������';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN.CURR_TERM is
'��ǰ����';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN.REMAIN_TERM is
'ʣ������';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN.LOAN_INIT_PRIN is
'�����ܱ���';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN.LOAN_FIXED_PMT_PRIN is
'����ÿ��Ӧ������';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN.LOAN_FIRST_TERM_PRIN is
'��������Ӧ������';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN.LOAN_FINAL_TERM_PRIN is
'����ĩ��Ӧ������';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN.LOAN_INIT_FEE1 is
'������������';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN.LOAN_FIXED_FEE1 is
'����ÿ��������';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN.LOAN_FIRST_TERM_FEE1 is
'��������������';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN.LOAN_FINAL_TERM_FEE1 is
'����ĩ��������';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN.UNEARNED_PRIN is
'δ���˵��ı���';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN.UNEARNED_FEE1 is
'δ���˵�������';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN.PAID_OUT_DATE is
'��������';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN.TERMINATE_DATE is
'��ǰ��ֹ����';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN.TERMINATE_REASON_CD is
'������ֹԭ�����';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN.PRIN_PAID is
'�ѳ�������';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN.INT_PAID is
'�ѳ�����Ϣ';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN.FEE_PAID is
'�ѳ�������';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN.LOAN_CURR_BAL is
'���ڵ�ǰ�����';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN.LOAN_BAL_XFROUT is
'����δ�������';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN.LOAN_BAL_XFRIN is
'�����ѳ��˵����';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN.LOAN_BAL_PRINCIPAL is
'Ƿ���ܱ���';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN.LOAN_BAL_INTEREST is
'Ƿ������Ϣ';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN.LOAN_BAL_PENALTY is
'Ƿ���ܷ�Ϣ';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN.LOAN_PRIN_XFROUT is
'����δ���ڱ���';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN.LOAN_PRIN_XFRIN is
'�����ѳ��˵�����';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN.LOAN_FEE1_XFROUT is
'����δ����������';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN.LOAN_FEE1_XFRIN is
'�����ѳ��˵�������';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN.ORIG_TXN_AMT is
'ԭʼ���ױ��ֽ��';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN.ORIG_TRANS_DATE is
'ԭʼ��������';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN.ORIG_AUTH_CODE is
'ԭʼ������Ȩ��';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN.JPA_VERSION is
'�ֹ����汾��';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN.LOAN_CODE is
'���ڼƻ�����';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN.REGISTER_ID is
'��������˳���';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN.RESCH_INIT_PRIN is
'չ�ڱ�����';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN.RESCH_DATE is
'չ����Ч����';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN.BEF_RESCH_FIXED_PMT_PRIN is
'չ��ǰÿ��Ӧ������';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN.BEF_RESCH_INIT_TERM is
'չ��ǰ������';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN.BEF_RESCH_FIRST_TERM_PRIN is
'չ��ǰ��������Ӧ������';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN.BEF_RESCH_FINAL_TERM_PRIN is
'չ��ǰ����ĩ��Ӧ������';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN.BEF_RESCH_INIT_FEE1 is
'չ��ǰ������������';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN.BEF_RESCH_FIXED_FEE1 is
'����ÿ��������';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN.BEF_RESCH_FIRST_TERM_FEE1 is
'չ��ǰ��������������';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN.BEF_RESCH_FINAL_TERM_FEE1 is
'չ��ǰ����ĩ��������';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN.RESCH_FIRST_TERM_FEE1 is
'չ�ں�����������';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN.LOAN_FEE_METHOD is
'������������ȡ��ʽ';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN.INTEREST_RATE is
'��������';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN.PENALTY_RATE is
'��Ϣ����';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN.COMPOUND_RATE is
'��������';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN.FLOAT_RATE is
'��������';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN.LOAN_RECEIPT_NBR is
'��ݺ�';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN.LOAN_EXPIRE_DATE is
'���������';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN.LOAN_CD is
'���������������';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN.PAYMENT_HIST is
'24���»���״̬';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN.CTD_PAYMENT_AMT is
'���ڻ����';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN.PAST_RESCH_CNT is
'��չ�ڴ���';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN.PAST_SHORTED_CNT is
'�����ڴ���';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN.ADV_PMT_AMT is
'��ǰ������';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN.LAST_ACTION_DATE is
'�ϴ��ж�����';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN.LAST_ACTION_TYPE is
'�ϴ��ж�����';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN.LAST_MODIFIED_DATETIME is
'�޸�ʱ��';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN.ACTIVATE_DATE is
'��������';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN.INTEREST_CALC_BASE is
'��Ϣ����';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN.FIRST_BILL_DATE is
'�׸��˵���';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN.AGE_CD is
'����';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN.RECALC_IND is
'���������־';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN.RECALC_DATE is
'����������';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN.GRACE_DATE is
'��������';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN.CANCEL_DATE is
'��������';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN.CANCEL_REASON is
'�����ԭ��';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN.BANK_GROUP_ID is
'���ű��';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN.DUE_DAYS is
'��ǰ��������';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN.CONTRACT_VER is
'��ͬ�汾��';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN.LOAN_INIT_INTEREST is
'��������Ϣ';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN.BEF_INIT_INTEREST is
'ԭ��������Ϣ';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN.PENALTY_PAID is
'�ѻ���Ϣ';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN.COMPOUND_PAID is
'�ѻ�����';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN.LATE_CHARGE_PAID is
'�ѻ����ɽ�';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN.LOAN_BAL_LATE_CHARGE is
'Ƿ�������ɽ�';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN.NEXT_XFR_DATE is
'��һ��ת��';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN.NEXT_LATE_CHARGE_DATE is
'��һ���ɽ���ȡ��';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN.FEE_RATE is
'����';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN.LATE_CHARGE_FEE_RATE is
'���ɽ����';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN.ADV_PMT_FEE_RATE is
'��ǰ���������ѷ���';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN.LOAN_BAL_ADV_PMT_FEE is
'��ǰ������������Ƿ��';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN.ADV_PMT_FEE_PAID is
'�ѻ���ǰ����������';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN.LAST_XFR_DATE is
'��һ��ת����';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN.LOAN_BAL_FEE is
'Ƿ���ܷ���';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN.PAYEE_CARD_NO is
'�տ��';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN.PAYEE_BANK_NAME is
'�տ�������';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN.BILLING_CYCLE is
'�˵���';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN.LAST_STMT_DATE is
'�ϸ��˵�����';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN.NEXT_STMT_DATE is
'�¸��˵�����';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN.IS_CHECK_FLAG is
'������˱�ʶ';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN.EXTEND_PARAM1 is
'��չ1';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN.EXTEND_PARAM2 is
'��չ2';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN.EXTEND_PARAM3 is
'��չ3';

--==============================================================
-- Table: ICPS_WBC_TM_LOAN_RECEIPT_LIST
--==============================================================
create table GAPSUSR.ICPS_WBC_TM_LOAN_RECEIPT_LIST
(
   BUSI_DATE            CHARACTER(8)           not null,
   FILE_ORDER           INTEGER                not null,
   CONSUMER_TRANS_ID    VARCHAR(32),
   SYS_TRANS_ID         VARCHAR(32),
   LOAN_RECEIPT_NBR     VARCHAR(20),
   ACCT_NO              VARCHAR(20),
   ACCT_TYPE            CHARACTER,
   CARD_NO              VARCHAR(19),
   POST_DATE            VARCHAR(8),
   LAST_MODIFIED_DATETIME VARCHAR(14),
   PAY_AMT              DECIMAL(15,2),
   BANK_GROUP_ID        VARCHAR(5),
   IS_CHECK_FLAG        CHARACTER,
   EXTEND_PARAM1        VARCHAR(100),
   EXTEND_PARAM2        VARCHAR(250),
   EXTEND_PARAM3        VARCHAR(40),
   constraint PK_ICPS_WBC_TM_LOAN_RECEIPT_LIST primary key (BUSI_DATE, FILE_ORDER)
)  IN GAPS_DATA INDEX IN GAPS_INDEX ;

comment on table GAPSUSR.ICPS_WBC_TM_LOAN_RECEIPT_LIST is
'�������嵥��';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN_RECEIPT_LIST.BUSI_DATE is
'ҵ������';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN_RECEIPT_LIST.FILE_ORDER is
'�ļ����';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN_RECEIPT_LIST.CONSUMER_TRANS_ID is
'ҵ����ˮ��';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN_RECEIPT_LIST.SYS_TRANS_ID is
'ϵͳ������ˮ��';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN_RECEIPT_LIST.LOAN_RECEIPT_NBR is
'��ݺ�';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN_RECEIPT_LIST.ACCT_NO is
'�˻����';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN_RECEIPT_LIST.ACCT_TYPE is
'�˻�����';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN_RECEIPT_LIST.CARD_NO is
'����';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN_RECEIPT_LIST.POST_DATE is
'��������';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN_RECEIPT_LIST.LAST_MODIFIED_DATETIME is
'ʱ���';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN_RECEIPT_LIST.PAY_AMT is
'������';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN_RECEIPT_LIST.BANK_GROUP_ID is
'���ű��';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN_RECEIPT_LIST.IS_CHECK_FLAG is
'������˱�ʶ';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN_RECEIPT_LIST.EXTEND_PARAM1 is
'��չ1';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN_RECEIPT_LIST.EXTEND_PARAM2 is
'��չ2';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN_RECEIPT_LIST.EXTEND_PARAM3 is
'��չ3';

--==============================================================
-- Table: ICPS_WBC_TM_LOAN_VMS
--==============================================================
create table GAPSUSR.ICPS_WBC_TM_LOAN_VMS
(
   BUSI_DATE            CHARACTER(8)           not null,
   FILE_ORDER           INTEGER                not null,
   ID                   VARCHAR(20),
   ORG                  CHARACTER(12),
   CARD_NO              VARCHAR(19),
   REF_NBR              VARCHAR(23),
   BANK_GROUP_ID        VARCHAR(5),
   BANK_NO              VARCHAR(10),
   PRODUCT_CD           VARCHAR(6),
   BIZ_TAX_INTEREST     DECIMAL(15,2),
   VAT_INT_BAL          DECIMAL(15,2),
   NOREVOKE_VAT_INT_BAL DECIMAL(15,2),
   VAT_TAX              DECIMAL(15,2),
   LOAN_INIT_TERM       INTEGER,
   LAST_MODIFIED_TIME   VARCHAR(14),
   PAID_OUT_DATE        VARCHAR(8),
   AGE_CD               CHARACTER,
   BATCH_DATE           VARCHAR(8),
   JPA_VERSION          INTEGER,
   IS_CHECK_FLAG        CHARACTER,
   EXTEND_PARAM1        VARCHAR(100),
   EXTEND_PARAM2        VARCHAR(250),
   EXTEND_PARAM3        VARCHAR(40),
   constraint PK_ICPS_WBC_TM_LOAN_VMS primary key (BUSI_DATE, FILE_ORDER)
)  IN GAPS_DATA INDEX IN GAPS_INDEX ;

comment on table GAPSUSR.ICPS_WBC_TM_LOAN_VMS is
'�����˰�ӹ���';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN_VMS.BUSI_DATE is
'ҵ������';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN_VMS.FILE_ORDER is
'�ļ����';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN_VMS.ID is
'��˰���ID';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN_VMS.ORG is
'������';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN_VMS.CARD_NO is
'���ʿ���';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN_VMS.REF_NBR is
'���ײο���';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN_VMS.BANK_GROUP_ID is
'���ű��';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN_VMS.BANK_NO is
'���б��';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN_VMS.PRODUCT_CD is
'��Ʒ��';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN_VMS.BIZ_TAX_INTEREST is
'Ӫҵ˰�µ�Ӧ�ƺ�Ӧ��Ϣ';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN_VMS.VAT_INT_BAL is
'90���ڵ�Ӧ��˰Ϣ���';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN_VMS.NOREVOKE_VAT_INT_BAL is
'������㷨��Ӧ��˰Ϣ����90����+90���⻹��ǲ��֣�';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN_VMS.VAT_TAX is
'������ֵ˰';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN_VMS.LOAN_INIT_TERM is
'����������';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN_VMS.LAST_MODIFIED_TIME is
'�ϴ��޸�ʱ��';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN_VMS.PAID_OUT_DATE is
'��������';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN_VMS.AGE_CD is
'����';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN_VMS.BATCH_DATE is
'��������';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN_VMS.JPA_VERSION is
'�ֹ����汾��';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN_VMS.IS_CHECK_FLAG is
'������˱�ʶ';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN_VMS.EXTEND_PARAM1 is
'��չ1';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN_VMS.EXTEND_PARAM2 is
'��չ2';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN_VMS.EXTEND_PARAM3 is
'��չ3';

--==============================================================
-- Table: ICPS_WBC_TM_LOAN_YX
--==============================================================
create table GAPSUSR.ICPS_WBC_TM_LOAN_YX
(
   BUSI_DATE            CHARACTER(8)           not null,
   FILE_ORDER           INTEGER                not null,
   LOAN_RECEIPT_NBR     VARCHAR(20),
   MERCHANT_ID          VARCHAR(20),
   PRODUCT_CD           CHARACTER(6),
   AGREEMENT_NO         VARCHAR(50),
   CNC_CARD_NO          VARCHAR(20),
   LOAN_INIT_TERM       INTEGER,
   CURR_TERM            INTEGER,
   REMAIN_TERM          INTEGER,
   INTEREST_RATE        DECIMAL(12,6),
   LOAN_STATUS          CHARACTER,
   LOAN_PRIN            DECIMAL(15,2),
   LOAN_PAID            DECIMAL(15,2),
   LOAN_INIT_INTEREST   DECIMAL(15,2),
   INT_PAID             DECIMAL(15,2),
   LOAN_EXPIRE_DATE     VARCHAR(8),
   GRACE_DATE           VARCHAR(8),
   DUE_DAYS             INTEGER,
   LOAN_PAIDOUT_FLG     CHARACTER,
   LOAN_PAIDOUT_DATE    VARCHAR(8),
   TERMINATE_REASON_CD  CHARACTER,
   BATCH_DATE           VARCHAR(8),
   BATCH_NO             VARCHAR(16),
   LOAN_BAL_LATE_CHARGE DECIMAL(15,2),
   LOAN_BAL_ADV_PMT_FEE DECIMAL(15,2),
   LOAN_BAL_FEE         DECIMAL(15,2),
   LATE_CHARGE_PAID     DECIMAL(15,2),
   ADV_PMT_FEE_PAID     DECIMAL(15,2),
   FEE_PAID             DECIMAL(15,2),
   NEXT_PRIN            DECIMAL(15,2),
   NEXT_FEE             DECIMAL(15,2),
   REGISTER_DATE        VARCHAR(8),
   PRIN_BAL             DECIMAL(15,2),
   INT_BAL              DECIMAL(15,2),
   PENALTY_BAL          DECIMAL(15,2),
   PENALTY_PAID         DECIMAL(15,2),
   PENALTY_RATE         DECIMAL(15,6),
   BIZ_DATE             VARCHAR(8),
   CREATED_DATETIME     VARCHAR(14),
   LAST_MODIFIED_DATETIME VARCHAR(14),
   LOAN_TYPE            VARCHAR(20),
   UNEARNED_PRIN        DECIMAL(15,2),
   INST_RETURN_FLAG     VARCHAR(1),
   PAID_OUT_RETURN_STATUS VARCHAR(1),
   REF_NBR              VARCHAR(20),
   LOAN_MERGE_TYPE      VARCHAR(20),
   BEF_INIT_INTEREST    DECIMAL(15,2),
   ORIG_INIT_TERM       INTEGER,
   GL_TERM              INTEGER,
   IS_CHECK_FLAG        CHARACTER,
   EXTEND_PARAM1        VARCHAR(100),
   EXTEND_PARAM2        VARCHAR(250),
   EXTEND_PARAM3        VARCHAR(40),
   constraint PK_ICPS_WBC_TM_LOAN_YX primary key (BUSI_DATE, FILE_ORDER)
)  IN GAPS_DATA INDEX IN GAPS_INDEX ;

comment on table GAPSUSR.ICPS_WBC_TM_LOAN_YX is
'���������ݺ�ӳ��';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN_YX.BUSI_DATE is
'ҵ������';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN_YX.FILE_ORDER is
'�ļ����';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN_YX.LOAN_RECEIPT_NBR is
'��ݺ�';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN_YX.MERCHANT_ID is
'ƽ̨ID';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN_YX.PRODUCT_CD is
'��ƷCD';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN_YX.AGREEMENT_NO is
'ƽ̨Э���';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN_YX.CNC_CARD_NO is
'�����';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN_YX.LOAN_INIT_TERM is
'������';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN_YX.CURR_TERM is
'��������';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN_YX.REMAIN_TERM is
'ʣ������';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN_YX.INTEREST_RATE is
'��Ϣ����';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN_YX.LOAN_STATUS is
'״̬';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN_YX.LOAN_PRIN is
'�ܱ���';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN_YX.LOAN_PAID is
'�ѻ�����';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN_YX.LOAN_INIT_INTEREST is
'����Ϣ';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN_YX.INT_PAID is
'�ѻ���Ϣ';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN_YX.LOAN_EXPIRE_DATE is
'��������';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN_YX.GRACE_DATE is
'������';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN_YX.DUE_DAYS is
'��������';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN_YX.LOAN_PAIDOUT_FLG is
'�����ʶ';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN_YX.LOAN_PAIDOUT_DATE is
'��������';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN_YX.TERMINATE_REASON_CD is
'��ֹԭ�����';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN_YX.BATCH_DATE is
'����ͬ������';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN_YX.BATCH_NO is
'���κ�';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN_YX.LOAN_BAL_LATE_CHARGE is
'Ƿ�������ɽ�';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN_YX.LOAN_BAL_ADV_PMT_FEE is
'Ƿ������ǰ����������';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN_YX.LOAN_BAL_FEE is
'Ƿ���ܷ���';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN_YX.LATE_CHARGE_PAID is
'�ѻ����ɽ�';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN_YX.ADV_PMT_FEE_PAID is
'�ѻ���ǰ����������';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN_YX.FEE_PAID is
'�ѻ�����';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN_YX.NEXT_PRIN is
'���ڱ���';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN_YX.NEXT_FEE is
'����������';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN_YX.REGISTER_DATE is
'���ע������';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN_YX.PRIN_BAL is
'Ƿ���ܱ���';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN_YX.INT_BAL is
'Ƿ������Ϣ';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN_YX.PENALTY_BAL is
'Ƿ���ܷ�Ϣ';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN_YX.PENALTY_PAID is
'�ѻ���Ϣ';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN_YX.PENALTY_RATE is
'��Ϣ����';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN_YX.BIZ_DATE is
'ҵ������';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN_YX.CREATED_DATETIME is
'����ʱ������';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN_YX.LAST_MODIFIED_DATETIME is
'����ʱ������';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN_YX.LOAN_TYPE is
'�������';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN_YX.UNEARNED_PRIN is
'δ���ڱ���';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN_YX.INST_RETURN_FLAG is
'�Ƿ�����Ϣ';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN_YX.PAID_OUT_RETURN_STATUS is
'�����˱���Ϣ״̬';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN_YX.REF_NBR is
'���׼�����';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN_YX.LOAN_MERGE_TYPE is
'��ݺϲ�����';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN_YX.BEF_INIT_INTEREST is
'ԭ��������Ϣ';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN_YX.ORIG_INIT_TERM is
'ԭʼ��������';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN_YX.GL_TERM is
'�����������������������Ҫ���Ի������Լӹ�';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN_YX.IS_CHECK_FLAG is
'������˱�ʶ';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN_YX.EXTEND_PARAM1 is
'��չ1';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN_YX.EXTEND_PARAM2 is
'��չ2';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN_YX.EXTEND_PARAM3 is
'��չ3';

--==============================================================
-- Table: ICPS_WBC_TM_MERCHANT_CUST
--==============================================================
create table GAPSUSR.ICPS_WBC_TM_MERCHANT_CUST
(
   BUSI_DATE            CHARACTER(8)           not null,
   FILE_ORDER           INTEGER                not null,
   USER_ID              VARCHAR(32),
   MERCHANT_ID          VARCHAR(20),
   NBS_CUST_ID          VARCHAR(20),
   USER_NAME            VARCHAR(60),
   USER_MOBILE          VARCHAR(20),
   APPLY_DATETIME       VARCHAR(14),
   REG_MOBILE           VARCHAR(20),
   QQ_OPENID            VARCHAR(32),
   WX_OPENID            VARCHAR(32),
   LOGIN_ID             VARCHAR(32),
   COMPANY_NAME         VARCHAR(60),
   COMPANY_PHONE        VARCHAR(20),
   ADDRESS              VARCHAR(60),
   CONTACT_NAME         VARCHAR(40),
   CONTACT_PHONE        VARCHAR(20),
   CONTACT_RELATION     VARCHAR(10),
   RESERVE1             VARCHAR(20),
   RESERVE2             VARCHAR(50),
   RESERVE3             VARCHAR(50),
   BIZ_DATE             VARCHAR(8),
   CREATED_DATETIME     VARCHAR(14),
   LAST_MODIFIED_DATETIME VARCHAR(14),
   CONTACT_ADDR         VARCHAR(80),
   CONTACT_ID_NO        VARCHAR(30),
   CO_LICENSES          VARCHAR(80),
   DRIVER_LICENSE       VARCHAR(30),
   COMPANY_ADDR         VARCHAR(80),
   HOME_PHONE           VARCHAR(20),
   OCCUPATION           VARCHAR(60),
   SS_AVE_AMT_MTLY      DECIMAL(13,2),
   SALARY_AVE_MTLY      DECIMAL(13,2),
   IS_HOME_VISITED      CHARACTER,
   HOUSE_INFO           VARCHAR(80),
   MER_APPLY_RESULT     CHARACTER,
   MER_APPLY_VIEW       VARCHAR(80),
   MER_REFUSE_REASON    VARCHAR(10),
   CUST_VALUE           VARCHAR(2014),
   IS_GUARANTOR         VARCHAR(1),
   IS_CHECK_FLAG        CHARACTER,
   EXTEND_PARAM1        VARCHAR(100),
   EXTEND_PARAM2        VARCHAR(250),
   EXTEND_PARAM3        VARCHAR(40),
   constraint PK_ICPS_WBC_TM_MERCHANT_CUST primary key (BUSI_DATE, FILE_ORDER)
)  IN GAPS_DATA INDEX IN GAPS_INDEX ;

comment on table GAPSUSR.ICPS_WBC_TM_MERCHANT_CUST is
'ƽ̨�ͻ���Ϣ��';

comment on column GAPSUSR.ICPS_WBC_TM_MERCHANT_CUST.BUSI_DATE is
'ҵ������';

comment on column GAPSUSR.ICPS_WBC_TM_MERCHANT_CUST.FILE_ORDER is
'�ļ����';

comment on column GAPSUSR.ICPS_WBC_TM_MERCHANT_CUST.USER_ID is
'ƽ̨�Ŀͻ�ID';

comment on column GAPSUSR.ICPS_WBC_TM_MERCHANT_CUST.MERCHANT_ID is
'ƽ̨ID';

comment on column GAPSUSR.ICPS_WBC_TM_MERCHANT_CUST.NBS_CUST_ID is
'NBS�ͻ�ID';

comment on column GAPSUSR.ICPS_WBC_TM_MERCHANT_CUST.USER_NAME is
'ƽ̨ע��Ŀͻ�����';

comment on column GAPSUSR.ICPS_WBC_TM_MERCHANT_CUST.USER_MOBILE is
'ƽ̨�Ǽǵ��û��ֻ���';

comment on column GAPSUSR.ICPS_WBC_TM_MERCHANT_CUST.APPLY_DATETIME is
'ƽ̨ID����ʱ��';

comment on column GAPSUSR.ICPS_WBC_TM_MERCHANT_CUST.REG_MOBILE is
'ע���ֻ���';

comment on column GAPSUSR.ICPS_WBC_TM_MERCHANT_CUST.QQ_OPENID is
'QQ_OPENID';

comment on column GAPSUSR.ICPS_WBC_TM_MERCHANT_CUST.WX_OPENID is
'WX_OPENID';

comment on column GAPSUSR.ICPS_WBC_TM_MERCHANT_CUST.LOGIN_ID is
'΢��WEB��¼ID';

comment on column GAPSUSR.ICPS_WBC_TM_MERCHANT_CUST.COMPANY_NAME is
'��λ����';

comment on column GAPSUSR.ICPS_WBC_TM_MERCHANT_CUST.COMPANY_PHONE is
'��λ�绰';

comment on column GAPSUSR.ICPS_WBC_TM_MERCHANT_CUST.ADDRESS is
'��ס��ַ';

comment on column GAPSUSR.ICPS_WBC_TM_MERCHANT_CUST.CONTACT_NAME is
'��ϵ������';

comment on column GAPSUSR.ICPS_WBC_TM_MERCHANT_CUST.CONTACT_PHONE is
'��ϵ���ֻ���';

comment on column GAPSUSR.ICPS_WBC_TM_MERCHANT_CUST.CONTACT_RELATION is
'��ϵ�˹�ϵ';

comment on column GAPSUSR.ICPS_WBC_TM_MERCHANT_CUST.RESERVE1 is
'�����ֶ�1';

comment on column GAPSUSR.ICPS_WBC_TM_MERCHANT_CUST.RESERVE2 is
'�����ֶ�2';

comment on column GAPSUSR.ICPS_WBC_TM_MERCHANT_CUST.RESERVE3 is
'�����ֶ�3';

comment on column GAPSUSR.ICPS_WBC_TM_MERCHANT_CUST.BIZ_DATE is
'ҵ������';

comment on column GAPSUSR.ICPS_WBC_TM_MERCHANT_CUST.CREATED_DATETIME is
'����ʱ������';

comment on column GAPSUSR.ICPS_WBC_TM_MERCHANT_CUST.LAST_MODIFIED_DATETIME is
'����ʱ������';

comment on column GAPSUSR.ICPS_WBC_TM_MERCHANT_CUST.CONTACT_ADDR is
'��ϵ�˵�ַ';

comment on column GAPSUSR.ICPS_WBC_TM_MERCHANT_CUST.CONTACT_ID_NO is
'��ϵ�����֤��';

comment on column GAPSUSR.ICPS_WBC_TM_MERCHANT_CUST.CO_LICENSES is
'Ӫҵִ�պ�';

comment on column GAPSUSR.ICPS_WBC_TM_MERCHANT_CUST.DRIVER_LICENSE is
'��ʻ֤����';

comment on column GAPSUSR.ICPS_WBC_TM_MERCHANT_CUST.COMPANY_ADDR is
'��˾��ַ';

comment on column GAPSUSR.ICPS_WBC_TM_MERCHANT_CUST.HOME_PHONE is
'��ͥ�̻�����';

comment on column GAPSUSR.ICPS_WBC_TM_MERCHANT_CUST.OCCUPATION is
'ְҵ';

comment on column GAPSUSR.ICPS_WBC_TM_MERCHANT_CUST.SS_AVE_AMT_MTLY is
'ÿ���籣ƽ���ɽ����';

comment on column GAPSUSR.ICPS_WBC_TM_MERCHANT_CUST.SALARY_AVE_MTLY is
'ÿ��ƽ�����ʽ�����ˮ';

comment on column GAPSUSR.ICPS_WBC_TM_MERCHANT_CUST.IS_HOME_VISITED is
'���޼ҷ�';

comment on column GAPSUSR.ICPS_WBC_TM_MERCHANT_CUST.HOUSE_INFO is
'������Ϣ';

comment on column GAPSUSR.ICPS_WBC_TM_MERCHANT_CUST.MER_APPLY_RESULT is
'�������';

comment on column GAPSUSR.ICPS_WBC_TM_MERCHANT_CUST.MER_APPLY_VIEW is
'�������';

comment on column GAPSUSR.ICPS_WBC_TM_MERCHANT_CUST.MER_REFUSE_REASON is
'�ܾ�ԭ�����';

comment on column GAPSUSR.ICPS_WBC_TM_MERCHANT_CUST.CUST_VALUE is
'�ͻ���Ϣ�����ֶΣ�';

comment on column GAPSUSR.ICPS_WBC_TM_MERCHANT_CUST.IS_GUARANTOR is
'���޵�����';

comment on column GAPSUSR.ICPS_WBC_TM_MERCHANT_CUST.IS_CHECK_FLAG is
'������˱�ʶ';

comment on column GAPSUSR.ICPS_WBC_TM_MERCHANT_CUST.EXTEND_PARAM1 is
'��չ1';

comment on column GAPSUSR.ICPS_WBC_TM_MERCHANT_CUST.EXTEND_PARAM2 is
'��չ2';

comment on column GAPSUSR.ICPS_WBC_TM_MERCHANT_CUST.EXTEND_PARAM3 is
'��չ3';

--==============================================================
-- Table: ICPS_WBC_TM_MERCHANT_PRODUCT_CUST
--==============================================================
create table GAPSUSR.ICPS_WBC_TM_MERCHANT_PRODUCT_CUST
(
   BUSI_DATE            CHARACTER(8)           not null,
   FILE_ORDER           INTEGER                not null,
   USER_ID              VARCHAR(32),
   MERCHANT_ID          VARCHAR(20),
   PRODUCT_CD           CHARACTER(6),
   CNC_CARD_NO          VARCHAR(20),
   DEBIT_CARD_NO        VARCHAR(19),
   WB_DEBIT_CARD_NO     VARCHAR(19),
   NBS_CUST_ID          VARCHAR(20),
   APS_APP_TIME         VARCHAR(8),
   APS_APP_NO           VARCHAR(20),
   APS_APP_NO_STATUS    VARCHAR(20),
   APS_APP_COUNT        INTEGER,
   APS_APPROVAL_DATE    VARCHAR(8),
   APS_RESULT_LEVEL     VARCHAR(2),
   APS_REJ_CODE         VARCHAR(15),
   APS_REJ_DATE         VARCHAR(10),
   CNC_SETUP_DATE       VARCHAR(8),
   APS_CREDIT_LIMIT     DECIMAL(15,2),
   GID                  VARCHAR(64),
   OPER_IP              VARCHAR(24),
   OS_TYPE              VARCHAR(20),
   LBS                  VARCHAR(60),
   IOS_IDFA             VARCHAR(50),
   ANDROID_IMEI         VARCHAR(50),
   SUBMITTED_ENTRY      CHARACTER(3),
   SUBMITTED_CITY       CHARACTER(32),
   RESERVE1             VARCHAR(20),
   RESERVE2             VARCHAR(50),
   RESERVE3             VARCHAR(50),
   BIZ_DATE             VARCHAR(8),
   CREATED_DATETIME     VARCHAR(14),
   LAST_MODIFIED_DATETIME VARCHAR(14),
   APP_BIZ_SEQ_NO       VARCHAR(32),
   APS_REJ_REASON       VARCHAR(120),
   APP_EXPIRY_DATE      VARCHAR(8),
   AGENT_ID             VARCHAR(20),
   AGENT_NAME           VARCHAR(30),
   IS_CHECK_FLAG        CHARACTER,
   EXTEND_PARAM1        VARCHAR(100),
   EXTEND_PARAM2        VARCHAR(250),
   EXTEND_PARAM3        VARCHAR(40),
   constraint PK_ICPS_WBC_TM_MERCHANT_PRODUCT_CUST primary key (BUSI_DATE, FILE_ORDER)
)  IN GAPS_DATA INDEX IN GAPS_INDEX ;

comment on table GAPSUSR.ICPS_WBC_TM_MERCHANT_PRODUCT_CUST is
'�ͻ���Ʒ��Ϣ��';

comment on column GAPSUSR.ICPS_WBC_TM_MERCHANT_PRODUCT_CUST.BUSI_DATE is
'ҵ������';

comment on column GAPSUSR.ICPS_WBC_TM_MERCHANT_PRODUCT_CUST.FILE_ORDER is
'�ļ����';

comment on column GAPSUSR.ICPS_WBC_TM_MERCHANT_PRODUCT_CUST.USER_ID is
'ƽ̨�Ŀͻ�ID';

comment on column GAPSUSR.ICPS_WBC_TM_MERCHANT_PRODUCT_CUST.MERCHANT_ID is
'ƽ̨ID';

comment on column GAPSUSR.ICPS_WBC_TM_MERCHANT_PRODUCT_CUST.PRODUCT_CD is
'��ƷCD';

comment on column GAPSUSR.ICPS_WBC_TM_MERCHANT_PRODUCT_CUST.CNC_CARD_NO is
'�����';

comment on column GAPSUSR.ICPS_WBC_TM_MERCHANT_PRODUCT_CUST.DEBIT_CARD_NO is
'���н�ǿ���';

comment on column GAPSUSR.ICPS_WBC_TM_MERCHANT_PRODUCT_CUST.WB_DEBIT_CARD_NO is
'���н�ǿ���';

comment on column GAPSUSR.ICPS_WBC_TM_MERCHANT_PRODUCT_CUST.NBS_CUST_ID is
'NBS�ͻ�ID';

comment on column GAPSUSR.ICPS_WBC_TM_MERCHANT_PRODUCT_CUST.APS_APP_TIME is
'APS��������ʱ��';

comment on column GAPSUSR.ICPS_WBC_TM_MERCHANT_PRODUCT_CUST.APS_APP_NO is
'APS���������';

comment on column GAPSUSR.ICPS_WBC_TM_MERCHANT_PRODUCT_CUST.APS_APP_NO_STATUS is
'APS�����״̬';

comment on column GAPSUSR.ICPS_WBC_TM_MERCHANT_PRODUCT_CUST.APS_APP_COUNT is
'�����������';

comment on column GAPSUSR.ICPS_WBC_TM_MERCHANT_PRODUCT_CUST.APS_APPROVAL_DATE is
'APS����ͨ������';

comment on column GAPSUSR.ICPS_WBC_TM_MERCHANT_PRODUCT_CUST.APS_RESULT_LEVEL is
'APS��������ȼ�';

comment on column GAPSUSR.ICPS_WBC_TM_MERCHANT_PRODUCT_CUST.APS_REJ_CODE is
'APS�����ܾ���';

comment on column GAPSUSR.ICPS_WBC_TM_MERCHANT_PRODUCT_CUST.APS_REJ_DATE is
'APS�����ܾ�ʱ��';

comment on column GAPSUSR.ICPS_WBC_TM_MERCHANT_PRODUCT_CUST.CNC_SETUP_DATE is
'���������';

comment on column GAPSUSR.ICPS_WBC_TM_MERCHANT_PRODUCT_CUST.APS_CREDIT_LIMIT is
'����ʱ���Ŷ��';

comment on column GAPSUSR.ICPS_WBC_TM_MERCHANT_PRODUCT_CUST.GID is
'����ԴGID';

comment on column GAPSUSR.ICPS_WBC_TM_MERCHANT_PRODUCT_CUST.OPER_IP is
'����ԴIP';

comment on column GAPSUSR.ICPS_WBC_TM_MERCHANT_PRODUCT_CUST.OS_TYPE is
'����ϵͳ';

comment on column GAPSUSR.ICPS_WBC_TM_MERCHANT_PRODUCT_CUST.LBS is
'LBS';

comment on column GAPSUSR.ICPS_WBC_TM_MERCHANT_PRODUCT_CUST.IOS_IDFA is
'IOS��ʾ��';

comment on column GAPSUSR.ICPS_WBC_TM_MERCHANT_PRODUCT_CUST.ANDROID_IMEI is
'ANDROID������ַ';

comment on column GAPSUSR.ICPS_WBC_TM_MERCHANT_PRODUCT_CUST.SUBMITTED_ENTRY is
'�ύ���';

comment on column GAPSUSR.ICPS_WBC_TM_MERCHANT_PRODUCT_CUST.SUBMITTED_CITY is
'�������';

comment on column GAPSUSR.ICPS_WBC_TM_MERCHANT_PRODUCT_CUST.RESERVE1 is
'�����ֶ�1';

comment on column GAPSUSR.ICPS_WBC_TM_MERCHANT_PRODUCT_CUST.RESERVE2 is
'�����ֶ�2';

comment on column GAPSUSR.ICPS_WBC_TM_MERCHANT_PRODUCT_CUST.RESERVE3 is
'�����ֶ�3';

comment on column GAPSUSR.ICPS_WBC_TM_MERCHANT_PRODUCT_CUST.BIZ_DATE is
'ҵ������';

comment on column GAPSUSR.ICPS_WBC_TM_MERCHANT_PRODUCT_CUST.CREATED_DATETIME is
'����ʱ������';

comment on column GAPSUSR.ICPS_WBC_TM_MERCHANT_PRODUCT_CUST.LAST_MODIFIED_DATETIME is
'����ʱ������';

comment on column GAPSUSR.ICPS_WBC_TM_MERCHANT_PRODUCT_CUST.APP_BIZ_SEQ_NO is
'����ҵ����ˮ��';

comment on column GAPSUSR.ICPS_WBC_TM_MERCHANT_PRODUCT_CUST.APS_REJ_REASON is
'����ܾ�ԭ��';

comment on column GAPSUSR.ICPS_WBC_TM_MERCHANT_PRODUCT_CUST.APP_EXPIRY_DATE is
'����ʧЧ����';

comment on column GAPSUSR.ICPS_WBC_TM_MERCHANT_PRODUCT_CUST.AGENT_ID is
'���������id';

comment on column GAPSUSR.ICPS_WBC_TM_MERCHANT_PRODUCT_CUST.AGENT_NAME is
'����������';

comment on column GAPSUSR.ICPS_WBC_TM_MERCHANT_PRODUCT_CUST.IS_CHECK_FLAG is
'������˱�ʶ';

comment on column GAPSUSR.ICPS_WBC_TM_MERCHANT_PRODUCT_CUST.EXTEND_PARAM1 is
'��չ1';

comment on column GAPSUSR.ICPS_WBC_TM_MERCHANT_PRODUCT_CUST.EXTEND_PARAM2 is
'��չ2';

comment on column GAPSUSR.ICPS_WBC_TM_MERCHANT_PRODUCT_CUST.EXTEND_PARAM3 is
'��չ3';

--==============================================================
-- Table: ICPS_WBC_TM_NBS_CUST
--==============================================================
create table GAPSUSR.ICPS_WBC_TM_NBS_CUST
(
   BUSI_DATE            CHARACTER(8)           not null,
   FILE_ORDER           INTEGER                not null,
   NBS_CUST_ID          VARCHAR(20),
   "NAME"               VARCHAR(80),
   ID_TYPE              CHARACTER(2),
   ID_NO                VARCHAR(30),
   ECIF_NO              VARCHAR(40),
   RESERVE1             VARCHAR(20),
   RESERVE2             VARCHAR(20),
   RESERVE3             VARCHAR(50),
   BIZ_DATE             VARCHAR(8),
   CREATED_DATETIME     VARCHAR(14),
   LAST_MODIFIED_DATETIME VARCHAR(14),
   IS_CHECK_FLAG        CHARACTER,
   EXTEND_PARAM1        VARCHAR(100),
   EXTEND_PARAM2        VARCHAR(250),
   EXTEND_PARAM3        VARCHAR(40),
   constraint PK_ICPS_WBC_TM_NBS_CUST primary key (BUSI_DATE, FILE_ORDER)
)  IN GAPS_DATA INDEX IN GAPS_INDEX ;

comment on table GAPSUSR.ICPS_WBC_TM_NBS_CUST is
'nbs�ͻ���';

comment on column GAPSUSR.ICPS_WBC_TM_NBS_CUST.BUSI_DATE is
'ҵ������';

comment on column GAPSUSR.ICPS_WBC_TM_NBS_CUST.FILE_ORDER is
'�ļ����';

comment on column GAPSUSR.ICPS_WBC_TM_NBS_CUST.NBS_CUST_ID is
'NBS�ͻ�ID';

comment on column GAPSUSR.ICPS_WBC_TM_NBS_CUST."NAME" is
'����';

comment on column GAPSUSR.ICPS_WBC_TM_NBS_CUST.ID_TYPE is
'֤������';

comment on column GAPSUSR.ICPS_WBC_TM_NBS_CUST.ID_NO is
'֤������';

comment on column GAPSUSR.ICPS_WBC_TM_NBS_CUST.ECIF_NO is
'ecif�ͻ���';

comment on column GAPSUSR.ICPS_WBC_TM_NBS_CUST.RESERVE1 is
'�����ֶ�1';

comment on column GAPSUSR.ICPS_WBC_TM_NBS_CUST.RESERVE2 is
'���֤��Ч��';

comment on column GAPSUSR.ICPS_WBC_TM_NBS_CUST.RESERVE3 is
'�����ֶ�3';

comment on column GAPSUSR.ICPS_WBC_TM_NBS_CUST.BIZ_DATE is
'ҵ������';

comment on column GAPSUSR.ICPS_WBC_TM_NBS_CUST.CREATED_DATETIME is
'����ʱ������';

comment on column GAPSUSR.ICPS_WBC_TM_NBS_CUST.LAST_MODIFIED_DATETIME is
'����ʱ������';

comment on column GAPSUSR.ICPS_WBC_TM_NBS_CUST.IS_CHECK_FLAG is
'������˱�ʶ';

comment on column GAPSUSR.ICPS_WBC_TM_NBS_CUST.EXTEND_PARAM1 is
'��չ1';

comment on column GAPSUSR.ICPS_WBC_TM_NBS_CUST.EXTEND_PARAM2 is
'��չ2';

comment on column GAPSUSR.ICPS_WBC_TM_NBS_CUST.EXTEND_PARAM3 is
'��չ3';

--==============================================================
-- Table: ICPS_WBC_TM_NBS_CUST_EXT_INFO
--==============================================================
create table GAPSUSR.ICPS_WBC_TM_NBS_CUST_EXT_INFO
(
   BUSI_DATE            CHARACTER(8)           not null,
   FILE_ORDER           INTEGER                not null,
   NBS_CUST_ID          VARCHAR(20),
   PRODUCT_CD           CHARACTER(6),
   MERCHANT_ID          VARCHAR(20),
   "NAME"               VARCHAR(80),
   ID_TYPE              CHARACTER(2),
   ID_NO                VARCHAR(30),
   ID_NO_EXPIRY         VARCHAR(30),
   RESIDENTIAL_ADDRESS  VARCHAR(100),
   GENDER               CHARACTER,
   NATIONALITY          VARCHAR(20),
   MARRIAGE             VARCHAR(20),
   EDUCATION            VARCHAR(20),
   CUST_EXT_INF1        VARCHAR(30),
   CUST_EXT_INF2        VARCHAR(30),
   CUST_EXT_INF3        VARCHAR(30),
   CUST_EXT_INF4        VARCHAR(30),
   CUST_EXT_INF5        VARCHAR(30),
   CUST_EXT_INF6        VARCHAR(30),
   CUST_EXT_INF7        VARCHAR(30),
   CUST_EXT_INF8        VARCHAR(30),
   CUST_EXT_INF9        VARCHAR(30),
   CUST_EXT_INF10       VARCHAR(30),
   CUST_EXT_INF11       VARCHAR(30),
   CUST_EXT_INF12       VARCHAR(30),
   CUST_EXT_INF13       VARCHAR(30),
   CUST_EXT_INF14       VARCHAR(30),
   CUST_EXT_INF15       VARCHAR(30),
   CUST_EXT_INF16       VARCHAR(30),
   CUST_EXT_INF17       VARCHAR(50),
   CUST_EXT_INF18       VARCHAR(50),
   CUST_EXT_INF19       VARCHAR(100),
   CUST_EXT_INF20       VARCHAR(100),
   CREATED_DATETIME     VARCHAR(14),
   LAST_MODIFIED_DATETIME VARCHAR(14),
   IS_CHECK_FLAG        CHARACTER,
   EXTEND_PARAM1        VARCHAR(100),
   EXTEND_PARAM2        VARCHAR(250),
   EXTEND_PARAM3        VARCHAR(40),
   constraint PK_ICPS_WBC_TM_NBS_CUST_EXT_INFO primary key (BUSI_DATE, FILE_ORDER)
)  IN GAPS_DATA INDEX IN GAPS_INDEX ;

comment on table GAPSUSR.ICPS_WBC_TM_NBS_CUST_EXT_INFO is
'nbs�ͻ���չ��';

comment on column GAPSUSR.ICPS_WBC_TM_NBS_CUST_EXT_INFO.BUSI_DATE is
'ҵ������';

comment on column GAPSUSR.ICPS_WBC_TM_NBS_CUST_EXT_INFO.FILE_ORDER is
'�ļ����';

comment on column GAPSUSR.ICPS_WBC_TM_NBS_CUST_EXT_INFO.NBS_CUST_ID is
'NBS�ͻ�ID';

comment on column GAPSUSR.ICPS_WBC_TM_NBS_CUST_EXT_INFO.PRODUCT_CD is
'��Ʒ��';

comment on column GAPSUSR.ICPS_WBC_TM_NBS_CUST_EXT_INFO.MERCHANT_ID is
'ƽ̨ID';

comment on column GAPSUSR.ICPS_WBC_TM_NBS_CUST_EXT_INFO."NAME" is
'����';

comment on column GAPSUSR.ICPS_WBC_TM_NBS_CUST_EXT_INFO.ID_TYPE is
'֤������';

comment on column GAPSUSR.ICPS_WBC_TM_NBS_CUST_EXT_INFO.ID_NO is
'֤������';

comment on column GAPSUSR.ICPS_WBC_TM_NBS_CUST_EXT_INFO.ID_NO_EXPIRY is
'���֤��Ч��';

comment on column GAPSUSR.ICPS_WBC_TM_NBS_CUST_EXT_INFO.RESIDENTIAL_ADDRESS is
'��ַ';

comment on column GAPSUSR.ICPS_WBC_TM_NBS_CUST_EXT_INFO.GENDER is
'�Ա�';

comment on column GAPSUSR.ICPS_WBC_TM_NBS_CUST_EXT_INFO.NATIONALITY is
'����';

comment on column GAPSUSR.ICPS_WBC_TM_NBS_CUST_EXT_INFO.MARRIAGE is
'����״��';

comment on column GAPSUSR.ICPS_WBC_TM_NBS_CUST_EXT_INFO.EDUCATION is
'ѧ��';

comment on column GAPSUSR.ICPS_WBC_TM_NBS_CUST_EXT_INFO.CUST_EXT_INF1 is
'����';

comment on column GAPSUSR.ICPS_WBC_TM_NBS_CUST_EXT_INFO.CUST_EXT_INF2 is
'�����ֶ�';

comment on column GAPSUSR.ICPS_WBC_TM_NBS_CUST_EXT_INFO.CUST_EXT_INF3 is
'�����ֶ�';

comment on column GAPSUSR.ICPS_WBC_TM_NBS_CUST_EXT_INFO.CUST_EXT_INF4 is
'�����ֶ�';

comment on column GAPSUSR.ICPS_WBC_TM_NBS_CUST_EXT_INFO.CUST_EXT_INF5 is
'�����ֶ�';

comment on column GAPSUSR.ICPS_WBC_TM_NBS_CUST_EXT_INFO.CUST_EXT_INF6 is
'�����ֶ�';

comment on column GAPSUSR.ICPS_WBC_TM_NBS_CUST_EXT_INFO.CUST_EXT_INF7 is
'�����ֶ�';

comment on column GAPSUSR.ICPS_WBC_TM_NBS_CUST_EXT_INFO.CUST_EXT_INF8 is
'�����ֶ�';

comment on column GAPSUSR.ICPS_WBC_TM_NBS_CUST_EXT_INFO.CUST_EXT_INF9 is
'�����ֶ�';

comment on column GAPSUSR.ICPS_WBC_TM_NBS_CUST_EXT_INFO.CUST_EXT_INF10 is
'�����ֶ�';

comment on column GAPSUSR.ICPS_WBC_TM_NBS_CUST_EXT_INFO.CUST_EXT_INF11 is
'�����ֶ�';

comment on column GAPSUSR.ICPS_WBC_TM_NBS_CUST_EXT_INFO.CUST_EXT_INF12 is
'�����ֶ�';

comment on column GAPSUSR.ICPS_WBC_TM_NBS_CUST_EXT_INFO.CUST_EXT_INF13 is
'�����ֶ�';

comment on column GAPSUSR.ICPS_WBC_TM_NBS_CUST_EXT_INFO.CUST_EXT_INF14 is
'�����ֶ�';

comment on column GAPSUSR.ICPS_WBC_TM_NBS_CUST_EXT_INFO.CUST_EXT_INF15 is
'�����ֶ�';

comment on column GAPSUSR.ICPS_WBC_TM_NBS_CUST_EXT_INFO.CUST_EXT_INF16 is
'�����ֶ�';

comment on column GAPSUSR.ICPS_WBC_TM_NBS_CUST_EXT_INFO.CUST_EXT_INF17 is
'�����ֶ�';

comment on column GAPSUSR.ICPS_WBC_TM_NBS_CUST_EXT_INFO.CUST_EXT_INF18 is
'�����ֶ�';

comment on column GAPSUSR.ICPS_WBC_TM_NBS_CUST_EXT_INFO.CUST_EXT_INF19 is
'�����ֶ�';

comment on column GAPSUSR.ICPS_WBC_TM_NBS_CUST_EXT_INFO.CUST_EXT_INF20 is
'�����ֶ�';

comment on column GAPSUSR.ICPS_WBC_TM_NBS_CUST_EXT_INFO.CREATED_DATETIME is
'����ʱ������';

comment on column GAPSUSR.ICPS_WBC_TM_NBS_CUST_EXT_INFO.LAST_MODIFIED_DATETIME is
'����ʱ������';

comment on column GAPSUSR.ICPS_WBC_TM_NBS_CUST_EXT_INFO.IS_CHECK_FLAG is
'������˱�ʶ';

comment on column GAPSUSR.ICPS_WBC_TM_NBS_CUST_EXT_INFO.EXTEND_PARAM1 is
'��չ1';

comment on column GAPSUSR.ICPS_WBC_TM_NBS_CUST_EXT_INFO.EXTEND_PARAM2 is
'��չ2';

comment on column GAPSUSR.ICPS_WBC_TM_NBS_CUST_EXT_INFO.EXTEND_PARAM3 is
'��չ3';

--==============================================================
-- Table: ICPS_WBC_TM_PLAN
--==============================================================
create table GAPSUSR.ICPS_WBC_TM_PLAN
(
   BUSI_DATE            CHARACTER(8)           not null,
   FILE_ORDER           INTEGER                not null,
   ORG                  CHARACTER(12),
   PLAN_ID              VARCHAR(20),
   ACCT_NO              VARCHAR(20),
   ACCT_TYPE            CHARACTER,
   LOGICAL_CARD_NO      VARCHAR(19),
   PLAN_NBR             CHARACTER(6),
   PLAN_TYPE            CHARACTER,
   PRODUCT_CD           CHARACTER(6),
   REF_NBR              VARCHAR(23),
   CURR_BAL             DECIMAL(15,2),
   BEGIN_BAL            DECIMAL(15,2),
   DISPUTE_AMT          DECIMAL(15,2),
   TOT_DUE_AMT          DECIMAL(15,2),
   PLAN_ADD_DATE        VARCHAR(8),
   PAID_OUT_DATE        VARCHAR(8),
   PAST_PRINCIPAL       DECIMAL(15,2),
   PAST_INTEREST        DECIMAL(15,2),
   PAST_CARD_FEE        DECIMAL(15,2),
   PAST_OVRLMT_FEE      DECIMAL(15,2),
   PAST_LPC             DECIMAL(15,2),
   PAST_NSF_FEE         DECIMAL(15,2),
   PAST_TXN_FEE         DECIMAL(15,2),
   PAST_SVC_FEE         DECIMAL(15,2),
   PAST_INS             DECIMAL(15,2),
   PAST_USER_FEE1       DECIMAL(15,2),
   PAST_USER_FEE2       DECIMAL(15,2),
   PAST_USER_FEE3       DECIMAL(15,2),
   PAST_USER_FEE4       DECIMAL(15,2),
   PAST_USER_FEE5       DECIMAL(15,2),
   PAST_USER_FEE6       DECIMAL(15,2),
   CTD_PRINCIPAL        DECIMAL(15,2),
   CTD_INTEREST         DECIMAL(15,2),
   CTD_CARD_FEE         DECIMAL(15,2),
   CTD_OVRLMT_FEE       DECIMAL(15,2),
   CTD_LPC              DECIMAL(15,2),
   CTD_NSF_FEE          DECIMAL(15,2),
   CTD_SVC_FEE          DECIMAL(15,2),
   CTD_TXN_FEE          DECIMAL(15,2),
   CTD_INS              DECIMAL(15,2),
   CTD_USER_FEE1        DECIMAL(15,2),
   CTD_USER_FEE2        DECIMAL(15,2),
   CTD_USER_FEE3        DECIMAL(15,2),
   CTD_USER_FEE4        DECIMAL(15,2),
   CTD_USER_FEE5        DECIMAL(15,2),
   CTD_USER_FEE6        DECIMAL(15,2),
   CTD_AMT_DB           DECIMAL(15,2),
   CTD_AMT_CR           DECIMAL(15,2),
   CTD_NBR_DB           INTEGER,
   CTD_NBR_CR           INTEGER,
   NODEFBNP_INT_ACRU    DECIMAL(15,4),
   BEG_DEFBNP_INT_ACRU  DECIMAL(15,4),
   CTD_DEFBNP_INT_ACRU  DECIMAL(15,4),
   USER_CODE1           VARCHAR(4),
   USER_CODE2           VARCHAR(4),
   USER_CODE3           VARCHAR(4),
   USER_CODE4           VARCHAR(4),
   USER_CODE5           VARCHAR(4),
   USER_CODE6           VARCHAR(4),
   USER_NUMBER1         INTEGER,
   USER_NUMBER2         INTEGER,
   USER_NUMBER3         INTEGER,
   USER_NUMBER4         INTEGER,
   USER_NUMBER5         INTEGER,
   USER_NUMBER6         INTEGER,
   USER_FIELD1          VARCHAR(40),
   USER_FIELD2          VARCHAR(40),
   USER_FIELD3          VARCHAR(40),
   USER_FIELD4          VARCHAR(40),
   USER_FIELD5          VARCHAR(40),
   USER_FIELD6          VARCHAR(40),
   USER_DATE1           VARCHAR(8),
   USER_DATE2           VARCHAR(8),
   USER_DATE3           VARCHAR(8),
   USER_DATE4           VARCHAR(8),
   USER_DATE5           VARCHAR(8),
   USER_DATE6           VARCHAR(8),
   USER_AMT1            DECIMAL(15,2),
   USER_AMT2            DECIMAL(15,2),
   USER_AMT3            DECIMAL(15,2),
   USER_AMT4            DECIMAL(15,2),
   USER_AMT5            DECIMAL(15,2),
   USER_AMT6            DECIMAL(15,2),
   JPA_VERSION          INTEGER,
   PAST_PENALTY         DECIMAL(15,2),
   CTD_PENALTY          DECIMAL(15,2),
   PAST_COMPOUND        DECIMAL(15,2),
   CTD_COMPOUND         DECIMAL(15,2),
   PENALTY_ACRU         DECIMAL(15,2),
   COMPOUND_ACRU        DECIMAL(15,2),
   INTEREST_RATE        DECIMAL(15,2),
   PENALTY_RATE         DECIMAL(15,2),
   COMPOUND_RATE        DECIMAL(15,2),
   USE_PLAN_RATE        CHARACTER,
   LAST_PMT_DATE        VARCHAR(8),
   TERM                 INTEGER,
   CALC_TYPE            CHARACTER,
   CALC_CYCLE           INTEGER,
   FEE_RATE             DECIMAL(12,4),
   LAST_FEE_DATE        VARCHAR(8),
   NEXT_FEE_DATE        VARCHAR(8),
   TXN_SEQ              VARCHAR(20),
   FIRST_DD_DATE        VARCHAR(8),
   CONSUMER_TRANS_ID    VARCHAR(32),
   SYS_TRANS_ID         VARCHAR(32),
   QCHANNEL_ID          VARCHAR(15),
   SUB_TERMINAL_TYPE    VARCHAR(15),
   SUB_MERCH_ID         VARCHAR(40),
   SUB_MERCH_NAME       VARCHAR(60),
   WARES_DESC           VARCHAR(60),
   LAST_MODIFIED_DATETIME VARCHAR(14),
   ORIGINAL_AMT         DECIMAL(15,4),
   INTEREST_CALC_BASE   CHARACTER,
   CREATED_DATETIME     VARCHAR(14),
   IS_CHECK_FLAG        CHARACTER,
   EXTEND_PARAM1        VARCHAR(100),
   EXTEND_PARAM2        VARCHAR(250),
   EXTEND_PARAM3        VARCHAR(40),
   constraint PK_ICPS_WBC_TM_PLAN primary key (BUSI_DATE, FILE_ORDER)
)  IN GAPS_DATA INDEX IN GAPS_INDEX ;

comment on table GAPSUSR.ICPS_WBC_TM_PLAN is
'���üƻ���';

comment on column GAPSUSR.ICPS_WBC_TM_PLAN.BUSI_DATE is
'ҵ������';

comment on column GAPSUSR.ICPS_WBC_TM_PLAN.FILE_ORDER is
'�ļ����';

comment on column GAPSUSR.ICPS_WBC_TM_PLAN.ORG is
'������';

comment on column GAPSUSR.ICPS_WBC_TM_PLAN.PLAN_ID is
'���üƻ�ID';

comment on column GAPSUSR.ICPS_WBC_TM_PLAN.ACCT_NO is
'�˻����';

comment on column GAPSUSR.ICPS_WBC_TM_PLAN.ACCT_TYPE is
'�˻�����';

comment on column GAPSUSR.ICPS_WBC_TM_PLAN.LOGICAL_CARD_NO is
'�߼�����';

comment on column GAPSUSR.ICPS_WBC_TM_PLAN.PLAN_NBR is
'���üƻ���';

comment on column GAPSUSR.ICPS_WBC_TM_PLAN.PLAN_TYPE is
'���üƻ�����';

comment on column GAPSUSR.ICPS_WBC_TM_PLAN.PRODUCT_CD is
'��Ʒ����';

comment on column GAPSUSR.ICPS_WBC_TM_PLAN.REF_NBR is
'���ײο���';

comment on column GAPSUSR.ICPS_WBC_TM_PLAN.CURR_BAL is
'��ǰ���';

comment on column GAPSUSR.ICPS_WBC_TM_PLAN.BEGIN_BAL is
'�ڳ����';

comment on column GAPSUSR.ICPS_WBC_TM_PLAN.DISPUTE_AMT is
'������';

comment on column GAPSUSR.ICPS_WBC_TM_PLAN.TOT_DUE_AMT is
'��С�����';

comment on column GAPSUSR.ICPS_WBC_TM_PLAN.PLAN_ADD_DATE is
'���üƻ���������';

comment on column GAPSUSR.ICPS_WBC_TM_PLAN.PAID_OUT_DATE is
'��������';

comment on column GAPSUSR.ICPS_WBC_TM_PLAN.PAST_PRINCIPAL is
'�ѳ��˵�����';

comment on column GAPSUSR.ICPS_WBC_TM_PLAN.PAST_INTEREST is
'�ѳ��˵���Ϣ';

comment on column GAPSUSR.ICPS_WBC_TM_PLAN.PAST_CARD_FEE is
'�ѳ��˵����';

comment on column GAPSUSR.ICPS_WBC_TM_PLAN.PAST_OVRLMT_FEE is
'�ѳ��˵����޷�';

comment on column GAPSUSR.ICPS_WBC_TM_PLAN.PAST_LPC is
'�ѳ��˵����ɽ�';

comment on column GAPSUSR.ICPS_WBC_TM_PLAN.PAST_NSF_FEE is
'�ѳ��˵��ʽ����';

comment on column GAPSUSR.ICPS_WBC_TM_PLAN.PAST_TXN_FEE is
'�ѳ��˵����׷�';

comment on column GAPSUSR.ICPS_WBC_TM_PLAN.PAST_SVC_FEE is
'�ѳ��˵������';

comment on column GAPSUSR.ICPS_WBC_TM_PLAN.PAST_INS is
'�ѳ��˵����ս��';

comment on column GAPSUSR.ICPS_WBC_TM_PLAN.PAST_USER_FEE1 is
'�ѳ��˵��Զ������1';

comment on column GAPSUSR.ICPS_WBC_TM_PLAN.PAST_USER_FEE2 is
'�ѳ��˵��Զ������2';

comment on column GAPSUSR.ICPS_WBC_TM_PLAN.PAST_USER_FEE3 is
'�ѳ��˵��Զ������3';

comment on column GAPSUSR.ICPS_WBC_TM_PLAN.PAST_USER_FEE4 is
'�ѳ��˵��Զ������4';

comment on column GAPSUSR.ICPS_WBC_TM_PLAN.PAST_USER_FEE5 is
'�ѳ��˵��Զ������5';

comment on column GAPSUSR.ICPS_WBC_TM_PLAN.PAST_USER_FEE6 is
'�ѳ��˵��Զ������6';

comment on column GAPSUSR.ICPS_WBC_TM_PLAN.CTD_PRINCIPAL is
'���ڱ���';

comment on column GAPSUSR.ICPS_WBC_TM_PLAN.CTD_INTEREST is
'������Ϣ';

comment on column GAPSUSR.ICPS_WBC_TM_PLAN.CTD_CARD_FEE is
'�������';

comment on column GAPSUSR.ICPS_WBC_TM_PLAN.CTD_OVRLMT_FEE is
'���ڳ��޷�';

comment on column GAPSUSR.ICPS_WBC_TM_PLAN.CTD_LPC is
'�������ɽ�';

comment on column GAPSUSR.ICPS_WBC_TM_PLAN.CTD_NSF_FEE is
'�����ʽ����';

comment on column GAPSUSR.ICPS_WBC_TM_PLAN.CTD_SVC_FEE is
'���ڷ����';

comment on column GAPSUSR.ICPS_WBC_TM_PLAN.CTD_TXN_FEE is
'���ڽ��׷�';

comment on column GAPSUSR.ICPS_WBC_TM_PLAN.CTD_INS is
'���ڱ��ս��';

comment on column GAPSUSR.ICPS_WBC_TM_PLAN.CTD_USER_FEE1 is
'���������Զ������1';

comment on column GAPSUSR.ICPS_WBC_TM_PLAN.CTD_USER_FEE2 is
'���������Զ������2';

comment on column GAPSUSR.ICPS_WBC_TM_PLAN.CTD_USER_FEE3 is
'���������Զ������3';

comment on column GAPSUSR.ICPS_WBC_TM_PLAN.CTD_USER_FEE4 is
'���������Զ������4';

comment on column GAPSUSR.ICPS_WBC_TM_PLAN.CTD_USER_FEE5 is
'���������Զ������5';

comment on column GAPSUSR.ICPS_WBC_TM_PLAN.CTD_USER_FEE6 is
'���������Զ������6';

comment on column GAPSUSR.ICPS_WBC_TM_PLAN.CTD_AMT_DB is
'���ڽ�ǽ��';

comment on column GAPSUSR.ICPS_WBC_TM_PLAN.CTD_AMT_CR is
'���ڴ��ǽ��';

comment on column GAPSUSR.ICPS_WBC_TM_PLAN.CTD_NBR_DB is
'���ڽ�ǽ��ױ���';

comment on column GAPSUSR.ICPS_WBC_TM_PLAN.CTD_NBR_CR is
'���ڴ��ǽ��ױ���';

comment on column GAPSUSR.ICPS_WBC_TM_PLAN.NODEFBNP_INT_ACRU is
'���ӳ���Ϣ';

comment on column GAPSUSR.ICPS_WBC_TM_PLAN.BEG_DEFBNP_INT_ACRU is
'�����ۻ���ʱ��Ϣ';

comment on column GAPSUSR.ICPS_WBC_TM_PLAN.CTD_DEFBNP_INT_ACRU is
'�����ۻ���ʱ��Ϣ';

comment on column GAPSUSR.ICPS_WBC_TM_PLAN.USER_CODE1 is
'�û��Զ������1';

comment on column GAPSUSR.ICPS_WBC_TM_PLAN.USER_CODE2 is
'�û��Զ������2';

comment on column GAPSUSR.ICPS_WBC_TM_PLAN.USER_CODE3 is
'�û��Զ������3';

comment on column GAPSUSR.ICPS_WBC_TM_PLAN.USER_CODE4 is
'�û��Զ������4';

comment on column GAPSUSR.ICPS_WBC_TM_PLAN.USER_CODE5 is
'�û��Զ������5';

comment on column GAPSUSR.ICPS_WBC_TM_PLAN.USER_CODE6 is
'�û��Զ������6';

comment on column GAPSUSR.ICPS_WBC_TM_PLAN.USER_NUMBER1 is
'�û��Զ������1';

comment on column GAPSUSR.ICPS_WBC_TM_PLAN.USER_NUMBER2 is
'�û��Զ������2';

comment on column GAPSUSR.ICPS_WBC_TM_PLAN.USER_NUMBER3 is
'�û��Զ������3';

comment on column GAPSUSR.ICPS_WBC_TM_PLAN.USER_NUMBER4 is
'�û��Զ������4';

comment on column GAPSUSR.ICPS_WBC_TM_PLAN.USER_NUMBER5 is
'�û��Զ������5';

comment on column GAPSUSR.ICPS_WBC_TM_PLAN.USER_NUMBER6 is
'�û��Զ������6';

comment on column GAPSUSR.ICPS_WBC_TM_PLAN.USER_FIELD1 is
'�û��Զ�����1';

comment on column GAPSUSR.ICPS_WBC_TM_PLAN.USER_FIELD2 is
'�û��Զ�����2';

comment on column GAPSUSR.ICPS_WBC_TM_PLAN.USER_FIELD3 is
'�û��Զ�����3';

comment on column GAPSUSR.ICPS_WBC_TM_PLAN.USER_FIELD4 is
'�û��Զ�����4';

comment on column GAPSUSR.ICPS_WBC_TM_PLAN.USER_FIELD5 is
'�û��Զ�����5';

comment on column GAPSUSR.ICPS_WBC_TM_PLAN.USER_FIELD6 is
'�û��Զ�����6';

comment on column GAPSUSR.ICPS_WBC_TM_PLAN.USER_DATE1 is
'�û��Զ�������1';

comment on column GAPSUSR.ICPS_WBC_TM_PLAN.USER_DATE2 is
'�û��Զ�������2';

comment on column GAPSUSR.ICPS_WBC_TM_PLAN.USER_DATE3 is
'�û��Զ�������3';

comment on column GAPSUSR.ICPS_WBC_TM_PLAN.USER_DATE4 is
'�û��Զ�������4';

comment on column GAPSUSR.ICPS_WBC_TM_PLAN.USER_DATE5 is
'�û��Զ�������5';

comment on column GAPSUSR.ICPS_WBC_TM_PLAN.USER_DATE6 is
'�û��Զ�������6';

comment on column GAPSUSR.ICPS_WBC_TM_PLAN.USER_AMT1 is
'�û��Զ�����1';

comment on column GAPSUSR.ICPS_WBC_TM_PLAN.USER_AMT2 is
'�û��Զ�����2';

comment on column GAPSUSR.ICPS_WBC_TM_PLAN.USER_AMT3 is
'�û��Զ�����3';

comment on column GAPSUSR.ICPS_WBC_TM_PLAN.USER_AMT4 is
'�û��Զ�����4';

comment on column GAPSUSR.ICPS_WBC_TM_PLAN.USER_AMT5 is
'�û��Զ�����5';

comment on column GAPSUSR.ICPS_WBC_TM_PLAN.USER_AMT6 is
'���մ��ǿ���ŵ���';

comment on column GAPSUSR.ICPS_WBC_TM_PLAN.JPA_VERSION is
'�ֹ����汾��';

comment on column GAPSUSR.ICPS_WBC_TM_PLAN.PAST_PENALTY is
'���ڷ�Ϣ';

comment on column GAPSUSR.ICPS_WBC_TM_PLAN.CTD_PENALTY is
'���ڷ�Ϣ';

comment on column GAPSUSR.ICPS_WBC_TM_PLAN.PAST_COMPOUND is
'���ڸ���';

comment on column GAPSUSR.ICPS_WBC_TM_PLAN.CTD_COMPOUND is
'���ڸ���';

comment on column GAPSUSR.ICPS_WBC_TM_PLAN.PENALTY_ACRU is
'��Ϣ�ۼ�';

comment on column GAPSUSR.ICPS_WBC_TM_PLAN.COMPOUND_ACRU is
'�����ۼ�';

comment on column GAPSUSR.ICPS_WBC_TM_PLAN.INTEREST_RATE is
'��������';

comment on column GAPSUSR.ICPS_WBC_TM_PLAN.PENALTY_RATE is
'��Ϣ����';

comment on column GAPSUSR.ICPS_WBC_TM_PLAN.COMPOUND_RATE is
'��������';

comment on column GAPSUSR.ICPS_WBC_TM_PLAN.USE_PLAN_RATE is
'�Ƿ�ʹ��plan������';

comment on column GAPSUSR.ICPS_WBC_TM_PLAN.LAST_PMT_DATE is
'��һ��������';

comment on column GAPSUSR.ICPS_WBC_TM_PLAN.TERM is
'���ڷ�������';

comment on column GAPSUSR.ICPS_WBC_TM_PLAN.CALC_TYPE is
'�Ʒ�����';

comment on column GAPSUSR.ICPS_WBC_TM_PLAN.CALC_CYCLE is
'�Ʒ�����';

comment on column GAPSUSR.ICPS_WBC_TM_PLAN.FEE_RATE is
'����';

comment on column GAPSUSR.ICPS_WBC_TM_PLAN.LAST_FEE_DATE is
'��һ�շ���';

comment on column GAPSUSR.ICPS_WBC_TM_PLAN.NEXT_FEE_DATE is
'��һ�շ���';

comment on column GAPSUSR.ICPS_WBC_TM_PLAN.TXN_SEQ is
'������ˮ��';

comment on column GAPSUSR.ICPS_WBC_TM_PLAN.FIRST_DD_DATE is
'�״�Լ����������';

comment on column GAPSUSR.ICPS_WBC_TM_PLAN.CONSUMER_TRANS_ID is
'ҵ����ˮ��';

comment on column GAPSUSR.ICPS_WBC_TM_PLAN.SYS_TRANS_ID is
'ϵͳ������ˮ��';

comment on column GAPSUSR.ICPS_WBC_TM_PLAN.QCHANNEL_ID is
'�������';

comment on column GAPSUSR.ICPS_WBC_TM_PLAN.SUB_TERMINAL_TYPE is
'�ն�����';

comment on column GAPSUSR.ICPS_WBC_TM_PLAN.SUB_MERCH_ID is
'�����̻�����';

comment on column GAPSUSR.ICPS_WBC_TM_PLAN.SUB_MERCH_NAME is
'�����̻�����';

comment on column GAPSUSR.ICPS_WBC_TM_PLAN.WARES_DESC is
'��Ʒ��Ϣ';

comment on column GAPSUSR.ICPS_WBC_TM_PLAN.LAST_MODIFIED_DATETIME is
'�޸�ʱ��';

comment on column GAPSUSR.ICPS_WBC_TM_PLAN.ORIGINAL_AMT is
'ԭʼ���ױ���';

comment on column GAPSUSR.ICPS_WBC_TM_PLAN.INTEREST_CALC_BASE is
'��Ϣ����';

comment on column GAPSUSR.ICPS_WBC_TM_PLAN.CREATED_DATETIME is
'����ʱ��';

comment on column GAPSUSR.ICPS_WBC_TM_PLAN.IS_CHECK_FLAG is
'������˱�ʶ';

comment on column GAPSUSR.ICPS_WBC_TM_PLAN.EXTEND_PARAM1 is
'��չ1';

comment on column GAPSUSR.ICPS_WBC_TM_PLAN.EXTEND_PARAM2 is
'��չ2';

comment on column GAPSUSR.ICPS_WBC_TM_PLAN.EXTEND_PARAM3 is
'��չ3';

--==============================================================
-- Table: ICPS_WBC_TM_PSB_CHECK_INFO
--==============================================================
create table GAPSUSR.ICPS_WBC_TM_PSB_CHECK_INFO
(
   BUSI_DATE            CHARACTER(8)           not null,
   FILE_ORDER           INTEGER                not null,
   SEQ_NO               VARCHAR(32),
   ORG                  CHARACTER(12),
   APP_NO               VARCHAR(20),
   ID_TYPE              VARCHAR(2),
   ID_NO                VARCHAR(18),
   "NAME"               VARCHAR(30),
   GENDER               CHARACTER(2),
   RESULT_PERSON_ID     CHARACTER,
   RESULT_PERSON_NAME   CHARACTER,
   PHOTO_ID             VARCHAR(100),
   NATION               VARCHAR(40),
   PHOTO_MD5            VARCHAR(100),
   OLD_NAME             VARCHAR(80),
   BIRTH                CHARACTER(8),
   NATIVE_PLACE         VARCHAR(100),
   ADDRESS              VARCHAR(100),
   WORK_PLACE           VARCHAR(100),
   MARITAL_STATUS       VARCHAR(40),
   DEGREE_OF_EDUCATION  VARCHAR(100),
   ISSUED_AUTHORITY     VARCHAR(50),
   BIRTH_PLACE          VARCHAR(25),
   OCCUPATION           VARCHAR(30),
   BL0                  VARCHAR(20),
   BL1                  VARCHAR(20),
   CREATED_DATETIME     VARCHAR(14),
   LAST_MODIFIED_DATETIME VARCHAR(14),
   JPA_VERSION          INTEGER,
   PRODUCT_CD           VARCHAR(6),
   MSG_SERV_ERROR       VARCHAR(40),
   MSG_ID_ERROR         VARCHAR(40),
   FLAG                 VARCHAR(1),
   IS_CHECK_FLAG        CHARACTER,
   EXTEND_PARAM1        VARCHAR(100),
   EXTEND_PARAM2        VARCHAR(250),
   EXTEND_PARAM3        VARCHAR(40),
   constraint PK_ICPS_WBC_TM_PSB_CHECK_INFO primary key (BUSI_DATE, FILE_ORDER)
)  IN GAPS_DATA INDEX IN GAPS_INDEX ;

comment on table GAPSUSR.ICPS_WBC_TM_PSB_CHECK_INFO is
'�����˲�����Ϣ��';

comment on column GAPSUSR.ICPS_WBC_TM_PSB_CHECK_INFO.BUSI_DATE is
'ҵ������';

comment on column GAPSUSR.ICPS_WBC_TM_PSB_CHECK_INFO.FILE_ORDER is
'�ļ����';

comment on column GAPSUSR.ICPS_WBC_TM_PSB_CHECK_INFO.SEQ_NO is
'��ѯ��ˮ��';

comment on column GAPSUSR.ICPS_WBC_TM_PSB_CHECK_INFO.ORG is
'������';

comment on column GAPSUSR.ICPS_WBC_TM_PSB_CHECK_INFO.APP_NO is
'��������';

comment on column GAPSUSR.ICPS_WBC_TM_PSB_CHECK_INFO.ID_TYPE is
'֤������';

comment on column GAPSUSR.ICPS_WBC_TM_PSB_CHECK_INFO.ID_NO is
'֤������';

comment on column GAPSUSR.ICPS_WBC_TM_PSB_CHECK_INFO."NAME" is
'����';

comment on column GAPSUSR.ICPS_WBC_TM_PSB_CHECK_INFO.GENDER is
'�Ա�';

comment on column GAPSUSR.ICPS_WBC_TM_PSB_CHECK_INFO.RESULT_PERSON_ID is
'֤������˲���';

comment on column GAPSUSR.ICPS_WBC_TM_PSB_CHECK_INFO.RESULT_PERSON_NAME is
'�����˲���';

comment on column GAPSUSR.ICPS_WBC_TM_PSB_CHECK_INFO.PHOTO_ID is
'��Ƭ�ļ�id';

comment on column GAPSUSR.ICPS_WBC_TM_PSB_CHECK_INFO.NATION is
'����';

comment on column GAPSUSR.ICPS_WBC_TM_PSB_CHECK_INFO.PHOTO_MD5 is
'��Ƭmd5ֵ';

comment on column GAPSUSR.ICPS_WBC_TM_PSB_CHECK_INFO.OLD_NAME is
'������';

comment on column GAPSUSR.ICPS_WBC_TM_PSB_CHECK_INFO.BIRTH is
'��������';

comment on column GAPSUSR.ICPS_WBC_TM_PSB_CHECK_INFO.NATIVE_PLACE is
'����ʡ���أ�����';

comment on column GAPSUSR.ICPS_WBC_TM_PSB_CHECK_INFO.ADDRESS is
'סַ';

comment on column GAPSUSR.ICPS_WBC_TM_PSB_CHECK_INFO.WORK_PLACE is
'������';

comment on column GAPSUSR.ICPS_WBC_TM_PSB_CHECK_INFO.MARITAL_STATUS is
'����״��';

comment on column GAPSUSR.ICPS_WBC_TM_PSB_CHECK_INFO.DEGREE_OF_EDUCATION is
'�Ļ��̶�';

comment on column GAPSUSR.ICPS_WBC_TM_PSB_CHECK_INFO.ISSUED_AUTHORITY is
'ǩ������';

comment on column GAPSUSR.ICPS_WBC_TM_PSB_CHECK_INFO.BIRTH_PLACE is
'������';

comment on column GAPSUSR.ICPS_WBC_TM_PSB_CHECK_INFO.OCCUPATION is
'ְҵ';

comment on column GAPSUSR.ICPS_WBC_TM_PSB_CHECK_INFO.BL0 is
'����״̬';

comment on column GAPSUSR.ICPS_WBC_TM_PSB_CHECK_INFO.BL1 is
'Υ��״̬';

comment on column GAPSUSR.ICPS_WBC_TM_PSB_CHECK_INFO.CREATED_DATETIME is
'����ʱ��';

comment on column GAPSUSR.ICPS_WBC_TM_PSB_CHECK_INFO.LAST_MODIFIED_DATETIME is
'����޸�ʱ��';

comment on column GAPSUSR.ICPS_WBC_TM_PSB_CHECK_INFO.JPA_VERSION is
'�ֹ���';

comment on column GAPSUSR.ICPS_WBC_TM_PSB_CHECK_INFO.PRODUCT_CD is
'��Ʒ���';

comment on column GAPSUSR.ICPS_WBC_TM_PSB_CHECK_INFO.MSG_SERV_ERROR is
'�����쳣����';

comment on column GAPSUSR.ICPS_WBC_TM_PSB_CHECK_INFO.MSG_ID_ERROR is
'��ѯ�������';

comment on column GAPSUSR.ICPS_WBC_TM_PSB_CHECK_INFO.FLAG is
'�����ȡ����';

comment on column GAPSUSR.ICPS_WBC_TM_PSB_CHECK_INFO.IS_CHECK_FLAG is
'������˱�ʶ';

comment on column GAPSUSR.ICPS_WBC_TM_PSB_CHECK_INFO.EXTEND_PARAM1 is
'��չ1';

comment on column GAPSUSR.ICPS_WBC_TM_PSB_CHECK_INFO.EXTEND_PARAM2 is
'��չ2';

comment on column GAPSUSR.ICPS_WBC_TM_PSB_CHECK_INFO.EXTEND_PARAM3 is
'��չ3';

--==============================================================
-- Table: ICPS_WBC_TM_PSB_PERSONAL_INFO
--==============================================================
create table GAPSUSR.ICPS_WBC_TM_PSB_PERSONAL_INFO
(
   BUSI_DATE            CHARACTER(8)           not null,
   FILE_ORDER           INTEGER                not null,
   ID                   INTEGER,
   APP_NO               VARCHAR(20),
   CERTI_TYPE           CHARACTER,
   CERTI_NO             VARCHAR(18),
   "NAME"               VARCHAR(90),
   SEX                  CHARACTER,
   BIRTH_DATE           VARCHAR(8),
   MARRYSTATE           VARCHAR(2),
   MOBILE               VARCHAR(20),
   HOMEPHONE            VARCHAR(30),
   COMPPHONE            VARCHAR(30),
   QUALIFICATION        VARCHAR(2),
   DEGREE               VARCHAR(2),
   ADDRESS              VARCHAR(700),
   RESIDE_ADDR          VARCHAR(700),
   MATE_CERTP           CHARACTER,
   MATE_CERNO           VARCHAR(18),
   MATE_NAME            VARCHAR(30),
   MATE_CORP            VARCHAR(500),
   MATE_PHONE           VARCHAR(30),
   ADDR                 VARCHAR(700),
   RESIDE_STATE         VARCHAR(2),
   COMP_NM              VARCHAR(700),
   COMP_ADDR            VARCHAR(700),
   PROFESS              VARCHAR(2),
   COMP_TRADE           VARCHAR(2),
   BUSINESS             VARCHAR(2),
   TEACH_POSE           VARCHAR(2),
   WORK_DATE            VARCHAR(4),
   INFODATE             VARCHAR(8),
   CREATE_TIME          VARCHAR(14),
   PSB_QUERY_DATE       VARCHAR(8),
   REPORTSN             VARCHAR(30),
   IS_CHECK_FLAG        CHARACTER,
   EXTEND_PARAM1        VARCHAR(100),
   EXTEND_PARAM2        VARCHAR(250),
   EXTEND_PARAM3        VARCHAR(40),
   constraint PK_ICPS_WBC_TM_PSB_PERSONAL_INFO primary key (BUSI_DATE, FILE_ORDER)
)  IN GAPS_DATA INDEX IN GAPS_INDEX ;

comment on table GAPSUSR.ICPS_WBC_TM_PSB_PERSONAL_INFO is
'�����Ϣ';

comment on column GAPSUSR.ICPS_WBC_TM_PSB_PERSONAL_INFO.BUSI_DATE is
'ҵ������';

comment on column GAPSUSR.ICPS_WBC_TM_PSB_PERSONAL_INFO.FILE_ORDER is
'�ļ����';

comment on column GAPSUSR.ICPS_WBC_TM_PSB_PERSONAL_INFO.ID is
'ID';

comment on column GAPSUSR.ICPS_WBC_TM_PSB_PERSONAL_INFO.APP_NO is
'��������';

comment on column GAPSUSR.ICPS_WBC_TM_PSB_PERSONAL_INFO.CERTI_TYPE is
'֤������';

comment on column GAPSUSR.ICPS_WBC_TM_PSB_PERSONAL_INFO.CERTI_NO is
'���֤��';

comment on column GAPSUSR.ICPS_WBC_TM_PSB_PERSONAL_INFO."NAME" is
'����';

comment on column GAPSUSR.ICPS_WBC_TM_PSB_PERSONAL_INFO.SEX is
'�Ա�';

comment on column GAPSUSR.ICPS_WBC_TM_PSB_PERSONAL_INFO.BIRTH_DATE is
'��������';

comment on column GAPSUSR.ICPS_WBC_TM_PSB_PERSONAL_INFO.MARRYSTATE is
'����״��';

comment on column GAPSUSR.ICPS_WBC_TM_PSB_PERSONAL_INFO.MOBILE is
'�ֻ�����';

comment on column GAPSUSR.ICPS_WBC_TM_PSB_PERSONAL_INFO.HOMEPHONE is
'��ͥ�绰';

comment on column GAPSUSR.ICPS_WBC_TM_PSB_PERSONAL_INFO.COMPPHONE is
'��λ�绰';

comment on column GAPSUSR.ICPS_WBC_TM_PSB_PERSONAL_INFO.QUALIFICATION is
'ѧ��';

comment on column GAPSUSR.ICPS_WBC_TM_PSB_PERSONAL_INFO.DEGREE is
'ѧλ';

comment on column GAPSUSR.ICPS_WBC_TM_PSB_PERSONAL_INFO.ADDRESS is
'ͨѶ��ַ';

comment on column GAPSUSR.ICPS_WBC_TM_PSB_PERSONAL_INFO.RESIDE_ADDR is
'������ַ';

comment on column GAPSUSR.ICPS_WBC_TM_PSB_PERSONAL_INFO.MATE_CERTP is
'��ż֤������';

comment on column GAPSUSR.ICPS_WBC_TM_PSB_PERSONAL_INFO.MATE_CERNO is
'��ż֤������';

comment on column GAPSUSR.ICPS_WBC_TM_PSB_PERSONAL_INFO.MATE_NAME is
'��ż����';

comment on column GAPSUSR.ICPS_WBC_TM_PSB_PERSONAL_INFO.MATE_CORP is
'��ż������λ';

comment on column GAPSUSR.ICPS_WBC_TM_PSB_PERSONAL_INFO.MATE_PHONE is
'��ż��ϵ�绰';

comment on column GAPSUSR.ICPS_WBC_TM_PSB_PERSONAL_INFO.ADDR is
'��ס��ַ';

comment on column GAPSUSR.ICPS_WBC_TM_PSB_PERSONAL_INFO.RESIDE_STATE is
'��ס״��';

comment on column GAPSUSR.ICPS_WBC_TM_PSB_PERSONAL_INFO.COMP_NM is
'������λ';

comment on column GAPSUSR.ICPS_WBC_TM_PSB_PERSONAL_INFO.COMP_ADDR is
'��λ��ַ';

comment on column GAPSUSR.ICPS_WBC_TM_PSB_PERSONAL_INFO.PROFESS is
'ְҵ';

comment on column GAPSUSR.ICPS_WBC_TM_PSB_PERSONAL_INFO.COMP_TRADE is
'��ҵ';

comment on column GAPSUSR.ICPS_WBC_TM_PSB_PERSONAL_INFO.BUSINESS is
'ְ��';

comment on column GAPSUSR.ICPS_WBC_TM_PSB_PERSONAL_INFO.TEACH_POSE is
'ְ��';

comment on column GAPSUSR.ICPS_WBC_TM_PSB_PERSONAL_INFO.WORK_DATE is
'����λ������ʼ���';

comment on column GAPSUSR.ICPS_WBC_TM_PSB_PERSONAL_INFO.INFODATE is
'��Ϣ��������';

comment on column GAPSUSR.ICPS_WBC_TM_PSB_PERSONAL_INFO.CREATE_TIME is
'����ʱ��';

comment on column GAPSUSR.ICPS_WBC_TM_PSB_PERSONAL_INFO.PSB_QUERY_DATE is
'���б����ѯʱ��';

comment on column GAPSUSR.ICPS_WBC_TM_PSB_PERSONAL_INFO.REPORTSN is
'���б�����';

comment on column GAPSUSR.ICPS_WBC_TM_PSB_PERSONAL_INFO.IS_CHECK_FLAG is
'������˱�ʶ';

comment on column GAPSUSR.ICPS_WBC_TM_PSB_PERSONAL_INFO.EXTEND_PARAM1 is
'��չ1';

comment on column GAPSUSR.ICPS_WBC_TM_PSB_PERSONAL_INFO.EXTEND_PARAM2 is
'��չ2';

comment on column GAPSUSR.ICPS_WBC_TM_PSB_PERSONAL_INFO.EXTEND_PARAM3 is
'��չ3';

--==============================================================
-- Table: ICPS_WBC_TM_SCHEDULE
--==============================================================
create table GAPSUSR.ICPS_WBC_TM_SCHEDULE
(
   BUSI_DATE            CHARACTER(8)           not null,
   FILE_ORDER           INTEGER                not null,
   SCHEDULE_ID          VARCHAR(20),
   LOAN_ID              VARCHAR(20),
   ORG                  CHARACTER(12),
   ACCT_NO              VARCHAR(20),
   ACCT_TYPE            CHARACTER,
   LOGICAL_CARD_NO      VARCHAR(19),
   CARD_NO              VARCHAR(19),
   LOAN_INIT_PRIN       DECIMAL(15,2),
   LOAN_INIT_TERM       INTEGER,
   CURR_TERM            INTEGER,
   LOAN_TERM_PRIN       DECIMAL(15,2),
   LOAN_TERM_FEE1       DECIMAL(15,2),
   LOAN_TERM_INTEREST   DECIMAL(15,2),
   LOAN_PMT_DUE_DATE    VARCHAR(8),
   LOAN_GRACE_DATE      VARCHAR(8),
   LAST_MODIFIED_DATETIME VARCHAR(14),
   START_DATE           VARCHAR(8),
   SCHEDULE_ACTION      CHARACTER,
   PRIN_PAID            DECIMAL(15,2),
   INT_PAID             DECIMAL(15,2),
   PENALTY_PAID         DECIMAL(15,2),
   COMPOUND_PAID        DECIMAL(15,2),
   FEE_PAID             DECIMAL(15,2),
   LATE_CHARGE_PAID     DECIMAL(15,2),
   ADV_PMT_FEE_PAID     DECIMAL(15,2),
   PAID_OUT_DATE        VARCHAR(8),
   IS_CHECK_FLAG        CHARACTER,
   EXTEND_PARAM1        VARCHAR(100),
   EXTEND_PARAM2        VARCHAR(250),
   EXTEND_PARAM3        VARCHAR(40),
   constraint PK_ICPS_WBC_TM_SCHEDULE primary key (BUSI_DATE, FILE_ORDER)
)  IN GAPS_DATA INDEX IN GAPS_INDEX ;

comment on table GAPSUSR.ICPS_WBC_TM_SCHEDULE is
'��������';

comment on column GAPSUSR.ICPS_WBC_TM_SCHEDULE.BUSI_DATE is
'ҵ������';

comment on column GAPSUSR.ICPS_WBC_TM_SCHEDULE.FILE_ORDER is
'�ļ����';

comment on column GAPSUSR.ICPS_WBC_TM_SCHEDULE.SCHEDULE_ID is
'�����ID';

comment on column GAPSUSR.ICPS_WBC_TM_SCHEDULE.LOAN_ID is
'���ڼƻ�ID';

comment on column GAPSUSR.ICPS_WBC_TM_SCHEDULE.ORG is
'������';

comment on column GAPSUSR.ICPS_WBC_TM_SCHEDULE.ACCT_NO is
'�˻����';

comment on column GAPSUSR.ICPS_WBC_TM_SCHEDULE.ACCT_TYPE is
'�˻�����';

comment on column GAPSUSR.ICPS_WBC_TM_SCHEDULE.LOGICAL_CARD_NO is
'�߼�����';

comment on column GAPSUSR.ICPS_WBC_TM_SCHEDULE.CARD_NO is
'����';

comment on column GAPSUSR.ICPS_WBC_TM_SCHEDULE.LOAN_INIT_PRIN is
'�����ܱ���';

comment on column GAPSUSR.ICPS_WBC_TM_SCHEDULE.LOAN_INIT_TERM is
'����������';

comment on column GAPSUSR.ICPS_WBC_TM_SCHEDULE.CURR_TERM is
'��ǰ����';

comment on column GAPSUSR.ICPS_WBC_TM_SCHEDULE.LOAN_TERM_PRIN is
'Ӧ������';

comment on column GAPSUSR.ICPS_WBC_TM_SCHEDULE.LOAN_TERM_FEE1 is
'Ӧ������';

comment on column GAPSUSR.ICPS_WBC_TM_SCHEDULE.LOAN_TERM_INTEREST is
'Ӧ����Ϣ';

comment on column GAPSUSR.ICPS_WBC_TM_SCHEDULE.LOAN_PMT_DUE_DATE is
'����ڻ�������';

comment on column GAPSUSR.ICPS_WBC_TM_SCHEDULE.LOAN_GRACE_DATE is
'������';

comment on column GAPSUSR.ICPS_WBC_TM_SCHEDULE.LAST_MODIFIED_DATETIME is
'�޸�ʱ��';

comment on column GAPSUSR.ICPS_WBC_TM_SCHEDULE.START_DATE is
'��Ϣ��';

comment on column GAPSUSR.ICPS_WBC_TM_SCHEDULE.SCHEDULE_ACTION is
'����ƻ���������';

comment on column GAPSUSR.ICPS_WBC_TM_SCHEDULE.PRIN_PAID is
'�ѳ�������';

comment on column GAPSUSR.ICPS_WBC_TM_SCHEDULE.INT_PAID is
'�ѳ�����Ϣ';

comment on column GAPSUSR.ICPS_WBC_TM_SCHEDULE.PENALTY_PAID is
'�ѳ�����Ϣ';

comment on column GAPSUSR.ICPS_WBC_TM_SCHEDULE.COMPOUND_PAID is
'�ѳ�������';

comment on column GAPSUSR.ICPS_WBC_TM_SCHEDULE.FEE_PAID is
'�ѳ�������';

comment on column GAPSUSR.ICPS_WBC_TM_SCHEDULE.LATE_CHARGE_PAID is
'�ѳ������ɽ�';

comment on column GAPSUSR.ICPS_WBC_TM_SCHEDULE.ADV_PMT_FEE_PAID is
'�ѳ�����ǰ����������';

comment on column GAPSUSR.ICPS_WBC_TM_SCHEDULE.PAID_OUT_DATE is
'��������';

comment on column GAPSUSR.ICPS_WBC_TM_SCHEDULE.IS_CHECK_FLAG is
'������˱�ʶ';

comment on column GAPSUSR.ICPS_WBC_TM_SCHEDULE.EXTEND_PARAM1 is
'��չ1';

comment on column GAPSUSR.ICPS_WBC_TM_SCHEDULE.EXTEND_PARAM2 is
'��չ2';

comment on column GAPSUSR.ICPS_WBC_TM_SCHEDULE.EXTEND_PARAM3 is
'��չ3';

--==============================================================
-- Table: ICPS_WBC_TM_TXN_CD
--==============================================================
create table GAPSUSR.ICPS_WBC_TM_TXN_CD
(
   BUSI_DATE            CHARACTER(8)           not null,
   FILE_ORDER           INTEGER                not null,
   FLOW_NO              VARCHAR(20),
   ORG                  CHARACTER(12),
   TXN_CODE             CHARACTER(4),
   TXN_DESC             VARCHAR(80),
   TXN_CLASS            CHARACTER,
   BNP                  VARCHAR(30),
   IS_CHECK_FLAG        CHARACTER,
   EXTEND_PARAM1        VARCHAR(100),
   EXTEND_PARAM2        VARCHAR(250),
   EXTEND_PARAM3        VARCHAR(40),
   constraint PK_ICPS_WBC_TM_TXN_CD primary key (BUSI_DATE, FILE_ORDER)
)  IN GAPS_DATA INDEX IN GAPS_INDEX ;

comment on table GAPSUSR.ICPS_WBC_TM_TXN_CD is
'�����������ã�';

comment on column GAPSUSR.ICPS_WBC_TM_TXN_CD.BUSI_DATE is
'ҵ������';

comment on column GAPSUSR.ICPS_WBC_TM_TXN_CD.FILE_ORDER is
'�ļ����';

comment on column GAPSUSR.ICPS_WBC_TM_TXN_CD.FLOW_NO is
'FLOW_NO';

comment on column GAPSUSR.ICPS_WBC_TM_TXN_CD.ORG is
'������';

comment on column GAPSUSR.ICPS_WBC_TM_TXN_CD.TXN_CODE is
'������';

comment on column GAPSUSR.ICPS_WBC_TM_TXN_CD.TXN_DESC is
'��������';

comment on column GAPSUSR.ICPS_WBC_TM_TXN_CD.TXN_CLASS is
'TXN_CLASS';

comment on column GAPSUSR.ICPS_WBC_TM_TXN_CD.BNP is
'���ɷ�';

comment on column GAPSUSR.ICPS_WBC_TM_TXN_CD.IS_CHECK_FLAG is
'������˱�ʶ';

comment on column GAPSUSR.ICPS_WBC_TM_TXN_CD.EXTEND_PARAM1 is
'��չ1';

comment on column GAPSUSR.ICPS_WBC_TM_TXN_CD.EXTEND_PARAM2 is
'��չ2';

comment on column GAPSUSR.ICPS_WBC_TM_TXN_CD.EXTEND_PARAM3 is
'��չ3';

--==============================================================
-- Table: ICPS_WBC_TT_TXN_POST
--==============================================================
create table GAPSUSR.ICPS_WBC_TT_TXN_POST
(
   BUSI_DATE            CHARACTER(8)           not null,
   FILE_ORDER           INTEGER                not null,
   ORG                  CHARACTER(12),
   TXN_SEQ              VARCHAR(20),
   ACCT_NO              VARCHAR(20),
   ACCT_TYPE            CHARACTER,
   CARD_NO              VARCHAR(19),
   LOGICAL_CARD_NO      VARCHAR(19),
   BSC_LOGICCARD_NO     VARCHAR(19),
   PRODUCT_CD           CHARACTER(6),
   TXN_DATE             VARCHAR(8),
   TXN_TIME             VARCHAR(14),
   POST_TXN_TYPE        CHARACTER,
   TXN_CODE             CHARACTER(4),
   DB_CR_IND            CHARACTER,
   TXN_AMT              DECIMAL(15,2),
   POST_AMT             DECIMAL(15,2),
   POST_DATE            VARCHAR(8),
   AUTH_CODE            CHARACTER(6),
   CARD_BLOCK_CODE      VARCHAR(27),
   TXN_CURR_CD          CHARACTER(3),
   POST_CURR_CD         CHARACTER(3),
   ORIG_TRANS_DATE      VARCHAR(8),
   PLAN_NBR             CHARACTER(6),
   REF_NBR              VARCHAR(23),
   TXN_DESC             VARCHAR(80),
   TXN_SHORT_DESC       VARCHAR(80),
   POINT                DECIMAL(13),
   POSTING_FLAG         CHARACTER(3),
   PRE_POSTING_FLAG     CHARACTER(3),
   REL_PMT_AMT          DECIMAL(15,2),
   ORIG_PMT_AMT         DECIMAL(15,2),
   ACQ_BRANCH_ID        CHARACTER(9),
   ACQ_TERMINAL_ID      VARCHAR(8),
   ACQ_ACCEPTOR_ID      VARCHAR(15),
   ACQ_NAME_ADDR        VARCHAR(40),
   MCC                  CHARACTER(4),
   INPUT_TXN_CODE       CHARACTER(4),
   INPUT_TXN_AMT        DECIMAL(15,2),
   INPUT_SETT_AMT       DECIMAL(15,2),
   INTERCHANGE_FEE      DECIMAL(15,2),
   FEE_PAYOUT           DECIMAL(15,2),
   FEE_PROFIT           DECIMAL(15,2),
   LOAN_ISSUE_PROFIT    DECIMAL(15,2),
   STMT_DATE            VARCHAR(8),
   VOUCHER_NO           VARCHAR(7),
   JPA_VERSION          INTEGER,
   TERM                 INTEGER,
   CONSUMER_TRANS_ID    VARCHAR(32),
   SYS_TRANS_ID         VARCHAR(32),
   QCHANNEL_ID          VARCHAR(15),
   SUB_TERMINAL_TYPE    VARCHAR(15),
   SUB_MERCH_ID         VARCHAR(40),
   SUB_MERCH_NAME       VARCHAR(60),
   WARES_DESC           VARCHAR(60),
   LAST_MODIFIED_DATETIME VARCHAR(14),
   PAID_STMT_DATE       VARCHAR(8),
   REPAY_AMT            DECIMAL(15,2),
   COUNTER_ACCT         VARCHAR(32),
   COUNTER_NAME         VARCHAR(120),
   COUNTER_BRNO         VARCHAR(14),
   COUNTER_BRNAME       VARCHAR(180),
   IS_CHECK_FLAG        CHARACTER,
   EXTEND_PARAM1        VARCHAR(100),
   EXTEND_PARAM2        VARCHAR(250),
   EXTEND_PARAM3        VARCHAR(40),
   constraint PK_ICPS_WBC_TT_TXN_POST primary key (BUSI_DATE, FILE_ORDER)
)  IN GAPS_DATA INDEX IN GAPS_INDEX ;

comment on table GAPSUSR.ICPS_WBC_TT_TXN_POST is
'�������˽��ױ�';

comment on column GAPSUSR.ICPS_WBC_TT_TXN_POST.BUSI_DATE is
'ҵ������';

comment on column GAPSUSR.ICPS_WBC_TT_TXN_POST.FILE_ORDER is
'�ļ����';

comment on column GAPSUSR.ICPS_WBC_TT_TXN_POST.ORG is
'������';

comment on column GAPSUSR.ICPS_WBC_TT_TXN_POST.TXN_SEQ is
'������ˮ��';

comment on column GAPSUSR.ICPS_WBC_TT_TXN_POST.ACCT_NO is
'�˻����';

comment on column GAPSUSR.ICPS_WBC_TT_TXN_POST.ACCT_TYPE is
'�˻�����';

comment on column GAPSUSR.ICPS_WBC_TT_TXN_POST.CARD_NO is
'����';

comment on column GAPSUSR.ICPS_WBC_TT_TXN_POST.LOGICAL_CARD_NO is
'�߼�����';

comment on column GAPSUSR.ICPS_WBC_TT_TXN_POST.BSC_LOGICCARD_NO is
'�߼�����������';

comment on column GAPSUSR.ICPS_WBC_TT_TXN_POST.PRODUCT_CD is
'��Ʒ����';

comment on column GAPSUSR.ICPS_WBC_TT_TXN_POST.TXN_DATE is
'��������';

comment on column GAPSUSR.ICPS_WBC_TT_TXN_POST.TXN_TIME is
'����ʱ��';

comment on column GAPSUSR.ICPS_WBC_TT_TXN_POST.POST_TXN_TYPE is
'���˽�������';

comment on column GAPSUSR.ICPS_WBC_TT_TXN_POST.TXN_CODE is
'������';

comment on column GAPSUSR.ICPS_WBC_TT_TXN_POST.DB_CR_IND is
'�����־';

comment on column GAPSUSR.ICPS_WBC_TT_TXN_POST.TXN_AMT is
'���׽��';

comment on column GAPSUSR.ICPS_WBC_TT_TXN_POST.POST_AMT is
'���˱��ֽ��';

comment on column GAPSUSR.ICPS_WBC_TT_TXN_POST.POST_DATE is
'��������';

comment on column GAPSUSR.ICPS_WBC_TT_TXN_POST.AUTH_CODE is
'��Ȩ��';

comment on column GAPSUSR.ICPS_WBC_TT_TXN_POST.CARD_BLOCK_CODE is
'��Ƭ������';

comment on column GAPSUSR.ICPS_WBC_TT_TXN_POST.TXN_CURR_CD is
'���ױ��ִ���';

comment on column GAPSUSR.ICPS_WBC_TT_TXN_POST.POST_CURR_CD is
'���˱��ִ���';

comment on column GAPSUSR.ICPS_WBC_TT_TXN_POST.ORIG_TRANS_DATE is
'ԭʼ��������';

comment on column GAPSUSR.ICPS_WBC_TT_TXN_POST.PLAN_NBR is
'���üƻ���';

comment on column GAPSUSR.ICPS_WBC_TT_TXN_POST.REF_NBR is
'���ײο���';

comment on column GAPSUSR.ICPS_WBC_TT_TXN_POST.TXN_DESC is
'��������';

comment on column GAPSUSR.ICPS_WBC_TT_TXN_POST.TXN_SHORT_DESC is
'�˵���������';

comment on column GAPSUSR.ICPS_WBC_TT_TXN_POST.POINT is
'������ֵ';

comment on column GAPSUSR.ICPS_WBC_TT_TXN_POST.POSTING_FLAG is
'���˽����ʾ��';

comment on column GAPSUSR.ICPS_WBC_TT_TXN_POST.PRE_POSTING_FLAG is
'�������˽����ʾ��';

comment on column GAPSUSR.ICPS_WBC_TT_TXN_POST.REL_PMT_AMT is
'��˾��������';

comment on column GAPSUSR.ICPS_WBC_TT_TXN_POST.ORIG_PMT_AMT is
'�����ԭʼ���';

comment on column GAPSUSR.ICPS_WBC_TT_TXN_POST.ACQ_BRANCH_ID is
'������д���';

comment on column GAPSUSR.ICPS_WBC_TT_TXN_POST.ACQ_TERMINAL_ID is
'��������ն˱�ʶ��';

comment on column GAPSUSR.ICPS_WBC_TT_TXN_POST.ACQ_ACCEPTOR_ID is
'�ܿ�����ʶ��';

comment on column GAPSUSR.ICPS_WBC_TT_TXN_POST.ACQ_NAME_ADDR is
'����������Ƶ�ַ';

comment on column GAPSUSR.ICPS_WBC_TT_TXN_POST.MCC is
'�̻�������';

comment on column GAPSUSR.ICPS_WBC_TT_TXN_POST.INPUT_TXN_CODE is
'ԭ���׽�����';

comment on column GAPSUSR.ICPS_WBC_TT_TXN_POST.INPUT_TXN_AMT is
'ԭ���׽��׽��';

comment on column GAPSUSR.ICPS_WBC_TT_TXN_POST.INPUT_SETT_AMT is
'ԭ����������';

comment on column GAPSUSR.ICPS_WBC_TT_TXN_POST.INTERCHANGE_FEE is
'ԭ���׻���ת����';

comment on column GAPSUSR.ICPS_WBC_TT_TXN_POST.FEE_PAYOUT is
'������Ӧ��������';

comment on column GAPSUSR.ICPS_WBC_TT_TXN_POST.FEE_PROFIT is
'������Ӧ��������';

comment on column GAPSUSR.ICPS_WBC_TT_TXN_POST.LOAN_ISSUE_PROFIT is
'���ڽ��׷���������';

comment on column GAPSUSR.ICPS_WBC_TT_TXN_POST.STMT_DATE is
'�˵�����';

comment on column GAPSUSR.ICPS_WBC_TT_TXN_POST.VOUCHER_NO is
'���۵�ƾ֤��';

comment on column GAPSUSR.ICPS_WBC_TT_TXN_POST.JPA_VERSION is
'�ֹ����汾��';

comment on column GAPSUSR.ICPS_WBC_TT_TXN_POST.TERM is
'���ڷ�������';

comment on column GAPSUSR.ICPS_WBC_TT_TXN_POST.CONSUMER_TRANS_ID is
'ҵ����ˮ��';

comment on column GAPSUSR.ICPS_WBC_TT_TXN_POST.SYS_TRANS_ID is
'ϵͳ������ˮ��';

comment on column GAPSUSR.ICPS_WBC_TT_TXN_POST.QCHANNEL_ID is
'�������';

comment on column GAPSUSR.ICPS_WBC_TT_TXN_POST.SUB_TERMINAL_TYPE is
'�ն�����';

comment on column GAPSUSR.ICPS_WBC_TT_TXN_POST.SUB_MERCH_ID is
'�����̻�����';

comment on column GAPSUSR.ICPS_WBC_TT_TXN_POST.SUB_MERCH_NAME is
'�����̻�����';

comment on column GAPSUSR.ICPS_WBC_TT_TXN_POST.WARES_DESC is
'��Ʒ��Ϣ';

comment on column GAPSUSR.ICPS_WBC_TT_TXN_POST.LAST_MODIFIED_DATETIME is
'�޸�ʱ��';

comment on column GAPSUSR.ICPS_WBC_TT_TXN_POST.PAID_STMT_DATE is
'�����˵���';

comment on column GAPSUSR.ICPS_WBC_TT_TXN_POST.REPAY_AMT is
'Ӧ�����';

comment on column GAPSUSR.ICPS_WBC_TT_TXN_POST.COUNTER_ACCT is
'���ַ��˻�';

comment on column GAPSUSR.ICPS_WBC_TT_TXN_POST.COUNTER_NAME is
'���ַ�����';

comment on column GAPSUSR.ICPS_WBC_TT_TXN_POST.COUNTER_BRNO is
'���ַ��к�';

comment on column GAPSUSR.ICPS_WBC_TT_TXN_POST.COUNTER_BRNAME is
'���ַ�����';

comment on column GAPSUSR.ICPS_WBC_TT_TXN_POST.IS_CHECK_FLAG is
'������˱�ʶ';

comment on column GAPSUSR.ICPS_WBC_TT_TXN_POST.EXTEND_PARAM1 is
'��չ1';

comment on column GAPSUSR.ICPS_WBC_TT_TXN_POST.EXTEND_PARAM2 is
'��չ2';

comment on column GAPSUSR.ICPS_WBC_TT_TXN_POST.EXTEND_PARAM3 is
'��չ3';

