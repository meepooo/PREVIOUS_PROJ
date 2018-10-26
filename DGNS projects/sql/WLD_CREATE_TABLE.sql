drop table ADDR_CODE_PARA;

drop table LOAN_ACCT_INFO;

drop table LOAN_CARD_INFO;

drop table LOAN_CHECK_DATA;

drop table LOAN_CHECK_RESULT;

drop table LOAN_CUST_INFO;

drop table LOAN_DUE_PRE_REG;

drop table LOAN_INFO;

drop table LOAN_SUB_ACCT;

drop table LOAN_SUB_ACCT_PARA;

drop table LOAN_SUB_ACCT_REG;

drop table LOAN_SUB_BAL;

drop table LOAN_SUB_CHECK;

drop table LOAN_TAX_REG;

drop table LOAN_TYPE_PARA;

drop table LOAN_VMS_INFO;

--==============================================================
-- Table: ADDR_CODE_PARA
--==============================================================
create table ADDR_CODE_PARA
(
   CODE                 VARCHAR(6)             not null,
   ADDR                 VARCHAR(60),
   IS_FARM              VARCHAR(1),
   VALID_FLAG           VARCHAR(1),
   EXTFLD1              VARCHAR(32),
   EXTFLD2              VARCHAR(64),
   constraint "P_Key_1" primary key (CODE)
);

comment on table ADDR_CODE_PARA is
'身份证前六位参数';

comment on column ADDR_CODE_PARA.CODE is
'身份证前六位';

comment on column ADDR_CODE_PARA.IS_FARM is
'是否农户标志，0-非农户，1-农户，9-未知';

comment on column ADDR_CODE_PARA.VALID_FLAG is
'有效标识:0-无效，1-有效';

comment on column ADDR_CODE_PARA.EXTFLD1 is
'备用字段1';

comment on column ADDR_CODE_PARA.EXTFLD2 is
'备用字段2';

--==============================================================
-- Table: LOAN_ACCT_INFO
--==============================================================
create table LOAN_ACCT_INFO
(
   BUSI_TYPE            VARCHAR(10)            not null,
   REG_DATE             VARCHAR(8),
   REG_TIME             VARCHAR(14),
   LOAN_ACCT_NO         VARCHAR(32)            not null,
   ACCT_TYPE            VARCHAR(1)             not null,
   LOAN_ACCT_NAME       VARCHAR(60),
   LOAN_CUST_NO         VARCHAR(32),
   GENDER               VARCHAR(1),
   ACCT_OPEN_DATE       VARCHAR(8),
   ACCT_CLOSE_DATE      VARCHAR(8),
   DUE_DAYS             INTEGER,
   DGNS_LOAN_TYPE       VARCHAR(1),
   DGNS_LOAN_IN_TYPE    VARCHAR(1),
   CUST_LIMIT_ID        VARCHAR(20),
   PRODUCT_CODE         VARCHAR(6),
   LOGICAL_CARD_NO      VARCHAR(19),
   DSF_LOAN_TYPE        VARCHAR(1),
   IS_FARM              VARCHAR(1),
   CURR                 VARCHAR(3),
   CREDIT_LIMIT         DECIMAL(16,2),
   CURR_BALANCE         DECIMAL(16,2),
   PRINCIPAL_BAL        DECIMAL(16,2),
   BEGIN_BAL            DECIMAL(16,2),
   PMT_DUE_DAY_BAL      DECIMAL(16,2),
   BILLING_CYCLE        VARCHAR(2),
   MOBILE_NO            VARCHAR(20),
   LOAN_ACCT_STAT       VARCHAR(2),
   AGE_CD               VARCHAR(8),
   UNMATCH_DB           DECIMAL(16,2),
   UNMATCH_CR           DECIMAL(16,2),
   DD_IND               VARCHAR(1),
   DD_BANK_NAME         VARCHAR(60),
   DD_BANK_BRANCH       VARCHAR(14),
   DD_BANK_ACCT_NO      VARCHAR(32),
   DD_BANK_ACCT_NAME    VARCHAR(60),
   LAST_DD_AMT          DECIMAL(16,2),
   LAST_DD_DATE         VARCHAR(8),
   LAST_PMT_AMT         DECIMAL(16,2),
   LAST_PMT_DATE        VARCHAR(8),
   LAST_STMT_DATE       VARCHAR(8),
   LAST_PMT_DUE_DATE    VARCHAR(8),
   LAST_AGING_DATE      VARCHAR(8),
   COLLECT_DATE         VARCHAR(8),
   COLLECT_OUT_DATE     VARCHAR(8),
   NEXT_STMT_DATE       VARCHAR(8),
   PMT_DUE_DATE         VARCHAR(8),
   DD_DATE              VARCHAR(8),
   GRACE_DATE           VARCHAR(8),
   CLOSED_DATE          VARCHAR(8),
   FIRST_STMT_DATE      VARCHAR(8),
   CANCEL_DATE          VARCHAR(8),
   CHARGE_OFF_DATE      VARCHAR(8),
   WAIVE_SVCFEE_IND     VARCHAR(1),
   USER_DATE2           VARCHAR(8),
   MTD_PAYMENT_AMT      DECIMAL(16,2),
   MTD_PAYMENT_CNT      INTEGER,
   YTD_PAYMENT_AMT      DECIMAL(16,2),
   YTD_PAYMENT_CNT      INTEGER,
   LTD_PAYMENT_AMT      DECIMAL(16,2),
   LTD_PAYMENT_CNT      INTEGER,
   LAST_MOD_DATETIME    VARCHAR(14),
   BANK_PROPORTION      DECIMAL(16,2),
   EXTFLD1              VARCHAR(32),
   EXTFLD2              VARCHAR(64),
   constraint "P_Key_1" primary key (BUSI_TYPE, LOAN_ACCT_NO, ACCT_TYPE)
);

comment on table LOAN_ACCT_INFO is
'贷款账户基础信息表';

comment on column LOAN_ACCT_INFO.BUSI_TYPE is
'业务类型
1:WLD 微粒贷
2:ALJB 阿里巴巴借呗
3:WCD 微车贷';

comment on column LOAN_ACCT_INFO.REG_DATE is
'登记日期';

comment on column LOAN_ACCT_INFO.REG_TIME is
'登记时间';

comment on column LOAN_ACCT_INFO.LOAN_ACCT_NO is
'贷款账号';

comment on column LOAN_ACCT_INFO.ACCT_TYPE is
'A	人民币独立基本信用账户
B	美元独立基本信用账户
C	人民币共享基本信用账户
D	美元共享基本信用账户
E	人民币独立小额贷款账户
F	人民币活期借记账户
G	人民币智能存款户
Q	Q币账户
H	人民币独立贷款账户
I	人民币共享贷款账户-wx
J	人民币共享贷款账户- J';

comment on column LOAN_ACCT_INFO.LOAN_ACCT_NAME is
'贷款账号户名';

comment on column LOAN_ACCT_INFO.LOAN_CUST_NO is
'贷款人客户号';

comment on column LOAN_ACCT_INFO.GENDER is
'性别：
1	男性
2	女性
9	未知';

comment on column LOAN_ACCT_INFO.ACCT_OPEN_DATE is
'开户日期，贷款开户日期';

comment on column LOAN_ACCT_INFO.ACCT_CLOSE_DATE is
'贷款账户销户日期';

comment on column LOAN_ACCT_INFO.DUE_DAYS is
'逾期天数';

comment on column LOAN_ACCT_INFO.DGNS_LOAN_TYPE is
'农商行七级分类
1：0天	正常一
2：0天	正常二，微粒贷联合贷款贷款分类所有正常都归到“正常二”当中，不存在“正常一”。
3：逾期1-30天	关注一
4：逾期31-90天	关注二
5：逾期91-120天	次级
6：逾期121-180天	可疑
7：181天以上	损失';

comment on column LOAN_ACCT_INFO.DGNS_LOAN_IN_TYPE is
'农商行贷款内部风险分类
内部风险分类结果	划分标准
1:一类贷款	正常一类
2:二类贷款	正常二类
3:三类贷款	贷款本金或正常利息逾期30天（含）以内
4:四类贷款	贷款本金或正常利息逾期31天-90天（含）以内或表5:外业务垫款30天（含）以内
5:五类贷款	贷款本金或正常利息逾期91天-180天（含）以内或表外业务垫款31天-90天（含）
6:六类贷款	贷款本金或正常利息逾期181天-550天（含）以内或表外业务垫款91天-270天（含）
7:七类贷款	贷款本金或正常利息逾期551天（含）以上或表外业务垫款271天（含）以上';

comment on column LOAN_ACCT_INFO.DSF_LOAN_TYPE is
'第三方贷款分类：
R	消费转分期
C	现金分期
B	账单分期
P	POS分期
M	大额分期（专项分期）
MCAT	随借随还
MCEP	等额本金
MCEI	等额本息
MCOT	一次性还本付息
WELO	微众一贷
DMCEP	微众二贷
MCEIS	微众等额本息S';

comment on column LOAN_ACCT_INFO.IS_FARM is
'是否农户标志，0-非农户，1-农户';

comment on column LOAN_ACCT_INFO.CURR is
'币种';

comment on column LOAN_ACCT_INFO.CREDIT_LIMIT is
'授信额度';

comment on column LOAN_ACCT_INFO.PRINCIPAL_BAL is
'贷款金额，乘以出资比例的金额';

comment on column LOAN_ACCT_INFO.BEGIN_BAL is
'上一到期日余额';

comment on column LOAN_ACCT_INFO.PMT_DUE_DAY_BAL is
'到期还款日余额';

comment on column LOAN_ACCT_INFO.BILLING_CYCLE is
'还款日';

comment on column LOAN_ACCT_INFO.MOBILE_NO is
'移动电话';

comment on column LOAN_ACCT_INFO.LOAN_ACCT_STAT is
'贷款账号状态，1-正常， 2-逾期， 3-销户';

comment on column LOAN_ACCT_INFO.AGE_CD is
'拖欠月数';

comment on column LOAN_ACCT_INFO.UNMATCH_DB is
'未入账借记金额';

comment on column LOAN_ACCT_INFO.UNMATCH_CR is
'未入账贷记金额';

