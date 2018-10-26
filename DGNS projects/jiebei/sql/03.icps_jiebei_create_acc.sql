drop table ICPS_JB_TOTAL;

drop table ICPS_JB_LENDING_DETAIL;

drop table ICPS_JB_LOAN_DETAIL;

drop table ICPS_JB_REPAY_PLAN;

drop table ICPS_JB_REPAY_LOAN_DETAIL;

drop table ICPS_JB_REPAY_INSTMNT_DETAIL;

drop table ICPS_JB_XPT_LOAN_DETAIL;

drop table ICPS_JB_XPT_INSTMNT_DETAIL;

drop table ICPS_JB_LOAN_INIT;

drop table ICPS_JB_INSTMNT_INIT;

drop table ICPS_JB_LOAN_CALC;

drop table ICPS_JB_ARG_STATUS_CHANGE;

drop table ICPS_JB_FUND_DETAIL;


/*==============================================================*/
/* Table: ICPS_JB_TOTAL                                         */
/*==============================================================*/
create table ICPS_JB_TOTAL 
(
   busi_date            CHAR(8)              not null,
   encash_amt           DECIMAL(16,2),
   withhold_amt         DECIMAL(16,2),
   refund_amt           DECIMAL(16,2),
   accrued_int_amt      DECIMAL(16,2),
   non_accrued_int_amt  DECIMAL(16,2),
   accrued_ovd_prin_pnlt_amt DECIMAL(16,2),
   non_accrued_ovd_prin_pnlt_amt DECIMAL(16,2),
   accrued_ovd_int_pnlt_amt DECIMAL(16,2),
   non_accrued_ovd_int_pnlt_amt DECIMAL(16,2),
   prin_to_ovd_prin_amt DECIMAL(16,2),
   int_to_ovd_int_amt   DECIMAL(16,2),
   accrued_to_non_prin_amt DECIMAL(16,2),
   accrued_to_non_ovd_prin_amt DECIMAL(16,2),
   in_to_out_int_amt    DECIMAL(16,2),
   in_to_out_ovd_int_amt DECIMAL(16,2),
   in_to_out_ovd_prin_pnlt_amt DECIMAL(16,2),
   in_to_out_ovd_int_pnlt_amt DECIMAL(16,2),
   non_to_accrued_prin_amt DECIMAL(16,2),
   non_to_accrued_ovd_prin_amt DECIMAL(16,2),
   out_to_in_int_amt    DECIMAL(16,2),
   out_to_in_ovd_int_amt DECIMAL(16,2),
   out_to_in_ovd_prin_pnlt_amt DECIMAL(16,2),
   out_to_in_ovd_int_pnlt_amt DECIMAL(16,2),
   paid_prin_amt        DECIMAL(16,2),
   paid_non_accrued_prin_amt DECIMAL(16,2),
   paid_accrued_ovd_prin_amt DECIMAL(16,2),
   paid_non_accrued_ovd_prin_amt DECIMAL(16,2),
   paid_int_amt         DECIMAL(16,2),
   paid_out_int_amt     DECIMAL(16,2),
   paid_in_ovd_int_amt  DECIMAL(16,2),
   paid_out_ovd_int_amt DECIMAL(16,2),
   paid_in_ovd_prin_pnlt_int_amt DECIMAL(16,2),
   paid_out_ovd_prin_pnlt_int_amt DECIMAL(16,2),
   paid_in_ovd_int_pnlt_int_amt DECIMAL(16,2),
   paid_out_ovd_int_pnlt_int_amt DECIMAL(16,2),
   xpt_in_int_amt       DECIMAL(16,2),
   xpt_out_int_amt      DECIMAL(16,2),
   xpt_in_ovd_int_amt   DECIMAL(16,2),
   xpt_out_ovd_int_amt  DECIMAL(16,2),
   xpt_in_ovd_prin_pnlt_int_amt DECIMAL(16,2),
   xpt_out_ovd_prin_pnlt_int_amt DECIMAL(16,2),
   xpt_in_ovd_int_pnlt_int_amt DECIMAL(16,2),
   xpt_out_ovd_int_pnlt_int_amt DECIMAL(16,2),
   extend_param1        VARCHAR(100),
   extend_param2        VARCHAR(250),
   extend_param3        VARCHAR(40),
   constraint PK_ICPS_JB_TOTAL primary key (busi_date)
);

comment on table ICPS_JB_TOTAL is
'���ܼ����ļ���';

comment on column ICPS_JB_TOTAL.busi_date is
'ҵ������';

comment on column ICPS_JB_TOTAL.encash_amt is
'�������Ž��';

comment on column ICPS_JB_TOTAL.withhold_amt is
'�������̱�������۽��';

comment on column ICPS_JB_TOTAL.refund_amt is
'�����˻����̱�������';

comment on column ICPS_JB_TOTAL.accrued_int_amt is
'��������/����90�����ڣ������������ÿ����Ϣ';

comment on column ICPS_JB_TOTAL.non_accrued_int_amt is
'��������90�����ϴ������ÿ����Ϣ';

comment on column ICPS_JB_TOTAL.accrued_ovd_prin_pnlt_amt is
'��������90�����ڣ������������ÿ�����ڱ���Ϣ';

comment on column ICPS_JB_TOTAL.non_accrued_ovd_prin_pnlt_amt is
'��������90�����ϴ������ÿ�����ڱ���Ϣ';

comment on column ICPS_JB_TOTAL.accrued_ovd_int_pnlt_amt is
'��������90�����ڣ������������ÿ��������Ϣ��Ϣ';

comment on column ICPS_JB_TOTAL.non_accrued_ovd_int_pnlt_amt is
'��������90�����ϴ������ÿ��������Ϣ��Ϣ';

comment on column ICPS_JB_TOTAL.prin_to_ovd_prin_amt is
'��������ת���ڱ���';

comment on column ICPS_JB_TOTAL.int_to_ovd_int_amt is
'������Ϣת������Ϣ';

comment on column ICPS_JB_TOTAL.accrued_to_non_prin_amt is
'��������Ӧ�ƣ�ת�������𣨷�Ӧ�ƣ�';

comment on column ICPS_JB_TOTAL.accrued_to_non_ovd_prin_amt is
'���ڱ���Ӧ�ƣ�ת���ڱ��𣨷�Ӧ�ƣ�';

comment on column ICPS_JB_TOTAL.in_to_out_int_amt is
'������Ϣ�����ڣ�ת������Ϣ�����⣩';

comment on column ICPS_JB_TOTAL.in_to_out_ovd_int_amt is
'������Ϣ�����ڣ�ת������Ϣ�����⣩';

comment on column ICPS_JB_TOTAL.in_to_out_ovd_prin_pnlt_amt is
'���ڱ���Ϣ�����ڣ�ת���ڱ���Ϣ�����⣩';

comment on column ICPS_JB_TOTAL.in_to_out_ovd_int_pnlt_amt is
'������Ϣ��Ϣ�����ڣ�ת������Ϣ��Ϣ�����⣩';

comment on column ICPS_JB_TOTAL.non_to_accrued_prin_amt is
'�������𣨷�Ӧ�ƣ�ת��������Ӧ�ƣ�';

comment on column ICPS_JB_TOTAL.non_to_accrued_ovd_prin_amt is
'���ڱ��𣨷�Ӧ�ƣ�ת���ڱ���Ӧ�ƣ�';

