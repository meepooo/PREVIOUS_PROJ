drop table ICPS_JT_LOAN_TOTAL;

drop table ICPS_JT_CUS;

drop table ICPS_JT_CUSCREDIT;

drop table ICPS_JT_QUOTAADJUST;

drop table ICPS_JT_LOAN;

drop table ICPS_JT_PLAN;

drop table ICPS_JT_FLOW;

drop table ICPS_JT_FUND_DETAIL;


/*==============================================================*/
/* Table: ICPS_JT_LOAN_TOTAL                                    */
/*==============================================================*/
create table ICPS_JT_LOAN_TOTAL 
(
   busi_date            CHAR(8)              not null,
   encash_amt           DECIMAL(16,2),
   prin_to_ovd_prin_amt DECIMAL(16,2),
   non_prin_to_ovd_prin_amt DECIMAL(16,2),
   accrued_to_non_ovd_prin_amt DECIMAL(16,2),
   in_int_to_ovd_int_amt DECIMAL(16,2),
   out_int_to_ovd_int_amt DECIMAL(16,2),
   in_to_out_ovd_int_amt DECIMAL(16,2),
   in_to_out_pnlt_int_amt DECIMAL(16,2),
   in_refund_ovd_int_amt DECIMAL(16,2),
   paid_prin_amt        DECIMAL(16,2),
   paid_accrued_ovd_prin_amt DECIMAL(16,2),
   paid_non_accrued_ovd_prin_amt DECIMAL(16,2),
   paid_int_amt         DECIMAL(16,2),
   paid_in_ovd_int_amt  DECIMAL(16,2),
   paid_out_ovd_int_amt DECIMAL(16,2),
   paid_in_pnlt_int_amt DECIMAL(16,2),
   paid_out_pnlt_int_amt DECIMAL(16,2),
   ahead_prin_amt       DECIMAL(16,2),
   ahead_int_amt        DECIMAL(16,2),
   refund_prin_amt      DECIMAL(16,2),
   refund_ovd_prin_amt  DECIMAL(16,2),
   refund_in_pnlt_int   DECIMAL(16,2),
   encash_amt2          DECIMAL(16,2),
   prin_to_ovd_prin_amt2 DECIMAL(16,2),
   non_prin_to_ovd_prin_amt2 DECIMAL(16,2),
   accrued_to_non_ovd_prin_amt2 DECIMAL(16,2),
   in_int_to_ovd_int_amt2 DECIMAL(16,2),
   out_int_to_ovd_int_amt2 DECIMAL(16,2),
   in_to_out_ovd_int_amt2 DECIMAL(16,2),
   in_to_out_pnlt_int_amt2 DECIMAL(16,2),
   in_refund_ovd_int_amt2 DECIMAL(16,2),
   paid_prin_amt2       DECIMAL(16,2),
   paid_accrued_ovd_prin_amt2 DECIMAL(16,2),
   paid_non_accrued_ovd_prin_amt2 DECIMAL(16,2),
   paid_int_amt2        DECIMAL(16,2),
   paid_in_ovd_int_amt2 DECIMAL(16,2),
   paid_out_ovd_int_amt2 DECIMAL(16,2),
   paid_in_pnlt_int_amt2 DECIMAL(16,2),
   paid_out_pnlt_int_amt2 DECIMAL(16,2),
   ahead_prin_amt2      DECIMAL(16,2),
   ahead_int_amt2       DECIMAL(16,2),
   refund_prin_amt2     DECIMAL(16,2),
   refund_ovd_prin_amt2 DECIMAL(16,2),
   refund_in_pnlt_int_amt2 DECIMAL(16,2),
   extend_param1        VARCHAR(100),
   extend_param2        VARCHAR(250),
   extend_param3        VARCHAR(40),
   constraint PK_ICPS_JT_LOAN_TOTAL primary key (busi_date)
);

comment on table ICPS_JT_LOAN_TOTAL is
'���ܼ��˱�';

comment on column ICPS_JT_LOAN_TOTAL.busi_date is
'ҵ������';

comment on column ICPS_JT_LOAN_TOTAL.encash_amt is
'���ڴ���ſ��ʽ�';

comment on column ICPS_JT_LOAN_TOTAL.prin_to_ovd_prin_amt is
'���ڴ�����������ת���ڱ���Ӧ�ƣ�';

comment on column ICPS_JT_LOAN_TOTAL.non_prin_to_ovd_prin_amt is
'���ڴ�����������ת���ڱ��𣨷�Ӧ�ƣ�';