comment on column LOAN_ACCT_INFO.DD_IND is
'约定还款类型';

comment on column LOAN_ACCT_INFO.DD_BANK_NAME is
'约定还款银行名称';

comment on column LOAN_ACCT_INFO.DD_BANK_BRANCH is
'约定还款开户行号';

comment on column LOAN_ACCT_INFO.DD_BANK_ACCT_NO is
'约定还款扣款账号';

comment on column LOAN_ACCT_INFO.DD_BANK_ACCT_NAME is
'约定还款扣款账户姓名';

comment on column LOAN_ACCT_INFO.LAST_DD_AMT is
'上期约定还款金额';

comment on column LOAN_ACCT_INFO.LAST_DD_DATE is
'上期约定还款日期';

comment on column LOAN_ACCT_INFO.LAST_PMT_AMT is
'上笔还款金额';

comment on column LOAN_ACCT_INFO.LAST_PMT_DATE is
'上个还款日期';

comment on column LOAN_ACCT_INFO.LAST_STMT_DATE is
'上个到期还款日期';

comment on column LOAN_ACCT_INFO.LAST_PMT_DUE_DATE is
'上个逾期还款日期';

comment on column LOAN_ACCT_INFO.LAST_AGING_DATE is
'上个逾期月数提升日期';

comment on column LOAN_ACCT_INFO.COLLECT_DATE is
'入催日期';

comment on column LOAN_ACCT_INFO.COLLECT_OUT_DATE is
'出催收队列日期';

comment on column LOAN_ACCT_INFO.NEXT_STMT_DATE is
'下个到期还款日期';

comment on column LOAN_ACCT_INFO.PMT_DUE_DATE is
'到期还款日期';

comment on column LOAN_ACCT_INFO.DD_DATE is
'约定还款日期';

comment on column LOAN_ACCT_INFO.GRACE_DATE is
'宽限日期';

comment on column LOAN_ACCT_INFO.CLOSED_DATE is
'最终销户日期';

comment on column LOAN_ACCT_INFO.FIRST_STMT_DATE is
'首个到期还款日期';

comment on column LOAN_ACCT_INFO.CANCEL_DATE is
'销户日期';

comment on column LOAN_ACCT_INFO.CHARGE_OFF_DATE is
'转呆账日期';

comment on column LOAN_ACCT_INFO.WAIVE_SVCFEE_IND is
'是否免除服务费';

comment on column LOAN_ACCT_INFO.USER_DATE2 is
'上次调额日期';

comment on column LOAN_ACCT_INFO.MTD_PAYMENT_AMT is
'当月还款金额';

comment on column LOAN_ACCT_INFO.MTD_PAYMENT_CNT is
'当月还款笔数';

comment on column LOAN_ACCT_INFO.YTD_PAYMENT_AMT is
'当年还款金额';

comment on column LOAN_ACCT_INFO.YTD_PAYMENT_CNT is
'当年还款笔数';

comment on column LOAN_ACCT_INFO.LTD_PAYMENT_AMT is
'历史还款金额';

comment on column LOAN_ACCT_INFO.LTD_PAYMENT_CNT is
'历史还款笔数';

comment on column LOAN_ACCT_INFO.LAST_MOD_DATETIME is
'修改日期';

comment on column LOAN_ACCT_INFO.BANK_PROPORTION is
'银行出资比例';

comment on column LOAN_ACCT_INFO.EXTFLD1 is
'备用字段1';

comment on column LOAN_ACCT_INFO.EXTFLD2 is
'备用字段2';

--==============================================================
-- Table: LOAN_CARD_INFO
--==============================================================
create table LOAN_CARD_INFO
(
   BUSI_TYPE            VARCHAR(10)            not null,
   REG_DATE             VARCHAR(8),
   REG_TIME             VARCHAR(14),
   LOGICAL_CARD_NO      VARCHAR(19)            not null,
   ACCT_NO              VARCHAR(32)            not null,
   CUST_ID              VARCHAR(32),
   PRODUCT_CODE         VARCHAR(6),
   APP_NO               VARCHAR(20),
   BSC_LOGICCARD_NO     VARCHAR(19),
   ACTIVATE_IND         VARCHAR(1),
   CANCEL_DATE          VARCHAR(14),
   LATEST_CARD_NO       VARCHAR(19),
   CARD_EXPIRE_DATE     VARCHAR(14),
   IS_CHECK_FLAG        VARCHAR(1),
   EXTFLD1              VARCHAR(32),
   EXTFLD2              VARCHAR(64),
   constraint "P_Key_1" primary key (BUSI_TYPE, LOGICAL_CARD_NO)
);

comment on table LOAN_CARD_INFO is
'贷款-卡账户信息表';

comment on column LOAN_CARD_INFO.BUSI_TYPE is
'业务类型
1:WLD 微粒贷
2:ALJB 阿里巴巴借呗
3:WCD 微车贷';

comment on column LOAN_CARD_INFO.REG_DATE is
'登记日期';

comment on column LOAN_CARD_INFO.REG_TIME is
'登记时间';

comment on column LOAN_CARD_INFO.ACCT_NO is
'贷款账号';

comment on column LOAN_CARD_INFO.CUST_ID is
'贷款人客户号';

comment on column LOAN_CARD_INFO.EXTFLD1 is
'备用字段1';

comment on column LOAN_CARD_INFO.EXTFLD2 is
'备用字段2';

--==============================================================
-- Table: LOAN_CHECK_DATA
--==============================================================
create table LOAN_CHECK_DATA
(
   BUSI_TYPE            VARCHAR(10)            not null,
   REG_DATE             VARCHAR(8),
   REG_TIME             VARCHAR(14),
   SUB_BELONG           VARCHAR(1)             not null,
   CHECK_DATE           VARCHAR(8)             not null,
   SEQNO                INTEGER                not null,
   LOAN_BUSI_NAME       VARCHAR(60),
   LOAN_BUSI_DESC       VARCHAR(60),
   ORG_ID               VARCHAR(12),
   CHECK_TYPE           VARCHAR(1),
   SUB_NUM              INTEGER,
   D_BAL                DECIMAL(16,2),
   D_AMT                DECIMAL(16,2),
   C_BAL                DECIMAL(16,2),
   C_AMT                DECIMAL(16,2),
   EXTFLD1              VARCHAR(32),
   EXTFLD2              VARCHAR(64),
   constraint "P_Key_1" primary key (CHECK_DATE, BUSI_TYPE, SEQNO, SUB_BELONG)
);

comment on table LOAN_CHECK_DATA is
'对账流水表';

comment on column LOAN_CHECK_DATA.BUSI_TYPE is
'业务类型
1:WLD 微粒贷
2:ALJB 阿里巴巴借呗
3:WCD 微车贷';

comment on column LOAN_CHECK_DATA.REG_DATE is
'登记日期';

comment on column LOAN_CHECK_DATA.REG_TIME is
'登记时间';

comment on column LOAN_CHECK_DATA.SUB_BELONG is
'第三方科目归属:
1.农商行对应科目
2.业务类型对应科目（如WLD)
3.账务登记簿对应科目';

comment on column LOAN_CHECK_DATA.SEQNO is
'序号';

comment on column LOAN_CHECK_DATA.ORG_ID is
'农商行机构号';

comment on column LOAN_CHECK_DATA.CHECK_TYPE is
'对账方式:
1-农商行科目余额与第三方科目余额对账
2-农商行登记簿余额与第三方科目余额对账
3-农商行科目余额+登记簿余额与第三方科目余额对账汇总对账
9-未知';

comment on column LOAN_CHECK_DATA.SUB_NUM is
'科目笔数';

comment on column LOAN_CHECK_DATA.EXTFLD1 is
'备用字段1';

comment on column LOAN_CHECK_DATA.EXTFLD2 is
'备用字段2';

--==============================================================
-- Table: LOAN_CHECK_RESULT
--==============================================================
create table LOAN_CHECK_RESULT
(
   BUSI_TYPE            VARCHAR(10)            not null,
   CHECK_DATE           VARCHAR(8)             not null,
   SEQNO                INTEGER                not null,
   LOAN_BUSI_NAME       VARCHAR(60),
   LOAN_BUSI_DESC       VARCHAR(60),
   ORG_ID               VARCHAR(12),
   CHECK_TYPE           VARCHAR(1),
   DGNS_D_SUM_BAL       DECIMAL(16,2),
   DGNS_D_SUM_AMT       DECIMAL(16,2),
   DGNS_C_SUM_BAL       DECIMAL(16,2),
   DGNS_C_SUM_AMT       DECIMAL(16,2),
   DSF_D_SUM_BAL        DECIMAL(16,2),
   DSF_D_SUM_AMT        DECIMAL(16,2),
   DSF_C_SUM_BAL        DECIMAL(16,2),
   DSF_C_SUM_AMT        DECIMAL(16,2),
   REG_D_SUM_BAL        DECIMAL(16,2),
   REG_D_SUM_AMT        DECIMAL(16,2),
   REG_C_SUM_BAL        DECIMAL(16,2),
   REG_C_SUM_AMT        DECIMAL(16,2),
   CHECK_FLAG           VARCHAR(10),
   CHECK_FLAG_DESC      VARCHAR(60),
   EXTFLD1              VARCHAR(32),
   EXTFLD2              VARCHAR(64),
   constraint "P_Key_1" primary key (CHECK_DATE, BUSI_TYPE, SEQNO)
);

comment on table LOAN_CHECK_RESULT is
'对账结果表';

comment on column LOAN_CHECK_RESULT.BUSI_TYPE is
'业务类型
1:WLD 微粒贷
2:ALJB 阿里巴巴借呗
3:WCD 微车贷';

comment on column LOAN_CHECK_RESULT.SEQNO is
'序号';

comment on column LOAN_CHECK_RESULT.ORG_ID is
'农商行机构号';

comment on column LOAN_CHECK_RESULT.CHECK_TYPE is
'对账方式:
1-农商行科目余额与第三方科目余额对账
2-农商行登记簿余额与第三方科目余额对账
3-农商行科目余额+登记簿余额与第三方科目余额对账汇总对账
9-未知';

comment on column LOAN_CHECK_RESULT.CHECK_FLAG is
'对账状态：
第一位：发生额对账
1-对账平
2-微粒贷少
3-农商行少
第二位：余额对账
1-对账平
2-微粒贷少
3-农商行少';

