/***********************************************************************
版权所有:恒生电子股份有限公司
项目名称:综合技术平台(Turandot)项目
版    本:V1.00
操作系统:
数 据 库:INFORMIX
文 件 名:ICPS_WB_TM_LOAN.h
文件描述:结构定义数据库开发嵌C头文件
项 目 组:
程 序 员:[wangzh14925]
发布时间:2009-4-29 19:40:39 [Gen]
修    订:
修改时间:
************************************************************************
表    名:ICPS_WB_TM_LOAN (F_WB11.分期信息表)
说    明:
************************************************************************
修改记录:
修改日期:
修改内容:
修 改 人:
修改内容:
************************************************************************/
#ifndef __ICPS_WB_TM_LOAN_H__
#define __ICPS_WB_TM_LOAN_H__
typedef struct TDB_ICPS_WB_TM_LOAN
{
	char   busi_date[8+1];  /*业务日期*/
		/*业务日期*/
	int   file_order;  /*文件序号*/
		/*文件序号*/
	char   org[12+1];  /*机构号*/
		/*机构号*/
	char   loan_id[20+1];  /*借据ID*/
		/*借据ID*/
	char   acct_no[20+1];  /*账户编号*/
		/*账户编号*/
	char   acct_type[1+1];  /*账户类型*/
		/*账户类型*/
	char   ref_nbr[23+1];  /*交易参考号*/
		/*交易参考号*/
	char   logical_card_no[19+1];  /*逻辑卡号*/
		/*逻辑卡号*/
	char   card_no[19+1];  /*卡号*/
		/*卡号*/
	char   register_date[14+1];  /*贷款注册日期*/
		/*贷款注册日期*/
	char   request_time[14+1];  /*请求日期时间*/
		/*请求日期时间*/
	char   loan_type[5+1];  /*贷款类型*/
		/*贷款类型*/
	char   loan_status[1+1];  /*贷款状态*/
		/*贷款状态*/
	char   last_loan_status[1+1];  /*贷款上次状态*/
		/*贷款上次状态*/
	int   loan_init_term;  /*贷款总期数*/
		/*贷款总期数*/
	int   curr_term;  /*当前期数*/
		/*当前期数*/
	int   remain_term;  /*剩余期数*/
		/*剩余期数*/
	double   loan_init_prin;  /*贷款总本金*/
		/*贷款总本金*/
	double   loan_fixed_pmt_prin;  /*贷款每期应还本金*/
		/*贷款每期应还本金*/
	double   loan_first_term_prin;  /*贷款首期应还本金*/
		/*贷款首期应还本金*/
	double   loan_final_term_prin;  /*贷款末期应还本金*/
		/*贷款末期应还本金*/
	double   loan_init_fee1;  /*贷款总手续费*/
		/*贷款总手续费*/
	double   loan_fixed_fee1;  /*贷款每期手续费*/
		/*贷款每期手续费*/
	double   loan_first_term_fee1;  /*贷款首期手续费*/
		/*贷款首期手续费*/
	double   loan_final_term_fee1;  /*贷款末期手续费*/
		/*贷款末期手续费*/
	double   unearned_prin;  /*贷款账单的本金*/
		/*贷款账单的本金*/
	double   unearned_fee1;  /*贷款账单手续费*/
		/*贷款账单手续费*/
	char   paid_out_date[14+1];  /*还清日期*/
		/*还清日期*/
	char   terminate_date[14+1];  /*提前终止日期*/
		/*提前终止日期*/
	char   terminate_reason_cd[1+1];  /*贷款终止原因代码*/
		/*贷款终止原因代码*/
	double   prin_paid;  /*已偿还本金*/
		/*已偿还本金*/
	double   int_paid;  /*已偿还利息*/
		/*已偿还利息*/
	double   fee_paid;  /*已偿还费用*/
		/*已偿还费用*/
	double   loan_curr_bal;  /*贷款当前总余额*/
		/*贷款当前总余额*/
	double   loan_bal_xfrout;  /*贷款未到期余额*/
		/*贷款未到期余额*/
	double   loan_bal_xfrin;  /*贷款已到期余额*/
		/*贷款已到期余额*/
	double   loan_bal_principal;  /*欠款总本金*/
		/*欠款总本金*/
	double   loan_bal_interest;  /*欠款总利息*/
		/*欠款总利息*/
	double   loan_bal_penalty;  /*欠款总罚息*/
		/*欠款总罚息*/
	double   loan_prin_xfrout;  /*贷款未到期本金*/
		/*贷款未到期本金*/
	double   loan_prin_xfrin;  /*贷款已到期本金*/
		/*贷款已到期本金*/
	double   loan_fee1_xfrout;  /*贷款未到期手续费*/
		/*贷款未到期手续费*/
	double   loan_fee1_xfrin;  /*贷款已到期手续费*/
		/*贷款已到期手续费*/
	double   orig_txn_amt;  /*原始交易币种金额*/
		/*原始交易币种金额*/
	char   orig_trans_date[14+1];  /*原始交易日期*/
		/*原始交易日期*/
	char   orig_auth_code[6+1];  /*原始交易授权码*/
		/*原始交易授权码*/
	int   jpa_version;  /*乐观锁版本号*/
		/*乐观锁版本号*/
	char   loan_code[4+1];  /*贷款产品号*/
		/*贷款产品号*/
	char   register_id[20+1];  /*贷款申请顺序号*/
		/*贷款申请顺序号*/
	double   resch_init_prin;  /*展期本金金额*/
		/*展期本金金额*/
	char   resch_date[14+1];  /*展期生效日期*/
		/*展期生效日期*/
	double   bef_resch_fixed_pmt_prin;  /*展期前每期应还本金*/
		/*展期前每期应还本金*/
	int   bef_resch_init_term;  /*展期前总期数*/
		/*展期前总期数*/
	double   bef_resch_first_term_prin;  /*展期前贷款首期应还本金*/
		/*展期前贷款首期应还本金*/
	double   bef_resch_final_term_prin;  /*展期前贷款末期应还本金*/
		/*展期前贷款末期应还本金*/
	double   bef_resch_init_fee1;  /*展期前贷款总手续费*/
		/*展期前贷款总手续费*/
	double   bef_resch_fixed_fee1;  /*BEF_贷款每期手续费*/
		/*BEF_贷款每期手续费*/
	double   bef_resch_first_term_fee1;  /*展期前贷款首期手续费*/
		/*展期前贷款首期手续费*/
	double   bef_resch_final_term_fee1;  /*展期前贷款末期手续费*/
		/*展期前贷款末期手续费*/
	double   resch_first_term_fee1;  /*展期后首期手续费*/
		/*展期后首期手续费*/
	char   loan_fee_method[1+1];  /*贷款手续费收取方式*/
		/*贷款手续费收取方式*/
	double   interest_rate;  /*基础利率*/
		/*基础利率*/
	double   penalty_rate;  /*罚息利率*/
		/*罚息利率*/
	double   compound_rate;  /*复利利率*/
		/*复利利率*/
	double   float_rate;  /*浮动比例*/
		/*浮动比例*/
	char   loan_receipt_nbr[20+1];  /*借据号*/
		/*借据号*/
	char   loan_expire_date[14+1];  /*贷款到期日期*/
		/*贷款到期日期*/
	char   loan_cd[2+1];  /*贷款逾期最大期数*/
		/*贷款逾期最大期数*/
	char   payment_hist[24+1];  /*24个月还款状态*/
		/*24个月还款状态*/
	double   ctd_payment_amt;  /*当期还款额*/
		/*当期还款额*/
	int   past_resch_cnt;  /*已展期次数*/
		/*已展期次数*/
	int   past_shorted_cnt;  /*已缩期次数*/
		/*已缩期次数*/
	double   adv_pmt_amt;  /*提前还款金额*/
		/*提前还款金额*/
	char   last_action_date[14+1];  /*上次行动日期*/
		/*上次行动日期*/
	char   last_action_type[1+1];  /*上次行动类型*/
		/*上次行动类型*/
	char   last_modified_datetime[14+1];  /*修改时间*/
		/*修改时间*/
	char   activate_date[14+1];  /*激活日期*/
		/*激活日期*/
	char   interest_calc_base[14+1];  /*计息基数*/
		/*计息基数*/
	char   first_bill_date[14+1];  /*首个到期还款日*/
		/*首个到期还款日*/
	char   age_cd[1+1];  /*账龄*/
		/*账龄*/
	char   recalc_ind[1+1];  /*利率重算标志*/
		/*利率重算标志*/
	char   recalc_date[14+1];  /*利率重算日*/
		/*利率重算日*/
	char   grace_date[14+1];  /*宽限日期*/
		/*宽限日期*/
	char   cancel_date[14+1];  /*撤销日期*/
		/*撤销日期*/
	char   cancel_reason[100+1];  /*贷款撤销原因*/
		/*贷款撤销原因*/
	char   bank_group_id[5+1];  /*银团编号*/
		/*银团编号*/
	int   due_days;  /*当前逾期天数*/
		/*当前逾期天数*/
	char   contract_ver[200+1];  /*合同版本号*/
		/*合同版本号*/
	double   loan_init_interest;  /*贷款总利息*/
		/*贷款总利息*/
	double   bef_init_interest;  /*原贷款总利息*/
		/*原贷款总利息*/
	double   bank_proportion;  /*银行出资比例*/
		/*银行出资比例*/
	char   is_check_flag[1+1];  /*参与对账标识*/
		/*参与对账标识*/
	char   extend_param1[100+1];  /*扩展1*/
		/*扩展1*/
	char   extend_param2[250+1];  /*扩展2*/
		/*扩展2*/
	char   extend_param3[40+1];  /*扩展3*/
		/*扩展3*/

}ICPS_WB_TM_LOAN;