comment on column ICPS_JT_LOAN_TOTAL.accrued_to_non_ovd_prin_amt is
'���ڴ������ڱ���Ӧ�ƣ�ת���ڱ��𣨷�Ӧ�ƣ�';

comment on column ICPS_JT_LOAN_TOTAL.in_int_to_ovd_int_amt is
'���ڴ���������Ϣת������Ϣ�����ڣ�';

comment on column ICPS_JT_LOAN_TOTAL.out_int_to_ovd_int_amt is
'���ڴ���������Ϣת������Ϣ�����⣩';

comment on column ICPS_JT_LOAN_TOTAL.in_to_out_ovd_int_amt is
'���ڴ���������Ϣ�����ڣ�ת������Ϣ�����⣩';

comment on column ICPS_JT_LOAN_TOTAL.in_to_out_pnlt_int_amt is
'���ڴ��Ϣ�����ڣ�ת��Ϣ�����⣩';

comment on column ICPS_JT_LOAN_TOTAL.in_refund_ovd_int_amt is
'�����˻����������������Ϣ�����ڣ�';

comment on column ICPS_JT_LOAN_TOTAL.paid_prin_amt is
'ʵ���������������';

comment on column ICPS_JT_LOAN_TOTAL.paid_accrued_ovd_prin_amt is
'ʵ���������ڴ����Ӧ�ƣ�';

comment on column ICPS_JT_LOAN_TOTAL.paid_non_accrued_ovd_prin_amt is
'ʵ���������ڴ���𣨷�Ӧ�ƣ�';

comment on column ICPS_JT_LOAN_TOTAL.paid_int_amt is
'ʵ����������������Ϣ';

comment on column ICPS_JT_LOAN_TOTAL.paid_in_ovd_int_amt is
'ʵ���������ڴ�����Ϣ�����ڣ�';

comment on column ICPS_JT_LOAN_TOTAL.paid_out_ovd_int_amt is
'ʵ���������ڴ�����Ϣ�����⣩';

comment on column ICPS_JT_LOAN_TOTAL.paid_in_pnlt_int_amt is
'ʵ�����ڴ��Ϣ�����ڣ�';

comment on column ICPS_JT_LOAN_TOTAL.paid_out_pnlt_int_amt is
'ʵ�����ڴ��Ϣ�����⣩';

comment on column ICPS_JT_LOAN_TOTAL.ahead_prin_amt is
'��ǰ�黹���ڴ�����������';

comment on column ICPS_JT_LOAN_TOTAL.ahead_int_amt is
'��ǰ�黹���ڴ���������Ϣ';

comment on column ICPS_JT_LOAN_TOTAL.refund_prin_amt is
'�˻����ڴ����';

comment on column ICPS_JT_LOAN_TOTAL.refund_ovd_prin_amt is
'�˻����ڴ������ڱ���Ӧ�ƣ�';

comment on column ICPS_JT_LOAN_TOTAL.refund_in_pnlt_int is
'�˻����ڴ��Ϣ�����ڣ�';

comment on column ICPS_JT_LOAN_TOTAL.encash_amt2 is
'�г��ڴ���ſ��ʽ�';

comment on column ICPS_JT_LOAN_TOTAL.prin_to_ovd_prin_amt2 is
'�г��ڴ�����������ת���ڱ���Ӧ�ƣ�';

comment on column ICPS_JT_LOAN_TOTAL.non_prin_to_ovd_prin_amt2 is
'�г��ڴ�����������ת���ڱ��𣨷�Ӧ�ƣ�';

comment on column ICPS_JT_LOAN_TOTAL.accrued_to_non_ovd_prin_amt2 is
'�г��ڴ������ڱ���Ӧ�ƣ�ת���ڱ��𣨷�Ӧ�ƣ�';

comment on column ICPS_JT_LOAN_TOTAL.in_int_to_ovd_int_amt2 is
'�г��ڴ���������Ϣת������Ϣ�����ڣ�';

comment on column ICPS_JT_LOAN_TOTAL.out_int_to_ovd_int_amt2 is
'�г��ڴ���������Ϣת������Ϣ�����⣩';

comment on column ICPS_JT_LOAN_TOTAL.in_to_out_ovd_int_amt2 is
'�г��ڴ���������Ϣ�����ڣ�ת������Ϣ�����⣩';

