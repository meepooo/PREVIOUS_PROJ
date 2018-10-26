/***********************************************************************
版权所有:恒生电子股份有限公司
项目名称:综合技术平台(Turandot)项目
版    本:V1.00
操作系统:
数 据 库:INFORMIX
文 件 名:ICPS_BANK_CREDIT.h
文件描述:结构定义数据库开发嵌C头文件
项 目 组:
程 序 员:[wangzh14925]
发布时间:2009-4-29 19:40:39 [Gen]
修    订:
修改时间:
************************************************************************
表    名:ICPS_BANK_CREDIT (5.银行征信信息)
说    明:
************************************************************************
修改记录:
修改日期:
修改内容:
修 改 人:
修改内容:
************************************************************************/
#ifndef __ICPS_BANK_CREDIT_H__
#define __ICPS_BANK_CREDIT_H__
typedef struct TDB_ICPS_BANK_CREDIT
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
	char   is_exist_customer[1+1];  /*是否存量客户*/
		/*是否存量客户 1-是 0-否*/
	char   is_exist_debt_customer[1+1];  /*是否存量借记卡客户*/
		/*是否存量借记卡客户 1-是 0-否*/
	double   balance;  /*卡内余额*/
		/*卡内余额*/
	double   avg_balance_last_3days;  /*近3个月日均余额*/
		/*近3个月日均余额*/
	double   avg_balance_last_6days;  /*近6个月日均余额*/
		/*近6个月日均余额*/
	double   income_last_3m;  /*近3个月银行流水收入金额数*/
		/*近3个月银行流水收入金额数*/
	double   pay_last_3m;  /*近3个月银行流水支出金额数*/
		/*近3个月银行流水支出金额数*/
	double   income_last_6m;  /*近6个月银行流水收入金额数*/
		/*近6个月银行流水收入金额数*/
	double   pay_last_6m;  /*近6个月银行流水支出金额数*/
		/*近6个月银行流水支出金额数*/
	char   is_exist_credit_customer[1+1];  /*是否存量信用卡客户*/
		/*是否存量信用卡客户 1-是 0-否*/
	double   curr_credit_card_amt;  /*本行信用卡授信额度*/
		/*本行信用卡授信额度*/
	double   curr_use_credit_card_amt;  /*本行信用卡当前使用额度*/
		/*本行信用卡当前使用额度*/
	char   is_exist_fin_customer[1+1];  /*是否存量理财客户*/
		/*是否存量理财客户 1-是 0-否*/
	double   fin_balance;  /*理财余额*/
		/*理财余额*/
	double   avg_fin_bal_last_6m;  /*近6个月日均理余额*/
		/*近6个月日均理余额*/
	char   is_exist_insurance_customer[1+1];  /*是否存量保险客户*/
		/*是否存量保险客户 1-是 0-否*/
	char   is_exist_loan_customer[1+1];  /*是否存量贷款客户*/
		/*是否存量贷款客户 1-是 0-否*/
	double   operation_loan_bal;  /*经营类贷款总余额*/
		/*经营类贷款总余额*/
	double   personal_credit_bal;  /*个人信用类贷总余额*/
		/*个人信用类贷总余额*/
	double   car_loan_bal;  /*车贷余额*/
		/*车贷余额*/
	double   car_asset;  /*车产价值评估额*/
		/*车产价值评估额*/
	double   house_loan_bal;  /*房贷余额*/
		/*房贷余额*/
	double   house_asset;  /*房产价值评估额*/
		/*房产价值评估额*/
	char   is_stock_customer[1+1];  /*是否证券客户*/
		/*是否证券客户 1-是 0-否*/
	char   is_third_depository[1+1];  /*是否第三方存管客户*/
		/*是否第三方存管客户 1-是 0-否*/
	char   is_payroll_customer[1+1];  /*是否工资代发客户*/
		/*是否工资代发客户 1-是 0-否*/
	char   is_social_security_customer[1+1];  /*是否社保代缴客户*/
		/*是否社保代缴客户 1-是 0-否*/
	char   is_life_payment_customer[1+1];  /*是否水电煤代缴客户*/
		/*是否水电煤代缴客户 1-是 0-否*/
	char   company_name[255+1];  /*工作单位*/
		/*工作单位*/
	char   company_origin[1+1];  /*工作单位数据来源*/
		/*工作单位数据来源 1-核实 2-客户填写 3-其他*/
	char   position[64+1];  /*职位*/
		/*职位*/
	char   position_origin[1+1];  /*职位信息来源*/
		/*职位信息来源 1-核实 2-客户填写 3-其他*/
	char   industry[64+1];  /*行业*/
		/*行业*/
	char   industry_origin[1+1];  /*行业信息来源*/
		/*行业信息来源 1-核实 2-客户填写 3-其他*/
	int   work_years;  /*工作年限*/
		/*工作年限*/
	char   work_years_origin[1+1];  /*工作年限信息来源*/
		/*工作年限信息 来源 1-核实 2-客户填写 3-其他*/
	int   income;  /*月收入区间*/
		/*月收入区间*/
	char   income_origin[1+1];  /*月收入信息来源*/
		/*月收入信息来源 1-核实 2-客户填写 3-其他*/
	char   marriage_status[1+1];  /*婚姻状态*/
		/*婚姻状态 1-未婚 2-已婚 3-离婚 4-丧偶 NULL-其他*/
	char   marriage_origin[1+1];  /*婚姻状态信息来源*/
		/*婚姻状态信息来源 1-核实 2-客户填写 3-其他*/
	char   is_operation[1+1];  /*是否经营者*/
		/*是否经营者 （工商企业或个体工商企业主）1-是 0-否*/
	char   operation_origin[1+1];  /*是否经营者信息来源*/
		/*是否经营者信息来源 1-核实 2-客户填写 3-其他*/
	char   is_inner_black_customer[1+1];  /*是否击中内部黑名单客户*/
		/*是否击中内部黑名单客户 1-是 0-否*/
	char   is_police_certified[1+1];  /*是否公安网身份验证成功*/
		/*是否公安网身份验证成功 1- 是 0-否*/
	char   is_court_exec_customer[1+1];  /*是否击中被执行人等涉诉信息*/
		/*是否击中被执行人等涉诉信息 1-是 0-否*/
	char   is_query_house_fund[1+1];  /*是否有查询公积金信息*/
		/*是否有查询公积金信息 1-是 0-否 */
	char   fund_query_date[6+1];  /*公积金查询时间*/
		/*公积金查询时间 YYYYMM*/
	double   fund_month_amt;  /*公积金查询月缴纳额*/
		/*公积金查询月缴纳额*/
	char   fund_acct_date[6+1];  /*公积金开户日期*/
		/*公积金开户日期 YYYYMM*/
	int   fund_months_last_6m;  /*近6个月累计缴纳月数*/
		/*近6个月累计缴纳月数*/
	double   fund_amt_last_6m;  /*近6个月累计缴纳金额*/
		/*近6个月累计缴纳金额*/
	int   fund_total_months;  /*总缴纳月数*/
		/*总缴纳月数*/
	double   fund_total_amt;  /*总缴纳金额*/
		/*总缴纳金额*/
	double   fund_max_amt;  /*公积金属地缴纳上限*/
		/*公积金属地缴纳上限*/
	char   is_query_social_security[1+1];  /*是否有查询社保信息*/
		/*是否有查询社保信息 1-是 0-否 */
	char   social_query_date[6+1];  /*社保信息查询时间*/
		/*社保信息查询时间 YYYYMM*/
	double   pension_query_month_amt;  /*养老保险查询月缴纳额*/
		/*养老保险查询月缴纳额*/
	char   pension_acct_date[6+1];  /*养老保险开户日期*/
		/*养老保险开户日期 YYYYMM*/
	int   pension_months_last_6m;  /*近6个月养老保险累计缴纳月数*/
		/*近6个月养老保险累计缴纳月数*/
	double   pension_amt_last_6m;  /*近6个月养老保险累计缴纳金额*/
		/*近6个月养老保险累计缴纳金额*/
	int   pension_total_months;  /*养老保险总缴纳月数*/
		/*养老保险总缴纳月数*/
	double   pension_total_amt;  /*养老保险总缴纳金额*/
		/*养老保险总缴纳金额*/
	double   medicare_month_amt;  /*医疗保险查询月缴纳额*/
		/*医疗保险查询月缴纳额*/
	char   medicare_acct_date[6+1];  /*医疗保险开户日期*/
		/*医疗保险开户日期 YYYYMM*/
	int   medicare_months_last_6m;  /*近6个月医疗保险累计缴纳月数*/
		/*近6个月医疗保险累计缴纳月数*/
	double   medicare_amt_last_6m;  /*近6个月医疗保险累计缴纳金额*/
		/*近6个月医疗保险累计缴纳金额*/
	int   medicare_total_months;  /*医疗保险总缴纳月数*/
		/*医疗保险总缴纳月数*/
	double   medicare_total_amt;  /*医疗保险总缴纳金额*/
		/*医疗保险总缴纳金额*/
	char   is_query_degree[1+1];  /*是否有查询学历信息*/
		/*是否有查询学历信息 1-是 0-否 */
	char   school_name[64+1];  /*院校名称*/
		/*院校名称*/
	char   degree_level[64+1];  /*学历层次*/
		/*学历层次 高中及以下，专科，学士，硕士，博士及以上*/
	char   degree_type[64+1];  /*学历类别*/
		/*学历类别*/
	char   entrance_year[4+1];  /*入学年份*/
		/*入学年份 YYYY*/
	char   is_query_communication[1+1];  /*是否有查询运营商信息*/
		/*是否有查询运营商信息 1-是 0-否 */
	char   communication[1+1];  /*运营商*/
		/*运营商 1-移动 2-联通 3-电信 4-其他*/
	int   online_days;  /*在网时长*/
		/*在网时长*/
	double   total_tel_fare;  /*总话费账单金额*/
		/*总话费账单金额*/
	int   total_call_hours;  /*半年内通话时长*/
		/*半年内通话时长 按小时向下取整*/
	char   is_out_black_customer[1+1];  /*是否击中外部查询黑名单*/
		/*是否击中外部查询黑名单 1-是 0-否 */
	char   extend_param1[100+1];  /*扩展1*/
		/*扩展1*/
	char   extend_param2[250+1];  /*扩展2*/
		/*扩展2*/
	char   extend_param3[40+1];  /*扩展3*/
		/*扩展3*/

}ICPS_BANK_CREDIT;

