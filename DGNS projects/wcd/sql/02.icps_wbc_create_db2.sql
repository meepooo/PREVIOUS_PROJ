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
'尾差调整表';

comment on column GAPSUSR.ICPS_WBC_BANK_GROUP_DFQ_SPLIT_DIFF.BUSI_DATE is
'业务日期';

comment on column GAPSUSR.ICPS_WBC_BANK_GROUP_DFQ_SPLIT_DIFF.FILE_ORDER is
'文件序号';

comment on column GAPSUSR.ICPS_WBC_BANK_GROUP_DFQ_SPLIT_DIFF.PARTITION_DATE is
'批量日期';

comment on column GAPSUSR.ICPS_WBC_BANK_GROUP_DFQ_SPLIT_DIFF.PRODUCT_CD is
'产品编号';

comment on column GAPSUSR.ICPS_WBC_BANK_GROUP_DFQ_SPLIT_DIFF.ERROR_TYPE is
'异常类型';

comment on column GAPSUSR.ICPS_WBC_BANK_GROUP_DFQ_SPLIT_DIFF.BANK_GROUP_ID is
'银团编号';

comment on column GAPSUSR.ICPS_WBC_BANK_GROUP_DFQ_SPLIT_DIFF.BANK_NO is
'银行编号';

comment on column GAPSUSR.ICPS_WBC_BANK_GROUP_DFQ_SPLIT_DIFF.CONSUMER_TRANS_ID is
'业务流水号';

comment on column GAPSUSR.ICPS_WBC_BANK_GROUP_DFQ_SPLIT_DIFF.REG_TYPE is
'交易类型';

comment on column GAPSUSR.ICPS_WBC_BANK_GROUP_DFQ_SPLIT_DIFF."NAME" is
'姓名';

comment on column GAPSUSR.ICPS_WBC_BANK_GROUP_DFQ_SPLIT_DIFF.LOGICAL_CARD_NO is
'逻辑卡号';

comment on column GAPSUSR.ICPS_WBC_BANK_GROUP_DFQ_SPLIT_DIFF.BF_AMT is
'备付金清算金额';

comment on column GAPSUSR.ICPS_WBC_BANK_GROUP_DFQ_SPLIT_DIFF.ACCOUNT_AMT is
'CNC记账金额';

comment on column GAPSUSR.ICPS_WBC_BANK_GROUP_DFQ_SPLIT_DIFF.ERROR_AMT is
'应调整差额';

comment on column GAPSUSR.ICPS_WBC_BANK_GROUP_DFQ_SPLIT_DIFF.IS_CHECK_FLAG is
'参与对账标识';

comment on column GAPSUSR.ICPS_WBC_BANK_GROUP_DFQ_SPLIT_DIFF.EXTEND_PARAM1 is
'扩展1';

comment on column GAPSUSR.ICPS_WBC_BANK_GROUP_DFQ_SPLIT_DIFF.EXTEND_PARAM2 is
'扩展2';

comment on column GAPSUSR.ICPS_WBC_BANK_GROUP_DFQ_SPLIT_DIFF.EXTEND_PARAM3 is
'扩展3';

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
'微车贷备付金对账表';

comment on column ICPS_WBC_DAILY_DIFF.BUSI_TYPE is
'业务类型';

comment on column ICPS_WBC_DAILY_DIFF.CHECK_DATE is
'对账日期';

comment on column ICPS_WBC_DAILY_DIFF.CHECK_STATUS is
'对账状态';

comment on column ICPS_WBC_DAILY_DIFF.BUSI_DATE is
'业务日期';

comment on column ICPS_WBC_DAILY_DIFF.DRC_BAL is
'影子账户余额';

comment on column ICPS_WBC_DAILY_DIFF.WB_BAL is
'备付金余额';

comment on column ICPS_WBC_DAILY_DIFF.DIFF_CZ is
'冲账';

comment on column ICPS_WBC_DAILY_DIFF.DIFF_A01 is
'A01尾差';

comment on column ICPS_WBC_DAILY_DIFF.DIFF_A02 is
'A02尾差';

comment on column ICPS_WBC_DAILY_DIFF.DIFF_B01 is
'B01尾差';

comment on column ICPS_WBC_DAILY_DIFF.DIFF_C01 is
'C01尾差';

comment on column ICPS_WBC_DAILY_DIFF.DIFF_C02 is
'C02尾差';

comment on column ICPS_WBC_DAILY_DIFF.CLEARING_DAY_AMT is
'平台费';

comment on column ICPS_WBC_DAILY_DIFF.CLEAR_AMT is
'清算差额';

comment on column ICPS_WBC_DAILY_DIFF.EXTEND_PARAM1 is
'扩展1';

comment on column ICPS_WBC_DAILY_DIFF.EXTEND_PARAM2 is
'扩展2';

comment on column ICPS_WBC_DAILY_DIFF.EXTEND_PARAM3 is
'扩展3';

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
'按照合作方的账号，该账号下面的所有存款交易明细表';

comment on column GAPSUSR.ICPS_WBC_KDPL_ZHMINX.BUSI_DATE is
'业务日期';

comment on column GAPSUSR.ICPS_WBC_KDPL_ZHMINX.FILE_ORDER is
'文件序号';

comment on column GAPSUSR.ICPS_WBC_KDPL_ZHMINX.ZHANGHAO is
'负债账号';

comment on column GAPSUSR.ICPS_WBC_KDPL_ZHMINX.MXIXUHAO is
'明细序号';

comment on column GAPSUSR.ICPS_WBC_KDPL_ZHMINX.JIAOYIRQ is
'交易日期';

comment on column GAPSUSR.ICPS_WBC_KDPL_ZHMINX.KHJYMXLB is
'客户交易明细类别';

comment on column GAPSUSR.ICPS_WBC_KDPL_ZHMINX.JYYYJIGO is
'交易营业机构';

comment on column GAPSUSR.ICPS_WBC_KDPL_ZHMINX.KAIHJIGO is
'账户开户机构';

comment on column GAPSUSR.ICPS_WBC_KDPL_ZHMINX.ZHHUZWMC is
'账户名称';

comment on column GAPSUSR.ICPS_WBC_KDPL_ZHMINX.JIEDAIBZ is
'借贷标志';

comment on column GAPSUSR.ICPS_WBC_KDPL_ZHMINX.JIAOYBIZ is
'交易币种';

comment on column GAPSUSR.ICPS_WBC_KDPL_ZHMINX.CHAOHUBZ is
'账户钞汇标志';

comment on column GAPSUSR.ICPS_WBC_KDPL_ZHMINX.JIAOYIJE is
'交易金额';

comment on column GAPSUSR.ICPS_WBC_KDPL_ZHMINX.ZHANGHYE is
'账户余额';

comment on column GAPSUSR.ICPS_WBC_KDPL_ZHMINX.KAHAOOOO is
'卡号';

comment on column GAPSUSR.ICPS_WBC_KDPL_ZHMINX.KEHUZHAO is
'客户账号';

comment on column GAPSUSR.ICPS_WBC_KDPL_ZHMINX.ZHHAOXUH is
'子账户序号';

comment on column GAPSUSR.ICPS_WBC_KDPL_ZHMINX.PNGZZLEI is
'凭证种类';

comment on column GAPSUSR.ICPS_WBC_KDPL_ZHMINX.PNGZXHAO is
'凭证号';

comment on column GAPSUSR.ICPS_WBC_KDPL_ZHMINX.ZHAIYODM is
'摘要代码';

comment on column GAPSUSR.ICPS_WBC_KDPL_ZHMINX.ZHAIYOMS is
'摘要描述';

comment on column GAPSUSR.ICPS_WBC_KDPL_ZHMINX.DUIFJGDM is
'对方金融机构';

comment on column GAPSUSR.ICPS_WBC_KDPL_ZHMINX.DUIFJGMC is
'对方金融机构名称';

comment on column GAPSUSR.ICPS_WBC_KDPL_ZHMINX.DUIFKHZH is
'对方客户账号';

comment on column GAPSUSR.ICPS_WBC_KDPL_ZHMINX.DUIFMINC is
'对方户名';

comment on column GAPSUSR.ICPS_WBC_KDPL_ZHMINX.DUIFBEZH is
'对方备注';

comment on column GAPSUSR.ICPS_WBC_KDPL_ZHMINX.BEIZHUUU is
'备注';

comment on column GAPSUSR.ICPS_WBC_KDPL_ZHMINX.QIXIRIQI is
'起息日期';

comment on column GAPSUSR.ICPS_WBC_KDPL_ZHMINX.QDAOLEIX is
'交易渠道';

comment on column GAPSUSR.ICPS_WBC_KDPL_ZHMINX.WAIBCLMA is
'对账代码';

comment on column GAPSUSR.ICPS_WBC_KDPL_ZHMINX.NBJOYIMA is
'内部交易码';

comment on column GAPSUSR.ICPS_WBC_KDPL_ZHMINX.XIANZZBZ is
'现转标志';

comment on column GAPSUSR.ICPS_WBC_KDPL_ZHMINX.GUIYLIUS is
'柜员流水(即交易流水)';

comment on column GAPSUSR.ICPS_WBC_KDPL_ZHMINX.CAOZGUIY is
'操作柜员';

comment on column GAPSUSR.ICPS_WBC_KDPL_ZHMINX.ZHUJRIQI is
'主机日期';

comment on column GAPSUSR.ICPS_WBC_KDPL_ZHMINX.ZJYILUSH is
'主交易流水';

comment on column GAPSUSR.ICPS_WBC_KDPL_ZHMINX.YEWULUSH is
'业务流水';

comment on column GAPSUSR.ICPS_WBC_KDPL_ZHMINX.JIAOYISJ is
'交易时间';

comment on column GAPSUSR.ICPS_WBC_KDPL_ZHMINX.BCHONGBZ is
'交易明细状态';

comment on column GAPSUSR.ICPS_WBC_KDPL_ZHMINX.CUOZRIQI is
'原错账日期';

comment on column GAPSUSR.ICPS_WBC_KDPL_ZHMINX.CUOZLIUS is
'原错账交易流水';

comment on column GAPSUSR.ICPS_WBC_KDPL_ZHMINX.YSZJYLSH is
'原始主交易流水';

comment on column GAPSUSR.ICPS_WBC_KDPL_ZHMINX.YSYEWUSH is
'原始业务流水';

comment on column GAPSUSR.ICPS_WBC_KDPL_ZHMINX.CZCZFLEI is
'冲正冲账分类';

comment on column GAPSUSR.ICPS_WBC_KDPL_ZHMINX.MOZHANBZ is
'抹账标志';

comment on column GAPSUSR.ICPS_WBC_KDPL_ZHMINX.TOKENNNN is
'token';

comment on column GAPSUSR.ICPS_WBC_KDPL_ZHMINX.DSFTOKEN is
'对手方token';

comment on column GAPSUSR.ICPS_WBC_KDPL_ZHMINX.LILVLILV is
'利率';

comment on column GAPSUSR.ICPS_WBC_KDPL_ZHMINX.JIOYSHIJ is
'交易事件';

comment on column GAPSUSR.ICPS_WBC_KDPL_ZHMINX.HUIDXHAO is
'回单序号';

comment on column GAPSUSR.ICPS_WBC_KDPL_ZHMINX.FARENDMA is
'法人代码';

comment on column GAPSUSR.ICPS_WBC_KDPL_ZHMINX.WEIHGUIY is
'维护柜员';

comment on column GAPSUSR.ICPS_WBC_KDPL_ZHMINX.WEIHJIGO is
'维护机构';

comment on column GAPSUSR.ICPS_WBC_KDPL_ZHMINX.WEIHRIQI is
'维护日期';

comment on column GAPSUSR.ICPS_WBC_KDPL_ZHMINX.SHIJCHUO is
'时间戳';

comment on column GAPSUSR.ICPS_WBC_KDPL_ZHMINX.IS_CHECK_FLAG is
'参与对账标识';

comment on column GAPSUSR.ICPS_WBC_KDPL_ZHMINX.EXTEND_PARAM1 is
'扩展1';

comment on column GAPSUSR.ICPS_WBC_KDPL_ZHMINX.EXTEND_PARAM2 is
'扩展2';

comment on column GAPSUSR.ICPS_WBC_KDPL_ZHMINX.EXTEND_PARAM3 is
'扩展3';

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
'CBS清结算明细报表';

comment on column GAPSUSR.ICPS_WBC_REPORT_CBS_PTJR_CAR_DATA_PAID_DETAIL_DAY_COOP.BUSI_DATE is
'业务日期';

comment on column GAPSUSR.ICPS_WBC_REPORT_CBS_PTJR_CAR_DATA_PAID_DETAIL_DAY_COOP.FILE_ORDER is
'文件序号';

comment on column GAPSUSR.ICPS_WBC_REPORT_CBS_PTJR_CAR_DATA_PAID_DETAIL_DAY_COOP.PARTITION_DATE is
'批量日期';

comment on column GAPSUSR.ICPS_WBC_REPORT_CBS_PTJR_CAR_DATA_PAID_DETAIL_DAY_COOP.BANK_GROUP_ID is
'银团编号';

comment on column GAPSUSR.ICPS_WBC_REPORT_CBS_PTJR_CAR_DATA_PAID_DETAIL_DAY_COOP.ORG_NO is
'合作机构名称';

comment on column GAPSUSR.ICPS_WBC_REPORT_CBS_PTJR_CAR_DATA_PAID_DETAIL_DAY_COOP.FEE_NAME is
'费用名称';

comment on column GAPSUSR.ICPS_WBC_REPORT_CBS_PTJR_CAR_DATA_PAID_DETAIL_DAY_COOP.LOAN_RECEIPT_NBR is
'借据号';

comment on column GAPSUSR.ICPS_WBC_REPORT_CBS_PTJR_CAR_DATA_PAID_DETAIL_DAY_COOP.TXN_DATE is
'交易发生批量日期';

comment on column GAPSUSR.ICPS_WBC_REPORT_CBS_PTJR_CAR_DATA_PAID_DETAIL_DAY_COOP.CLEARING_CALC_DAY_AMT is
'实收利息';

comment on column GAPSUSR.ICPS_WBC_REPORT_CBS_PTJR_CAR_DATA_PAID_DETAIL_DAY_COOP.CLEARING_DAY_AMT is
'平台费';

comment on column GAPSUSR.ICPS_WBC_REPORT_CBS_PTJR_CAR_DATA_PAID_DETAIL_DAY_COOP.CLEARING_DAY_NO_VAT_AMT is
'扣收平台费（不含税）';

comment on column GAPSUSR.ICPS_WBC_REPORT_CBS_PTJR_CAR_DATA_PAID_DETAIL_DAY_COOP.CLEARING_DAY_VAT_AMT is
'扣收平台费（税）';

comment on column GAPSUSR.ICPS_WBC_REPORT_CBS_PTJR_CAR_DATA_PAID_DETAIL_DAY_COOP.INTEREST_RATE is
'利率';

comment on column GAPSUSR.ICPS_WBC_REPORT_CBS_PTJR_CAR_DATA_PAID_DETAIL_DAY_COOP.FUND_RATIO is
'资金定价';

comment on column GAPSUSR.ICPS_WBC_REPORT_CBS_PTJR_CAR_DATA_PAID_DETAIL_DAY_COOP.IS_CHECK_FLAG is
'参与对账标识';

comment on column GAPSUSR.ICPS_WBC_REPORT_CBS_PTJR_CAR_DATA_PAID_DETAIL_DAY_COOP.EXTEND_PARAM1 is
'扩展1';

comment on column GAPSUSR.ICPS_WBC_REPORT_CBS_PTJR_CAR_DATA_PAID_DETAIL_DAY_COOP.EXTEND_PARAM2 is
'扩展2';

comment on column GAPSUSR.ICPS_WBC_REPORT_CBS_PTJR_CAR_DATA_PAID_DETAIL_DAY_COOP.EXTEND_PARAM3 is
'扩展3';

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
'CBS清结算汇总报表';

comment on column GAPSUSR.ICPS_WBC_REPORT_CBS_PTJR_CAR_DATA_PAID_SUM_DAY_COOP.BUSI_DATE is
'业务日期';

comment on column GAPSUSR.ICPS_WBC_REPORT_CBS_PTJR_CAR_DATA_PAID_SUM_DAY_COOP.FILE_ORDER is
'文件序号';

comment on column GAPSUSR.ICPS_WBC_REPORT_CBS_PTJR_CAR_DATA_PAID_SUM_DAY_COOP.PARTITION_DATE is
'批量日期';

comment on column GAPSUSR.ICPS_WBC_REPORT_CBS_PTJR_CAR_DATA_PAID_SUM_DAY_COOP.BANK_GROUP_ID is
'银团编号';

comment on column GAPSUSR.ICPS_WBC_REPORT_CBS_PTJR_CAR_DATA_PAID_SUM_DAY_COOP.CLEARING_CALC_DAY_AMT is
'实收利息';

comment on column GAPSUSR.ICPS_WBC_REPORT_CBS_PTJR_CAR_DATA_PAID_SUM_DAY_COOP.CLEARING_DAY_NO_VAT_AMT is
'扣收平台费（不含税）';

comment on column GAPSUSR.ICPS_WBC_REPORT_CBS_PTJR_CAR_DATA_PAID_SUM_DAY_COOP.CLEARING_DAY_VAT_AMT is
'扣收平台费（税）';

comment on column GAPSUSR.ICPS_WBC_REPORT_CBS_PTJR_CAR_DATA_PAID_SUM_DAY_COOP.TXN_NUM is
'交易数';

comment on column GAPSUSR.ICPS_WBC_REPORT_CBS_PTJR_CAR_DATA_PAID_SUM_DAY_COOP.CLEARING_DAY_AMT is
'平台费';

comment on column GAPSUSR.ICPS_WBC_REPORT_CBS_PTJR_CAR_DATA_PAID_SUM_DAY_COOP.IS_CHECK_FLAG is
'参与对账标识';

comment on column GAPSUSR.ICPS_WBC_REPORT_CBS_PTJR_CAR_DATA_PAID_SUM_DAY_COOP.EXTEND_PARAM1 is
'扩展1';

comment on column GAPSUSR.ICPS_WBC_REPORT_CBS_PTJR_CAR_DATA_PAID_SUM_DAY_COOP.EXTEND_PARAM2 is
'扩展2';

comment on column GAPSUSR.ICPS_WBC_REPORT_CBS_PTJR_CAR_DATA_PAID_SUM_DAY_COOP.EXTEND_PARAM3 is
'扩展3';

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
'备付金资金清算明细';

comment on column GAPSUSR.ICPS_WBC_RRS_BDM_UDF_CLEAR_DETAIL.BUSI_DATE is
'业务日期';

comment on column GAPSUSR.ICPS_WBC_RRS_BDM_UDF_CLEAR_DETAIL.FILE_ORDER is
'文件序号';

comment on column GAPSUSR.ICPS_WBC_RRS_BDM_UDF_CLEAR_DETAIL.DATA_DT is
'数据日期';

comment on column GAPSUSR.ICPS_WBC_RRS_BDM_UDF_CLEAR_DETAIL.ACCT_NO is
'备付金帐号';

comment on column GAPSUSR.ICPS_WBC_RRS_BDM_UDF_CLEAR_DETAIL.CCY is
'币种';

comment on column GAPSUSR.ICPS_WBC_RRS_BDM_UDF_CLEAR_DETAIL.BANK_GROUP_CODE is
'银团编号';

comment on column GAPSUSR.ICPS_WBC_RRS_BDM_UDF_CLEAR_DETAIL.DATA_TYPE is
'数据类型';

comment on column GAPSUSR.ICPS_WBC_RRS_BDM_UDF_CLEAR_DETAIL.AMOUNT is
'发生额';

comment on column GAPSUSR.ICPS_WBC_RRS_BDM_UDF_CLEAR_DETAIL.DS is
'日期分区';

comment on column GAPSUSR.ICPS_WBC_RRS_BDM_UDF_CLEAR_DETAIL.IS_CHECK_FLAG is
'参与对账标识';

comment on column GAPSUSR.ICPS_WBC_RRS_BDM_UDF_CLEAR_DETAIL.EXTEND_PARAM1 is
'扩展1';

comment on column GAPSUSR.ICPS_WBC_RRS_BDM_UDF_CLEAR_DETAIL.EXTEND_PARAM2 is
'扩展2';

comment on column GAPSUSR.ICPS_WBC_RRS_BDM_UDF_CLEAR_DETAIL.EXTEND_PARAM3 is
'扩展3';

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
'备付金其他款项资金明细';

comment on column GAPSUSR.ICPS_WBC_RRS_BDM_UDF_CLEAR_OTHER_DETAIL.BUSI_DATE is
'业务日期';

comment on column GAPSUSR.ICPS_WBC_RRS_BDM_UDF_CLEAR_OTHER_DETAIL.FILE_ORDER is
'文件序号';

comment on column GAPSUSR.ICPS_WBC_RRS_BDM_UDF_CLEAR_OTHER_DETAIL.DATA_DT is
'数据日期';

comment on column GAPSUSR.ICPS_WBC_RRS_BDM_UDF_CLEAR_OTHER_DETAIL.ACCT_NO is
'备付金帐号';

comment on column GAPSUSR.ICPS_WBC_RRS_BDM_UDF_CLEAR_OTHER_DETAIL.CCY is
'币种';

comment on column GAPSUSR.ICPS_WBC_RRS_BDM_UDF_CLEAR_OTHER_DETAIL.BANK_GROUP_CODE is
'银团编号';

comment on column GAPSUSR.ICPS_WBC_RRS_BDM_UDF_CLEAR_OTHER_DETAIL.DATA_TYPE is
'数据类型';

comment on column GAPSUSR.ICPS_WBC_RRS_BDM_UDF_CLEAR_OTHER_DETAIL.SER_NO is
'明细序号';

comment on column GAPSUSR.ICPS_WBC_RRS_BDM_UDF_CLEAR_OTHER_DETAIL.AMOUNT is
'发生额';

comment on column GAPSUSR.ICPS_WBC_RRS_BDM_UDF_CLEAR_OTHER_DETAIL.MEMO is
'备注';

comment on column GAPSUSR.ICPS_WBC_RRS_BDM_UDF_CLEAR_OTHER_DETAIL.DS is
'日期分区';

comment on column GAPSUSR.ICPS_WBC_RRS_BDM_UDF_CLEAR_OTHER_DETAIL.IS_CHECK_FLAG is
'参与对账标识';

comment on column GAPSUSR.ICPS_WBC_RRS_BDM_UDF_CLEAR_OTHER_DETAIL.EXTEND_PARAM1 is
'扩展1';

comment on column GAPSUSR.ICPS_WBC_RRS_BDM_UDF_CLEAR_OTHER_DETAIL.EXTEND_PARAM2 is
'扩展2';

comment on column GAPSUSR.ICPS_WBC_RRS_BDM_UDF_CLEAR_OTHER_DETAIL.EXTEND_PARAM3 is
'扩展3';

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
'备付金资金清算汇总';

comment on column GAPSUSR.ICPS_WBC_RRS_BDM_UDF_CLEAR_TOT.BUSI_DATE is
'业务日期';

comment on column GAPSUSR.ICPS_WBC_RRS_BDM_UDF_CLEAR_TOT.FILE_ORDER is
'文件序号';

comment on column GAPSUSR.ICPS_WBC_RRS_BDM_UDF_CLEAR_TOT.DATA_DT is
'数据日期';

comment on column GAPSUSR.ICPS_WBC_RRS_BDM_UDF_CLEAR_TOT.ACCT_NO is
'备付金帐号';

comment on column GAPSUSR.ICPS_WBC_RRS_BDM_UDF_CLEAR_TOT.CCY is
'币种';

comment on column GAPSUSR.ICPS_WBC_RRS_BDM_UDF_CLEAR_TOT.ACCT_NAME is
'户名';

comment on column GAPSUSR.ICPS_WBC_RRS_BDM_UDF_CLEAR_TOT.LAST_BALANCE is
'上日账户余额';

