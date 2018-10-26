/***********************************************************************
版权所有:恒生电子股份有限公司
项目名称:综合技术平台(Turandot)项目
版    本:V1.00
操作系统:
数 据 库:INFORMIX
文 件 名:ICPS_JT_LOAN.h
文件描述:结构定义数据库开发嵌C头文件
项 目 组:
程 序 员:[wangzh14925]
发布时间:2009-4-29 19:40:39 [Gen]
修    订:
修改时间:
************************************************************************
表    名:ICPS_JT_LOAN (F_JT5.贷款借据信息文件)
说    明:
************************************************************************
修改记录:
修改日期:
修改内容:
修 改 人:
修改内容:
************************************************************************/
#ifndef __ICPS_JT_LOAN_H__
#define __ICPS_JT_LOAN_H__
typedef struct TDB_ICPS_JT_LOAN
{
	char   busi_date[8+1];  /*业务日期*/
		/*业务日期YYYYMMDD*/
	int   file_order;  /*文件序号*/
		/**/
	char   contract_no[64+1];  /*合同号*/
		/*客户签订的合同号码*/
	char   customer_code[60+1];  /*客户编号*/
		/*客户编号*/
	char   product_code[4+1];  /*产品编号*/
		/*产品编号*/
	char   quota_code[60+1];  /*额度编号*/
		/*额度编号*/
	char   loan_code[60+1];  /*贷款编号*/
		/*贷款编号*/
	char   currency[3+1];  /*币种*/
		/*币种 默认CNY*/
	char   loan_status[1+1];  /*贷款状态*/
		/*贷款状态 1正常 2逾期 3结清 9其它*/
	char   encash_date[8+1];  /*放款日期*/
		/*放款日期*/
	double   encash_amt;  /*放款金额*/
		/*放款金额*/
	char   end_date[8+1];  /*到期日期*/
		/*到期日期*/
	char   use_area[6+1];  /*贷款资金使用位置*/
		/*贷款资金使用位置 I:境内（中国大陆）O:境外（含港澳台）*/
	char   prin_repay_frequency[6+1];  /*本金还款频率*/
		/*本金还款频率 连续两次还款时间的间隔 01:日 02:周 03:月 04:季 05:半年 06:年 07:一次性08:不定期（贷款期限内任意时间还款）99:其他*/
	char   int_repay_frequency[6+1];  /*利息还款频率*/
		/*利息还款频率 连续两次还款时间的间隔 01:日 02:周 03:月 04:季 05:半年 06:年 07:一次性08:不定期（贷款期限内任意时间还款）99:其他*/
	double   self_pay_amt;  /*自主支付金额*/
		/*自主支付金额*/
	double   entrusted_pay_amt;  /*受托支付金额*/
		/*受托支付金额*/
	char   ovd_flag[1+1];  /*逾期标志*/
		/*逾期标志 1:逾期 0:正常*/
	int   ovd_days;  /*逾期天数*/
		/*逾期天数*/
	int   ovd_non_days;  /*逾期宽限天数*/
		/*逾期宽限天数*/
	char   prin_ovd_days[8+1];  /*本金逾期日期*/
		/*本金逾期日期*/
	char   int_ovd_days[8+1];  /*利息逾期日期*/
		/*利息逾期日期*/
	char   next_int_date[8+1];  /*下一付息日*/
		/*下一付息日*/
	char   rate_type[6+1];  /*利率类型*/
		/*利率类型 F:固定利率 L0:浮动利率-按日 L1:浮动利率-按周 L2:浮动利率-按月 L3:浮动利率-按季 L4:浮动利率-按半年 L5:浮动利率-按年 L9:浮动利率-其它*/
	double   loan_bal;  /*贷款余额*/
		/*贷款余额*/
	double   ovd_loan_bal;  /*逾期贷款余额*/
		/*逾期贷款余额*/
	double   ovd_int;  /*逾期利息*/
		/*逾期利息*/
	double   out_int_bal;  /*表外欠息*/
		/*表外欠息*/
	char   int_flag[1+1];  /*计息标志*/
		/*计息标志 Y:正常计息 N:停止计息*/
	double   accrued_int;  /*应计利息*/
		/*应计利息*/
	double   int_amt;  /*当日利息*/
		/*当日利息*/
	double   pnlt_amt;  /*当日罚息*/
		/*当日罚息*/
	char   encash_acct[64+1];  /*贷款入帐账号*/
		/*贷款入帐账号*/
	char   repay_acct[64+1];  /*还款账号*/
		/*还款账号*/
	char   guarantee_type[3+1];  /*贷款担保方式*/
		/*贷款担保方式 A质押贷款B抵押贷款B01房地产抵押贷款B99其他抵押贷款C保证贷款C01联保贷款C99其他保证贷款D信用/免担保贷款E组合担保Z 其他*/
	char   repay_mode[1+1];  /*还款方式*/
		/*还款方式 1-等额本金;2-分期还款*/
	double   loan_rate;  /*借款利率*/
		/*借款利率*/
	double   penalty_rate;  /*违约金利率*/
		/*违约金利率*/
	char   loan_rate_type[1+1];  /*借款利率类型*/
		/*借款利率类型*/
	char   penalty_rate_type[1+1];  /*违约金利率类型*/
		/*违约金利率类型*/
	char   is_check_flag[1+1];  /*参与对账标识*/
		/*参与对账标识*/
	char   extend_param1[100+1];  /*扩展1*/
		/*扩展1*/
	char   extend_param2[250+1];  /*扩展2*/
		/*扩展2*/
	char   extend_param3[40+1];  /*扩展3*/
		/*扩展3*/

}ICPS_JT_LOAN;