#define SD_DATA  ICPS_BANK_CREDIT
#define SD_MEMBERS \ 
	APP_DEFSDMEMBER(T_STRING,  apply_no, 0),\
	APP_DEFSDMEMBER(T_STRING,  plt_date, 0),\
	APP_DEFSDMEMBER(T_STRING,  plt_serial, 0),\
	APP_DEFSDMEMBER(T_STRING,  id_type, 0),\
	APP_DEFSDMEMBER(T_STRING,  id_num, 0),\
	APP_DEFSDMEMBER(T_STRING,  is_exist_customer, 0),\
	APP_DEFSDMEMBER(T_STRING,  is_exist_debt_customer, 0),\
	APP_DEFSDMEMBER(T_DOUBLE,  balance, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  avg_balance_last_3days, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  avg_balance_last_6days, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  income_last_3m, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  pay_last_3m, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  income_last_6m, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  pay_last_6m, 2),\
	APP_DEFSDMEMBER(T_STRING,  is_exist_credit_customer, 0),\
	APP_DEFSDMEMBER(T_DOUBLE,  curr_credit_card_amt, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  curr_use_credit_card_amt, 2),\
	APP_DEFSDMEMBER(T_STRING,  is_exist_fin_customer, 0),\
	APP_DEFSDMEMBER(T_DOUBLE,  fin_balance, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  avg_fin_bal_last_6m, 2),\
	APP_DEFSDMEMBER(T_STRING,  is_exist_insurance_customer, 0),\
	APP_DEFSDMEMBER(T_STRING,  is_exist_loan_customer, 0),\
	APP_DEFSDMEMBER(T_DOUBLE,  operation_loan_bal, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  personal_credit_bal, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  car_loan_bal, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  car_asset, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  house_loan_bal, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  house_asset, 2),\
	APP_DEFSDMEMBER(T_STRING,  is_stock_customer, 0),\
	APP_DEFSDMEMBER(T_STRING,  is_third_depository, 0),\
	APP_DEFSDMEMBER(T_STRING,  is_payroll_customer, 0),\
	APP_DEFSDMEMBER(T_STRING,  is_social_security_customer, 0),\
	APP_DEFSDMEMBER(T_STRING,  is_life_payment_customer, 0),\
	APP_DEFSDMEMBER(T_STRING,  company_name, 0),\
	APP_DEFSDMEMBER(T_STRING,  company_origin, 0),\
	APP_DEFSDMEMBER(T_STRING,  position, 0),\
	APP_DEFSDMEMBER(T_STRING,  position_origin, 0),\
	APP_DEFSDMEMBER(T_STRING,  industry, 0),\
	APP_DEFSDMEMBER(T_STRING,  industry_origin, 0),\
	APP_DEFSDMEMBER(T_LONG,  work_years, 0),\
	APP_DEFSDMEMBER(T_STRING,  work_years_origin, 0),\
	APP_DEFSDMEMBER(T_LONG,  income, 0),\
	APP_DEFSDMEMBER(T_STRING,  income_origin, 0),\
	APP_DEFSDMEMBER(T_STRING,  marriage_status, 0),\
	APP_DEFSDMEMBER(T_STRING,  marriage_origin, 0),\
	APP_DEFSDMEMBER(T_STRING,  is_operation, 0),\
	APP_DEFSDMEMBER(T_STRING,  operation_origin, 0),\
	APP_DEFSDMEMBER(T_STRING,  is_inner_black_customer, 0),\
	APP_DEFSDMEMBER(T_STRING,  is_police_certified, 0),\
	APP_DEFSDMEMBER(T_STRING,  is_court_exec_customer, 0),\
	APP_DEFSDMEMBER(T_STRING,  is_query_house_fund, 0),\
	APP_DEFSDMEMBER(T_STRING,  fund_query_date, 0),\
	APP_DEFSDMEMBER(T_DOUBLE,  fund_month_amt, 2),\
	APP_DEFSDMEMBER(T_STRING,  fund_acct_date, 0),\
	APP_DEFSDMEMBER(T_LONG,  fund_months_last_6m, 0),\
	APP_DEFSDMEMBER(T_DOUBLE,  fund_amt_last_6m, 2),\
	APP_DEFSDMEMBER(T_LONG,  fund_total_months, 0),\
	APP_DEFSDMEMBER(T_DOUBLE,  fund_total_amt, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  fund_max_amt, 2),\
	APP_DEFSDMEMBER(T_STRING,  is_query_social_security, 0),\
	APP_DEFSDMEMBER(T_STRING,  social_query_date, 0),\
	APP_DEFSDMEMBER(T_DOUBLE,  pension_query_month_amt, 2),\
	APP_DEFSDMEMBER(T_STRING,  pension_acct_date, 0),\
	APP_DEFSDMEMBER(T_LONG,  pension_months_last_6m, 0),\
	APP_DEFSDMEMBER(T_DOUBLE,  pension_amt_last_6m, 2),\
	APP_DEFSDMEMBER(T_LONG,  pension_total_months, 0),\
	APP_DEFSDMEMBER(T_DOUBLE,  pension_total_amt, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  medicare_month_amt, 2),\
	APP_DEFSDMEMBER(T_STRING,  medicare_acct_date, 0),\
	APP_DEFSDMEMBER(T_LONG,  medicare_months_last_6m, 0),\
	APP_DEFSDMEMBER(T_DOUBLE,  medicare_amt_last_6m, 2),\
	APP_DEFSDMEMBER(T_LONG,  medicare_total_months, 0),\
	APP_DEFSDMEMBER(T_DOUBLE,  medicare_total_amt, 2),\
	APP_DEFSDMEMBER(T_STRING,  is_query_degree, 0),\
	APP_DEFSDMEMBER(T_STRING,  school_name, 0),\
	APP_DEFSDMEMBER(T_STRING,  degree_level, 0),\
	APP_DEFSDMEMBER(T_STRING,  degree_type, 0),\
	APP_DEFSDMEMBER(T_STRING,  entrance_year, 0),\
	APP_DEFSDMEMBER(T_STRING,  is_query_communication, 0),\
	APP_DEFSDMEMBER(T_STRING,  communication, 0),\
	APP_DEFSDMEMBER(T_LONG,  online_days, 0),\
	APP_DEFSDMEMBER(T_DOUBLE,  total_tel_fare, 2),\
	APP_DEFSDMEMBER(T_LONG,  total_call_hours, 0),\
	APP_DEFSDMEMBER(T_STRING,  is_out_black_customer, 0),\
	APP_DEFSDMEMBER(T_STRING,  extend_param1, 0),\
	APP_DEFSDMEMBER(T_STRING,  extend_param2, 0),\
	APP_DEFSDMEMBER(T_STRING,  extend_param3, 0)


	APP_DECLAREFIELDS(SD_ICPS_BANK_CREDIT)
#undef SD_DATA
#undef SD_MEMBERS

#endif  /*end of __ICPS_BANK_CREDIT_H__*/
