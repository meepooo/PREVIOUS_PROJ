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
'���֤ǰ��λ����';

comment on column ADDR_CODE_PARA.CODE is
'���֤ǰ��λ';

comment on column ADDR_CODE_PARA.IS_FARM is
'�Ƿ�ũ����־��0-��ũ����1-ũ����9-δ֪';

comment on column ADDR_CODE_PARA.VALID_FLAG is
'��Ч��ʶ:0-��Ч��1-��Ч';

comment on column ADDR_CODE_PARA.EXTFLD1 is
'�����ֶ�1';

comment on column ADDR_CODE_PARA.EXTFLD2 is
'�����ֶ�2';

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
'�����˻�������Ϣ��';

comment on column LOAN_ACCT_INFO.BUSI_TYPE is
'ҵ������
1:WLD ΢����
2:ALJB ����Ͱͽ���
3:WCD ΢����';

comment on column LOAN_ACCT_INFO.REG_DATE is
'�Ǽ�����';

comment on column LOAN_ACCT_INFO.REG_TIME is
'�Ǽ�ʱ��';

comment on column LOAN_ACCT_INFO.LOAN_ACCT_NO is
'�����˺�';

comment on column LOAN_ACCT_INFO.ACCT_TYPE is
'A	����Ҷ������������˻�
B	��Ԫ�������������˻�
C	����ҹ�����������˻�
D	��Ԫ������������˻�
E	����Ҷ���С������˻�
F	����һ��ڽ���˻�
G	��������ܴ�
Q	Q���˻�
H	����Ҷ��������˻�
I	����ҹ�������˻�-wx
J	����ҹ�������˻�- J';

comment on column LOAN_ACCT_INFO.LOAN_ACCT_NAME is
'�����˺Ż���';

comment on column LOAN_ACCT_INFO.LOAN_CUST_NO is
'�����˿ͻ���';

comment on column LOAN_ACCT_INFO.GENDER is
'�Ա�
1	����
2	Ů��
9	δ֪';

comment on column LOAN_ACCT_INFO.ACCT_OPEN_DATE is
'�������ڣ����������';

comment on column LOAN_ACCT_INFO.ACCT_CLOSE_DATE is
'�����˻���������';

comment on column LOAN_ACCT_INFO.DUE_DAYS is
'��������';

comment on column LOAN_ACCT_INFO.DGNS_LOAN_TYPE is
'ũ�����߼�����
1��0��	����һ
2��0��	��������΢�������ϴ��������������������鵽�������������У������ڡ�����һ����
3������1-30��	��עһ
4������31-90��	��ע��
5������91-120��	�μ�
6������121-180��	����
7��181������	��ʧ';

comment on column LOAN_ACCT_INFO.DGNS_LOAN_IN_TYPE is
'ũ���д����ڲ����շ���
�ڲ����շ�����	���ֱ�׼
1:һ�����	����һ��
2:�������	��������
3:�������	������������Ϣ����30�죨��������
4:�������	������������Ϣ����31��-90�죨�������ڻ��5:��ҵ����30�죨��������
5:�������	������������Ϣ����91��-180�죨�������ڻ����ҵ����31��-90�죨����
6:�������	������������Ϣ����181��-550�죨�������ڻ����ҵ����91��-270�죨����
7:�������	������������Ϣ����551�죨�������ϻ����ҵ����271�죨��������';

comment on column LOAN_ACCT_INFO.DSF_LOAN_TYPE is
'������������ࣺ
R	����ת����
C	�ֽ����
B	�˵�����
P	POS����
M	�����ڣ�ר����ڣ�
MCAT	����滹
MCEP	�ȶ��
MCEI	�ȶϢ
MCOT	һ���Ի�����Ϣ
WELO	΢��һ��
DMCEP	΢�ڶ���
MCEIS	΢�ڵȶϢS';

comment on column LOAN_ACCT_INFO.IS_FARM is
'�Ƿ�ũ����־��0-��ũ����1-ũ��';

comment on column LOAN_ACCT_INFO.CURR is
'����';

comment on column LOAN_ACCT_INFO.CREDIT_LIMIT is
'���Ŷ��';

comment on column LOAN_ACCT_INFO.PRINCIPAL_BAL is
'��������Գ��ʱ����Ľ��';

comment on column LOAN_ACCT_INFO.BEGIN_BAL is
'��һ���������';

comment on column LOAN_ACCT_INFO.PMT_DUE_DAY_BAL is
'���ڻ��������';

comment on column LOAN_ACCT_INFO.BILLING_CYCLE is
'������';

comment on column LOAN_ACCT_INFO.MOBILE_NO is
'�ƶ��绰';

comment on column LOAN_ACCT_INFO.LOAN_ACCT_STAT is
'�����˺�״̬��1-������ 2-���ڣ� 3-����';

comment on column LOAN_ACCT_INFO.AGE_CD is
'��Ƿ����';

comment on column LOAN_ACCT_INFO.UNMATCH_DB is
'δ���˽�ǽ��';

comment on column LOAN_ACCT_INFO.UNMATCH_CR is
'δ���˴��ǽ��';

comment on column LOAN_ACCT_INFO.DD_IND is
'Լ����������';

comment on column LOAN_ACCT_INFO.DD_BANK_NAME is
'Լ��������������';

comment on column LOAN_ACCT_INFO.DD_BANK_BRANCH is
'Լ��������к�';

comment on column LOAN_ACCT_INFO.DD_BANK_ACCT_NO is
'Լ������ۿ��˺�';

comment on column LOAN_ACCT_INFO.DD_BANK_ACCT_NAME is
'Լ������ۿ��˻�����';

comment on column LOAN_ACCT_INFO.LAST_DD_AMT is
'����Լ��������';

comment on column LOAN_ACCT_INFO.LAST_DD_DATE is
'����Լ����������';

comment on column LOAN_ACCT_INFO.LAST_PMT_AMT is
'�ϱʻ�����';

comment on column LOAN_ACCT_INFO.LAST_PMT_DATE is
'�ϸ���������';

comment on column LOAN_ACCT_INFO.LAST_STMT_DATE is
'�ϸ����ڻ�������';

comment on column LOAN_ACCT_INFO.LAST_PMT_DUE_DATE is
'�ϸ����ڻ�������';

comment on column LOAN_ACCT_INFO.LAST_AGING_DATE is
'�ϸ�����������������';

comment on column LOAN_ACCT_INFO.COLLECT_DATE is
'�������';