comment on column GAPSUSR.ICPS_WBC_RRS_BDM_UDF_CLEAR_TOT.BALANCE is
'本日账户余额';

comment on column GAPSUSR.ICPS_WBC_RRS_BDM_UDF_CLEAR_TOT.PAYMENT_AMT is
'当日放款总金额';

comment on column GAPSUSR.ICPS_WBC_RRS_BDM_UDF_CLEAR_TOT.REPAYMENT_AMT is
'当日还款总金额';

comment on column GAPSUSR.ICPS_WBC_RRS_BDM_UDF_CLEAR_TOT.OTHER_CREDIT_AMT is
'当日其他划入款项';

comment on column GAPSUSR.ICPS_WBC_RRS_BDM_UDF_CLEAR_TOT.OTHER_DEBIT_AMT is
'当日其他划出款项';

comment on column GAPSUSR.ICPS_WBC_RRS_BDM_UDF_CLEAR_TOT.DS is
'日期分区';

comment on column GAPSUSR.ICPS_WBC_RRS_BDM_UDF_CLEAR_TOT.IS_CHECK_FLAG is
'参与对账标识';

comment on column GAPSUSR.ICPS_WBC_RRS_BDM_UDF_CLEAR_TOT.EXTEND_PARAM1 is
'扩展1';

comment on column GAPSUSR.ICPS_WBC_RRS_BDM_UDF_CLEAR_TOT.EXTEND_PARAM2 is
'扩展2';

comment on column GAPSUSR.ICPS_WBC_RRS_BDM_UDF_CLEAR_TOT.EXTEND_PARAM3 is
'扩展3';

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
'账户信息表-核心批量';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.BUSI_DATE is
'业务日期';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.FILE_ORDER is
'文件序号';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.ORG is
'机构号';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.ACCT_NO is
'账户编号';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.ACCT_TYPE is
'账户类型';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.CUST_ID is
'客户编号';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.CUST_LIMIT_ID is
'客户额度ID';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.PRODUCT_CD is
'产品代码';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.DEFAULT_LOGICAL_CARD_NO is
'默认逻辑卡号';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.CURR_CD is
'币种';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.CREDIT_LIMIT is
'信用额度';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.TEMP_LIMIT is
'临时额度';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.TEMP_LIMIT_BEGIN_DATE is
'临时额度开始日期';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.TEMP_LIMIT_END_DATE is
'临时额度结束日期';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.CASH_LIMIT_RT is
'取现额度比例';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.OVRLMT_RATE is
'授权超限比例';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.LOAN_LIMIT_RT is
'额度内分期额度比例';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.CURR_BAL is
'当前余额';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.CASH_BAL is
'取现余额';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.PRINCIPAL_BAL is
'本金余额';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.LOAN_BAL is
'额度内分期余额';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.DISPUTE_AMT is
'争议金额';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.BEGIN_BAL is
'期初余额';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.PMT_DUE_DAY_BAL is
'到期还款日余额';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.QUAL_GRACE_BAL is
'全部应还款额';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.GRACE_DAYS_FULL_IND is
'是否已全额还款';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.POINT_BEGIN_BAL is
'期初积分余额';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.CTD_EARNED_POINTS is
'当期新增积分';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.CTD_DISB_POINTS is
'当期兑换积分';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.CTD_ADJ_POINTS is
'当期调整积分';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.POINT_BAL is
'积分余额';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.SETUP_DATE is
'创建日期';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.DORMENT_DATE is
'账户睡眠日期';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.REINSTATE_DATE is
'账户恢复活动日期';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.OVRLMT_DATE is
'超限日期';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.OVRLMT_NBR_OF_CYC is
'连续超限账期';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT."NAME" is
'姓名';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.GENDER is
'性别';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.OWNING_BRANCH is
'发卡网点';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.MOBILE_NO is
'移动电话';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.CORP_NAME is
'公司名称';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.BILLING_CYCLE is
'账单周期';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.STMT_FLAG is
'账单标志';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.STMT_MAIL_ADDR_IND is
'账单寄送地址标志';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.STMT_MEDIA_TYPE is
'账单介质类型';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.STMT_COUNTRY_CD is
'账单地址国家代码';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.STMT_STATE is
'账单地址省份';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.STMT_CITY is
'账单地址城市';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.STMT_DISTRICT is
'账单地址行政区';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.STMT_ADDRESS is
'账单地址';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.STMT_ZIP is
'账单地址邮政编码';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.EMAIL is
'电子邮箱';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.BLOCK_CODE is
'锁定码';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.AGE_CD is
'账龄';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.GL_AGE_CD is
'总账账龄';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.UNMATCH_DB is
'未匹配借记金额';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.UNMATCH_CASH is
'未匹配取现金额';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.UNMATCH_CR is
'未匹配贷记金额';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.DD_IND is
'约定还款类型';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.DD_BANK_NAME is
'约定还款银行名称';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.DD_BANK_BRANCH is
'约定还款开户行号';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.DD_BANK_ACCT_NO is
'约定还款扣款账号';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.DD_BANK_ACCT_NAME is
'约定还款扣款账户姓名';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.LAST_DD_AMT is
'上期约定还款金额';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.LAST_DD_DATE is
'上期约定还款日期';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.DUAL_BILLING_FLAG is
'本币溢缴款还外币指示';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.LAST_PMT_AMT is
'上笔还款金额';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.LAST_PMT_DATE is
'上个还款日期';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.LAST_STMT_DATE is
'上个账单日期';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.LAST_PMT_DUE_DATE is
'上个到期还款日期';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.LAST_AGING_DATE is
'上个账龄提升日期';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.COLLECT_DATE is
'入催日期';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.COLLECT_OUT_DATE is
'出催收队列日期';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.NEXT_STMT_DATE is
'下个账单日期';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.PMT_DUE_DATE is
'到期还款日期';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.DD_DATE is
'约定还款日期';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.GRACE_DATE is
'宽限日期';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.DLBL_DATE is
'本币还外币日期';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.CLOSED_DATE is
'最终销户日期';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.FIRST_STMT_DATE is
'首个账单日期';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.CANCEL_DATE is
'销卡销户日期';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.CHARGE_OFF_DATE is
'转呆账日期';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.FIRST_PURCHASE_DATE is
'首次消费日期';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.FIRST_PURCHASE_AMT is
'首次消费金额';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.TOT_DUE_AMT is
'最小还款额';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.CURR_DUE_AMT is
'当期最小还款额';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.PAST_DUE_AMT1 is
'上个月最小还款额';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.PAST_DUE_AMT2 is
'上2个月最小还款额';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.PAST_DUE_AMT3 is
'上3个月最小还款额';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.PAST_DUE_AMT4 is
'上4个月最小还款额';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.PAST_DUE_AMT5 is
'上5个月最小还款额';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.PAST_DUE_AMT6 is
'上6个月最小还款额';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.PAST_DUE_AMT7 is
'上7个月最小还款额';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.PAST_DUE_AMT8 is
'上8个月最小还款额';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.CTD_CASH_AMT is
'当期取现金额';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.CTD_CASH_CNT is
'当期取现笔数';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.CTD_RETAIL_AMT is
'当期消费金额';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.CTD_RETAIL_CNT is
'当期消费笔数';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.CTD_PAYMENT_AMT is
'当期还款金额';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.CTD_PAYMENT_CNT is
'当期还款笔数';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.CTD_DB_ADJ_AMT is
'当期借记调整金额';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.CTD_DB_ADJ_CNT is
'当期借记调整笔数';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.CTD_CR_ADJ_AMT is
'当期贷记调整金额';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.CTD_CR_ADJ_CNT is
'当期贷记调整笔数';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.CTD_FEE_AMT is
'当期费用金额';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.CTD_FEE_CNT is
'当期费用笔数';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.CTD_INTEREST_AMT is
'当期利息金额';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.CTD_INTEREST_CNT is
'当期利息笔数';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.CTD_REFUND_AMT is
'当期退货金额';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.CTD_REFUND_CNT is
'当期退货笔数';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.CTD_HI_OVRLMT_AMT is
'当期最高超限金额';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.MTD_RETAIL_AMT is
'本月消费金额';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.MTD_RETAIL_CNT is
'本月消费笔数';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.MTD_CASH_AMT is
'本月取现金额';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.MTD_CASH_CNT is
'本月取现笔数';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.MTD_REFUND_AMT is
'本月退货金额';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.MTD_REFUND_CNT is
'本月退货笔数';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.YTD_RETAIL_AMT is
'本年消费金额';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.YTD_RETAIL_CNT is
'本年消费笔数';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.YTD_CASH_AMT is
'本年取现金额';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.YTD_CASH_CNT is
'本年取现笔数';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.YTD_REFUND_AMT is
'本年退货金额';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.YTD_REFUND_CNT is
'本年退货笔数';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.YTD_OVRLMT_FEE_AMT is
'本年超限费收取金额';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.YTD_OVRLMT_FEE_CNT is
'本年超限费收取笔数';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.YTD_LPC_AMT is
'本年滞纳金收取金额';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.YTD_LPC_CNT is
'本年滞纳金收取笔数';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.LTD_RETAIL_AMT is
'历史消费金额';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.LTD_RETAIL_CNT is
'历史消费笔数';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.LTD_CASH_AMT is
'历史取现金额';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.LTD_CASH_CNT is
'历史取现笔数';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.LTD_REFUND_AMT is
'历史退货金额';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.LTD_REFUND_CNT is
'历史退货笔数';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.LTD_HIGHEST_PRINCIPAL is
'历史最高本金欠款';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.LTD_HIGHEST_CR_BAL is
'历史最高溢缴款';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.LTD_HIGHEST_BAL is
'历史最高余额';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.COLLECT_TIMES is
'入催次数';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.COLLECT_COLR is
'催收员代码';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.COLLECT_REASON is
'入催原因';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.AGE_HIST is
'账龄历史信息';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.PAYMENT_HIST is
'还款历史信息';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.WAIVE_OVLFEE_IND is
'是否免除超限费';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.WAIVE_CARDFEE_IND is
'是否免除年费';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.WAIVE_LATEFEE_IND is
'是否免除滞纳金';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.WAIVE_SVCFEE_IND is
'是否免除服务费';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.USER_CODE1 is
'用户自定义代码1';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.USER_CODE2 is
'用户自定义代码2';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.USER_CODE3 is
'用户自定义代码3';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.USER_CODE4 is
'用户自定义代码4';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.USER_CODE5 is
'用户自定义代码5';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.USER_CODE6 is
'用户自定义代码6';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.USER_DATE1 is
'用户自定义日期1';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.USER_DATE2 is
'上次调额日期';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.USER_DATE3 is
'用户自定义日期3';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.USER_DATE4 is
'用户自定义日期4';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.USER_DATE5 is
'用户自定义日期5';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.USER_DATE6 is
'用户自定义日期6';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.USER_NUMBER1 is
'用户自定义笔数1';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.USER_NUMBER2 is
'用户自定义笔数2';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.USER_NUMBER3 is
'用户自定义笔数3';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.USER_NUMBER4 is
'用户自定义笔数4';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.USER_NUMBER5 is
'用户自定义笔数5';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.USER_NUMBER6 is
'用户自定义笔数6';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.USER_FIELD1 is
'用户自定义域1';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.USER_FIELD2 is
'用户自定义域2';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.USER_FIELD3 is
'用户自定义域3';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.USER_FIELD4 is
'用户自定义域4';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.USER_FIELD5 is
'用户自定义域5';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.USER_FIELD6 is
'用户自定义域6';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.USER_AMT1 is
'用户自定义金额1';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.USER_AMT2 is
'用户自定义金额2';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.USER_AMT3 is
'用户自定义金额3';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.USER_AMT4 is
'用户自定义金额4';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.USER_AMT5 is
'用户自定义金额5';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.USER_AMT6 is
'昨日贷记卡承诺余额';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.JPA_VERSION is
'乐观锁版本号';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.MTD_PAYMENT_AMT is
'当月还款金额';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.MTD_PAYMENT_CNT is
'当月还款笔数';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.YTD_PAYMENT_AMT is
'当年还款金额';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.YTD_PAYMENT_CNT is
'当年还款笔数';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.LTD_PAYMENT_AMT is
'历史还款金额';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.LTD_PAYMENT_CNT is
'历史还款笔数';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.SMS_IND is
'短信发送标识';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.USER_SMS_AMT is
'个性化动账短信发送阈值';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.YTD_CYCLE_CHAG_CNT is
'本年度账单日修改次数';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.LAST_POST_DATE is
'上个入账日期';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.LAST_MODIFIED_DATETIME is
'修改时间';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.LOCK_DATE is
'自动锁定日';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.LAST_SYNC_DATE is
'上一次入账的批量日期';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.CREATED_DATETIME is
'创建时间';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.DELAY_BAL is
'账户逾期金额';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.BANK_GROUP_ID is
'银团编号';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.CUSTOMER_TYPE is
'客群分类';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.IS_CHECK_FLAG is
'参与对账标识';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.EXTEND_PARAM1 is
'扩展1';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.EXTEND_PARAM2 is
'扩展2';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNT.EXTEND_PARAM3 is
'扩展3';

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
'会计分录日报表';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNTING_FLOW.BUSI_DATE is
'业务日期';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNTING_FLOW.FILE_ORDER is
'文件序号';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNTING_FLOW.ORG is
'内部机构号';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNTING_FLOW.CPS_TXN_SEQ is
'核心交易流水';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNTING_FLOW.CARD_NO is
'卡号';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNTING_FLOW.CURR_CD is
'币种';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNTING_FLOW.TXN_CODE is
'交易码';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNTING_FLOW.TXN_DESC is
'交易描述';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNTING_FLOW.DB_CR_IND is
'借贷标记';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNTING_FLOW.POST_AMT is
'入账金额';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNTING_FLOW.POST_GL_IND is
'入账方式';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNTING_FLOW.OWNING_BRANCH is
'支行';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNTING_FLOW.SUBJECT is
'科目';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNTING_FLOW.RED_FLAG is
'红蓝字标识';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNTING_FLOW.QUEUE is
'排序';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNTING_FLOW.PRODUCT_CD is
'产品号';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNTING_FLOW.REF_NBR is
'借据号';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNTING_FLOW.AGE_GROUP is
'账龄组';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNTING_FLOW.PLAN_NBR is
'信用计划号';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNTING_FLOW.BNP_GROUP is
'余额成分组';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNTING_FLOW.BANK_GROUP_ID is
'银团代码';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNTING_FLOW.BANK_NO is
'银行代码';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNTING_FLOW.TERM is
'期数';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNTING_FLOW.BATCHDATE is
'批量';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNTING_FLOW.IS_CHECK_FLAG is
'参与对账标识';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNTING_FLOW.EXTEND_PARAM1 is
'扩展1';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNTING_FLOW.EXTEND_PARAM2 is
'扩展2';

comment on column GAPSUSR.ICPS_WBC_TM_ACCOUNTING_FLOW.EXTEND_PARAM3 is
'扩展3';

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
'协议表';

comment on column GAPSUSR.ICPS_WBC_TM_AGREEMENT.BUSI_DATE is
'业务日期';

comment on column GAPSUSR.ICPS_WBC_TM_AGREEMENT.FILE_ORDER is
'文件序号';

comment on column GAPSUSR.ICPS_WBC_TM_AGREEMENT.AGREEMENT_NO is
'平台订单号';

comment on column GAPSUSR.ICPS_WBC_TM_AGREEMENT.MERCHANT_ID is
'平台ID';

comment on column GAPSUSR.ICPS_WBC_TM_AGREEMENT.PRODUCT_CD is
'产品CD';

comment on column GAPSUSR.ICPS_WBC_TM_AGREEMENT.PRODUCT_STCODE is
'产品结构代码';

comment on column GAPSUSR.ICPS_WBC_TM_AGREEMENT.NBS_CUST_ID is
'NBS客户ID';

comment on column GAPSUSR.ICPS_WBC_TM_AGREEMENT.USER_ID is
'平台的客户ID';

comment on column GAPSUSR.ICPS_WBC_TM_AGREEMENT.CNC_CARD_NO is
'贷款卡号';

comment on column GAPSUSR.ICPS_WBC_TM_AGREEMENT.DEBIT_CARD_NO is
'他行借记卡号';

comment on column GAPSUSR.ICPS_WBC_TM_AGREEMENT.WB_DEBIT_CARD_NO is
'本行借记卡号';

comment on column GAPSUSR.ICPS_WBC_TM_AGREEMENT.LAST_TXN_STATUS is
'上一个业务状态';

comment on column GAPSUSR.ICPS_WBC_TM_AGREEMENT.TXN_STATUS is
'当前业务状态';

comment on column GAPSUSR.ICPS_WBC_TM_AGREEMENT.LAST_NATIVE_STAUS is
'上一处理状态';

comment on column GAPSUSR.ICPS_WBC_TM_AGREEMENT.NATIVE_STAUS is
'当前处理状态';

comment on column GAPSUSR.ICPS_WBC_TM_AGREEMENT.BILLING_CYCLE is
'账单周期';

comment on column GAPSUSR.ICPS_WBC_TM_AGREEMENT.FIRST_STMT_DATE is
'首个账单日';

comment on column GAPSUSR.ICPS_WBC_TM_AGREEMENT.AGREEMENT_AMT is
'协议金额';

comment on column GAPSUSR.ICPS_WBC_TM_AGREEMENT.PCT_ID is
'定价控制编号';

comment on column GAPSUSR.ICPS_WBC_TM_AGREEMENT.FEE_RATE is
'费用利率';

comment on column GAPSUSR.ICPS_WBC_TM_AGREEMENT.INTEREST_RATE is
'利息利率';

comment on column GAPSUSR.ICPS_WBC_TM_AGREEMENT.PENALTY_RATE is
'罚息利率';

comment on column GAPSUSR.ICPS_WBC_TM_AGREEMENT.LIQUIDATED_DAMAGES is
'违约金';

comment on column GAPSUSR.ICPS_WBC_TM_AGREEMENT.CURR_TERM is
'当期期数';

comment on column GAPSUSR.ICPS_WBC_TM_AGREEMENT.CURR_DEDUCT_STAGE is
'当前扣款阶段';

comment on column GAPSUSR.ICPS_WBC_TM_AGREEMENT.DEDUCT_STAGE_HST is
'扣款阶段历史记录';

comment on column GAPSUSR.ICPS_WBC_TM_AGREEMENT.CREDIT_INTEREST_RATE is
'信用贷利率';

comment on column GAPSUSR.ICPS_WBC_TM_AGREEMENT.CREDIT_PENALTY_RATE is
'信用贷罚息利率';

comment on column GAPSUSR.ICPS_WBC_TM_AGREEMENT.CREDIT_CURR_DEDUCT_STAGE is
'信用贷当前扣款阶段';

comment on column GAPSUSR.ICPS_WBC_TM_AGREEMENT.CREDIT_DEDUCT_STAGE_HST is
'信用贷扣款阶段历史记录';

comment on column GAPSUSR.ICPS_WBC_TM_AGREEMENT.MASTER_CARD_FLAG is
'主还款卡标识';

comment on column GAPSUSR.ICPS_WBC_TM_AGREEMENT.RESERVE1 is
'保留字段1';

comment on column GAPSUSR.ICPS_WBC_TM_AGREEMENT.RESERVE2 is
'保留字段2';

comment on column GAPSUSR.ICPS_WBC_TM_AGREEMENT.RESERVE3 is
'保留字段3';

comment on column GAPSUSR.ICPS_WBC_TM_AGREEMENT.BIZ_DATE is
'业务日期';

comment on column GAPSUSR.ICPS_WBC_TM_AGREEMENT.CREATED_DATETIME is
'创建时间日期';

comment on column GAPSUSR.ICPS_WBC_TM_AGREEMENT.LAST_MODIFIED_DATETIME is
'更新时间日期';

comment on column GAPSUSR.ICPS_WBC_TM_AGREEMENT.LOAN_INIT_TERM is
'总期数';

comment on column GAPSUSR.ICPS_WBC_TM_AGREEMENT.ORDER_TYPE is
'订单类型';

comment on column GAPSUSR.ICPS_WBC_TM_AGREEMENT.FUND_STATUS is
'资金占压状态';

comment on column GAPSUSR.ICPS_WBC_TM_AGREEMENT.FEE_CURR_DEDUCT_STAGE is
'费用贷当前扣款阶段';

comment on column GAPSUSR.ICPS_WBC_TM_AGREEMENT.PROFIT_RATIO is
'分润比例';

comment on column GAPSUSR.ICPS_WBC_TM_AGREEMENT.PRODUCT_CATEGORY is
'产品大类';

comment on column GAPSUSR.ICPS_WBC_TM_AGREEMENT.FEE_DEDUCT_STAGE_HST is
'费用贷扣款阶段历史记录';

comment on column GAPSUSR.ICPS_WBC_TM_AGREEMENT.RESERVE4 is
'保留字段4';

comment on column GAPSUSR.ICPS_WBC_TM_AGREEMENT.RESERVE5 is
'保留字段5';

comment on column GAPSUSR.ICPS_WBC_TM_AGREEMENT.RESERVE6 is
'保留字段6';

comment on column GAPSUSR.ICPS_WBC_TM_AGREEMENT.RESERVE7 is
'保留字段7';

comment on column GAPSUSR.ICPS_WBC_TM_AGREEMENT.RESERVE8 is
'保留字段8';

comment on column GAPSUSR.ICPS_WBC_TM_AGREEMENT.RESERVE9 is
'保留字段9';

comment on column GAPSUSR.ICPS_WBC_TM_AGREEMENT.RESERVE10 is
'保留字段10';

comment on column GAPSUSR.ICPS_WBC_TM_AGREEMENT.IS_CHECK_FLAG is
'参与对账标识';

comment on column GAPSUSR.ICPS_WBC_TM_AGREEMENT.EXTEND_PARAM1 is
'扩展1';

comment on column GAPSUSR.ICPS_WBC_TM_AGREEMENT.EXTEND_PARAM2 is
'扩展2';

comment on column GAPSUSR.ICPS_WBC_TM_AGREEMENT.EXTEND_PARAM3 is
'扩展3';

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
'协议附加表(车)';

comment on column GAPSUSR.ICPS_WBC_TM_AGREEMENT_CAR.BUSI_DATE is
'业务日期';

comment on column GAPSUSR.ICPS_WBC_TM_AGREEMENT_CAR.FILE_ORDER is
'文件序号';

comment on column GAPSUSR.ICPS_WBC_TM_AGREEMENT_CAR.AGREEMENT_NO is
'平台订单号';

comment on column GAPSUSR.ICPS_WBC_TM_AGREEMENT_CAR.MERCHANT_ID is
'平台ID号';

comment on column GAPSUSR.ICPS_WBC_TM_AGREEMENT_CAR.PRODUCT_CD is
'产品号';

comment on column GAPSUSR.ICPS_WBC_TM_AGREEMENT_CAR.MER_ORDER_NO is
'平台协议号';

comment on column GAPSUSR.ICPS_WBC_TM_AGREEMENT_CAR.IS_NEW_CAR is
'是否新车';

comment on column GAPSUSR.ICPS_WBC_TM_AGREEMENT_CAR.CAR_ID is
'车辆ID';

comment on column GAPSUSR.ICPS_WBC_TM_AGREEMENT_CAR.CAR_PRICE is
'车辆销售价';

comment on column GAPSUSR.ICPS_WBC_TM_AGREEMENT_CAR.CAR_INQUIRY_PRICE is
'外部数据源查询价';

comment on column GAPSUSR.ICPS_WBC_TM_AGREEMENT_CAR.ASSESS_AMOUNT is
'车辆估值';

comment on column GAPSUSR.ICPS_WBC_TM_AGREEMENT_CAR.ASSESS_TIME is
'车辆评估时间';

comment on column GAPSUSR.ICPS_WBC_TM_AGREEMENT_CAR.ASSESS_CLASS is
'车辆检测级别';

comment on column GAPSUSR.ICPS_WBC_TM_AGREEMENT_CAR.REGISTRATE_TIME is
'上牌日期';

comment on column GAPSUSR.ICPS_WBC_TM_AGREEMENT_CAR.VEHICLE_ID is
'机动车架号';

