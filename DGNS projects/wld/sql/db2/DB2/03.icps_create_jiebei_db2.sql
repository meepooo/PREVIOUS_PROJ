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
'授信申请流水表';

comment on column ICPS_APPLY.busi_no is
'业务编号 jiebei-借呗 jintiao-金条 wbank-微粒贷';

comment on column ICPS_APPLY.apply_no is
'申请单号';

comment on column ICPS_APPLY.id_type is
'证件类型';

comment on column ICPS_APPLY.id_num is
'证件号码';

comment on column ICPS_APPLY.id_valid_end_date is
'证件有效期';

comment on column ICPS_APPLY.name is
'姓名';

comment on column ICPS_APPLY.mobile_no is
'手机号';

comment on column ICPS_APPLY.auth_flag is
'芝麻授权成功标识 Y-授权成功 N-授权失败';

comment on column ICPS_APPLY.has_admit_flag is
'之前是否有额度 Y-之前有额度，N-之前没有额度';

comment on column ICPS_APPLY.apply_plt_date is
'授信申请平台日期';

comment on column ICPS_APPLY.apply_plt_serial is
'授信申请平台流水号';

comment on column ICPS_APPLY.apply_status is
'授信申请状态 0-成功 1-失败 6-未知 9-初始';

comment on column ICPS_APPLY.credit_no is
'授信编号';

comment on column ICPS_APPLY.info_admit_flag is
'银行是否推荐准入 Y-准入 N-不准入';

comment on column ICPS_APPLY.credit_amt is
'推荐额度';

comment on column ICPS_APPLY.credit_rate is
'推荐利率';

comment on column ICPS_APPLY.refuse_code is
'拒绝码';

comment on column ICPS_APPLY.refuse_reason is
'拒绝原因';

comment on column ICPS_APPLY.info_plt_date is
'银行初审平台日期';

comment on column ICPS_APPLY.info_plt_serial is
'银行初审平台流水号';

comment on column ICPS_APPLY.info_status is
'初审状态 0-成功 1-失败 6-未知 9-初始';

comment on column ICPS_APPLY.third_access is
'是否通过审批 Y-通过 N-不通过';

comment on column ICPS_APPLY.third_refuse_reason is
'审批不通过原因';

comment on column ICPS_APPLY.third_amt is
'审批额度';

comment on column ICPS_APPLY.third_rate is
'审批基础利率';

comment on column ICPS_APPLY.risk_rating is
'风险评级';

comment on column ICPS_APPLY.solvency_rating is
'偿债能力评级';

comment on column ICPS_APPLY.change_result_reason is
'额度定价变更原因';

comment on column ICPS_APPLY.ack_admit_flag is
'终审银行是否准入 Y-准入 N-不准入';

comment on column ICPS_APPLY.ack_admit_msg is
'准入原因';

comment on column ICPS_APPLY.ack_plt_date is
'终审平台日期';

comment on column ICPS_APPLY.ack_plt_serial is
'终审平台流水号';

comment on column ICPS_APPLY.ack_status is
'终审状态 0-成功 1-失败 6-未知 9-初始';

comment on column ICPS_APPLY.extend_param1 is
'扩展1';

comment on column ICPS_APPLY.extend_param2 is
'扩展2';

comment on column ICPS_APPLY.extend_param3 is
'扩展3';


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
'人行征信信息表';

comment on column ICPS_PBOC_CREDIT.apply_no is
'申请单号';

comment on column ICPS_PBOC_CREDIT.plt_date is
'平台日期';

comment on column ICPS_PBOC_CREDIT.plt_serial is
'平台流水号';

comment on column ICPS_PBOC_CREDIT.id_type is
'证件类型';

comment on column ICPS_PBOC_CREDIT.id_num is
'证件号码';

comment on column ICPS_PBOC_CREDIT.query_no is
'查询编号';

comment on column ICPS_PBOC_CREDIT.query_flag is
'查询标记 1：有查询且查到报告；0：有查询但查无此人';

comment on column ICPS_PBOC_CREDIT.manage_last_12_qry_cnt is
'查询-贷后管理：最近12个月查询次数';

comment on column ICPS_PBOC_CREDIT.manage_last_3_qry_cnt is
'查询-贷后管理：最近3个月查询次数';

comment on column ICPS_PBOC_CREDIT.manage_last_6_qry_cnt is
'查询-贷后管理：最近6个月查询次数';

comment on column ICPS_PBOC_CREDIT.approve_last_12_qry_cnt is
'查询-贷款审批：最近12个月查询次数';

comment on column ICPS_PBOC_CREDIT.approve_last_3_qry_cnt is
'查询-贷款审批：最近3个月查询次数';

comment on column ICPS_PBOC_CREDIT.approve_last_6_qry_cnt is
'查询-贷款审批：最近6个月查询次数';

comment on column ICPS_PBOC_CREDIT.approve_last_30d_qry_org_cnt is
'查询-贷款审批：最近1个月查询机构数';

comment on column ICPS_PBOC_CREDIT.approve_last_12_qry_org_cnt is
'查询-贷款审批：最近12个月查询机构数';

comment on column ICPS_PBOC_CREDIT.approve_last_3_qry_org_cnt is
'查询-贷款审批：最近3个月查询机构数';

comment on column ICPS_PBOC_CREDIT.approve_last_6_qry_org_cnt is
'查询-贷款审批：最近6个月查询机构数';

comment on column ICPS_PBOC_CREDIT.card_last_12_qry_cnt is
'查询-信用卡审批：最近12个月查询次数';

comment on column ICPS_PBOC_CREDIT.card_last_3_qry_cnt is
'查询-信用卡审批：最近3个月查询次数';

comment on column ICPS_PBOC_CREDIT.card_last_6_qry_cnt is
'查询-信用卡审批：最近6个月查询次数';

comment on column ICPS_PBOC_CREDIT.card_last_30d_qry_org_cnt is
'查询-信用卡审批：最近1个月查询次数';

comment on column ICPS_PBOC_CREDIT.card_last_3_qry_org_cnt is
'查询-信用卡审批：最近3个月查询机构数';

comment on column ICPS_PBOC_CREDIT.card_last_6_qry_org_cnt is
'查询-信用卡审批：最近6个月查询机构数';

comment on column ICPS_PBOC_CREDIT.all_loan_num is
'总贷款笔数（包含所有状态）';

comment on column ICPS_PBOC_CREDIT.car_loan_num is
'车贷笔数';

comment on column ICPS_PBOC_CREDIT.biz_loan_num is
'经营贷款笔数';

comment on column ICPS_PBOC_CREDIT.house_loan_num is
'房贷笔数';

comment on column ICPS_PBOC_CREDIT.os_all_loan_num is
'未结清人民币帐户贷款总笔数';

comment on column ICPS_PBOC_CREDIT.os_car_loan_num is
'未结清车贷笔数';

comment on column ICPS_PBOC_CREDIT.os_house_loan_num is
'未结清房贷笔数';

comment on column ICPS_PBOC_CREDIT.os_biz_loan_num is
'未结清经营贷款笔数';

comment on column ICPS_PBOC_CREDIT.ln_nca_con13_cnt_sum is
'未结清消费贷款（仅统计个人消费贷款）笔数';

comment on column ICPS_PBOC_CREDIT.ln_nca_crd_cnt_sum is
'未结清信用贷款笔数';

comment on column ICPS_PBOC_CREDIT.loan_max_amount is
'贷款最高额度';

comment on column ICPS_PBOC_CREDIT.loan_oper_max_amount is
'经营性贷款最高额度';

comment on column ICPS_PBOC_CREDIT.balance_sum is
'未结清贷款本金余额总和';

comment on column ICPS_PBOC_CREDIT.loan_sum_amount is
'未结清贷款额度总和';

comment on column ICPS_PBOC_CREDIT.ln_nca_amt_avg is
'未结清贷款平均合同金额';

comment on column ICPS_PBOC_CREDIT.loan_house_amt_sum is
'未结清房贷合同金额';

comment on column ICPS_PBOC_CREDIT.loan_house_bal_sum is
'未结清房贷余额';

comment on column ICPS_PBOC_CREDIT.business_loan_sum_amount is
'未结清经营贷款合同金额';