comment on column LOAN_ACCT_INFO.COLLECT_OUT_DATE is
'�����ն�������';

comment on column LOAN_ACCT_INFO.NEXT_STMT_DATE is
'�¸����ڻ�������';

comment on column LOAN_ACCT_INFO.PMT_DUE_DATE is
'���ڻ�������';

comment on column LOAN_ACCT_INFO.DD_DATE is
'Լ����������';

comment on column LOAN_ACCT_INFO.GRACE_DATE is
'��������';

comment on column LOAN_ACCT_INFO.CLOSED_DATE is
'������������';

comment on column LOAN_ACCT_INFO.FIRST_STMT_DATE is
'�׸����ڻ�������';

comment on column LOAN_ACCT_INFO.CANCEL_DATE is
'��������';

comment on column LOAN_ACCT_INFO.CHARGE_OFF_DATE is
'ת��������';

comment on column LOAN_ACCT_INFO.WAIVE_SVCFEE_IND is
'�Ƿ���������';

comment on column LOAN_ACCT_INFO.USER_DATE2 is
'�ϴε�������';

comment on column LOAN_ACCT_INFO.MTD_PAYMENT_AMT is
'���»�����';

comment on column LOAN_ACCT_INFO.MTD_PAYMENT_CNT is
'���»������';

comment on column LOAN_ACCT_INFO.YTD_PAYMENT_AMT is
'���껹����';

comment on column LOAN_ACCT_INFO.YTD_PAYMENT_CNT is
'���껹�����';

comment on column LOAN_ACCT_INFO.LTD_PAYMENT_AMT is
'��ʷ������';

comment on column LOAN_ACCT_INFO.LTD_PAYMENT_CNT is
'��ʷ�������';

comment on column LOAN_ACCT_INFO.LAST_MOD_DATETIME is
'�޸�����';

comment on column LOAN_ACCT_INFO.BANK_PROPORTION is
'���г��ʱ���';

comment on column LOAN_ACCT_INFO.EXTFLD1 is
'�����ֶ�1';

comment on column LOAN_ACCT_INFO.EXTFLD2 is
'�����ֶ�2';

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
'����-���˻���Ϣ��';

comment on column LOAN_CARD_INFO.BUSI_TYPE is
'ҵ������
1:WLD ΢����
2:ALJB ����Ͱͽ���
3:WCD ΢����';

comment on column LOAN_CARD_INFO.REG_DATE is
'�Ǽ�����';

comment on column LOAN_CARD_INFO.REG_TIME is
'�Ǽ�ʱ��';

comment on column LOAN_CARD_INFO.ACCT_NO is
'�����˺�';

comment on column LOAN_CARD_INFO.CUST_ID is
'�����˿ͻ���';

comment on column LOAN_CARD_INFO.EXTFLD1 is
'�����ֶ�1';

comment on column LOAN_CARD_INFO.EXTFLD2 is
'�����ֶ�2';

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
'������ˮ��';

comment on column LOAN_CHECK_DATA.BUSI_TYPE is
'ҵ������
1:WLD ΢����
2:ALJB ����Ͱͽ���
3:WCD ΢����';

comment on column LOAN_CHECK_DATA.REG_DATE is
'�Ǽ�����';

comment on column LOAN_CHECK_DATA.REG_TIME is
'�Ǽ�ʱ��';

comment on column LOAN_CHECK_DATA.SUB_BELONG is
'��������Ŀ����:
1.ũ���ж�Ӧ��Ŀ
2.ҵ�����Ͷ�Ӧ��Ŀ����WLD)
3.����Ǽǲ���Ӧ��Ŀ';

comment on column LOAN_CHECK_DATA.SEQNO is
'���';

comment on column LOAN_CHECK_DATA.ORG_ID is
'ũ���л�����';

comment on column LOAN_CHECK_DATA.CHECK_TYPE is
'���˷�ʽ:
1-ũ���п�Ŀ������������Ŀ������
2-ũ���еǼǲ�������������Ŀ������
3-ũ���п�Ŀ���+�Ǽǲ�������������Ŀ�����˻��ܶ���
9-δ֪';

comment on column LOAN_CHECK_DATA.SUB_NUM is
'��Ŀ����';

comment on column LOAN_CHECK_DATA.EXTFLD1 is
'�����ֶ�1';

comment on column LOAN_CHECK_DATA.EXTFLD2 is
'�����ֶ�2';

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
'���˽����';

comment on column LOAN_CHECK_RESULT.BUSI_TYPE is
'ҵ������
1:WLD ΢����
2:ALJB ����Ͱͽ���
3:WCD ΢����';

comment on column LOAN_CHECK_RESULT.SEQNO is
'���';

comment on column LOAN_CHECK_RESULT.ORG_ID is
'ũ���л�����';

comment on column LOAN_CHECK_RESULT.CHECK_TYPE is
'���˷�ʽ:
1-ũ���п�Ŀ������������Ŀ������
2-ũ���еǼǲ�������������Ŀ������
3-ũ���п�Ŀ���+�Ǽǲ�������������Ŀ�����˻��ܶ���
9-δ֪';

comment on column LOAN_CHECK_RESULT.CHECK_FLAG is
'����״̬��
��һλ�����������
1-����ƽ
2-΢������
3-ũ������
�ڶ�λ��������
1-����ƽ
2-΢������
3-ũ������';

comment on column LOAN_CHECK_RESULT.CHECK_FLAG_DESC is
'���˽������';

comment on column LOAN_CHECK_RESULT.EXTFLD1 is
'�����ֶ�1';

comment on column LOAN_CHECK_RESULT.EXTFLD2 is
'�����ֶ�2';

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
'�ͻ���Ϣ��';

comment on column LOAN_CUST_INFO.BUSI_TYPE is
'ҵ������
1:WLD ΢����
2:ALJB ����Ͱͽ���
3:WCD ΢����';

comment on column LOAN_CUST_INFO.REG_DATE is
'�Ǽ�����';

comment on column LOAN_CUST_INFO.REG_TIME is
'�Ǽ�ʱ��';

comment on column LOAN_CUST_INFO.ORG_ID is
'������';

comment on column LOAN_CUST_INFO.CUST_ID is
'�ͻ���ţ�Ψһ��ʶ';

comment on column LOAN_CUST_INFO.ID_NO is
'֤������';

comment on column LOAN_CUST_INFO.ID_TYPE is
'֤������';

comment on column LOAN_CUST_INFO."NAME" is
'�ͻ�����';