comment on column LOAN_CHECK_RESULT.CHECK_FLAG_DESC is
'对账结果描述';

comment on column LOAN_CHECK_RESULT.EXTFLD1 is
'备用字段1';

comment on column LOAN_CHECK_RESULT.EXTFLD2 is
'备用字段2';

--==============================================================
-- Table: LOAN_CUST_INFO
--==============================================================
create table LOAN_CUST_INFO
(
   BUSI_TYPE            VARCHAR(10)            not null,
   REG_DATE             VARCHAR(8),
   REG_TIME             VARCHAR(14),
   ORG_ID               VARCHAR(12),
   CUST_ID              VARCHAR(32)            not null,
   ID_NO                VARCHAR(30),
   ID_TYPE              VARCHAR(1),
   "NAME"               VARCHAR(60),
   GENDER               VARCHAR(1),
   BIRTHDAY             VARCHAR(8),
   NATIONALITY          VARCHAR(3),
   PR_OF_COUNTRY        VARCHAR(1),
   COUNTRY_CODE         VARCHAR(3),
   MOBILE_NO            VARCHAR(20),
   EMB_NAME             VARCHAR(26),
   CUST_LIMIT_ID        VARCHAR(20),
   LAST_MOD_DATETIME    VARCHAR(14),
   SURNAME              VARCHAR(20),
   IS_FARM              VARCHAR(1),
   EXTFLD1              VARCHAR(32),
   EXTFLD2              VARCHAR(64),
   constraint "P_Key_1" primary key (BUSI_TYPE, CUST_ID)
);

comment on table LOAN_CUST_INFO is
'客户信息表';

comment on column LOAN_CUST_INFO.BUSI_TYPE is
'业务类型
1:WLD 微粒贷
2:ALJB 阿里巴巴借呗
3:WCD 微车贷';

comment on column LOAN_CUST_INFO.REG_DATE is
'登记日期';

comment on column LOAN_CUST_INFO.REG_TIME is
'登记时间';

comment on column LOAN_CUST_INFO.ORG_ID is
'机构号';

comment on column LOAN_CUST_INFO.CUST_ID is
'客户编号，唯一标识';

comment on column LOAN_CUST_INFO.ID_NO is
'证件号码';

comment on column LOAN_CUST_INFO.ID_TYPE is
'证件类型';

comment on column LOAN_CUST_INFO."NAME" is
'客户姓名';

comment on column LOAN_CUST_INFO.GENDER is
'性别：
1	男性
2	女性
9	未知';

comment on column LOAN_CUST_INFO.NATIONALITY is
'国籍代码';

comment on column LOAN_CUST_INFO.PR_OF_COUNTRY is
'是否永久居住
Y	是
N	否';

comment on column LOAN_CUST_INFO.COUNTRY_CODE is
'永久居住地国家代码';

comment on column LOAN_CUST_INFO.MOBILE_NO is
'移动电话';

comment on column LOAN_CUST_INFO.EMB_NAME is
'拼音名';

comment on column LOAN_CUST_INFO.CUST_LIMIT_ID is
'客户额度ID';

comment on column LOAN_CUST_INFO.LAST_MOD_DATETIME is
'修改日期';

comment on column LOAN_CUST_INFO.SURNAME is
'姓氏';

comment on column LOAN_CUST_INFO.IS_FARM is
'是否农户标志，0-非农户，1-农户';

comment on column LOAN_CUST_INFO.EXTFLD1 is
'备用字段1';

comment on column LOAN_CUST_INFO.EXTFLD2 is
'备用字段2';

--==============================================================
-- Table: LOAN_DUE_PRE_REG
--==============================================================
create table LOAN_DUE_PRE_REG
(
   BUSI_TYPE            VARCHAR(10)            not null,
   REG_DATE             VARCHAR(8),
   REG_TIME             VARCHAR(14),
   LOAN_ID              VARCHAR(20)            not null,
   LOAN_ACCT_NO         VARCHAR(32),
   CARD_NO              VARCHAR(19),
   REF_NBR              VARCHAR(23),
   LOGICAL_CARD_NO      VARCHAR(19),
   OLD_LOAN_IN_TYPE     VARCHAR(1),
   DGNS_LOAN_IN_TYPE    VARCHAR(1)             not null,
   ACCT_DATE            VARCHAR(8),
   ACCT_SEQNO           VARCHAR(32),
   SEQNO                INTEGER,
   LOAN_BAL             DECIMAL(16,2),
   AMT1                 DECIMAL(16,2),
   AMT2                 DECIMAL(16,2),
   AMT                  DECIMAL(16,2),
   STATE                VARCHAR(1),
   EXTFLD1              VARCHAR(32),
   EXTFLD2              VARCHAR(64),
   constraint "P_Key_1" primary key (BUSI_TYPE, LOAN_ID, DGNS_LOAN_IN_TYPE)
);

comment on table LOAN_DUE_PRE_REG is
'逾期贷款计提准备登记簿';

comment on column LOAN_DUE_PRE_REG.BUSI_TYPE is
'业务类型
1:WLD 微粒贷
2:ALJB 阿里巴巴借呗
3:WCD 微车贷';

comment on column LOAN_DUE_PRE_REG.REG_DATE is
'登记日期';

comment on column LOAN_DUE_PRE_REG.REG_TIME is
'登记时间';

comment on column LOAN_DUE_PRE_REG.LOAN_ID is
'借据ID';

comment on column LOAN_DUE_PRE_REG.LOAN_ACCT_NO is
'贷款账号';

comment on column LOAN_DUE_PRE_REG.CARD_NO is
'介质卡号';

comment on column LOAN_DUE_PRE_REG.REF_NBR is
'交易参考号';

comment on column LOAN_DUE_PRE_REG.LOGICAL_CARD_NO is
'默认逻辑卡号';

comment on column LOAN_DUE_PRE_REG.DGNS_LOAN_IN_TYPE is
'农商行贷款内部风险分类
内部风险分类结果	划分标准
1:一类贷款	正常一类
2:二类贷款	正常二类
3:三类贷款	贷款本金或正常利息逾期30天（含）以内
4:四类贷款	贷款本金或正常利息逾期31天-90天（含）以内或表5:外业务垫款30天（含）以内
5:五类贷款	贷款本金或正常利息逾期91天-180天（含）以内或表外业务垫款31天-90天（含）
6:六类贷款	贷款本金或正常利息逾期181天-550天（含）以内或表外业务垫款91天-270天（含）
7:七类贷款	贷款本金或正常利息逾期551天（含）以上或表外业务垫款271天（含）以上';

comment on column LOAN_DUE_PRE_REG.ACCT_DATE is
'账务日期';

comment on column LOAN_DUE_PRE_REG.ACCT_SEQNO is
'平台流水号';

comment on column LOAN_DUE_PRE_REG.SEQNO is
'交易序号';

comment on column LOAN_DUE_PRE_REG.LOAN_BAL is
'到期还款日余额';

comment on column LOAN_DUE_PRE_REG.AMT1 is
'到期还款日余额';

comment on column LOAN_DUE_PRE_REG.AMT2 is
'到期还款日余额';

comment on column LOAN_DUE_PRE_REG.STATE is
'1-成功，2-失败，9-初始，A-本金计提，B-利息计提';

comment on column LOAN_DUE_PRE_REG.EXTFLD1 is
'备用字段1';

comment on column LOAN_DUE_PRE_REG.EXTFLD2 is
'备用字段2';

