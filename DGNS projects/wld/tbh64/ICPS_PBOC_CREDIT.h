/***********************************************************************
版权所有:恒生电子股份有限公司
项目名称:综合技术平台(Turandot)项目
版    本:V1.00
操作系统:
数 据 库:INFORMIX
文 件 名:ICPS_PBOC_CREDIT.h
文件描述:结构定义数据库开发嵌C头文件
项 目 组:
程 序 员:[wangzh14925]
发布时间:2009-4-29 19:40:39 [Gen]
修    订:
修改时间:
************************************************************************
表    名:ICPS_PBOC_CREDIT (3.人行征信信息表)
说    明:
************************************************************************
修改记录:
修改日期:
修改内容:
修 改 人:
修改内容:
************************************************************************/
#ifndef __ICPS_PBOC_CREDIT_H__
#define __ICPS_PBOC_CREDIT_H__
typedef struct TDB_ICPS_PBOC_CREDIT
{
	char   apply_no[64+1];  /*申请单号*/
		/*申请单号*/
	char   plt_date[8+1];  /*平台日期*/
		/*平台日期*/
	char   plt_serial[16+1];  /*平台流水号*/
		/*平台流水号*/
	char   id_type[2+1];  /*证件类型*/
		/*证件类型*/
	char   id_num[32+1];  /*证件号码*/
		/*证件号码*/
	char   query_no[64+1];  /*查询编号*/
		/*查询编号*/
	char   query_flag[1+1];  /*查询标记*/
		/*查询标记 1：有查询且查到报告；0：有查询但查无此人*/
	int   manage_last_12_qry_cnt;  /*贷后管理最近12个月查询次数*/
		/*查询-贷后管理：最近12个月查询次数*/
	int   manage_last_3_qry_cnt;  /*贷后管理最近3个月查询次数*/
		/*查询-贷后管理：最近3个月查询次数*/
	int   manage_last_6_qry_cnt;  /*贷后管理最近6个月查询次数*/
		/*查询-贷后管理：最近6个月查询次数*/
	int   approve_last_12_qry_cnt;  /*贷款审批最近12个月查询次数*/
		/*查询-贷款审批：最近12个月查询次数*/
	int   approve_last_3_qry_cnt;  /*贷款审批最近3个月查询次数*/
		/*查询-贷款审批：最近3个月查询次数*/
	int   approve_last_6_qry_cnt;  /*贷款审批最近6个月查询次数*/
		/*查询-贷款审批：最近6个月查询次数*/
	int   approve_last_30d_qry_org_cnt;  /*贷款审批最近1个月查询机构数*/
		/*查询-贷款审批：最近1个月查询机构数*/
	int   approve_last_12_qry_org_cnt;  /*贷款审批最近12个月查询机构数*/
		/*查询-贷款审批：最近12个月查询机构数*/
	int   approve_last_3_qry_org_cnt;  /*贷款审批最近3个月查询机构数*/
		/*查询-贷款审批：最近3个月查询机构数*/
	int   approve_last_6_qry_org_cnt;  /*贷款审批最近6个月查询机构数*/
		/*查询-贷款审批：最近6个月查询机构数*/
	int   card_last_12_qry_cnt;  /*信用卡审批最近12个月查询次数*/
		/*查询-信用卡审批：最近12个月查询次数*/
	int   card_last_3_qry_cnt;  /*信用卡审批最近3个月查询次数*/
		/*查询-信用卡审批：最近3个月查询次数*/
	int   card_last_6_qry_cnt;  /*信用卡审批最近6个月查询次数*/
		/*查询-信用卡审批：最近6个月查询次数*/
	int   card_last_30d_qry_org_cnt;  /*信用卡审批最近1个月查询次数*/
		/*查询-信用卡审批：最近1个月查询次数*/
	int   card_last_3_qry_org_cnt;  /*信用卡审批最近3个月查询机构数*/
		/*查询-信用卡审批：最近3个月查询机构数*/
	int   card_last_6_qry_org_cnt;  /*信用卡审批最近6个月查询机构数*/
		/*查询-信用卡审批：最近6个月查询机构数*/
	int   all_loan_num;  /*总贷款笔数*/
		/*总贷款笔数（包含所有状态）*/
	int   car_loan_num;  /*车贷笔数*/
		/*车贷笔数*/
	int   biz_loan_num;  /*经营贷款笔数*/
		/*经营贷款笔数*/
	int   house_loan_num;  /*房贷笔数*/
		/*房贷笔数*/
	int   os_all_loan_num;  /*未结清人民币帐户贷款总笔数*/
		/*未结清人民币帐户贷款总笔数*/
	int   os_car_loan_num;  /*未结清车贷笔数*/
		/*未结清车贷笔数*/
	int   os_house_loan_num;  /*未结清房贷笔数*/
		/*未结清房贷笔数*/
	int   os_biz_loan_num;  /*未结清经营贷款笔数*/
		/*未结清经营贷款笔数*/
	int   ln_nca_con13_cnt_sum;  /*未结清个人消费贷款笔数*/
		/*未结清消费贷款（仅统计个人消费贷款）笔数*/
	int   ln_nca_crd_cnt_sum;  /*未结清信用贷款笔数*/
		/*未结清信用贷款笔数*/
	double   loan_max_amount;  /*贷款最高额度*/
		/*贷款最高额度*/
	double   loan_oper_max_amount;  /*经营性贷款最高额度*/
		/*经营性贷款最高额度*/
	double   balance_sum;  /*未结清贷款本金余额总和*/
		/*未结清贷款本金余额总和*/
	double   loan_sum_amount;  /*未结清贷款额度总和*/
		/*未结清贷款额度总和*/
	double   ln_nca_amt_avg;  /*未结清贷款平均合同金额*/
		/*未结清贷款平均合同金额*/
	double   loan_house_amt_sum;  /*未结清房贷合同金额*/
		/*未结清房贷合同金额*/
	double   loan_house_bal_sum;  /*未结清房贷余额*/
		/*未结清房贷余额*/
	double   business_loan_sum_amount;  /*未结清经营贷款合同金额*/
		/*未结清经营贷款合同金额*/
	double   business_loan_sum_balance;  /*未结清经营贷款余额*/
		/*未结清经营贷款余额*/
	double   ln_nca_con13_bal_sum;  /*未结清个人消费贷款余额*/
		/*未结清消费贷款（仅统计个人消费贷款）余额*/
	int   ln_nca_rmm_avg;  /*未结清贷款平均剩余还款月数*/
		/*未结清贷款平均剩余还款月数*/
	int   ln_nca_pmm_avg;  /*未结清贷款平均还款月数*/
		/*未结清贷款平均还款月数*/
	double   ln_nca_pmo_avg;  /*当月未结清贷款平均应还款*/
		/*当月未结清贷款平均应还款*/
	double   ln_nca_pmt_sum;  /*未结清贷款当月总实还款*/
		/*未结清贷款当月总实还款*/
	double   repay_car_mon;  /*月度车贷按揭应还款*/
		/*月度车贷按揭应还款*/
	double   repay_house_mon;  /*月度房贷按揭应还款*/
		/*月度房贷按揭应还款*/
	int   ln_nca_m1_max_3m;  /*未结清贷款近3个月最大逾期次数*/
		/*未结清贷款近3个月最大逾期次数*/
	double   loan_ovd_max_bal_cpt;  /*贷款单月最大逾期金额*/
		/*贷款单月最大逾期金额*/
	double   loan_cur_ovd_amount;  /*贷款当前逾期总金额*/
		/*贷款当前逾期总金额*/
	int   ln_cd_max_24m;  /*贷款近24个月最大逾期期数*/
		/*贷款近24个月最大逾期期数*/
	int   ln_cd_max;  /*当前贷款最大逾期期数*/
		/*当前贷款最大逾期期数*/
	int   loan_delq_12mth_max;  /*未结清贷款近12个月最大逾期期数*/
		/*未结清贷款近12个月最大逾期期数*/
	int   loan_delq_3mth_max;  /*未结清贷款近3个月最大逾期期数*/
		/*未结清贷款近3个月最大逾期期数*/
	int   loan_delq_6mth_max;  /*未结清贷款近6个月最大逾期期数*/
		/*未结清贷款近6个月最大逾期期数*/
	char   class_5_credit_mortgage[1+1];  /*按揭类贷款（房贷、车贷）五级分类*/
		/*按揭类贷款（房贷、车贷）五级分类 1-正常 2-关注 3-次级 4-可疑 5-损失 6-未知*/
	char   class_5_not_mortgage[1+1];  /*非按揭类贷款（房贷、车贷）五级分类*/
		/*非按揭类贷款（房贷、车贷）五级分类 1-正常 2-关注 3-次级 4-可疑 5-损失 6-未知*/
	int   dull_loan_num;  /*呆帐信用贷款笔数*/
		/*呆帐信用贷款笔数*/
	double   dull_loan_sum;  /*呆账的贷款数*/
		/*呆账的贷款数*/
	int   all_assure_loan_num;  /*总担保笔数*/
		/*总担保笔数*/
	double   all_assure_loan_sum;  /*总担保金额*/
		/*总担保金额*/
	int   cont_under_attention_assure;  /*对外担保五级分类关注及以上笔数*/
		/*对外担保五级分类关注及以上笔数*/
	double   cont_under_secondary_assure;  /*状态为次级及以上的担保贷款数*/
		/*担保：状态为“次级”及以上的担保贷款数*/
	double   assure_under_attention_amt;  /*状态为关注及以上的担保贷款金额*/
		/*担保：状态为“关注”及以上的担保贷款金额*/
	double   as_cv2_bal_sum;  /*对外担保五级分类关注及以上余额*/
		/*对外担保五级分类关注及以上余额*/
	double   card_amt_sum;  /*对外担保五级分类关注及以上余额激活且未销户信用卡最大授信额度*/
		/*对外担保五级分类关注及以上余额激活且未销户信用卡最大授信额度*/
	double   cc_act_lmt_max;  /*激活且未销户信用卡最大授信额度*/
		/*激活且未销户信用卡最大授信额度*/
	double   ac_nml_lmt_avg;  /*正常状态卡平均额度*/
		/*正常状态卡平均额度*/
	double   ac_nml_lmt_sum;  /*正常状态卡总额度*/
		/*正常状态卡总额度*/
	int   card_issue_org_cnt;  /*正常状态发卡机构数*/
		/*正常状态发卡机构数*/
	int   card_rmb_cnt;  /*当前激活且未销户人民币贷记卡数*/
		/*当前激活且未销户人民币贷记卡数*/
	int   cc_cnt_sum;  /*激活未销户贷记卡数*/
		/*激活未销户贷记卡数*/
	int   cc_nca_cnt_sum;  /*未销户贷记卡数*/
		/*未销户贷记卡数*/
	int   normal_num;  /*正常状态贷记卡数*/
		/*正常状态贷记卡数*/
	int   all_card_cnt;  /*总卡数*/
		/*总卡数（贷记卡+准贷记卡，包含所有状态）*/
	double   cc_act_cu_o90_pct;  /*激活且未销户贷记卡当前使用率大于等于90%占激活未销户贷记卡比例*/
		/*激活且未销户贷记卡当前使用率大于等于90%占激活未销户贷记卡比例*/
	double   cc_nca_cu_min;  /*未销户贷记卡当前最小使用率*/
		/*未销户贷记卡当前最小使用率*/
	double   cc_nca_mu_max;  /*未销户贷记卡最大6个月平均使用率*/
		/*未销户贷记卡最大6个月平均使用率*/
	double   card_nca_hb_max;  /*未销户贷记卡最大使用额度*/
		/*未销户贷记卡最大使用额度*/
	double   ac_nca_cu_avg;  /*未销户卡当前平均使用率*/
		/*未销户卡当前平均使用率*/
	double   ac_nca_hb_max;  /*未销户卡最大使用额度*/
		/*未销户卡最大使用额度*/
	double   cc_nml_mu_avg;  /*正常状态贷记卡6个月平均使用率*/
		/*正常状态贷记卡6个月平均使用率*/
	double   all_card_cur_ovd_used;  /*正常状态卡当前平均使用率*/
		/*正常状态卡当前平均使用率*/
	double   card_nca_pmo_sum;  /*所有未销户贷记卡的应还款总额*/
		/*所有未销户贷记卡的应还款总额*/
	int   card_delq_6mth_max_cnt;  /*未销户贷记卡近6个月最大逾期次数*/
		/*未销户贷记卡近6个月最大逾期次数*/
	int   card_delq_12mth_max_cnt;  /*未销户贷记卡近12个月最大逾期次数*/
		/*未销户贷记卡近12个月最大逾期次数*/
	int   card_delq_3mth_max_cnt;  /*未销户贷记卡近3个月最大逾期次数*/
		/*未销户贷记卡近3个月最大逾期次数*/
	double   card_max_ovd_bal;  /*贷记卡单月最高逾期金额*/
		/*贷记卡单月最高逾期金额*/
	double   all_card_cur_ovd_amt_sum;  /*未销户卡当前总逾期金额*/
		/*未销户卡当前总逾期金额*/
	int   cont_dull_card_cnt;  /*呆账的贷记卡数*/
		/*呆账的贷记卡数*/
	int   dull_scard_cnt;  /*呆账的准贷记卡数*/
		/*呆账的准贷记卡数*/
	int   ac_abn_cnt_sum;  /*贷记卡为呆帐冻结止付卡数*/
		/*贷记卡为呆帐、冻结、止付卡数*/
	int   cc_act_m1_cnt_3m;  /*激活未销户贷记卡近3个月1期及以上逾期卡数*/
		/*激活未销户贷记卡：近3个月1期及以上逾期卡数*/
	double   cc_act_m1_cnt_pct_3m;  /*激活未销户贷记卡近3个月1期及以上逾期卡数占比*/
		/*激活未销户贷记卡：近3个月1期及以上逾期卡数占比*/
	double   cc_act_m1_cnt_pct_6m;  /*激活未销户贷记卡近6个月1期及以上逾期卡数占比*/
		/*激活未销户贷记卡：近6个月1期及以上逾期卡数占比*/
	int   ac_nca_cd_max;  /*未销户卡当前最大逾期期数*/
		/*未销户卡当前最大逾期期数*/
	int   cc_cd_max_24m;  /*贷记卡近24个月最大逾期期数*/
		/*贷记卡近24个月最大逾期期数*/
	int   card_delq_12mth_max;  /*贷记卡未销户账户中过去12个月最大逾期期数*/
		/*贷记卡未销户账户中，过去12个月最大逾期期数*/
	int   card_delq_3mth_max;  /*贷记卡未销户账户中过去3个月最大逾期期数*/
		/*贷记卡未销户账户中，过去3个月最大逾期期数*/
	int   card_delq_6mth_max;  /*贷记卡未销户账户中过去6个月最大逾期期数*/
		/*贷记卡未销户账户中，过去6个月最大逾期期数*/
	int   qc_act_cd_max_24m;  /*准贷卡近24个月最大逾期期数*/
		/*准贷卡：近24个月最大逾期期数*/
	int   scard_delq_12mth_max;  /*准贷卡未销户账户中过去12个月最大逾期期数*/
		/*准贷卡：未销户账户中，过去12个月最大逾期期数*/
	int   scard_delq_3mth_max;  /*准贷卡未销户账户中过去3个月最大逾期期数*/
		/*准贷卡：未销户账户中，过去3个月最大逾期期数*/
	int   scard_delq_6mth_max;  /*准贷卡未销户账户中过去6个月最大逾期期数*/
		/*准贷卡：未销户账户中，过去6个月最大逾期期数*/
	int   credit_opm_max;  /*信用历史*/
		/*信用历史(最早开卡至查询月数与最早贷款至查询月数取最大)*/
	int   ac_opm_max;  /*最大开卡月数*/
		/*最大开卡月数*/
	char   extend_param1[100+1];  /*扩展1*/
		/*扩展1*/
	char   extend_param2[250+1];  /*扩展2*/
		/*扩展2*/
	char   extend_param3[40+1];  /*扩展3*/
		/*扩展3*/

}ICPS_PBOC_CREDIT;