comment on column ICPS_JB_TOTAL.out_to_in_int_amt is
'������Ϣ�����⣩ת������Ϣ�����ڣ�';

comment on column ICPS_JB_TOTAL.out_to_in_ovd_int_amt is
'������Ϣ�����⣩ת������Ϣ�����ڣ�';

comment on column ICPS_JB_TOTAL.out_to_in_ovd_prin_pnlt_amt is
'���ڱ���Ϣ�����⣩ת�Ȿ��Ϣ�����ڣ�';

comment on column ICPS_JB_TOTAL.out_to_in_ovd_int_pnlt_amt is
'������Ϣ��Ϣ�����⣩ת������Ϣ��Ϣ�����ڣ�';

comment on column ICPS_JB_TOTAL.paid_prin_amt is
'ʵ����������Ӧ�ƣ�';

comment on column ICPS_JB_TOTAL.paid_non_accrued_prin_amt is
'ʵ���������𣨷�Ӧ�ƣ�';

comment on column ICPS_JB_TOTAL.paid_accrued_ovd_prin_amt is
'ʵ�����ڱ���Ӧ�ƣ�';

comment on column ICPS_JB_TOTAL.paid_non_accrued_ovd_prin_amt is
'ʵ�����ڱ��𣨷�Ӧ�ƣ�';

comment on column ICPS_JB_TOTAL.paid_int_amt is
'ʵ��������Ϣ�����ڣ�';

comment on column ICPS_JB_TOTAL.paid_out_int_amt is
'ʵ��������Ϣ�����⣩';

comment on column ICPS_JB_TOTAL.paid_in_ovd_int_amt is
'ʵ��������Ϣ�����ڣ�';

comment on column ICPS_JB_TOTAL.paid_out_ovd_int_amt is
'ʵ��������Ϣ�����⣩';

comment on column ICPS_JB_TOTAL.paid_in_ovd_prin_pnlt_int_amt is
'ʵ�����ڱ���Ϣ�����ڣ�';

comment on column ICPS_JB_TOTAL.paid_out_ovd_prin_pnlt_int_amt is
'ʵ�����ڱ���Ϣ�����⣩';

comment on column ICPS_JB_TOTAL.paid_in_ovd_int_pnlt_int_amt is
'ʵ��������Ϣ��Ϣ�����ڣ�';

comment on column ICPS_JB_TOTAL.paid_out_ovd_int_pnlt_int_amt is
'ʵ��������Ϣ��Ϣ�����⣩';

comment on column ICPS_JB_TOTAL.xpt_in_int_amt is
'����������Ϣ�����ڣ�';

comment on column ICPS_JB_TOTAL.xpt_out_int_amt is
'����������Ϣ�����⣩';

comment on column ICPS_JB_TOTAL.xpt_in_ovd_int_amt is
'����������Ϣ�����ڣ�';

comment on column ICPS_JB_TOTAL.xpt_out_ovd_int_amt is
'����������Ϣ�����⣩';

comment on column ICPS_JB_TOTAL.xpt_in_ovd_prin_pnlt_int_amt is
'�������ڱ���Ϣ�����ڣ�';

comment on column ICPS_JB_TOTAL.xpt_out_ovd_prin_pnlt_int_amt is
'�������ڱ���Ϣ�����⣩';

comment on column ICPS_JB_TOTAL.xpt_in_ovd_int_pnlt_int_amt is
'����������Ϣ��Ϣ�����ڣ�';

comment on column ICPS_JB_TOTAL.xpt_out_ovd_int_pnlt_int_amt is
'����������Ϣ��Ϣ�����⣩';

comment on column ICPS_JB_TOTAL.extend_param1 is
'��չ1';

comment on column ICPS_JB_TOTAL.extend_param2 is
'��չ2';

comment on column ICPS_JB_TOTAL.extend_param3 is
'��չ3';


/*==============================================================*/
/* Table: ICPS_JB_LENDING_DETAIL                                */
/*==============================================================*/
create table ICPS_JB_LENDING_DETAIL 
(
   busi_date            VARCHAR(8)          not null,
   file_order           INTEGER              not null,
   contract_no          VARCHAR(64),
   fund_seq_no          VARCHAR(64),
   third_product_code   VARCHAR(64),
   name                 VARCHAR(128),
   id_type              VARCHAR(2),
   id_num               VARCHAR(32),
   loan_status          VARCHAR(2),
   loan_use             VARCHAR(2),
   use_area             VARCHAR(2),
   apply_date           VARCHAR(20),
   encash_date          VARCHAR(20),
   currency             VARCHAR(3),
   encash_amt           DECIMAL(16,2),
   start_date           VARCHAR(8),
   end_date             VARCHAR(8),
   total_terms          INTEGER,
   repay_mode           VARCHAR(8),
   grace_day            INTEGER,
   rate_type            VARCHAR(2),
   day_rate             DECIMAL(16,6),
   prin_repay_frequency VARCHAR(2),
   int_repay_frequency  VARCHAR(2),
   guarantee_type       VARCHAR(3),
   credit_no            VARCHAR(64),
   encash_acct_type     VARCHAR(2),
   encash_acct          VARCHAR(32),
   repay_acct_type      VARCHAR(2),
   repay_acct           VARCHAR(32),
   loan_apply_no        VARCHAR(32),
   is_check_flag        CHAR(1),
   extend_param1        VARCHAR(100),
   extend_param2        VARCHAR(250),
   extend_param3        VARCHAR(40),
   constraint PK_ICPS_JB_LENDING_DETAIL primary key (busi_date, file_order)
);

comment on table ICPS_JB_LENDING_DETAIL is
'��;֧����ϸ�ļ�';

comment on column ICPS_JB_LENDING_DETAIL.busi_date is
'ҵ������';

comment on column ICPS_JB_LENDING_DETAIL.file_order is
'�ļ����';

comment on column ICPS_JB_LENDING_DETAIL.contract_no is
'����ƽ̨�����ͬ��';

comment on column ICPS_JB_LENDING_DETAIL.fund_seq_no is
'�ſ��ʽ���ˮ��';

comment on column ICPS_JB_LENDING_DETAIL.third_product_code is
'��Ʒ��';

comment on column ICPS_JB_LENDING_DETAIL.name is
'�ͻ���ʵ����';

comment on column ICPS_JB_LENDING_DETAIL.id_type is
'֤������';

comment on column ICPS_JB_LENDING_DETAIL.id_num is
'�ͻ�֤������';

comment on column ICPS_JB_LENDING_DETAIL.loan_status is
'����״̬ 1-�ɹ� 2-ʧ�� 3-��;';

comment on column ICPS_JB_LENDING_DETAIL.loan_use is
'������; 1-���� 2-��Ӫ';

comment on column ICPS_JB_LENDING_DETAIL.use_area is
'�����ʽ�ʹ��λ�� 0-���� 1-����';

comment on column ICPS_JB_LENDING_DETAIL.apply_date is
'����֧��ʱ�� YYYYMMDDHHMMSS';

comment on column ICPS_JB_LENDING_DETAIL.encash_date is
'�ſ����� YYYYMMDDHHMMSS';

comment on column ICPS_JB_LENDING_DETAIL.currency is
'���� CNY';

comment on column ICPS_JB_LENDING_DETAIL.encash_amt is
'�ſ���';

comment on column ICPS_JB_LENDING_DETAIL.start_date is
'������Ϣ�� YYYYMMDD';

comment on column ICPS_JB_LENDING_DETAIL.end_date is
'������� YYYYMMDD';