comment on column ICPS_PBOC_CREDIT.business_loan_sum_balance is
'未结清经营贷款余额';

comment on column ICPS_PBOC_CREDIT.ln_nca_con13_bal_sum is
'未结清消费贷款（仅统计个人消费贷款）余额';

comment on column ICPS_PBOC_CREDIT.ln_nca_rmm_avg is
'未结清贷款平均剩余还款月数';

comment on column ICPS_PBOC_CREDIT.ln_nca_pmm_avg is
'未结清贷款平均还款月数';

comment on column ICPS_PBOC_CREDIT.ln_nca_pmo_avg is
'当月未结清贷款平均应还款';

comment on column ICPS_PBOC_CREDIT.ln_nca_pmt_sum is
'未结清贷款当月总实还款';

comment on column ICPS_PBOC_CREDIT.repay_car_mon is
'月度车贷按揭应还款';

comment on column ICPS_PBOC_CREDIT.repay_house_mon is
'月度房贷按揭应还款';

comment on column ICPS_PBOC_CREDIT.ln_nca_m1_max_3m is
'未结清贷款近3个月最大逾期次数';

comment on column ICPS_PBOC_CREDIT.loan_ovd_max_bal_cpt is
'贷款单月最大逾期金额';

comment on column ICPS_PBOC_CREDIT.loan_cur_ovd_amount is
'贷款当前逾期总金额';

comment on column ICPS_PBOC_CREDIT.ln_cd_max_24m is
'贷款近24个月最大逾期期数';

comment on column ICPS_PBOC_CREDIT.ln_cd_max is
'当前贷款最大逾期期数';

comment on column ICPS_PBOC_CREDIT.loan_delq_12mth_max is
'未结清贷款近12个月最大逾期期数';

comment on column ICPS_PBOC_CREDIT.loan_delq_3mth_max is
'未结清贷款近3个月最大逾期期数';

comment on column ICPS_PBOC_CREDIT.loan_delq_6mth_max is
'未结清贷款近6个月最大逾期期数';

comment on column ICPS_PBOC_CREDIT.class_5_credit_mortgage is
'按揭类贷款（房贷、车贷）五级分类 1-正常 2-关注 3-次级 4-可疑 5-损失 6-未知';

comment on column ICPS_PBOC_CREDIT.class_5_not_mortgage is
'非按揭类贷款（房贷、车贷）五级分类 1-正常 2-关注 3-次级 4-可疑 5-损失 6-未知';

comment on column ICPS_PBOC_CREDIT.dull_loan_num is
'呆帐信用贷款笔数';

comment on column ICPS_PBOC_CREDIT.dull_loan_sum is
'呆账的贷款数';

comment on column ICPS_PBOC_CREDIT.all_assure_loan_num is
'总担保笔数';

comment on column ICPS_PBOC_CREDIT.all_assure_loan_sum is
'总担保金额';

comment on column ICPS_PBOC_CREDIT.cont_under_attention_assure is
'对外担保五级分类关注及以上笔数';

comment on column ICPS_PBOC_CREDIT.cont_under_secondary_assure is
'担保：状态为“次级”及以上的担保贷款数';

comment on column ICPS_PBOC_CREDIT.assure_under_attention_amt is
'担保：状态为“关注”及以上的担保贷款金额';

comment on column ICPS_PBOC_CREDIT.as_cv2_bal_sum is
'对外担保五级分类关注及以上余额';

comment on column ICPS_PBOC_CREDIT.card_amt_sum is
'对外担保五级分类关注及以上余额激活且未销户信用卡最大授信额度';

comment on column ICPS_PBOC_CREDIT.cc_act_lmt_max is
'激活且未销户信用卡最大授信额度';

comment on column ICPS_PBOC_CREDIT.ac_nml_lmt_avg is
'正常状态卡平均额度';

comment on column ICPS_PBOC_CREDIT.ac_nml_lmt_sum is
'正常状态卡总额度';

comment on column ICPS_PBOC_CREDIT.card_issue_org_cnt is
'正常状态发卡机构数';

comment on column ICPS_PBOC_CREDIT.card_rmb_cnt is
'当前激活且未销户人民币贷记卡数';

comment on column ICPS_PBOC_CREDIT.cc_cnt_sum is
'激活未销户贷记卡数';

comment on column ICPS_PBOC_CREDIT.cc_nca_cnt_sum is
'未销户贷记卡数';

comment on column ICPS_PBOC_CREDIT.normal_num is
'正常状态贷记卡数';

comment on column ICPS_PBOC_CREDIT.all_card_cnt is
'总卡数（贷记卡+准贷记卡，包含所有状态）';

comment on column ICPS_PBOC_CREDIT.cc_act_cu_o90_pct is
'激活且未销户贷记卡当前使用率大于等于90%占激活未销户贷记卡比例';

comment on column ICPS_PBOC_CREDIT.cc_nca_cu_min is
'未销户贷记卡当前最小使用率';

comment on column ICPS_PBOC_CREDIT.cc_nca_mu_max is
'未销户贷记卡最大6个月平均使用率';

comment on column ICPS_PBOC_CREDIT.card_nca_hb_max is
'未销户贷记卡最大使用额度';

comment on column ICPS_PBOC_CREDIT.ac_nca_cu_avg is
'未销户卡当前平均使用率';

comment on column ICPS_PBOC_CREDIT.ac_nca_hb_max is
'未销户卡最大使用额度';

comment on column ICPS_PBOC_CREDIT.cc_nml_mu_avg is
'正常状态贷记卡6个月平均使用率';

comment on column ICPS_PBOC_CREDIT.all_card_cur_ovd_used is
'正常状态卡当前平均使用率';

comment on column ICPS_PBOC_CREDIT.card_nca_pmo_sum is
'所有未销户贷记卡的应还款总额';

comment on column ICPS_PBOC_CREDIT.card_delq_6mth_max_cnt is
'未销户贷记卡近6个月最大逾期次数';

comment on column ICPS_PBOC_CREDIT.card_delq_12mth_max_cnt is
'未销户贷记卡近12个月最大逾期次数';

comment on column ICPS_PBOC_CREDIT.card_delq_3mth_max_cnt is
'未销户贷记卡近3个月最大逾期次数';

comment on column ICPS_PBOC_CREDIT.card_max_ovd_bal is
'贷记卡单月最高逾期金额';

comment on column ICPS_PBOC_CREDIT.all_card_cur_ovd_amt_sum is
'未销户卡当前总逾期金额';

comment on column ICPS_PBOC_CREDIT.cont_dull_card_cnt is
'呆账的贷记卡数';

comment on column ICPS_PBOC_CREDIT.dull_scard_cnt is
'呆账的准贷记卡数';

comment on column ICPS_PBOC_CREDIT.ac_abn_cnt_sum is
'贷记卡为呆帐、冻结、止付卡数';

comment on column ICPS_PBOC_CREDIT.cc_act_m1_cnt_3m is
'激活未销户贷记卡：近3个月1期及以上逾期卡数';

comment on column ICPS_PBOC_CREDIT.cc_act_m1_cnt_pct_3m is
'激活未销户贷记卡：近3个月1期及以上逾期卡数占比';

comment on column ICPS_PBOC_CREDIT.cc_act_m1_cnt_pct_6m is
'激活未销户贷记卡：近6个月1期及以上逾期卡数占比';

comment on column ICPS_PBOC_CREDIT.ac_nca_cd_max is
'未销户卡当前最大逾期期数';

comment on column ICPS_PBOC_CREDIT.cc_cd_max_24m is
'贷记卡近24个月最大逾期期数';

comment on column ICPS_PBOC_CREDIT.card_delq_12mth_max is
'贷记卡未销户账户中，过去12个月最大逾期期数';

comment on column ICPS_PBOC_CREDIT.card_delq_3mth_max is
'贷记卡未销户账户中，过去3个月最大逾期期数';

comment on column ICPS_PBOC_CREDIT.card_delq_6mth_max is
'贷记卡未销户账户中，过去6个月最大逾期期数';

comment on column ICPS_PBOC_CREDIT.qc_act_cd_max_24m is
'准贷卡：近24个月最大逾期期数';

comment on column ICPS_PBOC_CREDIT.scard_delq_12mth_max is
'准贷卡：未销户账户中，过去12个月最大逾期期数';