comment on column LOAN_CUST_INFO.GENDER is
'�Ա�
1	����
2	Ů��
9	δ֪';

comment on column LOAN_CUST_INFO.NATIONALITY is
'��������';

comment on column LOAN_CUST_INFO.PR_OF_COUNTRY is
'�Ƿ����þ�ס
Y	��
N	��';

comment on column LOAN_CUST_INFO.COUNTRY_CODE is
'���þ�ס�ع��Ҵ���';

comment on column LOAN_CUST_INFO.MOBILE_NO is
'�ƶ��绰';

comment on column LOAN_CUST_INFO.EMB_NAME is
'ƴ����';

comment on column LOAN_CUST_INFO.CUST_LIMIT_ID is
'�ͻ����ID';

comment on column LOAN_CUST_INFO.LAST_MOD_DATETIME is
'�޸�����';

comment on column LOAN_CUST_INFO.SURNAME is
'����';

comment on column LOAN_CUST_INFO.IS_FARM is
'�Ƿ�ũ����־��0-��ũ����1-ũ��';

comment on column LOAN_CUST_INFO.EXTFLD1 is
'�����ֶ�1';

comment on column LOAN_CUST_INFO.EXTFLD2 is
'�����ֶ�2';

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
'���ڴ������׼���Ǽǲ�';

comment on column LOAN_DUE_PRE_REG.BUSI_TYPE is
'ҵ������
1:WLD ΢����
2:ALJB ����Ͱͽ���
3:WCD ΢����';

comment on column LOAN_DUE_PRE_REG.REG_DATE is
'�Ǽ�����';

comment on column LOAN_DUE_PRE_REG.REG_TIME is
'�Ǽ�ʱ��';

comment on column LOAN_DUE_PRE_REG.LOAN_ID is
'���ID';

comment on column LOAN_DUE_PRE_REG.LOAN_ACCT_NO is
'�����˺�';

comment on column LOAN_DUE_PRE_REG.CARD_NO is
'���ʿ���';

comment on column LOAN_DUE_PRE_REG.REF_NBR is
'���ײο���';

comment on column LOAN_DUE_PRE_REG.LOGICAL_CARD_NO is
'Ĭ���߼�����';

comment on column LOAN_DUE_PRE_REG.DGNS_LOAN_IN_TYPE is
'ũ���д����ڲ����շ���
�ڲ����շ�����	���ֱ�׼
1:һ�����	����һ��
2:�������	��������
3:�������	������������Ϣ����30�죨��������
4:�������	������������Ϣ����31��-90�죨�������ڻ��5:��ҵ����30�죨��������
5:�������	������������Ϣ����91��-180�죨�������ڻ����ҵ����31��-90�죨����
6:�������	������������Ϣ����181��-550�죨�������ڻ����ҵ����91��-270�죨����
7:�������	������������Ϣ����551�죨�������ϻ����ҵ����271�죨��������';

comment on column LOAN_DUE_PRE_REG.ACCT_DATE is
'��������';

comment on column LOAN_DUE_PRE_REG.ACCT_SEQNO is
'ƽ̨��ˮ��';

comment on column LOAN_DUE_PRE_REG.SEQNO is
'�������';

comment on column LOAN_DUE_PRE_REG.LOAN_BAL is
'���ڻ��������';

comment on column LOAN_DUE_PRE_REG.AMT1 is
'���ڻ��������';

comment on column LOAN_DUE_PRE_REG.AMT2 is
'���ڻ��������';

comment on column LOAN_DUE_PRE_REG.STATE is
'1-�ɹ���2-ʧ�ܣ�9-��ʼ��A-������ᣬB-��Ϣ����';

comment on column LOAN_DUE_PRE_REG.EXTFLD1 is
'�����ֶ�1';

comment on column LOAN_DUE_PRE_REG.EXTFLD2 is
'�����ֶ�2';

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
'�����ݱ�';

comment on column LOAN_INFO.BUSI_TYPE is
'ҵ������
1:WLD ΢����
2:ALJB ����Ͱͽ���
3:WCD ΢����';

comment on column LOAN_INFO.REG_DATE is
'�Ǽ�����';

comment on column LOAN_INFO.REG_TIME is
'�Ǽ�ʱ��';

comment on column LOAN_INFO.ORG_ID is
'������';

comment on column LOAN_INFO.LOAN_ID is
'���ID';

comment on column LOAN_INFO.ACCT_NO is
'�����˺�';

comment on column LOAN_INFO.ACCT_TYPE is
'A	����Ҷ������������˻�
B	��Ԫ�������������˻�
C	����ҹ�����������˻�
D	��Ԫ������������˻�
E	����Ҷ���С������˻�
F	����һ��ڽ���˻�
G	��������ܴ�
Q	Q���˻�
H	����Ҷ��������˻�
I	����ҹ�������˻�-wx
J	����ҹ�������˻�- J';

comment on column LOAN_INFO.REF_NBR is
'���ײο���';

comment on column LOAN_INFO.LOGICAL_CARD_NO is
'Ĭ���߼�����';

comment on column LOAN_INFO.CARD_NO is
'����';

comment on column LOAN_INFO.REGISTER_DATE is
'����ע������';

comment on column LOAN_INFO.REQUEST_TIME is
'��������ʱ��';

comment on column LOAN_INFO.LOAN_TYPE is
'������������ࣺ
R	����ת����
C	�ֽ����
B	�˵�����
P	POS����
M	�����ڣ�ר����ڣ�
MCAT	����滹
MCEP	�ȶ��
MCEI	�ȶϢ
MCOT	һ���Ի�����Ϣ
WELO	΢��һ��
DMCEP	΢�ڶ���
MCEIS	΢�ڵȶϢS';

comment on column LOAN_INFO.LOAN_STATUS is
'����״̬:
I	ע�ᵫδ�
A	�״̬(active)
R	����չ��
T	��ֹ(terminate)
F	���(finish)
S	����(systole)
C	����(cancel)';

comment on column LOAN_INFO.LAST_LOAN_STATUS is
'�����ϴ�״̬:
I	ע�ᵫδ�
A	�״̬(active)
R	����չ��
T	��ֹ(terminate)
F	���(finish)
S	����(systole)
C	����(cancel)';

comment on column LOAN_INFO.LOAN_INIT_TERM is
'����������';

comment on column LOAN_INFO.CURR_TERM is
'��ǰ����';