--==============================================================
-- Table: LOAN_INFO
--==============================================================
create table LOAN_INFO
(
   BUSI_TYPE            VARCHAR(10)            not null,
   REG_DATE             VARCHAR(8),
   REG_TIME             VARCHAR(14),
   ORG_ID               VARCHAR(12),
   LOAN_ID              VARCHAR(20)            not null,
   ACCT_NO              VARCHAR(32)            not null,
   ACCT_TYPE            VARCHAR(1),
   REF_NBR              VARCHAR(23),
   LOGICAL_CARD_NO      VARCHAR(19),
   CARD_NO              VARCHAR(19),
   REGISTER_DATE        VARCHAR(14),
   REQUEST_TIME         VARCHAR(14),
   LOAN_TYPE            VARCHAR(5),
   LOAN_STATUS          VARCHAR(1),
   LAST_LOAN_STATUS     VARCHAR(1),
   LOAN_INIT_TERM       INTEGER,
   CURR_TERM            INTEGER,
   REMAIN_TERM          INTEGER,
   LOAN_INIT_PRIN       DECIMAL(16,2),
   FIXED_PMT_PRIN       DECIMAL(16,2),
   FIRST_TERM_PRIN      DECIMAL(16,2),
   FINAL_TERM_PRIN      DECIMAL(16,2),
   LOAN_INIT_FEE1       DECIMAL(16,2),
   LOAN_FIXED_FEE1      DECIMAL(16,2),
   FIRST_TERM_FEE1      DECIMAL(16,2),
   FINAL_TERM_FEE1      DECIMAL(16,2),
   UNEARNED_PRIN        DECIMAL(16,2),
   UNEARNED_FEE1        DECIMAL(16,2),
   PAID_OUT_DATE        VARCHAR(14),
   TERMINATE_DATE       VARCHAR(14),
   TERM_REASON_CD       VARCHAR(1),
   PRIN_PAID            DECIMAL(16,2),
   INT_PAID             DECIMAL(16,2),
   FEE_PAID             DECIMAL(16,2),
   LOAN_CURR_BAL        DECIMAL(16,2),
   LOAN_BAL_XFROUT      DECIMAL(16,2),
   LOAN_BAL_XFRIN       DECIMAL(16,2),
   BAL_PRINCIPAL        DECIMAL(16,2),
   BAL_INTEREST         DECIMAL(16,2),
   BAL_PENALTY          DECIMAL(16,2),
   LOAN_PRIN_XFROUT     DECIMAL(16,2),
   LOAN_PRIN_XFRIN      DECIMAL(16,2),
   LOAN_FEE1_XFROUT     DECIMAL(16,2),
   LOAN_FEE1_XFRIN      DECIMAL(16,2),
   ORIG_TXN_AMT         DECIMAL(16,2),
   ORIG_TRANS_DATE      VARCHAR(14),
   ORIG_AUTH_CODE       VARCHAR(6),
   LOAN_CODE            VARCHAR(4),
   REGISTER_ID          VARCHAR(20),
   RESCH_INIT_PRIN      DECIMAL(16,2),
   RESCH_DATE           VARCHAR(14),
   BEF_RESCH_PRIN       DECIMAL(16,2),
   BEF_RESCH_TERM       INTEGER,
   BEF_RESCH_PRIN1      DECIMAL(16,2),
   BEF_RESCH_PRIN2      DECIMAL(16,2),
   BEF_RESCH_FEE1       DECIMAL(16,2),
   BEF_RESCH_FEE2       DECIMAL(16,2),
   BEF_RESCH_FEE3       DECIMAL(16,2),
   BEF_RESCH_FEE4       DECIMAL(16,2),
   BEF_RESCH_FEE5       DECIMAL(16,2),
   LOAN_FEE_METHOD      VARCHAR(1),
   INTEREST_RATE        DECIMAL(12,4),
   PENALTY_RATE         DECIMAL(12,4),
   COMPOUND_RATE        DECIMAL(12,4),
   FLOAT_RATE           DECIMAL(5,2),
   LOAN_RECEIPT_NBR     VARCHAR(20),
   LOAN_EXPIRE_DATE     VARCHAR(14),
   LOAN_CD              VARCHAR(2),
   PAYMENT_HIST         VARCHAR(24),
   CTD_PAYMENT_AMT      DECIMAL(16,2),
   PAST_RESCH_CNT       INTEGER,
   PAST_SHORTED_CNT     INTEGER,
   ADV_PMT_AMT          DECIMAL(16,2),
   LAST_ACTION_DATE     VARCHAR(14),
   LAST_ACTION_TYPE     VARCHAR(1),
   LAST_MOD_DATE        VARCHAR(14),
   ACTIVATE_DATE        VARCHAR(14),
   INTEREST_CAL_BASE    VARCHAR(14),
   FIRST_BILL_DATE      VARCHAR(14),
   AGE_CD               VARCHAR(1),
   RECALC_IND           VARCHAR(1),
   RECALC_DATE          VARCHAR(14),
   GRACE_DATE           VARCHAR(514),
   CANCEL_DATE          VARCHAR(14),
   CANCEL_REASON        VARCHAR(100),
   BANK_GROUP_ID        VARCHAR(5),
   DUE_DAYS             INTEGER,
   INIT_INTEREST        DECIMAL(16,2),
   BEF_INIT_INTEREST    DECIMAL(16,2),
   BANK_PROPORTION      DECIMAL(5,2),
   IS_CHECK_FLAG        VARCHAR(1),
   IS_FARM              VARCHAR(1),
   DGNS_LOAN_TYPE       VARCHAR(1),
   DGNS_LOAN_IN_TYPE    VARCHAR(1),
   EXTFLD1              VARCHAR(32),
   EXTFLD2              VARCHAR(64),
   constraint "P_Key_1" primary key (BUSI_TYPE, LOAN_ID)
);

comment on table LOAN_INFO is
'贷款借据表';

comment on column LOAN_INFO.BUSI_TYPE is
'业务类型
1:WLD 微粒贷
2:ALJB 阿里巴巴借呗
3:WCD 微车贷';

comment on column LOAN_INFO.REG_DATE is
'登记日期';

comment on column LOAN_INFO.REG_TIME is
'登记时间';

comment on column LOAN_INFO.ORG_ID is
'机构号';

comment on column LOAN_INFO.LOAN_ID is
'借据ID';

comment on column LOAN_INFO.ACCT_NO is
'贷款账号';

comment on column LOAN_INFO.ACCT_TYPE is
'A	人民币独立基本信用账户
B	美元独立基本信用账户
C	人民币共享基本信用账户
D	美元共享基本信用账户
E	人民币独立小额贷款账户
F	人民币活期借记账户
G	人民币智能存款户
Q	Q币账户
H	人民币独立贷款账户
I	人民币共享贷款账户-wx
J	人民币共享贷款账户- J';

comment on column LOAN_INFO.REF_NBR is
'交易参考号';

comment on column LOAN_INFO.LOGICAL_CARD_NO is
'默认逻辑卡号';

comment on column LOAN_INFO.CARD_NO is
'卡号';

comment on column LOAN_INFO.REGISTER_DATE is
'贷款注册日期';

comment on column LOAN_INFO.REQUEST_TIME is
'请求日期时间';

comment on column LOAN_INFO.LOAN_TYPE is
'第三方贷款分类：
R	消费转分期
C	现金分期
B	账单分期
P	POS分期
M	大额分期（专项分期）
MCAT	随借随还
MCEP	等额本金
MCEI	等额本息
MCOT	一次性还本付息
WELO	微众一贷
DMCEP	微众二贷
MCEIS	微众等额本息S';

comment on column LOAN_INFO.LOAN_STATUS is
'贷款状态:
I	注册但未活动
A	活动状态(active)
R	分期展期
T	终止(terminate)
F	完成(finish)
S	缩期(systole)
C	撤销(cancel)';

comment on column LOAN_INFO.LAST_LOAN_STATUS is
'贷款上次状态:
I	注册但未活动
A	活动状态(active)
R	分期展期
T	终止(terminate)
F	完成(finish)
S	缩期(systole)
C	撤销(cancel)';

comment on column LOAN_INFO.LOAN_INIT_TERM is
'贷款总期数';

comment on column LOAN_INFO.CURR_TERM is
'当前期数';

comment on column LOAN_INFO.REMAIN_TERM is
'剩余期数';

comment on column LOAN_INFO.LOAN_INIT_PRIN is
'贷款总本金';

comment on column LOAN_INFO.FIXED_PMT_PRIN is
'贷款每期应还本金';

comment on column LOAN_INFO.FIRST_TERM_PRIN is
'贷款首期应还本金';

comment on column LOAN_INFO.FINAL_TERM_PRIN is
'贷款末期应还本金';

comment on column LOAN_INFO.LOAN_INIT_FEE1 is
'贷款总手续费';

comment on column LOAN_INFO.LOAN_FIXED_FEE1 is
'贷款每期手续费';

comment on column LOAN_INFO.FIRST_TERM_FEE1 is
'贷款首期手续费';

comment on column LOAN_INFO.FINAL_TERM_FEE1 is
'贷款末期手续费';

comment on column LOAN_INFO.UNEARNED_PRIN is
'贷款账单的本金';

comment on column LOAN_INFO.UNEARNED_FEE1 is
'贷款账单手续费';

comment on column LOAN_INFO.PAID_OUT_DATE is
'还清日期';

comment on column LOAN_INFO.TERMINATE_DATE is
'提前终止日期';

comment on column LOAN_INFO.TERM_REASON_CD is
'贷款终止原因代码';

comment on column LOAN_INFO.PRIN_PAID is
'已偿还本金';

comment on column LOAN_INFO.INT_PAID is
'已偿还利息';

comment on column LOAN_INFO.FEE_PAID is
'已偿还费用';

comment on column LOAN_INFO.LOAN_CURR_BAL is
'贷款当前总余额';

comment on column LOAN_INFO.LOAN_BAL_XFROUT is
'贷款未到期余额';

comment on column LOAN_INFO.LOAN_BAL_XFRIN is
'贷款已到期余额';

comment on column LOAN_INFO.BAL_PRINCIPAL is
'欠款总本金';

comment on column LOAN_INFO.BAL_INTEREST is
'欠款总利息';

comment on column LOAN_INFO.BAL_PENALTY is
'欠款总罚息';

comment on column LOAN_INFO.LOAN_PRIN_XFROUT is
'贷款未到期本金';

comment on column LOAN_INFO.LOAN_PRIN_XFRIN is
'贷款已到期本金';

comment on column LOAN_INFO.LOAN_FEE1_XFROUT is
'首个到期还款日期';

comment on column LOAN_INFO.LOAN_FEE1_XFRIN is
'贷款已到期手续费';

comment on column LOAN_INFO.ORIG_TXN_AMT is
'原始交易币种金额';

comment on column LOAN_INFO.ORIG_TRANS_DATE is
'原始交易日期';

comment on column LOAN_INFO.ORIG_AUTH_CODE is
'原始交易授权码';

comment on column LOAN_INFO.LOAN_CODE is
'贷款产品号';

comment on column LOAN_INFO.REGISTER_ID is
'贷款申请顺序号';

comment on column LOAN_INFO.RESCH_INIT_PRIN is
'展期本金金额';

comment on column LOAN_INFO.RESCH_DATE is
'展期生效日期';

comment on column LOAN_INFO.BEF_RESCH_PRIN is
'展期前每期应还本金';

comment on column LOAN_INFO.BEF_RESCH_TERM is
'展期前总期数';

comment on column LOAN_INFO.BEF_RESCH_PRIN1 is
'展期前贷款首期应还本金';

comment on column LOAN_INFO.BEF_RESCH_PRIN2 is
'展期前贷款末期应还本金';

comment on column LOAN_INFO.BEF_RESCH_FEE1 is
'展期前贷款总手续费';

comment on column LOAN_INFO.BEF_RESCH_FEE2 is
'展期前贷款每期手续费';

comment on column LOAN_INFO.BEF_RESCH_FEE3 is
'展期前贷款首期手续费';

comment on column LOAN_INFO.BEF_RESCH_FEE4 is
'展期前贷款末期手续费';

comment on column LOAN_INFO.BEF_RESCH_FEE5 is
'展期后首期手续费';

comment on column LOAN_INFO.LOAN_FEE_METHOD is
'贷款手续费收取方式';

comment on column LOAN_INFO.INTEREST_RATE is
'基础利率';

comment on column LOAN_INFO.PENALTY_RATE is
'罚息利率';

comment on column LOAN_INFO.COMPOUND_RATE is
'复利利率';

comment on column LOAN_INFO.FLOAT_RATE is
'浮动比例';

comment on column LOAN_INFO.LOAN_RECEIPT_NBR is
'借据号';

comment on column LOAN_INFO.LOAN_EXPIRE_DATE is
'贷款到期日期';

comment on column LOAN_INFO.LOAN_CD is
'贷款逾期最大期数';