comment on column GAPSUSR.ICPS_WBC_TM_AGREEMENT_CAR.ENGINE_NO is
'发动机号';

comment on column GAPSUSR.ICPS_WBC_TM_AGREEMENT_CAR.MILEAGE is
'行驶里程';

comment on column GAPSUSR.ICPS_WBC_TM_AGREEMENT_CAR.XFR_TIMES is
'过户次数';

comment on column GAPSUSR.ICPS_WBC_TM_AGREEMENT_CAR.COTY is
'车龄';

comment on column GAPSUSR.ICPS_WBC_TM_AGREEMENT_CAR.MOTORCYCLE_TYPE is
'车型描述';

comment on column GAPSUSR.ICPS_WBC_TM_AGREEMENT_CAR.INS_EXPIRE_DATE is
'保险到期日';

comment on column GAPSUSR.ICPS_WBC_TM_AGREEMENT_CAR.DEALER_ID is
'车商ID';

comment on column GAPSUSR.ICPS_WBC_TM_AGREEMENT_CAR.DEALER_NAME is
'车商';

comment on column GAPSUSR.ICPS_WBC_TM_AGREEMENT_CAR.IS_STAGE_GUARANTEE_DEALER is
'是否阶段性担保车商';

comment on column GAPSUSR.ICPS_WBC_TM_AGREEMENT_CAR.CAR_NAME is
'车辆名称';

comment on column GAPSUSR.ICPS_WBC_TM_AGREEMENT_CAR.IS_SECOND_HAND_CAR is
'是否二手车';

comment on column GAPSUSR.ICPS_WBC_TM_AGREEMENT_CAR.CAR_ACTUAL_PRICE is
'车辆实际成交价';

comment on column GAPSUSR.ICPS_WBC_TM_AGREEMENT_CAR.DOWN_PAYMENT is
'首付总金额';

comment on column GAPSUSR.ICPS_WBC_TM_AGREEMENT_CAR.CAR_CONTEXT is
'补充信息';

comment on column GAPSUSR.ICPS_WBC_TM_AGREEMENT_CAR.DRIVER_LICENSE is
'驾驶证号码';

comment on column GAPSUSR.ICPS_WBC_TM_AGREEMENT_CAR.HOME_PHONE is
'家庭固话号码';

comment on column GAPSUSR.ICPS_WBC_TM_AGREEMENT_CAR.OCCUPATION is
'职业';

comment on column GAPSUSR.ICPS_WBC_TM_AGREEMENT_CAR.SS_AVE_AMT_MTLY is
'每月社保平均缴交金额';

comment on column GAPSUSR.ICPS_WBC_TM_AGREEMENT_CAR.SALARY_AVE_MTLY is
'每月平均工资进账流水';

comment on column GAPSUSR.ICPS_WBC_TM_AGREEMENT_CAR.IS_HOME_VISITED is
'有无家访';

comment on column GAPSUSR.ICPS_WBC_TM_AGREEMENT_CAR.HOUSE_INFO is
'房产信息';

comment on column GAPSUSR.ICPS_WBC_TM_AGREEMENT_CAR.MER_APPLY_RESULT is
'审批结果';

comment on column GAPSUSR.ICPS_WBC_TM_AGREEMENT_CAR.MER_APPLY_VIEW is
'审批意见';

comment on column GAPSUSR.ICPS_WBC_TM_AGREEMENT_CAR.MER_REFUSE_REASON is
'拒绝原因分类';

comment on column GAPSUSR.ICPS_WBC_TM_AGREEMENT_CAR.BIZ_DATE is
'业务日期';

comment on column GAPSUSR.ICPS_WBC_TM_AGREEMENT_CAR.CREATED_DATETIME is
'创建时间';

comment on column GAPSUSR.ICPS_WBC_TM_AGREEMENT_CAR.LAST_MODIFIED_DATETIME is
'更新时间';

comment on column GAPSUSR.ICPS_WBC_TM_AGREEMENT_CAR.IS_CHECK_FLAG is
'参与对账标识';

comment on column GAPSUSR.ICPS_WBC_TM_AGREEMENT_CAR.EXTEND_PARAM1 is
'扩展1';

comment on column GAPSUSR.ICPS_WBC_TM_AGREEMENT_CAR.EXTEND_PARAM2 is
'扩展2';

comment on column GAPSUSR.ICPS_WBC_TM_AGREEMENT_CAR.EXTEND_PARAM3 is
'扩展3';

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
'订单号映射表';

comment on column GAPSUSR.ICPS_WBC_TM_AGREEMENT_NO_MAP.BUSI_DATE is
'业务日期';

comment on column GAPSUSR.ICPS_WBC_TM_AGREEMENT_NO_MAP.FILE_ORDER is
'文件序号';

comment on column GAPSUSR.ICPS_WBC_TM_AGREEMENT_NO_MAP.AGREEMENT_NO is
'NBS订单号';

comment on column GAPSUSR.ICPS_WBC_TM_AGREEMENT_NO_MAP.MERCHANT_ID is
'平台ID号';

comment on column GAPSUSR.ICPS_WBC_TM_AGREEMENT_NO_MAP.MER_ORDER_NO is
'平台订单号';

comment on column GAPSUSR.ICPS_WBC_TM_AGREEMENT_NO_MAP.TXN_STATUS is
'平台协议状态';

comment on column GAPSUSR.ICPS_WBC_TM_AGREEMENT_NO_MAP.BIZ_DATA is
'业务日期';

comment on column GAPSUSR.ICPS_WBC_TM_AGREEMENT_NO_MAP.CREATED_DATETIME is
'创建时间';

comment on column GAPSUSR.ICPS_WBC_TM_AGREEMENT_NO_MAP.LAST_MODIFIED_DATETIME is
'修改时间';

comment on column GAPSUSR.ICPS_WBC_TM_AGREEMENT_NO_MAP.IS_CHECK_FLAG is
'参与对账标识';

comment on column GAPSUSR.ICPS_WBC_TM_AGREEMENT_NO_MAP.EXTEND_PARAM1 is
'扩展1';

comment on column GAPSUSR.ICPS_WBC_TM_AGREEMENT_NO_MAP.EXTEND_PARAM2 is
'扩展2';

comment on column GAPSUSR.ICPS_WBC_TM_AGREEMENT_NO_MAP.EXTEND_PARAM3 is
'扩展3';

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
'申请主表';

comment on column GAPSUSR.ICPS_WBC_TM_APP_MAIN.BUSI_DATE is
'业务日期';

comment on column GAPSUSR.ICPS_WBC_TM_APP_MAIN.FILE_ORDER is
'文件序号';

comment on column GAPSUSR.ICPS_WBC_TM_APP_MAIN.ORG is
'机构号';

comment on column GAPSUSR.ICPS_WBC_TM_APP_MAIN.APP_NO is
'申请件编号';

comment on column GAPSUSR.ICPS_WBC_TM_APP_MAIN.APP_TYPE is
'申请类型';

comment on column GAPSUSR.ICPS_WBC_TM_APP_MAIN.APP_LMT is
'申请额度';

comment on column GAPSUSR.ICPS_WBC_TM_APP_MAIN.SUG_LMT is
'系统建议额度';

comment on column GAPSUSR.ICPS_WBC_TM_APP_MAIN.ACC_LMT is
'核准额度';

comment on column GAPSUSR.ICPS_WBC_TM_APP_MAIN.PRODUCT_CD is
'卡产品代码';

comment on column GAPSUSR.ICPS_WBC_TM_APP_MAIN.BUSINESS_LIMIT is
'商务卡额度';

comment on column GAPSUSR.ICPS_WBC_TM_APP_MAIN.MICRO_LOAN_LIMIT is
'小额贷款额度';

comment on column GAPSUSR.ICPS_WBC_TM_APP_MAIN.VEHICLE_LOAN is
'专项额度车贷';

comment on column GAPSUSR.ICPS_WBC_TM_APP_MAIN.HOUSE_LOAN is
'专项额度房贷';

comment on column GAPSUSR.ICPS_WBC_TM_APP_MAIN.RENOVATION_LOAN is
'专项额度装修贷';

comment on column GAPSUSR.ICPS_WBC_TM_APP_MAIN.TRAVEL_LOAN is
'专项额度旅游贷';

comment on column GAPSUSR.ICPS_WBC_TM_APP_MAIN.WEDDING_LOAN is
'专项额度婚庆贷';

comment on column GAPSUSR.ICPS_WBC_TM_APP_MAIN.DURABLE_LOAN is
'专项额度耐消贷';

comment on column GAPSUSR.ICPS_WBC_TM_APP_MAIN.PRIORITY is
'客户等级';

comment on column GAPSUSR.ICPS_WBC_TM_APP_MAIN.CLIENT_TYPE is
'客户类型';

comment on column GAPSUSR.ICPS_WBC_TM_APP_MAIN.APPROVE_QUICK_FLAG is
'快速审批标志';

comment on column GAPSUSR.ICPS_WBC_TM_APP_MAIN.BUSNS_NUM is
'公司编号';

comment on column GAPSUSR.ICPS_WBC_TM_APP_MAIN.RTF_STATE is
'审批状态';

comment on column GAPSUSR.ICPS_WBC_TM_APP_MAIN.POINT_RESULT is
'评分值';

comment on column GAPSUSR.ICPS_WBC_TM_APP_MAIN.CUST_RATE_DISCOUNT is
'客户利率浮动比例';

comment on column GAPSUSR.ICPS_WBC_TM_APP_MAIN.PRO_NUM is
'流程实例号';

comment on column GAPSUSR.ICPS_WBC_TM_APP_MAIN.PRO_NAME is
'流程节点名称';

comment on column GAPSUSR.ICPS_WBC_TM_APP_MAIN.REFUSE_CODE is
'拒绝原因码';

comment on column GAPSUSR.ICPS_WBC_TM_APP_MAIN.ANSWER_ERR_CNT is
'问题回答错误次数';

comment on column GAPSUSR.ICPS_WBC_TM_APP_MAIN.IS_CLT is
'是否集体件';

comment on column GAPSUSR.ICPS_WBC_TM_APP_MAIN.SPREADER_NUM is
'推广人编号';

comment on column GAPSUSR.ICPS_WBC_TM_APP_MAIN.SPREADER_ORG is
'推广机构';

comment on column GAPSUSR.ICPS_WBC_TM_APP_MAIN.SPREADER_BANK is
'推广人所属分行';

comment on column GAPSUSR.ICPS_WBC_TM_APP_MAIN.SPREADER_WAY is
'推广方式';

comment on column GAPSUSR.ICPS_WBC_TM_APP_MAIN.SPREADER_TYPE is
'推广渠道';

comment on column GAPSUSR.ICPS_WBC_TM_APP_MAIN.SPREADER_NAME is
'推广人姓名';

comment on column GAPSUSR.ICPS_WBC_TM_APP_MAIN.SPREADER_NUM_PRE is
'推广单位预审人编号';

comment on column GAPSUSR.ICPS_WBC_TM_APP_MAIN.SPREADER_PHONE is
'推广人手机号码';

comment on column GAPSUSR.ICPS_WBC_TM_APP_MAIN.SALES_IND is
'是否接受推广邮件';

comment on column GAPSUSR.ICPS_WBC_TM_APP_MAIN.OWNING_BRANCH is
'发卡网点';

comment on column GAPSUSR.ICPS_WBC_TM_APP_MAIN.APP_PROMOTION_CD is
'促销码';

comment on column GAPSUSR.ICPS_WBC_TM_APP_MAIN.APP_SOURCE is
'申请来源';

comment on column GAPSUSR.ICPS_WBC_TM_APP_MAIN.BANK_CUSTOMER_ID is
'行内客户号';

comment on column GAPSUSR.ICPS_WBC_TM_APP_MAIN.DD_FLAG is
'约定扣款是否开通标识';

comment on column GAPSUSR.ICPS_WBC_TM_APP_MAIN.DEDUCT_DEAL_NO is
'自扣协议号';

comment on column GAPSUSR.ICPS_WBC_TM_APP_MAIN.IF_REFUSE is
'是否拒绝';

comment on column GAPSUSR.ICPS_WBC_TM_APP_MAIN.IF_END is
'是否处理完成件';

comment on column GAPSUSR.ICPS_WBC_TM_APP_MAIN.APPLY_FROM_TYPE is
'申请来源类别';

comment on column GAPSUSR.ICPS_WBC_TM_APP_MAIN.APPNO_EXTERNAL is
'申请编号_外部送入';

comment on column GAPSUSR.ICPS_WBC_TM_APP_MAIN.APPNO_ATTACH_EXTERNAL is
'附卡申请编号_外部送入';

comment on column GAPSUSR.ICPS_WBC_TM_APP_MAIN.REMARK is
'备注';

comment on column GAPSUSR.ICPS_WBC_TM_APP_MAIN.CREATE_USER is
'创建人';

comment on column GAPSUSR.ICPS_WBC_TM_APP_MAIN.UPDATE_USER is
'修改人';

comment on column GAPSUSR.ICPS_WBC_TM_APP_MAIN.BIZ_NO is
'业务流水号';

comment on column GAPSUSR.ICPS_WBC_TM_APP_MAIN.TRACE_NO is
'调起方流水号';

comment on column GAPSUSR.ICPS_WBC_TM_APP_MAIN.CALLED_NO is
'被调方流水号';

comment on column GAPSUSR.ICPS_WBC_TM_APP_MAIN.RESULT_CODE is
'审批结果码';

comment on column GAPSUSR.ICPS_WBC_TM_APP_MAIN.CREATED_DATETIME is
'创建时间';

comment on column GAPSUSR.ICPS_WBC_TM_APP_MAIN.LAST_MODIFIED_DATETIME is
'最后修改时间';

comment on column GAPSUSR.ICPS_WBC_TM_APP_MAIN.JPA_VERSION is
'乐观锁';

comment on column GAPSUSR.ICPS_WBC_TM_APP_MAIN.IS_SHARED_CREDIT_LIMIT is
'是否共享额度';

comment on column GAPSUSR.ICPS_WBC_TM_APP_MAIN.APPROVAL_DATETIME is
'审批通过时间';

comment on column GAPSUSR.ICPS_WBC_TM_APP_MAIN.IS_CHECK_FLAG is
'参与对账标识';

comment on column GAPSUSR.ICPS_WBC_TM_APP_MAIN.EXTEND_PARAM1 is
'扩展1';

comment on column GAPSUSR.ICPS_WBC_TM_APP_MAIN.EXTEND_PARAM2 is
'扩展2';

comment on column GAPSUSR.ICPS_WBC_TM_APP_MAIN.EXTEND_PARAM3 is
'扩展3';

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
'主卡申请人信息表';

comment on column GAPSUSR.ICPS_WBC_TM_APP_PRIM_APPLICANT_INFO.BUSI_DATE is
'业务日期';

comment on column GAPSUSR.ICPS_WBC_TM_APP_PRIM_APPLICANT_INFO.FILE_ORDER is
'文件序号';

comment on column GAPSUSR.ICPS_WBC_TM_APP_PRIM_APPLICANT_INFO.ID is
'标识';

comment on column GAPSUSR.ICPS_WBC_TM_APP_PRIM_APPLICANT_INFO.ORG is
'机构号';

comment on column GAPSUSR.ICPS_WBC_TM_APP_PRIM_APPLICANT_INFO.APP_NO is
'申请件编号';

comment on column GAPSUSR.ICPS_WBC_TM_APP_PRIM_APPLICANT_INFO.IF_SELECTED_CARD is
'是否自选卡号';

comment on column GAPSUSR.ICPS_WBC_TM_APP_PRIM_APPLICANT_INFO.CARD_NO is
'卡号';

comment on column GAPSUSR.ICPS_WBC_TM_APP_PRIM_APPLICANT_INFO."NAME" is
'姓名';

comment on column GAPSUSR.ICPS_WBC_TM_APP_PRIM_APPLICANT_INFO.EMB_LOGO is
'凸印名称';

comment on column GAPSUSR.ICPS_WBC_TM_APP_PRIM_APPLICANT_INFO.GENDER is
'性别';

comment on column GAPSUSR.ICPS_WBC_TM_APP_PRIM_APPLICANT_INFO.NATIONALITY is
'国籍';

comment on column GAPSUSR.ICPS_WBC_TM_APP_PRIM_APPLICANT_INFO.RESIDENCY_COUNTRY_CD is
'永久居住地国家代码';

comment on column GAPSUSR.ICPS_WBC_TM_APP_PRIM_APPLICANT_INFO.ID_TYPE is
'证件类型';

comment on column GAPSUSR.ICPS_WBC_TM_APP_PRIM_APPLICANT_INFO.ID_NO is
'证件号码';

comment on column GAPSUSR.ICPS_WBC_TM_APP_PRIM_APPLICANT_INFO.ID_LAST_DATE is
'证件到期日';

comment on column GAPSUSR.ICPS_WBC_TM_APP_PRIM_APPLICANT_INFO.ID_ISSUER_ADDRESS is
'发证机关所在地址';

comment on column GAPSUSR.ICPS_WBC_TM_APP_PRIM_APPLICANT_INFO.BIRTHDAY is
'生日';

comment on column GAPSUSR.ICPS_WBC_TM_APP_PRIM_APPLICANT_INFO.LIQUID_ASSET is
'个人资产类型';

comment on column GAPSUSR.ICPS_WBC_TM_APP_PRIM_APPLICANT_INFO.YEAR_INCOME is
'年收入';

comment on column GAPSUSR.ICPS_WBC_TM_APP_PRIM_APPLICANT_INFO.QUALIFICATION is
'教育状况';

comment on column GAPSUSR.ICPS_WBC_TM_APP_PRIM_APPLICANT_INFO.MARITAL_STATUS is
'婚姻状况';

comment on column GAPSUSR.ICPS_WBC_TM_APP_PRIM_APPLICANT_INFO.HOME_ADDR_CTRY_CD is
'家庭国家代码';

comment on column GAPSUSR.ICPS_WBC_TM_APP_PRIM_APPLICANT_INFO.HOME_STATE is
'家庭所在省';

comment on column GAPSUSR.ICPS_WBC_TM_APP_PRIM_APPLICANT_INFO.HOME_CITY is
'家庭所在市';

comment on column GAPSUSR.ICPS_WBC_TM_APP_PRIM_APPLICANT_INFO.HOME_ZONE is
'家庭所在区县';

comment on column GAPSUSR.ICPS_WBC_TM_APP_PRIM_APPLICANT_INFO.HOUSE_OWNERSHIP is
'房屋持有类型';

comment on column GAPSUSR.ICPS_WBC_TM_APP_PRIM_APPLICANT_INFO.HOME_ADD is
'家庭地址';

comment on column GAPSUSR.ICPS_WBC_TM_APP_PRIM_APPLICANT_INFO.HOME_POSTCODE is
'家庭住宅邮编';

comment on column GAPSUSR.ICPS_WBC_TM_APP_PRIM_APPLICANT_INFO.HOME_PHONE is
'家庭电话';

comment on column GAPSUSR.ICPS_WBC_TM_APP_PRIM_APPLICANT_INFO.HOME_STAND_FROM is
'现住址居住起始年月';

comment on column GAPSUSR.ICPS_WBC_TM_APP_PRIM_APPLICANT_INFO.CELLPHONE is
'移动电话';

comment on column GAPSUSR.ICPS_WBC_TM_APP_PRIM_APPLICANT_INFO.EMAIL is
'电子邮箱';

comment on column GAPSUSR.ICPS_WBC_TM_APP_PRIM_APPLICANT_INFO.QQ_ACCT is
'QQ账号';

comment on column GAPSUSR.ICPS_WBC_TM_APP_PRIM_APPLICANT_INFO.OPEN_ID is
'公众号';

comment on column GAPSUSR.ICPS_WBC_TM_APP_PRIM_APPLICANT_INFO.HOUSE_TYPE is
'住宅类型';

comment on column GAPSUSR.ICPS_WBC_TM_APP_PRIM_APPLICANT_INFO.FAMILY_MEMBER is
'家庭人口';

comment on column GAPSUSR.ICPS_WBC_TM_APP_PRIM_APPLICANT_INFO.FAMILY_AVGE_VENUE is
'家庭人均年收入';

comment on column GAPSUSR.ICPS_WBC_TM_APP_PRIM_APPLICANT_INFO.BANKMEM_FLAG is
'是否行内员工';

comment on column GAPSUSR.ICPS_WBC_TM_APP_PRIM_APPLICANT_INFO.BANKMEMBER_NO is
'本行员工号';

comment on column GAPSUSR.ICPS_WBC_TM_APP_PRIM_APPLICANT_INFO.CORP_NAME is
'公司名称';

comment on column GAPSUSR.ICPS_WBC_TM_APP_PRIM_APPLICANT_INFO.EMP_ADDR_CTRY_CD is
'公司国家代码';

comment on column GAPSUSR.ICPS_WBC_TM_APP_PRIM_APPLICANT_INFO.EMP_PROVINCE is
'公司所在省';

comment on column GAPSUSR.ICPS_WBC_TM_APP_PRIM_APPLICANT_INFO.EMP_CITY is
'公司所在市';

comment on column GAPSUSR.ICPS_WBC_TM_APP_PRIM_APPLICANT_INFO.EMP_ZONE is
'公司所在区/县';

comment on column GAPSUSR.ICPS_WBC_TM_APP_PRIM_APPLICANT_INFO.EMP_ADD is
'公司地址';

comment on column GAPSUSR.ICPS_WBC_TM_APP_PRIM_APPLICANT_INFO.EMP_POSTCODE is
'公司邮编';

comment on column GAPSUSR.ICPS_WBC_TM_APP_PRIM_APPLICANT_INFO.EMP_PHONE is
'公司电话';

comment on column GAPSUSR.ICPS_WBC_TM_APP_PRIM_APPLICANT_INFO.EMP_DEPAPMENT is
'任职部门';

comment on column GAPSUSR.ICPS_WBC_TM_APP_PRIM_APPLICANT_INFO.EMP_POST is
'职务';

comment on column GAPSUSR.ICPS_WBC_TM_APP_PRIM_APPLICANT_INFO.EMP_STRUCTURE is
'公司性质';

comment on column GAPSUSR.ICPS_WBC_TM_APP_PRIM_APPLICANT_INFO.EMP_TYPE is
'公司行业类别';

comment on column GAPSUSR.ICPS_WBC_TM_APP_PRIM_APPLICANT_INFO.EMP_WORKYEARS is
'本公司工作年限';

comment on column GAPSUSR.ICPS_WBC_TM_APP_PRIM_APPLICANT_INFO.CORP_FAX is
'公司传真';

comment on column GAPSUSR.ICPS_WBC_TM_APP_PRIM_APPLICANT_INFO.OCCUPATION is
'职业';

comment on column GAPSUSR.ICPS_WBC_TM_APP_PRIM_APPLICANT_INFO.TITLE_OF_TECHNICAL is
'职称';

comment on column GAPSUSR.ICPS_WBC_TM_APP_PRIM_APPLICANT_INFO.EMP_STAND_FROM is
'现单位工作起始年月';

comment on column GAPSUSR.ICPS_WBC_TM_APP_PRIM_APPLICANT_INFO.POS_PIN_VERIFY_IND is
'是否消费凭密';

comment on column GAPSUSR.ICPS_WBC_TM_APP_PRIM_APPLICANT_INFO.PHOTO_USE_FLAG is
'是否彩照卡';

comment on column GAPSUSR.ICPS_WBC_TM_APP_PRIM_APPLICANT_INFO.GROUP_NUM is
'申请团办编号';

comment on column GAPSUSR.ICPS_WBC_TM_APP_PRIM_APPLICANT_INFO.EMP_STABILITY is
'工作稳定性';

comment on column GAPSUSR.ICPS_WBC_TM_APP_PRIM_APPLICANT_INFO.EMP_STATUS is
'是否在职';

comment on column GAPSUSR.ICPS_WBC_TM_APP_PRIM_APPLICANT_INFO.PR_OF_COUNTRY is
'是否永久居住';