#define SD_DATA  ICPS_JT_LOAN
#define SD_MEMBERS \ 
	APP_DEFSDMEMBER(T_STRING,  busi_date, 0),\
	APP_DEFSDMEMBER(T_LONG,  file_order, 0),\
	APP_DEFSDMEMBER(T_STRING,  contract_no, 0),\
	APP_DEFSDMEMBER(T_STRING,  customer_code, 0),\
	APP_DEFSDMEMBER(T_STRING,  product_code, 0),\
	APP_DEFSDMEMBER(T_STRING,  quota_code, 0),\
	APP_DEFSDMEMBER(T_STRING,  loan_code, 0),\
	APP_DEFSDMEMBER(T_STRING,  currency, 0),\
	APP_DEFSDMEMBER(T_STRING,  loan_status, 0),\
	APP_DEFSDMEMBER(T_STRING,  encash_date, 0),\
	APP_DEFSDMEMBER(T_DOUBLE,  encash_amt, 8),\
	APP_DEFSDMEMBER(T_STRING,  end_date, 0),\
	APP_DEFSDMEMBER(T_STRING,  use_area, 0),\
	APP_DEFSDMEMBER(T_STRING,  prin_repay_frequency, 0),\
	APP_DEFSDMEMBER(T_STRING,  int_repay_frequency, 0),\
	APP_DEFSDMEMBER(T_DOUBLE,  self_pay_amt, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  entrusted_pay_amt, 2),\
	APP_DEFSDMEMBER(T_STRING,  ovd_flag, 0),\
	APP_DEFSDMEMBER(T_LONG,  ovd_days, 0),\
	APP_DEFSDMEMBER(T_LONG,  ovd_non_days, 0),\
	APP_DEFSDMEMBER(T_STRING,  prin_ovd_days, 0),\
	APP_DEFSDMEMBER(T_STRING,  int_ovd_days, 0),\
	APP_DEFSDMEMBER(T_STRING,  next_int_date, 0),\
	APP_DEFSDMEMBER(T_STRING,  rate_type, 0),\
	APP_DEFSDMEMBER(T_DOUBLE,  loan_bal, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  ovd_loan_bal, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  ovd_int, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  out_int_bal, 2),\
	APP_DEFSDMEMBER(T_STRING,  int_flag, 0),\
	APP_DEFSDMEMBER(T_DOUBLE,  accrued_int, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  int_amt, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  pnlt_amt, 2),\
	APP_DEFSDMEMBER(T_STRING,  encash_acct, 0),\
	APP_DEFSDMEMBER(T_STRING,  repay_acct, 0),\
	APP_DEFSDMEMBER(T_STRING,  guarantee_type, 0),\
	APP_DEFSDMEMBER(T_STRING,  repay_mode, 0),\
	APP_DEFSDMEMBER(T_DOUBLE,  loan_rate, 8),\
	APP_DEFSDMEMBER(T_DOUBLE,  penalty_rate, 8),\
	APP_DEFSDMEMBER(T_STRING,  loan_rate_type, 0),\
	APP_DEFSDMEMBER(T_STRING,  penalty_rate_type, 0),\
	APP_DEFSDMEMBER(T_STRING,  is_check_flag, 0),\
	APP_DEFSDMEMBER(T_STRING,  extend_param1, 0),\
	APP_DEFSDMEMBER(T_STRING,  extend_param2, 0),\
	APP_DEFSDMEMBER(T_STRING,  extend_param3, 0)


	APP_DECLAREFIELDS(SD_ICPS_JT_LOAN)
#undef SD_DATA
#undef SD_MEMBERS

#endif  /*end of __ICPS_JT_LOAN_H__*/
