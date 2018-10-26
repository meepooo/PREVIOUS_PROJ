drop table ICPS_APPLY;

drop table ICPS_PBOC_CREDIT;

drop table ICPS_ZM_CREDIT;

drop table ICPS_BANK_CREDIT;

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
/* Table: ICPS_APPLY                                            */
/*==============================================================*/
create table ICPS_APPLY 
(
   busi_no              VARCHAR(16)         not null,
   apply_no             VARCHAR(64)         not null,
   id_type              VARCHAR(2)          not null,
   id_num               VARCHAR(32)         not null,
   id_valid_end_date    VARCHAR(8),
   name                 VARCHAR(64)         not null,
   mobile_no            VARCHAR(32)         not null,
   auth_flag            CHAR(1),
   has_admit_flag       CHAR(1),
   apply_plt_date       CHAR(8),
   apply_plt_serial     VARCHAR(16),
   apply_status         CHAR(1),
   credit_no            VARCHAR(32),
   info_admit_flag      CHAR(1),
   credit_amt           DECIMAL(16,2),
   credit_rate          DECIMAL(16,6),
   refuse_code          VARCHAR(64),
   refuse_reason        VARCHAR(1024),
   info_plt_date        CHAR(8),
   info_plt_serial      VARCHAR(16),
   info_status          CHAR(1),
   third_access         CHAR(1),
   third_refuse_reason  VARCHAR(1024),
   third_amt            DECIMAL(16,2),
   third_rate           DECIMAL(16,6),
   risk_rating          CHAR(1),
   solvency_rating      CHAR(1),
   change_result_reason VARCHAR(1024),
   ack_admit_flag       CHAR(1),
   ack_admit_msg        VARCHAR(255),
   ack_plt_date         CHAR(8),
   ack_plt_serial       VARCHAR(16),
   ack_status           CHAR(1),
   extend_param1        VARCHAR(100),
   extend_param2        VARCHAR(250),
   extend_param3        VARCHAR(40),
   constraint PK_ICPS_APPLY primary key (busi_no, apply_no)
);

comment on table ICPS_APPLY is
'����������ˮ��';

comment on column ICPS_APPLY.busi_no is
'ҵ���� jiebei-���� jintiao-���� wbank-΢����';

comment on column ICPS_APPLY.apply_no is
'���뵥��';

comment on column ICPS_APPLY.id_type is
'֤������';

comment on column ICPS_APPLY.id_num is
'֤������';

comment on column ICPS_APPLY.id_valid_end_date is
'֤����Ч��';

comment on column ICPS_APPLY.name is
'����';

comment on column ICPS_APPLY.mobile_no is
'�ֻ���';

comment on column ICPS_APPLY.auth_flag is
'֥����Ȩ�ɹ���ʶ Y-��Ȩ�ɹ� N-��Ȩʧ��';

comment on column ICPS_APPLY.has_admit_flag is
'֮ǰ�Ƿ��ж�� Y-֮ǰ�ж�ȣ�N-֮ǰû�ж��';

comment on column ICPS_APPLY.apply_plt_date is
'��������ƽ̨����';

comment on column ICPS_APPLY.apply_plt_serial is
'��������ƽ̨��ˮ��';

comment on column ICPS_APPLY.apply_status is
'��������״̬ 0-�ɹ� 1-ʧ�� 6-δ֪ 9-��ʼ';

comment on column ICPS_APPLY.credit_no is
'���ű��';

comment on column ICPS_APPLY.info_admit_flag is
'�����Ƿ��Ƽ�׼�� Y-׼�� N-��׼��';

comment on column ICPS_APPLY.credit_amt is
'�Ƽ����';

comment on column ICPS_APPLY.credit_rate is
'�Ƽ�����';

comment on column ICPS_APPLY.refuse_code is
'�ܾ���';

comment on column ICPS_APPLY.refuse_reason is
'�ܾ�ԭ��';

comment on column ICPS_APPLY.info_plt_date is
'���г���ƽ̨����';

comment on column ICPS_APPLY.info_plt_serial is
'���г���ƽ̨��ˮ��';

comment on column ICPS_APPLY.info_status is
'����״̬ 0-�ɹ� 1-ʧ�� 6-δ֪ 9-��ʼ';

comment on column ICPS_APPLY.third_access is
'�Ƿ�ͨ������ Y-ͨ�� N-��ͨ��';

comment on column ICPS_APPLY.third_refuse_reason is
'������ͨ��ԭ��';

comment on column ICPS_APPLY.third_amt is
'�������';

comment on column ICPS_APPLY.third_rate is
'������������';

comment on column ICPS_APPLY.risk_rating is
'��������';

comment on column ICPS_APPLY.solvency_rating is
'��ծ��������';

comment on column ICPS_APPLY.change_result_reason is
'��ȶ��۱��ԭ��';

comment on column ICPS_APPLY.ack_admit_flag is
'���������Ƿ�׼�� Y-׼�� N-��׼��';

comment on column ICPS_APPLY.ack_admit_msg is
'׼��ԭ��';

comment on column ICPS_APPLY.ack_plt_date is
'����ƽ̨����';

comment on column ICPS_APPLY.ack_plt_serial is
'����ƽ̨��ˮ��';

comment on column ICPS_APPLY.ack_status is
'����״̬ 0-�ɹ� 1-ʧ�� 6-δ֪ 9-��ʼ';

comment on column ICPS_APPLY.extend_param1 is
'��չ1';

comment on column ICPS_APPLY.extend_param2 is
'��չ2';

comment on column ICPS_APPLY.extend_param3 is
'��չ3';