comment on column ICPS_JB_LENDING_DETAIL.total_terms is
'�����ڴ���';

comment on column ICPS_JB_LENDING_DETAIL.repay_mode is
'���ʽ 1-�ȶϢ 2-�ȶ�� 6-���ڸ�Ϣ����һ�λ���';

comment on column ICPS_JB_LENDING_DETAIL.grace_day is
'����������';

comment on column ICPS_JB_LENDING_DETAIL.rate_type is
'�������� F-�̶����� L0-��������-���� L1-��������-���� L2-��������-���� L3-��������-���� L4-��������-������ L5-��������-���� L9-��������-����';

comment on column ICPS_JB_LENDING_DETAIL.day_rate is
'����������';

comment on column ICPS_JB_LENDING_DETAIL.prin_repay_frequency is
'���𻹿�Ƶ�ʣ��ñʴ����������λ���ʱ��ļ����01:��02:��03:��04:��05:����06:��07:һ����08:�����ڣ���������������ʱ�仹�99:����';

comment on column ICPS_JB_LENDING_DETAIL.int_repay_frequency is
'���𻹿�Ƶ�ʣ��ñʴ����������λ���ʱ��ļ����01:��02:��03:��04:��05:����06:��07:һ����08:�����ڣ���������������ʱ�仹�99:����';

comment on column ICPS_JB_LENDING_DETAIL.guarantee_type is
'�������ͣ�A ��Ѻ����B ��Ѻ����B01   ���ز���Ѻ����B99   ������Ѻ����C ��֤����C01   ��������C99   ������֤����D ����/�ⵣ������E ��ϵ���Z ����';

comment on column ICPS_JB_LENDING_DETAIL.credit_no is
'���ű��';

comment on column ICPS_JB_LENDING_DETAIL.encash_acct_type is
'�ſ��ʺ����ͣ�01:���н�ǿ�02:֧����';

comment on column ICPS_JB_LENDING_DETAIL.encash_acct is
'�ſ��ʺ�';

comment on column ICPS_JB_LENDING_DETAIL.repay_acct_type is
'�����ʺ����ͣ�01:���н�ǿ�02:֧����';

comment on column ICPS_JB_LENDING_DETAIL.repay_acct is
'�����ʺ�';

comment on column ICPS_JB_LENDING_DETAIL.loan_apply_no is
'�������뵥��';

comment on column ICPS_JB_LENDING_DETAIL.is_check_flag is
'������˱�ʶ';

comment on column ICPS_JB_LENDING_DETAIL.extend_param1 is
'��չ1';

comment on column ICPS_JB_LENDING_DETAIL.extend_param2 is
'��չ2';

comment on column ICPS_JB_LENDING_DETAIL.extend_param3 is
'��չ3';


/*==============================================================*/
/* Table: ICPS_JB_LOAN_DETAIL                                   */
/*==============================================================*/
create table ICPS_JB_LOAN_DETAIL 
(
   busi_date            VARCHAR(8)          not null,
   file_order           INTEGER              not null,
   contract_no          VARCHAR(64),
   fund_seq_no          VARCHAR(64),
   third_product_code   VARCHAR(64),
   name                 VARCHAR(128),
   id_type              VARCHAR(2),
   id_num               VARCHAR(32),
   loan_status          VARCHAR(2),
   loan_use             VARCHAR(2),
   use_area             VARCHAR(2),
   apply_date           VARCHAR(20),
   encash_date          VARCHAR(20),
   currency             VARCHAR(3),
   encash_amt           DECIMAL(16,2),
   start_date           VARCHAR(8),
   end_date             VARCHAR(8),
   total_terms          INTEGER,
   repay_mode           VARCHAR(8),
   grace_day            INTEGER,
   rate_type            VARCHAR(2),
   day_rate             DECIMAL(16,6),
   prin_repay_frequency VARCHAR(2),
   int_repay_frequency  VARCHAR(2),
   guarantee_type       VARCHAR(3),
   credit_no            VARCHAR(64),
   encash_acct_type     VARCHAR(2),
   encash_acct          VARCHAR(32),
   repay_acct_type      VARCHAR(2),
   repay_acct           VARCHAR(32),
   loan_apply_no        VARCHAR(64),
   is_check_flag        CHAR(1),
   extend_param1        VARCHAR(100),
   extend_param2        VARCHAR(250),
   extend_param3        VARCHAR(40),
   constraint PK_ICPS_JB_LOAN_DETAIL primary key (busi_date, file_order)
);

comment on table ICPS_JB_LOAN_DETAIL is
'�ſ��ݣ���ϸ�ļ�';

comment on column ICPS_JB_LOAN_DETAIL.busi_date is
'ҵ������';

comment on column ICPS_JB_LOAN_DETAIL.file_order is
'�ļ����';

comment on column ICPS_JB_LOAN_DETAIL.contract_no is
'����ƽ̨�����ͬ��';

comment on column ICPS_JB_LOAN_DETAIL.fund_seq_no is
'�ſ��ʽ���ˮ��';

comment on column ICPS_JB_LOAN_DETAIL.third_product_code is
'��Ʒ��';

comment on column ICPS_JB_LOAN_DETAIL.name is
'�ͻ���ʵ����';

comment on column ICPS_JB_LOAN_DETAIL.id_type is
'֤������';

comment on column ICPS_JB_LOAN_DETAIL.id_num is
'�ͻ�֤������';

comment on column ICPS_JB_LOAN_DETAIL.loan_status is
'����״̬ 1-�ɹ� 2-ʧ�� 3-��;';

comment on column ICPS_JB_LOAN_DETAIL.loan_use is
'������; 1-���� 2-��Ӫ';

comment on column ICPS_JB_LOAN_DETAIL.use_area is
'�����ʽ�ʹ��λ�� 0-���� 1-����';

comment on column ICPS_JB_LOAN_DETAIL.apply_date is
'����֧��ʱ�� YYYYMMDDHHMMSS';

comment on column ICPS_JB_LOAN_DETAIL.encash_date is
'�ſ����� YYYYMMDDHHMMSS';

comment on column ICPS_JB_LOAN_DETAIL.currency is
'���� CNY-�����';

comment on column ICPS_JB_LOAN_DETAIL.encash_amt is
'�ſ���';

comment on column ICPS_JB_LOAN_DETAIL.start_date is
'������Ϣ�� YYYYMMDD';

comment on column ICPS_JB_LOAN_DETAIL.end_date is
'������� YYYYMMDD';

comment on column ICPS_JB_LOAN_DETAIL.total_terms is
'�����ڴ���';

comment on column ICPS_JB_LOAN_DETAIL.repay_mode is
'���ʽ 1-�ȶϢ 2-�ȶ�� 6-���ڸ�Ϣ����һ�λ���';

comment on column ICPS_JB_LOAN_DETAIL.grace_day is
'����������';

comment on column ICPS_JB_LOAN_DETAIL.rate_type is
'�������ͣ�F:�̶�����L0:��������-����L1:��������-����L2:��������-����L3:��������-����L4:��������-������L5:��������-����L9:��������-����';

comment on column ICPS_JB_LOAN_DETAIL.day_rate is
'����������';

comment on column ICPS_JB_LOAN_DETAIL.prin_repay_frequency is
'���𻹿�Ƶ�ʣ��ñʴ����������λ���ʱ��ļ����01:��02:��03:��04:��05:����06:��07:һ����08:�����ڣ���������������ʱ�仹�99:����';