comment on column LOAN_INFO.REMAIN_TERM is
'ʣ������';

comment on column LOAN_INFO.LOAN_INIT_PRIN is
'�����ܱ���';

comment on column LOAN_INFO.FIXED_PMT_PRIN is
'����ÿ��Ӧ������';

comment on column LOAN_INFO.FIRST_TERM_PRIN is
'��������Ӧ������';

comment on column LOAN_INFO.FINAL_TERM_PRIN is
'����ĩ��Ӧ������';

comment on column LOAN_INFO.LOAN_INIT_FEE1 is
'������������';

comment on column LOAN_INFO.LOAN_FIXED_FEE1 is
'����ÿ��������';

comment on column LOAN_INFO.FIRST_TERM_FEE1 is
'��������������';

comment on column LOAN_INFO.FINAL_TERM_FEE1 is
'����ĩ��������';

comment on column LOAN_INFO.UNEARNED_PRIN is
'�����˵��ı���';

comment on column LOAN_INFO.UNEARNED_FEE1 is
'�����˵�������';

comment on column LOAN_INFO.PAID_OUT_DATE is
'��������';

comment on column LOAN_INFO.TERMINATE_DATE is
'��ǰ��ֹ����';

comment on column LOAN_INFO.TERM_REASON_CD is
'������ֹԭ�����';

comment on column LOAN_INFO.PRIN_PAID is
'�ѳ�������';

comment on column LOAN_INFO.INT_PAID is
'�ѳ�����Ϣ';

comment on column LOAN_INFO.FEE_PAID is
'�ѳ�������';

comment on column LOAN_INFO.LOAN_CURR_BAL is
'���ǰ�����';

comment on column LOAN_INFO.LOAN_BAL_XFROUT is
'����δ�������';

comment on column LOAN_INFO.LOAN_BAL_XFRIN is
'�����ѵ������';

comment on column LOAN_INFO.BAL_PRINCIPAL is
'Ƿ���ܱ���';

comment on column LOAN_INFO.BAL_INTEREST is
'Ƿ������Ϣ';

comment on column LOAN_INFO.BAL_PENALTY is
'Ƿ���ܷ�Ϣ';

comment on column LOAN_INFO.LOAN_PRIN_XFROUT is
'����δ���ڱ���';

comment on column LOAN_INFO.LOAN_PRIN_XFRIN is
'�����ѵ��ڱ���';

comment on column LOAN_INFO.LOAN_FEE1_XFROUT is
'�׸����ڻ�������';

comment on column LOAN_INFO.LOAN_FEE1_XFRIN is
'�����ѵ���������';

comment on column LOAN_INFO.ORIG_TXN_AMT is
'ԭʼ���ױ��ֽ��';

comment on column LOAN_INFO.ORIG_TRANS_DATE is
'ԭʼ��������';

comment on column LOAN_INFO.ORIG_AUTH_CODE is
'ԭʼ������Ȩ��';

comment on column LOAN_INFO.LOAN_CODE is
'�����Ʒ��';

comment on column LOAN_INFO.REGISTER_ID is
'��������˳���';

comment on column LOAN_INFO.RESCH_INIT_PRIN is
'չ�ڱ�����';

comment on column LOAN_INFO.RESCH_DATE is
'չ����Ч����';

comment on column LOAN_INFO.BEF_RESCH_PRIN is
'չ��ǰÿ��Ӧ������';

comment on column LOAN_INFO.BEF_RESCH_TERM is
'չ��ǰ������';

comment on column LOAN_INFO.BEF_RESCH_PRIN1 is
'չ��ǰ��������Ӧ������';

comment on column LOAN_INFO.BEF_RESCH_PRIN2 is
'չ��ǰ����ĩ��Ӧ������';

comment on column LOAN_INFO.BEF_RESCH_FEE1 is
'չ��ǰ������������';

comment on column LOAN_INFO.BEF_RESCH_FEE2 is
'չ��ǰ����ÿ��������';

comment on column LOAN_INFO.BEF_RESCH_FEE3 is
'չ��ǰ��������������';

comment on column LOAN_INFO.BEF_RESCH_FEE4 is
'չ��ǰ����ĩ��������';

comment on column LOAN_INFO.BEF_RESCH_FEE5 is
'չ�ں�����������';

comment on column LOAN_INFO.LOAN_FEE_METHOD is
'������������ȡ��ʽ';

comment on column LOAN_INFO.INTEREST_RATE is
'��������';

comment on column LOAN_INFO.PENALTY_RATE is
'��Ϣ����';

comment on column LOAN_INFO.COMPOUND_RATE is
'��������';

comment on column LOAN_INFO.FLOAT_RATE is
'��������';

comment on column LOAN_INFO.LOAN_RECEIPT_NBR is
'��ݺ�';

comment on column LOAN_INFO.LOAN_EXPIRE_DATE is
'���������';

comment on column LOAN_INFO.LOAN_CD is
'���������������';

comment on column LOAN_INFO.PAYMENT_HIST is
'24���»���״̬';

comment on column LOAN_INFO.CTD_PAYMENT_AMT is
'���ڻ����';

comment on column LOAN_INFO.PAST_RESCH_CNT is
'��չ�ڴ���';

comment on column LOAN_INFO.PAST_SHORTED_CNT is
'�����ڴ���';

comment on column LOAN_INFO.ADV_PMT_AMT is
'��ǰ������';

comment on column LOAN_INFO.LAST_ACTION_DATE is
'�ϴ��ж�����';

comment on column LOAN_INFO.LAST_ACTION_TYPE is
'�ϴ��ж�����';

comment on column LOAN_INFO.INTEREST_CAL_BASE is
'��Ϣ����';

comment on column LOAN_INFO.FIRST_BILL_DATE is
'�׸����ڻ�����';

comment on column LOAN_INFO.AGE_CD is
'����';

comment on column LOAN_INFO.RECALC_IND is
'���������־';

comment on column LOAN_INFO.RECALC_DATE is
'����������';

comment on column LOAN_INFO.GRACE_DATE is
'��������';

comment on column LOAN_INFO.CANCEL_DATE is
'��������';

comment on column LOAN_INFO.CANCEL_REASON is
'�����ԭ��';

comment on column LOAN_INFO.BANK_GROUP_ID is
'���ű��';

comment on column LOAN_INFO.DUE_DAYS is
'��ǰ��������';

comment on column LOAN_INFO.INIT_INTEREST is
'��������Ϣ';