/*==============================================================*/
/* Table: ICPS_PBOC_CREDIT                                      */
/*==============================================================*/
create table ICPS_PBOC_CREDIT 
(
   apply_no             VARCHAR(64)         not null,
   plt_date             CHAR(8)              not null,
   plt_serial           VARCHAR(16)         not null,
   id_type              VARCHAR(2)          not null,
   id_num               VARCHAR(32)         not null,
   query_no             VARCHAR(64),
   query_flag           CHAR(1),
   manage_last_12_qry_cnt INTEGER,
   manage_last_3_qry_cnt INTEGER,
   manage_last_6_qry_cnt INTEGER,
   approve_last_12_qry_cnt INTEGER,
   approve_last_3_qry_cnt INTEGER,
   approve_last_6_qry_cnt INTEGER,
   approve_last_30d_qry_org_cnt INTEGER,
   approve_last_12_qry_org_cnt INTEGER,
   approve_last_3_qry_org_cnt INTEGER,
   approve_last_6_qry_org_cnt INTEGER,
   card_last_12_qry_cnt INTEGER,
   card_last_3_qry_cnt  INTEGER,
   card_last_6_qry_cnt  INTEGER,
   card_last_30d_qry_org_cnt INTEGER,
   card_last_3_qry_org_cnt INTEGER,
   card_last_6_qry_org_cnt INTEGER,
   all_loan_num         INTEGER,
   car_loan_num         INTEGER,
   biz_loan_num         INTEGER,
   house_loan_num       INTEGER,
   os_all_loan_num      INTEGER,
   os_car_loan_num      INTEGER,
   os_house_loan_num    INTEGER,
   os_biz_loan_num      INTEGER,
   ln_nca_con13_cnt_sum INTEGER,
   ln_nca_crd_cnt_sum   INTEGER,
   loan_max_amount      DECIMAL(16,2),
   loan_oper_max_amount DECIMAL(16,2),
   balance_sum          DECIMAL(16,2),
   loan_sum_amount      DECIMAL(16,2),
   ln_nca_amt_avg       DECIMAL(16,2),
   loan_house_amt_sum   DECIMAL(16,2),
   loan_house_bal_sum   DECIMAL(16,2),
   business_loan_sum_amount DECIMAL(16,2),
   business_loan_sum_balance DECIMAL(16,2),
   ln_nca_con13_bal_sum DECIMAL(16,2),
   ln_nca_rmm_avg       INTEGER,
   ln_nca_pmm_avg       INTEGER,
   ln_nca_pmo_avg       DECIMAL(16,2),
   ln_nca_pmt_sum       DECIMAL(16,2),
   repay_car_mon        DECIMAL(16,2),
   repay_house_mon      DECIMAL(16,2),
   ln_nca_m1_max_3m     INTEGER,
   loan_ovd_max_bal_cpt DECIMAL(16,2),
   loan_cur_ovd_amount  DECIMAL(16,2),
   ln_cd_max_24m        INTEGER,
   ln_cd_max            INTEGER,
   loan_delq_12mth_max  INTEGER,
   loan_delq_3mth_max   INTEGER,
   loan_delq_6mth_max   INTEGER,
   class_5_credit_mortgage CHAR(1),
   class_5_not_mortgage CHAR(1),
   dull_loan_num        INTEGER,
   dull_loan_sum        DECIMAL(16,2),
   all_assure_loan_num  INTEGER,
   all_assure_loan_sum  DECIMAL(16,2),
   cont_under_attention_assure INTEGER,
   cont_under_secondary_assure DECIMAL(16,2),
   assure_under_attention_amt DECIMAL(16,2),
   as_cv2_bal_sum       DECIMAL(16,2),
   card_amt_sum         DECIMAL(16,2),
   cc_act_lmt_max       DECIMAL(16,2),
   ac_nml_lmt_avg       DECIMAL(16,2),
   ac_nml_lmt_sum       DECIMAL(16,2),
   card_issue_org_cnt   INTEGER,
   card_rmb_cnt         INTEGER,
   cc_cnt_sum           INTEGER,
   cc_nca_cnt_sum       INTEGER,
   normal_num           INTEGER,
   all_card_cnt         INTEGER,
   cc_act_cu_o90_pct    DECIMAL(16,5),
   cc_nca_cu_min        DECIMAL(16,5),
   cc_nca_mu_max        DECIMAL(16,5),
   card_nca_hb_max      DECIMAL(16,2),
   ac_nca_cu_avg        DECIMAL(16,5),
   ac_nca_hb_max        DECIMAL(16,2),
   cc_nml_mu_avg        DECIMAL(16,5),
   all_card_cur_ovd_used DECIMAL(16,5),
   card_nca_pmo_sum     DECIMAL(16,2),
   card_delq_6mth_max_cnt INTEGER,
   card_delq_12mth_max_cnt INTEGER,
   card_delq_3mth_max_cnt INTEGER,
   card_max_ovd_bal     DECIMAL(16,2),
   all_card_cur_ovd_amt_sum DECIMAL(16,2),
   cont_dull_card_cnt   INTEGER,
   dull_scard_cnt       INTEGER,
   ac_abn_cnt_sum       INTEGER,
   cc_act_m1_cnt_3m     INTEGER,
   cc_act_m1_cnt_pct_3m DECIMAL(16,5),
   cc_act_m1_cnt_pct_6m DECIMAL(16,5),
   ac_nca_cd_max        INTEGER,
   cc_cd_max_24m        INTEGER,
   card_delq_12mth_max  INTEGER,
   card_delq_3mth_max   INTEGER,
   card_delq_6mth_max   INTEGER,
   qc_act_cd_max_24m    INTEGER,
   scard_delq_12mth_max INTEGER,
   scard_delq_3mth_max  INTEGER,
   scard_delq_6mth_max  INTEGER,
   credit_opm_max       INTEGER,
   ac_opm_max           INTEGER,
   extend_param1        VARCHAR(100),
   extend_param2        VARCHAR(250),
   extend_param3        VARCHAR(40),
   constraint PK_ICPS_PBOC_CREDIT primary key (apply_no)
);