comment on column GAPSUSR.ICPS_WBC_TM_APP_PRIM_APPLICANT_INFO.OTHER_ASK is
'预留问题';

comment on column GAPSUSR.ICPS_WBC_TM_APP_PRIM_APPLICANT_INFO.OTHER_ANSWER is
'预留答案';

comment on column GAPSUSR.ICPS_WBC_TM_APP_PRIM_APPLICANT_INFO.PRI_NAME is
'推荐人姓名';

comment on column GAPSUSR.ICPS_WBC_TM_APP_PRIM_APPLICANT_INFO.PRI_CARD_NUM is
'推荐人卡号';

comment on column GAPSUSR.ICPS_WBC_TM_APP_PRIM_APPLICANT_INFO.APPNO_EXTERNAL is
'申请编号_外部送入';

comment on column GAPSUSR.ICPS_WBC_TM_APP_PRIM_APPLICANT_INFO.BANK_CUSTOMER_ID is
'行内客户号';

comment on column GAPSUSR.ICPS_WBC_TM_APP_PRIM_APPLICANT_INFO.REF_CONTACT_ID is
'推荐人联系号码';

comment on column GAPSUSR.ICPS_WBC_TM_APP_PRIM_APPLICANT_INFO.REF_CONTACT_TYPE is
'推荐人联系号码类型';

comment on column GAPSUSR.ICPS_WBC_TM_APP_PRIM_APPLICANT_INFO.PLEDEG_TYPE is
'押品类型';

comment on column GAPSUSR.ICPS_WBC_TM_APP_PRIM_APPLICANT_INFO.UPDATE_USER is
'修改人';

comment on column GAPSUSR.ICPS_WBC_TM_APP_PRIM_APPLICANT_INFO.CREATE_USER is
'创建人';

comment on column GAPSUSR.ICPS_WBC_TM_APP_PRIM_APPLICANT_INFO.CREATED_DATETIME is
'创建时间';

comment on column GAPSUSR.ICPS_WBC_TM_APP_PRIM_APPLICANT_INFO.LAST_MODIFIED_DATETIME is
'最后修改时间';

comment on column GAPSUSR.ICPS_WBC_TM_APP_PRIM_APPLICANT_INFO.JPA_VERSION is
'乐观锁';

comment on column GAPSUSR.ICPS_WBC_TM_APP_PRIM_APPLICANT_INFO.CUST_NO is
'客户号';

comment on column GAPSUSR.ICPS_WBC_TM_APP_PRIM_APPLICANT_INFO.ACCT_NO is
'账户号';

comment on column GAPSUSR.ICPS_WBC_TM_APP_PRIM_APPLICANT_INFO.PRODUCT_CD is
'产品编号';

comment on column GAPSUSR.ICPS_WBC_TM_APP_PRIM_APPLICANT_INFO.OPEN_ACC_DATETIME is
'开户时间';

comment on column GAPSUSR.ICPS_WBC_TM_APP_PRIM_APPLICANT_INFO.IS_CHECK_FLAG is
'参与对账标识';

comment on column GAPSUSR.ICPS_WBC_TM_APP_PRIM_APPLICANT_INFO.EXTEND_PARAM1 is
'扩展1';

comment on column GAPSUSR.ICPS_WBC_TM_APP_PRIM_APPLICANT_INFO.EXTEND_PARAM2 is
'扩展2';

comment on column GAPSUSR.ICPS_WBC_TM_APP_PRIM_APPLICANT_INFO.EXTEND_PARAM3 is
'扩展3';

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
'授权流水银团拆分表';

comment on column GAPSUSR.ICPS_WBC_TM_AUTH_BANK_COST.BUSI_DATE is
'业务日期';

comment on column GAPSUSR.ICPS_WBC_TM_AUTH_BANK_COST.FILE_ORDER is
'文件序号';

comment on column GAPSUSR.ICPS_WBC_TM_AUTH_BANK_COST.CONSUMER_TRANS_ID is
'业务流水号';

comment on column GAPSUSR.ICPS_WBC_TM_AUTH_BANK_COST.BANK_GROUP_ID is
'银团编号';

comment on column GAPSUSR.ICPS_WBC_TM_AUTH_BANK_COST.BANK_NO is
'银行号';

comment on column GAPSUSR.ICPS_WBC_TM_AUTH_BANK_COST.REG_TYPE is
'登记类型';

comment on column GAPSUSR.ICPS_WBC_TM_AUTH_BANK_COST.REG_AMT is
'登记金额';

comment on column GAPSUSR.ICPS_WBC_TM_AUTH_BANK_COST.REG_STATUS is
'登记状态';

comment on column GAPSUSR.ICPS_WBC_TM_AUTH_BANK_COST.BIZ_DATE is
'业务日期';

comment on column GAPSUSR.ICPS_WBC_TM_AUTH_BANK_COST.REG_SYS_ID is
'记账流水号';

comment on column GAPSUSR.ICPS_WBC_TM_AUTH_BANK_COST.REG_DATE is
'记账日期';

comment on column GAPSUSR.ICPS_WBC_TM_AUTH_BANK_COST.REG_TIME is
'记账请求时间';

comment on column GAPSUSR.ICPS_WBC_TM_AUTH_BANK_COST.RECON_CODE is
'对账码';

comment on column GAPSUSR.ICPS_WBC_TM_AUTH_BANK_COST.ORI_SYS_ID is
'原记账流水号';

comment on column GAPSUSR.ICPS_WBC_TM_AUTH_BANK_COST.CUST_ID is
'客户编号';

comment on column GAPSUSR.ICPS_WBC_TM_AUTH_BANK_COST.ACCT_NO is
'账户编号';

comment on column GAPSUSR.ICPS_WBC_TM_AUTH_BANK_COST.ACCT_TYPE is
'账户类型';

comment on column GAPSUSR.ICPS_WBC_TM_AUTH_BANK_COST.RETRY is
'尝试次数';

comment on column GAPSUSR.ICPS_WBC_TM_AUTH_BANK_COST.CREATED_DATETIME is
'创建时间';

comment on column GAPSUSR.ICPS_WBC_TM_AUTH_BANK_COST.LAST_MODIFIED_DATETIME is
'时间戳';

comment on column GAPSUSR.ICPS_WBC_TM_AUTH_BANK_COST.JPA_VERSION is
'乐观锁版本号';

comment on column GAPSUSR.ICPS_WBC_TM_AUTH_BANK_COST.CARD_NO is
'卡号';

comment on column GAPSUSR.ICPS_WBC_TM_AUTH_BANK_COST.IS_CHECK_FLAG is
'参与对账标识';

comment on column GAPSUSR.ICPS_WBC_TM_AUTH_BANK_COST.EXTEND_PARAM1 is
'扩展1';

comment on column GAPSUSR.ICPS_WBC_TM_AUTH_BANK_COST.EXTEND_PARAM2 is
'扩展2';

comment on column GAPSUSR.ICPS_WBC_TM_AUTH_BANK_COST.EXTEND_PARAM3 is
'扩展3';

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
'授权流水银团拆分明细表';

comment on column GAPSUSR.ICPS_WBC_TM_AUTH_BANK_COST_DTL.BUSI_DATE is
'业务日期';

comment on column GAPSUSR.ICPS_WBC_TM_AUTH_BANK_COST_DTL.FILE_ORDER is
'文件序号';

comment on column GAPSUSR.ICPS_WBC_TM_AUTH_BANK_COST_DTL.CONSUMER_TRANS_ID is
'业务流水号';

comment on column GAPSUSR.ICPS_WBC_TM_AUTH_BANK_COST_DTL.BANK_GROUP_ID is
'银团编号';

comment on column GAPSUSR.ICPS_WBC_TM_AUTH_BANK_COST_DTL.BANK_NO is
'银行号';

comment on column GAPSUSR.ICPS_WBC_TM_AUTH_BANK_COST_DTL.LOAN_RECEIPT_NBR is
'借据号';

comment on column GAPSUSR.ICPS_WBC_TM_AUTH_BANK_COST_DTL.REG_TYPE is
'登记类型';

comment on column GAPSUSR.ICPS_WBC_TM_AUTH_BANK_COST_DTL.REG_AMT is
'登记金额';

comment on column GAPSUSR.ICPS_WBC_TM_AUTH_BANK_COST_DTL.BIZ_DATE is
'业务日期';

comment on column GAPSUSR.ICPS_WBC_TM_AUTH_BANK_COST_DTL.CUST_ID is
'客户编号';

comment on column GAPSUSR.ICPS_WBC_TM_AUTH_BANK_COST_DTL.ACCT_NO is
'账户编号';

comment on column GAPSUSR.ICPS_WBC_TM_AUTH_BANK_COST_DTL.ACCT_TYPE is
'账户类型';

comment on column GAPSUSR.ICPS_WBC_TM_AUTH_BANK_COST_DTL.CREATED_DATETIME is
'创建时间';

comment on column GAPSUSR.ICPS_WBC_TM_AUTH_BANK_COST_DTL.LAST_MODIFIED_DATETIME is
'时间戳';

comment on column GAPSUSR.ICPS_WBC_TM_AUTH_BANK_COST_DTL.CARD_NO is
'卡号';

comment on column GAPSUSR.ICPS_WBC_TM_AUTH_BANK_COST_DTL.IS_CHECK_FLAG is
'参与对账标识';

comment on column GAPSUSR.ICPS_WBC_TM_AUTH_BANK_COST_DTL.EXTEND_PARAM1 is
'扩展1';

comment on column GAPSUSR.ICPS_WBC_TM_AUTH_BANK_COST_DTL.EXTEND_PARAM2 is
'扩展2';

comment on column GAPSUSR.ICPS_WBC_TM_AUTH_BANK_COST_DTL.EXTEND_PARAM3 is
'扩展3';

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
'授权交易历史';

comment on column GAPSUSR.ICPS_WBC_TM_AUTH_HST.BUSI_DATE is
'业务日期';

comment on column GAPSUSR.ICPS_WBC_TM_AUTH_HST.FILE_ORDER is
'文件序号';

comment on column GAPSUSR.ICPS_WBC_TM_AUTH_HST.ORG is
'机构号';

comment on column GAPSUSR.ICPS_WBC_TM_AUTH_HST.LOG_KV is
'LOG的键值';

comment on column GAPSUSR.ICPS_WBC_TM_AUTH_HST.ACCT_NO is
'账户编号';

comment on column GAPSUSR.ICPS_WBC_TM_AUTH_HST.ACCT_TYPE is
'账户类型';

comment on column GAPSUSR.ICPS_WBC_TM_AUTH_HST.LOGICAL_CARD_NO is
'逻辑卡号';

comment on column GAPSUSR.ICPS_WBC_TM_AUTH_HST.ACQ_REF_NO is
'受理机构交易编码';

comment on column GAPSUSR.ICPS_WBC_TM_AUTH_HST.TXN_AMT is
'交易金额';

comment on column GAPSUSR.ICPS_WBC_TM_AUTH_HST.TXN_CURR_CD is
'交易币种代码';

comment on column GAPSUSR.ICPS_WBC_TM_AUTH_HST.AUTH_CODE is
'授权码';

comment on column GAPSUSR.ICPS_WBC_TM_AUTH_HST.ACQ_NAME_ADDR is
'受理机构名称地址';

comment on column GAPSUSR.ICPS_WBC_TM_AUTH_HST.CHB_TXN_AMT is
'持卡人账户币种金额';

comment on column GAPSUSR.ICPS_WBC_TM_AUTH_HST.CHB_CURR_CD is
'持卡人账户币种';

comment on column GAPSUSR.ICPS_WBC_TM_AUTH_HST.CHANNEL is
'交易渠道';

comment on column GAPSUSR.ICPS_WBC_TM_AUTH_HST.MCC is
'商户类别代码';

comment on column GAPSUSR.ICPS_WBC_TM_AUTH_HST.ACQ_BRANCH_ID is
'受理分行代码';

comment on column GAPSUSR.ICPS_WBC_TM_AUTH_HST.FWD_INST_ID is
'转发机构号';

comment on column GAPSUSR.ICPS_WBC_TM_AUTH_HST.TRANSMISSION_TIMESTAMP is
'传送日期';

comment on column GAPSUSR.ICPS_WBC_TM_AUTH_HST.SETTLE_DATE is
'清算日期';

comment on column GAPSUSR.ICPS_WBC_TM_AUTH_HST.TXN_DIRECTION is
'交易方向';

comment on column GAPSUSR.ICPS_WBC_TM_AUTH_HST.TXN_TERMINAL is
'交易终端';

comment on column GAPSUSR.ICPS_WBC_TM_AUTH_HST.TXN_STATUS is
'交易状态';

comment on column GAPSUSR.ICPS_WBC_TM_AUTH_HST.TXN_TYPE is
'交易类型';

comment on column GAPSUSR.ICPS_WBC_TM_AUTH_HST.LOG_OL_TIME is
'LOG联机时间';

comment on column GAPSUSR.ICPS_WBC_TM_AUTH_HST.LOG_BIZ_DATE is
'联机业务日期';

comment on column GAPSUSR.ICPS_WBC_TM_AUTH_HST.MTI is
'交易类型标识';

comment on column GAPSUSR.ICPS_WBC_TM_AUTH_HST.ORIG_TXN_TYPE is
'原交易类型';

comment on column GAPSUSR.ICPS_WBC_TM_AUTH_HST.ORIG_FWD_INST_ID is
'原始转发机构号';

comment on column GAPSUSR.ICPS_WBC_TM_AUTH_HST.ORIG_ACQ_INST_ID is
'原始受理机构号';

comment on column GAPSUSR.ICPS_WBC_TM_AUTH_HST.ORIG_MTI is
'原交易MTI';

comment on column GAPSUSR.ICPS_WBC_TM_AUTH_HST.ORIG_TRANS_DATE is
'原始交易日期';

comment on column GAPSUSR.ICPS_WBC_TM_AUTH_HST.ORIG_TRACE_NO is
'原始系统跟踪号';

comment on column GAPSUSR.ICPS_WBC_TM_AUTH_HST.ORIG_TXN_PROC is
'原交易处理码';

comment on column GAPSUSR.ICPS_WBC_TM_AUTH_HST.ORIG_TXN_AMT is
'原始交易币种金额';

comment on column GAPSUSR.ICPS_WBC_TM_AUTH_HST.ORIG_LOG_KV is
'原交易LOG键值';

comment on column GAPSUSR.ICPS_WBC_TM_AUTH_HST.ORIG_TXN_VAL_1 is
'原交易键值1';

comment on column GAPSUSR.ICPS_WBC_TM_AUTH_HST.ORIG_TXN_VAL_2 is
'原交易键值2';

comment on column GAPSUSR.ICPS_WBC_TM_AUTH_HST.ORIG_CHB_TXN_AMT is
'原始入账币种金额';

comment on column GAPSUSR.ICPS_WBC_TM_AUTH_HST.ORIG_BIZ_DATE is
'原交易的联机业务处理日期';

comment on column GAPSUSR.ICPS_WBC_TM_AUTH_HST.LAST_REVERSAL_DATE is
'最后一次冲撤时间';

comment on column GAPSUSR.ICPS_WBC_TM_AUTH_HST.VOID_COUNT is
'撤销次数';

comment on column GAPSUSR.ICPS_WBC_TM_AUTH_HST.MANUAL_AUTH_FLAG is
'人工授权标志';

comment on column GAPSUSR.ICPS_WBC_TM_AUTH_HST.OPERA_ID is
'操作员ID';

comment on column GAPSUSR.ICPS_WBC_TM_AUTH_HST.BRAND is
'品牌';

comment on column GAPSUSR.ICPS_WBC_TM_AUTH_HST.PRODUCT_CD is
'产品代码';

comment on column GAPSUSR.ICPS_WBC_TM_AUTH_HST.MCC_TYPE is
'商户类型分组';

comment on column GAPSUSR.ICPS_WBC_TM_AUTH_HST.FINAL_REASON is
'授权原因';

comment on column GAPSUSR.ICPS_WBC_TM_AUTH_HST.FINAL_ACTION is
'最终行动';

comment on column GAPSUSR.ICPS_WBC_TM_AUTH_HST.COMP_AMT is
'最终授权金额';

comment on column GAPSUSR.ICPS_WBC_TM_AUTH_HST.FINAL_UPD_DIRECTION is
'最终更新方向';

comment on column GAPSUSR.ICPS_WBC_TM_AUTH_HST.FINAL_UPD_AMT is
'最终更新金额';

comment on column GAPSUSR.ICPS_WBC_TM_AUTH_HST.IC_IND is
'是否IC卡';

comment on column GAPSUSR.ICPS_WBC_TM_AUTH_HST.THE_3DSECURE_TYPE is
'是否3D电子安全交易';

comment on column GAPSUSR.ICPS_WBC_TM_AUTH_HST.VIP_STATUS is
'VIP状态';

comment on column GAPSUSR.ICPS_WBC_TM_AUTH_HST.CURR_BAL is
'当前余额';

comment on column GAPSUSR.ICPS_WBC_TM_AUTH_HST.CASH_AMT is
'取现金额';

comment on column GAPSUSR.ICPS_WBC_TM_AUTH_HST.OTB is
'可用额度';

comment on column GAPSUSR.ICPS_WBC_TM_AUTH_HST.CASH_OTB is
'取现可用额度';

comment on column GAPSUSR.ICPS_WBC_TM_AUTH_HST.CUST_OTB is
'客户可用额度';

comment on column GAPSUSR.ICPS_WBC_TM_AUTH_HST.CARD_BLACK_FLAG is
'是否账户黑名单';

comment on column GAPSUSR.ICPS_WBC_TM_AUTH_HST.MERCHANT_BLACK_FLAG is
'是否商户黑名单';

comment on column GAPSUSR.ICPS_WBC_TM_AUTH_HST.EXPIRE_DATE is
'有效日期';

comment on column GAPSUSR.ICPS_WBC_TM_AUTH_HST.TRACK_ONE_RESULT is
'一磁道完整性结果';

comment on column GAPSUSR.ICPS_WBC_TM_AUTH_HST.TRACK_TWO_RESULT is
'二磁道完整性结果';

comment on column GAPSUSR.ICPS_WBC_TM_AUTH_HST.TRACK_THREE_RESULT is
'三磁道完整性结果';

comment on column GAPSUSR.ICPS_WBC_TM_AUTH_HST.PWD_TYPE is
'密码种类';

comment on column GAPSUSR.ICPS_WBC_TM_AUTH_HST.CHECK_PWD_RESULT is
'验证密码结果';

comment on column GAPSUSR.ICPS_WBC_TM_AUTH_HST.PAY_PWD_ERR_NUM is
'支付密码错误次数';

comment on column GAPSUSR.ICPS_WBC_TM_AUTH_HST.CHECK_CVV_RESULT is
'CVV验证结果';

comment on column GAPSUSR.ICPS_WBC_TM_AUTH_HST.CHECK_CVV2_RESULT is
'CVV2验证结果';

comment on column GAPSUSR.ICPS_WBC_TM_AUTH_HST.CHECK_ICVN_RESULT is
'ICVN验证结果';

comment on column GAPSUSR.ICPS_WBC_TM_AUTH_HST.CHECK_ARQC_RESULT is
'ARQC验证结果';

comment on column GAPSUSR.ICPS_WBC_TM_AUTH_HST.CHECK_ATC_RESULT is
'ATC验证结果';

comment on column GAPSUSR.ICPS_WBC_TM_AUTH_HST.CHECK_CVR_RESULT is
'CVR验证结果';

comment on column GAPSUSR.ICPS_WBC_TM_AUTH_HST.CHECK_TVR_RESULT is
'TVR验证结果';

comment on column GAPSUSR.ICPS_WBC_TM_AUTH_HST.REJ_REASON is
'拒绝原因';

comment on column GAPSUSR.ICPS_WBC_TM_AUTH_HST.UNMATCH_CR is
'未匹配贷记金额';

comment on column GAPSUSR.ICPS_WBC_TM_AUTH_HST.UNMATCH_DB is
'未匹配借记金额';

comment on column GAPSUSR.ICPS_WBC_TM_AUTH_HST.B002 is
'介质卡号-B002';

comment on column GAPSUSR.ICPS_WBC_TM_AUTH_HST.B003 is
'交易处理码-B003';

comment on column GAPSUSR.ICPS_WBC_TM_AUTH_HST.B007 is
'交易传输时间-B007';

comment on column GAPSUSR.ICPS_WBC_TM_AUTH_HST.B011 is
'系统跟踪号-B011';

comment on column GAPSUSR.ICPS_WBC_TM_AUTH_HST.B022 is
'服务点PIN获取码-B022';

comment on column GAPSUSR.ICPS_WBC_TM_AUTH_HST.B025 is
'服务点条件码-B025';

comment on column GAPSUSR.ICPS_WBC_TM_AUTH_HST.B032 is
'受理机构标识码-B032';

comment on column GAPSUSR.ICPS_WBC_TM_AUTH_HST.B033 is
'受理机构名称地址-B033';

comment on column GAPSUSR.ICPS_WBC_TM_AUTH_HST.B039 is
'返回码-B039';

comment on column GAPSUSR.ICPS_WBC_TM_AUTH_HST.B042 is
'受卡方(商户)标识码-B042';

comment on column GAPSUSR.ICPS_WBC_TM_AUTH_HST.B060 is
'自定义域-B060';

comment on column GAPSUSR.ICPS_WBC_TM_AUTH_HST.B061 is
'持卡人身份认证信息-B061';

comment on column GAPSUSR.ICPS_WBC_TM_AUTH_HST.B090 is
'原始数据元';

comment on column GAPSUSR.ICPS_WBC_TM_AUTH_HST.OPERA_TERM_ID is
'操作用户终端编号';

comment on column GAPSUSR.ICPS_WBC_TM_AUTH_HST.JPA_VERSION is
'乐观锁版本号';

comment on column GAPSUSR.ICPS_WBC_TM_AUTH_HST.B004 is
'交易货币金额-B004';

comment on column GAPSUSR.ICPS_WBC_TM_AUTH_HST.B006 is
'账户货币金额-B006';

comment on column GAPSUSR.ICPS_WBC_TM_AUTH_HST.B049 is
'交易货币代码-B049';

comment on column GAPSUSR.ICPS_WBC_TM_AUTH_HST.B051 is
'账户货币代码-B051';

comment on column GAPSUSR.ICPS_WBC_TM_AUTH_HST.B037 is
'检索参考号-B037';

comment on column GAPSUSR.ICPS_WBC_TM_AUTH_HST.B028 is
'手续费-B028';

comment on column GAPSUSR.ICPS_WBC_TM_AUTH_HST.B048 is
'附加数据-B048';

comment on column GAPSUSR.ICPS_WBC_TM_AUTH_HST.B054 is
'返回余额数组-B054';

comment on column GAPSUSR.ICPS_WBC_TM_AUTH_HST.CARD_BLOCK_CODE is
'卡片锁定码';

comment on column GAPSUSR.ICPS_WBC_TM_AUTH_HST.ACCOUNT_BLOCK_CODE is
'帐户锁定码';

comment on column GAPSUSR.ICPS_WBC_TM_AUTH_HST.MEDIUM_BLOCK_CODE is
'介质锁定码';

comment on column GAPSUSR.ICPS_WBC_TM_AUTH_HST.CONSUMER_TRANS_ID is
'业务流水号';

comment on column GAPSUSR.ICPS_WBC_TM_AUTH_HST.SYS_TRANS_ID is
'系统调用流水号';

comment on column GAPSUSR.ICPS_WBC_TM_AUTH_HST.QCHANNEL_ID is
'渠道编号';

comment on column GAPSUSR.ICPS_WBC_TM_AUTH_HST.SUB_TERMINAL_TYPE is
'终端类型';

comment on column GAPSUSR.ICPS_WBC_TM_AUTH_HST.SUB_MERCH_ID is
'二级商户编码';

comment on column GAPSUSR.ICPS_WBC_TM_AUTH_HST.SUB_MERCH_NAME is
'二级商户名称';

comment on column GAPSUSR.ICPS_WBC_TM_AUTH_HST.WARES_DESC is
'商品信息';