comment on column ICPS_JB_LOAN_DETAIL.int_repay_frequency is
'���𻹿�Ƶ�ʣ��ñʴ����������λ���ʱ��ļ����01:��02:��03:��04:��05:����06:��07:һ����08:�����ڣ���������������ʱ�仹�99:����';

comment on column ICPS_JB_LOAN_DETAIL.guarantee_type is
'�������ͣ�A ��Ѻ����B ��Ѻ����B01   ���ز���Ѻ����B99   ������Ѻ����C ��֤����C01   ��������C99   ������֤����D ����/�ⵣ������E ��ϵ���Z ����';

comment on column ICPS_JB_LOAN_DETAIL.credit_no is
'���ű��';

comment on column ICPS_JB_LOAN_DETAIL.encash_acct_type is
'�ſ��ʺ����ͣ�01:���н�ǿ�02:֧����';

comment on column ICPS_JB_LOAN_DETAIL.encash_acct is
'�ſ��ʺ�';

comment on column ICPS_JB_LOAN_DETAIL.repay_acct_type is
'�����ʺ����ͣ�01:���н�ǿ�02:֧����';

comment on column ICPS_JB_LOAN_DETAIL.repay_acct is
'�����ʺ�';

comment on column ICPS_JB_LOAN_DETAIL.loan_apply_no is
'�������뵥��';

comment on column ICPS_JB_LOAN_DETAIL.is_check_flag is
'������˱�ʶ';

comment on column ICPS_JB_LOAN_DETAIL.extend_param1 is
'��չ1';

comment on column ICPS_JB_LOAN_DETAIL.extend_param2 is
'��չ2';

comment on column ICPS_JB_LOAN_DETAIL.extend_param3 is
'��չ3';


/*==============================================================*/
/* Table: ICPS_JB_REPAY_PLAN                                    */
/*==============================================================*/
create table ICPS_JB_REPAY_PLAN 
(
   busi_date            CHAR(8)              not null,
   file_order           INTEGER              not null,
   contract_no          VARCHAR(64),
   term_no              INTEGER,
   start_date           VARCHAR(8),
   end_date             VARCHAR(8),
   prin_amt             DECIMAL(16,2),
   int_amt              DECIMAL(16,2),
   is_check_flag        CHAR(1),
   extend_param1        VARCHAR(100),
   extend_param2        VARCHAR(250),
   extend_param3        VARCHAR(40),
   constraint PK_ICPS_JB_REPAY_PLAN primary key (busi_date, file_order)
);

comment on table ICPS_JB_REPAY_PLAN is
'�ſ���ڣ���ϸ�ļ�';

comment on column ICPS_JB_REPAY_PLAN.busi_date is
'ҵ������';

comment on column ICPS_JB_REPAY_PLAN.file_order is
'�ļ����';

comment on column ICPS_JB_REPAY_PLAN.contract_no is
'����ƽ̨�����Լ��';

comment on column ICPS_JB_REPAY_PLAN.term_no is
'�ڴκ�';

comment on column ICPS_JB_REPAY_PLAN.start_date is
'���ڿ�ʼ���� YYYYMMDD';

comment on column ICPS_JB_REPAY_PLAN.end_date is
'���ڽ������� YYYYMMDD';

comment on column ICPS_JB_REPAY_PLAN.prin_amt is
'������';

comment on column ICPS_JB_REPAY_PLAN.int_amt is
'��ʼ��Ϣ������';

comment on column ICPS_JB_REPAY_PLAN.is_check_flag is
'������˱�ʶ';

comment on column ICPS_JB_REPAY_PLAN.extend_param1 is
'��չ1';

comment on column ICPS_JB_REPAY_PLAN.extend_param2 is
'��չ2';

comment on column ICPS_JB_REPAY_PLAN.extend_param3 is
'��չ3';


/*==============================================================*/
/* Table: ICPS_JB_REPAY_LOAN_DETAIL                             */
/*==============================================================*/
create table ICPS_JB_REPAY_LOAN_DETAIL 
(
   busi_date            CHAR(8)              not null,
   file_order           INTEGER              not null,
   contract_no          VARCHAR(64),
   repay_seq_no         VARCHAR(64),
   fee_no               VARCHAR(64),
   withdraw_no          VARCHAR(64),
   repay_type           VARCHAR(8),
   repay_date           VARCHAR(20),
   curr_prin_bal        DECIMAL(16,2),
   curr_ovd_prin_bal    DECIMAL(16,2),
   curr_int_bal         DECIMAL(16,2),
   curr_ovd_int_bal     DECIMAL(16,2),
   curr_ovd_prin_pnlt_bal DECIMAL(16,2),
   curr_ovd_int_pnlt_bal DECIMAL(16,2),
   repay_amt            DECIMAL(16,2),
   paid_prin_amt        DECIMAL(16,2),
   paid_ovd_prin_amt    DECIMAL(16,2),
   paid_int_amt         DECIMAL(16,2),
   paid_ovd_int_amt     DECIMAL(16,2),
   paid_ovd_prin_pnlt_amt DECIMAL(16,2),
   paid_ovd_int_pnlt_amt DECIMAL(16,2),
   fee_amt              DECIMAL(16,2),
   is_check_flag        CHAR(1),
   extend_param1        VARCHAR(100),
   extend_param2        VARCHAR(250),
   extend_param3        VARCHAR(40),
   constraint PK_ICPS_JB_REPAY_LOAN_DETAIL primary key (busi_date, file_order)
);

comment on table ICPS_JB_REPAY_LOAN_DETAIL is
'�����ݣ���ϸ�ļ�';

comment on column ICPS_JB_REPAY_LOAN_DETAIL.busi_date is
'ҵ������';

comment on column ICPS_JB_REPAY_LOAN_DETAIL.file_order is
'�ļ����';

comment on column ICPS_JB_REPAY_LOAN_DETAIL.contract_no is
'����ƽ̨�����ͬ��';

comment on column ICPS_JB_REPAY_LOAN_DETAIL.repay_seq_no is
'������ˮ��';

comment on column ICPS_JB_REPAY_LOAN_DETAIL.fee_no is
'�շѵ���';

comment on column ICPS_JB_REPAY_LOAN_DETAIL.withdraw_no is
'�������ֵ���';

comment on column ICPS_JB_REPAY_LOAN_DETAIL.repay_type is
'�������� 01-�������� 02-�����ۿ� 03-����֪ͨ���� 04-���»���';

comment on column ICPS_JB_REPAY_LOAN_DETAIL.repay_date is
'�������� YYYYMMDDHHMMSS';

comment on column ICPS_JB_REPAY_LOAN_DETAIL.curr_prin_bal is
'���λ���ǰ��Ӧ��δ�������������';

comment on column ICPS_JB_REPAY_LOAN_DETAIL.curr_ovd_prin_bal is
'���λ���ǰ��Ӧ��δ�����ڱ������';

comment on column ICPS_JB_REPAY_LOAN_DETAIL.curr_int_bal is
'���λ���ǰ��Ӧ��δ��������Ϣ���';

comment on column ICPS_JB_REPAY_LOAN_DETAIL.curr_ovd_int_bal is
'���λ���ǰ��Ӧ��δ��������Ϣ���';

comment on column ICPS_JB_REPAY_LOAN_DETAIL.curr_ovd_prin_pnlt_bal is
'���λ���ǰ��Ӧ��δ�����ڱ���Ϣ���';