comment on table ICPS_PBOC_CREDIT is
'����������Ϣ��';

comment on column ICPS_PBOC_CREDIT.apply_no is
'���뵥��';

comment on column ICPS_PBOC_CREDIT.plt_date is
'ƽ̨����';

comment on column ICPS_PBOC_CREDIT.plt_serial is
'ƽ̨��ˮ��';

comment on column ICPS_PBOC_CREDIT.id_type is
'֤������';

comment on column ICPS_PBOC_CREDIT.id_num is
'֤������';

comment on column ICPS_PBOC_CREDIT.query_no is
'��ѯ���';

comment on column ICPS_PBOC_CREDIT.query_flag is
'��ѯ��� 1���в�ѯ�Ҳ鵽���棻0���в�ѯ�����޴���';

comment on column ICPS_PBOC_CREDIT.manage_last_12_qry_cnt is
'��ѯ-����������12���²�ѯ����';

comment on column ICPS_PBOC_CREDIT.manage_last_3_qry_cnt is
'��ѯ-����������3���²�ѯ����';

comment on column ICPS_PBOC_CREDIT.manage_last_6_qry_cnt is
'��ѯ-����������6���²�ѯ����';

comment on column ICPS_PBOC_CREDIT.approve_last_12_qry_cnt is
'��ѯ-�������������12���²�ѯ����';

comment on column ICPS_PBOC_CREDIT.approve_last_3_qry_cnt is
'��ѯ-�������������3���²�ѯ����';

comment on column ICPS_PBOC_CREDIT.approve_last_6_qry_cnt is
'��ѯ-�������������6���²�ѯ����';

comment on column ICPS_PBOC_CREDIT.approve_last_30d_qry_org_cnt is
'��ѯ-�������������1���²�ѯ������';

comment on column ICPS_PBOC_CREDIT.approve_last_12_qry_org_cnt is
'��ѯ-�������������12���²�ѯ������';

comment on column ICPS_PBOC_CREDIT.approve_last_3_qry_org_cnt is
'��ѯ-�������������3���²�ѯ������';

comment on column ICPS_PBOC_CREDIT.approve_last_6_qry_org_cnt is
'��ѯ-�������������6���²�ѯ������';

comment on column ICPS_PBOC_CREDIT.card_last_12_qry_cnt is
'��ѯ-���ÿ����������12���²�ѯ����';

comment on column ICPS_PBOC_CREDIT.card_last_3_qry_cnt is
'��ѯ-���ÿ����������3���²�ѯ����';

comment on column ICPS_PBOC_CREDIT.card_last_6_qry_cnt is
'��ѯ-���ÿ����������6���²�ѯ����';

comment on column ICPS_PBOC_CREDIT.card_last_30d_qry_org_cnt is
'��ѯ-���ÿ����������1���²�ѯ����';

comment on column ICPS_PBOC_CREDIT.card_last_3_qry_org_cnt is
'��ѯ-���ÿ����������3���²�ѯ������';

comment on column ICPS_PBOC_CREDIT.card_last_6_qry_org_cnt is
'��ѯ-���ÿ����������6���²�ѯ������';

comment on column ICPS_PBOC_CREDIT.all_loan_num is
'�ܴ����������������״̬��';

comment on column ICPS_PBOC_CREDIT.car_loan_num is
'��������';

comment on column ICPS_PBOC_CREDIT.biz_loan_num is
'��Ӫ�������';

comment on column ICPS_PBOC_CREDIT.house_loan_num is
'��������';

comment on column ICPS_PBOC_CREDIT.os_all_loan_num is
'δ����������ʻ������ܱ���';

comment on column ICPS_PBOC_CREDIT.os_car_loan_num is
'δ���峵������';

comment on column ICPS_PBOC_CREDIT.os_house_loan_num is
'δ���巿������';

comment on column ICPS_PBOC_CREDIT.os_biz_loan_num is
'δ���徭Ӫ�������';

comment on column ICPS_PBOC_CREDIT.ln_nca_con13_cnt_sum is
'δ�������Ѵ����ͳ�Ƹ������Ѵ������';

comment on column ICPS_PBOC_CREDIT.ln_nca_crd_cnt_sum is
'δ�������ô������';

comment on column ICPS_PBOC_CREDIT.loan_max_amount is
'������߶��';

comment on column ICPS_PBOC_CREDIT.loan_oper_max_amount is
'��Ӫ�Դ�����߶��';

comment on column ICPS_PBOC_CREDIT.balance_sum is
'δ������������ܺ�';

comment on column ICPS_PBOC_CREDIT.loan_sum_amount is
'δ����������ܺ�';

comment on column ICPS_PBOC_CREDIT.ln_nca_amt_avg is
'δ�������ƽ����ͬ���';

comment on column ICPS_PBOC_CREDIT.loan_house_amt_sum is
'δ���巿����ͬ���';

comment on column ICPS_PBOC_CREDIT.loan_house_bal_sum is
'δ���巿�����';