comment on column LOAN_INFO.BEF_INIT_INTEREST is
'ԭ��������Ϣ';

comment on column LOAN_INFO.BANK_PROPORTION is
'���г��ʱ���';

comment on column LOAN_INFO.IS_CHECK_FLAG is
'������˱�ʶ';

comment on column LOAN_INFO.IS_FARM is
'�Ƿ�ũ����־��0-��ũ����1-ũ��';

comment on column LOAN_INFO.DGNS_LOAN_TYPE is
'ũ�����߼�����
1��0��	����һ
2��0��	��������΢�������ϴ��������������������鵽�������������У������ڡ�����һ����
3������1-30��	��עһ
4������31-90��	��ע��
5������91-120��	�μ�
6������121-180��	����
7��181������	��ʧ';

comment on column LOAN_INFO.DGNS_LOAN_IN_TYPE is
'ũ���д����ڲ����շ���
�ڲ����շ�����	���ֱ�׼
1:һ�����	����һ��
2:�������	��������
3:�������	������������Ϣ����30�죨��������
4:�������	������������Ϣ����31��-90�죨�������ڻ��5:��ҵ����30�죨��������
5:�������	������������Ϣ����91��-180�죨�������ڻ����ҵ����31��-90�죨����
6:�������	������������Ϣ����181��-550�죨�������ڻ����ҵ����91��-270�죨����
7:�������	������������Ϣ����551�죨�������ϻ����ҵ����271�죨��������';

comment on column LOAN_INFO.EXTFLD1 is
'�����ֶ�1';

comment on column LOAN_INFO.EXTFLD2 is
'�����ֶ�2';

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
'������˿�Ŀӳ��';

comment on column LOAN_SUB_ACCT.BUSI_TYPE is
'ҵ������
1:WLD ΢����
2:ALJB ����Ͱͽ���
3:WCD ΢����';

comment on column LOAN_SUB_ACCT.SEQNO is
'��ţ�Ψһ��ʶ';

comment on column LOAN_SUB_ACCT.DGNS_SUB_TYPE is
'��Ŀӳ�����ͣ�
0-����1��1ӳ�����ˣ�
1-��������ũ���з�¼1�Զ࣬��ũ�����ˣ�
2-��������ũ���з�¼1�Զ࣬����ũ�����ˣ�
3-��������ũ���з�¼���1�����������ˣ�
4-��������ũ���з�¼1�Զ࣬�����ڴ������ˣ�
5-��������ũ���з�¼1�Զ࣬���Ѻ����������ˣ�
9-��������ֵ׼��';

comment on column LOAN_SUB_ACCT.ORG_ID is
'ũ���л�����';

comment on column LOAN_SUB_ACCT.ACCT_TYPE is
'1-�Ǻ�����
2-�Ǳ�����
3-�ǵǼǲ���';

comment on column LOAN_SUB_ACCT.D_SUB_NO is
'�跽��Ŀ��';

comment on column LOAN_SUB_ACCT.D_SUB_NAME is
'�跽��Ŀ����';

comment on column LOAN_SUB_ACCT.D_ACCT_NO is
'�跽�˺�';

comment on column LOAN_SUB_ACCT.D_ACCT_NAME is
'�跽����';

comment on column LOAN_SUB_ACCT.C_SUB_NO is
'������Ŀ��';

comment on column LOAN_SUB_ACCT.C_SUB_NAME is
'������Ŀ����';

comment on column LOAN_SUB_ACCT.C_ACCT_NO is
'�����˺�';

comment on column LOAN_SUB_ACCT.C_ACCT_NAME is
'��������';

comment on column LOAN_SUB_ACCT.RED_FLAG is
'�����ֱ�ʶ��
R-����
B-����';

comment on column LOAN_SUB_ACCT.BNP_GROUP is
'���ɷ��飺
LD- ������ɿ�			
LP- �����			
LT- ��Ϣ			
LI- ������Ϣ		';

comment on column LOAN_SUB_ACCT.DSF_C_SUB_NUM is
'��������¼���';

comment on column LOAN_SUB_ACCT.DSF_D_SUB_NO1 is
'�������跽��Ŀ��';

comment on column LOAN_SUB_ACCT.DSF_D_SUB_NAME1 is
'�������跽��Ŀ����';

comment on column LOAN_SUB_ACCT.DSF_D_SUB_NO2 is
'�������跽��Ŀ��';

comment on column LOAN_SUB_ACCT.DSF_D_SUB_NAME2 is
'�������跽��Ŀ����';

comment on column LOAN_SUB_ACCT.DSF_D_SUB_NO3 is
'�������跽��Ŀ��';

comment on column LOAN_SUB_ACCT.DSF_D_SUB_NAME3 is
'�������跽��Ŀ����';

comment on column LOAN_SUB_ACCT.DSF_D_SUB_NO4 is
'�������跽��Ŀ��';

comment on column LOAN_SUB_ACCT.DSF_D_SUB_NAME4 is
'�������跽��Ŀ����';

comment on column LOAN_SUB_ACCT.DSF_D_SUB_NO5 is
'�������跽��Ŀ��';

comment on column LOAN_SUB_ACCT.DSF_D_SUB_NAME5 is
'�������跽��Ŀ����';

comment on column LOAN_SUB_ACCT.DSF_D_SUB_NO6 is
'�������跽��Ŀ��';

comment on column LOAN_SUB_ACCT.DSF_D_SUB_NAME6 is
'�������跽��Ŀ����';

comment on column LOAN_SUB_ACCT.DSF_C_SUB_NUM2 is
'��������¼���';

comment on column LOAN_SUB_ACCT.DSF_C_SUB_NO1 is
'������������Ŀ��';

comment on column LOAN_SUB_ACCT.DSF_C_SUB_NAME1 is
'������������Ŀ����';

comment on column LOAN_SUB_ACCT.DSF_C_SUB_NO2 is
'������������Ŀ��';

comment on column LOAN_SUB_ACCT.DSF_C_SUB_NAME2 is
'������������Ŀ����';

comment on column LOAN_SUB_ACCT.DSF_C_SUB_NO3 is
'������������Ŀ��';

comment on column LOAN_SUB_ACCT.DSF_C_SUB_NAME3 is
'������������Ŀ����';

comment on column LOAN_SUB_ACCT.DSF_C_SUB_NO4 is
'������������Ŀ��';

comment on column LOAN_SUB_ACCT.DSF_C_SUB_NAME4 is
'������������Ŀ����';