comment on column LOAN_INFO.PAYMENT_HIST is
'24个月还款状态';

comment on column LOAN_INFO.CTD_PAYMENT_AMT is
'当期还款额';

comment on column LOAN_INFO.PAST_RESCH_CNT is
'已展期次数';

comment on column LOAN_INFO.PAST_SHORTED_CNT is
'已缩期次数';

comment on column LOAN_INFO.ADV_PMT_AMT is
'提前还款金额';

comment on column LOAN_INFO.LAST_ACTION_DATE is
'上次行动日期';

comment on column LOAN_INFO.LAST_ACTION_TYPE is
'上次行动类型';

comment on column LOAN_INFO.INTEREST_CAL_BASE is
'计息基数';

comment on column LOAN_INFO.FIRST_BILL_DATE is
'首个到期还款日';

comment on column LOAN_INFO.AGE_CD is
'账龄';

comment on column LOAN_INFO.RECALC_IND is
'利率重算标志';

comment on column LOAN_INFO.RECALC_DATE is
'利率重算日';

comment on column LOAN_INFO.GRACE_DATE is
'宽限日期';

comment on column LOAN_INFO.CANCEL_DATE is
'撤销日期';

comment on column LOAN_INFO.CANCEL_REASON is
'贷款撤销原因';

comment on column LOAN_INFO.BANK_GROUP_ID is
'银团编号';

comment on column LOAN_INFO.DUE_DAYS is
'当前逾期天数';

comment on column LOAN_INFO.INIT_INTEREST is
'贷款总利息';

comment on column LOAN_INFO.BEF_INIT_INTEREST is
'原贷款总利息';

comment on column LOAN_INFO.BANK_PROPORTION is
'银行出资比例';

comment on column LOAN_INFO.IS_CHECK_FLAG is
'参与对账标识';

comment on column LOAN_INFO.IS_FARM is
'是否农户标志，0-非农户，1-农户';

comment on column LOAN_INFO.DGNS_LOAN_TYPE is
'农商行七级分类
1：0天	正常一
2：0天	正常二，微粒贷联合贷款贷款分类所有正常都归到“正常二”当中，不存在“正常一”。
3：逾期1-30天	关注一
4：逾期31-90天	关注二
5：逾期91-120天	次级
6：逾期121-180天	可疑
7：181天以上	损失';

comment on column LOAN_INFO.DGNS_LOAN_IN_TYPE is
'农商行贷款内部风险分类
内部风险分类结果	划分标准
1:一类贷款	正常一类
2:二类贷款	正常二类
3:三类贷款	贷款本金或正常利息逾期30天（含）以内
4:四类贷款	贷款本金或正常利息逾期31天-90天（含）以内或表5:外业务垫款30天（含）以内
5:五类贷款	贷款本金或正常利息逾期91天-180天（含）以内或表外业务垫款31天-90天（含）
6:六类贷款	贷款本金或正常利息逾期181天-550天（含）以内或表外业务垫款91天-270天（含）
7:七类贷款	贷款本金或正常利息逾期551天（含）以上或表外业务垫款271天（含）以上';

comment on column LOAN_INFO.EXTFLD1 is
'备用字段1';

comment on column LOAN_INFO.EXTFLD2 is
'备用字段2';

--==============================================================
-- Table: LOAN_SUB_ACCT
--==============================================================
create table LOAN_SUB_ACCT
(
   BUSI_TYPE            VARCHAR(10)            not null,
   SEQNO                INTEGER                not null,
   DGNS_SUB_TYPE        VARCHAR(1),
   LOAN_BUSI_TYPE_NAME  VARCHAR(60),
   LOAN_BUSI_TYPE_DESC  VARCHAR(60),
   ORG_ID               VARCHAR(12),
   ACCT_SEQNO           INTEGER,
   ACCT_TYPE            VARCHAR(1),
   D_SUB_NO             VARCHAR(32),
   D_SUB_NAME           VARCHAR(60),
   D_ACCT_NO            VARCHAR(32),
   D_ACCT_NAME          VARCHAR(60),
   C_SUB_NO             VARCHAR(32),
   C_SUB_NAME           VARCHAR(60),
   C_ACCT_NO            VARCHAR(32),
   C_ACCT_NAME          VARCHAR(60),
   RED_FLAG             VARCHAR(1),
   BNP_GROUP            VARCHAR(2),
   REMARK_CODE          VARCHAR(8),
   REMARK_NAME          VARCHAR(60),
   DSF_TRAN_CODE        VARCHAR(8),
   DSF_TRAN_NAME        VARCHAR(60),
   DSF_C_SUB_NUM        INTEGER,
   DSF_D_SUB_NO1        VARCHAR(32),
   DSF_D_SUB_NAME1      VARCHAR(60),
   DSF_D_SUB_NO2        VARCHAR(32),
   DSF_D_SUB_NAME2      VARCHAR(60),
   DSF_D_SUB_NO3        VARCHAR(32),
   DSF_D_SUB_NAME3      VARCHAR(60),
   DSF_D_SUB_NO4        VARCHAR(32),
   DSF_D_SUB_NAME4      VARCHAR(60),
   DSF_D_SUB_NO5        VARCHAR(32),
   DSF_D_SUB_NAME5      VARCHAR(60),
   DSF_D_SUB_NO6        VARCHAR(32),
   DSF_D_SUB_NAME6      VARCHAR(60),
   DSF_C_SUB_NUM2       INTEGER,
   DSF_C_SUB_NO1        VARCHAR(32),
   DSF_C_SUB_NAME1      VARCHAR(60),
   DSF_C_SUB_NO2        VARCHAR(32),
   DSF_C_SUB_NAME2      VARCHAR(60),
   DSF_C_SUB_NO3        VARCHAR(32),
   DSF_C_SUB_NAME3      VARCHAR(60),
   DSF_C_SUB_NO4        VARCHAR(32),
   DSF_C_SUB_NAME4      VARCHAR(60),
   DSF_C_SUB_NO5        VARCHAR(32),
   DSF_C_SUB_NAME5      VARCHAR(60),
   DSF_C_SUB_NO6        VARCHAR(32),
   DSF_C_SUB_NAME6      VARCHAR(60),
   DSF_RED_FLAG         VARCHAR(1),
   VALID_FLAG           VARCHAR(1),
   EXTFLD1              VARCHAR(32),
   EXTFLD2              VARCHAR(64),
   constraint "P_Key_1" primary key (BUSI_TYPE, SEQNO)
);

comment on table LOAN_SUB_ACCT is
'会计入账科目映射';

comment on column LOAN_SUB_ACCT.BUSI_TYPE is
'业务类型
1:WLD 微粒贷
2:ALJB 阿里巴巴借呗
3:WCD 微车贷';

comment on column LOAN_SUB_ACCT.SEQNO is
'序号，唯一标识';

comment on column LOAN_SUB_ACCT.DGNS_SUB_TYPE is
'科目映射类型：
0-按照1对1映射入账；
1-第三方对农商行分录1对多，按农户入账；
2-第三方对农商行分录1对多，按非农户入账；
3-第三方对农商行分录多对1，按汇总入账；
4-第三方对农商行分录1对多，按逾期贷款入账；
5-第三方对农商行分录1对多，按已核销贷款入账；
9-计提贷款减值准备';

comment on column LOAN_SUB_ACCT.ORG_ID is
'农商行机构号';

comment on column LOAN_SUB_ACCT.ACCT_TYPE is
'1-记核心账
2-记表外账
3-记登记簿账';

comment on column LOAN_SUB_ACCT.D_SUB_NO is
'借方科目号';

comment on column LOAN_SUB_ACCT.D_SUB_NAME is
'借方科目名称';

comment on column LOAN_SUB_ACCT.D_ACCT_NO is
'借方账号';

comment on column LOAN_SUB_ACCT.D_ACCT_NAME is
'借方户名';

comment on column LOAN_SUB_ACCT.C_SUB_NO is
'贷方科目号';

comment on column LOAN_SUB_ACCT.C_SUB_NAME is
'贷方科目名称';

comment on column LOAN_SUB_ACCT.C_ACCT_NO is
'贷方账号';

comment on column LOAN_SUB_ACCT.C_ACCT_NAME is
'贷方户名';

comment on column LOAN_SUB_ACCT.RED_FLAG is
'红蓝字标识：
R-红字
B-蓝字';

comment on column LOAN_SUB_ACCT.BNP_GROUP is
'余额成分组：
LD- 贷款溢缴款			
LP- 贷款本金			
LT- 罚息			
LI- 贷款利息		';

comment on column LOAN_SUB_ACCT.DSF_C_SUB_NUM is
'第三方分录序号';

comment on column LOAN_SUB_ACCT.DSF_D_SUB_NO1 is
'第三方借方科目号';

comment on column LOAN_SUB_ACCT.DSF_D_SUB_NAME1 is
'第三方借方科目名称';

comment on column LOAN_SUB_ACCT.DSF_D_SUB_NO2 is
'第三方借方科目号';

comment on column LOAN_SUB_ACCT.DSF_D_SUB_NAME2 is
'第三方借方科目名称';

comment on column LOAN_SUB_ACCT.DSF_D_SUB_NO3 is
'第三方借方科目号';

comment on column LOAN_SUB_ACCT.DSF_D_SUB_NAME3 is
'第三方借方科目名称';

comment on column LOAN_SUB_ACCT.DSF_D_SUB_NO4 is
'第三方借方科目号';

comment on column LOAN_SUB_ACCT.DSF_D_SUB_NAME4 is
'第三方借方科目名称';

comment on column LOAN_SUB_ACCT.DSF_D_SUB_NO5 is
'第三方借方科目号';

comment on column LOAN_SUB_ACCT.DSF_D_SUB_NAME5 is
'第三方借方科目名称';

comment on column LOAN_SUB_ACCT.DSF_D_SUB_NO6 is
'第三方借方科目号';

comment on column LOAN_SUB_ACCT.DSF_D_SUB_NAME6 is
'第三方借方科目名称';

comment on column LOAN_SUB_ACCT.DSF_C_SUB_NUM2 is
'第三方分录序号';

comment on column LOAN_SUB_ACCT.DSF_C_SUB_NO1 is
'第三方贷方科目号';