comment on column ICPS_PBOC_CREDIT.business_loan_sum_amount is
'δ���徭Ӫ�����ͬ���';

comment on column ICPS_PBOC_CREDIT.business_loan_sum_balance is
'δ���徭Ӫ�������';

comment on column ICPS_PBOC_CREDIT.ln_nca_con13_bal_sum is
'δ�������Ѵ����ͳ�Ƹ������Ѵ�����';

comment on column ICPS_PBOC_CREDIT.ln_nca_rmm_avg is
'δ�������ƽ��ʣ�໹������';

comment on column ICPS_PBOC_CREDIT.ln_nca_pmm_avg is
'δ�������ƽ����������';

comment on column ICPS_PBOC_CREDIT.ln_nca_pmo_avg is
'����δ�������ƽ��Ӧ����';

comment on column ICPS_PBOC_CREDIT.ln_nca_pmt_sum is
'δ����������ʵ����';

comment on column ICPS_PBOC_CREDIT.repay_car_mon is
'�¶ȳ�������Ӧ����';

comment on column ICPS_PBOC_CREDIT.repay_house_mon is
'�¶ȷ�������Ӧ����';

comment on column ICPS_PBOC_CREDIT.ln_nca_m1_max_3m is
'δ��������3����������ڴ���';

comment on column ICPS_PBOC_CREDIT.loan_ovd_max_bal_cpt is
'�����������ڽ��';

comment on column ICPS_PBOC_CREDIT.loan_cur_ovd_amount is
'���ǰ�����ܽ��';

comment on column ICPS_PBOC_CREDIT.ln_cd_max_24m is
'�����24���������������';

comment on column ICPS_PBOC_CREDIT.ln_cd_max is
'��ǰ���������������';

comment on column ICPS_PBOC_CREDIT.loan_delq_12mth_max is
'δ��������12���������������';

comment on column ICPS_PBOC_CREDIT.loan_delq_3mth_max is
'δ��������3���������������';

comment on column ICPS_PBOC_CREDIT.loan_delq_6mth_max is
'δ��������6���������������';

comment on column ICPS_PBOC_CREDIT.class_5_credit_mortgage is
'���������������������弶���� 1-���� 2-��ע 3-�μ� 4-���� 5-��ʧ 6-δ֪';

comment on column ICPS_PBOC_CREDIT.class_5_not_mortgage is
'�ǰ��������������������弶���� 1-���� 2-��ע 3-�μ� 4-���� 5-��ʧ 6-δ֪';

comment on column ICPS_PBOC_CREDIT.dull_loan_num is
'�������ô������';

comment on column ICPS_PBOC_CREDIT.dull_loan_sum is
'���˵Ĵ�����';

comment on column ICPS_PBOC_CREDIT.all_assure_loan_num is
'�ܵ�������';

comment on column ICPS_PBOC_CREDIT.all_assure_loan_sum is
'�ܵ������';

comment on column ICPS_PBOC_CREDIT.cont_under_attention_assure is
'���ⵣ���弶�����ע�����ϱ���';

comment on column ICPS_PBOC_CREDIT.cont_under_secondary_assure is
'������״̬Ϊ���μ��������ϵĵ���������';

comment on column ICPS_PBOC_CREDIT.assure_under_attention_amt is
'������״̬Ϊ����ע�������ϵĵ���������';

comment on column ICPS_PBOC_CREDIT.as_cv2_bal_sum is
'���ⵣ���弶�����ע���������';

comment on column ICPS_PBOC_CREDIT.card_amt_sum is
'���ⵣ���弶�����ע������������δ�������ÿ�������Ŷ��';

comment on column ICPS_PBOC_CREDIT.cc_act_lmt_max is
'������δ�������ÿ�������Ŷ��';

comment on column ICPS_PBOC_CREDIT.ac_nml_lmt_avg is
'����״̬��ƽ�����';

comment on column ICPS_PBOC_CREDIT.ac_nml_lmt_sum is
'����״̬���ܶ��';

comment on column ICPS_PBOC_CREDIT.card_issue_org_cnt is
'����״̬����������';

comment on column ICPS_PBOC_CREDIT.card_rmb_cnt is
'��ǰ������δ��������Ҵ��ǿ���';

comment on column ICPS_PBOC_CREDIT.cc_cnt_sum is
'����δ�������ǿ���';

comment on column ICPS_PBOC_CREDIT.cc_nca_cnt_sum is
'δ�������ǿ���';

comment on column ICPS_PBOC_CREDIT.normal_num is
'����״̬���ǿ���';

comment on column ICPS_PBOC_CREDIT.all_card_cnt is
'�ܿ��������ǿ�+׼���ǿ�����������״̬��';

comment on column ICPS_PBOC_CREDIT.cc_act_cu_o90_pct is
'������δ�������ǿ���ǰʹ���ʴ��ڵ���90%ռ����δ�������ǿ�����';

comment on column ICPS_PBOC_CREDIT.cc_nca_cu_min is
'δ�������ǿ���ǰ��Сʹ����';

comment on column ICPS_PBOC_CREDIT.cc_nca_mu_max is
'δ�������ǿ����6����ƽ��ʹ����';

comment on column ICPS_PBOC_CREDIT.card_nca_hb_max is
'δ�������ǿ����ʹ�ö��';

comment on column ICPS_PBOC_CREDIT.ac_nca_cu_avg is
'δ��������ǰƽ��ʹ����';

comment on column ICPS_PBOC_CREDIT.ac_nca_hb_max is
'δ���������ʹ�ö��';

