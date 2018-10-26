/***********************************************************************
版权所有:恒生电子股份有限公司
项目名称:综合技术平台(Turandot)项目
版    本:V1.00
操作系统:
数 据 库:INFORMIX
文 件 名:ICPS_WB_TM_PLAN.h
文件描述:结构定义数据库开发嵌C头文件
项 目 组:
程 序 员:[wangzh14925]
发布时间:2009-4-29 19:40:39 [Gen]
修    订:
修改时间:
************************************************************************
表    名:ICPS_WB_TM_PLAN (F_WB5.信用计划表)
说    明:
************************************************************************
修改记录:
修改日期:
修改内容:
修 改 人:
修改内容:
************************************************************************/
#ifndef __ICPS_WB_TM_PLAN_H__
#define __ICPS_WB_TM_PLAN_H__
typedef struct TDB_ICPS_WB_TM_PLAN
{
	char   busi_date[8+1];  /*业务日期*/
		/*业务日期*/
	int   file_order;  /*文件序号*/
		/*文件序号*/
	char   org[12+1];  /*机构号*/
		/*机构号*/
	char   plan_id[20+1];  /*流水号*/
		/*流水号*/
	char   acct_no[20+1];  /*账户编号*/
		/*账户编号*/
	char   acct_type[1+1];  /*账户类型*/
		/*账户类型*/
	char   logical_card_no[19+1];  /*逻辑卡号*/
		/*逻辑卡号*/
	char   plan_nbr[6+1];  /*信用计划号*/
		/*信用计划号*/
	char   plan_type[1+1];  /*信用计划类型*/
		/*信用计划类型*/
	char   product_code[6+1];  /*产品代码*/
		/*产品代码*/
	char   ref_nbr[23+1];  /*交易参考号*/
		/*交易参考号*/
	double   curr_balance;  /*当前余额*/
		/*当前余额*/
	double   begin_bal;  /*期初余额*/
		/*期初余额*/
	double   dispute_amt;  /*争议金额*/
		/*争议金额*/
	double   tot_due_amt;  /*最小还款额*/
		/*最小还款额*/
	char   plan_add_date[14+1];  /*纪录建立日期*/
		/*纪录建立日期*/
	char   paid_out_date[14+1];  /*还清日期*/
		/*还清日期*/
	double   past_principal;  /*上期本金*/
		/*上期本金*/
	double   past_interest;  /*上期利息*/
		/*上期利息*/
	double   past_card_fee;  /*上期年费*/
		/*上期年费*/
	double   past_ovrlmt_fee;  /*上期超限费*/
		/*上期超限费*/
	double   past_lpc;  /*上期滞纳金*/
		/*上期滞纳金*/
	double   past_nsf_fee;  /*上期资金不足费*/
		/*上期资金不足费*/
	double   past_txn_fee;  /*上期交易费*/
		/*上期交易费*/
	double   past_svc_fee;  /*上期服务费*/
		/*上期服务费*/
	double   past_ins;  /*上期保险金额*/
		/*上期保险金额*/
	double   past_user_fee1;  /*上期自定义费用1*/
		/*上期自定义费用1*/
	double   past_user_fee2;  /*上期自定义费用2*/
		/*上期自定义费用2*/
	double   past_user_fee3;  /*上期自定义费用3*/
		/*上期自定义费用3*/
	double   past_user_fee4;  /*上期自定义费用4*/
		/*上期自定义费用4*/
	double   past_user_fee5;  /*上期自定义费用5*/
		/*上期自定义费用5*/
	double   past_user_fee6;  /*上期自定义费用6*/
		/*上期自定义费用6*/
	double   CTD_PRINCIPAL;  /*当前本金*/
		/*当前本金*/
	double   ctd_interest;  /*当期利息*/
		/*当期利息*/
	double   ctd_card_fee;  /*当期年费*/
		/*当期年费*/
	double   ctd_ovrlmt_fee;  /*当期超限费*/
		/*当期超限费*/
	double   ctd_lpc;  /*当期滞纳金*/
		/*当期滞纳金*/
	double   ctd_nsf_fee;  /*当期资金不足费*/
		/*当期资金不足费*/
	double   ctd_svc_fee;  /*当期服务费*/
		/*当期服务费*/
	double   ctd_txn_fee;  /*当期交易费*/
		/*当期交易费*/
	double   ctd_ins;  /*当期保险金额*/
		/*当期保险金额*/
	double   ctd_user_fee1;  /*当期新增自定义费用1*/
		/*当期新增自定义费用1*/
	double   ctd_user_fee2;  /*当期新增自定义费用2*/
		/*当期新增自定义费用2*/
	double   ctd_user_fee3;  /*当期新增自定义费用3*/
		/*当期新增自定义费用3*/
	double   ctd_user_fee4;  /*当期新增自定义费用4*/
		/*当期新增自定义费用4*/
	double   ctd_user_fee5;  /*当期新增自定义费用5*/
		/*当期新增自定义费用5*/
	double   ctd_user_fee6;  /*当期新增自定义费用6*/
		/*当期新增自定义费用6*/
	double   ctd_amt_db;  /*当期借记金额*/
		/*当期借记金额*/
	double   ctd_amt_cr;  /*当期贷记金额*/
		/*当期贷记金额*/
	int   ctd_nbr_db;  /*当期借记交易笔数*/
		/*当期借记交易笔数*/
	int   ctd_nbr_cr;  /*当期贷记交易笔数*/
		/*当期贷记交易笔数*/
	double   nodefbnp_int_acru;  /*非延迟利息*/
		/*非延迟利息*/
	double   beg_defbnp_int_acru;  /*往期累积延时利息*/
		/*往期累积延时利息*/
	double   ctd_defbnp_int_acru;  /*当期累积延时利息*/
		/*当期累积延时利息*/
	char   user_field146[4+1];  /*备用字段146*/
		/*备用字段146*/
	char   user_field147[4+1];  /*备用字段147*/
		/*备用字段147*/
	char   user_field148[4+1];  /*备用字段148*/
		/*备用字段148*/
	char   user_field149[4+1];  /*备用字段149*/
		/*备用字段149*/
	char   user_field150[4+1];  /*备用字段150*/
		/*备用字段150*/
	char   user_field151[4+1];  /*备用字段151*/
		/*备用字段151*/
	int   user_field152;  /*备用字段152*/
		/*备用字段152*/
	int   user_field153;  /*备用字段153*/
		/*备用字段153*/
	int   user_field154;  /*备用字段154*/
		/*备用字段154*/
	int   user_field155;  /*备用字段155*/
		/*备用字段155*/
	int   user_field156;  /*备用字段156*/
		/*备用字段156*/
	int   user_field157;  /*备用字段157*/
		/*备用字段157*/
	char   user_field158[40+1];  /*备用字段158*/
		/*备用字段158*/
	char   user_field159[40+1];  /*备用字段159*/
		/*备用字段159*/
	char   user_field160[40+1];  /*备用字段160*/
		/*备用字段160*/
	char   user_field161[40+1];  /*备用字段161*/
		/*备用字段161*/
	char   user_field162[40+1];  /*备用字段162*/
		/*备用字段162*/
	char   user_field163[40+1];  /*备用字段163*/
		/*备用字段163*/
	char   user_field164[14+1];  /*备用字段164*/
		/*备用字段164*/
	char   user_field165[14+1];  /*备用字段165*/
		/*备用字段165*/
	char   user_field166[14+1];  /*备用字段166*/
		/*备用字段166*/
	char   user_field167[14+1];  /*备用字段167*/
		/*备用字段167*/
	char   user_field168[14+1];  /*备用字段168*/
		/*备用字段168*/
	char   user_field169[14+1];  /*备用字段169*/
		/*备用字段169*/
	double   user_field170;  /*备用字段170*/
		/*备用字段170*/
	double   user_field171;  /*备用字段171*/
		/*备用字段171*/
	double   user_field172;  /*备用字段172*/
		/*备用字段172*/
	double   user_field173;  /*备用字段173*/
		/*备用字段173*/
	double   user_field174;  /*备用字段174*/
		/*备用字段174*/
	double   user_field175;  /*备用字段175*/
		/*备用字段175*/
	int   jpa_version;  /*乐观锁版本号*/
		/*乐观锁版本号*/
	double   past_penalty;  /*往期罚息*/
		/*往期罚息*/
	double   ctd_penalty;  /*当期罚息*/
		/*当期罚息*/
	double   past_compound;  /*往期复利*/
		/*往期复利*/
	double   ctd_compound;  /*当期复利*/
		/*当期复利*/
	double   penalty_acru;  /*罚息累计*/
		/*罚息累计*/
	double   compound_acru;  /*复利累计*/
		/*复利累计*/
	double   interest_rate;  /*基础利率*/
		/*基础利率*/
	double   penalty_rate;  /*罚息利率*/
		/*罚息利率*/
	double   compound_rate;  /*复利利率*/
		/*复利利率*/
	char   use_plan_rate[1+1];  /*是否使用plan的利率*/
		/*是否使用plan的利率*/
	char   last_pmt_date[14+1];  /*上一还款日期*/
		/*上一还款日期*/
	int   term;  /*所在贷款期数*/
		/*所在贷款期数*/
	char   calc_type[1+1];  /*计费类型*/
		/*计费类型*/
	int   calc_cycle;  /*计费周期*/
		/*计费周期*/
	double   fee_rate;  /*费率*/
		/*费率*/
	char   last_fee_date[14+1];  /*上一收费日*/
		/*上一收费日*/
	char   next_fee_date[14+1];  /*下一收费日*/
		/*下一收费日*/
	char   trans_serial[20+1];  /*交易流水号*/
		/*交易流水号*/
	char   first_dd_date[14+1];  /*首次约定还款日期*/
		/*交易流水号*/
	char   busi_serial[32+1];  /*业务流水号*/
		/*业务流水号*/
	char   sys_trans_id[32+1];  /*系统调用流水号*/
		/*系统调用流水号*/
	char   user_field176[15+1];  /*备用字段176*/
		/*备用字段176*/
	char   sub_terminal_type[15+1];  /*终端类型*/
		/*终端类型*/
	char   sub_merch_id[40+1];  /*二级商户编码*/
		/*二级商户编码*/
	char   sub_merch_name[60+1];  /*二级商户名称*/
		/*二级商户名称*/
	char   wares_desc[60+1];  /*商品信息*/
		/*商品信息*/
	char   last_modified_datetime[14+1];  /*修改时间*/
		/*修改时间*/
	double   original_amt;  /*原始交易本金*/
		/*原始交易本金*/
	char   interest_calc_base[1+1];  /*计息基数*/
		/*计息基数*/
	char   created_datetime[14+1];  /*创建时间*/
		/*创建时间*/
	char   is_check_flag[1+1];  /*参与对账标识*/
		/*参与对账标识*/
	char   extend_param1[100+1];  /*扩展1*/
		/*扩展1*/
	char   extend_param2[250+1];  /*扩展2*/
		/*扩展2*/
	char   extend_param3[40+1];  /*扩展3*/
		/*扩展3*/

}ICPS_WB_TM_PLAN;