comment on column LOAN_SUB_ACCT.DSF_C_SUB_NAME1 is
'第三方贷方科目名称';

comment on column LOAN_SUB_ACCT.DSF_C_SUB_NO2 is
'第三方贷方科目号';

comment on column LOAN_SUB_ACCT.DSF_C_SUB_NAME2 is
'第三方贷方科目名称';

comment on column LOAN_SUB_ACCT.DSF_C_SUB_NO3 is
'第三方贷方科目号';

comment on column LOAN_SUB_ACCT.DSF_C_SUB_NAME3 is
'第三方贷方科目名称';

comment on column LOAN_SUB_ACCT.DSF_C_SUB_NO4 is
'第三方贷方科目号';

comment on column LOAN_SUB_ACCT.DSF_C_SUB_NAME4 is
'第三方贷方科目名称';

comment on column LOAN_SUB_ACCT.DSF_C_SUB_NO5 is
'第三方贷方科目号';

comment on column LOAN_SUB_ACCT.DSF_C_SUB_NAME5 is
'第三方贷方科目名称';

comment on column LOAN_SUB_ACCT.DSF_C_SUB_NO6 is
'第三方贷方科目号';

comment on column LOAN_SUB_ACCT.DSF_C_SUB_NAME6 is
'第三方贷方科目名称';

comment on column LOAN_SUB_ACCT.DSF_RED_FLAG is
'红蓝字标识：
R-红字
B-蓝字';

comment on column LOAN_SUB_ACCT.VALID_FLAG is
'有效标识:0-无效，1-有效';

comment on column LOAN_SUB_ACCT.EXTFLD1 is
'备用字段1';

comment on column LOAN_SUB_ACCT.EXTFLD2 is
'备用字段2';

--==============================================================
-- Table: LOAN_SUB_ACCT_PARA
--==============================================================
create table LOAN_SUB_ACCT_PARA
(
   BUSI_TYPE            VARCHAR(10)            not null,
   SEQNO                INTEGER                not null,
   DGNS_SUB_TYPE        VARCHAR(1),
   BUSI_TYPE_NAME       VARCHAR(60),
   BUSI_TYPE_DESC       VARCHAR(60),
   ORG_ID               VARCHAR(12),
   ACCT_SEQNO           INTEGER,
   ACCT_TYPE            VARCHAR(1),
   DC_FLAG              VARCHAR(1),
   SUB_BELONG           VARCHAR(1),
   SUB_NO               VARCHAR(32),
   SUB_NAME             VARCHAR(60),
   ACCT_NO              VARCHAR(32),
   ACCT_NAME            VARCHAR(60),
   RED_FLAG             VARCHAR(1),
   BNP_GROUP            VARCHAR(2),
   REMARK_CODE          VARCHAR(8),
   REMARK_NAME          VARCHAR(60),
   DSF_TRAN_CODE        VARCHAR(8),
   DSF_TRAN_NAME        VARCHAR(60),
   VALID_FLAG           VARCHAR(1),
   EXTFLD1              VARCHAR(32),
   EXTFLD2              VARCHAR(64),
   constraint "P_Key_1" primary key (BUSI_TYPE, SEQNO)
);

comment on table LOAN_SUB_ACCT_PARA is
'会计入账科目映射参数';

comment on column LOAN_SUB_ACCT_PARA.BUSI_TYPE is
'业务类型
1:WLD 微粒贷
2:ALJB 阿里巴巴借呗
3:WCD 微车贷';

comment on column LOAN_SUB_ACCT_PARA.SEQNO is
'序号，唯一标识';

comment on column LOAN_SUB_ACCT_PARA.DGNS_SUB_TYPE is
'科目映射类型：
0-按照1对1映射入账；
1-第三方对农商行分录1对多，按农户入账；
2-第三方对农商行分录1对多，按非农户入账；
3-第三方对农商行分录多对1，按汇总入账；
4-第三方对农商行分录1对多，按逾期贷款入账；
5-第三方对农商行分录1对多，按已核销贷款入账；
9-计提贷款减值准备';

comment on column LOAN_SUB_ACCT_PARA.ORG_ID is
'农商行机构号';

comment on column LOAN_SUB_ACCT_PARA.ACCT_TYPE is
'1-记核心账
2-记表外账
3-记登记簿账';

comment on column LOAN_SUB_ACCT_PARA.DC_FLAG is
'D-借，C-贷';

comment on column LOAN_SUB_ACCT_PARA.SUB_BELONG is
'第三方科目归属:
1.农商行对应科目
2.业务类型对应科目（如WLD)
3.账务登记簿对应科目
4.农商行资金清算科目
5.业务类型对应资金清算科目（如WLD)';

comment on column LOAN_SUB_ACCT_PARA.SUB_NO is
'借方科目号';

comment on column LOAN_SUB_ACCT_PARA.SUB_NAME is
'借方科目名称';

comment on column LOAN_SUB_ACCT_PARA.ACCT_NO is
'借方账号';

comment on column LOAN_SUB_ACCT_PARA.ACCT_NAME is
'借方户名';

comment on column LOAN_SUB_ACCT_PARA.RED_FLAG is
'红蓝字标识：
R-红字
B-蓝字';

comment on column LOAN_SUB_ACCT_PARA.BNP_GROUP is
'余额成分组：
LD- 贷款溢缴款			
LP- 贷款本金			
LT- 罚息			
LI- 贷款利息		';

comment on column LOAN_SUB_ACCT_PARA.VALID_FLAG is
'有效标识:0-无效，1-有效';

comment on column LOAN_SUB_ACCT_PARA.EXTFLD1 is
'备用字段1';

comment on column LOAN_SUB_ACCT_PARA.EXTFLD2 is
'备用字段2';

--==============================================================
-- Table: LOAN_SUB_ACCT_REG
--==============================================================
create table LOAN_SUB_ACCT_REG
(
   BUSI_TYPE            VARCHAR(10)            not null,
   ACCT_DATE            VARCHAR(8)             not null,
   ACCT_SEQNO           VARCHAR(32)            not null,
   SEQNO                INTEGER                not null,
   REG_DATE             VARCHAR(8),
   REG_TIME             VARCHAR(14),
   OLD_ACCT_SEQNO       INTEGER,
   ACCT_NO              VARCHAR(32),
   ACCT_NAME            VARCHAR(60),
   ACCT_TYPE            VARCHAR(2),
   DC_FLAG              VARCHAR(1),
   AMT                  DECIMAL(16,2),
   REMARK_CODE          VARCHAR(40),
   SUB_NO               VARCHAR(32),
   SUB_NAME             VARCHAR(60),
   BUSI_TYPE_NAME       VARCHAR(60),
   BUSI_TYPE_DESC       VARCHAR(60),
   BNP_GROUP            VARCHAR(2),
   RED_FLAG             VARCHAR(1),
   CURR                 VARCHAR(3),
   TRAN_CODE            VARCHAR(8),
   TRANS_DESC           VARCHAR(60),
   ORG_ID               VARCHAR(12),
   AREA_CODE            VARCHAR(8),
   CHANNEL_CODE         VARCHAR(3),
   ZDSBBH               VARCHAR(8),
   PRODUCT_CODE         VARCHAR(16),
   BUSI_SEQNO           VARCHAR(32),
   BUSI_NO              VARCHAR(16),
   FEE                  DECIMAL(16,2),
   DELAY_AMT            DECIMAL(16,2),
   FQF_SEQNO            VARCHAR(22),
   FQF_TIME             VARCHAR(6),
   FQF_TRAN_CODE        VARCHAR(8),
   DSF_SEQNO            VARCHAR(32),
   DSF_ACCT_DATE        VARCHAR(14),
   DSF_TRAN_TYPE        VARCHAR(8),
   DSF_TRAN_CODE        VARCHAR(8),
   DSF_RESP_CODE        VARCHAR(8),
   DSF_RESP_INFO        VARCHAR(60),
   DSF_CNT              INTEGER,
   DSF_TRAN_STAT        VARCHAR(1),
   CORE_SEQNO           VARCHAR(32),
   CORE_DATE            VARCHAR(14),
   CORE_TRAN_CODE       VARCHAR(8),
   CORE_RESP_CODE       VARCHAR(8),
   CORE_RESP_INFO       VARCHAR(60),
   CORE_STAT            VARCHAR(1),
   RESP_CODE            VARCHAR(8),
   RESP_INFO            VARCHAR(60),
   ACCT_FLAG            VARCHAR(1),
   ACCT_STAT            VARCHAR(1),
   DSF_IS_CHECK         VARCHAR(1),
   IS_CHECK             VARCHAR(1),
   EXTFLD1              VARCHAR(32),
   EXTFLD2              VARCHAR(64),
   EXTFLD3              VARCHAR(40),
   EXTFLD4              VARCHAR(40),
   EXTFLD5              VARCHAR(40),
   EXTFLD6              VARCHAR(40),
   constraint "P_Key_1" primary key (BUSI_TYPE, ACCT_DATE, ACCT_SEQNO, SEQNO)
);

comment on table LOAN_SUB_ACCT_REG is
'贷款科目记账登记簿';

comment on column LOAN_SUB_ACCT_REG.BUSI_TYPE is
'业务类型
1:WLD 微粒贷
2:ALJB 阿里巴巴借呗
3:WCD 微车贷';

comment on column LOAN_SUB_ACCT_REG.ACCT_DATE is
'账务日期';

comment on column LOAN_SUB_ACCT_REG.ACCT_SEQNO is
'平台流水号';

comment on column LOAN_SUB_ACCT_REG.SEQNO is
'交易序号';

comment on column LOAN_SUB_ACCT_REG.REG_DATE is
'登记日期';

comment on column LOAN_SUB_ACCT_REG.REG_TIME is
'登记时间';

comment on column LOAN_SUB_ACCT_REG.OLD_ACCT_SEQNO is
'原平台流水号';

comment on column LOAN_SUB_ACCT_REG.ACCT_NO is
'账户';

comment on column LOAN_SUB_ACCT_REG.ACCT_NAME is
'账户名称';

comment on column LOAN_SUB_ACCT_REG.ACCT_TYPE is
'01 对公活期； 02 对私活期； 03 对公定期； 04 对私定期； 05 保证金； 06 贷款； 07 内部账； 08 表外账；09 登记簿账';