comment on column ICPS_PBOC_CREDIT.cc_nml_mu_avg is
'����״̬���ǿ�6����ƽ��ʹ����';

comment on column ICPS_PBOC_CREDIT.all_card_cur_ovd_used is
'����״̬����ǰƽ��ʹ����';

comment on column ICPS_PBOC_CREDIT.card_nca_pmo_sum is
'����δ�������ǿ���Ӧ�����ܶ�';

comment on column ICPS_PBOC_CREDIT.card_delq_6mth_max_cnt is
'δ�������ǿ���6����������ڴ���';

comment on column ICPS_PBOC_CREDIT.card_delq_12mth_max_cnt is
'δ�������ǿ���12����������ڴ���';

comment on column ICPS_PBOC_CREDIT.card_delq_3mth_max_cnt is
'δ�������ǿ���3����������ڴ���';

comment on column ICPS_PBOC_CREDIT.card_max_ovd_bal is
'���ǿ�����������ڽ��';

comment on column ICPS_PBOC_CREDIT.all_card_cur_ovd_amt_sum is
'δ��������ǰ�����ڽ��';

comment on column ICPS_PBOC_CREDIT.cont_dull_card_cnt is
'���˵Ĵ��ǿ���';

comment on column ICPS_PBOC_CREDIT.dull_scard_cnt is
'���˵�׼���ǿ���';

comment on column ICPS_PBOC_CREDIT.ac_abn_cnt_sum is
'���ǿ�Ϊ���ʡ����ᡢֹ������';

comment on column ICPS_PBOC_CREDIT.cc_act_m1_cnt_3m is
'����δ�������ǿ�����3����1�ڼ��������ڿ���';

comment on column ICPS_PBOC_CREDIT.cc_act_m1_cnt_pct_3m is
'����δ�������ǿ�����3����1�ڼ��������ڿ���ռ��';

comment on column ICPS_PBOC_CREDIT.cc_act_m1_cnt_pct_6m is
'����δ�������ǿ�����6����1�ڼ��������ڿ���ռ��';

comment on column ICPS_PBOC_CREDIT.ac_nca_cd_max is
'δ��������ǰ�����������';

comment on column ICPS_PBOC_CREDIT.cc_cd_max_24m is
'���ǿ���24���������������';

comment on column ICPS_PBOC_CREDIT.card_delq_12mth_max is
'���ǿ�δ�����˻��У���ȥ12���������������';

comment on column ICPS_PBOC_CREDIT.card_delq_3mth_max is
'���ǿ�δ�����˻��У���ȥ3���������������';

comment on column ICPS_PBOC_CREDIT.card_delq_6mth_max is
'���ǿ�δ�����˻��У���ȥ6���������������';

comment on column ICPS_PBOC_CREDIT.qc_act_cd_max_24m is
'׼��������24���������������';

comment on column ICPS_PBOC_CREDIT.scard_delq_12mth_max is
'׼������δ�����˻��У���ȥ12���������������';

comment on column ICPS_PBOC_CREDIT.scard_delq_3mth_max is
'׼������δ�����˻��У���ȥ3���������������';

comment on column ICPS_PBOC_CREDIT.scard_delq_6mth_max is
'׼������δ�����˻��У���ȥ6���������������';

comment on column ICPS_PBOC_CREDIT.credit_opm_max is
'������ʷ(���翪������ѯ�����������������ѯ����ȡ���)';

comment on column ICPS_PBOC_CREDIT.ac_opm_max is
'��󿪿�����';

comment on column ICPS_PBOC_CREDIT.extend_param1 is
'��չ1';

comment on column ICPS_PBOC_CREDIT.extend_param2 is
'��չ2';

comment on column ICPS_PBOC_CREDIT.extend_param3 is
'��չ3';


/*==============================================================*/
/* Table: ICPS_ZM_CREDIT                                        */
/*==============================================================*/
create table ICPS_ZM_CREDIT 
(
   apply_no             VARCHAR(64)         not null,
   plt_date             CHAR(8)              not null,
   plt_serial           VARCHAR(16)         not null,
   id_type              VARCHAR(2)          not null,
   id_num               VARCHAR(32)         not null,
   company_name         VARCHAR(255),
   occupation           VARCHAR(64),
   have_car_flag        CHAR(1),
   have_house_flag      CHAR(1),
   auth_fin_last_1m_cnt INTEGER,
   auth_fin_last_3m_cnt INTEGER,
   auth_fin_last_6m_cnt INTEGER,
   ovd_order_cnt_6m     INTEGER,
   ovd_order_amt_6m     DECIMAL(16,2),
   mobile_fixed_days    INTEGER,
   adr_stability_days   INTEGER,
   last_6m_avg_asset_total DECIMAL(16,2),
   tot_pay_amt_6m       DECIMAL(16,2),
   xfdc_index           VARCHAR(64),
   positive_biz_cnt_1y  INTEGER,
   extend_param1        VARCHAR(100),
   extend_param2        VARCHAR(250),
   extend_param3        VARCHAR(40),
   constraint PK_ICPS_ZM_CREDIT primary key (apply_no)
);

comment on table ICPS_ZM_CREDIT is
'֥��������Ϣ��';

comment on column ICPS_ZM_CREDIT.apply_no is
'���뵥��';

comment on column ICPS_ZM_CREDIT.plt_date is
'ƽ̨����';

comment on column ICPS_ZM_CREDIT.plt_serial is
'ƽ̨��ˮ��';

comment on column ICPS_ZM_CREDIT.id_type is
'֤������';

comment on column ICPS_ZM_CREDIT.id_num is
'֤������';