comment on column ICPS_JB_REPAY_LOAN_DETAIL.curr_ovd_int_pnlt_bal is
'���λ���ǰ��Ӧ��δ��������Ϣ��Ϣ���';

comment on column ICPS_JB_REPAY_LOAN_DETAIL.repay_amt is
'�ܽ��';

comment on column ICPS_JB_REPAY_LOAN_DETAIL.paid_prin_amt is
'����ʵ������������';

comment on column ICPS_JB_REPAY_LOAN_DETAIL.paid_ovd_prin_amt is
'����ʵ�����ڱ�����';

comment on column ICPS_JB_REPAY_LOAN_DETAIL.paid_int_amt is
'����ʵ��������Ϣ���';

comment on column ICPS_JB_REPAY_LOAN_DETAIL.paid_ovd_int_amt is
'����ʵ��������Ϣ���';

comment on column ICPS_JB_REPAY_LOAN_DETAIL.paid_ovd_prin_pnlt_amt is
'����ʵ�����ڱ���Ϣ���';

comment on column ICPS_JB_REPAY_LOAN_DETAIL.paid_ovd_int_pnlt_amt is
'����ʵ��������Ϣ��Ϣ���';

comment on column ICPS_JB_REPAY_LOAN_DETAIL.fee_amt is
'���λ����Ӧ��ƽ̨����ѽ��';

comment on column ICPS_JB_REPAY_LOAN_DETAIL.is_check_flag is
'������˱�ʶ';

comment on column ICPS_JB_REPAY_LOAN_DETAIL.extend_param1 is
'��չ1';

comment on column ICPS_JB_REPAY_LOAN_DETAIL.extend_param2 is
'��չ2';

comment on column ICPS_JB_REPAY_LOAN_DETAIL.extend_param3 is
'��չ3';


/*==============================================================*/
/* Table: ICPS_JB_REPAY_INSTMNT_DETAIL                          */
/*==============================================================*/
create table ICPS_JB_REPAY_INSTMNT_DETAIL 
(
   busi_date            CHAR(8)              not null,
   file_order           INTEGER              not null,
   contract_no          VARCHAR(32),
   repay_seq_no         VARCHAR(64),
   term_no              INTEGER,
   repay_amt_type       VARCHAR(8),
   repay_date           VARCHAR(8),
   curr_prin_bal        DECIMAL(16,2),
   curr_int_bal         DECIMAL(16,2),
   curr_ovd_prin_pnlt_bal DECIMAL(16,2),
   curr_ovd_int_pnlt_bal DECIMAL(16,2),
   repay_amt            DECIMAL(16,2),
   paid_prin_amt        DECIMAL(16,2),
   paid_int_amt         DECIMAL(16,2),
   paid_ovd_prin_pnlt_amt DECIMAL(16,2),
   paid_ovd_int_pnlt_amt DECIMAL(16,2),
   is_check_flag        CHAR(1),
   extend_param1        VARCHAR(100),
   extend_param2        VARCHAR(250),
   extend_param3        VARCHAR(40),
   constraint PK_ICPS_JB_REPAY_INSTMNT_DETAI primary key (busi_date, file_order)
);

comment on table ICPS_JB_REPAY_INSTMNT_DETAIL is
'������ڣ���ϸ�ļ�';

comment on column ICPS_JB_REPAY_INSTMNT_DETAIL.busi_date is
'ҵ������';

comment on column ICPS_JB_REPAY_INSTMNT_DETAIL.file_order is
'�ļ����';

comment on column ICPS_JB_REPAY_INSTMNT_DETAIL.contract_no is
'����ƽ̨�����ͬ��';

comment on column ICPS_JB_REPAY_INSTMNT_DETAIL.repay_seq_no is
'������ˮ��';

comment on column ICPS_JB_REPAY_INSTMNT_DETAIL.term_no is
'�ڴκ�';

comment on column ICPS_JB_REPAY_INSTMNT_DETAIL.repay_amt_type is
'���������� 01-���ڻ��� 02-��ǰ���� 03-���ڻ���';

comment on column ICPS_JB_REPAY_INSTMNT_DETAIL.repay_date is
'�������� YYYYMMDD';

comment on column ICPS_JB_REPAY_INSTMNT_DETAIL.curr_prin_bal is
'���λ���ǰ��Ӧ��δ�ձ���';

comment on column ICPS_JB_REPAY_INSTMNT_DETAIL.curr_int_bal is
'���λ���ǰ��Ӧ��δ����Ϣ';

comment on column ICPS_JB_REPAY_INSTMNT_DETAIL.curr_ovd_prin_pnlt_bal is
'���λ���ǰ��Ӧ��δ�����ڱ���Ϣ';

comment on column ICPS_JB_REPAY_INSTMNT_DETAIL.curr_ovd_int_pnlt_bal is
'���λ���ǰ��Ӧ��δ��������Ϣ��Ϣ';

comment on column ICPS_JB_REPAY_INSTMNT_DETAIL.repay_amt is
'����ʵ���ܽ��';

comment on column ICPS_JB_REPAY_INSTMNT_DETAIL.paid_prin_amt is
'����ʵ��������';

comment on column ICPS_JB_REPAY_INSTMNT_DETAIL.paid_int_amt is
'����ʵ����Ϣ���';

comment on column ICPS_JB_REPAY_INSTMNT_DETAIL.paid_ovd_prin_pnlt_amt is
'����ʵ�����ڱ���Ϣ���';

comment on column ICPS_JB_REPAY_INSTMNT_DETAIL.paid_ovd_int_pnlt_amt is
'����ʵ��������Ϣ��Ϣ���';

comment on column ICPS_JB_REPAY_INSTMNT_DETAIL.is_check_flag is
'������˱�ʶ';

comment on column ICPS_JB_REPAY_INSTMNT_DETAIL.extend_param1 is
'��չ1';

comment on column ICPS_JB_REPAY_INSTMNT_DETAIL.extend_param2 is
'��չ2';

comment on column ICPS_JB_REPAY_INSTMNT_DETAIL.extend_param3 is
'��չ3';


/*==============================================================*/
/* Table: ICPS_JB_XPT_LOAN_DETAIL                               */
/*==============================================================*/
create table ICPS_JB_XPT_LOAN_DETAIL 
(
   busi_date            CHAR(8)              not null,
   file_order           INTEGER              not null,
   contract_no          VARCHAR(32),
   xpt_seq_no           VARCHAR(64),
   xpt_date             VARCHAR(20),
   curr_int_bal         DECIMAL(16,2),
   curr_ovd_int_bal     DECIMAL(16,2),
   curr_ovd_prin_pnlt_bal DECIMAL(16,2),
   curr_ovd_int_pnlt_bal DECIMAL(16,2),
   xpt_amt              DECIMAL(16,2),
   xpt_int_amt          DECIMAL(16,2),
   xpt_ovd_int_amt      DECIMAL(16,2),
   xpt_ovd_prin_pnlt_amt DECIMAL(16,2),
   xpt_ovd_int_pnlt_amt DECIMAL(16,2),
   is_check_flag        CHAR(1),
   extend_param1        VARCHAR(100),
   extend_param2        VARCHAR(250),
   extend_param3        VARCHAR(40),
   constraint PK_ICPS_JB_XPT_LOAN_DETAIL primary key (busi_date, file_order)
);

comment on table ICPS_JB_XPT_LOAN_DETAIL is
'���⣨��ݣ���ϸ�ļ�';