comment on column LOAN_SUB_ACCT_REG.DC_FLAG is
'D-借，C-贷';

comment on column LOAN_SUB_ACCT_REG.AMT is
'发生额';

comment on column LOAN_SUB_ACCT_REG.REMARK_CODE is
'交易摘要';

comment on column LOAN_SUB_ACCT_REG.SUB_NO is
'科目号';

comment on column LOAN_SUB_ACCT_REG.SUB_NAME is
'科目名称';

comment on column LOAN_SUB_ACCT_REG.BNP_GROUP is
'余额成分组：
LD- 贷款溢缴款			
LP- 贷款本金			
LT- 罚息			
LI- 贷款利息		';

comment on column LOAN_SUB_ACCT_REG.RED_FLAG is
'红蓝字标识：
R-红字
B-蓝字';

comment on column LOAN_SUB_ACCT_REG.CURR is
'交易币种';

comment on column LOAN_SUB_ACCT_REG.TRANS_DESC is
'交易描述';

comment on column LOAN_SUB_ACCT_REG.AREA_CODE is
'地区代码';

comment on column LOAN_SUB_ACCT_REG.CHANNEL_CODE is
'渠道标识';

comment on column LOAN_SUB_ACCT_REG.PRODUCT_CODE is
'产品代码';

comment on column LOAN_SUB_ACCT_REG.BUSI_NO is
'业务编号';

comment on column LOAN_SUB_ACCT_REG.FEE is
'手续费';

comment on column LOAN_SUB_ACCT_REG.DELAY_AMT is
'滞纳金';

comment on column LOAN_SUB_ACCT_REG.FQF_SEQNO is
'发起方流水号';

comment on column LOAN_SUB_ACCT_REG.FQF_TIME is
'发起方时间';

comment on column LOAN_SUB_ACCT_REG.FQF_TRAN_CODE is
'发起方交易代码';

comment on column LOAN_SUB_ACCT_REG.DSF_SEQNO is
'第三方流水号';

comment on column LOAN_SUB_ACCT_REG.DSF_ACCT_DATE is
'第三方日期';

comment on column LOAN_SUB_ACCT_REG.DSF_TRAN_TYPE is
'第三方交易类类型';

comment on column LOAN_SUB_ACCT_REG.DSF_RESP_CODE is
'第三方响应码';

comment on column LOAN_SUB_ACCT_REG.DSF_RESP_INFO is
'第三方响应信息';

comment on column LOAN_SUB_ACCT_REG.DSF_TRAN_STAT is
'第三方交易状态';

comment on column LOAN_SUB_ACCT_REG.CORE_SEQNO is
'主机流水号';

comment on column LOAN_SUB_ACCT_REG.CORE_TRAN_CODE is
'主机交易代码';

comment on column LOAN_SUB_ACCT_REG.CORE_RESP_CODE is
'主机响应码';

comment on column LOAN_SUB_ACCT_REG.CORE_RESP_INFO is
'主机响应信息';

comment on column LOAN_SUB_ACCT_REG.ACCT_FLAG is
'1-核心记账；
2-表外记账；
3-登记簿记账；
4-第三方记账；';

comment on column LOAN_SUB_ACCT_REG.ACCT_STAT is
'交易状态，1-成功，0-失败，9-初始，A-处理中';

comment on column LOAN_SUB_ACCT_REG.EXTFLD1 is
'备用字段1';

comment on column LOAN_SUB_ACCT_REG.EXTFLD2 is
'备用字段2';

--==============================================================
-- Table: LOAN_SUB_BAL
--==============================================================
create table LOAN_SUB_BAL
(
   BUSI_TYPE            VARCHAR(10)            not null,
   REG_DATE             VARCHAR(8),
   REG_TIME             VARCHAR(14),
   SEQNO                INTEGER                not null,
   SUB_BELONG           VARCHAR(1)             not null,
   ACCT_DATE            VARCHAR(8)             not null,
   SUB_NO               VARCHAR(32)            not null,
   SUB_NAME             VARCHAR(60),
   ACCT_NO              VARCHAR(32)            not null,
   ACCT_NAME            VARCHAR(60),
   D_BAL                DECIMAL(16,2),
   C_BAL                DECIMAL(16,2),
   D_CNT                INTEGER,
   D_AMT                DECIMAL(16,2),
   C_CNT                INTEGER,
   C_AMT                DECIMAL(16,2),
   EXTFLD1              VARCHAR(32),
   EXTFLD2              VARCHAR(64),
   constraint "P_Key_1" primary key (BUSI_TYPE, SEQNO, SUB_BELONG, ACCT_NO, ACCT_DATE)
);

comment on table LOAN_SUB_BAL is
'贷款业务涉及科目每日余额';

comment on column LOAN_SUB_BAL.BUSI_TYPE is
'业务类型
1:WLD 微粒贷
2:ALJB 阿里巴巴借呗
3:WCD 微车贷';

comment on column LOAN_SUB_BAL.REG_DATE is
'登记日期';

comment on column LOAN_SUB_BAL.REG_TIME is
'登记时间';

comment on column LOAN_SUB_BAL.SEQNO is
'序号';

comment on column LOAN_SUB_BAL.SUB_BELONG is
'第三方科目归属:
1.农商行对应科目
2.业务类型对应科目（如WLD)
3.账务登记簿对应科目';

comment on column LOAN_SUB_BAL.ACCT_DATE is
'账务日期';

comment on column LOAN_SUB_BAL.SUB_NO is
'科目号';

comment on column LOAN_SUB_BAL.SUB_NAME is
'科目名称';

comment on column LOAN_SUB_BAL.ACCT_NO is
'账户';

comment on column LOAN_SUB_BAL.ACCT_NAME is
'账户名称';

comment on column LOAN_SUB_BAL.C_BAL is
'余额';

comment on column LOAN_SUB_BAL.EXTFLD1 is
'备用字段1';

comment on column LOAN_SUB_BAL.EXTFLD2 is
'备用字段2';

--==============================================================
-- Table: LOAN_SUB_CHECK
--==============================================================
create table LOAN_SUB_CHECK
(
   BUSI_TYPE            VARCHAR(10)            not null,
   SEQNO                INTEGER                not null,
   SUB_BELONG           VARCHAR(1)             not null,
   LOAN_BUSI_NAME       VARCHAR(60),
   LOAN_BUSI_DESC       VARCHAR(60),
   ORG_ID               VARCHAR(12),
   CHECK_TYPE           VARCHAR(1),
   SUB_NUM              INTEGER,
   SUB_NO1              VARCHAR(32),
   SUB_NAME1            VARCHAR(60),
   ACCT_NO1             VARCHAR(32),
   ACCT_NAME1           VARCHAR(60),
   SUB_NO2              VARCHAR(32),
   SUB_NAME2            VARCHAR(60),
   ACCT_NO2             VARCHAR(32),
   ACCT_NAME2           VARCHAR(60),
   SUB_NO3              VARCHAR(32),
   SUB_NAME3            VARCHAR(60),
   ACCT_NO3             VARCHAR(32),
   ACCT_NAME3           VARCHAR(60),
   SUB_NO4              VARCHAR(32),
   SUB_NAME4            VARCHAR(60),
   ACCT_NO4             VARCHAR(32),
   ACCT_NAME4           VARCHAR(60),
   SUB_NO5              VARCHAR(32),
   SUB_NAME5            VARCHAR(60),
   ACCT_NO5             VARCHAR(32),
   ACCT_NAME5           VARCHAR(60),
   SUB_NO6              VARCHAR(32),
   SUB_NAME6            VARCHAR(60),
   ACCT_NO6             VARCHAR(32),
   ACCT_NAME6           VARCHAR(60),
   VALID_FLAG           VARCHAR(1),
   EXTFLD1              VARCHAR(32),
   EXTFLD2              VARCHAR(64),
   constraint "P_Key_1" primary key (BUSI_TYPE, SEQNO, SUB_BELONG)
);

comment on table LOAN_SUB_CHECK is
'农商行与第三方对账科目汇总';

comment on column LOAN_SUB_CHECK.BUSI_TYPE is
'业务类型
1:WLD 微粒贷
2:ALJB 阿里巴巴借呗
3:WCD 微车贷';

comment on column LOAN_SUB_CHECK.SEQNO is
'序号';

comment on column LOAN_SUB_CHECK.SUB_BELONG is
'第三方科目归属:
1.农商行对应科目
2.业务类型对应科目（如WLD)
3.账务登记簿对应科目';

comment on column LOAN_SUB_CHECK.ORG_ID is
'农商行机构号';

comment on column LOAN_SUB_CHECK.CHECK_TYPE is
'对账方式:
1-农商行科目余额与第三方科目余额对账
2-农商行登记簿余额与第三方科目余额对账
3-农商行科目余额+登记簿余额与第三方科目余额对账汇总对账
9-未知';

comment on column LOAN_SUB_CHECK.SUB_NUM is
'科目笔数';

comment on column LOAN_SUB_CHECK.SUB_NO1 is
'科目1';

comment on column LOAN_SUB_CHECK.SUB_NAME1 is
'科目名称1';

comment on column LOAN_SUB_CHECK.ACCT_NO1 is
'科目账号1';

comment on column LOAN_SUB_CHECK.ACCT_NAME1 is
'科目账号户名1';

comment on column LOAN_SUB_CHECK.SUB_NO2 is
'科目2';

comment on column LOAN_SUB_CHECK.SUB_NAME2 is
'科目名称2';

comment on column LOAN_SUB_CHECK.ACCT_NO2 is
'科目账号2';

comment on column LOAN_SUB_CHECK.ACCT_NAME2 is
'科目账号户名2';

comment on column LOAN_SUB_CHECK.SUB_NO3 is
'科目3';

comment on column LOAN_SUB_CHECK.SUB_NAME3 is
'科目名称3';

comment on column LOAN_SUB_CHECK.ACCT_NO3 is
'科目账号3';

comment on column LOAN_SUB_CHECK.ACCT_NAME3 is
'科目账号户名3';

comment on column LOAN_SUB_CHECK.SUB_NO4 is
'科目4';

comment on column LOAN_SUB_CHECK.SUB_NAME4 is
'科目名称4';