comment on column ICPS_ZM_CREDIT.company_name is
'���ڹ�˾';

comment on column ICPS_ZM_CREDIT.occupation is
'ְҵ����';

comment on column ICPS_ZM_CREDIT.have_car_flag is
'�Ƿ��г�';

comment on column ICPS_ZM_CREDIT.have_house_flag is
'�Ƿ��з�';

comment on column ICPS_ZM_CREDIT.auth_fin_last_1m_cnt is
'���һ����������ѯ���ڻ�����';

comment on column ICPS_ZM_CREDIT.auth_fin_last_3m_cnt is
'���������������ѯ���ڻ�����';

comment on column ICPS_ZM_CREDIT.auth_fin_last_6m_cnt is
'���������������ѯ���ڻ�����';

comment on column ICPS_ZM_CREDIT.ovd_order_cnt_6m is
'��������������ܱ���';

comment on column ICPS_ZM_CREDIT.ovd_order_amt_6m is
'��������������ܽ��';

comment on column ICPS_ZM_CREDIT.mobile_fixed_days is
'�ֻ����ȶ�����';

comment on column ICPS_ZM_CREDIT.adr_stability_days is
'��ַ�ȶ�����';

comment on column ICPS_ZM_CREDIT.last_6m_avg_asset_total is
'��������������ʲ��վ�ֵ';

comment on column ICPS_ZM_CREDIT.tot_pay_amt_6m is
'���������֧���ܽ��';

comment on column ICPS_ZM_CREDIT.xfdc_index is
'���ѵ���';

comment on column ICPS_ZM_CREDIT.positive_biz_cnt_1y is
'���һ����Լ������';

comment on column ICPS_ZM_CREDIT.extend_param1 is
'��չ1';

comment on column ICPS_ZM_CREDIT.extend_param2 is
'��չ2';

comment on column ICPS_ZM_CREDIT.extend_param3 is
'��չ3';


/*==============================================================*/
/* Table: ICPS_BANK_CREDIT                                      */
/*==============================================================*/
create table ICPS_BANK_CREDIT 
(
   apply_no             VARCHAR(64)         not null,
   plt_date             CHAR(8)              not null,
   plt_serial           VARCHAR(16)         not null,
   id_type              VARCHAR(2)          not null,
   id_num               VARCHAR(32)         not null,
   is_exist_customer    CHAR(1),
   is_exist_debt_customer CHAR(1),
   balance              DECIMAL(16,2),
   avg_balance_last_3days DECIMAL(16,2),
   avg_balance_last_6days DECIMAL(16,2),
   income_last_3m       DECIMAL(16,2),
   pay_last_3m          DECIMAL(16,2),
   income_last_6m       DECIMAL(16,2),
   pay_last_6m          DECIMAL(16,2),
   is_exist_credit_customer CHAR(1),
   curr_credit_card_amt DECIMAL(16,2),
   curr_use_credit_card_amt DECIMAL(16,2),
   is_exist_fin_customer CHAR(1),
   fin_balance          DECIMAL(16,2),
   avg_fin_bal_last_6m  DECIMAL(16,2),
   is_exist_insurance_customer CHAR(1),
   is_exist_loan_customer CHAR(1),
   operation_loan_bal   DECIMAL(16,2),
   personal_credit_bal  DECIMAL(16,2),
   car_loan_bal         DECIMAL(16,2),
   car_asset            DECIMAL(16,2),
   house_loan_bal       DECIMAL(16,2),
   house_asset          DECIMAL(16,2),
   is_stock_customer    CHAR(1),
   is_third_depository  CHAR(1),
   is_payroll_customer  CHAR(1),
   is_social_security_customer CHAR(1),
   is_life_payment_customer CHAR(1),
   company_name         VARCHAR(255),
   company_origin       CHAR(1),
   position             VARCHAR(64),
   position_origin      CHAR(1),
   industry             VARCHAR(64),
   industry_origin      CHAR(1),
   work_years           INTEGER,
   work_years_origin    CHAR(1),
   income               INTEGER,
   income_origin        CHAR(1),
   marriage_status      CHAR(1),
   marriage_origin      CHAR(1),
   is_operation         CHAR(1),
   operation_origin     CHAR(1),
   is_inner_black_customer CHAR(1),
   is_police_certified  CHAR(1),
   is_court_exec_customer CHAR(1),
   is_query_house_fund  CHAR(1),
   fund_query_date      CHAR(6),
   fund_month_amt       DECIMAL(16,2),
   fund_acct_date       CHAR(6),
   fund_months_last_6m  INTEGER,
   fund_amt_last_6m     DECIMAL(16,2),
   fund_total_months    INTEGER,
   fund_total_amt       DECIMAL(16,2),
   fund_max_amt         DECIMAL(16,2),
   is_query_social_security CHAR(1),
   social_query_date    CHAR(6),
   pension_query_month_amt DECIMAL(16,2),
   pension_acct_date    CHAR(6),
   pension_months_last_6m INTEGER,
   pension_amt_last_6m  DECIMAL(16,2),
   pension_total_months INTEGER,
   pension_total_amt    DECIMAL(16,2),
   medicare_month_amt   DECIMAL(16,2),
   medicare_acct_date   CHAR(6),
   medicare_months_last_6m INTEGER,
   medicare_amt_last_6m DECIMAL(16,2),
   medicare_total_months INTEGER,
   medicare_total_amt   DECIMAL(16,2),
   is_query_degree      CHAR(1),
   school_name          VARCHAR(64),
   degree_level         VARCHAR(64),
   degree_type          VARCHAR(64),
   entrance_year        CHAR(4),
   is_query_communication CHAR(1),
   communication        CHAR(1),
   online_days          INTEGER,
   total_tel_fare       DECIMAL(16,2),
   total_call_hours     INTEGER,
   is_out_black_customer CHAR(1),
   extend_param1        VARCHAR(100),
   extend_param2        VARCHAR(250),
   extend_param3        VARCHAR(40),
   constraint PK_ICPS_BANK_CREDIT primary key (apply_no)
);