comment on column LOAN_SUB_ACCT.DSF_C_SUB_NO5 is
'������������Ŀ��';

comment on column LOAN_SUB_ACCT.DSF_C_SUB_NAME5 is
'������������Ŀ����';

comment on column LOAN_SUB_ACCT.DSF_C_SUB_NO6 is
'������������Ŀ��';

comment on column LOAN_SUB_ACCT.DSF_C_SUB_NAME6 is
'������������Ŀ����';

comment on column LOAN_SUB_ACCT.DSF_RED_FLAG is
'�����ֱ�ʶ��
R-����
B-����';

comment on column LOAN_SUB_ACCT.VALID_FLAG is
'��Ч��ʶ:0-��Ч��1-��Ч';

comment on column LOAN_SUB_ACCT.EXTFLD1 is
'�����ֶ�1';

comment on column LOAN_SUB_ACCT.EXTFLD2 is
'�����ֶ�2';

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
'������˿�Ŀӳ�����';

comment on column LOAN_SUB_ACCT_PARA.BUSI_TYPE is
'ҵ������
1:WLD ΢����
2:ALJB ����Ͱͽ���
3:WCD ΢����';

comment on column LOAN_SUB_ACCT_PARA.SEQNO is
'��ţ�Ψһ��ʶ';

comment on column LOAN_SUB_ACCT_PARA.DGNS_SUB_TYPE is
'��Ŀӳ�����ͣ�
0-����1��1ӳ�����ˣ�
1-��������ũ���з�¼1�Զ࣬��ũ�����ˣ�
2-��������ũ���з�¼1�Զ࣬����ũ�����ˣ�
3-��������ũ���з�¼���1�����������ˣ�
4-��������ũ���з�¼1�Զ࣬�����ڴ������ˣ�
5-��������ũ���з�¼1�Զ࣬���Ѻ����������ˣ�
9-��������ֵ׼��';

comment on column LOAN_SUB_ACCT_PARA.ORG_ID is
'ũ���л�����';

comment on column LOAN_SUB_ACCT_PARA.ACCT_TYPE is
'1-�Ǻ�����
2-�Ǳ�����
3-�ǵǼǲ���';

comment on column LOAN_SUB_ACCT_PARA.DC_FLAG is
'D-�裬C-��';

comment on column LOAN_SUB_ACCT_PARA.SUB_BELONG is
'��������Ŀ����:
1.ũ���ж�Ӧ��Ŀ
2.ҵ�����Ͷ�Ӧ��Ŀ����WLD)
3.����Ǽǲ���Ӧ��Ŀ
4.ũ�����ʽ������Ŀ
5.ҵ�����Ͷ�Ӧ�ʽ������Ŀ����WLD)';

comment on column LOAN_SUB_ACCT_PARA.SUB_NO is
'�跽��Ŀ��';

comment on column LOAN_SUB_ACCT_PARA.SUB_NAME is
'�跽��Ŀ����';

comment on column LOAN_SUB_ACCT_PARA.ACCT_NO is
'�跽�˺�';

comment on column LOAN_SUB_ACCT_PARA.ACCT_NAME is
'�跽����';

comment on column LOAN_SUB_ACCT_PARA.RED_FLAG is
'�����ֱ�ʶ��
R-����
B-����';

comment on column LOAN_SUB_ACCT_PARA.BNP_GROUP is
'���ɷ��飺
LD- ������ɿ�			
LP- �����			
LT- ��Ϣ			
LI- ������Ϣ		';

comment on column LOAN_SUB_ACCT_PARA.VALID_FLAG is
'��Ч��ʶ:0-��Ч��1-��Ч';

comment on column LOAN_SUB_ACCT_PARA.EXTFLD1 is
'�����ֶ�1';

comment on column LOAN_SUB_ACCT_PARA.EXTFLD2 is
'�����ֶ�2';

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
'�����Ŀ���˵Ǽǲ�';

comment on column LOAN_SUB_ACCT_REG.BUSI_TYPE is
'ҵ������
1:WLD ΢����
2:ALJB ����Ͱͽ���
3:WCD ΢����';

comment on column LOAN_SUB_ACCT_REG.ACCT_DATE is
'��������';

comment on column LOAN_SUB_ACCT_REG.ACCT_SEQNO is
'ƽ̨��ˮ��';

comment on column LOAN_SUB_ACCT_REG.SEQNO is
'�������';

comment on column LOAN_SUB_ACCT_REG.REG_DATE is
'�Ǽ�����';

comment on column LOAN_SUB_ACCT_REG.REG_TIME is
'�Ǽ�ʱ��';

comment on column LOAN_SUB_ACCT_REG.OLD_ACCT_SEQNO is
'ԭƽ̨��ˮ��';

comment on column LOAN_SUB_ACCT_REG.ACCT_NO is
'�˻�';

comment on column LOAN_SUB_ACCT_REG.ACCT_NAME is
'�˻�����';

comment on column LOAN_SUB_ACCT_REG.ACCT_TYPE is
'01 �Թ����ڣ� 02 ��˽���ڣ� 03 �Թ����ڣ� 04 ��˽���ڣ� 05 ��֤�� 06 ��� 07 �ڲ��ˣ� 08 �����ˣ�09 �Ǽǲ���';

comment on column LOAN_SUB_ACCT_REG.DC_FLAG is
'D-�裬C-��';

comment on column LOAN_SUB_ACCT_REG.AMT is
'������';

comment on column LOAN_SUB_ACCT_REG.REMARK_CODE is
'����ժҪ';

comment on column LOAN_SUB_ACCT_REG.SUB_NO is
'��Ŀ��';

comment on column LOAN_SUB_ACCT_REG.SUB_NAME is
'��Ŀ����';

comment on column LOAN_SUB_ACCT_REG.BNP_GROUP is
'���ɷ��飺
LD- ������ɿ�			
LP- �����			
LT- ��Ϣ			
LI- ������Ϣ		';

comment on column LOAN_SUB_ACCT_REG.RED_FLAG is
'�����ֱ�ʶ��
R-����
B-����';

comment on column LOAN_SUB_ACCT_REG.CURR is
'���ױ���';

comment on column LOAN_SUB_ACCT_REG.TRANS_DESC is
'��������';

comment on column LOAN_SUB_ACCT_REG.AREA_CODE is
'��������';

comment on column LOAN_SUB_ACCT_REG.CHANNEL_CODE is
'������ʶ';