comment on column GAPSUSR.ICPS_WBC_TM_AUTH_HST.LAST_MODIFIED_DATETIME is
'修改时间';

comment on column GAPSUSR.ICPS_WBC_TM_AUTH_HST.PART_MONTH is
'分区用的月份';

comment on column GAPSUSR.ICPS_WBC_TM_AUTH_HST.PAID_STMT_DATE is
'还款账单日';

comment on column GAPSUSR.ICPS_WBC_TM_AUTH_HST.REPAY_AMT is
'应还款额';

comment on column GAPSUSR.ICPS_WBC_TM_AUTH_HST.TRANSFER_TYPE is
'转账类型';

comment on column GAPSUSR.ICPS_WBC_TM_AUTH_HST.IS_CHECK_FLAG is
'参与对账标识';

comment on column GAPSUSR.ICPS_WBC_TM_AUTH_HST.EXTEND_PARAM1 is
'扩展1';

comment on column GAPSUSR.ICPS_WBC_TM_AUTH_HST.EXTEND_PARAM2 is
'扩展2';

comment on column GAPSUSR.ICPS_WBC_TM_AUTH_HST.EXTEND_PARAM3 is
'扩展3';

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
'银行表';

comment on column GAPSUSR.ICPS_WBC_TM_BANK.BUSI_DATE is
'业务日期';

comment on column GAPSUSR.ICPS_WBC_TM_BANK.FILE_ORDER is
'文件序号';

comment on column GAPSUSR.ICPS_WBC_TM_BANK.BANK_NO is
'银行号';

comment on column GAPSUSR.ICPS_WBC_TM_BANK.BANK_NAME is
'银行名称';

comment on column GAPSUSR.ICPS_WBC_TM_BANK.PAYING_ACCT is
'备付金账户号';

comment on column GAPSUSR.ICPS_WBC_TM_BANK.IS_CHECK_FLAG is
'参与对账标识';

comment on column GAPSUSR.ICPS_WBC_TM_BANK.EXTEND_PARAM1 is
'扩展1';

comment on column GAPSUSR.ICPS_WBC_TM_BANK.EXTEND_PARAM2 is
'扩展2';

comment on column GAPSUSR.ICPS_WBC_TM_BANK.EXTEND_PARAM3 is
'扩展3';

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
'银行决策结果表';

comment on column GAPSUSR.ICPS_WBC_TM_BANK_CREDIT_RESULT.BUSI_DATE is
'业务日期';

comment on column GAPSUSR.ICPS_WBC_TM_BANK_CREDIT_RESULT.FILE_ORDER is
'文件序号';

comment on column GAPSUSR.ICPS_WBC_TM_BANK_CREDIT_RESULT.SEQ_NO is
'决策流水';

comment on column GAPSUSR.ICPS_WBC_TM_BANK_CREDIT_RESULT.BANK_NO is
'银行编号';

comment on column GAPSUSR.ICPS_WBC_TM_BANK_CREDIT_RESULT.BANK_NAME is
'银行名';

comment on column GAPSUSR.ICPS_WBC_TM_BANK_CREDIT_RESULT.ID_NO is
'证件号';

comment on column GAPSUSR.ICPS_WBC_TM_BANK_CREDIT_RESULT.ID_TYPE is
'证件类型';

comment on column GAPSUSR.ICPS_WBC_TM_BANK_CREDIT_RESULT."NAME" is
'姓名';

comment on column GAPSUSR.ICPS_WBC_TM_BANK_CREDIT_RESULT.NBS_ORDER_NO is
'订单号';

comment on column GAPSUSR.ICPS_WBC_TM_BANK_CREDIT_RESULT.CREDIT_INFO is
'征信信息';

comment on column GAPSUSR.ICPS_WBC_TM_BANK_CREDIT_RESULT.RULE_ACTION_TYPE is
'征信规则命中状态';

comment on column GAPSUSR.ICPS_WBC_TM_BANK_CREDIT_RESULT.RULE_CODE is
'征信规则规则拒绝码';

comment on column GAPSUSR.ICPS_WBC_TM_BANK_CREDIT_RESULT.RUILE_DESC is
'规则规则决策拒绝描述';

comment on column GAPSUSR.ICPS_WBC_TM_BANK_CREDIT_RESULT.IS_BL_REJ is
'黑名单命中状态';

comment on column GAPSUSR.ICPS_WBC_TM_BANK_CREDIT_RESULT.BL_REJ_CODE is
'黑名单拒绝编码';

comment on column GAPSUSR.ICPS_WBC_TM_BANK_CREDIT_RESULT.BL_REJ_DESC is
'黑名单拒绝描述';

comment on column GAPSUSR.ICPS_WBC_TM_BANK_CREDIT_RESULT.CREDIT_DATETIME is
'风险判定时间';

comment on column GAPSUSR.ICPS_WBC_TM_BANK_CREDIT_RESULT.RESULT_CODE is
'决策结果';

comment on column GAPSUSR.ICPS_WBC_TM_BANK_CREDIT_RESULT.RESULT_DESC is
'决策结果描述';

comment on column GAPSUSR.ICPS_WBC_TM_BANK_CREDIT_RESULT.CREATED_DATETIME is
'创建时间';

comment on column GAPSUSR.ICPS_WBC_TM_BANK_CREDIT_RESULT.LAST_MODIFIED_DATETIME is
'更新时间';

comment on column GAPSUSR.ICPS_WBC_TM_BANK_CREDIT_RESULT.IS_CHECK_FLAG is
'参与对账标识';

comment on column GAPSUSR.ICPS_WBC_TM_BANK_CREDIT_RESULT.EXTEND_PARAM1 is
'扩展1';

comment on column GAPSUSR.ICPS_WBC_TM_BANK_CREDIT_RESULT.EXTEND_PARAM2 is
'扩展2';

comment on column GAPSUSR.ICPS_WBC_TM_BANK_CREDIT_RESULT.EXTEND_PARAM3 is
'扩展3';

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
'银团成员表';

comment on column GAPSUSR.ICPS_WBC_TM_BANK_GROUP_MEMBER.BUSI_DATE is
'业务日期';

comment on column GAPSUSR.ICPS_WBC_TM_BANK_GROUP_MEMBER.FILE_ORDER is
'文件序号';

comment on column GAPSUSR.ICPS_WBC_TM_BANK_GROUP_MEMBER.MEMBER_ID is
'顺序号';

comment on column GAPSUSR.ICPS_WBC_TM_BANK_GROUP_MEMBER.BANK_GROUP_ID is
'银团编号';

comment on column GAPSUSR.ICPS_WBC_TM_BANK_GROUP_MEMBER.BANK_NO is
'银行号';

comment on column GAPSUSR.ICPS_WBC_TM_BANK_GROUP_MEMBER.BANK_PROPORTION is
'银行出资比例';

comment on column GAPSUSR.ICPS_WBC_TM_BANK_GROUP_MEMBER.PRODUCT_CATEGORY is
'产品大类';

comment on column GAPSUSR.ICPS_WBC_TM_BANK_GROUP_MEMBER.PRIORITY is
'出资优先级';

comment on column GAPSUSR.ICPS_WBC_TM_BANK_GROUP_MEMBER.IS_CHECK_FLAG is
'参与对账标识';

comment on column GAPSUSR.ICPS_WBC_TM_BANK_GROUP_MEMBER.EXTEND_PARAM1 is
'扩展1';

comment on column GAPSUSR.ICPS_WBC_TM_BANK_GROUP_MEMBER.EXTEND_PARAM2 is
'扩展2';

comment on column GAPSUSR.ICPS_WBC_TM_BANK_GROUP_MEMBER.EXTEND_PARAM3 is
'扩展3';

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
'客户信息表';

comment on column GAPSUSR.ICPS_WBC_TM_CUSTOMER.BUSI_DATE is
'业务日期';

comment on column GAPSUSR.ICPS_WBC_TM_CUSTOMER.FILE_ORDER is
'文件序号';

comment on column GAPSUSR.ICPS_WBC_TM_CUSTOMER.ORG is
'机构号';

comment on column GAPSUSR.ICPS_WBC_TM_CUSTOMER.CUST_ID is
'客户编号';

comment on column GAPSUSR.ICPS_WBC_TM_CUSTOMER.ID_NO is
'证件号码';

comment on column GAPSUSR.ICPS_WBC_TM_CUSTOMER.ID_TYPE is
'证件类型';

comment on column GAPSUSR.ICPS_WBC_TM_CUSTOMER.TITLE is
'称谓';

comment on column GAPSUSR.ICPS_WBC_TM_CUSTOMER."NAME" is
'姓名';

comment on column GAPSUSR.ICPS_WBC_TM_CUSTOMER.GENDER is
'性别';

comment on column GAPSUSR.ICPS_WBC_TM_CUSTOMER.BIRTHDAY is
'生日';

comment on column GAPSUSR.ICPS_WBC_TM_CUSTOMER.OCCUPATION is
'职业';

comment on column GAPSUSR.ICPS_WBC_TM_CUSTOMER.BANKMEMBER_NO is
'本行员工号';

comment on column GAPSUSR.ICPS_WBC_TM_CUSTOMER.NATIONALITY is
'国籍';

comment on column GAPSUSR.ICPS_WBC_TM_CUSTOMER.PR_OF_COUNTRY is
'是否永久居住';

comment on column GAPSUSR.ICPS_WBC_TM_CUSTOMER.RESIDENCY_COUNTRY_CD is
'永久居住地国家代码';

comment on column GAPSUSR.ICPS_WBC_TM_CUSTOMER.MARITAL_STATUS is
'婚姻状况';

comment on column GAPSUSR.ICPS_WBC_TM_CUSTOMER.QUALIFICATION is
'教育状况';

comment on column GAPSUSR.ICPS_WBC_TM_CUSTOMER.SOCIAL_STATUS is
'风险情况';

comment on column GAPSUSR.ICPS_WBC_TM_CUSTOMER.ID_ISSUER_ADDRESS is
'发证机关所在地址';

comment on column GAPSUSR.ICPS_WBC_TM_CUSTOMER.HOME_PHONE is
'家庭电话';

comment on column GAPSUSR.ICPS_WBC_TM_CUSTOMER.HOUSE_OWNERSHIP is
'房屋持有类型';

comment on column GAPSUSR.ICPS_WBC_TM_CUSTOMER.HOUSE_TYPE is
'住宅类型';

comment on column GAPSUSR.ICPS_WBC_TM_CUSTOMER.HOME_STAND_FROM is
'现住址居住起始年月';

comment on column GAPSUSR.ICPS_WBC_TM_CUSTOMER.LIQUID_ASSET is
'个人资产类型';

comment on column GAPSUSR.ICPS_WBC_TM_CUSTOMER.MOBILE_NO is
'移动电话';

comment on column GAPSUSR.ICPS_WBC_TM_CUSTOMER.EMAIL is
'电子邮箱';

comment on column GAPSUSR.ICPS_WBC_TM_CUSTOMER.EMP_STATUS is
'就业状态';

comment on column GAPSUSR.ICPS_WBC_TM_CUSTOMER.NBR_OF_DEPENDENTS is
'抚养人数';

comment on column GAPSUSR.ICPS_WBC_TM_CUSTOMER.LANGUAGE_IND is
'语言代码';

comment on column GAPSUSR.ICPS_WBC_TM_CUSTOMER.SETUP_DATE is
'创建日期';

comment on column GAPSUSR.ICPS_WBC_TM_CUSTOMER.SOCIAL_INS_AMT is
'社保缴存金额';

comment on column GAPSUSR.ICPS_WBC_TM_CUSTOMER.DRIVE_LICENSE_ID is
'驾驶证号码';

comment on column GAPSUSR.ICPS_WBC_TM_CUSTOMER.DRIVE_LIC_REG_DATE is
'驾驶证登记日期';

comment on column GAPSUSR.ICPS_WBC_TM_CUSTOMER.OBLIGATE_QUESTION is
'预留问题';

comment on column GAPSUSR.ICPS_WBC_TM_CUSTOMER.OBLIGATE_ANSWER is
'预留答案';

comment on column GAPSUSR.ICPS_WBC_TM_CUSTOMER.EMP_STABILITY is
'工作稳定性';

comment on column GAPSUSR.ICPS_WBC_TM_CUSTOMER.CORP_NAME is
'公司名称';

comment on column GAPSUSR.ICPS_WBC_TM_CUSTOMER.USER_CODE1 is
'用户自定义代码1';

comment on column GAPSUSR.ICPS_WBC_TM_CUSTOMER.USER_CODE2 is
'用户自定义代码2';

comment on column GAPSUSR.ICPS_WBC_TM_CUSTOMER.USER_CODE3 is
'用户自定义代码3';

comment on column GAPSUSR.ICPS_WBC_TM_CUSTOMER.USER_CODE4 is
'用户自定义代码4';

comment on column GAPSUSR.ICPS_WBC_TM_CUSTOMER.USER_CODE5 is
'用户自定义代码5';

comment on column GAPSUSR.ICPS_WBC_TM_CUSTOMER.USER_CODE6 is
'用户自定义代码6';

comment on column GAPSUSR.ICPS_WBC_TM_CUSTOMER.USER_DATE1 is
'用户自定义日期1';

comment on column GAPSUSR.ICPS_WBC_TM_CUSTOMER.USER_DATE2 is
'用户自定义日期2';

comment on column GAPSUSR.ICPS_WBC_TM_CUSTOMER.USER_DATE3 is
'用户自定义日期3';

comment on column GAPSUSR.ICPS_WBC_TM_CUSTOMER.USER_DATE4 is
'用户自定义日期4';

comment on column GAPSUSR.ICPS_WBC_TM_CUSTOMER.USER_DATE5 is
'用户自定义日期5';

comment on column GAPSUSR.ICPS_WBC_TM_CUSTOMER.USER_DATE6 is
'用户自定义日期6';

comment on column GAPSUSR.ICPS_WBC_TM_CUSTOMER.USER_NUMBER1 is
'用户自定义笔数1';

comment on column GAPSUSR.ICPS_WBC_TM_CUSTOMER.USER_NUMBER2 is
'用户自定义笔数2';

comment on column GAPSUSR.ICPS_WBC_TM_CUSTOMER.USER_NUMBER3 is
'用户自定义笔数3';

comment on column GAPSUSR.ICPS_WBC_TM_CUSTOMER.USER_NUMBER4 is
'用户自定义笔数4';

comment on column GAPSUSR.ICPS_WBC_TM_CUSTOMER.USER_NUMBER5 is
'用户自定义笔数5';

comment on column GAPSUSR.ICPS_WBC_TM_CUSTOMER.USER_NUMBER6 is
'用户自定义笔数6';

comment on column GAPSUSR.ICPS_WBC_TM_CUSTOMER.USER_FIELD1 is
'用户自定义域1';

comment on column GAPSUSR.ICPS_WBC_TM_CUSTOMER.USER_FIELD2 is
'用户自定义域2';

comment on column GAPSUSR.ICPS_WBC_TM_CUSTOMER.USER_FIELD3 is
'用户自定义域3';

comment on column GAPSUSR.ICPS_WBC_TM_CUSTOMER.USER_FIELD4 is
'用户自定义域4';

comment on column GAPSUSR.ICPS_WBC_TM_CUSTOMER.USER_FIELD5 is
'用户自定义域5';

comment on column GAPSUSR.ICPS_WBC_TM_CUSTOMER.USER_FIELD6 is
'用户自定义域6';

comment on column GAPSUSR.ICPS_WBC_TM_CUSTOMER.USER_AMT1 is
'用户自定义金额1';

comment on column GAPSUSR.ICPS_WBC_TM_CUSTOMER.USER_AMT2 is
'用户自定义金额2';

comment on column GAPSUSR.ICPS_WBC_TM_CUSTOMER.USER_AMT3 is
'用户自定义金额3';

comment on column GAPSUSR.ICPS_WBC_TM_CUSTOMER.USER_AMT4 is
'用户自定义金额4';

comment on column GAPSUSR.ICPS_WBC_TM_CUSTOMER.USER_AMT5 is
'用户自定义金额5';

comment on column GAPSUSR.ICPS_WBC_TM_CUSTOMER.USER_AMT6 is
'昨日贷记卡承诺余额';

comment on column GAPSUSR.ICPS_WBC_TM_CUSTOMER.BANK_CUSTOMER_ID is
'行内统一用户号';

comment on column GAPSUSR.ICPS_WBC_TM_CUSTOMER.EMB_NAME is
'凸印姓名';

comment on column GAPSUSR.ICPS_WBC_TM_CUSTOMER.JPA_VERSION is
'乐观锁版本号';

comment on column GAPSUSR.ICPS_WBC_TM_CUSTOMER.CUST_LIMIT_ID is
'客户额度ID';

comment on column GAPSUSR.ICPS_WBC_TM_CUSTOMER.LAST_MODIFIED_DATETIME is
'修改时间';

comment on column GAPSUSR.ICPS_WBC_TM_CUSTOMER.CUST_LEVEL is
'客户等级';

comment on column GAPSUSR.ICPS_WBC_TM_CUSTOMER.PLEDEG_TYPE is
'押品类型';

comment on column GAPSUSR.ICPS_WBC_TM_CUSTOMER.SURNAME is
'姓氏';

comment on column GAPSUSR.ICPS_WBC_TM_CUSTOMER.CREATED_DATETIME is
'创建时间';

comment on column GAPSUSR.ICPS_WBC_TM_CUSTOMER.CUSTOMER_TYPE is
'客群分类';

comment on column GAPSUSR.ICPS_WBC_TM_CUSTOMER.BLOCK_CODE is
'锁定码';

comment on column GAPSUSR.ICPS_WBC_TM_CUSTOMER.IS_CHECK_FLAG is
'参与对账标识';

comment on column GAPSUSR.ICPS_WBC_TM_CUSTOMER.EXTEND_PARAM1 is
'扩展1';

comment on column GAPSUSR.ICPS_WBC_TM_CUSTOMER.EXTEND_PARAM2 is
'扩展2';

comment on column GAPSUSR.ICPS_WBC_TM_CUSTOMER.EXTEND_PARAM3 is
'扩展3';

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
'自定义额度信息表-授权';

comment on column GAPSUSR.ICPS_WBC_TM_CUST_LIMIT_O.BUSI_DATE is
'业务日期';

comment on column GAPSUSR.ICPS_WBC_TM_CUST_LIMIT_O.FILE_ORDER is
'文件序号';

comment on column GAPSUSR.ICPS_WBC_TM_CUST_LIMIT_O.ORG is
'机构号';

comment on column GAPSUSR.ICPS_WBC_TM_CUST_LIMIT_O.CUST_LIMIT_ID is
'客户额度ID';

comment on column GAPSUSR.ICPS_WBC_TM_CUST_LIMIT_O.LIMIT_CATEGORY is
'额度种类';

comment on column GAPSUSR.ICPS_WBC_TM_CUST_LIMIT_O.LIMIT_TYPE is
'额度类型';

comment on column GAPSUSR.ICPS_WBC_TM_CUST_LIMIT_O.CREDIT_LIMIT is
'信用额度';

comment on column GAPSUSR.ICPS_WBC_TM_CUST_LIMIT_O.JPA_VERSION is
'乐观锁版本号';

comment on column GAPSUSR.ICPS_WBC_TM_CUST_LIMIT_O.LAST_MODIFIED_DATETIME is
'修改时间';

comment on column GAPSUSR.ICPS_WBC_TM_CUST_LIMIT_O.CREATED_DATETIME is
'创建时间';

comment on column GAPSUSR.ICPS_WBC_TM_CUST_LIMIT_O.IS_CHECK_FLAG is
'参与对账标识';

comment on column GAPSUSR.ICPS_WBC_TM_CUST_LIMIT_O.EXTEND_PARAM1 is
'扩展1';

comment on column GAPSUSR.ICPS_WBC_TM_CUST_LIMIT_O.EXTEND_PARAM2 is
'扩展2';

comment on column GAPSUSR.ICPS_WBC_TM_CUST_LIMIT_O.EXTEND_PARAM3 is
'扩展3';

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
'总账会计科目表';

comment on column GAPSUSR.ICPS_WBC_TM_GL_BAL.BUSI_DATE is
'业务日期';

comment on column GAPSUSR.ICPS_WBC_TM_GL_BAL.FILE_ORDER is
'文件序号';

comment on column GAPSUSR.ICPS_WBC_TM_GL_BAL.ORG is
'机构号';

comment on column GAPSUSR.ICPS_WBC_TM_GL_BAL.SUBJECT is
'科目';

comment on column GAPSUSR.ICPS_WBC_TM_GL_BAL.BRANCH_ID is
'分支行号';

comment on column GAPSUSR.ICPS_WBC_TM_GL_BAL.DB_BAL is
'借方余额';

comment on column GAPSUSR.ICPS_WBC_TM_GL_BAL.CR_BAL is
'贷方余额';

comment on column GAPSUSR.ICPS_WBC_TM_GL_BAL.DB_AMT is
'借方发生额';

comment on column GAPSUSR.ICPS_WBC_TM_GL_BAL.DB_COUNT is
'借方笔数';

comment on column GAPSUSR.ICPS_WBC_TM_GL_BAL.CR_AMT is
'贷方发生额';

comment on column GAPSUSR.ICPS_WBC_TM_GL_BAL.CR_COUNT is
'贷方笔数';

comment on column GAPSUSR.ICPS_WBC_TM_GL_BAL.LAST_DB_BAL is
'昨日借方余额';

comment on column GAPSUSR.ICPS_WBC_TM_GL_BAL.LAST_CR_BAL is
'昨日贷方余额';

comment on column GAPSUSR.ICPS_WBC_TM_GL_BAL.LAST_MTH_DB_BAL is
'上月末借方余额';

comment on column GAPSUSR.ICPS_WBC_TM_GL_BAL.LAST_MTH_CR_BAL is
'上月末贷方余额';

comment on column GAPSUSR.ICPS_WBC_TM_GL_BAL.LAST_QTR_DB_BAL is
'上季末借方余额';

comment on column GAPSUSR.ICPS_WBC_TM_GL_BAL.LAST_QTR_CR_BAL is
'上季末贷方余额';

comment on column GAPSUSR.ICPS_WBC_TM_GL_BAL.LAST_YR_DB_BAL is
'上年末借方余额';

comment on column GAPSUSR.ICPS_WBC_TM_GL_BAL.LAST_YR_CR_BAL is
'上年末贷方余额';

comment on column GAPSUSR.ICPS_WBC_TM_GL_BAL.JPA_VERSION is
'乐观锁版本号';

comment on column GAPSUSR.ICPS_WBC_TM_GL_BAL.PRODUCT_CD is
'产品编号';

comment on column GAPSUSR.ICPS_WBC_TM_GL_BAL.BAL_ID is
'顺序号';

comment on column GAPSUSR.ICPS_WBC_TM_GL_BAL.BANK_NO is
'银行代码';

comment on column GAPSUSR.ICPS_WBC_TM_GL_BAL.BANK_GROUP_ID is
'银团代码';

comment on column GAPSUSR.ICPS_WBC_TM_GL_BAL.IS_CHECK_FLAG is
'参与对账标识';

comment on column GAPSUSR.ICPS_WBC_TM_GL_BAL.EXTEND_PARAM1 is
'扩展1';

comment on column GAPSUSR.ICPS_WBC_TM_GL_BAL.EXTEND_PARAM2 is
'扩展2';