comment on column ICPS_PBOC_CREDIT.scard_delq_3mth_max is
'准贷卡：未销户账户中，过去3个月最大逾期期数';

comment on column ICPS_PBOC_CREDIT.scard_delq_6mth_max is
'准贷卡：未销户账户中，过去6个月最大逾期期数';

comment on column ICPS_PBOC_CREDIT.credit_opm_max is
'信用历史(最早开卡至查询月数与最早贷款至查询月数取最大)';

comment on column ICPS_PBOC_CREDIT.ac_opm_max is
'最大开卡月数';

comment on column ICPS_PBOC_CREDIT.extend_param1 is
'扩展1';

comment on column ICPS_PBOC_CREDIT.extend_param2 is
'扩展2';

comment on column ICPS_PBOC_CREDIT.extend_param3 is
'扩展3';


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
'芝麻信用信息表';

comment on column ICPS_ZM_CREDIT.apply_no is
'申请单号';

comment on column ICPS_ZM_CREDIT.plt_date is
'平台日期';

comment on column ICPS_ZM_CREDIT.plt_serial is
'平台流水号';

comment on column ICPS_ZM_CREDIT.id_type is
'证件类型';

comment on column ICPS_ZM_CREDIT.id_num is
'证件号码';

comment on column ICPS_ZM_CREDIT.company_name is
'所在公司';

comment on column ICPS_ZM_CREDIT.occupation is
'职业类型';

comment on column ICPS_ZM_CREDIT.have_car_flag is
'是否有车';

comment on column ICPS_ZM_CREDIT.have_house_flag is
'是否有房';

comment on column ICPS_ZM_CREDIT.auth_fin_last_1m_cnt is
'最近一个月主动查询金融机构数';

comment on column ICPS_ZM_CREDIT.auth_fin_last_3m_cnt is
'最近三个月主动查询金融机构数';

comment on column ICPS_ZM_CREDIT.auth_fin_last_6m_cnt is
'最近六个月主动查询金融机构数';

comment on column ICPS_ZM_CREDIT.ovd_order_cnt_6m is
'最近六个月逾期总笔数';

comment on column ICPS_ZM_CREDIT.ovd_order_amt_6m is
'最近六个月逾期总金额';

comment on column ICPS_ZM_CREDIT.mobile_fixed_days is
'手机号稳定天数';

comment on column ICPS_ZM_CREDIT.adr_stability_days is
'地址稳定天数';

comment on column ICPS_ZM_CREDIT.last_6m_avg_asset_total is
'最近六个月流动资产日均值';

comment on column ICPS_ZM_CREDIT.tot_pay_amt_6m is
'最近六个月支付总金额';

comment on column ICPS_ZM_CREDIT.xfdc_index is
'消费档次';

comment on column ICPS_ZM_CREDIT.positive_biz_cnt_1y is
'最近一年履约场景数';

comment on column ICPS_ZM_CREDIT.extend_param1 is
'扩展1';

comment on column ICPS_ZM_CREDIT.extend_param2 is
'扩展2';

comment on column ICPS_ZM_CREDIT.extend_param3 is
'扩展3';


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
'银行征信信息';

comment on column ICPS_BANK_CREDIT.apply_no is
'申请单号';

comment on column ICPS_BANK_CREDIT.plt_date is
'平台日期';

comment on column ICPS_BANK_CREDIT.plt_serial is
'平台流水号';

comment on column ICPS_BANK_CREDIT.id_type is
'证件类型';

comment on column ICPS_BANK_CREDIT.id_num is
'证件号码';

comment on column ICPS_BANK_CREDIT.is_exist_customer is
'是否存量客户 1-是 0-否';

comment on column ICPS_BANK_CREDIT.is_exist_debt_customer is
'是否存量借记卡客户 1-是 0-否';

comment on column ICPS_BANK_CREDIT.balance is
'卡内余额';

comment on column ICPS_BANK_CREDIT.avg_balance_last_3days is
'近3个月日均余额';

comment on column ICPS_BANK_CREDIT.avg_balance_last_6days is
'近6个月日均余额';

comment on column ICPS_BANK_CREDIT.income_last_3m is
'近3个月银行流水收入金额数';

comment on column ICPS_BANK_CREDIT.pay_last_3m is
'近3个月银行流水支出金额数';

comment on column ICPS_BANK_CREDIT.income_last_6m is
'近6个月银行流水收入金额数';

comment on column ICPS_BANK_CREDIT.pay_last_6m is
'近6个月银行流水支出金额数';

comment on column ICPS_BANK_CREDIT.is_exist_credit_customer is
'是否存量信用卡客户 1-是 0-否';

comment on column ICPS_BANK_CREDIT.curr_credit_card_amt is
'本行信用卡授信额度';

comment on column ICPS_BANK_CREDIT.curr_use_credit_card_amt is
'本行信用卡当前使用额度';

comment on column ICPS_BANK_CREDIT.is_exist_fin_customer is
'是否存量理财客户 1-是 0-否';

comment on column ICPS_BANK_CREDIT.fin_balance is
'理财余额';

comment on column ICPS_BANK_CREDIT.avg_fin_bal_last_6m is
'近6个月日均理余额';

comment on column ICPS_BANK_CREDIT.is_exist_insurance_customer is
'是否存量保险客户 1-是 0-否';

comment on column ICPS_BANK_CREDIT.is_exist_loan_customer is
'是否存量贷款客户 1-是 0-否';

comment on column ICPS_BANK_CREDIT.operation_loan_bal is
'经营类贷款总余额';

comment on column ICPS_BANK_CREDIT.personal_credit_bal is
'个人信用类贷总余额';

comment on column ICPS_BANK_CREDIT.car_loan_bal is
'车贷余额';

comment on column ICPS_BANK_CREDIT.car_asset is
'车产价值评估额';

comment on column ICPS_BANK_CREDIT.house_loan_bal is
'房贷余额';

comment on column ICPS_BANK_CREDIT.house_asset is
'房产价值评估额';

comment on column ICPS_BANK_CREDIT.is_stock_customer is
'是否证券客户 1-是 0-否';

comment on column ICPS_BANK_CREDIT.is_third_depository is
'是否第三方存管客户 1-是 0-否';

comment on column ICPS_BANK_CREDIT.is_payroll_customer is
'是否工资代发客户 1-是 0-否';

comment on column ICPS_BANK_CREDIT.is_social_security_customer is
'是否社保代缴客户 1-是 0-否';

comment on column ICPS_BANK_CREDIT.is_life_payment_customer is
'是否水电煤代缴客户 1-是 0-否';

comment on column ICPS_BANK_CREDIT.company_name is
'工作单位';

comment on column ICPS_BANK_CREDIT.company_origin is
'工作单位数据来源 1-核实 2-客户填写 3-其他';

comment on column ICPS_BANK_CREDIT.position is
'职位';

comment on column ICPS_BANK_CREDIT.position_origin is
'职位信息来源 1-核实 2-客户填写 3-其他';

comment on column ICPS_BANK_CREDIT.industry is
'行业';

comment on column ICPS_BANK_CREDIT.industry_origin is
'行业信息来源 1-核实 2-客户填写 3-其他';

comment on column ICPS_BANK_CREDIT.work_years is
'工作年限';

comment on column ICPS_BANK_CREDIT.work_years_origin is
'工作年限信息 来源 1-核实 2-客户填写 3-其他';

comment on column ICPS_BANK_CREDIT.income is
'月收入区间';

comment on column ICPS_BANK_CREDIT.income_origin is
'月收入信息来源 1-核实 2-客户填写 3-其他';

comment on column ICPS_BANK_CREDIT.marriage_status is
'婚姻状态 1-未婚 2-已婚 3-离婚 4-丧偶 NULL-其他';

comment on column ICPS_BANK_CREDIT.marriage_origin is
'婚姻状态信息来源 1-核实 2-客户填写 3-其他';

comment on column ICPS_BANK_CREDIT.is_operation is
'是否经营者 （工商企业或个体工商企业主）1-是 0-否';

comment on column ICPS_BANK_CREDIT.operation_origin is
'是否经营者信息来源 1-核实 2-客户填写 3-其他';

comment on column ICPS_BANK_CREDIT.is_inner_black_customer is
'是否击中内部黑名单客户 1-是 0-否';

