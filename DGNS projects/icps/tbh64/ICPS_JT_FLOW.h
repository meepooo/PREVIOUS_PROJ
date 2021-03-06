/***********************************************************************
版权所有:恒生电子股份有限公司
项目名称:综合技术平台(Turandot)项目
版    本:V1.00
操作系统:
数 据 库:INFORMIX
文 件 名:ICPS_JT_FLOW.h
文件描述:结构定义数据库开发嵌C头文件
项 目 组:
程 序 员:[wangzh14925]
发布时间:2009-4-29 19:40:39 [Gen]
修    订:
修改时间:
************************************************************************
表    名:ICPS_JT_FLOW (F_JT7.贷款还款明细信息文件)
说    明:
************************************************************************
修改记录:
修改日期:
修改内容:
修 改 人:
修改内容:
************************************************************************/
#ifndef __ICPS_JT_FLOW_H__
#define __ICPS_JT_FLOW_H__
typedef struct TDB_ICPS_JT_FLOW
{
	char   busi_date[8+1];  /*业务日期*/
		/*业务日期YYYYMMDD*/
	int   file_order;  /*文件序号*/
		/**/
	char   contract_no[64+1];  /*合同号*/
		/*客户签订的合同号码*/
	char   product_code[4+1];  /*产品编号*/
		/*产品编号*/
	char   quota_code[60+1];  /*额度编号*/
		/*额度编号*/
	char   loan_code[60+1];  /*贷款编号*/
		/*贷款编号*/
	char   term_no[20+1];  /*分期单号*/
		/*分期单号*/
	char   repay_date[10+1];  /*还款日期*/
		/*还款日期yyyy-MM-dd*/
	char   repay_serial[40+1];  /*流水号*/
		/*流水号*/
	char   repay_mode[6+1];  /*还款方式*/
		/*还款方式 1-等额本金;2-分期还款*/
	double   curr_prin_amt;  /*本期应还本金*/
		/*本期应还本金*/
	double   prin_amt;  /*本金金额*/
		/*实际偿还本金金额*/
	double   curr_int_amt;  /*本期应还利息*/
		/*本期应还利息*/
	double   int_amt;  /*利息金额*/
		/*实际偿还利息金额*/
	double   curr_other_amt;  /*本期应还其他金额*/
		/*本期应还其他金额*/
	double   pnlt_amt;  /*罚息金额*/
		/*罚息金额*/
	int   repay_order;  /*还款期数*/
		/*还款期数*/
	int   unclear_terms;  /*剩余还款期数*/
		/*剩余还款期数*/
	char   repay_amt_type[6+1];  /*还款类型*/
		/*还款类型 01按期还款、02提前还款、03逾期还款、04退货、05冲销、06差额补足、07归还差额补足*/
	char   is_check_flag[1+1];  /*参与对账标识*/
		/*参与对账标识*/
	char   extend_param1[100+1];  /*扩展1*/
		/*扩展1*/
	char   extend_param2[250+1];  /*扩展2*/
		/*扩展2*/
	char   extend_param3[40+1];  /*扩展3*/
		/*扩展3*/

}ICPS_JT_FLOW;

#define SD_DATA  ICPS_JT_FLOW
#define SD_MEMBERS \ 
	APP_DEFSDMEMBER(T_STRING,  busi_date, 0),\
	APP_DEFSDMEMBER(T_LONG,  file_order, 0),\
	APP_DEFSDMEMBER(T_STRING,  contract_no, 0),\
	APP_DEFSDMEMBER(T_STRING,  product_code, 0),\
	APP_DEFSDMEMBER(T_STRING,  quota_code, 0),\
	APP_DEFSDMEMBER(T_STRING,  loan_code, 0),\
	APP_DEFSDMEMBER(T_STRING,  term_no, 0),\
	APP_DEFSDMEMBER(T_STRING,  repay_date, 0),\
	APP_DEFSDMEMBER(T_STRING,  repay_serial, 0),\
	APP_DEFSDMEMBER(T_STRING,  repay_mode, 0),\
	APP_DEFSDMEMBER(T_DOUBLE,  curr_prin_amt, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  prin_amt, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  curr_int_amt, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  int_amt, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  curr_other_amt, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  pnlt_amt, 2),\
	APP_DEFSDMEMBER(T_LONG,  repay_order, 0),\
	APP_DEFSDMEMBER(T_LONG,  unclear_terms, 0),\
	APP_DEFSDMEMBER(T_STRING,  repay_amt_type, 0),\
	APP_DEFSDMEMBER(T_STRING,  is_check_flag, 0),\
	APP_DEFSDMEMBER(T_STRING,  extend_param1, 0),\
	APP_DEFSDMEMBER(T_STRING,  extend_param2, 0),\
	APP_DEFSDMEMBER(T_STRING,  extend_param3, 0)


	APP_DECLAREFIELDS(SD_ICPS_JT_FLOW)
#undef SD_DATA
#undef SD_MEMBERS

#endif  /*end of __ICPS_JT_FLOW_H__*/