comment on column ICPS_JT_LOAN_TOTAL.in_to_out_pnlt_int_amt2 is
'�г��ڴ��Ϣ�����ڣ�ת��Ϣ�����⣩';

comment on column ICPS_JT_LOAN_TOTAL.in_refund_ovd_int_amt2 is
'�г����˻����������������Ϣ�����ڣ�';

comment on column ICPS_JT_LOAN_TOTAL.paid_prin_amt2 is
'ʵ���г������������';

comment on column ICPS_JT_LOAN_TOTAL.paid_accrued_ovd_prin_amt2 is
'ʵ���г������ڴ����Ӧ�ƣ�';

comment on column ICPS_JT_LOAN_TOTAL.paid_non_accrued_ovd_prin_amt2 is
'ʵ���г������ڴ���𣨷�Ӧ�ƣ�';

comment on column ICPS_JT_LOAN_TOTAL.paid_int_amt2 is
'ʵ���г�������������Ϣ';

comment on column ICPS_JT_LOAN_TOTAL.paid_in_ovd_int_amt2 is
'ʵ���г������ڴ�����Ϣ�����ڣ�';

comment on column ICPS_JT_LOAN_TOTAL.paid_out_ovd_int_amt2 is
'ʵ���г������ڴ�����Ϣ�����⣩';

comment on column ICPS_JT_LOAN_TOTAL.paid_in_pnlt_int_amt2 is
'ʵ���г��ڴ��Ϣ�����ڣ�';

comment on column ICPS_JT_LOAN_TOTAL.paid_out_pnlt_int_amt2 is
'ʵ���г��ڴ��Ϣ�����⣩';

comment on column ICPS_JT_LOAN_TOTAL.ahead_prin_amt2 is
'��ǰ�黹�г��ڴ�����������';

comment on column ICPS_JT_LOAN_TOTAL.ahead_int_amt2 is
'��ǰ�黹�г��ڴ���������Ϣ';

comment on column ICPS_JT_LOAN_TOTAL.refund_prin_amt2 is
'�˻��г��ڴ����';

comment on column ICPS_JT_LOAN_TOTAL.refund_ovd_prin_amt2 is
'�˻��г��ڴ������ڱ���Ӧ�ƣ�';

comment on column ICPS_JT_LOAN_TOTAL.refund_in_pnlt_int_amt2 is
'�˻��г��ڴ��Ϣ�����ڣ�';

comment on column ICPS_JT_LOAN_TOTAL.extend_param1 is
'��չ1';

comment on column ICPS_JT_LOAN_TOTAL.extend_param2 is
'��չ2';

comment on column ICPS_JT_LOAN_TOTAL.extend_param3 is
'��չ3';


/*==============================================================*/
/* Table: ICPS_JT_CUS                                           */
/*==============================================================*/
create table ICPS_JT_CUS 
(
   busi_date            VARCHAR(8)          not null,
   file_order           INTEGER              not null,
   customer_code        VARCHAR(60),
   customer_name        VARCHAR(250),
   gender               CHAR(1),
   brith_date           VARCHAR(8),
   resident_flag        CHAR(1),
   customer_status      CHAR(1),
   border_in_out_flag   CHAR(1),
   id_type              CHAR(5),
   id_num               VARCHAR(60),
   mobile_no            VARCHAR(60),
   addr                 VARCHAR(250),
   bank_name            VARCHAR(100),
   bank_acct            VARCHAR(60),
   is_check_flag        CHAR(1),
   extend_param1        VARCHAR(100),
   extend_param2        VARCHAR(250),
   extend_param3        VARCHAR(40),
   constraint PK_ICPS_JT_CUS primary key (busi_date, file_order)
);

comment on table ICPS_JT_CUS is
'�ͻ���Ϣ�ļ�';

comment on column ICPS_JT_CUS.busi_date is
'ҵ������YYYYMMDD';

comment on column ICPS_JT_CUS.customer_code is
'�ͻ����';

comment on column ICPS_JT_CUS.customer_name is
'�ͻ�����';

comment on column ICPS_JT_CUS.gender is
'�ͻ��Ա�';

comment on column ICPS_JT_CUS.brith_date is
'��������YYYYMMDD';

comment on column ICPS_JT_CUS.resident_flag is
'�����־';

comment on column ICPS_JT_CUS.customer_status is
'�ͻ�״̬';

comment on column ICPS_JT_CUS.border_in_out_flag is
'���ھ����־';