comment on column ICPS_JB_XPT_LOAN_DETAIL.busi_date is
'ҵ������';

comment on column ICPS_JB_XPT_LOAN_DETAIL.file_order is
'�ļ����';

comment on column ICPS_JB_XPT_LOAN_DETAIL.contract_no is
'����ƽ̨�����ͬ��';

comment on column ICPS_JB_XPT_LOAN_DETAIL.xpt_seq_no is
'������ˮ��';

comment on column ICPS_JB_XPT_LOAN_DETAIL.xpt_date is
'����ʱ�� YYYYMMDDHHMMSS';

comment on column ICPS_JB_XPT_LOAN_DETAIL.curr_int_bal is
'���λ���ǰ��Ӧ��δ��������Ϣ���';

comment on column ICPS_JB_XPT_LOAN_DETAIL.curr_ovd_int_bal is
'���λ���ǰ��Ӧ��δ��������Ϣ���';

comment on column ICPS_JB_XPT_LOAN_DETAIL.curr_ovd_prin_pnlt_bal is
'���λ���ǰ��Ӧ��δ�����ڱ���Ϣ���';

comment on column ICPS_JB_XPT_LOAN_DETAIL.curr_ovd_int_pnlt_bal is
'���λ���ǰ��Ӧ��δ��������Ϣ��Ϣ���';

comment on column ICPS_JB_XPT_LOAN_DETAIL.xpt_amt is
'�����ܽ���λ�֣�';

comment on column ICPS_JB_XPT_LOAN_DETAIL.xpt_int_amt is
'���μ���������Ϣ���';

comment on column ICPS_JB_XPT_LOAN_DETAIL.xpt_ovd_int_amt is
'���μ���������Ϣ���';

comment on column ICPS_JB_XPT_LOAN_DETAIL.xpt_ovd_prin_pnlt_amt is
'���μ������ڱ���Ϣ���';

comment on column ICPS_JB_XPT_LOAN_DETAIL.xpt_ovd_int_pnlt_amt is
'���μ���������Ϣ��Ϣ���';

comment on column ICPS_JB_XPT_LOAN_DETAIL.is_check_flag is
'������˱�ʶ';

comment on column ICPS_JB_XPT_LOAN_DETAIL.extend_param1 is
'��չ1';

comment on column ICPS_JB_XPT_LOAN_DETAIL.extend_param2 is
'��չ2';

comment on column ICPS_JB_XPT_LOAN_DETAIL.extend_param3 is
'��չ3';


/*==============================================================*/
/* Table: ICPS_JB_XPT_INSTMNT_DETAIL                            */
/*==============================================================*/
create table ICPS_JB_XPT_INSTMNT_DETAIL 
(
   busi_date            CHAR(8)              not null,
   file_order           INTEGER              not null,
   contract_no          VARCHAR(32),
   xpt_seq_no           VARCHAR(64),
   term_no              INTEGER,
   settle_date          VARCHAR(8),
   curr_int_bal         DECIMAL(16,2),
   curr_ovd_prin_pnlt_bal DECIMAL(16,2),
   curr_ovd_int_pnlt_bal DECIMAL(16,2),
   xpt_amt              DECIMAL(16,2),
   xpt_int_amt          DECIMAL(16,2),
   xpt_ovd_prin_pnlt_amt DECIMAL(16,2),
   xpt_ovd_int_pnlt_amt DECIMAL(16,2),
   is_check_flag        CHAR(1),
   extend_param1        VARCHAR(100),
   extend_param2        VARCHAR(250),
   extend_param3        VARCHAR(40),
   constraint PK_ICPS_JB_XPT_INSTMNT_DETAIL primary key (busi_date, file_order)
);

comment on table ICPS_JB_XPT_INSTMNT_DETAIL is
'���⣨���ڣ���ϸ�ļ�';

comment on column ICPS_JB_XPT_INSTMNT_DETAIL.busi_date is
'ҵ������';

comment on column ICPS_JB_XPT_INSTMNT_DETAIL.file_order is
'�ļ����';

comment on column ICPS_JB_XPT_INSTMNT_DETAIL.contract_no is
'����ƽ̨�����ͬ��';

comment on column ICPS_JB_XPT_INSTMNT_DETAIL.xpt_seq_no is
'������ˮ��';

comment on column ICPS_JB_XPT_INSTMNT_DETAIL.term_no is
'�ڴκ�';

comment on column ICPS_JB_XPT_INSTMNT_DETAIL.settle_date is
'���������� YYYYMMDD';

comment on column ICPS_JB_XPT_INSTMNT_DETAIL.curr_int_bal is
'���λ���ǰ��Ӧ��δ����Ϣ';

comment on column ICPS_JB_XPT_INSTMNT_DETAIL.curr_ovd_prin_pnlt_bal is
'���λ���ǰ��Ӧ��δ�����ڱ���Ϣ';

comment on column ICPS_JB_XPT_INSTMNT_DETAIL.curr_ovd_int_pnlt_bal is
'���λ���ǰ��Ӧ��δ��������Ϣ��Ϣ';

comment on column ICPS_JB_XPT_INSTMNT_DETAIL.xpt_amt is
'���μ����ܽ��';

comment on column ICPS_JB_XPT_INSTMNT_DETAIL.xpt_int_amt is
'���μ�����Ϣ���';

comment on column ICPS_JB_XPT_INSTMNT_DETAIL.xpt_ovd_prin_pnlt_amt is
'���μ������ڱ���Ϣ���';

comment on column ICPS_JB_XPT_INSTMNT_DETAIL.xpt_ovd_int_pnlt_amt is
'���μ���������Ϣ��Ϣ���';

comment on column ICPS_JB_XPT_INSTMNT_DETAIL.is_check_flag is
'������˱�ʶ';

comment on column ICPS_JB_XPT_INSTMNT_DETAIL.extend_param1 is
'��չ1';

comment on column ICPS_JB_XPT_INSTMNT_DETAIL.extend_param2 is
'��չ2';

comment on column ICPS_JB_XPT_INSTMNT_DETAIL.extend_param3 is
'��չ3';


/*==============================================================*/
/* Table: ICPS_JB_LOAN_INIT                                     */
/*==============================================================*/
create table ICPS_JB_LOAN_INIT 
(
   busi_date            CHAR(8)              not null,
   file_order           INTEGER              not null,
   contract_no          VARCHAR(32),
   settle_date          VARCHAR(8),
   status               VARCHAR(10),
   clear_date           VARCHAR(8),
   asset_class          VARCHAR(2),
   accrued_status       VARCHAR(2),
   next_repay_date      VARCHAR(8),
   unclear_terms        INTEGER,
   ovd_terms            INTEGER,
   prin_ovd_days        INTEGER,
   int_ovd_days         INTEGER,
   prin_bal             DECIMAL(16,2),
   ovd_prin_bal         DECIMAL(16,2),
   int_bal              DECIMAL(16,2),
   ovd_int_bal          DECIMAL(16,2),
   ovd_prin_pnlt_bal    DECIMAL(16,2),
   ovd_int_pnlt_bal     DECIMAL(16,2),
   is_check_flag        CHAR(1),
   extend_param1        VARCHAR(100),
   extend_param2        VARCHAR(250),
   extend_param3        VARCHAR(40),
   constraint PK_ICPS_JB_LOAN_INIT primary key (busi_date, file_order)
);

comment on table ICPS_JB_LOAN_INIT is
'�ճ�����ݣ���Ϣ�ļ�';