#define SD_DATA  ICPS_WB_TM_LOAN
#define SD_MEMBERS \ 
	APP_DEFSDMEMBER(T_STRING,  busi_date, 0),\
	APP_DEFSDMEMBER(T_LONG,  file_order, 0),\
	APP_DEFSDMEMBER(T_STRING,  org, 0),\
	APP_DEFSDMEMBER(T_STRING,  loan_id, 0),\
	APP_DEFSDMEMBER(T_STRING,  acct_no, 0),\
	APP_DEFSDMEMBER(T_STRING,  acct_type, 0),\
	APP_DEFSDMEMBER(T_STRING,  ref_nbr, 0),\
	APP_DEFSDMEMBER(T_STRING,  logical_card_no, 0),\
	APP_DEFSDMEMBER(T_STRING,  card_no, 0),\
	APP_DEFSDMEMBER(T_STRING,  register_date, 0),\
	APP_DEFSDMEMBER(T_STRING,  request_time, 0),\
	APP_DEFSDMEMBER(T_STRING,  loan_type, 0),\
	APP_DEFSDMEMBER(T_STRING,  loan_status, 0),\
	APP_DEFSDMEMBER(T_STRING,  last_loan_status, 0),\
	APP_DEFSDMEMBER(T_LONG,  loan_init_term, 0),\
	APP_DEFSDMEMBER(T_LONG,  curr_term, 0),\
	APP_DEFSDMEMBER(T_LONG,  remain_term, 0),\
	APP_DEFSDMEMBER(T_DOUBLE,  loan_init_prin, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  loan_fixed_pmt_prin, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  loan_first_term_prin, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  loan_final_term_prin, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  loan_init_fee1, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  loan_fixed_fee1, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  loan_first_term_fee1, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  loan_final_term_fee1, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  unearned_prin, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  unearned_fee1, 2),\
	APP_DEFSDMEMBER(T_STRING,  paid_out_date, 0),\
	APP_DEFSDMEMBER(T_STRING,  terminate_date, 0),\
	APP_DEFSDMEMBER(T_STRING,  terminate_reason_cd, 0),\
	APP_DEFSDMEMBER(T_DOUBLE,  prin_paid, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  int_paid, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  fee_paid, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  loan_curr_bal, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  loan_bal_xfrout, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  loan_bal_xfrin, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  loan_bal_principal, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  loan_bal_interest, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  loan_bal_penalty, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  loan_prin_xfrout, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  loan_prin_xfrin, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  loan_fee1_xfrout, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  loan_fee1_xfrin, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  orig_txn_amt, 2),\
	APP_DEFSDMEMBER(T_STRING,  orig_trans_date, 0),\
	APP_DEFSDMEMBER(T_STRING,  orig_auth_code, 0),\
	APP_DEFSDMEMBER(T_LONG,  jpa_version, 0),\
	APP_DEFSDMEMBER(T_STRING,  loan_code, 0),\
	APP_DEFSDMEMBER(T_STRING,  register_id, 0),\
	APP_DEFSDMEMBER(T_DOUBLE,  resch_init_prin, 2),\
	APP_DEFSDMEMBER(T_STRING,  resch_date, 0),\
	APP_DEFSDMEMBER(T_DOUBLE,  bef_resch_fixed_pmt_prin, 2),\
	APP_DEFSDMEMBER(T_LONG,  bef_resch_init_term, 0),\
	APP_DEFSDMEMBER(T_DOUBLE,  bef_resch_first_term_prin, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  bef_resch_final_term_prin, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  bef_resch_init_fee1, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  bef_resch_fixed_fee1, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  bef_resch_first_term_fee1, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  bef_resch_final_term_fee1, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  resch_first_term_fee1, 2),\
	APP_DEFSDMEMBER(T_STRING,  loan_fee_method, 0),\
	APP_DEFSDMEMBER(T_DOUBLE,  interest_rate, 4),\
	APP_DEFSDMEMBER(T_DOUBLE,  penalty_rate, 4),\
	APP_DEFSDMEMBER(T_DOUBLE,  compound_rate, 4),\
	APP_DEFSDMEMBER(T_DOUBLE,  float_rate, 2),\
	APP_DEFSDMEMBER(T_STRING,  loan_receipt_nbr, 0),\
	APP_DEFSDMEMBER(T_STRING,  loan_expire_date, 0),\
	APP_DEFSDMEMBER(T_STRING,  loan_cd, 0),\
	APP_DEFSDMEMBER(T_STRING,  payment_hist, 0),\
	APP_DEFSDMEMBER(T_DOUBLE,  ctd_payment_amt, 2),\
	APP_DEFSDMEMBER(T_LONG,  past_resch_cnt, 0),\
	APP_DEFSDMEMBER(T_LONG,  past_shorted_cnt, 0),\
	APP_DEFSDMEMBER(T_DOUBLE,  adv_pmt_amt, 2),\
	APP_DEFSDMEMBER(T_STRING,  last_action_date, 0),\
	APP_DEFSDMEMBER(T_STRING,  last_action_type, 0),\
	APP_DEFSDMEMBER(T_STRING,  last_modified_datetime, 0),\
	APP_DEFSDMEMBER(T_STRING,  activate_date, 0),\
	APP_DEFSDMEMBER(T_STRING,  interest_calc_base, 0),\
	APP_DEFSDMEMBER(T_STRING,  first_bill_date, 0),\
	APP_DEFSDMEMBER(T_STRING,  age_cd, 0),\
	APP_DEFSDMEMBER(T_STRING,  recalc_ind, 0),\
	APP_DEFSDMEMBER(T_STRING,  recalc_date, 0),\
	APP_DEFSDMEMBER(T_STRING,  grace_date, 0),\
	APP_DEFSDMEMBER(T_STRING,  cancel_date, 0),\
	APP_DEFSDMEMBER(T_STRING,  cancel_reason, 0),\
	APP_DEFSDMEMBER(T_STRING,  bank_group_id, 0),\
	APP_DEFSDMEMBER(T_LONG,  due_days, 0),\
	APP_DEFSDMEMBER(T_STRING,  contract_ver, 0),\
	APP_DEFSDMEMBER(T_DOUBLE,  loan_init_interest, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  bef_init_interest, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  bank_proportion, 2),\
	APP_DEFSDMEMBER(T_STRING,  is_check_flag, 0),\
	APP_DEFSDMEMBER(T_STRING,  extend_param1, 0),\
	APP_DEFSDMEMBER(T_STRING,  extend_param2, 0),\
	APP_DEFSDMEMBER(T_STRING,  extend_param3, 0)


	APP_DECLAREFIELDS(SD_ICPS_WB_TM_LOAN)
#undef SD_DATA
#undef SD_MEMBERS

#endif  /*end of __ICPS_WB_TM_LOAN_H__*/
