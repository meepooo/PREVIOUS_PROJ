/***********************************************************************
版权所有:恒生电子股份有限公司
项目名称:综合技术平台(Turandot)项目
版    本:V1.00
操作系统:
数 据 库:INFORMIX
文 件 名:ICPS_JB_LENDING_DETAIL.h
文件描述:结构定义数据库开发嵌C头文件
项 目 组:
程 序 员:[wangzh14925]
发布时间:2009-4-29 19:40:39 [Gen]
修    订:
修改时间:
************************************************************************
表    名:ICPS_JB_LENDING_DETAIL (F_JB2.在途支用明细文件)
说    明:
************************************************************************
修改记录:
修改日期:
修改内容:
修 改 人:
修改内容:
************************************************************************/
#ifndef __ICPS_JB_LENDING_DETAIL_H__
#define __ICPS_JB_LENDING_DETAIL_H__
typedef struct TDB_ICPS_JB_LENDING_DETAIL
{
	char   busi_date[8+1];  /*业务日期*/
		/*业务日期*/
	int   file_order;  /*文件序号*/
		/*文件序号*/
	char   contract_no[64+1];  /*借呗平台贷款合同号*/
		/*借呗平台贷款合同号*/
	char   fund_seq_no[64+1];  /*放款资金流水号*/
		/*放款资金流水号*/
	char   third_product_code[64+1];  /*产品码*/
		/*产品码*/
	char   name[128+1];  /*客户真实姓名*/
		/*客户真实姓名*/
	char   id_type[2+1];  /*证件类型*/
		/*证件类型*/
	char   id_num[32+1];  /*客户证件号码*/
		/*客户证件号码*/
	char   loan_status[2+1];  /*贷款状态*/
		/*贷款状态 1-成功 2-失败 3-在途*/
	char   loan_use[2+1];  /*贷款用途*/
		/*贷款用途 1-消费 2-经营*/
	char   use_area[2+1];  /*贷款资金使用位置*/
		/*贷款资金使用位置 0-境外 1-境内*/
	char   apply_date[20+1];  /*申请支用时间*/
		/*申请支用时间 YYYYMMDDHHMMSS*/
	char   encash_date[20+1];  /*放款日期*/
		/*放款日期 YYYYMMDDHHMMSS*/
	char   currency[3+1];  /*币种*/
		/*币种 CNY*/
	double   encash_amt;  /*放款金额*/
		/*放款金额*/
	char   start_date[8+1];  /*贷款起息日*/
		/*贷款起息日 YYYYMMDD*/
	char   end_date[8+1];  /*贷款到期日*/
		/*贷款到期日 YYYYMMDD*/
	int   total_terms;  /*贷款期次数*/
		/*贷款期次数*/
	char   repay_mode[8+1];  /*还款方式*/
		/*还款方式 1-等额本息 2-等额本金 6-按期付息到期一次还本*/
	int   grace_day;  /*宽限期天数*/
		/*宽限期天数*/
	char   rate_type[2+1];  /*利率类型*/
		/*利率类型 F-固定利率 L0-浮动利率-按日 L1-浮动利率-按周 L2-浮动利率-按月 L3-浮动利率-按季 L4-浮动利率-按半年 L5-浮动利率-按年 L9-浮动利率-其它*/
	double   day_rate;  /*贷款日利率*/
		/*贷款日利率*/
	char   prin_repay_frequency[2+1];  /*本金还款频率*/
		/*本金还款频率，该笔贷款连续两次还款时间的间隔。01:日02:周03:月04:季05:半年06:年07:一次性08:不定期（贷款期限内任意时间还款）99:其他*/
	char   int_repay_frequency[2+1];  /*利息还款频率*/
		/*本金还款频率，该笔贷款连续两次还款时间的间隔。01:日02:周03:月04:季05:半年06:年07:一次性08:不定期（贷款期限内任意时间还款）99:其他*/
	char   guarantee_type[3+1];  /*担保类型*/
		/*担保类型，A 质押贷款B 抵押贷款B01   房地产抵押贷款B99   其他抵押贷款C 保证贷款C01   联保贷款C99   其他保证贷款D 信用/免担保贷款E 组合担保Z 其他*/
	char   credit_no[64+1];  /*授信编号*/
		/*授信编号*/
	char   encash_acct_type[2+1];  /*放款帐号类型*/
		/*放款帐号类型，01:银行借记卡02:支付宝*/
	char   encash_acct[32+1];  /*放款帐号*/
		/*放款帐号*/
	char   repay_acct_type[2+1];  /*还款帐号类型*/
		/*还款帐号类型，01:银行借记卡02:支付宝*/
	char   repay_acct[32+1];  /*还款帐号*/
		/*还款帐号*/
	char   loan_apply_no[32+1];  /*贷款申请单号*/
		/*贷款申请单号*/
	char   is_check_flag[1+1];  /*参与对账标识*/
		/*参与对账标识*/
	char   extend_param1[100+1];  /*扩展1*/
		/*扩展1*/
	char   extend_param2[250+1];  /*扩展2*/
		/*扩展2*/
	char   extend_param3[40+1];  /*扩展3*/
		/*扩展3*/

}ICPS_JB_LENDING_DETAIL;