comment on table ICPS_BANK_CREDIT is
'����������Ϣ';

comment on column ICPS_BANK_CREDIT.apply_no is
'���뵥��';

comment on column ICPS_BANK_CREDIT.plt_date is
'ƽ̨����';

comment on column ICPS_BANK_CREDIT.plt_serial is
'ƽ̨��ˮ��';

comment on column ICPS_BANK_CREDIT.id_type is
'֤������';

comment on column ICPS_BANK_CREDIT.id_num is
'֤������';

comment on column ICPS_BANK_CREDIT.is_exist_customer is
'�Ƿ�����ͻ� 1-�� 0-��';

comment on column ICPS_BANK_CREDIT.is_exist_debt_customer is
'�Ƿ������ǿ��ͻ� 1-�� 0-��';

comment on column ICPS_BANK_CREDIT.balance is
'�������';

comment on column ICPS_BANK_CREDIT.avg_balance_last_3days is
'��3�����վ����';

comment on column ICPS_BANK_CREDIT.avg_balance_last_6days is
'��6�����վ����';

comment on column ICPS_BANK_CREDIT.income_last_3m is
'��3����������ˮ��������';

comment on column ICPS_BANK_CREDIT.pay_last_3m is
'��3����������ˮ֧�������';

comment on column ICPS_BANK_CREDIT.income_last_6m is
'��6����������ˮ��������';

comment on column ICPS_BANK_CREDIT.pay_last_6m is
'��6����������ˮ֧�������';

comment on column ICPS_BANK_CREDIT.is_exist_credit_customer is
'�Ƿ�������ÿ��ͻ� 1-�� 0-��';

comment on column ICPS_BANK_CREDIT.curr_credit_card_amt is
'�������ÿ����Ŷ��';

comment on column ICPS_BANK_CREDIT.curr_use_credit_card_amt is
'�������ÿ���ǰʹ�ö��';

comment on column ICPS_BANK_CREDIT.is_exist_fin_customer is
'�Ƿ������ƿͻ� 1-�� 0-��';

comment on column ICPS_BANK_CREDIT.fin_balance is
'������';

comment on column ICPS_BANK_CREDIT.avg_fin_bal_last_6m is
'��6�����վ������';

comment on column ICPS_BANK_CREDIT.is_exist_insurance_customer is
'�Ƿ�������տͻ� 1-�� 0-��';

comment on column ICPS_BANK_CREDIT.is_exist_loan_customer is
'�Ƿ��������ͻ� 1-�� 0-��';

comment on column ICPS_BANK_CREDIT.operation_loan_bal is
'��Ӫ����������';

comment on column ICPS_BANK_CREDIT.personal_credit_bal is
'����������������';

comment on column ICPS_BANK_CREDIT.car_loan_bal is
'�������';

comment on column ICPS_BANK_CREDIT.car_asset is
'������ֵ������';

comment on column ICPS_BANK_CREDIT.house_loan_bal is
'�������';

comment on column ICPS_BANK_CREDIT.house_asset is
'������ֵ������';

comment on column ICPS_BANK_CREDIT.is_stock_customer is
'�Ƿ�֤ȯ�ͻ� 1-�� 0-��';

comment on column ICPS_BANK_CREDIT.is_third_depository is
'�Ƿ��������ܿͻ� 1-�� 0-��';

comment on column ICPS_BANK_CREDIT.is_payroll_customer is
'�Ƿ��ʴ����ͻ� 1-�� 0-��';

comment on column ICPS_BANK_CREDIT.is_social_security_customer is
'�Ƿ��籣���ɿͻ� 1-�� 0-��';

comment on column ICPS_BANK_CREDIT.is_life_payment_customer is
'�Ƿ�ˮ��ú���ɿͻ� 1-�� 0-��';

comment on column ICPS_BANK_CREDIT.company_name is
'������λ';

comment on column ICPS_BANK_CREDIT.company_origin is
'������λ������Դ 1-��ʵ 2-�ͻ���д 3-����';

comment on column ICPS_BANK_CREDIT.position is
'ְλ';

comment on column ICPS_BANK_CREDIT.position_origin is
'ְλ��Ϣ��Դ 1-��ʵ 2-�ͻ���д 3-����';

comment on column ICPS_BANK_CREDIT.industry is
'��ҵ';

comment on column ICPS_BANK_CREDIT.industry_origin is
'��ҵ��Ϣ��Դ 1-��ʵ 2-�ͻ���д 3-����';

comment on column ICPS_BANK_CREDIT.work_years is
'��������';

comment on column ICPS_BANK_CREDIT.work_years_origin is
'����������Ϣ ��Դ 1-��ʵ 2-�ͻ���д 3-����';

comment on column ICPS_BANK_CREDIT.income is
'����������';

comment on column ICPS_BANK_CREDIT.income_origin is
'��������Ϣ��Դ 1-��ʵ 2-�ͻ���д 3-����';

comment on column ICPS_BANK_CREDIT.marriage_status is
'����״̬ 1-δ�� 2-�ѻ� 3-��� 4-ɥż NULL-����';