comment on column GAPSUSR.ICPS_WBC_TM_GL_BAL.EXTEND_PARAM3 is
'扩展3';

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
'分期信息表';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN.BUSI_DATE is
'业务日期';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN.FILE_ORDER is
'文件序号';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN.ORG is
'机构号';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN.LOAN_ID is
'分期计划ID';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN.ACCT_NO is
'账户编号';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN.ACCT_TYPE is
'账户类型';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN.REF_NBR is
'交易参考号';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN.LOGICAL_CARD_NO is
'逻辑卡号';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN.CARD_NO is
'卡号';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN.REGISTER_DATE is
'分期注册日期';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN.REQUEST_TIME is
'请求日期时间';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN.LOAN_TYPE is
'分期类型';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN.LOAN_STATUS is
'分期状态';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN.LAST_LOAN_STATUS is
'分期上次状态';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN.LOAN_INIT_TERM is
'分期总期数';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN.CURR_TERM is
'当前期数';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN.REMAIN_TERM is
'剩余期数';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN.LOAN_INIT_PRIN is
'分期总本金';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN.LOAN_FIXED_PMT_PRIN is
'分期每期应还本金';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN.LOAN_FIRST_TERM_PRIN is
'分期首期应还本金';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN.LOAN_FINAL_TERM_PRIN is
'分期末期应还本金';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN.LOAN_INIT_FEE1 is
'分期总手续费';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN.LOAN_FIXED_FEE1 is
'分期每期手续费';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN.LOAN_FIRST_TERM_FEE1 is
'分期首期手续费';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN.LOAN_FINAL_TERM_FEE1 is
'分期末期手续费';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN.UNEARNED_PRIN is
'未出账单的本金';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN.UNEARNED_FEE1 is
'未出账单手续费';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN.PAID_OUT_DATE is
'还清日期';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN.TERMINATE_DATE is
'提前终止日期';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN.TERMINATE_REASON_CD is
'分期终止原因代码';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN.PRIN_PAID is
'已偿还本金';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN.INT_PAID is
'已偿还利息';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN.FEE_PAID is
'已偿还费用';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN.LOAN_CURR_BAL is
'分期当前总余额';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN.LOAN_BAL_XFROUT is
'分期未到期余额';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN.LOAN_BAL_XFRIN is
'分期已出账单余额';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN.LOAN_BAL_PRINCIPAL is
'欠款总本金';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN.LOAN_BAL_INTEREST is
'欠款总利息';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN.LOAN_BAL_PENALTY is
'欠款总罚息';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN.LOAN_PRIN_XFROUT is
'分期未到期本金';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN.LOAN_PRIN_XFRIN is
'分期已出账单本金';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN.LOAN_FEE1_XFROUT is
'分期未到期手续费';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN.LOAN_FEE1_XFRIN is
'分期已出账单手续费';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN.ORIG_TXN_AMT is
'原始交易币种金额';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN.ORIG_TRANS_DATE is
'原始交易日期';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN.ORIG_AUTH_CODE is
'原始交易授权码';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN.JPA_VERSION is
'乐观锁版本号';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN.LOAN_CODE is
'分期计划代码';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN.REGISTER_ID is
'分期申请顺序号';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN.RESCH_INIT_PRIN is
'展期本金金额';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN.RESCH_DATE is
'展期生效日期';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN.BEF_RESCH_FIXED_PMT_PRIN is
'展期前每期应还本金';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN.BEF_RESCH_INIT_TERM is
'展期前总期数';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN.BEF_RESCH_FIRST_TERM_PRIN is
'展期前分期首期应还本金';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN.BEF_RESCH_FINAL_TERM_PRIN is
'展期前分期末期应还本金';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN.BEF_RESCH_INIT_FEE1 is
'展期前分期总手续费';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN.BEF_RESCH_FIXED_FEE1 is
'分期每期手续费';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN.BEF_RESCH_FIRST_TERM_FEE1 is
'展期前分期首期手续费';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN.BEF_RESCH_FINAL_TERM_FEE1 is
'展期前分期末期手续费';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN.RESCH_FIRST_TERM_FEE1 is
'展期后首期手续费';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN.LOAN_FEE_METHOD is
'分期手续费收取方式';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN.INTEREST_RATE is
'基础利率';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN.PENALTY_RATE is
'罚息利率';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN.COMPOUND_RATE is
'复利利率';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN.FLOAT_RATE is
'浮动比例';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN.LOAN_RECEIPT_NBR is
'借据号';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN.LOAN_EXPIRE_DATE is
'贷款到期日期';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN.LOAN_CD is
'贷款逾期最大期数';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN.PAYMENT_HIST is
'24个月还款状态';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN.CTD_PAYMENT_AMT is
'当期还款额';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN.PAST_RESCH_CNT is
'已展期次数';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN.PAST_SHORTED_CNT is
'已缩期次数';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN.ADV_PMT_AMT is
'提前还款金额';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN.LAST_ACTION_DATE is
'上次行动日期';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN.LAST_ACTION_TYPE is
'上次行动类型';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN.LAST_MODIFIED_DATETIME is
'修改时间';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN.ACTIVATE_DATE is
'激活日期';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN.INTEREST_CALC_BASE is
'计息基数';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN.FIRST_BILL_DATE is
'首个账单日';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN.AGE_CD is
'账龄';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN.RECALC_IND is
'利率重算标志';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN.RECALC_DATE is
'利率重算日';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN.GRACE_DATE is
'宽限日期';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN.CANCEL_DATE is
'撤销日期';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN.CANCEL_REASON is
'贷款撤销原因';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN.BANK_GROUP_ID is
'银团编号';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN.DUE_DAYS is
'当前逾期天数';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN.CONTRACT_VER is
'合同版本号';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN.LOAN_INIT_INTEREST is
'贷款总利息';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN.BEF_INIT_INTEREST is
'原贷款总利息';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN.PENALTY_PAID is
'已还罚息';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN.COMPOUND_PAID is
'已还复利';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN.LATE_CHARGE_PAID is
'已还滞纳金';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN.LOAN_BAL_LATE_CHARGE is
'欠款总滞纳金';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN.NEXT_XFR_DATE is
'下一结转日';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN.NEXT_LATE_CHARGE_DATE is
'下一滞纳金收取日';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN.FEE_RATE is
'费率';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN.LATE_CHARGE_FEE_RATE is
'滞纳金费率';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN.ADV_PMT_FEE_RATE is
'提前还款手续费费率';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN.LOAN_BAL_ADV_PMT_FEE is
'提前还款手续费总欠款';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN.ADV_PMT_FEE_PAID is
'已还提前还款手续费';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN.LAST_XFR_DATE is
'上一结转日期';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN.LOAN_BAL_FEE is
'欠款总费用';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN.PAYEE_CARD_NO is
'收款卡号';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN.PAYEE_BANK_NAME is
'收款行名称';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN.BILLING_CYCLE is
'账单日';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN.LAST_STMT_DATE is
'上个账单日期';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN.NEXT_STMT_DATE is
'下个账单日期';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN.IS_CHECK_FLAG is
'参与对账标识';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN.EXTEND_PARAM1 is
'扩展1';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN.EXTEND_PARAM2 is
'扩展2';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN.EXTEND_PARAM3 is
'扩展3';

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
'还款借据清单表';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN_RECEIPT_LIST.BUSI_DATE is
'业务日期';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN_RECEIPT_LIST.FILE_ORDER is
'文件序号';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN_RECEIPT_LIST.CONSUMER_TRANS_ID is
'业务流水号';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN_RECEIPT_LIST.SYS_TRANS_ID is
'系统调用流水号';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN_RECEIPT_LIST.LOAN_RECEIPT_NBR is
'借据号';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN_RECEIPT_LIST.ACCT_NO is
'账户编号';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN_RECEIPT_LIST.ACCT_TYPE is
'账户类型';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN_RECEIPT_LIST.CARD_NO is
'卡号';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN_RECEIPT_LIST.POST_DATE is
'入账日期';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN_RECEIPT_LIST.LAST_MODIFIED_DATETIME is
'时间戳';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN_RECEIPT_LIST.PAY_AMT is
'还款金额';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN_RECEIPT_LIST.BANK_GROUP_ID is
'银团编号';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN_RECEIPT_LIST.IS_CHECK_FLAG is
'参与对账标识';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN_RECEIPT_LIST.EXTEND_PARAM1 is
'扩展1';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN_RECEIPT_LIST.EXTEND_PARAM2 is
'扩展2';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN_RECEIPT_LIST.EXTEND_PARAM3 is
'扩展3';

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
'借据纳税加工表';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN_VMS.BUSI_DATE is
'业务日期';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN_VMS.FILE_ORDER is
'文件序号';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN_VMS.ID is
'纳税借据ID';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN_VMS.ORG is
'机构号';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN_VMS.CARD_NO is
'介质卡号';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN_VMS.REF_NBR is
'交易参考号';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN_VMS.BANK_GROUP_ID is
'银团编号';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN_VMS.BANK_NO is
'银行编号';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN_VMS.PRODUCT_CD is
'产品号';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN_VMS.BIZ_TAX_INTEREST is
'营业税下的应计和应收息';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN_VMS.VAT_INT_BAL is
'90天内的应纳税息余额';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN_VMS.NOREVOKE_VAT_INT_BAL is
'不冲抵算法下应纳税息（含90天内+90天外还款补记部分）';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN_VMS.VAT_TAX is
'记账增值税';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN_VMS.LOAN_INIT_TERM is
'贷款总期数';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN_VMS.LAST_MODIFIED_TIME is
'上次修改时间';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN_VMS.PAID_OUT_DATE is
'结清日期';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN_VMS.AGE_CD is
'账龄';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN_VMS.BATCH_DATE is
'批量日期';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN_VMS.JPA_VERSION is
'乐观锁版本号';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN_VMS.IS_CHECK_FLAG is
'参与对账标识';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN_VMS.EXTEND_PARAM1 is
'扩展1';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN_VMS.EXTEND_PARAM2 is
'扩展2';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN_VMS.EXTEND_PARAM3 is
'扩展3';

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
'订单号与借据号映射';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN_YX.BUSI_DATE is
'业务日期';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN_YX.FILE_ORDER is
'文件序号';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN_YX.LOAN_RECEIPT_NBR is
'借据号';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN_YX.MERCHANT_ID is
'平台ID';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN_YX.PRODUCT_CD is
'产品CD';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN_YX.AGREEMENT_NO is
'平台协议号';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN_YX.CNC_CARD_NO is
'贷款卡号';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN_YX.LOAN_INIT_TERM is
'总期数';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN_YX.CURR_TERM is
'当期期数';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN_YX.REMAIN_TERM is
'剩余期数';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN_YX.INTEREST_RATE is
'利息利率';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN_YX.LOAN_STATUS is
'状态';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN_YX.LOAN_PRIN is
'总本金';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN_YX.LOAN_PAID is
'已还本金';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN_YX.LOAN_INIT_INTEREST is
'总利息';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN_YX.INT_PAID is
'已还利息';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN_YX.LOAN_EXPIRE_DATE is
'到期日期';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN_YX.GRACE_DATE is
'宽限日';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN_YX.DUE_DAYS is
'逾期天数';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN_YX.LOAN_PAIDOUT_FLG is
'结清标识';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN_YX.LOAN_PAIDOUT_DATE is
'结清日期';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN_YX.TERMINATE_REASON_CD is
'终止原因代码';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN_YX.BATCH_DATE is
'批量同步日期';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN_YX.BATCH_NO is
'批次号';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN_YX.LOAN_BAL_LATE_CHARGE is
'欠款总滞纳金';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN_YX.LOAN_BAL_ADV_PMT_FEE is
'欠款总提前还款手续费';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN_YX.LOAN_BAL_FEE is
'欠款总费用';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN_YX.LATE_CHARGE_PAID is
'已还滞纳金';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN_YX.ADV_PMT_FEE_PAID is
'已还提前还款手续费';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN_YX.FEE_PAID is
'已还费用';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN_YX.NEXT_PRIN is
'下期本金';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN_YX.NEXT_FEE is
'下期手续费';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN_YX.REGISTER_DATE is
'借据注册日期';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN_YX.PRIN_BAL is
'欠款总本金';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN_YX.INT_BAL is
'欠款总利息';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN_YX.PENALTY_BAL is
'欠款总罚息';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN_YX.PENALTY_PAID is
'已还罚息';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN_YX.PENALTY_RATE is
'罚息利率';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN_YX.BIZ_DATE is
'业务日期';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN_YX.CREATED_DATETIME is
'创建时间日期';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN_YX.LAST_MODIFIED_DATETIME is
'更新时间日期';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN_YX.LOAN_TYPE is
'借据类型';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN_YX.UNEARNED_PRIN is
'未到期本金';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN_YX.INST_RETURN_FLAG is
'是否已退息';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN_YX.PAID_OUT_RETURN_STATUS is
'结清退保退息状态';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN_YX.REF_NBR is
'交易检索号';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN_YX.LOAN_MERGE_TYPE is
'借据合并类型';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN_YX.BEF_INIT_INTEREST is
'原贷款总利息';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN_YX.ORIG_INIT_TERM is
'原始贷款期数';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN_YX.GL_TERM is
'总账期数，会计账期数。需要乘以还款间隔以加工';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN_YX.IS_CHECK_FLAG is
'参与对账标识';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN_YX.EXTEND_PARAM1 is
'扩展1';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN_YX.EXTEND_PARAM2 is
'扩展2';

comment on column GAPSUSR.ICPS_WBC_TM_LOAN_YX.EXTEND_PARAM3 is
'扩展3';

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
'平台客户信息表';

comment on column GAPSUSR.ICPS_WBC_TM_MERCHANT_CUST.BUSI_DATE is
'业务日期';

comment on column GAPSUSR.ICPS_WBC_TM_MERCHANT_CUST.FILE_ORDER is
'文件序号';

comment on column GAPSUSR.ICPS_WBC_TM_MERCHANT_CUST.USER_ID is
'平台的客户ID';

comment on column GAPSUSR.ICPS_WBC_TM_MERCHANT_CUST.MERCHANT_ID is
'平台ID';

comment on column GAPSUSR.ICPS_WBC_TM_MERCHANT_CUST.NBS_CUST_ID is
'NBS客户ID';

comment on column GAPSUSR.ICPS_WBC_TM_MERCHANT_CUST.USER_NAME is
'平台注册的客户名称';

comment on column GAPSUSR.ICPS_WBC_TM_MERCHANT_CUST.USER_MOBILE is
'平台登记的用户手机号';

comment on column GAPSUSR.ICPS_WBC_TM_MERCHANT_CUST.APPLY_DATETIME is
'平台ID申请时间';

comment on column GAPSUSR.ICPS_WBC_TM_MERCHANT_CUST.REG_MOBILE is
'注册手机号';

comment on column GAPSUSR.ICPS_WBC_TM_MERCHANT_CUST.QQ_OPENID is
'QQ_OPENID';

comment on column GAPSUSR.ICPS_WBC_TM_MERCHANT_CUST.WX_OPENID is
'WX_OPENID';

comment on column GAPSUSR.ICPS_WBC_TM_MERCHANT_CUST.LOGIN_ID is
'微众WEB登录ID';

comment on column GAPSUSR.ICPS_WBC_TM_MERCHANT_CUST.COMPANY_NAME is
'单位名称';

comment on column GAPSUSR.ICPS_WBC_TM_MERCHANT_CUST.COMPANY_PHONE is
'单位电话';

comment on column GAPSUSR.ICPS_WBC_TM_MERCHANT_CUST.ADDRESS is
'居住地址';

comment on column GAPSUSR.ICPS_WBC_TM_MERCHANT_CUST.CONTACT_NAME is
'联系人名称';

comment on column GAPSUSR.ICPS_WBC_TM_MERCHANT_CUST.CONTACT_PHONE is
'联系人手机号';

comment on column GAPSUSR.ICPS_WBC_TM_MERCHANT_CUST.CONTACT_RELATION is
'联系人关系';

comment on column GAPSUSR.ICPS_WBC_TM_MERCHANT_CUST.RESERVE1 is
'保留字段1';

comment on column GAPSUSR.ICPS_WBC_TM_MERCHANT_CUST.RESERVE2 is
'保留字段2';

comment on column GAPSUSR.ICPS_WBC_TM_MERCHANT_CUST.RESERVE3 is
'保留字段3';

comment on column GAPSUSR.ICPS_WBC_TM_MERCHANT_CUST.BIZ_DATE is
'业务日期';

comment on column GAPSUSR.ICPS_WBC_TM_MERCHANT_CUST.CREATED_DATETIME is
'创建时间日期';

comment on column GAPSUSR.ICPS_WBC_TM_MERCHANT_CUST.LAST_MODIFIED_DATETIME is
'更新时间日期';

comment on column GAPSUSR.ICPS_WBC_TM_MERCHANT_CUST.CONTACT_ADDR is
'联系人地址';

comment on column GAPSUSR.ICPS_WBC_TM_MERCHANT_CUST.CONTACT_ID_NO is
'联系人身份证号';

comment on column GAPSUSR.ICPS_WBC_TM_MERCHANT_CUST.CO_LICENSES is
'营业执照号';

comment on column GAPSUSR.ICPS_WBC_TM_MERCHANT_CUST.DRIVER_LICENSE is
'驾驶证号码';

comment on column GAPSUSR.ICPS_WBC_TM_MERCHANT_CUST.COMPANY_ADDR is
'公司地址';

comment on column GAPSUSR.ICPS_WBC_TM_MERCHANT_CUST.HOME_PHONE is
'家庭固话号码';

comment on column GAPSUSR.ICPS_WBC_TM_MERCHANT_CUST.OCCUPATION is
'职业';

comment on column GAPSUSR.ICPS_WBC_TM_MERCHANT_CUST.SS_AVE_AMT_MTLY is
'每月社保平均缴交金额';

comment on column GAPSUSR.ICPS_WBC_TM_MERCHANT_CUST.SALARY_AVE_MTLY is
'每月平均工资进账流水';

comment on column GAPSUSR.ICPS_WBC_TM_MERCHANT_CUST.IS_HOME_VISITED is
'有无家访';

comment on column GAPSUSR.ICPS_WBC_TM_MERCHANT_CUST.HOUSE_INFO is
'房产信息';

comment on column GAPSUSR.ICPS_WBC_TM_MERCHANT_CUST.MER_APPLY_RESULT is
'审批结果';

comment on column GAPSUSR.ICPS_WBC_TM_MERCHANT_CUST.MER_APPLY_VIEW is
'审批意见';

comment on column GAPSUSR.ICPS_WBC_TM_MERCHANT_CUST.MER_REFUSE_REASON is
'拒绝原因分类';

comment on column GAPSUSR.ICPS_WBC_TM_MERCHANT_CUST.CUST_VALUE is
'客户信息（大字段）';

comment on column GAPSUSR.ICPS_WBC_TM_MERCHANT_CUST.IS_GUARANTOR is
'有无担保人';

comment on column GAPSUSR.ICPS_WBC_TM_MERCHANT_CUST.IS_CHECK_FLAG is
'参与对账标识';

comment on column GAPSUSR.ICPS_WBC_TM_MERCHANT_CUST.EXTEND_PARAM1 is
'扩展1';

comment on column GAPSUSR.ICPS_WBC_TM_MERCHANT_CUST.EXTEND_PARAM2 is
'扩展2';

comment on column GAPSUSR.ICPS_WBC_TM_MERCHANT_CUST.EXTEND_PARAM3 is
'扩展3';

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
'客户产品信息表';

comment on column GAPSUSR.ICPS_WBC_TM_MERCHANT_PRODUCT_CUST.BUSI_DATE is
'业务日期';

comment on column GAPSUSR.ICPS_WBC_TM_MERCHANT_PRODUCT_CUST.FILE_ORDER is
'文件序号';

comment on column GAPSUSR.ICPS_WBC_TM_MERCHANT_PRODUCT_CUST.USER_ID is
'平台的客户ID';

comment on column GAPSUSR.ICPS_WBC_TM_MERCHANT_PRODUCT_CUST.MERCHANT_ID is
'平台ID';

comment on column GAPSUSR.ICPS_WBC_TM_MERCHANT_PRODUCT_CUST.PRODUCT_CD is
'产品CD';

comment on column GAPSUSR.ICPS_WBC_TM_MERCHANT_PRODUCT_CUST.CNC_CARD_NO is
'贷款卡号';

comment on column GAPSUSR.ICPS_WBC_TM_MERCHANT_PRODUCT_CUST.DEBIT_CARD_NO is
'他行借记卡号';

comment on column GAPSUSR.ICPS_WBC_TM_MERCHANT_PRODUCT_CUST.WB_DEBIT_CARD_NO is
'本行借记卡号';

comment on column GAPSUSR.ICPS_WBC_TM_MERCHANT_PRODUCT_CUST.NBS_CUST_ID is
'NBS客户ID';

comment on column GAPSUSR.ICPS_WBC_TM_MERCHANT_PRODUCT_CUST.APS_APP_TIME is
'APS开户申请时间';

comment on column GAPSUSR.ICPS_WBC_TM_MERCHANT_PRODUCT_CUST.APS_APP_NO is
'APS开户申请号';

comment on column GAPSUSR.ICPS_WBC_TM_MERCHANT_PRODUCT_CUST.APS_APP_NO_STATUS is
'APS申请号状态';

comment on column GAPSUSR.ICPS_WBC_TM_MERCHANT_PRODUCT_CUST.APS_APP_COUNT is
'单日申请次数';

comment on column GAPSUSR.ICPS_WBC_TM_MERCHANT_PRODUCT_CUST.APS_APPROVAL_DATE is
'APS审批通过日期';

comment on column GAPSUSR.ICPS_WBC_TM_MERCHANT_PRODUCT_CUST.APS_RESULT_LEVEL is
'APS审批结果等级';

comment on column GAPSUSR.ICPS_WBC_TM_MERCHANT_PRODUCT_CUST.APS_REJ_CODE is
'APS审批拒绝码';

comment on column GAPSUSR.ICPS_WBC_TM_MERCHANT_PRODUCT_CUST.APS_REJ_DATE is
'APS审批拒绝时间';

comment on column GAPSUSR.ICPS_WBC_TM_MERCHANT_PRODUCT_CUST.CNC_SETUP_DATE is
'开贷款户日期';

comment on column GAPSUSR.ICPS_WBC_TM_MERCHANT_PRODUCT_CUST.APS_CREDIT_LIMIT is
'开户时授信额度';

comment on column GAPSUSR.ICPS_WBC_TM_MERCHANT_PRODUCT_CUST.GID is
'操作源GID';

comment on column GAPSUSR.ICPS_WBC_TM_MERCHANT_PRODUCT_CUST.OPER_IP is
'操作源IP';

comment on column GAPSUSR.ICPS_WBC_TM_MERCHANT_PRODUCT_CUST.OS_TYPE is
'操作系统';

comment on column GAPSUSR.ICPS_WBC_TM_MERCHANT_PRODUCT_CUST.LBS is
'LBS';

comment on column GAPSUSR.ICPS_WBC_TM_MERCHANT_PRODUCT_CUST.IOS_IDFA is
'IOS标示符';

comment on column GAPSUSR.ICPS_WBC_TM_MERCHANT_PRODUCT_CUST.ANDROID_IMEI is
'ANDROID蓝牙地址';

comment on column GAPSUSR.ICPS_WBC_TM_MERCHANT_PRODUCT_CUST.SUBMITTED_ENTRY is
'提交入口';

comment on column GAPSUSR.ICPS_WBC_TM_MERCHANT_PRODUCT_CUST.SUBMITTED_CITY is
'申请城市';

comment on column GAPSUSR.ICPS_WBC_TM_MERCHANT_PRODUCT_CUST.RESERVE1 is
'保留字段1';

comment on column GAPSUSR.ICPS_WBC_TM_MERCHANT_PRODUCT_CUST.RESERVE2 is
'保留字段2';

comment on column GAPSUSR.ICPS_WBC_TM_MERCHANT_PRODUCT_CUST.RESERVE3 is
'保留字段3';

comment on column GAPSUSR.ICPS_WBC_TM_MERCHANT_PRODUCT_CUST.BIZ_DATE is
'业务日期';

comment on column GAPSUSR.ICPS_WBC_TM_MERCHANT_PRODUCT_CUST.CREATED_DATETIME is
'创建时间日期';

comment on column GAPSUSR.ICPS_WBC_TM_MERCHANT_PRODUCT_CUST.LAST_MODIFIED_DATETIME is
'更新时间日期';

comment on column GAPSUSR.ICPS_WBC_TM_MERCHANT_PRODUCT_CUST.APP_BIZ_SEQ_NO is
'申请业务流水号';