comment on column LOAN_SUB_ACCT_REG.PRODUCT_CODE is
'��Ʒ����';

comment on column LOAN_SUB_ACCT_REG.BUSI_NO is
'ҵ����';

comment on column LOAN_SUB_ACCT_REG.FEE is
'������';

comment on column LOAN_SUB_ACCT_REG.DELAY_AMT is
'���ɽ�';

comment on column LOAN_SUB_ACCT_REG.FQF_SEQNO is
'������ˮ��';

comment on column LOAN_SUB_ACCT_REG.FQF_TIME is
'����ʱ��';

comment on column LOAN_SUB_ACCT_REG.FQF_TRAN_CODE is
'���𷽽��״���';

comment on column LOAN_SUB_ACCT_REG.DSF_SEQNO is
'��������ˮ��';

comment on column LOAN_SUB_ACCT_REG.DSF_ACCT_DATE is
'����������';

comment on column LOAN_SUB_ACCT_REG.DSF_TRAN_TYPE is
'����������������';

comment on column LOAN_SUB_ACCT_REG.DSF_RESP_CODE is
'��������Ӧ��';

comment on column LOAN_SUB_ACCT_REG.DSF_RESP_INFO is
'��������Ӧ��Ϣ';

comment on column LOAN_SUB_ACCT_REG.DSF_TRAN_STAT is
'����������״̬';

comment on column LOAN_SUB_ACCT_REG.CORE_SEQNO is
'������ˮ��';

comment on column LOAN_SUB_ACCT_REG.CORE_TRAN_CODE is
'�������״���';

comment on column LOAN_SUB_ACCT_REG.CORE_RESP_CODE is
'������Ӧ��';

comment on column LOAN_SUB_ACCT_REG.CORE_RESP_INFO is
'������Ӧ��Ϣ';

comment on column LOAN_SUB_ACCT_REG.ACCT_FLAG is
'1-���ļ��ˣ�
2-������ˣ�
3-�Ǽǲ����ˣ�
4-���������ˣ�';

comment on column LOAN_SUB_ACCT_REG.ACCT_STAT is
'����״̬��1-�ɹ���0-ʧ�ܣ�9-��ʼ��A-������';

comment on column LOAN_SUB_ACCT_REG.EXTFLD1 is
'�����ֶ�1';

comment on column LOAN_SUB_ACCT_REG.EXTFLD2 is
'�����ֶ�2';

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
'����ҵ���漰��Ŀÿ�����';

comment on column LOAN_SUB_BAL.BUSI_TYPE is
'ҵ������
1:WLD ΢����
2:ALJB ����Ͱͽ���
3:WCD ΢����';

comment on column LOAN_SUB_BAL.REG_DATE is
'�Ǽ�����';

comment on column LOAN_SUB_BAL.REG_TIME is
'�Ǽ�ʱ��';

comment on column LOAN_SUB_BAL.SEQNO is
'���';

comment on column LOAN_SUB_BAL.SUB_BELONG is
'��������Ŀ����:
1.ũ���ж�Ӧ��Ŀ
2.ҵ�����Ͷ�Ӧ��Ŀ����WLD)
3.����Ǽǲ���Ӧ��Ŀ';

comment on column LOAN_SUB_BAL.ACCT_DATE is
'��������';

comment on column LOAN_SUB_BAL.SUB_NO is
'��Ŀ��';

comment on column LOAN_SUB_BAL.SUB_NAME is
'��Ŀ����';

comment on column LOAN_SUB_BAL.ACCT_NO is
'�˻�';

comment on column LOAN_SUB_BAL.ACCT_NAME is
'�˻�����';

comment on column LOAN_SUB_BAL.C_BAL is
'���';

comment on column LOAN_SUB_BAL.EXTFLD1 is
'�����ֶ�1';

comment on column LOAN_SUB_BAL.EXTFLD2 is
'�����ֶ�2';

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
'ũ��������������˿�Ŀ����';

comment on column LOAN_SUB_CHECK.BUSI_TYPE is
'ҵ������
1:WLD ΢����
2:ALJB ����Ͱͽ���
3:WCD ΢����';

comment on column LOAN_SUB_CHECK.SEQNO is
'���';

comment on column LOAN_SUB_CHECK.SUB_BELONG is
'��������Ŀ����:
1.ũ���ж�Ӧ��Ŀ
2.ҵ�����Ͷ�Ӧ��Ŀ����WLD)
3.����Ǽǲ���Ӧ��Ŀ';

comment on column LOAN_SUB_CHECK.ORG_ID is
'ũ���л�����';

comment on column LOAN_SUB_CHECK.CHECK_TYPE is
'���˷�ʽ:
1-ũ���п�Ŀ������������Ŀ������
2-ũ���еǼǲ�������������Ŀ������
3-ũ���п�Ŀ���+�Ǽǲ�������������Ŀ�����˻��ܶ���
9-δ֪';

comment on column LOAN_SUB_CHECK.SUB_NUM is
'��Ŀ����';

comment on column LOAN_SUB_CHECK.SUB_NO1 is
'��Ŀ1';

comment on column LOAN_SUB_CHECK.SUB_NAME1 is
'��Ŀ����1';

comment on column LOAN_SUB_CHECK.ACCT_NO1 is
'��Ŀ�˺�1';

comment on column LOAN_SUB_CHECK.ACCT_NAME1 is
'��Ŀ�˺Ż���1';

comment on column LOAN_SUB_CHECK.SUB_NO2 is
'��Ŀ2';

comment on column LOAN_SUB_CHECK.SUB_NAME2 is
'��Ŀ����2';

comment on column LOAN_SUB_CHECK.ACCT_NO2 is
'��Ŀ�˺�2';

comment on column LOAN_SUB_CHECK.ACCT_NAME2 is
'��Ŀ�˺Ż���2';

comment on column LOAN_SUB_CHECK.SUB_NO3 is
'��Ŀ3';

comment on column LOAN_SUB_CHECK.SUB_NAME3 is
'��Ŀ����3';

comment on column LOAN_SUB_CHECK.ACCT_NO3 is
'��Ŀ�˺�3';

comment on column LOAN_SUB_CHECK.ACCT_NAME3 is
'��Ŀ�˺Ż���3';

comment on column LOAN_SUB_CHECK.SUB_NO4 is
'��Ŀ4';

comment on column LOAN_SUB_CHECK.SUB_NAME4 is
'��Ŀ����4';

comment on column LOAN_SUB_CHECK.ACCT_NO4 is
'��Ŀ�˺�4';