#define SD_DATA  ICPS_WB_TM_PLAN
#define SD_MEMBERS \ 
	APP_DEFSDMEMBER(T_STRING,  busi_date, 0),\
	APP_DEFSDMEMBER(T_LONG,  file_order, 0),\
	APP_DEFSDMEMBER(T_STRING,  org, 0),\
	APP_DEFSDMEMBER(T_STRING,  plan_id, 0),\
	APP_DEFSDMEMBER(T_STRING,  acct_no, 0),\
	APP_DEFSDMEMBER(T_STRING,  acct_type, 0),\
	APP_DEFSDMEMBER(T_STRING,  logical_card_no, 0),\
	APP_DEFSDMEMBER(T_STRING,  plan_nbr, 0),\
	APP_DEFSDMEMBER(T_STRING,  plan_type, 0),\
	APP_DEFSDMEMBER(T_STRING,  product_code, 0),\
	APP_DEFSDMEMBER(T_STRING,  ref_nbr, 0),\
	APP_DEFSDMEMBER(T_DOUBLE,  curr_balance, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  begin_bal, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  dispute_amt, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  tot_due_amt, 2),\
	APP_DEFSDMEMBER(T_STRING,  plan_add_date, 0),\
	APP_DEFSDMEMBER(T_STRING,  paid_out_date, 0),\
	APP_DEFSDMEMBER(T_DOUBLE,  past_principal, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  past_interest, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  past_card_fee, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  past_ovrlmt_fee, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  past_lpc, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  past_nsf_fee, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  past_txn_fee, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  past_svc_fee, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  past_ins, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  past_user_fee1, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  past_user_fee2, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  past_user_fee3, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  past_user_fee4, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  past_user_fee5, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  past_user_fee6, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  CTD_PRINCIPAL, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  ctd_interest, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  ctd_card_fee, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  ctd_ovrlmt_fee, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  ctd_lpc, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  ctd_nsf_fee, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  ctd_svc_fee, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  ctd_txn_fee, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  ctd_ins, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  ctd_user_fee1, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  ctd_user_fee2, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  ctd_user_fee3, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  ctd_user_fee4, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  ctd_user_fee5, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  ctd_user_fee6, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  ctd_amt_db, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  ctd_amt_cr, 2),\
	APP_DEFSDMEMBER(T_LONG,  ctd_nbr_db, 0),\
	APP_DEFSDMEMBER(T_LONG,  ctd_nbr_cr, 0),\
	APP_DEFSDMEMBER(T_DOUBLE,  nodefbnp_int_acru, 4),\
	APP_DEFSDMEMBER(T_DOUBLE,  beg_defbnp_int_acru, 4),\
	APP_DEFSDMEMBER(T_DOUBLE,  ctd_defbnp_int_acru, 4),\
	APP_DEFSDMEMBER(T_STRING,  user_field146, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field147, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field148, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field149, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field150, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field151, 0),\
	APP_DEFSDMEMBER(T_LONG,  user_field152, 0),\
	APP_DEFSDMEMBER(T_LONG,  user_field153, 0),\
	APP_DEFSDMEMBER(T_LONG,  user_field154, 0),\
	APP_DEFSDMEMBER(T_LONG,  user_field155, 0),\
	APP_DEFSDMEMBER(T_LONG,  user_field156, 0),\
	APP_DEFSDMEMBER(T_LONG,  user_field157, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field158, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field159, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field160, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field161, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field162, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field163, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field164, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field165, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field166, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field167, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field168, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field169, 0),\
	APP_DEFSDMEMBER(T_DOUBLE,  user_field170, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  user_field171, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  user_field172, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  user_field173, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  user_field174, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  user_field175, 2),\
	APP_DEFSDMEMBER(T_LONG,  jpa_version, 0),\
	APP_DEFSDMEMBER(T_DOUBLE,  past_penalty, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  ctd_penalty, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  past_compound, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  ctd_compound, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  penalty_acru, 4),\
	APP_DEFSDMEMBER(T_DOUBLE,  compound_acru, 4),\
	APP_DEFSDMEMBER(T_DOUBLE,  interest_rate, 4),\
	APP_DEFSDMEMBER(T_DOUBLE,  penalty_rate, 4),\
	APP_DEFSDMEMBER(T_DOUBLE,  compound_rate, 4),\
	APP_DEFSDMEMBER(T_STRING,  use_plan_rate, 0),\
	APP_DEFSDMEMBER(T_STRING,  last_pmt_date, 0),\
	APP_DEFSDMEMBER(T_LONG,  term, 0),\
	APP_DEFSDMEMBER(T_STRING,  calc_type, 0),\
	APP_DEFSDMEMBER(T_LONG,  calc_cycle, 0),\
	APP_DEFSDMEMBER(T_DOUBLE,  fee_rate, 4),\
	APP_DEFSDMEMBER(T_STRING,  last_fee_date, 0),\
	APP_DEFSDMEMBER(T_STRING,  next_fee_date, 0),\
	APP_DEFSDMEMBER(T_STRING,  trans_serial, 0),\
	APP_DEFSDMEMBER(T_STRING,  first_dd_date, 0),\
	APP_DEFSDMEMBER(T_STRING,  busi_serial, 0),\
	APP_DEFSDMEMBER(T_STRING,  sys_trans_id, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field176, 0),\
	APP_DEFSDMEMBER(T_STRING,  sub_terminal_type, 0),\
	APP_DEFSDMEMBER(T_STRING,  sub_merch_id, 0),\
	APP_DEFSDMEMBER(T_STRING,  sub_merch_name, 0),\
	APP_DEFSDMEMBER(T_STRING,  wares_desc, 0),\
	APP_DEFSDMEMBER(T_STRING,  last_modified_datetime, 0),\
	APP_DEFSDMEMBER(T_DOUBLE,  original_amt, 4),\
	APP_DEFSDMEMBER(T_STRING,  interest_calc_base, 0),\
	APP_DEFSDMEMBER(T_STRING,  created_datetime, 0),\
	APP_DEFSDMEMBER(T_STRING,  is_check_flag, 0),\
	APP_DEFSDMEMBER(T_STRING,  extend_param1, 0),\
	APP_DEFSDMEMBER(T_STRING,  extend_param2, 0),\
	APP_DEFSDMEMBER(T_STRING,  extend_param3, 0)


	APP_DECLAREFIELDS(SD_ICPS_WB_TM_PLAN)
#undef SD_DATA
#undef SD_MEMBERS

#endif  /*end of __ICPS_WB_TM_PLAN_H__*/