comment on column GAPSUSR.ICPS_WBC_TM_MERCHANT_PRODUCT_CUST.APS_REJ_REASON is
'申请拒绝原因';

comment on column GAPSUSR.ICPS_WBC_TM_MERCHANT_PRODUCT_CUST.APP_EXPIRY_DATE is
'申请失效日期';

comment on column GAPSUSR.ICPS_WBC_TM_MERCHANT_PRODUCT_CUST.AGENT_ID is
'代理人身份id';

comment on column GAPSUSR.ICPS_WBC_TM_MERCHANT_PRODUCT_CUST.AGENT_NAME is
'代理人姓名';

comment on column GAPSUSR.ICPS_WBC_TM_MERCHANT_PRODUCT_CUST.IS_CHECK_FLAG is
'参与对账标识';

comment on column GAPSUSR.ICPS_WBC_TM_MERCHANT_PRODUCT_CUST.EXTEND_PARAM1 is
'扩展1';

comment on column GAPSUSR.ICPS_WBC_TM_MERCHANT_PRODUCT_CUST.EXTEND_PARAM2 is
'扩展2';

comment on column GAPSUSR.ICPS_WBC_TM_MERCHANT_PRODUCT_CUST.EXTEND_PARAM3 is
'扩展3';

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
'nbs客户表';

comment on column GAPSUSR.ICPS_WBC_TM_NBS_CUST.BUSI_DATE is
'业务日期';

comment on column GAPSUSR.ICPS_WBC_TM_NBS_CUST.FILE_ORDER is
'文件序号';

comment on column GAPSUSR.ICPS_WBC_TM_NBS_CUST.NBS_CUST_ID is
'NBS客户ID';

comment on column GAPSUSR.ICPS_WBC_TM_NBS_CUST."NAME" is
'姓名';

comment on column GAPSUSR.ICPS_WBC_TM_NBS_CUST.ID_TYPE is
'证件类型';

comment on column GAPSUSR.ICPS_WBC_TM_NBS_CUST.ID_NO is
'证件号码';

comment on column GAPSUSR.ICPS_WBC_TM_NBS_CUST.ECIF_NO is
'ecif客户号';

comment on column GAPSUSR.ICPS_WBC_TM_NBS_CUST.RESERVE1 is
'保留字段1';

comment on column GAPSUSR.ICPS_WBC_TM_NBS_CUST.RESERVE2 is
'身份证有效期';

comment on column GAPSUSR.ICPS_WBC_TM_NBS_CUST.RESERVE3 is
'保留字段3';

comment on column GAPSUSR.ICPS_WBC_TM_NBS_CUST.BIZ_DATE is
'业务日期';

comment on column GAPSUSR.ICPS_WBC_TM_NBS_CUST.CREATED_DATETIME is
'创建时间日期';

comment on column GAPSUSR.ICPS_WBC_TM_NBS_CUST.LAST_MODIFIED_DATETIME is
'更新时间日期';

comment on column GAPSUSR.ICPS_WBC_TM_NBS_CUST.IS_CHECK_FLAG is
'参与对账标识';

comment on column GAPSUSR.ICPS_WBC_TM_NBS_CUST.EXTEND_PARAM1 is
'扩展1';

comment on column GAPSUSR.ICPS_WBC_TM_NBS_CUST.EXTEND_PARAM2 is
'扩展2';

comment on column GAPSUSR.ICPS_WBC_TM_NBS_CUST.EXTEND_PARAM3 is
'扩展3';

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
'nbs客户延展表';

comment on column GAPSUSR.ICPS_WBC_TM_NBS_CUST_EXT_INFO.BUSI_DATE is
'业务日期';

comment on column GAPSUSR.ICPS_WBC_TM_NBS_CUST_EXT_INFO.FILE_ORDER is
'文件序号';

comment on column GAPSUSR.ICPS_WBC_TM_NBS_CUST_EXT_INFO.NBS_CUST_ID is
'NBS客户ID';

comment on column GAPSUSR.ICPS_WBC_TM_NBS_CUST_EXT_INFO.PRODUCT_CD is
'产品号';

comment on column GAPSUSR.ICPS_WBC_TM_NBS_CUST_EXT_INFO.MERCHANT_ID is
'平台ID';

comment on column GAPSUSR.ICPS_WBC_TM_NBS_CUST_EXT_INFO."NAME" is
'姓名';

comment on column GAPSUSR.ICPS_WBC_TM_NBS_CUST_EXT_INFO.ID_TYPE is
'证件类型';

comment on column GAPSUSR.ICPS_WBC_TM_NBS_CUST_EXT_INFO.ID_NO is
'证件号码';

comment on column GAPSUSR.ICPS_WBC_TM_NBS_CUST_EXT_INFO.ID_NO_EXPIRY is
'身份证有效期';

comment on column GAPSUSR.ICPS_WBC_TM_NBS_CUST_EXT_INFO.RESIDENTIAL_ADDRESS is
'地址';

comment on column GAPSUSR.ICPS_WBC_TM_NBS_CUST_EXT_INFO.GENDER is
'性别';

comment on column GAPSUSR.ICPS_WBC_TM_NBS_CUST_EXT_INFO.NATIONALITY is
'国籍';

comment on column GAPSUSR.ICPS_WBC_TM_NBS_CUST_EXT_INFO.MARRIAGE is
'婚姻状况';

comment on column GAPSUSR.ICPS_WBC_TM_NBS_CUST_EXT_INFO.EDUCATION is
'学历';

comment on column GAPSUSR.ICPS_WBC_TM_NBS_CUST_EXT_INFO.CUST_EXT_INF1 is
'民族';

comment on column GAPSUSR.ICPS_WBC_TM_NBS_CUST_EXT_INFO.CUST_EXT_INF2 is
'保留字段';

comment on column GAPSUSR.ICPS_WBC_TM_NBS_CUST_EXT_INFO.CUST_EXT_INF3 is
'保留字段';

comment on column GAPSUSR.ICPS_WBC_TM_NBS_CUST_EXT_INFO.CUST_EXT_INF4 is
'保留字段';

comment on column GAPSUSR.ICPS_WBC_TM_NBS_CUST_EXT_INFO.CUST_EXT_INF5 is
'保留字段';

comment on column GAPSUSR.ICPS_WBC_TM_NBS_CUST_EXT_INFO.CUST_EXT_INF6 is
'保留字段';

comment on column GAPSUSR.ICPS_WBC_TM_NBS_CUST_EXT_INFO.CUST_EXT_INF7 is
'保留字段';

comment on column GAPSUSR.ICPS_WBC_TM_NBS_CUST_EXT_INFO.CUST_EXT_INF8 is
'保留字段';

comment on column GAPSUSR.ICPS_WBC_TM_NBS_CUST_EXT_INFO.CUST_EXT_INF9 is
'保留字段';

comment on column GAPSUSR.ICPS_WBC_TM_NBS_CUST_EXT_INFO.CUST_EXT_INF10 is
'保留字段';

comment on column GAPSUSR.ICPS_WBC_TM_NBS_CUST_EXT_INFO.CUST_EXT_INF11 is
'保留字段';

comment on column GAPSUSR.ICPS_WBC_TM_NBS_CUST_EXT_INFO.CUST_EXT_INF12 is
'保留字段';

comment on column GAPSUSR.ICPS_WBC_TM_NBS_CUST_EXT_INFO.CUST_EXT_INF13 is
'保留字段';

comment on column GAPSUSR.ICPS_WBC_TM_NBS_CUST_EXT_INFO.CUST_EXT_INF14 is
'保留字段';

comment on column GAPSUSR.ICPS_WBC_TM_NBS_CUST_EXT_INFO.CUST_EXT_INF15 is
'保留字段';

comment on column GAPSUSR.ICPS_WBC_TM_NBS_CUST_EXT_INFO.CUST_EXT_INF16 is
'保留字段';

comment on column GAPSUSR.ICPS_WBC_TM_NBS_CUST_EXT_INFO.CUST_EXT_INF17 is
'保留字段';

comment on column GAPSUSR.ICPS_WBC_TM_NBS_CUST_EXT_INFO.CUST_EXT_INF18 is
'保留字段';

comment on column GAPSUSR.ICPS_WBC_TM_NBS_CUST_EXT_INFO.CUST_EXT_INF19 is
'保留字段';

comment on column GAPSUSR.ICPS_WBC_TM_NBS_CUST_EXT_INFO.CUST_EXT_INF20 is
'保留字段';

comment on column GAPSUSR.ICPS_WBC_TM_NBS_CUST_EXT_INFO.CREATED_DATETIME is
'创建时间日期';

comment on column GAPSUSR.ICPS_WBC_TM_NBS_CUST_EXT_INFO.LAST_MODIFIED_DATETIME is
'更新时间日期';

comment on column GAPSUSR.ICPS_WBC_TM_NBS_CUST_EXT_INFO.IS_CHECK_FLAG is
'参与对账标识';

comment on column GAPSUSR.ICPS_WBC_TM_NBS_CUST_EXT_INFO.EXTEND_PARAM1 is
'扩展1';

comment on column GAPSUSR.ICPS_WBC_TM_NBS_CUST_EXT_INFO.EXTEND_PARAM2 is
'扩展2';

comment on column GAPSUSR.ICPS_WBC_TM_NBS_CUST_EXT_INFO.EXTEND_PARAM3 is
'扩展3';

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
'信用计划表';

comment on column GAPSUSR.ICPS_WBC_TM_PLAN.BUSI_DATE is
'业务日期';

comment on column GAPSUSR.ICPS_WBC_TM_PLAN.FILE_ORDER is
'文件序号';

comment on column GAPSUSR.ICPS_WBC_TM_PLAN.ORG is
'机构号';

comment on column GAPSUSR.ICPS_WBC_TM_PLAN.PLAN_ID is
'信用计划ID';

comment on column GAPSUSR.ICPS_WBC_TM_PLAN.ACCT_NO is
'账户编号';

comment on column GAPSUSR.ICPS_WBC_TM_PLAN.ACCT_TYPE is
'账户类型';

comment on column GAPSUSR.ICPS_WBC_TM_PLAN.LOGICAL_CARD_NO is
'逻辑卡号';

comment on column GAPSUSR.ICPS_WBC_TM_PLAN.PLAN_NBR is
'信用计划号';

comment on column GAPSUSR.ICPS_WBC_TM_PLAN.PLAN_TYPE is
'信用计划类型';

comment on column GAPSUSR.ICPS_WBC_TM_PLAN.PRODUCT_CD is
'产品代码';

comment on column GAPSUSR.ICPS_WBC_TM_PLAN.REF_NBR is
'交易参考号';

comment on column GAPSUSR.ICPS_WBC_TM_PLAN.CURR_BAL is
'当前余额';

comment on column GAPSUSR.ICPS_WBC_TM_PLAN.BEGIN_BAL is
'期初余额';

comment on column GAPSUSR.ICPS_WBC_TM_PLAN.DISPUTE_AMT is
'争议金额';

comment on column GAPSUSR.ICPS_WBC_TM_PLAN.TOT_DUE_AMT is
'最小还款额';

comment on column GAPSUSR.ICPS_WBC_TM_PLAN.PLAN_ADD_DATE is
'信用计划建立日期';

comment on column GAPSUSR.ICPS_WBC_TM_PLAN.PAID_OUT_DATE is
'还清日期';

comment on column GAPSUSR.ICPS_WBC_TM_PLAN.PAST_PRINCIPAL is
'已出账单本金';

comment on column GAPSUSR.ICPS_WBC_TM_PLAN.PAST_INTEREST is
'已出账单利息';

comment on column GAPSUSR.ICPS_WBC_TM_PLAN.PAST_CARD_FEE is
'已出账单年费';

comment on column GAPSUSR.ICPS_WBC_TM_PLAN.PAST_OVRLMT_FEE is
'已出账单超限费';

comment on column GAPSUSR.ICPS_WBC_TM_PLAN.PAST_LPC is
'已出账单滞纳金';

comment on column GAPSUSR.ICPS_WBC_TM_PLAN.PAST_NSF_FEE is
'已出账单资金不足费';

comment on column GAPSUSR.ICPS_WBC_TM_PLAN.PAST_TXN_FEE is
'已出账单交易费';

comment on column GAPSUSR.ICPS_WBC_TM_PLAN.PAST_SVC_FEE is
'已出账单服务费';

comment on column GAPSUSR.ICPS_WBC_TM_PLAN.PAST_INS is
'已出账单保险金额';

comment on column GAPSUSR.ICPS_WBC_TM_PLAN.PAST_USER_FEE1 is
'已出账单自定义费用1';

comment on column GAPSUSR.ICPS_WBC_TM_PLAN.PAST_USER_FEE2 is
'已出账单自定义费用2';

comment on column GAPSUSR.ICPS_WBC_TM_PLAN.PAST_USER_FEE3 is
'已出账单自定义费用3';

comment on column GAPSUSR.ICPS_WBC_TM_PLAN.PAST_USER_FEE4 is
'已出账单自定义费用4';

comment on column GAPSUSR.ICPS_WBC_TM_PLAN.PAST_USER_FEE5 is
'已出账单自定义费用5';

comment on column GAPSUSR.ICPS_WBC_TM_PLAN.PAST_USER_FEE6 is
'已出账单自定义费用6';

comment on column GAPSUSR.ICPS_WBC_TM_PLAN.CTD_PRINCIPAL is
'当期本金';

comment on column GAPSUSR.ICPS_WBC_TM_PLAN.CTD_INTEREST is
'当期利息';

comment on column GAPSUSR.ICPS_WBC_TM_PLAN.CTD_CARD_FEE is
'当期年费';

comment on column GAPSUSR.ICPS_WBC_TM_PLAN.CTD_OVRLMT_FEE is
'当期超限费';

comment on column GAPSUSR.ICPS_WBC_TM_PLAN.CTD_LPC is
'当期滞纳金';

comment on column GAPSUSR.ICPS_WBC_TM_PLAN.CTD_NSF_FEE is
'当期资金不足费';

comment on column GAPSUSR.ICPS_WBC_TM_PLAN.CTD_SVC_FEE is
'当期服务费';

comment on column GAPSUSR.ICPS_WBC_TM_PLAN.CTD_TXN_FEE is
'当期交易费';

comment on column GAPSUSR.ICPS_WBC_TM_PLAN.CTD_INS is
'当期保险金额';

comment on column GAPSUSR.ICPS_WBC_TM_PLAN.CTD_USER_FEE1 is
'当期新增自定义费用1';

comment on column GAPSUSR.ICPS_WBC_TM_PLAN.CTD_USER_FEE2 is
'当期新增自定义费用2';

comment on column GAPSUSR.ICPS_WBC_TM_PLAN.CTD_USER_FEE3 is
'当期新增自定义费用3';

comment on column GAPSUSR.ICPS_WBC_TM_PLAN.CTD_USER_FEE4 is
'当期新增自定义费用4';

comment on column GAPSUSR.ICPS_WBC_TM_PLAN.CTD_USER_FEE5 is
'当期新增自定义费用5';

comment on column GAPSUSR.ICPS_WBC_TM_PLAN.CTD_USER_FEE6 is
'当期新增自定义费用6';

comment on column GAPSUSR.ICPS_WBC_TM_PLAN.CTD_AMT_DB is
'当期借记金额';

comment on column GAPSUSR.ICPS_WBC_TM_PLAN.CTD_AMT_CR is
'当期贷记金额';

comment on column GAPSUSR.ICPS_WBC_TM_PLAN.CTD_NBR_DB is
'当期借记交易笔数';

comment on column GAPSUSR.ICPS_WBC_TM_PLAN.CTD_NBR_CR is
'当期贷记交易笔数';

comment on column GAPSUSR.ICPS_WBC_TM_PLAN.NODEFBNP_INT_ACRU is
'非延迟利息';

comment on column GAPSUSR.ICPS_WBC_TM_PLAN.BEG_DEFBNP_INT_ACRU is
'往期累积延时利息';

comment on column GAPSUSR.ICPS_WBC_TM_PLAN.CTD_DEFBNP_INT_ACRU is
'当期累积延时利息';

comment on column GAPSUSR.ICPS_WBC_TM_PLAN.USER_CODE1 is
'用户自定义代码1';

comment on column GAPSUSR.ICPS_WBC_TM_PLAN.USER_CODE2 is
'用户自定义代码2';

comment on column GAPSUSR.ICPS_WBC_TM_PLAN.USER_CODE3 is
'用户自定义代码3';

comment on column GAPSUSR.ICPS_WBC_TM_PLAN.USER_CODE4 is
'用户自定义代码4';

comment on column GAPSUSR.ICPS_WBC_TM_PLAN.USER_CODE5 is
'用户自定义代码5';

comment on column GAPSUSR.ICPS_WBC_TM_PLAN.USER_CODE6 is
'用户自定义代码6';

comment on column GAPSUSR.ICPS_WBC_TM_PLAN.USER_NUMBER1 is
'用户自定义笔数1';

comment on column GAPSUSR.ICPS_WBC_TM_PLAN.USER_NUMBER2 is
'用户自定义笔数2';

comment on column GAPSUSR.ICPS_WBC_TM_PLAN.USER_NUMBER3 is
'用户自定义笔数3';

comment on column GAPSUSR.ICPS_WBC_TM_PLAN.USER_NUMBER4 is
'用户自定义笔数4';

comment on column GAPSUSR.ICPS_WBC_TM_PLAN.USER_NUMBER5 is
'用户自定义笔数5';

comment on column GAPSUSR.ICPS_WBC_TM_PLAN.USER_NUMBER6 is
'用户自定义笔数6';

comment on column GAPSUSR.ICPS_WBC_TM_PLAN.USER_FIELD1 is
'用户自定义域1';

comment on column GAPSUSR.ICPS_WBC_TM_PLAN.USER_FIELD2 is
'用户自定义域2';

comment on column GAPSUSR.ICPS_WBC_TM_PLAN.USER_FIELD3 is
'用户自定义域3';

comment on column GAPSUSR.ICPS_WBC_TM_PLAN.USER_FIELD4 is
'用户自定义域4';

comment on column GAPSUSR.ICPS_WBC_TM_PLAN.USER_FIELD5 is
'用户自定义域5';

comment on column GAPSUSR.ICPS_WBC_TM_PLAN.USER_FIELD6 is
'用户自定义域6';

comment on column GAPSUSR.ICPS_WBC_TM_PLAN.USER_DATE1 is
'用户自定义日期1';

comment on column GAPSUSR.ICPS_WBC_TM_PLAN.USER_DATE2 is
'用户自定义日期2';

comment on column GAPSUSR.ICPS_WBC_TM_PLAN.USER_DATE3 is
'用户自定义日期3';

comment on column GAPSUSR.ICPS_WBC_TM_PLAN.USER_DATE4 is
'用户自定义日期4';

comment on column GAPSUSR.ICPS_WBC_TM_PLAN.USER_DATE5 is
'用户自定义日期5';

comment on column GAPSUSR.ICPS_WBC_TM_PLAN.USER_DATE6 is
'用户自定义日期6';

comment on column GAPSUSR.ICPS_WBC_TM_PLAN.USER_AMT1 is
'用户自定义金额1';

comment on column GAPSUSR.ICPS_WBC_TM_PLAN.USER_AMT2 is
'用户自定义金额2';

comment on column GAPSUSR.ICPS_WBC_TM_PLAN.USER_AMT3 is
'用户自定义金额3';

comment on column GAPSUSR.ICPS_WBC_TM_PLAN.USER_AMT4 is
'用户自定义金额4';

comment on column GAPSUSR.ICPS_WBC_TM_PLAN.USER_AMT5 is
'用户自定义金额5';

comment on column GAPSUSR.ICPS_WBC_TM_PLAN.USER_AMT6 is
'昨日贷记卡承诺余额';

comment on column GAPSUSR.ICPS_WBC_TM_PLAN.JPA_VERSION is
'乐观锁版本号';

comment on column GAPSUSR.ICPS_WBC_TM_PLAN.PAST_PENALTY is
'往期罚息';

comment on column GAPSUSR.ICPS_WBC_TM_PLAN.CTD_PENALTY is
'当期罚息';

comment on column GAPSUSR.ICPS_WBC_TM_PLAN.PAST_COMPOUND is
'往期复利';

comment on column GAPSUSR.ICPS_WBC_TM_PLAN.CTD_COMPOUND is
'当期复利';

comment on column GAPSUSR.ICPS_WBC_TM_PLAN.PENALTY_ACRU is
'罚息累计';

comment on column GAPSUSR.ICPS_WBC_TM_PLAN.COMPOUND_ACRU is
'复利累计';

comment on column GAPSUSR.ICPS_WBC_TM_PLAN.INTEREST_RATE is
'基础利率';

comment on column GAPSUSR.ICPS_WBC_TM_PLAN.PENALTY_RATE is
'罚息利率';

comment on column GAPSUSR.ICPS_WBC_TM_PLAN.COMPOUND_RATE is
'复利利率';

comment on column GAPSUSR.ICPS_WBC_TM_PLAN.USE_PLAN_RATE is
'是否使用plan的利率';

comment on column GAPSUSR.ICPS_WBC_TM_PLAN.LAST_PMT_DATE is
'上一还款日期';

comment on column GAPSUSR.ICPS_WBC_TM_PLAN.TERM is
'所在分期期数';

comment on column GAPSUSR.ICPS_WBC_TM_PLAN.CALC_TYPE is
'计费类型';

comment on column GAPSUSR.ICPS_WBC_TM_PLAN.CALC_CYCLE is
'计费周期';

comment on column GAPSUSR.ICPS_WBC_TM_PLAN.FEE_RATE is
'费率';

comment on column GAPSUSR.ICPS_WBC_TM_PLAN.LAST_FEE_DATE is
'上一收费日';

comment on column GAPSUSR.ICPS_WBC_TM_PLAN.NEXT_FEE_DATE is
'下一收费日';

comment on column GAPSUSR.ICPS_WBC_TM_PLAN.TXN_SEQ is
'交易流水号';

comment on column GAPSUSR.ICPS_WBC_TM_PLAN.FIRST_DD_DATE is
'首次约定还款日期';

comment on column GAPSUSR.ICPS_WBC_TM_PLAN.CONSUMER_TRANS_ID is
'业务流水号';

comment on column GAPSUSR.ICPS_WBC_TM_PLAN.SYS_TRANS_ID is
'系统调用流水号';

comment on column GAPSUSR.ICPS_WBC_TM_PLAN.QCHANNEL_ID is
'渠道编号';

comment on column GAPSUSR.ICPS_WBC_TM_PLAN.SUB_TERMINAL_TYPE is
'终端类型';

comment on column GAPSUSR.ICPS_WBC_TM_PLAN.SUB_MERCH_ID is
'二级商户编码';

comment on column GAPSUSR.ICPS_WBC_TM_PLAN.SUB_MERCH_NAME is
'二级商户名称';

comment on column GAPSUSR.ICPS_WBC_TM_PLAN.WARES_DESC is
'商品信息';

comment on column GAPSUSR.ICPS_WBC_TM_PLAN.LAST_MODIFIED_DATETIME is
'修改时间';

comment on column GAPSUSR.ICPS_WBC_TM_PLAN.ORIGINAL_AMT is
'原始交易本金';

comment on column GAPSUSR.ICPS_WBC_TM_PLAN.INTEREST_CALC_BASE is
'计息基数';

comment on column GAPSUSR.ICPS_WBC_TM_PLAN.CREATED_DATETIME is
'创建时间';

comment on column GAPSUSR.ICPS_WBC_TM_PLAN.IS_CHECK_FLAG is
'参与对账标识';

comment on column GAPSUSR.ICPS_WBC_TM_PLAN.EXTEND_PARAM1 is
'扩展1';

comment on column GAPSUSR.ICPS_WBC_TM_PLAN.EXTEND_PARAM2 is
'扩展2';

comment on column GAPSUSR.ICPS_WBC_TM_PLAN.EXTEND_PARAM3 is
'扩展3';

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
'公安核查结果信息表';

comment on column GAPSUSR.ICPS_WBC_TM_PSB_CHECK_INFO.BUSI_DATE is
'业务日期';