comment on column ICPS_BANK_CREDIT.is_police_certified is
'是否公安网身份验证成功 1- 是 0-否';

comment on column ICPS_BANK_CREDIT.is_court_exec_customer is
'是否击中被执行人等涉诉信息 1-是 0-否';

comment on column ICPS_BANK_CREDIT.is_query_house_fund is
'是否有查询公积金信息 1-是 0-否 ';

comment on column ICPS_BANK_CREDIT.fund_query_date is
'公积金查询时间 YYYYMM';

comment on column ICPS_BANK_CREDIT.fund_month_amt is
'公积金查询月缴纳额';

comment on column ICPS_BANK_CREDIT.fund_acct_date is
'公积金开户日期 YYYYMM';

comment on column ICPS_BANK_CREDIT.fund_months_last_6m is
'近6个月累计缴纳月数';

comment on column ICPS_BANK_CREDIT.fund_amt_last_6m is
'近6个月累计缴纳金额';

comment on column ICPS_BANK_CREDIT.fund_total_months is
'总缴纳月数';

comment on column ICPS_BANK_CREDIT.fund_total_amt is
'总缴纳金额';

comment on column ICPS_BANK_CREDIT.fund_max_amt is
'公积金属地缴纳上限';

comment on column ICPS_BANK_CREDIT.is_query_social_security is
'是否有查询社保信息 1-是 0-否 ';

comment on column ICPS_BANK_CREDIT.social_query_date is
'社保信息查询时间 YYYYMM';

comment on column ICPS_BANK_CREDIT.pension_query_month_amt is
'养老保险查询月缴纳额';

comment on column ICPS_BANK_CREDIT.pension_acct_date is
'养老保险开户日期 YYYYMM';

comment on column ICPS_BANK_CREDIT.pension_months_last_6m is
'近6个月养老保险累计缴纳月数';

comment on column ICPS_BANK_CREDIT.pension_amt_last_6m is
'近6个月养老保险累计缴纳金额';

comment on column ICPS_BANK_CREDIT.pension_total_months is
'养老保险总缴纳月数';

comment on column ICPS_BANK_CREDIT.pension_total_amt is
'养老保险总缴纳金额';

comment on column ICPS_BANK_CREDIT.medicare_month_amt is
'医疗保险查询月缴纳额';

comment on column ICPS_BANK_CREDIT.medicare_acct_date is
'医疗保险开户日期 YYYYMM';

comment on column ICPS_BANK_CREDIT.medicare_months_last_6m is
'近6个月医疗保险累计缴纳月数';

comment on column ICPS_BANK_CREDIT.medicare_amt_last_6m is
'近6个月医疗保险累计缴纳金额';

comment on column ICPS_BANK_CREDIT.medicare_total_months is
'医疗保险总缴纳月数';

comment on column ICPS_BANK_CREDIT.medicare_total_amt is
'医疗保险总缴纳金额';

comment on column ICPS_BANK_CREDIT.is_query_degree is
'是否有查询学历信息 1-是 0-否 ';

comment on column ICPS_BANK_CREDIT.school_name is
'院校名称';

comment on column ICPS_BANK_CREDIT.degree_level is
'学历层次 高中及以下，专科，学士，硕士，博士及以上';

comment on column ICPS_BANK_CREDIT.degree_type is
'学历类别';

comment on column ICPS_BANK_CREDIT.entrance_year is
'入学年份 YYYY';

comment on column ICPS_BANK_CREDIT.is_query_communication is
'是否有查询运营商信息 1-是 0-否 ';

comment on column ICPS_BANK_CREDIT.communication is
'运营商 1-移动 2-联通 3-电信 4-其他';

comment on column ICPS_BANK_CREDIT.online_days is
'在网时长';

comment on column ICPS_BANK_CREDIT.total_tel_fare is
'总话费账单金额';

comment on column ICPS_BANK_CREDIT.total_call_hours is
'半年内通话时长 按小时向下取整';

comment on column ICPS_BANK_CREDIT.is_out_black_customer is
'是否击中外部查询黑名单 1-是 0-否 ';

comment on column ICPS_BANK_CREDIT.extend_param1 is
'扩展1';

comment on column ICPS_BANK_CREDIT.extend_param2 is
'扩展2';

comment on column ICPS_BANK_CREDIT.extend_param3 is
'扩展3';


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
'汇总记账文件表';

comment on column ICPS_JB_TOTAL.busi_date is
'业务日期';

comment on column ICPS_JB_TOTAL.encash_amt is
'当天贷款发放金额';

comment on column ICPS_JB_TOTAL.withhold_amt is
'当天网商备付金代扣金额';

comment on column ICPS_JB_TOTAL.refund_amt is
'当天退回网商备付金金额';

comment on column ICPS_JB_TOTAL.accrued_int_amt is
'短期正常/逾期90天以内（含）贷款计提每日利息';

comment on column ICPS_JB_TOTAL.non_accrued_int_amt is
'短期逾期90天以上贷款计提每日利息';

comment on column ICPS_JB_TOTAL.accrued_ovd_prin_pnlt_amt is
'短期逾期90天以内（含）贷款计提每日逾期本金罚息';

comment on column ICPS_JB_TOTAL.non_accrued_ovd_prin_pnlt_amt is
'短期逾期90天以上贷款计提每日逾期本金罚息';

comment on column ICPS_JB_TOTAL.accrued_ovd_int_pnlt_amt is
'短期逾期90天以内（含）贷款计提每日逾期利息罚息';

comment on column ICPS_JB_TOTAL.non_accrued_ovd_int_pnlt_amt is
'短期逾期90天以上贷款计提每日逾期利息罚息';

comment on column ICPS_JB_TOTAL.prin_to_ovd_prin_amt is
'正常本金转逾期本金';

comment on column ICPS_JB_TOTAL.int_to_ovd_int_amt is
'正常利息转逾期利息';

comment on column ICPS_JB_TOTAL.accrued_to_non_prin_amt is
'正常本金（应计）转正常本金（非应计）';

comment on column ICPS_JB_TOTAL.accrued_to_non_ovd_prin_amt is
'逾期本金（应计）转逾期本金（非应计）';

comment on column ICPS_JB_TOTAL.in_to_out_int_amt is
'正常利息（表内）转正常利息（表外）';

comment on column ICPS_JB_TOTAL.in_to_out_ovd_int_amt is
'逾期利息（表内）转逾期利息（表外）';

comment on column ICPS_JB_TOTAL.in_to_out_ovd_prin_pnlt_amt is
'逾期本金罚息（表内）转逾期本金罚息（表外）';

comment on column ICPS_JB_TOTAL.in_to_out_ovd_int_pnlt_amt is
'逾期利息罚息（表内）转逾期利息罚息（表外）';

comment on column ICPS_JB_TOTAL.non_to_accrued_prin_amt is
'正常本金（非应计）转正常本金（应计）';

comment on column ICPS_JB_TOTAL.non_to_accrued_ovd_prin_amt is
'逾期本金（非应计）转逾期本金（应计）';

comment on column ICPS_JB_TOTAL.out_to_in_int_amt is
'正常利息（表外）转正常利息（表内）';

comment on column ICPS_JB_TOTAL.out_to_in_ovd_int_amt is
'逾期利息（表外）转逾期利息（表内）';

comment on column ICPS_JB_TOTAL.out_to_in_ovd_prin_pnlt_amt is
'逾期本金罚息（表外）转逾本金罚息（表内）';

comment on column ICPS_JB_TOTAL.out_to_in_ovd_int_pnlt_amt is
'逾期利息罚息（表外）转逾期利息罚息（表内）';

comment on column ICPS_JB_TOTAL.paid_prin_amt is
'实还正常本金（应计）';

comment on column ICPS_JB_TOTAL.paid_non_accrued_prin_amt is
'实还正常本金（非应计）';

comment on column ICPS_JB_TOTAL.paid_accrued_ovd_prin_amt is
'实还逾期本金（应计）';

comment on column ICPS_JB_TOTAL.paid_non_accrued_ovd_prin_amt is
'实还逾期本金（非应计）';

comment on column ICPS_JB_TOTAL.paid_int_amt is
'实还正常利息（表内）';