comment on column ICPS_JT_CUS.id_type is
'֤������';

comment on column ICPS_JT_CUS.id_num is
'֤������';

comment on column ICPS_JT_CUS.mobile_no is
'�ֻ�����';

comment on column ICPS_JT_CUS.addr is
'ͨѶ��ַ';

comment on column ICPS_JT_CUS.bank_name is
'�����п�����';

comment on column ICPS_JT_CUS.bank_acct is
'�����п�����';

comment on column ICPS_JT_CUS.is_check_flag is
'������˱�ʶ';

comment on column ICPS_JT_CUS.extend_param1 is
'��չ1';

comment on column ICPS_JT_CUS.extend_param2 is
'��չ2';

comment on column ICPS_JT_CUS.extend_param3 is
'��չ3';


/*==============================================================*/
/* Table: ICPS_JT_CUSCREDIT                                     */
/*==============================================================*/
create table ICPS_JT_CUSCREDIT 
(
   busi_date            VARCHAR(8)          not null,
   file_order           INTEGER              not null,
   customer_code        VARCHAR(60),
   product_code         VARCHAR(4),
   quota_code           VARCHAR(60),
   currency             VARCHAR(3),
   cycle_quota_flag     CHAR(1),
   start_date           VARCHAR(8),
   end_date             VARCHAR(8),
   quota                DECIMAL(16,2),
   limit                INTEGER,
   nouse_quota          DECIMAL(16,2),
   tmp_quota_flag       VARCHAR(4),
   auth_status          VARCHAR(3),
   is_check_flag        CHAR(1),
   extend_param1        VARCHAR(100),
   extend_param2        VARCHAR(250),
   extend_param3        VARCHAR(40),
   constraint PK_ICPS_JT_CUSCREDIT primary key (busi_date, file_order)
);

comment on table ICPS_JT_CUSCREDIT is
'���Ŷ����Ϣ�ļ�';

comment on column ICPS_JT_CUSCREDIT.busi_date is
'ҵ������YYYYMMDD';

comment on column ICPS_JT_CUSCREDIT.customer_code is
'�ͻ����';

comment on column ICPS_JT_CUSCREDIT.product_code is
'��Ʒ���';

comment on column ICPS_JT_CUSCREDIT.quota_code is
'��ȱ��';

comment on column ICPS_JT_CUSCREDIT.currency is
'����';

comment on column ICPS_JT_CUSCREDIT.cycle_quota_flag is
'ѭ����ȱ�־';

comment on column ICPS_JT_CUSCREDIT.start_date is
'������Ч��ʼ����';

comment on column ICPS_JT_CUSCREDIT.end_date is
'���ŵ�����';

comment on column ICPS_JT_CUSCREDIT.quota is
'���Ŷ��';

comment on column ICPS_JT_CUSCREDIT.limit is
'��������';

comment on column ICPS_JT_CUSCREDIT.nouse_quota is
'δ�������Ŷ��';

comment on column ICPS_JT_CUSCREDIT.tmp_quota_flag is
'�Ƿ���ʱ���';

comment on column ICPS_JT_CUSCREDIT.auth_status is
'����״̬';

comment on column ICPS_JT_CUSCREDIT.is_check_flag is
'������˱�ʶ';

comment on column ICPS_JT_CUSCREDIT.extend_param1 is
'��չ1';

comment on column ICPS_JT_CUSCREDIT.extend_param2 is
'��չ2';

comment on column ICPS_JT_CUSCREDIT.extend_param3 is
'��չ3';


/*==============================================================*/
/* Table: ICPS_JT_QUOTAADJUST                                   */
/*==============================================================*/
create table ICPS_JT_QUOTAADJUST 
(
   busi_date            VARCHAR(8)          not null,
   file_order           INTEGER              not null,
   customer_code        VARCHAR(60),
   product_code         VARCHAR(4),
   quota_code           VARCHAR(60),
   adjust_type          VARCHAR(2),
   adjust_mode          VARCHAR(2),
   adjust_quota         DECIMAL(26,8),
   before_adjust_quota  DECIMAL(26,8),
   after_adjust_quota   DECIMAL(26,8),
   adjust_cal_date      VARCHAR(8),
   adjust_effective_date VARCHAR(8),
   adjust_serial        VARCHAR(60),
   error_type           CHAR(1),
   is_check_flag        CHAR(1),
   extend_param1        VARCHAR(100),
   extend_param2        VARCHAR(250),
   extend_param3        VARCHAR(40),
   constraint PK_ICPS_JT_QUOTAADJUST primary key (busi_date, file_order)
);