#define SD_DATA  ICPS_JB_LENDING_DETAIL
#define SD_MEMBERS \
	APP_DEFSDMEMBER(T_STRING,  busi_date, 0),\
	APP_DEFSDMEMBER(T_LONG,  file_order, 0),\
	APP_DEFSDMEMBER(T_STRING,  contract_no, 0),\
	APP_DEFSDMEMBER(T_STRING,  fund_seq_no, 0),\
	APP_DEFSDMEMBER(T_STRING,  third_product_code, 0),\
	APP_DEFSDMEMBER(T_STRING,  name, 0),\
	APP_DEFSDMEMBER(T_STRING,  id_type, 0),\
	APP_DEFSDMEMBER(T_STRING,  id_num, 0),\
	APP_DEFSDMEMBER(T_STRING,  loan_status, 0),\
	APP_DEFSDMEMBER(T_STRING,  loan_use, 0),\
	APP_DEFSDMEMBER(T_STRING,  use_area, 0),\
	APP_DEFSDMEMBER(T_STRING,  apply_date, 0),\
	APP_DEFSDMEMBER(T_STRING,  encash_date, 0),\
	APP_DEFSDMEMBER(T_STRING,  currency, 0),\
	APP_DEFSDMEMBER(T_DOUBLE,  encash_amt, 2),\
	APP_DEFSDMEMBER(T_STRING,  start_date, 0),\
	APP_DEFSDMEMBER(T_STRING,  end_date, 0),\
	APP_DEFSDMEMBER(T_LONG,  total_terms, 0),\
	APP_DEFSDMEMBER(T_STRING,  repay_mode, 0),\
	APP_DEFSDMEMBER(T_LONG,  grace_day, 0),\
	APP_DEFSDMEMBER(T_STRING,  rate_type, 0),\
	APP_DEFSDMEMBER(T_DOUBLE,  day_rate, 6),\
	APP_DEFSDMEMBER(T_STRING,  prin_repay_frequency, 0),\
	APP_DEFSDMEMBER(T_STRING,  int_repay_frequency, 0),\
	APP_DEFSDMEMBER(T_STRING,  guarantee_type, 0),\
	APP_DEFSDMEMBER(T_STRING,  credit_no, 0),\
	APP_DEFSDMEMBER(T_STRING,  encash_acct_type, 0),\
	APP_DEFSDMEMBER(T_STRING,  encash_acct, 0),\
	APP_DEFSDMEMBER(T_STRING,  repay_acct_type, 0),\
	APP_DEFSDMEMBER(T_STRING,  repay_acct, 0),\
	APP_DEFSDMEMBER(T_STRING,  loan_apply_no, 0),\
	APP_DEFSDMEMBER(T_STRING,  is_check_flag, 0),\
	APP_DEFSDMEMBER(T_STRING,  extend_param1, 0),\
	APP_DEFSDMEMBER(T_STRING,  extend_param2, 0),\
	APP_DEFSDMEMBER(T_STRING,  extend_param3, 0)


	APP_DECLAREFIELDS(SD_ICPS_JB_LENDING_DETAIL)
#undef SD_DATA
#undef SD_MEMBERS

#endif  /*end of __ICPS_JB_LENDING_DETAIL_H__*/