comment on column ICPS_JB_TOTAL.paid_out_int_amt is
'实还正常利息（表外）';

comment on column ICPS_JB_TOTAL.paid_in_ovd_int_amt is
'实还逾期利息（表内）';

comment on column ICPS_JB_TOTAL.paid_out_ovd_int_amt is
'实还逾期利息（表外）';

comment on column ICPS_JB_TOTAL.paid_in_ovd_prin_pnlt_int_amt is
'实还逾期本金罚息（表内）';

comment on column ICPS_JB_TOTAL.paid_out_ovd_prin_pnlt_int_amt is
'实还逾期本金罚息（表外）';

comment on column ICPS_JB_TOTAL.paid_in_ovd_int_pnlt_int_amt is
'实还逾期利息罚息（表内）';

comment on column ICPS_JB_TOTAL.paid_out_ovd_int_pnlt_int_amt is
'实还逾期利息罚息（表外）';

comment on column ICPS_JB_TOTAL.xpt_in_int_amt is
'减免正常利息（表内）';

comment on column ICPS_JB_TOTAL.xpt_out_int_amt is
'减免正常利息（表外）';

comment on column ICPS_JB_TOTAL.xpt_in_ovd_int_amt is
'减免逾期利息（表内）';

comment on column ICPS_JB_TOTAL.xpt_out_ovd_int_amt is
'减免逾期利息（表外）';

comment on column ICPS_JB_TOTAL.xpt_in_ovd_prin_pnlt_int_amt is
'减免逾期本金罚息（表内）';

comment on column ICPS_JB_TOTAL.xpt_out_ovd_prin_pnlt_int_amt is
'减免逾期本金罚息（表外）';

comment on column ICPS_JB_TOTAL.xpt_in_ovd_int_pnlt_int_amt is
'减免逾期利息罚息（表内）';

comment on column ICPS_JB_TOTAL.xpt_out_ovd_int_pnlt_int_amt is
'减免逾期利息罚息（表外）';

comment on column ICPS_JB_TOTAL.extend_param1 is
'扩展1';

comment on column ICPS_JB_TOTAL.extend_param2 is
'扩展2';

comment on column ICPS_JB_TOTAL.extend_param3 is
'扩展3';


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
'在途支用明细文件';

comment on column ICPS_JB_LENDING_DETAIL.busi_date is
'业务日期';

comment on column ICPS_JB_LENDING_DETAIL.file_order is
'文件序号';

comment on column ICPS_JB_LENDING_DETAIL.contract_no is
'借呗平台贷款合同号';

comment on column ICPS_JB_LENDING_DETAIL.fund_seq_no is
'放款资金流水号';

comment on column ICPS_JB_LENDING_DETAIL.third_product_code is
'产品码';

comment on column ICPS_JB_LENDING_DETAIL.name is
'客户真实姓名';

comment on column ICPS_JB_LENDING_DETAIL.id_type is
'证件类型';

comment on column ICPS_JB_LENDING_DETAIL.id_num is
'客户证件号码';

comment on column ICPS_JB_LENDING_DETAIL.loan_status is
'贷款状态 1-成功 2-失败 3-在途';

comment on column ICPS_JB_LENDING_DETAIL.loan_use is
'贷款用途 1-消费 2-经营';

comment on column ICPS_JB_LENDING_DETAIL.use_area is
'贷款资金使用位置 0-境外 1-境内';

comment on column ICPS_JB_LENDING_DETAIL.apply_date is
'申请支用时间 YYYYMMDDHHMMSS';

comment on column ICPS_JB_LENDING_DETAIL.encash_date is
'放款日期 YYYYMMDDHHMMSS';

comment on column ICPS_JB_LENDING_DETAIL.currency is
'币种 CNY';

comment on column ICPS_JB_LENDING_DETAIL.encash_amt is
'放款金额';

comment on column ICPS_JB_LENDING_DETAIL.start_date is
'贷款起息日 YYYYMMDD';

comment on column ICPS_JB_LENDING_DETAIL.end_date is
'贷款到期日 YYYYMMDD';

comment on column ICPS_JB_LENDING_DETAIL.total_terms is
'贷款期次数';

comment on column ICPS_JB_LENDING_DETAIL.repay_mode is
'还款方式 1-等额本息 2-等额本金 6-按期付息到期一次还本';

comment on column ICPS_JB_LENDING_DETAIL.grace_day is
'宽限期天数';

comment on column ICPS_JB_LENDING_DETAIL.rate_type is
'利率类型 F-固定利率 L0-浮动利率-按日 L1-浮动利率-按周 L2-浮动利率-按月 L3-浮动利率-按季 L4-浮动利率-按半年 L5-浮动利率-按年 L9-浮动利率-其它';

comment on column ICPS_JB_LENDING_DETAIL.day_rate is
'贷款日利率';

comment on column ICPS_JB_LENDING_DETAIL.prin_repay_frequency is
'本金还款频率，该笔贷款连续两次还款时间的间隔。01:日02:周03:月04:季05:半年06:年07:一次性08:不定期（贷款期限内任意时间还款）99:其他';

comment on column ICPS_JB_LENDING_DETAIL.int_repay_frequency is
'本金还款频率，该笔贷款连续两次还款时间的间隔。01:日02:周03:月04:季05:半年06:年07:一次性08:不定期（贷款期限内任意时间还款）99:其他';

comment on column ICPS_JB_LENDING_DETAIL.guarantee_type is
'担保类型，A 质押贷款B 抵押贷款B01   房地产抵押贷款B99   其他抵押贷款C 保证贷款C01   联保贷款C99   其他保证贷款D 信用/免担保贷款E 组合担保Z 其他';

comment on column ICPS_JB_LENDING_DETAIL.credit_no is
'授信编号';

comment on column ICPS_JB_LENDING_DETAIL.encash_acct_type is
'放款帐号类型，01:银行借记卡02:支付宝';

comment on column ICPS_JB_LENDING_DETAIL.encash_acct is
'放款帐号';

comment on column ICPS_JB_LENDING_DETAIL.repay_acct_type is
'还款帐号类型，01:银行借记卡02:支付宝';

comment on column ICPS_JB_LENDING_DETAIL.repay_acct is
'还款帐号';

comment on column ICPS_JB_LENDING_DETAIL.loan_apply_no is
'贷款申请单号';

comment on column ICPS_JB_LENDING_DETAIL.is_check_flag is
'参与对账标识';

comment on column ICPS_JB_LENDING_DETAIL.extend_param1 is
'扩展1';

comment on column ICPS_JB_LENDING_DETAIL.extend_param2 is
'扩展2';

comment on column ICPS_JB_LENDING_DETAIL.extend_param3 is
'扩展3';


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
'放款（借据）明细文件';

comment on column ICPS_JB_LOAN_DETAIL.busi_date is
'业务日期';

comment on column ICPS_JB_LOAN_DETAIL.file_order is
'文件序号';

comment on column ICPS_JB_LOAN_DETAIL.contract_no is
'借呗平台贷款合同号';

comment on column ICPS_JB_LOAN_DETAIL.fund_seq_no is
'放款资金流水号';

comment on column ICPS_JB_LOAN_DETAIL.third_product_code is
'产品码';

comment on column ICPS_JB_LOAN_DETAIL.name is
'客户真实姓名';

comment on column ICPS_JB_LOAN_DETAIL.id_type is
'证件类型';

comment on column ICPS_JB_LOAN_DETAIL.id_num is
'客户证件号码';

comment on column ICPS_JB_LOAN_DETAIL.loan_status is
'贷款状态 1-成功 2-失败 3-在途';

comment on column ICPS_JB_LOAN_DETAIL.loan_use is
'贷款用途 1-消费 2-经营';

comment on column ICPS_JB_LOAN_DETAIL.use_area is
'贷款资金使用位置 0-境外 1-境内';

comment on column ICPS_JB_LOAN_DETAIL.apply_date is
'申请支用时间 YYYYMMDDHHMMSS';

comment on column ICPS_JB_LOAN_DETAIL.encash_date is
'放款日期 YYYYMMDDHHMMSS';

comment on column ICPS_JB_LOAN_DETAIL.currency is
'币种 CNY-人民币';

comment on column ICPS_JB_LOAN_DETAIL.encash_amt is
'放款金额';