comment on table ICPS_JT_QUOTAADJUST is
'������Ϣ�ļ�';

comment on column ICPS_JT_QUOTAADJUST.busi_date is
'ҵ������YYYYMMDD';

comment on column ICPS_JT_QUOTAADJUST.customer_code is
'�ͻ����';

comment on column ICPS_JT_QUOTAADJUST.product_code is
'��Ʒ���';

comment on column ICPS_JT_QUOTAADJUST.quota_code is
'��ȱ��';

comment on column ICPS_JT_QUOTAADJUST.adjust_type is
'����';

comment on column ICPS_JT_QUOTAADJUST.adjust_mode is
'ѭ����ȱ�־';

comment on column ICPS_JT_QUOTAADJUST.adjust_quota is
'������Ч��ʼ����';

comment on column ICPS_JT_QUOTAADJUST.before_adjust_quota is
'���ŵ�����';

comment on column ICPS_JT_QUOTAADJUST.after_adjust_quota is
'���Ŷ��';

comment on column ICPS_JT_QUOTAADJUST.adjust_cal_date is
'��������';

comment on column ICPS_JT_QUOTAADJUST.adjust_effective_date is
'δ�������Ŷ��';

comment on column ICPS_JT_QUOTAADJUST.adjust_serial is
'�Ƿ���ʱ���';

comment on column ICPS_JT_QUOTAADJUST.error_type is
'����״̬';

comment on column ICPS_JT_QUOTAADJUST.is_check_flag is
'������˱�ʶ';

comment on column ICPS_JT_QUOTAADJUST.extend_param1 is
'��չ1';

comment on column ICPS_JT_QUOTAADJUST.extend_param2 is
'��չ2';

comment on column ICPS_JT_QUOTAADJUST.extend_param3 is
'��չ3';


/*==============================================================*/
/* Table: ICPS_JT_LOAN                                          */
/*==============================================================*/
create table ICPS_JT_LOAN 
(
   busi_date            VARCHAR(8)          not null,
   file_order           INTEGER              not null,
   contract_no          VARCHAR(64),
   customer_code        VARCHAR(60),
   product_code         VARCHAR(4),
   quota_code           VARCHAR(60),
   loan_code            VARCHAR(60),
   currency             CHAR(3),
   loan_status          CHAR(1),
   encash_date          VARCHAR(8),
   encash_amt           DECIMAL(16,8),
   end_date             VARCHAR(8),
   use_area             VARCHAR(6),
   prin_repay_frequency VARCHAR(6),
   int_repay_frequency  VARCHAR(6),
   self_pay_amt         DECIMAL(16,2),
   entrusted_pay_amt    DECIMAL(16,2),
   ovd_flag             CHAR(1),
   ovd_days             INTEGER,
   ovd_non_days         INTEGER,
   prin_ovd_days        VARCHAR(8),
   int_ovd_days         VARCHAR(8),
   next_int_date        VARCHAR(8),
   rate_type            VARCHAR(6),
   loan_bal             DECIMAL(16,2),
   ovd_loan_bal         DECIMAL(16,2),
   ovd_int              DECIMAL(16,2),
   out_int_bal          DECIMAL(16,2),
   int_flag             CHAR(1),
   accrued_int          DECIMAL(16,2),
   int_amt              DECIMAL(16,2),
   pnlt_amt             DECIMAL(16,2),
   encash_acct          VARCHAR(64),
   repay_acct           VARCHAR(64),
   guarantee_type       CHAR(3),
   repay_mode           CHAR(1),
   loan_rate            DECIMAL(16,8),
   penalty_rate         DECIMAL(16,8),
   loan_rate_type       CHAR(1),
   penalty_rate_type    CHAR(1),
   is_check_flag        CHAR(1),
   extend_param1        VARCHAR(100),
   extend_param2        VARCHAR(250),
   extend_param3        VARCHAR(40),
   constraint PK_ICPS_JT_LOAN primary key (busi_date, file_order)
);

comment on table ICPS_JT_LOAN is
'��������Ϣ���ļ�';

comment on column ICPS_JT_LOAN.busi_date is
'ҵ������YYYYMMDD';

comment on column ICPS_JT_LOAN.contract_no is
'�ͻ�ǩ���ĺ�ͬ����';