comment on column LOAN_SUB_CHECK.ACCT_NAME4 is
'��Ŀ�˺Ż���4';

comment on column LOAN_SUB_CHECK.SUB_NO5 is
'��Ŀ5';

comment on column LOAN_SUB_CHECK.SUB_NAME5 is
'��Ŀ����5';

comment on column LOAN_SUB_CHECK.ACCT_NO5 is
'��Ŀ�˺�5';

comment on column LOAN_SUB_CHECK.ACCT_NAME5 is
'��Ŀ�˺Ż���5';

comment on column LOAN_SUB_CHECK.SUB_NO6 is
'��Ŀ6';

comment on column LOAN_SUB_CHECK.SUB_NAME6 is
'��Ŀ����6';

comment on column LOAN_SUB_CHECK.ACCT_NO6 is
'��Ŀ�˺�6';

comment on column LOAN_SUB_CHECK.ACCT_NAME6 is
'��Ŀ�˺Ż���6';

comment on column LOAN_SUB_CHECK.VALID_FLAG is
'��Ч��ʶ:0-��Ч��1-��Ч';

comment on column LOAN_SUB_CHECK.EXTFLD1 is
'�����ֶ�1';

comment on column LOAN_SUB_CHECK.EXTFLD2 is
'�����ֶ�2';

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
'ҵ������
1:WLD ΢����
2:ALJB ����Ͱͽ���
3:WCD ΢����';

comment on column LOAN_TAX_REG.REG_DATE is
'�Ǽ�����';

comment on column LOAN_TAX_REG.REG_TIME is
'�Ǽ�ʱ��';

comment on column LOAN_TAX_REG.LOAN_ID is
'���ID';

comment on column LOAN_TAX_REG.ORG_ID is
'������';

comment on column LOAN_TAX_REG.CARD_NO is
'����';

comment on column LOAN_TAX_REG.AMT is
'������';

comment on column LOAN_TAX_REG.ACCT_DATE is
'��������';

comment on column LOAN_TAX_REG.ACCT_SEQNO is
'ƽ̨��ˮ��';

comment on column LOAN_TAX_REG.SEQNO is
'�������';

comment on column LOAN_TAX_REG.REF_NBR is
'���ײο���';

comment on column LOAN_TAX_REG.REMARK_CODE is
'����ժҪ';

comment on column LOAN_TAX_REG.BANK_GROUP_ID is
'���ű��';

comment on column LOAN_TAX_REG.BANK_NO is
'���ű��';

comment on column LOAN_TAX_REG.PRODUCT_CD is
'��Ʒ����';

comment on column LOAN_TAX_REG.BIZ_TAX_INTERES is
'��������';

comment on column LOAN_TAX_REG.VAT_INT_BAL is
'������';

comment on column LOAN_TAX_REG.NOREVOKE_VAT_INT_BAL is
'������';

comment on column LOAN_TAX_REG.VAT_TAX is
'������';

comment on column LOAN_TAX_REG.LOAN_INT_TERM is
'������';

comment on column LOAN_TAX_REG.STAT is
'1-�ѱ�˰��0-δ��˰';

comment on column LOAN_TAX_REG.EXTFLD1 is
'�����ֶ�1';

comment on column LOAN_TAX_REG.EXTFLD2 is
'�����ֶ�2';

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
'����������,������Ღ������';

comment on column LOAN_TYPE_PARA.BUSI_TYPE is
'ҵ������
1:WLD ΢����
2:ALJB ����Ͱͽ���
3:WCD ΢����';

comment on column LOAN_TYPE_PARA.SEQNO is
'���';

comment on column LOAN_TYPE_PARA.LOAN_IN_TYPE_CODE is
'�����ڲ����շ������:
1- һ�����
2- �������
3- �������
4- �������
5- �������
6- �������
7- �������';

comment on column LOAN_TYPE_PARA.LOAN_IN_TYPE_NAME is
'�����ڲ����շ�������';

comment on column LOAN_TYPE_PARA.LOAN_IN_TYPE_DESC is
'�����ڲ����շ�������';

comment on column LOAN_TYPE_PARA.PRINCIPAL_POINT is
'���Ღ������������';

comment on column LOAN_TYPE_PARA.INTEREST_POINT is
'���Ღ����������Ϣ��';

comment on column LOAN_TYPE_PARA.VALID_FLAG is
'��Ч��ʶ:0-��Ч��1-��Ч';

comment on column LOAN_TYPE_PARA.EXTFLD1 is
'�����ֶ�1';

comment on column LOAN_TYPE_PARA.EXTFLD2 is
'�����ֶ�2';

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
'�����˰�ӹ���';

comment on column LOAN_VMS_INFO.BUSI_TYPE is
'ҵ������
1:WLD ΢����
2:ALJB ����Ͱͽ���
3:WCD ΢����';

comment on column LOAN_VMS_INFO.REG_DATE is
'�Ǽ�����';

comment on column LOAN_VMS_INFO.REG_TIME is
'�Ǽ�ʱ��';

comment on column LOAN_VMS_INFO.LOAN_ID is
'��˰���ID';

comment on column LOAN_VMS_INFO.ORG_ID is
'������';

comment on column LOAN_VMS_INFO.CARD_NO is
'���ʿ���';

comment on column LOAN_VMS_INFO.REF_NBR is
'���ײο���';

comment on column LOAN_VMS_INFO.BANK_GROUP_ID is
'���ű��';

comment on column LOAN_VMS_INFO.BANK_NO is
'���б��';

comment on column LOAN_VMS_INFO.PRODUCT_CD is
'��Ʒ��';

comment on column LOAN_VMS_INFO.BIZ_TAX_INTERES is
'Ӫҵ˰�µ�Ӧ�ƺ�Ӧ��Ϣ';

comment on column LOAN_VMS_INFO.VAT_INT_BAL is
'90���ڵ�Ӧ��˰Ϣ���';

comment on column LOAN_VMS_INFO.NOREVOKE_VAT_INT_BAL is
'������㷨��Ӧ��˰Ϣ����90����+90���⻹��ǲ��֣�';

comment on column LOAN_VMS_INFO.IS_CHECK_FLAG is
'������˱�ʶ��
1-������ˣ�0-���������';

comment on column LOAN_VMS_INFO.EXTFLD1 is
'�����ֶ�1';

comment on column LOAN_VMS_INFO.EXTFLD2 is
'�����ֶ�2';