comment on column ICPS_JB_LOAN_DETAIL.start_date is
'贷款起息日 YYYYMMDD';

comment on column ICPS_JB_LOAN_DETAIL.end_date is
'贷款到期日 YYYYMMDD';

comment on column ICPS_JB_LOAN_DETAIL.total_terms is
'贷款期次数';

comment on column ICPS_JB_LOAN_DETAIL.repay_mode is
'还款方式 1-等额本息 2-等额本金 6-按期付息到期一次还本';

comment on column ICPS_JB_LOAN_DETAIL.grace_day is
'宽限期天数';

comment on column ICPS_JB_LOAN_DETAIL.rate_type is
'利率类型，F:固定利率L0:浮动利率-按日L1:浮动利率-按周L2:浮动利率-按月L3:浮动利率-按季L4:浮动利率-按半年L5:浮动利率-按年L9:浮动利率-其它';

comment on column ICPS_JB_LOAN_DETAIL.day_rate is
'贷款日利率';

comment on column ICPS_JB_LOAN_DETAIL.prin_repay_frequency is
'本金还款频率，该笔贷款连续两次还款时间的间隔。01:日02:周03:月04:季05:半年06:年07:一次性08:不定期（贷款期限内任意时间还款）99:其他';

comment on column ICPS_JB_LOAN_DETAIL.int_repay_frequency is
'本金还款频率，该笔贷款连续两次还款时间的间隔。01:日02:周03:月04:季05:半年06:年07:一次性08:不定期（贷款期限内任意时间还款）99:其他';

comment on column ICPS_JB_LOAN_DETAIL.guarantee_type is
'担保类型，A 质押贷款B 抵押贷款B01   房地产抵押贷款B99   其他抵押贷款C 保证贷款C01   联保贷款C99   其他保证贷款D 信用/免担保贷款E 组合担保Z 其他';

comment on column ICPS_JB_LOAN_DETAIL.credit_no is
'授信编号';

comment on column ICPS_JB_LOAN_DETAIL.encash_acct_type is
'放款帐号类型，01:银行借记卡02:支付宝';

comment on column ICPS_JB_LOAN_DETAIL.encash_acct is
'放款帐号';

comment on column ICPS_JB_LOAN_DETAIL.repay_acct_type is
'还款帐号类型，01:银行借记卡02:支付宝';

comment on column ICPS_JB_LOAN_DETAIL.repay_acct is
'还款帐号';

comment on column ICPS_JB_LOAN_DETAIL.loan_apply_no is
'贷款申请单号';

comment on column ICPS_JB_LOAN_DETAIL.is_check_flag is
'参与对账标识';

comment on column ICPS_JB_LOAN_DETAIL.extend_param1 is
'扩展1';

comment on column ICPS_JB_LOAN_DETAIL.extend_param2 is
'扩展2';

comment on column ICPS_JB_LOAN_DETAIL.extend_param3 is
'扩展3';


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
'放款（分期）明细文件';

comment on column ICPS_JB_REPAY_PLAN.busi_date is
'业务日期';

comment on column ICPS_JB_REPAY_PLAN.file_order is
'文件序号';

comment on column ICPS_JB_REPAY_PLAN.contract_no is
'借呗平台贷款合约号';

comment on column ICPS_JB_REPAY_PLAN.term_no is
'期次号';

comment on column ICPS_JB_REPAY_PLAN.start_date is
'分期开始日期 YYYYMMDD';

comment on column ICPS_JB_REPAY_PLAN.end_date is
'分期结束日期 YYYYMMDD';

comment on column ICPS_JB_REPAY_PLAN.prin_amt is
'本金金额';

comment on column ICPS_JB_REPAY_PLAN.int_amt is
'初始利息匡算金额';

comment on column ICPS_JB_REPAY_PLAN.is_check_flag is
'参与对账标识';

comment on column ICPS_JB_REPAY_PLAN.extend_param1 is
'扩展1';

comment on column ICPS_JB_REPAY_PLAN.extend_param2 is
'扩展2';

comment on column ICPS_JB_REPAY_PLAN.extend_param3 is
'扩展3';


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
'还款（借据）明细文件';

comment on column ICPS_JB_REPAY_LOAN_DETAIL.busi_date is
'业务日期';

comment on column ICPS_JB_REPAY_LOAN_DETAIL.file_order is
'文件序号';

comment on column ICPS_JB_REPAY_LOAN_DETAIL.contract_no is
'借呗平台贷款合同号';

comment on column ICPS_JB_REPAY_LOAN_DETAIL.repay_seq_no is
'还款流水号';

comment on column ICPS_JB_REPAY_LOAN_DETAIL.fee_no is
'收费单号';

comment on column ICPS_JB_REPAY_LOAN_DETAIL.withdraw_no is
'还款提现单号';

comment on column ICPS_JB_REPAY_LOAN_DETAIL.repay_type is
'还款类型 01-主动还款 02-批量扣款 03-动账通知还款 04-线下还款';

comment on column ICPS_JB_REPAY_LOAN_DETAIL.repay_date is
'还款日期 YYYYMMDDHHMMSS';

comment on column ICPS_JB_REPAY_LOAN_DETAIL.curr_prin_bal is
'本次还款前的应收未收正常本金余额';

comment on column ICPS_JB_REPAY_LOAN_DETAIL.curr_ovd_prin_bal is
'本次还款前的应收未收逾期本金余额';

comment on column ICPS_JB_REPAY_LOAN_DETAIL.curr_int_bal is
'本次还款前的应收未收正常利息余额';

comment on column ICPS_JB_REPAY_LOAN_DETAIL.curr_ovd_int_bal is
'本次还款前的应收未收逾期利息余额';

comment on column ICPS_JB_REPAY_LOAN_DETAIL.curr_ovd_prin_pnlt_bal is
'本次还款前的应收未收逾期本金罚息余额';

comment on column ICPS_JB_REPAY_LOAN_DETAIL.curr_ovd_int_pnlt_bal is
'本次还款前的应收未收逾期利息罚息余额';

comment on column ICPS_JB_REPAY_LOAN_DETAIL.repay_amt is
'总金额';

comment on column ICPS_JB_REPAY_LOAN_DETAIL.paid_prin_amt is
'本次实还正常本金金额';

comment on column ICPS_JB_REPAY_LOAN_DETAIL.paid_ovd_prin_amt is
'本次实还逾期本金金额';

comment on column ICPS_JB_REPAY_LOAN_DETAIL.paid_int_amt is
'本次实还正常利息金额';

comment on column ICPS_JB_REPAY_LOAN_DETAIL.paid_ovd_int_amt is
'本次实还逾期利息金额';

comment on column ICPS_JB_REPAY_LOAN_DETAIL.paid_ovd_prin_pnlt_amt is
'本次实还逾期本金罚息金额';

comment on column ICPS_JB_REPAY_LOAN_DETAIL.paid_ovd_int_pnlt_amt is
'本次实还逾期利息罚息金额';

comment on column ICPS_JB_REPAY_LOAN_DETAIL.fee_amt is
'本次还款对应的平台服务费金额';

comment on column ICPS_JB_REPAY_LOAN_DETAIL.is_check_flag is
'参与对账标识';

comment on column ICPS_JB_REPAY_LOAN_DETAIL.extend_param1 is
'扩展1';

comment on column ICPS_JB_REPAY_LOAN_DETAIL.extend_param2 is
'扩展2';

comment on column ICPS_JB_REPAY_LOAN_DETAIL.extend_param3 is
'扩展3';


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
'还款（分期）明细文件';

comment on column ICPS_JB_REPAY_INSTMNT_DETAIL.busi_date is
'业务日期';

comment on column ICPS_JB_REPAY_INSTMNT_DETAIL.file_order is
'文件序号';

comment on column ICPS_JB_REPAY_INSTMNT_DETAIL.contract_no is
'借呗平台贷款合同号';

comment on column ICPS_JB_REPAY_INSTMNT_DETAIL.repay_seq_no is
'还款流水号';

comment on column ICPS_JB_REPAY_INSTMNT_DETAIL.term_no is
'期次号';

comment on column ICPS_JB_REPAY_INSTMNT_DETAIL.repay_amt_type is
'还款金额类型 01-按期还款 02-提前还款 03-逾期还款';