comment on column ICPS_JT_LOAN.customer_code is
'�ͻ����';

comment on column ICPS_JT_LOAN.product_code is
'��Ʒ���';

comment on column ICPS_JT_LOAN.quota_code is
'��ȱ��';

comment on column ICPS_JT_LOAN.loan_code is
'������';

comment on column ICPS_JT_LOAN.currency is
'���� Ĭ��CNY';

comment on column ICPS_JT_LOAN.loan_status is
'����״̬ 1���� 2���� 3���� 9����';

comment on column ICPS_JT_LOAN.encash_date is
'�ſ�����';

comment on column ICPS_JT_LOAN.encash_amt is
'�ſ���';

comment on column ICPS_JT_LOAN.end_date is
'��������';

comment on column ICPS_JT_LOAN.use_area is
'�����ʽ�ʹ��λ�� I:���ڣ��й���½��O:���⣨���۰�̨��';

comment on column ICPS_JT_LOAN.prin_repay_frequency is
'���𻹿�Ƶ�� �������λ���ʱ��ļ�� 01:�� 02:�� 03:�� 04:�� 05:����
06:�� 07:һ����08:�����ڣ���������������ʱ�仹�99:����';

comment on column ICPS_JT_LOAN.int_repay_frequency is
'��Ϣ����Ƶ�� �������λ���ʱ��ļ�� 01:�� 02:�� 03:�� 04:�� 05:����
06:�� 07:һ����08:�����ڣ���������������ʱ�仹�99:����';

comment on column ICPS_JT_LOAN.self_pay_amt is
'����֧�����';

comment on column ICPS_JT_LOAN.entrusted_pay_amt is
'����֧�����';

comment on column ICPS_JT_LOAN.ovd_flag is
'���ڱ�־ 1:���� 0:����';

comment on column ICPS_JT_LOAN.ovd_days is
'��������';

comment on column ICPS_JT_LOAN.ovd_non_days is
'���ڿ�������';

comment on column ICPS_JT_LOAN.prin_ovd_days is
'������������';

comment on column ICPS_JT_LOAN.int_ovd_days is
'��Ϣ��������';

comment on column ICPS_JT_LOAN.next_int_date is
'��һ��Ϣ��';

comment on column ICPS_JT_LOAN.rate_type is
'�������� F:�̶����� L0:��������-���� L1:��������-���� L2:��������-����
L3:��������-���� L4:��������-������ L5:��������-���� L9:��������-����';

comment on column ICPS_JT_LOAN.loan_bal is
'�������';

comment on column ICPS_JT_LOAN.ovd_loan_bal is
'���ڴ������';

comment on column ICPS_JT_LOAN.ovd_int is
'������Ϣ';

comment on column ICPS_JT_LOAN.out_int_bal is
'����ǷϢ';

comment on column ICPS_JT_LOAN.int_flag is
'��Ϣ��־ Y:������Ϣ N:ֹͣ��Ϣ';

comment on column ICPS_JT_LOAN.accrued_int is
'Ӧ����Ϣ';

comment on column ICPS_JT_LOAN.int_amt is
'������Ϣ';

comment on column ICPS_JT_LOAN.pnlt_amt is
'���շ�Ϣ';

comment on column ICPS_JT_LOAN.encash_acct is
'���������˺�';

comment on column ICPS_JT_LOAN.repay_acct is
'�����˺�';

comment on column ICPS_JT_LOAN.guarantee_type is
'�������ʽ A��Ѻ����B��Ѻ����B01���ز���Ѻ����B99������Ѻ����C��֤����C01��������C99������֤����D����/�ⵣ������E��ϵ���Z ����';

comment on column ICPS_JT_LOAN.repay_mode is
'���ʽ 1-�ȶ��;2-���ڻ���';

comment on column ICPS_JT_LOAN.loan_rate is
'�������';

comment on column ICPS_JT_LOAN.penalty_rate is
'ΥԼ������';

comment on column ICPS_JT_LOAN.loan_rate_type is
'�����������';

comment on column ICPS_JT_LOAN.penalty_rate_type is
'ΥԼ����������';

comment on column ICPS_JT_LOAN.is_check_flag is
'������˱�ʶ';

comment on column ICPS_JT_LOAN.extend_param1 is
'��չ1';

comment on column ICPS_JT_LOAN.extend_param2 is
'��չ2';

comment on column ICPS_JT_LOAN.extend_param3 is
'��չ3';