comment on column ICPS_JB_LOAN_INIT.busi_date is
'ҵ������';

comment on column ICPS_JB_LOAN_INIT.file_order is
'�ļ����';

comment on column ICPS_JB_LOAN_INIT.contract_no is
'����ƽ̨�����ͬ��';

comment on column ICPS_JB_LOAN_INIT.settle_date is
'������ڣ���ʽYYYYMMdd';

comment on column ICPS_JB_LOAN_INIT.status is
'���״̬������NORMAL,����OVD,����CLEAR ';

comment on column ICPS_JB_LOAN_INIT.clear_date is
'�������ڣ���ʽYYYYMMdd';

comment on column ICPS_JB_LOAN_INIT.asset_class is
'�弶�����ʶ������1����ע2���μ�3������4����ʧ5';

comment on column ICPS_JB_LOAN_INIT.accrued_status is
'Ӧ�Ʒ�Ӧ�Ʊ�ʶ��Ӧ��0����Ӧ��1';

comment on column ICPS_JB_LOAN_INIT.next_repay_date is
'��һ�������� YYYYMMDD';

comment on column ICPS_JB_LOAN_INIT.unclear_terms is
'δ��������';

comment on column ICPS_JB_LOAN_INIT.ovd_terms is
'�����ڴ���';

comment on column ICPS_JB_LOAN_INIT.prin_ovd_days is
'������������';

comment on column ICPS_JB_LOAN_INIT.int_ovd_days is
'��Ϣ��������';

comment on column ICPS_JB_LOAN_INIT.prin_bal is
'�����������';

comment on column ICPS_JB_LOAN_INIT.ovd_prin_bal is
'���ڱ������';

comment on column ICPS_JB_LOAN_INIT.int_bal is
'������Ϣ���';

comment on column ICPS_JB_LOAN_INIT.ovd_int_bal is
'������Ϣ���';

comment on column ICPS_JB_LOAN_INIT.ovd_prin_pnlt_bal is
'���ڱ���Ϣ���';

comment on column ICPS_JB_LOAN_INIT.ovd_int_pnlt_bal is
'������Ϣ��Ϣ���';

comment on column ICPS_JB_LOAN_INIT.is_check_flag is
'������˱�ʶ';

comment on column ICPS_JB_LOAN_INIT.extend_param1 is
'��չ1';

comment on column ICPS_JB_LOAN_INIT.extend_param2 is
'��չ2';

comment on column ICPS_JB_LOAN_INIT.extend_param3 is
'��չ3';


/*==============================================================*/
/* Table: ICPS_JB_INSTMNT_INIT                                  */
/*==============================================================*/
create table ICPS_JB_INSTMNT_INIT 
(
   busi_date            CHAR(8)              not null,
   file_order           INTEGER              not null,
   contract_no          VARCHAR(32)         not null,
   settle_date          VARCHAR(8),
   term_no              INTEGER,
   start_date           VARCHAR(8),
   end_date             VARCHAR(8),
   status               VARCHAR(10),
   clear_date           VARCHAR(8),
   prin_ovd_date        VARCHAR(8),
   int_ovd_date         VARCHAR(8),
   prin_ovd_days        INTEGER,
   int_ovd_days         INTEGER,
   prin_bal             DECIMAL(16,2),
   int_bal              DECIMAL(16,2),
   ovd_prin_pnlt_bal    DECIMAL(16,2),
   ovd_int_pnlt_bal     DECIMAL(16,2),
   is_check_flag        CHAR(1),
   extend_param1        VARCHAR(100),
   extend_param2        VARCHAR(250),
   extend_param3        VARCHAR(40),
   constraint PK_ICPS_JB_INSTMNT_INIT primary key (busi_date, file_order)
);

comment on table ICPS_JB_INSTMNT_INIT is
'�ճ������ڣ���Ϣ�ļ�';

comment on column ICPS_JB_INSTMNT_INIT.busi_date is
'ҵ������';

comment on column ICPS_JB_INSTMNT_INIT.file_order is
'�ļ����';

comment on column ICPS_JB_INSTMNT_INIT.contract_no is
'����ƽ̨�����ͬ��';

comment on column ICPS_JB_INSTMNT_INIT.settle_date is
'������� YYYYMMDD';

comment on column ICPS_JB_INSTMNT_INIT.term_no is
'�ڴκ�';

comment on column ICPS_JB_INSTMNT_INIT.start_date is
'���ڿ�ʼ���� YYYYMMDD';

comment on column ICPS_JB_INSTMNT_INIT.end_date is
'���ڽ������ڣ����ڻ����գ� YYYYMMDD';

comment on column ICPS_JB_INSTMNT_INIT.status is
'����״̬������NORMAL,����OVD,����CLEAR ';

comment on column ICPS_JB_INSTMNT_INIT.clear_date is
'�������� YYYYMMDD';

comment on column ICPS_JB_INSTMNT_INIT.prin_ovd_date is
'����ת�������� YYYYMMDD';

comment on column ICPS_JB_INSTMNT_INIT.int_ovd_date is
'��Ϣת�������� YYYYMMDD';

comment on column ICPS_JB_INSTMNT_INIT.prin_ovd_days is
'������������';

comment on column ICPS_JB_INSTMNT_INIT.int_ovd_days is
'��Ϣ��������';

comment on column ICPS_JB_INSTMNT_INIT.prin_bal is
'�������';

comment on column ICPS_JB_INSTMNT_INIT.int_bal is
'��Ϣ���';

comment on column ICPS_JB_INSTMNT_INIT.ovd_prin_pnlt_bal is
'���ڱ���Ϣ���';

comment on column ICPS_JB_INSTMNT_INIT.ovd_int_pnlt_bal is
'������Ϣ��Ϣ���';

comment on column ICPS_JB_INSTMNT_INIT.is_check_flag is
'������˱�ʶ';

comment on column ICPS_JB_INSTMNT_INIT.extend_param1 is
'��չ1';

comment on column ICPS_JB_INSTMNT_INIT.extend_param2 is
'��չ2';

comment on column ICPS_JB_INSTMNT_INIT.extend_param3 is
'��չ3';


/*==============================================================*/
/* Table: ICPS_JB_LOAN_CALC                                     */
/*==============================================================*/
create table ICPS_JB_LOAN_CALC 
(
   busi_date            CHAR(8)              not null,
   file_order           INTEGER              not null,
   contract_no          VARCHAR(64),
   calc_date            VARCHAR(8),
   accrued_status       VARCHAR(2),
   prin_bal             DECIMAL(16,2),
   ovd_prin_bal         DECIMAL(16,2),
   ovd_int_bal          DECIMAL(16,2),
   real_rate            DECIMAL(16,6),
   pnlt_rate            DECIMAL(16,6),
   int_amt              DECIMAL(16,2),
   ovd_prin_pnlt_amt    DECIMAL(16,2),
   ovd_int_pnlt_amt     DECIMAL(16,2),
   is_check_flag        CHAR(1),
   extend_param1        VARCHAR(100),
   extend_param2        VARCHAR(250),
   extend_param3        VARCHAR(40),
   constraint PK_ICPS_JB_LOAN_CALC primary key (busi_date, file_order)
);

comment on table ICPS_JB_LOAN_CALC is
'��Ϣ������ϸ�ļ�';

comment on column ICPS_JB_LOAN_CALC.busi_date is
'ҵ������';

comment on column ICPS_JB_LOAN_CALC.file_order is
'�ļ����';