comment on column ICPS_JB_REPAY_INSTMNT_DETAIL.repay_date is
'还款日期 YYYYMMDD';

comment on column ICPS_JB_REPAY_INSTMNT_DETAIL.curr_prin_bal is
'本次还款前的应收未收本金';

comment on column ICPS_JB_REPAY_INSTMNT_DETAIL.curr_int_bal is
'本次还款前的应收未收利息';

comment on column ICPS_JB_REPAY_INSTMNT_DETAIL.curr_ovd_prin_pnlt_bal is
'本次还款前的应收未收逾期本金罚息';

comment on column ICPS_JB_REPAY_INSTMNT_DETAIL.curr_ovd_int_pnlt_bal is
'本次还款前的应收未收逾期利息罚息';

comment on column ICPS_JB_REPAY_INSTMNT_DETAIL.repay_amt is
'本次实还总金额';

comment on column ICPS_JB_REPAY_INSTMNT_DETAIL.paid_prin_amt is
'本次实还本金金额';

comment on column ICPS_JB_REPAY_INSTMNT_DETAIL.paid_int_amt is
'本次实还利息金额';

comment on column ICPS_JB_REPAY_INSTMNT_DETAIL.paid_ovd_prin_pnlt_amt is
'本次实还逾期本金罚息金额';

comment on column ICPS_JB_REPAY_INSTMNT_DETAIL.paid_ovd_int_pnlt_amt is
'本次实还逾期利息罚息金额';

comment on column ICPS_JB_REPAY_INSTMNT_DETAIL.is_check_flag is
'参与对账标识';

comment on column ICPS_JB_REPAY_INSTMNT_DETAIL.extend_param1 is
'扩展1';

comment on column ICPS_JB_REPAY_INSTMNT_DETAIL.extend_param2 is
'扩展2';

comment on column ICPS_JB_REPAY_INSTMNT_DETAIL.extend_param3 is
'扩展3';


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
'减免（借据）明细文件';

comment on column ICPS_JB_XPT_LOAN_DETAIL.busi_date is
'业务日期';

comment on column ICPS_JB_XPT_LOAN_DETAIL.file_order is
'文件序号';

comment on column ICPS_JB_XPT_LOAN_DETAIL.contract_no is
'借呗平台贷款合同号';

comment on column ICPS_JB_XPT_LOAN_DETAIL.xpt_seq_no is
'减免流水号';

comment on column ICPS_JB_XPT_LOAN_DETAIL.xpt_date is
'减免时间 YYYYMMDDHHMMSS';

comment on column ICPS_JB_XPT_LOAN_DETAIL.curr_int_bal is
'本次还款前的应收未收正常利息余额';

comment on column ICPS_JB_XPT_LOAN_DETAIL.curr_ovd_int_bal is
'本次还款前的应收未收逾期利息余额';

comment on column ICPS_JB_XPT_LOAN_DETAIL.curr_ovd_prin_pnlt_bal is
'本次还款前的应收未收逾期本金罚息余额';

comment on column ICPS_JB_XPT_LOAN_DETAIL.curr_ovd_int_pnlt_bal is
'本次还款前的应收未收逾期利息罚息余额';

comment on column ICPS_JB_XPT_LOAN_DETAIL.xpt_amt is
'减免总金额（单位分）';

comment on column ICPS_JB_XPT_LOAN_DETAIL.xpt_int_amt is
'本次减免正常利息金额';

comment on column ICPS_JB_XPT_LOAN_DETAIL.xpt_ovd_int_amt is
'本次减免逾期利息金额';

comment on column ICPS_JB_XPT_LOAN_DETAIL.xpt_ovd_prin_pnlt_amt is
'本次减免逾期本金罚息金额';

comment on column ICPS_JB_XPT_LOAN_DETAIL.xpt_ovd_int_pnlt_amt is
'本次减免逾期利息罚息金额';

comment on column ICPS_JB_XPT_LOAN_DETAIL.is_check_flag is
'参与对账标识';

comment on column ICPS_JB_XPT_LOAN_DETAIL.extend_param1 is
'扩展1';

comment on column ICPS_JB_XPT_LOAN_DETAIL.extend_param2 is
'扩展2';

comment on column ICPS_JB_XPT_LOAN_DETAIL.extend_param3 is
'扩展3';


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
'减免（分期）明细文件';

comment on column ICPS_JB_XPT_INSTMNT_DETAIL.busi_date is
'业务日期';

comment on column ICPS_JB_XPT_INSTMNT_DETAIL.file_order is
'文件序号';

comment on column ICPS_JB_XPT_INSTMNT_DETAIL.contract_no is
'借呗平台贷款合同号';

comment on column ICPS_JB_XPT_INSTMNT_DETAIL.xpt_seq_no is
'减免流水号';

comment on column ICPS_JB_XPT_INSTMNT_DETAIL.term_no is
'期次号';

comment on column ICPS_JB_XPT_INSTMNT_DETAIL.settle_date is
'减免会计日期 YYYYMMDD';

comment on column ICPS_JB_XPT_INSTMNT_DETAIL.curr_int_bal is
'本次还款前的应收未收利息';

comment on column ICPS_JB_XPT_INSTMNT_DETAIL.curr_ovd_prin_pnlt_bal is
'本次还款前的应收未收逾期本金罚息';

comment on column ICPS_JB_XPT_INSTMNT_DETAIL.curr_ovd_int_pnlt_bal is
'本次还款前的应收未收逾期利息罚息';

comment on column ICPS_JB_XPT_INSTMNT_DETAIL.xpt_amt is
'本次减免总金额';

comment on column ICPS_JB_XPT_INSTMNT_DETAIL.xpt_int_amt is
'本次减免利息金额';

comment on column ICPS_JB_XPT_INSTMNT_DETAIL.xpt_ovd_prin_pnlt_amt is
'本次减免逾期本金罚息金额';

comment on column ICPS_JB_XPT_INSTMNT_DETAIL.xpt_ovd_int_pnlt_amt is
'本次减免逾期利息罚息金额';

comment on column ICPS_JB_XPT_INSTMNT_DETAIL.is_check_flag is
'参与对账标识';

comment on column ICPS_JB_XPT_INSTMNT_DETAIL.extend_param1 is
'扩展1';

comment on column ICPS_JB_XPT_INSTMNT_DETAIL.extend_param2 is
'扩展2';

comment on column ICPS_JB_XPT_INSTMNT_DETAIL.extend_param3 is
'扩展3';


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
'日初（借据）信息文件';

comment on column ICPS_JB_LOAN_INIT.busi_date is
'业务日期';

comment on column ICPS_JB_LOAN_INIT.file_order is
'文件序号';

comment on column ICPS_JB_LOAN_INIT.contract_no is
'借呗平台贷款合同号';

comment on column ICPS_JB_LOAN_INIT.settle_date is
'会计日期，格式YYYYMMdd';

comment on column ICPS_JB_LOAN_INIT.status is
'借据状态，正常NORMAL,逾期OVD,结清CLEAR ';

comment on column ICPS_JB_LOAN_INIT.clear_date is
'结清日期，格式YYYYMMdd';

comment on column ICPS_JB_LOAN_INIT.asset_class is
'五级分类标识，正常1，关注2，次级3，可疑4，损失5';

comment on column ICPS_JB_LOAN_INIT.accrued_status is
'应计非应计标识，应计0，非应计1';

comment on column ICPS_JB_LOAN_INIT.next_repay_date is
'下一还款日期 YYYYMMDD';

comment on column ICPS_JB_LOAN_INIT.unclear_terms is
'未结清期数';

comment on column ICPS_JB_LOAN_INIT.ovd_terms is
'逾期期次数';

comment on column ICPS_JB_LOAN_INIT.prin_ovd_days is
'本金逾期天数';

comment on column ICPS_JB_LOAN_INIT.int_ovd_days is
'利息逾期天数';

comment on column ICPS_JB_LOAN_INIT.prin_bal is
'正常本金余额';

comment on column ICPS_JB_LOAN_INIT.ovd_prin_bal is
'逾期本金余额';

comment on column ICPS_JB_LOAN_INIT.int_bal is
'正常利息余额';