/*==============================================================*/
/* Table: ICPS_JT_PLAN                                          */
/*==============================================================*/
create table ICPS_JT_PLAN 
(
   busi_date            VARCHAR(8)          not null,
   file_order           INTEGER              not null,
   contract_no          VARCHAR(64),
   product_code         VARCHAR(4),
   quota_code           VARCHAR(60),
   loan_code            VARCHAR(60),
   term_no              VARCHAR(20),
   repay_order          INTEGER,
   prin_end_date        VARCHAR(10),
   prin_amt             DECIMAL(16,2),
   int_end_date         VARCHAR(10),
   int_amt              DECIMAL(16,2),
   repay_terms          INTEGER,
   pnlt_amt             DECIMAL(16,2),
   is_check_flag        CHAR(1),
   extend_param1        VARCHAR(100),
   extend_param2        VARCHAR(250),
   extend_param3        VARCHAR(40),
   constraint PK_ICPS_JT_PLAN primary key (busi_date, file_order)
);

comment on table ICPS_JT_PLAN is
'�����ƻ���Ϣ�ļ�';

comment on column ICPS_JT_PLAN.busi_date is
'ҵ������YYYYMMDD';

comment on column ICPS_JT_PLAN.contract_no is
'�ͻ�ǩ���ĺ�ͬ����';

comment on column ICPS_JT_PLAN.product_code is
'��Ʒ���';

comment on column ICPS_JT_PLAN.quota_code is
'��ȱ��';

comment on column ICPS_JT_PLAN.loan_code is
'������';

comment on column ICPS_JT_PLAN.term_no is
'���ڵ���';

comment on column ICPS_JT_PLAN.repay_order is
'��������';

comment on column ICPS_JT_PLAN.prin_end_date is
'��������YYYYMMDD';

comment on column ICPS_JT_PLAN.prin_amt is
'���� ����Ӧ�ó����ı�������';

comment on column ICPS_JT_PLAN.int_end_date is
'��Ϣ������YYYYMMDD';

comment on column ICPS_JT_PLAN.int_amt is
'��Ϣ ���ڣ���ֹ��Ϣ�����գ�Ӧ����Ϣ������������Ϣ�ͷ�Ϣ';

comment on column ICPS_JT_PLAN.repay_terms is
'����������';

comment on column ICPS_JT_PLAN.pnlt_amt is
'��Ϣ';

comment on column ICPS_JT_PLAN.is_check_flag is
'������˱�ʶ';

comment on column ICPS_JT_PLAN.extend_param1 is
'��չ1';

comment on column ICPS_JT_PLAN.extend_param2 is
'��չ2';

comment on column ICPS_JT_PLAN.extend_param3 is
'��չ3';


/*==============================================================*/
/* Table: ICPS_JT_FLOW                                          */
/*==============================================================*/
create table ICPS_JT_FLOW 
(
   busi_date            VARCHAR(8)          not null,
   file_order           INTEGER              not null,
   contract_no          VARCHAR(64),
   product_code         VARCHAR(4),
   quota_code           VARCHAR(60),
   loan_code            VARCHAR(60),
   term_no              VARCHAR(20),
   repay_date           VARCHAR(10),
   repay_serial         VARCHAR(40),
   repay_mode           VARCHAR(6),
   curr_prin_amt        DECIMAL(16,2),
   prin_amt             DECIMAL(16,2),
   curr_int_amt         DECIMAL(16,2),
   int_amt              DECIMAL(16,2),
   curr_other_amt       DECIMAL(16,2),
   pnlt_amt             DECIMAL(16,2),
   repay_order          INTEGER,
   unclear_terms        INTEGER,
   repay_amt_type       VARCHAR(6),
   is_check_flag        CHAR(1),
   extend_param1        VARCHAR(100),
   extend_param2        VARCHAR(250),
   extend_param3        VARCHAR(40),
   constraint PK_ICPS_JT_FLOW primary key (busi_date, file_order)
);

comment on table ICPS_JT_FLOW is
'�������ϸ��Ϣ�ļ�';

comment on column ICPS_JT_FLOW.busi_date is
'ҵ������YYYYMMDD';

comment on column ICPS_JT_FLOW.contract_no is
'�ͻ�ǩ���ĺ�ͬ����';

comment on column ICPS_JT_FLOW.product_code is
'��Ʒ���';

comment on column ICPS_JT_FLOW.quota_code is
'��ȱ��';