comment on column ICPS_BANK_CREDIT.marriage_origin is
'����״̬��Ϣ��Դ 1-��ʵ 2-�ͻ���д 3-����';

comment on column ICPS_BANK_CREDIT.is_operation is
'�Ƿ�Ӫ�� ��������ҵ����幤����ҵ����1-�� 0-��';

comment on column ICPS_BANK_CREDIT.operation_origin is
'�Ƿ�Ӫ����Ϣ��Դ 1-��ʵ 2-�ͻ���д 3-����';

comment on column ICPS_BANK_CREDIT.is_inner_black_customer is
'�Ƿ�����ڲ��������ͻ� 1-�� 0-��';

comment on column ICPS_BANK_CREDIT.is_police_certified is
'�Ƿ񹫰��������֤�ɹ� 1- �� 0-��';

comment on column ICPS_BANK_CREDIT.is_court_exec_customer is
'�Ƿ���б�ִ���˵�������Ϣ 1-�� 0-��';

comment on column ICPS_BANK_CREDIT.is_query_house_fund is
'�Ƿ��в�ѯ��������Ϣ 1-�� 0-�� ';

comment on column ICPS_BANK_CREDIT.fund_query_date is
'�������ѯʱ�� YYYYMM';

comment on column ICPS_BANK_CREDIT.fund_month_amt is
'�������ѯ�½��ɶ�';

comment on column ICPS_BANK_CREDIT.fund_acct_date is
'�����𿪻����� YYYYMM';

comment on column ICPS_BANK_CREDIT.fund_months_last_6m is
'��6�����ۼƽ�������';

comment on column ICPS_BANK_CREDIT.fund_amt_last_6m is
'��6�����ۼƽ��ɽ��';

comment on column ICPS_BANK_CREDIT.fund_total_months is
'�ܽ�������';

comment on column ICPS_BANK_CREDIT.fund_total_amt is
'�ܽ��ɽ��';

comment on column ICPS_BANK_CREDIT.fund_max_amt is
'���������ؽ�������';

comment on column ICPS_BANK_CREDIT.is_query_social_security is
'�Ƿ��в�ѯ�籣��Ϣ 1-�� 0-�� ';

comment on column ICPS_BANK_CREDIT.social_query_date is
'�籣��Ϣ��ѯʱ�� YYYYMM';

comment on column ICPS_BANK_CREDIT.pension_query_month_amt is
'���ϱ��ղ�ѯ�½��ɶ�';

comment on column ICPS_BANK_CREDIT.pension_acct_date is
'���ϱ��տ������� YYYYMM';

comment on column ICPS_BANK_CREDIT.pension_months_last_6m is
'��6�������ϱ����ۼƽ�������';

comment on column ICPS_BANK_CREDIT.pension_amt_last_6m is
'��6�������ϱ����ۼƽ��ɽ��';

comment on column ICPS_BANK_CREDIT.pension_total_months is
'���ϱ����ܽ�������';

comment on column ICPS_BANK_CREDIT.pension_total_amt is
'���ϱ����ܽ��ɽ��';

comment on column ICPS_BANK_CREDIT.medicare_month_amt is
'ҽ�Ʊ��ղ�ѯ�½��ɶ�';

comment on column ICPS_BANK_CREDIT.medicare_acct_date is
'ҽ�Ʊ��տ������� YYYYMM';

comment on column ICPS_BANK_CREDIT.medicare_months_last_6m is
'��6����ҽ�Ʊ����ۼƽ�������';

comment on column ICPS_BANK_CREDIT.medicare_amt_last_6m is
'��6����ҽ�Ʊ����ۼƽ��ɽ��';

comment on column ICPS_BANK_CREDIT.medicare_total_months is
'ҽ�Ʊ����ܽ�������';

comment on column ICPS_BANK_CREDIT.medicare_total_amt is
'ҽ�Ʊ����ܽ��ɽ��';

comment on column ICPS_BANK_CREDIT.is_query_degree is
'�Ƿ��в�ѯѧ����Ϣ 1-�� 0-�� ';

comment on column ICPS_BANK_CREDIT.school_name is
'ԺУ����';

comment on column ICPS_BANK_CREDIT.degree_level is
'ѧ����� ���м����£�ר�ƣ�ѧʿ��˶ʿ����ʿ������';

comment on column ICPS_BANK_CREDIT.degree_type is
'ѧ�����';

comment on column ICPS_BANK_CREDIT.entrance_year is
'��ѧ��� YYYY';

comment on column ICPS_BANK_CREDIT.is_query_communication is
'�Ƿ��в�ѯ��Ӫ����Ϣ 1-�� 0-�� ';

comment on column ICPS_BANK_CREDIT.communication is
'��Ӫ�� 1-�ƶ� 2-��ͨ 3-���� 4-����';

comment on column ICPS_BANK_CREDIT.online_days is
'����ʱ��';

comment on column ICPS_BANK_CREDIT.total_tel_fare is
'�ܻ����˵����';

comment on column ICPS_BANK_CREDIT.total_call_hours is
'������ͨ��ʱ�� ��Сʱ����ȡ��';

comment on column ICPS_BANK_CREDIT.is_out_black_customer is
'�Ƿ�����ⲿ��ѯ������ 1-�� 0-�� ';

comment on column ICPS_BANK_CREDIT.extend_param1 is
'��չ1';

comment on column ICPS_BANK_CREDIT.extend_param2 is
'��չ2';

comment on column ICPS_BANK_CREDIT.extend_param3 is
'��չ3';


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