comment on column LOAN_SUB_CHECK.ACCT_NO4 is
'科目账号4';

comment on column LOAN_SUB_CHECK.ACCT_NAME4 is
'科目账号户名4';

comment on column LOAN_SUB_CHECK.SUB_NO5 is
'科目5';

comment on column LOAN_SUB_CHECK.SUB_NAME5 is
'科目名称5';

comment on column LOAN_SUB_CHECK.ACCT_NO5 is
'科目账号5';

comment on column LOAN_SUB_CHECK.ACCT_NAME5 is
'科目账号户名5';

comment on column LOAN_SUB_CHECK.SUB_NO6 is
'科目6';

comment on column LOAN_SUB_CHECK.SUB_NAME6 is
'科目名称6';

comment on column LOAN_SUB_CHECK.ACCT_NO6 is
'科目账号6';

comment on column LOAN_SUB_CHECK.ACCT_NAME6 is
'科目账号户名6';

comment on column LOAN_SUB_CHECK.VALID_FLAG is
'有效标识:0-无效，1-有效';

comment on column LOAN_SUB_CHECK.EXTFLD1 is
'备用字段1';

comment on column LOAN_SUB_CHECK.EXTFLD2 is
'备用字段2';

--==============================================================
-- Table: LOAN_TAX_REG
--==============================================================
create table LOAN_TAX_REG
(
   BUSI_TYPE            VARCHAR(10)            not null,
   REG_DATE             VARCHAR(8),
   REG_TIME             VARCHAR(14),
   LOAN_ID              VARCHAR(20)            not null,
   ORG_ID               VARCHAR(12),
   CARD_NO              VARCHAR(19),
   AMT                  DECIMAL(16,2),
   ACCT_DATE            VARCHAR(8),
   ACCT_SEQNO           VARCHAR(32),
   SEQNO                INTEGER,
   REF_NBR              VARCHAR(23),
   REMARK_CODE          VARCHAR(40),
   BANK_GROUP_ID        VARCHAR(5),
   BANK_NO              VARCHAR(10),
   PRODUCT_CD           VARCHAR(6),
   BIZ_TAX_INTERES      DECIMAL(16,2),
   VAT_INT_BAL          DECIMAL(16,2),
   NOREVOKE_VAT_INT_BAL DECIMAL(16,2),
   VAT_TAX              DECIMAL(16,2),
   LOAN_INT_TERM        INTEGER,
   LAST_MOD_TIME        VARCHAR(14),
   PAID_OUT_DATE        VARCHAR(14),
   AGE_NO               VARCHAR(1),
   BATCH_DATE           VARCHAR(14),
   STAT                 VARCHAR(1),
   TRANS_DESC           VARCHAR(60),
   IS_CHECK_FLAG        VARCHAR(1),
   EXTFLD1              VARCHAR(32),
   EXTFLD2              VARCHAR(64),
   constraint "P_Key_1" primary key (BUSI_TYPE, LOAN_ID)
);

comment on column LOAN_TAX_REG.BUSI_TYPE is
'业务类型
1:WLD 微粒贷
2:ALJB 阿里巴巴借呗
3:WCD 微车贷';

comment on column LOAN_TAX_REG.REG_DATE is
'登记日期';

comment on column LOAN_TAX_REG.REG_TIME is
'登记时间';

comment on column LOAN_TAX_REG.LOAN_ID is
'借据ID';

comment on column LOAN_TAX_REG.ORG_ID is
'机构号';

comment on column LOAN_TAX_REG.CARD_NO is
'卡号';

comment on column LOAN_TAX_REG.AMT is
'发生额';

comment on column LOAN_TAX_REG.ACCT_DATE is
'账务日期';

comment on column LOAN_TAX_REG.ACCT_SEQNO is
'平台流水号';

comment on column LOAN_TAX_REG.SEQNO is
'交易序号';

comment on column LOAN_TAX_REG.REF_NBR is
'交易参考号';

comment on column LOAN_TAX_REG.REMARK_CODE is
'交易摘要';

comment on column LOAN_TAX_REG.BANK_GROUP_ID is
'银团编号';

comment on column LOAN_TAX_REG.BANK_NO is
'银团编号';

comment on column LOAN_TAX_REG.PRODUCT_CD is
'产品代码';

comment on column LOAN_TAX_REG.BIZ_TAX_INTERES is
'交易描述';

comment on column LOAN_TAX_REG.VAT_INT_BAL is
'手续费';

comment on column LOAN_TAX_REG.NOREVOKE_VAT_INT_BAL is
'手续费';

comment on column LOAN_TAX_REG.VAT_TAX is
'手续费';

comment on column LOAN_TAX_REG.LOAN_INT_TERM is
'手续费';

comment on column LOAN_TAX_REG.STAT is
'1-已报税；0-未报税';

comment on column LOAN_TAX_REG.EXTFLD1 is
'备用字段1';

comment on column LOAN_TAX_REG.EXTFLD2 is
'备用字段2';

--==============================================================
-- Table: LOAN_TYPE_PARA
--==============================================================
create table LOAN_TYPE_PARA
(
   BUSI_TYPE            VARCHAR(10)            not null,
   SEQNO                INTEGER                not null,
   LOAN_IN_TYPE_CODE    VARCHAR(1),
   LOAN_IN_TYPE_NAME    VARCHAR(20),
   LOAN_IN_TYPE_DESC    VARCHAR(200),
   PRINCIPAL_POINT      DECIMAL(14,4),
   INTEREST_POINT       DECIMAL(14,4),
   VALID_FLAG           VARCHAR(1),
   EXTFLD1              VARCHAR(32),
   EXTFLD2              VARCHAR(64),
   constraint "P_Key_1" primary key (BUSI_TYPE, SEQNO)
);

comment on table LOAN_TYPE_PARA is
'贷款类别参数,贷款计提拨备比例';

comment on column LOAN_TYPE_PARA.BUSI_TYPE is
'业务类型
1:WLD 微粒贷
2:ALJB 阿里巴巴借呗
3:WCD 微车贷';

comment on column LOAN_TYPE_PARA.SEQNO is
'序号';

comment on column LOAN_TYPE_PARA.LOAN_IN_TYPE_CODE is
'贷款内部风险分类代码:
1- 一类贷款
2- 二类贷款
3- 三类贷款
4- 四类贷款
5- 五类贷款
6- 六类贷款
7- 七类贷款';

comment on column LOAN_TYPE_PARA.LOAN_IN_TYPE_NAME is
'贷款内部风险分类名称';

comment on column LOAN_TYPE_PARA.LOAN_IN_TYPE_DESC is
'贷款内部风险分类描述';

comment on column LOAN_TYPE_PARA.PRINCIPAL_POINT is
'计提拨备比例（本金）';

comment on column LOAN_TYPE_PARA.INTEREST_POINT is
'计提拨备比例（利息）';

comment on column LOAN_TYPE_PARA.VALID_FLAG is
'有效标识:0-无效，1-有效';

comment on column LOAN_TYPE_PARA.EXTFLD1 is
'备用字段1';

comment on column LOAN_TYPE_PARA.EXTFLD2 is
'备用字段2';

--==============================================================
-- Table: LOAN_VMS_INFO
--==============================================================
create table LOAN_VMS_INFO
(
   BUSI_TYPE            VARCHAR(10)            not null,
   REG_DATE             VARCHAR(8),
   REG_TIME             VARCHAR(14),
   LOAN_ID              VARCHAR(20)            not null,
   ORG_ID               VARCHAR(12),
   CARD_NO              VARCHAR(19),
   REF_NBR              VARCHAR(23)            not null,
   BANK_GROUP_ID        VARCHAR(5),
   BANK_NO              VARCHAR(10),
   PRODUCT_CD           VARCHAR(6),
   BIZ_TAX_INTERES      DECIMAL(16,2),
   VAT_INT_BAL          DECIMAL(16,2),
   NOREVOKE_VAT_INT_BAL DECIMAL(16,2),
   VAT_TAX              DECIMAL(16,2),
   LOAN_INT_TERM        INTEGER,
   LAST_MODIFIED_TIME   VARCHAR(14),
   PAID_OUT_DATE        VARCHAR(14),
   AGE_NO               VARCHAR(1),
   BATCH_DATE           VARCHAR(10),
   IS_CHECK_FLAG        VARCHAR(14),
   EXTFLD1              VARCHAR(32),
   EXTFLD2              VARCHAR(64),
   constraint "P_Key_1" primary key (BUSI_TYPE, LOAN_ID, REF_NBR)
);

comment on table LOAN_VMS_INFO is
'借据纳税加工表';

comment on column LOAN_VMS_INFO.BUSI_TYPE is
'业务类型
1:WLD 微粒贷
2:ALJB 阿里巴巴借呗
3:WCD 微车贷';

comment on column LOAN_VMS_INFO.REG_DATE is
'登记日期';

comment on column LOAN_VMS_INFO.REG_TIME is
'登记时间';

comment on column LOAN_VMS_INFO.LOAN_ID is
'纳税借据ID';

comment on column LOAN_VMS_INFO.ORG_ID is
'机构号';

comment on column LOAN_VMS_INFO.CARD_NO is
'介质卡号';

comment on column LOAN_VMS_INFO.REF_NBR is
'交易参考号';

comment on column LOAN_VMS_INFO.BANK_GROUP_ID is
'银团编号';

comment on column LOAN_VMS_INFO.BANK_NO is
'银行编号';

comment on column LOAN_VMS_INFO.PRODUCT_CD is
'产品号';

comment on column LOAN_VMS_INFO.BIZ_TAX_INTERES is
'营业税下的应计和应收息';

comment on column LOAN_VMS_INFO.VAT_INT_BAL is
'90天内的应纳税息余额';

comment on column LOAN_VMS_INFO.NOREVOKE_VAT_INT_BAL is
'不冲抵算法下应纳税息（含90天内+90天外还款补记部分）';

comment on column LOAN_VMS_INFO.IS_CHECK_FLAG is
'参与对账标识：
1-参与对账；0-不参与对账';

comment on column LOAN_VMS_INFO.EXTFLD1 is
'备用字段1';

comment on column LOAN_VMS_INFO.EXTFLD2 is
'备用字段2';