comment on column ICPS_JT_FLOW.loan_code is
'������';

comment on column ICPS_JT_FLOW.term_no is
'���ڵ���';

comment on column ICPS_JT_FLOW.repay_date is
'��������yyyy-MM-dd';

comment on column ICPS_JT_FLOW.repay_serial is
'��ˮ��';

comment on column ICPS_JT_FLOW.repay_mode is
'���ʽ 1-�ȶ��;2-���ڻ���';

comment on column ICPS_JT_FLOW.curr_prin_amt is
'����Ӧ������';

comment on column ICPS_JT_FLOW.prin_amt is
'ʵ�ʳ���������';

comment on column ICPS_JT_FLOW.curr_int_amt is
'����Ӧ����Ϣ';

comment on column ICPS_JT_FLOW.int_amt is
'ʵ�ʳ�����Ϣ���';

comment on column ICPS_JT_FLOW.curr_other_amt is
'����Ӧ���������';

comment on column ICPS_JT_FLOW.pnlt_amt is
'��Ϣ���';

comment on column ICPS_JT_FLOW.repay_order is
'��������';

comment on column ICPS_JT_FLOW.unclear_terms is
'ʣ�໹������';

comment on column ICPS_JT_FLOW.repay_amt_type is
'�������� 01���ڻ��02��ǰ���03���ڻ��04�˻���05������06���㡢07�黹����';

comment on column ICPS_JT_FLOW.is_check_flag is
'������˱�ʶ';

comment on column ICPS_JT_FLOW.extend_param1 is
'��չ1';

comment on column ICPS_JT_FLOW.extend_param2 is
'��չ2';

comment on column ICPS_JT_FLOW.extend_param3 is
'��չ3';


/*==============================================================*/
/* Table: ICPS_JT_FUND_DETAIL                                   */
/*==============================================================*/
create table ICPS_JT_FUND_DETAIL 
(
   trans_date           VARCHAR(8)          not null,
   file_type            CHAR(8)              not null,
   file_order           INTEGER              not null,
   trans_time           CHAR(6),
   sys_date             CHAR(8),
   acct_direction       CHAR(1),
   trans_amt            DECIMAL(16,2),
   summary_code         VARCHAR(10),
   summary              VARCHAR(250),
   acct_bal             DECIMAL(16,2),
   currency             CHAR(3),
   peer_acct            VARCHAR(36),
   peer_acct_name       VARCHAR(60),
   remarks              VARCHAR(250),
   is_check_flag        CHAR(1),
   extend_param1        VARCHAR(100),
   extend_param2        VARCHAR(250),
   extend_param3        VARCHAR(40),
   constraint PK_ICPS_JT_FUND_DETAIL primary key (trans_date, file_type, file_order)
);

comment on table ICPS_JT_FUND_DETAIL is
'��ҵ�ʽ���ˮ�ļ�';

comment on column ICPS_JT_FUND_DETAIL.trans_date is
'ҵ������';

comment on column ICPS_JT_FUND_DETAIL.file_type is
'�ļ�����';

comment on column ICPS_JT_FUND_DETAIL.trans_time is
'����ʱ��';

comment on column ICPS_JT_FUND_DETAIL.sys_date is
'ϵͳ����';

comment on column ICPS_JT_FUND_DETAIL.acct_direction is
'��֧����';

comment on column ICPS_JT_FUND_DETAIL.trans_amt is
'���׽��';

comment on column ICPS_JT_FUND_DETAIL.summary_code is
'ժҪ����';

comment on column ICPS_JT_FUND_DETAIL.summary is
'����ժҪ';

comment on column ICPS_JT_FUND_DETAIL.acct_bal is
'�˻����';

comment on column ICPS_JT_FUND_DETAIL.currency is
'���Һ�';

comment on column ICPS_JT_FUND_DETAIL.peer_acct is
'�Է��˻�';

comment on column ICPS_JT_FUND_DETAIL.peer_acct_name is
'�Է��˻�����';

comment on column ICPS_JT_FUND_DETAIL.remarks is
'��ע';

comment on column ICPS_JT_FUND_DETAIL.is_check_flag is
'������˱�ʶ';

comment on column ICPS_JT_FUND_DETAIL.extend_param1 is
'��չ1';

comment on column ICPS_JT_FUND_DETAIL.extend_param2 is
'��չ2';

comment on column ICPS_JT_FUND_DETAIL.extend_param3 is
'��չ3';