#define SD_DATA  ICPS_PBOC_CREDIT
#define SD_MEMBERS \ 
	APP_DEFSDMEMBER(T_STRING,  apply_no, 0),\
	APP_DEFSDMEMBER(T_STRING,  plt_date, 0),\
	APP_DEFSDMEMBER(T_STRING,  plt_serial, 0),\
	APP_DEFSDMEMBER(T_STRING,  id_type, 0),\
	APP_DEFSDMEMBER(T_STRING,  id_num, 0),\
	APP_DEFSDMEMBER(T_STRING,  query_no, 0),\
	APP_DEFSDMEMBER(T_STRING,  query_flag, 0),\
	APP_DEFSDMEMBER(T_LONG,  manage_last_12_qry_cnt, 0),\
	APP_DEFSDMEMBER(T_LONG,  manage_last_3_qry_cnt, 0),\
	APP_DEFSDMEMBER(T_LONG,  manage_last_6_qry_cnt, 0),\
	APP_DEFSDMEMBER(T_LONG,  approve_last_12_qry_cnt, 0),\
	APP_DEFSDMEMBER(T_LONG,  approve_last_3_qry_cnt, 0),\
	APP_DEFSDMEMBER(T_LONG,  approve_last_6_qry_cnt, 0),\
	APP_DEFSDMEMBER(T_LONG,  approve_last_30d_qry_org_cnt, 0),\
	APP_DEFSDMEMBER(T_LONG,  approve_last_12_qry_org_cnt, 0),\
	APP_DEFSDMEMBER(T_LONG,  approve_last_3_qry_org_cnt, 0),\
	APP_DEFSDMEMBER(T_LONG,  approve_last_6_qry_org_cnt, 0),\
	APP_DEFSDMEMBER(T_LONG,  card_last_12_qry_cnt, 0),\
	APP_DEFSDMEMBER(T_LONG,  card_last_3_qry_cnt, 0),\
	APP_DEFSDMEMBER(T_LONG,  card_last_6_qry_cnt, 0),\
	APP_DEFSDMEMBER(T_LONG,  card_last_30d_qry_org_cnt, 0),\
	APP_DEFSDMEMBER(T_LONG,  card_last_3_qry_org_cnt, 0),\
	APP_DEFSDMEMBER(T_LONG,  card_last_6_qry_org_cnt, 0),\
	APP_DEFSDMEMBER(T_LONG,  all_loan_num, 0),\
	APP_DEFSDMEMBER(T_LONG,  car_loan_num, 0),\
	APP_DEFSDMEMBER(T_LONG,  biz_loan_num, 0),\
	APP_DEFSDMEMBER(T_LONG,  house_loan_num, 0),\
	APP_DEFSDMEMBER(T_LONG,  os_all_loan_num, 0),\
	APP_DEFSDMEMBER(T_LONG,  os_car_loan_num, 0),\
	APP_DEFSDMEMBER(T_LONG,  os_house_loan_num, 0),\
	APP_DEFSDMEMBER(T_LONG,  os_biz_loan_num, 0),\
	APP_DEFSDMEMBER(T_LONG,  ln_nca_con13_cnt_sum, 0),\
	APP_DEFSDMEMBER(T_LONG,  ln_nca_crd_cnt_sum, 0),\
	APP_DEFSDMEMBER(T_DOUBLE,  loan_max_amount, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  loan_oper_max_amount, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  balance_sum, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  loan_sum_amount, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  ln_nca_amt_avg, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  loan_house_amt_sum, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  loan_house_bal_sum, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  business_loan_sum_amount, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  business_loan_sum_balance, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  ln_nca_con13_bal_sum, 2),\
	APP_DEFSDMEMBER(T_LONG,  ln_nca_rmm_avg, 0),\
	APP_DEFSDMEMBER(T_LONG,  ln_nca_pmm_avg, 0),\
	APP_DEFSDMEMBER(T_DOUBLE,  ln_nca_pmo_avg, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  ln_nca_pmt_sum, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  repay_car_mon, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  repay_house_mon, 2),\
	APP_DEFSDMEMBER(T_LONG,  ln_nca_m1_max_3m, 0),\
	APP_DEFSDMEMBER(T_DOUBLE,  loan_ovd_max_bal_cpt, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  loan_cur_ovd_amount, 2),\
	APP_DEFSDMEMBER(T_LONG,  ln_cd_max_24m, 0),\
	APP_DEFSDMEMBER(T_LONG,  ln_cd_max, 0),\
	APP_DEFSDMEMBER(T_LONG,  loan_delq_12mth_max, 0),\
	APP_DEFSDMEMBER(T_LONG,  loan_delq_3mth_max, 0),\
	APP_DEFSDMEMBER(T_LONG,  loan_delq_6mth_max, 0),\
	APP_DEFSDMEMBER(T_STRING,  class_5_credit_mortgage, 0),\
	APP_DEFSDMEMBER(T_STRING,  class_5_not_mortgage, 0),\
	APP_DEFSDMEMBER(T_LONG,  dull_loan_num, 0),\
	APP_DEFSDMEMBER(T_DOUBLE,  dull_loan_sum, 2),\
	APP_DEFSDMEMBER(T_LONG,  all_assure_loan_num, 0),\
	APP_DEFSDMEMBER(T_DOUBLE,  all_assure_loan_sum, 2),\
	APP_DEFSDMEMBER(T_LONG,  cont_under_attention_assure, 0),\
	APP_DEFSDMEMBER(T_DOUBLE,  cont_under_secondary_assure, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  assure_under_attention_amt, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  as_cv2_bal_sum, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  card_amt_sum, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  cc_act_lmt_max, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  ac_nml_lmt_avg, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  ac_nml_lmt_sum, 2),\
	APP_DEFSDMEMBER(T_LONG,  card_issue_org_cnt, 0),\
	APP_DEFSDMEMBER(T_LONG,  card_rmb_cnt, 0),\
	APP_DEFSDMEMBER(T_LONG,  cc_cnt_sum, 0),\
	APP_DEFSDMEMBER(T_LONG,  cc_nca_cnt_sum, 0),\
	APP_DEFSDMEMBER(T_LONG,  normal_num, 0),\
	APP_DEFSDMEMBER(T_LONG,  all_card_cnt, 0),\
	APP_DEFSDMEMBER(T_DOUBLE,  cc_act_cu_o90_pct, 5),\
	APP_DEFSDMEMBER(T_DOUBLE,  cc_nca_cu_min, 5),\
	APP_DEFSDMEMBER(T_DOUBLE,  cc_nca_mu_max, 5),\
	APP_DEFSDMEMBER(T_DOUBLE,  card_nca_hb_max, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  ac_nca_cu_avg, 5),\
	APP_DEFSDMEMBER(T_DOUBLE,  ac_nca_hb_max, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  cc_nml_mu_avg, 5),\
	APP_DEFSDMEMBER(T_DOUBLE,  all_card_cur_ovd_used, 5),\
	APP_DEFSDMEMBER(T_DOUBLE,  card_nca_pmo_sum, 2),\
	APP_DEFSDMEMBER(T_LONG,  card_delq_6mth_max_cnt, 0),\
	APP_DEFSDMEMBER(T_LONG,  card_delq_12mth_max_cnt, 0),\
	APP_DEFSDMEMBER(T_LONG,  card_delq_3mth_max_cnt, 0),\
	APP_DEFSDMEMBER(T_DOUBLE,  card_max_ovd_bal, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  all_card_cur_ovd_amt_sum, 2),\
	APP_DEFSDMEMBER(T_LONG,  cont_dull_card_cnt, 0),\
	APP_DEFSDMEMBER(T_LONG,  dull_scard_cnt, 0),\
	APP_DEFSDMEMBER(T_LONG,  ac_abn_cnt_sum, 0),\
	APP_DEFSDMEMBER(T_LONG,  cc_act_m1_cnt_3m, 0),\
	APP_DEFSDMEMBER(T_DOUBLE,  cc_act_m1_cnt_pct_3m, 5),\
	APP_DEFSDMEMBER(T_DOUBLE,  cc_act_m1_cnt_pct_6m, 5),\
	APP_DEFSDMEMBER(T_LONG,  ac_nca_cd_max, 0),\
	APP_DEFSDMEMBER(T_LONG,  cc_cd_max_24m, 0),\
	APP_DEFSDMEMBER(T_LONG,  card_delq_12mth_max, 0),\
	APP_DEFSDMEMBER(T_LONG,  card_delq_3mth_max, 0),\
	APP_DEFSDMEMBER(T_LONG,  card_delq_6mth_max, 0),\
	APP_DEFSDMEMBER(T_LONG,  qc_act_cd_max_24m, 0),\
	APP_DEFSDMEMBER(T_LONG,  scard_delq_12mth_max, 0),\
	APP_DEFSDMEMBER(T_LONG,  scard_delq_3mth_max, 0),\
	APP_DEFSDMEMBER(T_LONG,  scard_delq_6mth_max, 0),\
	APP_DEFSDMEMBER(T_LONG,  credit_opm_max, 0),\
	APP_DEFSDMEMBER(T_LONG,  ac_opm_max, 0),\
	APP_DEFSDMEMBER(T_STRING,  extend_param1, 0),\
	APP_DEFSDMEMBER(T_STRING,  extend_param2, 0),\
	APP_DEFSDMEMBER(T_STRING,  extend_param3, 0)


	APP_DECLAREFIELDS(SD_ICPS_PBOC_CREDIT)
#undef SD_DATA
#undef SD_MEMBERS

#endif  /*end of __ICPS_PBOC_CREDIT_H__*/