comment on column ICPS_JB_LOAN_CALC.contract_no is
'����ƽ̨�����ͬ��';

comment on column ICPS_JB_LOAN_CALC.calc_date is
'��Ϣ���� YYYYMMDD';

comment on column ICPS_JB_LOAN_CALC.accrued_status is
'Ӧ�Ʒ�Ӧ�Ʊ�ʶ Ӧ��0����Ӧ��1';

comment on column ICPS_JB_LOAN_CALC.prin_bal is
'�����������';

comment on column ICPS_JB_LOAN_CALC.ovd_prin_bal is
'���ڱ������';

comment on column ICPS_JB_LOAN_CALC.ovd_int_bal is
'������Ϣ���';

comment on column ICPS_JB_LOAN_CALC.real_rate is
'����ʵ��������';

comment on column ICPS_JB_LOAN_CALC.pnlt_rate is
'���Ϣ������';

comment on column ICPS_JB_LOAN_CALC.int_amt is
'������Ϣ';

comment on column ICPS_JB_LOAN_CALC.ovd_prin_pnlt_amt is
'���ڱ���Ϣ';

comment on column ICPS_JB_LOAN_CALC.ovd_int_pnlt_amt is
'������Ϣ��Ϣ';

comment on column ICPS_JB_LOAN_CALC.is_check_flag is
'������˱�ʶ';

comment on column ICPS_JB_LOAN_CALC.extend_param1 is
'��չ1';

comment on column ICPS_JB_LOAN_CALC.extend_param2 is
'��չ2';

comment on column ICPS_JB_LOAN_CALC.extend_param3 is
'��չ3';


/*==============================================================*/
/* Table: ICPS_JB_ARG_STATUS_CHANGE                             */
/*==============================================================*/
create table ICPS_JB_ARG_STATUS_CHANGE 
(
   busi_date            CHAR(8)              not null,
   file_order           INTEGER              not null,
   contract_no          VARCHAR(32),
   settle_date          VARCHAR(8),
   status_seq_no        VARCHAR(64),
   event_code           VARCHAR(16),
   before_status        VARCHAR(10),
   after_status         VARCHAR(10),
   prin_amt             DECIMAL(16,2),
   int_amt              DECIMAL(16,2),
   ovd_prin_pnlt_amt    DECIMAL(16,2),
   ovd_int_pnlt_amt     DECIMAL(16,2),
   is_check_flag        CHAR(1),
   extend_param1        VARCHAR(100),
   extend_param2        VARCHAR(250),
   extend_param3        VARCHAR(40),
   constraint PK_ICPS_JB_ARG_STATUS_CHANGE primary key (busi_date, file_order)
);

comment on table ICPS_JB_ARG_STATUS_CHANGE is
'�����̬ת����ˮ�ļ�';

comment on column ICPS_JB_ARG_STATUS_CHANGE.busi_date is
'ҵ������';

comment on column ICPS_JB_ARG_STATUS_CHANGE.file_order is
'�ļ����';

comment on column ICPS_JB_ARG_STATUS_CHANGE.contract_no is
'����ƽ̨�����ͬ��';

comment on column ICPS_JB_ARG_STATUS_CHANGE.settle_date is
'�������';

comment on column ICPS_JB_ARG_STATUS_CHANGE.status_seq_no is
'״̬�仯��ˮ��';

comment on column ICPS_JB_ARG_STATUS_CHANGE.event_code is
'�¼��룬ת����11020007��ת��Ӧ��11020014��תӦ��11020015';

comment on column ICPS_JB_ARG_STATUS_CHANGE.before_status is
'���ת��ǰ״̬������Ӧ�ƣ� ��ȡֵΪNORMAL��Ӧ�Ʊ��ȡֵ��0��1��';

comment on column ICPS_JB_ARG_STATUS_CHANGE.after_status is
'���ת�ƺ�״̬������Ӧ�ƣ���ȡֵΪOVD��Ӧ�Ʊ��ȡֵΪ0��1��';

comment on column ICPS_JB_ARG_STATUS_CHANGE.prin_amt is
'��������';

comment on column ICPS_JB_ARG_STATUS_CHANGE.int_amt is
'��Ϣ������';

comment on column ICPS_JB_ARG_STATUS_CHANGE.ovd_prin_pnlt_amt is
'���ڱ���Ϣ������';

comment on column ICPS_JB_ARG_STATUS_CHANGE.ovd_int_pnlt_amt is
'������Ϣ��Ϣ������';

comment on column ICPS_JB_ARG_STATUS_CHANGE.is_check_flag is
'������˱�ʶ';

comment on column ICPS_JB_ARG_STATUS_CHANGE.extend_param1 is
'��չ1';

comment on column ICPS_JB_ARG_STATUS_CHANGE.extend_param2 is
'��չ2';

comment on column ICPS_JB_ARG_STATUS_CHANGE.extend_param3 is
'��չ3';


/*==============================================================*/
/* Table: ICPS_JB_FUND_DETAIL                                   */
/*==============================================================*/
create table ICPS_JB_FUND_DETAIL 
(
   busi_date            CHAR(8)              not null,
   file_order           INTEGER              not null,
   third_busi_serial    VARCHAR(64),
   third_busi_type      VARCHAR(32),
   trans_amt            DECIMAL(16,2),
   trans_refund_amt     DECIMAL(16,2),
   trans_dttm           VARCHAR(14),
   third_trans_name     VARCHAR(256),
   peer_org_name        VARCHAR(32),
   trans_sub_detail     VARCHAR(128),
   is_check_flag        CHAR(1),
   extend_param1        VARCHAR(100),
   extend_param2        VARCHAR(250),
   extend_param3        VARCHAR(40),
   constraint PK_ICPS_JB_FUND_DETAIL primary key (busi_date, file_order)
);

comment on table ICPS_JB_FUND_DETAIL is
'���������ʽ�����ļ�';

comment on column ICPS_JB_FUND_DETAIL.busi_date is
'ҵ������';

comment on column ICPS_JB_FUND_DETAIL.file_order is
'�ļ����';

comment on column ICPS_JB_FUND_DETAIL.third_busi_serial is
'�������н�����ˮ��';

comment on column ICPS_JB_FUND_DETAIL.third_busi_type is
'ҵ�����������P_DLGATE������P_WITHDRAW������շ��˻��Ƕ����ģ���P_FEE�������շѣ�';

comment on column ICPS_JB_FUND_DETAIL.trans_amt is
'���׽�� ����Ϊ����������Ϊ����';

comment on column ICPS_JB_FUND_DETAIL.trans_refund_amt is
'�����˿��� ����˽�����0������Ǵ����˿�';

comment on column ICPS_JB_FUND_DETAIL.trans_dttm is
'����ʱ�� YYYYMMDDHHMMSS';

comment on column ICPS_JB_FUND_DETAIL.third_trans_name is
'�������� ���գ�����';

comment on column ICPS_JB_FUND_DETAIL.peer_org_name is
'�Է���������';

comment on column ICPS_JB_FUND_DETAIL.trans_sub_detail is
'ҵ�񵥺�';

comment on column ICPS_JB_FUND_DETAIL.is_check_flag is
'������˱�ʶ';

comment on column ICPS_JB_FUND_DETAIL.extend_param1 is
'��չ1';

comment on column ICPS_JB_FUND_DETAIL.extend_param2 is
'��չ2';

comment on column ICPS_JB_FUND_DETAIL.extend_param3 is
'��չ3';