comment on column GAPSUSR.ICPS_WBC_TM_PSB_CHECK_INFO.FILE_ORDER is
'文件序号';

comment on column GAPSUSR.ICPS_WBC_TM_PSB_CHECK_INFO.SEQ_NO is
'查询流水号';

comment on column GAPSUSR.ICPS_WBC_TM_PSB_CHECK_INFO.ORG is
'机构号';

comment on column GAPSUSR.ICPS_WBC_TM_PSB_CHECK_INFO.APP_NO is
'申请件编号';

comment on column GAPSUSR.ICPS_WBC_TM_PSB_CHECK_INFO.ID_TYPE is
'证件类型';

comment on column GAPSUSR.ICPS_WBC_TM_PSB_CHECK_INFO.ID_NO is
'证件号码';

comment on column GAPSUSR.ICPS_WBC_TM_PSB_CHECK_INFO."NAME" is
'姓名';

comment on column GAPSUSR.ICPS_WBC_TM_PSB_CHECK_INFO.GENDER is
'性别';

comment on column GAPSUSR.ICPS_WBC_TM_PSB_CHECK_INFO.RESULT_PERSON_ID is
'证件号码核查结果';

comment on column GAPSUSR.ICPS_WBC_TM_PSB_CHECK_INFO.RESULT_PERSON_NAME is
'姓名核查结果';

comment on column GAPSUSR.ICPS_WBC_TM_PSB_CHECK_INFO.PHOTO_ID is
'照片文件id';

comment on column GAPSUSR.ICPS_WBC_TM_PSB_CHECK_INFO.NATION is
'民族';

comment on column GAPSUSR.ICPS_WBC_TM_PSB_CHECK_INFO.PHOTO_MD5 is
'照片md5值';

comment on column GAPSUSR.ICPS_WBC_TM_PSB_CHECK_INFO.OLD_NAME is
'曾用名';

comment on column GAPSUSR.ICPS_WBC_TM_PSB_CHECK_INFO.BIRTH is
'出生日期';

comment on column GAPSUSR.ICPS_WBC_TM_PSB_CHECK_INFO.NATIVE_PLACE is
'籍贯省市县（区）';

comment on column GAPSUSR.ICPS_WBC_TM_PSB_CHECK_INFO.ADDRESS is
'住址';

comment on column GAPSUSR.ICPS_WBC_TM_PSB_CHECK_INFO.WORK_PLACE is
'服务处所';

comment on column GAPSUSR.ICPS_WBC_TM_PSB_CHECK_INFO.MARITAL_STATUS is
'婚姻状况';

comment on column GAPSUSR.ICPS_WBC_TM_PSB_CHECK_INFO.DEGREE_OF_EDUCATION is
'文化程度';

comment on column GAPSUSR.ICPS_WBC_TM_PSB_CHECK_INFO.ISSUED_AUTHORITY is
'签发机关';

comment on column GAPSUSR.ICPS_WBC_TM_PSB_CHECK_INFO.BIRTH_PLACE is
'出生地';

comment on column GAPSUSR.ICPS_WBC_TM_PSB_CHECK_INFO.OCCUPATION is
'职业';

comment on column GAPSUSR.ICPS_WBC_TM_PSB_CHECK_INFO.BL0 is
'在逃状态';

comment on column GAPSUSR.ICPS_WBC_TM_PSB_CHECK_INFO.BL1 is
'违法状态';

comment on column GAPSUSR.ICPS_WBC_TM_PSB_CHECK_INFO.CREATED_DATETIME is
'创建时间';

comment on column GAPSUSR.ICPS_WBC_TM_PSB_CHECK_INFO.LAST_MODIFIED_DATETIME is
'最后修改时间';

comment on column GAPSUSR.ICPS_WBC_TM_PSB_CHECK_INFO.JPA_VERSION is
'乐观锁';

comment on column GAPSUSR.ICPS_WBC_TM_PSB_CHECK_INFO.PRODUCT_CD is
'产品编号';

comment on column GAPSUSR.ICPS_WBC_TM_PSB_CHECK_INFO.MSG_SERV_ERROR is
'服务异常描述';

comment on column GAPSUSR.ICPS_WBC_TM_PSB_CHECK_INFO.MSG_ID_ERROR is
'查询结果描述';

comment on column GAPSUSR.ICPS_WBC_TM_PSB_CHECK_INFO.FLAG is
'结果获取渠道';

comment on column GAPSUSR.ICPS_WBC_TM_PSB_CHECK_INFO.IS_CHECK_FLAG is
'参与对账标识';

comment on column GAPSUSR.ICPS_WBC_TM_PSB_CHECK_INFO.EXTEND_PARAM1 is
'扩展1';

comment on column GAPSUSR.ICPS_WBC_TM_PSB_CHECK_INFO.EXTEND_PARAM2 is
'扩展2';

comment on column GAPSUSR.ICPS_WBC_TM_PSB_CHECK_INFO.EXTEND_PARAM3 is
'扩展3';

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
'身份信息';

comment on column GAPSUSR.ICPS_WBC_TM_PSB_PERSONAL_INFO.BUSI_DATE is
'业务日期';

comment on column GAPSUSR.ICPS_WBC_TM_PSB_PERSONAL_INFO.FILE_ORDER is
'文件序号';

comment on column GAPSUSR.ICPS_WBC_TM_PSB_PERSONAL_INFO.ID is
'ID';

comment on column GAPSUSR.ICPS_WBC_TM_PSB_PERSONAL_INFO.APP_NO is
'申请件编号';

comment on column GAPSUSR.ICPS_WBC_TM_PSB_PERSONAL_INFO.CERTI_TYPE is
'证件类型';

comment on column GAPSUSR.ICPS_WBC_TM_PSB_PERSONAL_INFO.CERTI_NO is
'身份证号';

comment on column GAPSUSR.ICPS_WBC_TM_PSB_PERSONAL_INFO."NAME" is
'姓名';

comment on column GAPSUSR.ICPS_WBC_TM_PSB_PERSONAL_INFO.SEX is
'性别';

comment on column GAPSUSR.ICPS_WBC_TM_PSB_PERSONAL_INFO.BIRTH_DATE is
'出生日期';

comment on column GAPSUSR.ICPS_WBC_TM_PSB_PERSONAL_INFO.MARRYSTATE is
'婚姻状况';

comment on column GAPSUSR.ICPS_WBC_TM_PSB_PERSONAL_INFO.MOBILE is
'手机号码';

comment on column GAPSUSR.ICPS_WBC_TM_PSB_PERSONAL_INFO.HOMEPHONE is
'家庭电话';

comment on column GAPSUSR.ICPS_WBC_TM_PSB_PERSONAL_INFO.COMPPHONE is
'单位电话';

comment on column GAPSUSR.ICPS_WBC_TM_PSB_PERSONAL_INFO.QUALIFICATION is
'学历';

comment on column GAPSUSR.ICPS_WBC_TM_PSB_PERSONAL_INFO.DEGREE is
'学位';

comment on column GAPSUSR.ICPS_WBC_TM_PSB_PERSONAL_INFO.ADDRESS is
'通讯地址';

comment on column GAPSUSR.ICPS_WBC_TM_PSB_PERSONAL_INFO.RESIDE_ADDR is
'户籍地址';

comment on column GAPSUSR.ICPS_WBC_TM_PSB_PERSONAL_INFO.MATE_CERTP is
'配偶证件类型';

comment on column GAPSUSR.ICPS_WBC_TM_PSB_PERSONAL_INFO.MATE_CERNO is
'配偶证件号码';

comment on column GAPSUSR.ICPS_WBC_TM_PSB_PERSONAL_INFO.MATE_NAME is
'配偶姓名';

comment on column GAPSUSR.ICPS_WBC_TM_PSB_PERSONAL_INFO.MATE_CORP is
'配偶工作单位';

comment on column GAPSUSR.ICPS_WBC_TM_PSB_PERSONAL_INFO.MATE_PHONE is
'配偶联系电话';

comment on column GAPSUSR.ICPS_WBC_TM_PSB_PERSONAL_INFO.ADDR is
'居住地址';

comment on column GAPSUSR.ICPS_WBC_TM_PSB_PERSONAL_INFO.RESIDE_STATE is
'居住状况';

comment on column GAPSUSR.ICPS_WBC_TM_PSB_PERSONAL_INFO.COMP_NM is
'工作单位';

comment on column GAPSUSR.ICPS_WBC_TM_PSB_PERSONAL_INFO.COMP_ADDR is
'单位地址';

comment on column GAPSUSR.ICPS_WBC_TM_PSB_PERSONAL_INFO.PROFESS is
'职业';

comment on column GAPSUSR.ICPS_WBC_TM_PSB_PERSONAL_INFO.COMP_TRADE is
'行业';

comment on column GAPSUSR.ICPS_WBC_TM_PSB_PERSONAL_INFO.BUSINESS is
'职务';

comment on column GAPSUSR.ICPS_WBC_TM_PSB_PERSONAL_INFO.TEACH_POSE is
'职称';

comment on column GAPSUSR.ICPS_WBC_TM_PSB_PERSONAL_INFO.WORK_DATE is
'本单位工作起始年份';

comment on column GAPSUSR.ICPS_WBC_TM_PSB_PERSONAL_INFO.INFODATE is
'信息更新日期';

comment on column GAPSUSR.ICPS_WBC_TM_PSB_PERSONAL_INFO.CREATE_TIME is
'创建时间';

comment on column GAPSUSR.ICPS_WBC_TM_PSB_PERSONAL_INFO.PSB_QUERY_DATE is
'人行报告查询时间';

comment on column GAPSUSR.ICPS_WBC_TM_PSB_PERSONAL_INFO.REPORTSN is
'人行报告编号';

comment on column GAPSUSR.ICPS_WBC_TM_PSB_PERSONAL_INFO.IS_CHECK_FLAG is
'参与对账标识';

comment on column GAPSUSR.ICPS_WBC_TM_PSB_PERSONAL_INFO.EXTEND_PARAM1 is
'扩展1';

comment on column GAPSUSR.ICPS_WBC_TM_PSB_PERSONAL_INFO.EXTEND_PARAM2 is
'扩展2';

comment on column GAPSUSR.ICPS_WBC_TM_PSB_PERSONAL_INFO.EXTEND_PARAM3 is
'扩展3';

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
'贷款分配表';

comment on column GAPSUSR.ICPS_WBC_TM_SCHEDULE.BUSI_DATE is
'业务日期';

comment on column GAPSUSR.ICPS_WBC_TM_SCHEDULE.FILE_ORDER is
'文件序号';

comment on column GAPSUSR.ICPS_WBC_TM_SCHEDULE.SCHEDULE_ID is
'分配表ID';

comment on column GAPSUSR.ICPS_WBC_TM_SCHEDULE.LOAN_ID is
'分期计划ID';

comment on column GAPSUSR.ICPS_WBC_TM_SCHEDULE.ORG is
'机构号';

comment on column GAPSUSR.ICPS_WBC_TM_SCHEDULE.ACCT_NO is
'账户编号';

comment on column GAPSUSR.ICPS_WBC_TM_SCHEDULE.ACCT_TYPE is
'账户类型';

comment on column GAPSUSR.ICPS_WBC_TM_SCHEDULE.LOGICAL_CARD_NO is
'逻辑卡号';

comment on column GAPSUSR.ICPS_WBC_TM_SCHEDULE.CARD_NO is
'卡号';

comment on column GAPSUSR.ICPS_WBC_TM_SCHEDULE.LOAN_INIT_PRIN is
'分期总本金';

comment on column GAPSUSR.ICPS_WBC_TM_SCHEDULE.LOAN_INIT_TERM is
'分期总期数';

comment on column GAPSUSR.ICPS_WBC_TM_SCHEDULE.CURR_TERM is
'当前期数';

comment on column GAPSUSR.ICPS_WBC_TM_SCHEDULE.LOAN_TERM_PRIN is
'应还本金';

comment on column GAPSUSR.ICPS_WBC_TM_SCHEDULE.LOAN_TERM_FEE1 is
'应还费用';

comment on column GAPSUSR.ICPS_WBC_TM_SCHEDULE.LOAN_TERM_INTEREST is
'应还利息';

comment on column GAPSUSR.ICPS_WBC_TM_SCHEDULE.LOAN_PMT_DUE_DATE is
'到款到期还款日期';

comment on column GAPSUSR.ICPS_WBC_TM_SCHEDULE.LOAN_GRACE_DATE is
'宽限日';

comment on column GAPSUSR.ICPS_WBC_TM_SCHEDULE.LAST_MODIFIED_DATETIME is
'修改时间';

comment on column GAPSUSR.ICPS_WBC_TM_SCHEDULE.START_DATE is
'起息日';

comment on column GAPSUSR.ICPS_WBC_TM_SCHEDULE.SCHEDULE_ACTION is
'还款计划操作动作';

comment on column GAPSUSR.ICPS_WBC_TM_SCHEDULE.PRIN_PAID is
'已偿还本金';

comment on column GAPSUSR.ICPS_WBC_TM_SCHEDULE.INT_PAID is
'已偿还利息';

comment on column GAPSUSR.ICPS_WBC_TM_SCHEDULE.PENALTY_PAID is
'已偿还罚息';

comment on column GAPSUSR.ICPS_WBC_TM_SCHEDULE.COMPOUND_PAID is
'已偿还复利';

comment on column GAPSUSR.ICPS_WBC_TM_SCHEDULE.FEE_PAID is
'已偿还费用';

comment on column GAPSUSR.ICPS_WBC_TM_SCHEDULE.LATE_CHARGE_PAID is
'已偿还滞纳金';

comment on column GAPSUSR.ICPS_WBC_TM_SCHEDULE.ADV_PMT_FEE_PAID is
'已偿还提前还款手续费';

comment on column GAPSUSR.ICPS_WBC_TM_SCHEDULE.PAID_OUT_DATE is
'还清日期';

comment on column GAPSUSR.ICPS_WBC_TM_SCHEDULE.IS_CHECK_FLAG is
'参与对账标识';

comment on column GAPSUSR.ICPS_WBC_TM_SCHEDULE.EXTEND_PARAM1 is
'扩展1';

comment on column GAPSUSR.ICPS_WBC_TM_SCHEDULE.EXTEND_PARAM2 is
'扩展2';

comment on column GAPSUSR.ICPS_WBC_TM_SCHEDULE.EXTEND_PARAM3 is
'扩展3';

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
'交易码表（监管用）';

comment on column GAPSUSR.ICPS_WBC_TM_TXN_CD.BUSI_DATE is
'业务日期';

comment on column GAPSUSR.ICPS_WBC_TM_TXN_CD.FILE_ORDER is
'文件序号';

comment on column GAPSUSR.ICPS_WBC_TM_TXN_CD.FLOW_NO is
'FLOW_NO';

comment on column GAPSUSR.ICPS_WBC_TM_TXN_CD.ORG is
'机构号';

comment on column GAPSUSR.ICPS_WBC_TM_TXN_CD.TXN_CODE is
'交易码';

comment on column GAPSUSR.ICPS_WBC_TM_TXN_CD.TXN_DESC is
'交易描述';

comment on column GAPSUSR.ICPS_WBC_TM_TXN_CD.TXN_CLASS is
'TXN_CLASS';

comment on column GAPSUSR.ICPS_WBC_TM_TXN_CD.BNP is
'余额成分';

comment on column GAPSUSR.ICPS_WBC_TM_TXN_CD.IS_CHECK_FLAG is
'参与对账标识';

comment on column GAPSUSR.ICPS_WBC_TM_TXN_CD.EXTEND_PARAM1 is
'扩展1';

comment on column GAPSUSR.ICPS_WBC_TM_TXN_CD.EXTEND_PARAM2 is
'扩展2';

comment on column GAPSUSR.ICPS_WBC_TM_TXN_CD.EXTEND_PARAM3 is
'扩展3';

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
'当日入账交易表';

comment on column GAPSUSR.ICPS_WBC_TT_TXN_POST.BUSI_DATE is
'业务日期';

comment on column GAPSUSR.ICPS_WBC_TT_TXN_POST.FILE_ORDER is
'文件序号';

comment on column GAPSUSR.ICPS_WBC_TT_TXN_POST.ORG is
'机构号';

comment on column GAPSUSR.ICPS_WBC_TT_TXN_POST.TXN_SEQ is
'交易流水号';

comment on column GAPSUSR.ICPS_WBC_TT_TXN_POST.ACCT_NO is
'账户编号';

comment on column GAPSUSR.ICPS_WBC_TT_TXN_POST.ACCT_TYPE is
'账户类型';

comment on column GAPSUSR.ICPS_WBC_TT_TXN_POST.CARD_NO is
'卡号';

comment on column GAPSUSR.ICPS_WBC_TT_TXN_POST.LOGICAL_CARD_NO is
'逻辑卡号';

comment on column GAPSUSR.ICPS_WBC_TT_TXN_POST.BSC_LOGICCARD_NO is
'逻辑卡主卡卡号';

comment on column GAPSUSR.ICPS_WBC_TT_TXN_POST.PRODUCT_CD is
'产品代码';

comment on column GAPSUSR.ICPS_WBC_TT_TXN_POST.TXN_DATE is
'交易日期';

comment on column GAPSUSR.ICPS_WBC_TT_TXN_POST.TXN_TIME is
'交易时间';

comment on column GAPSUSR.ICPS_WBC_TT_TXN_POST.POST_TXN_TYPE is
'入账交易类型';

comment on column GAPSUSR.ICPS_WBC_TT_TXN_POST.TXN_CODE is
'交易码';

comment on column GAPSUSR.ICPS_WBC_TT_TXN_POST.DB_CR_IND is
'借贷标志';

comment on column GAPSUSR.ICPS_WBC_TT_TXN_POST.TXN_AMT is
'交易金额';

comment on column GAPSUSR.ICPS_WBC_TT_TXN_POST.POST_AMT is
'入账币种金额';

comment on column GAPSUSR.ICPS_WBC_TT_TXN_POST.POST_DATE is
'入账日期';

comment on column GAPSUSR.ICPS_WBC_TT_TXN_POST.AUTH_CODE is
'授权码';

comment on column GAPSUSR.ICPS_WBC_TT_TXN_POST.CARD_BLOCK_CODE is
'卡片锁定码';

comment on column GAPSUSR.ICPS_WBC_TT_TXN_POST.TXN_CURR_CD is
'交易币种代码';

comment on column GAPSUSR.ICPS_WBC_TT_TXN_POST.POST_CURR_CD is
'入账币种代码';

comment on column GAPSUSR.ICPS_WBC_TT_TXN_POST.ORIG_TRANS_DATE is
'原始交易日期';

comment on column GAPSUSR.ICPS_WBC_TT_TXN_POST.PLAN_NBR is
'信用计划号';

comment on column GAPSUSR.ICPS_WBC_TT_TXN_POST.REF_NBR is
'交易参考号';

comment on column GAPSUSR.ICPS_WBC_TT_TXN_POST.TXN_DESC is
'交易描述';

comment on column GAPSUSR.ICPS_WBC_TT_TXN_POST.TXN_SHORT_DESC is
'账单交易描述';

comment on column GAPSUSR.ICPS_WBC_TT_TXN_POST.POINT is
'积分数值';

comment on column GAPSUSR.ICPS_WBC_TT_TXN_POST.POSTING_FLAG is
'入账结果标示码';

comment on column GAPSUSR.ICPS_WBC_TT_TXN_POST.PRE_POSTING_FLAG is
'往日入账结果标示码';

comment on column GAPSUSR.ICPS_WBC_TT_TXN_POST.REL_PMT_AMT is
'公司卡还款金额';

comment on column GAPSUSR.ICPS_WBC_TT_TXN_POST.ORIG_PMT_AMT is
'还款交易原始金额';

comment on column GAPSUSR.ICPS_WBC_TT_TXN_POST.ACQ_BRANCH_ID is
'受理分行代码';

comment on column GAPSUSR.ICPS_WBC_TT_TXN_POST.ACQ_TERMINAL_ID is
'受理机构终端标识码';

comment on column GAPSUSR.ICPS_WBC_TT_TXN_POST.ACQ_ACCEPTOR_ID is
'受卡方标识码';

comment on column GAPSUSR.ICPS_WBC_TT_TXN_POST.ACQ_NAME_ADDR is
'受理机构名称地址';

comment on column GAPSUSR.ICPS_WBC_TT_TXN_POST.MCC is
'商户类别代码';

comment on column GAPSUSR.ICPS_WBC_TT_TXN_POST.INPUT_TXN_CODE is
'原交易交易码';

comment on column GAPSUSR.ICPS_WBC_TT_TXN_POST.INPUT_TXN_AMT is
'原交易交易金额';

comment on column GAPSUSR.ICPS_WBC_TT_TXN_POST.INPUT_SETT_AMT is
'原交易清算金额';

comment on column GAPSUSR.ICPS_WBC_TT_TXN_POST.INTERCHANGE_FEE is
'原交易货币转换费';

comment on column GAPSUSR.ICPS_WBC_TT_TXN_POST.FEE_PAYOUT is
'发卡方应付手续费';

comment on column GAPSUSR.ICPS_WBC_TT_TXN_POST.FEE_PROFIT is
'发卡方应得手续费';

comment on column GAPSUSR.ICPS_WBC_TT_TXN_POST.LOAN_ISSUE_PROFIT is
'分期交易发卡行收益';

comment on column GAPSUSR.ICPS_WBC_TT_TXN_POST.STMT_DATE is
'账单日期';

comment on column GAPSUSR.ICPS_WBC_TT_TXN_POST.VOUCHER_NO is
'销售单凭证号';

comment on column GAPSUSR.ICPS_WBC_TT_TXN_POST.JPA_VERSION is
'乐观锁版本号';

comment on column GAPSUSR.ICPS_WBC_TT_TXN_POST.TERM is
'所在分期期数';

comment on column GAPSUSR.ICPS_WBC_TT_TXN_POST.CONSUMER_TRANS_ID is
'业务流水号';

comment on column GAPSUSR.ICPS_WBC_TT_TXN_POST.SYS_TRANS_ID is
'系统调用流水号';

comment on column GAPSUSR.ICPS_WBC_TT_TXN_POST.QCHANNEL_ID is
'渠道编号';

comment on column GAPSUSR.ICPS_WBC_TT_TXN_POST.SUB_TERMINAL_TYPE is
'终端类型';

comment on column GAPSUSR.ICPS_WBC_TT_TXN_POST.SUB_MERCH_ID is
'二级商户编码';

comment on column GAPSUSR.ICPS_WBC_TT_TXN_POST.SUB_MERCH_NAME is
'二级商户名称';

comment on column GAPSUSR.ICPS_WBC_TT_TXN_POST.WARES_DESC is
'商品信息';

comment on column GAPSUSR.ICPS_WBC_TT_TXN_POST.LAST_MODIFIED_DATETIME is
'修改时间';

comment on column GAPSUSR.ICPS_WBC_TT_TXN_POST.PAID_STMT_DATE is
'还款账单日';

comment on column GAPSUSR.ICPS_WBC_TT_TXN_POST.REPAY_AMT is
'应还款额';

comment on column GAPSUSR.ICPS_WBC_TT_TXN_POST.COUNTER_ACCT is
'对手方账户';

comment on column GAPSUSR.ICPS_WBC_TT_TXN_POST.COUNTER_NAME is
'对手方姓名';

comment on column GAPSUSR.ICPS_WBC_TT_TXN_POST.COUNTER_BRNO is
'对手方行号';

comment on column GAPSUSR.ICPS_WBC_TT_TXN_POST.COUNTER_BRNAME is
'对手方行名';

comment on column GAPSUSR.ICPS_WBC_TT_TXN_POST.IS_CHECK_FLAG is
'参与对账标识';

comment on column GAPSUSR.ICPS_WBC_TT_TXN_POST.EXTEND_PARAM1 is
'扩展1';

comment on column GAPSUSR.ICPS_WBC_TT_TXN_POST.EXTEND_PARAM2 is
'扩展2';

comment on column GAPSUSR.ICPS_WBC_TT_TXN_POST.EXTEND_PARAM3 is
'扩展3';