comment on column ICPS_JB_LOAN_INIT.ovd_int_bal is
'逾期利息余额';

comment on column ICPS_JB_LOAN_INIT.ovd_prin_pnlt_bal is
'逾期本金罚息余额';

comment on column ICPS_JB_LOAN_INIT.ovd_int_pnlt_bal is
'逾期利息罚息余额';

comment on column ICPS_JB_LOAN_INIT.is_check_flag is
'参与对账标识';

comment on column ICPS_JB_LOAN_INIT.extend_param1 is
'扩展1';

comment on column ICPS_JB_LOAN_INIT.extend_param2 is
'扩展2';

comment on column ICPS_JB_LOAN_INIT.extend_param3 is
'扩展3';


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
'日初（分期）信息文件';

comment on column ICPS_JB_INSTMNT_INIT.busi_date is
'业务日期';

comment on column ICPS_JB_INSTMNT_INIT.file_order is
'文件序号';

comment on column ICPS_JB_INSTMNT_INIT.contract_no is
'借呗平台贷款合同号';

comment on column ICPS_JB_INSTMNT_INIT.settle_date is
'会计日期 YYYYMMDD';

comment on column ICPS_JB_INSTMNT_INIT.term_no is
'期次号';

comment on column ICPS_JB_INSTMNT_INIT.start_date is
'分期开始日期 YYYYMMDD';

comment on column ICPS_JB_INSTMNT_INIT.end_date is
'分期结束日期（当期还款日） YYYYMMDD';

comment on column ICPS_JB_INSTMNT_INIT.status is
'分期状态，正常NORMAL,逾期OVD,结清CLEAR ';

comment on column ICPS_JB_INSTMNT_INIT.clear_date is
'结清日期 YYYYMMDD';

comment on column ICPS_JB_INSTMNT_INIT.prin_ovd_date is
'本金转逾期日期 YYYYMMDD';

comment on column ICPS_JB_INSTMNT_INIT.int_ovd_date is
'利息转逾期日期 YYYYMMDD';

comment on column ICPS_JB_INSTMNT_INIT.prin_ovd_days is
'本金逾期天数';

comment on column ICPS_JB_INSTMNT_INIT.int_ovd_days is
'利息逾期天数';

comment on column ICPS_JB_INSTMNT_INIT.prin_bal is
'本金余额';

comment on column ICPS_JB_INSTMNT_INIT.int_bal is
'利息余额';

comment on column ICPS_JB_INSTMNT_INIT.ovd_prin_pnlt_bal is
'逾期本金罚息余额';

comment on column ICPS_JB_INSTMNT_INIT.ovd_int_pnlt_bal is
'逾期利息罚息余额';

comment on column ICPS_JB_INSTMNT_INIT.is_check_flag is
'参与对账标识';

comment on column ICPS_JB_INSTMNT_INIT.extend_param1 is
'扩展1';

comment on column ICPS_JB_INSTMNT_INIT.extend_param2 is
'扩展2';

comment on column ICPS_JB_INSTMNT_INIT.extend_param3 is
'扩展3';


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
'利息计提明细文件';

comment on column ICPS_JB_LOAN_CALC.busi_date is
'业务日期';

comment on column ICPS_JB_LOAN_CALC.file_order is
'文件序号';

comment on column ICPS_JB_LOAN_CALC.contract_no is
'借呗平台贷款合同号';

comment on column ICPS_JB_LOAN_CALC.calc_date is
'计息日期 YYYYMMDD';

comment on column ICPS_JB_LOAN_CALC.accrued_status is
'应计非应计标识 应计0，非应计1';

comment on column ICPS_JB_LOAN_CALC.prin_bal is
'正常本金余额';

comment on column ICPS_JB_LOAN_CALC.ovd_prin_bal is
'逾期本金余额';

comment on column ICPS_JB_LOAN_CALC.ovd_int_bal is
'逾期利息余额';

comment on column ICPS_JB_LOAN_CALC.real_rate is
'贷款实际日利率';

comment on column ICPS_JB_LOAN_CALC.pnlt_rate is
'贷款罚息日利率';

comment on column ICPS_JB_LOAN_CALC.int_amt is
'正常利息';

comment on column ICPS_JB_LOAN_CALC.ovd_prin_pnlt_amt is
'逾期本金罚息';

comment on column ICPS_JB_LOAN_CALC.ovd_int_pnlt_amt is
'逾期利息罚息';

comment on column ICPS_JB_LOAN_CALC.is_check_flag is
'参与对账标识';

comment on column ICPS_JB_LOAN_CALC.extend_param1 is
'扩展1';

comment on column ICPS_JB_LOAN_CALC.extend_param2 is
'扩展2';

comment on column ICPS_JB_LOAN_CALC.extend_param3 is
'扩展3';


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
'借据形态转移流水文件';

comment on column ICPS_JB_ARG_STATUS_CHANGE.busi_date is
'业务日期';

comment on column ICPS_JB_ARG_STATUS_CHANGE.file_order is
'文件序号';

comment on column ICPS_JB_ARG_STATUS_CHANGE.contract_no is
'借呗平台贷款合同号';

comment on column ICPS_JB_ARG_STATUS_CHANGE.settle_date is
'会计日期';

comment on column ICPS_JB_ARG_STATUS_CHANGE.status_seq_no is
'状态变化流水号';

comment on column ICPS_JB_ARG_STATUS_CHANGE.event_code is
'事件码，转逾期11020007，转非应计11020014，转应计11020015';

comment on column ICPS_JB_ARG_STATUS_CHANGE.before_status is
'借据转移前状态（包括应计） ，取值为NORMAL（应计变更取值切0或1）';

comment on column ICPS_JB_ARG_STATUS_CHANGE.after_status is
'借据转移后状态（包括应计），取值为OVD（应计变更取值为0或1）';

comment on column ICPS_JB_ARG_STATUS_CHANGE.prin_amt is
'本金发生额';

comment on column ICPS_JB_ARG_STATUS_CHANGE.int_amt is
'利息发生额';

comment on column ICPS_JB_ARG_STATUS_CHANGE.ovd_prin_pnlt_amt is
'逾期本金罚息发生额';

comment on column ICPS_JB_ARG_STATUS_CHANGE.ovd_int_pnlt_amt is
'逾期利息罚息发生额';

comment on column ICPS_JB_ARG_STATUS_CHANGE.is_check_flag is
'参与对账标识';

comment on column ICPS_JB_ARG_STATUS_CHANGE.extend_param1 is
'扩展1';

comment on column ICPS_JB_ARG_STATUS_CHANGE.extend_param2 is
'扩展2';

comment on column ICPS_JB_ARG_STATUS_CHANGE.extend_param3 is
'扩展3';


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
'网商银行资金对账文件';

comment on column ICPS_JB_FUND_DETAIL.busi_date is
'业务日期';

comment on column ICPS_JB_FUND_DETAIL.file_order is
'文件序号';

comment on column ICPS_JB_FUND_DETAIL.third_busi_serial is
'网商银行交易流水号';

comment on column ICPS_JB_FUND_DETAIL.third_busi_type is
'业务操作，代收P_DLGATE，代扣P_WITHDRAW（如果收费账户是独立的，则P_FEE代表是收费）';

comment on column ICPS_JB_FUND_DETAIL.trans_amt is
'交易金额 代扣为负数，代收为正数';

comment on column ICPS_JB_FUND_DETAIL.trans_refund_amt is
'交易退款金额 如果此金额大于0则代表是代扣退款';

comment on column ICPS_JB_FUND_DETAIL.trans_dttm is
'交易时间 YYYYMMDDHHMMSS';

comment on column ICPS_JB_FUND_DETAIL.third_trans_name is
'交易名称 代收，代扣';

comment on column ICPS_JB_FUND_DETAIL.peer_org_name is
'对方机构名称';

comment on column ICPS_JB_FUND_DETAIL.trans_sub_detail is
'业务单号';

comment on column ICPS_JB_FUND_DETAIL.is_check_flag is
'参与对账标识';

comment on column ICPS_JB_FUND_DETAIL.extend_param1 is
'扩展1';

comment on column ICPS_JB_FUND_DETAIL.extend_param2 is
'扩展2';

comment on column ICPS_JB_FUND_DETAIL.extend_param3 is
'扩展3';
