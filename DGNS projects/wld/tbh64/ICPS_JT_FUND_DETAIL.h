/***********************************************************************
版权所有:恒生电子股份有限公司
项目名称:综合技术平台(Turandot)项目
版    本:V1.00
操作系统:
数 据 库:INFORMIX
文 件 名:ICPS_JT_FUND_DETAIL.h
文件描述:结构定义数据库开发嵌C头文件
项 目 组:
程 序 员:[wangzh14925]
发布时间:2009-4-29 19:40:39 [Gen]
修    订:
修改时间:
************************************************************************
表    名:ICPS_JT_FUND_DETAIL (F_JT8.兴业资金流水文件)
说    明:
************************************************************************
修改记录:
修改日期:
修改内容:
修 改 人:
修改内容:
************************************************************************/
#ifndef __ICPS_JT_FUND_DETAIL_H__
#define __ICPS_JT_FUND_DETAIL_H__
typedef struct TDB_ICPS_JT_FUND_DETAIL
{
	char   trans_date[8+1];  /*业务日期*/
		/*业务日期*/
	char   file_type[8+1];  /*文件类型*/
		/*文件类型*/
	int   file_order;  /*文件序号*/
		/**/
	char   trans_time[6+1];  /*交易时间*/
		/*交易时间*/
	char   sys_date[8+1];  /*系统日期*/
		/*系统日期*/
	char   acct_direction[1+1];  /*收支方向*/
		/*收支方向*/
	double   trans_amt;  /*交易金额*/
		/*交易金额*/
	char   summary_code[10+1];  /*摘要代码*/
		/*摘要代码*/
	char   summary[250+1];  /*中文摘要*/
		/*中文摘要*/
	double   acct_bal;  /*账户余额*/
		/*账户余额*/
	char   currency[3+1];  /*货币号*/
		/*货币号*/
	char   peer_acct[36+1];  /*对方账户*/
		/*对方账户*/
	char   peer_acct_name[60+1];  /*对方账户户名*/
		/*对方账户户名*/
	char   remarks[250+1];  /*备注*/
		/*备注*/
	char   is_check_flag[1+1];  /*参与对账标识*/
		/*参与对账标识*/
	char   extend_param1[100+1];  /*扩展1*/
		/*扩展1*/
	char   extend_param2[250+1];  /*扩展2*/
		/*扩展2*/
	char   extend_param3[40+1];  /*扩展3*/
		/*扩展3*/

}ICPS_JT_FUND_DETAIL;

#define SD_DATA  ICPS_JT_FUND_DETAIL
#define SD_MEMBERS \ 
	APP_DEFSDMEMBER(T_STRING,  trans_date, 0),\
	APP_DEFSDMEMBER(T_STRING,  file_type, 0),\
	APP_DEFSDMEMBER(T_LONG,  file_order, 0),\
	APP_DEFSDMEMBER(T_STRING,  trans_time, 0),\
	APP_DEFSDMEMBER(T_STRING,  sys_date, 0),\
	APP_DEFSDMEMBER(T_STRING,  acct_direction, 0),\
	APP_DEFSDMEMBER(T_DOUBLE,  trans_amt, 2),\
	APP_DEFSDMEMBER(T_STRING,  summary_code, 0),\
	APP_DEFSDMEMBER(T_STRING,  summary, 0),\
	APP_DEFSDMEMBER(T_DOUBLE,  acct_bal, 2),\
	APP_DEFSDMEMBER(T_STRING,  currency, 0),\
	APP_DEFSDMEMBER(T_STRING,  peer_acct, 0),\
	APP_DEFSDMEMBER(T_STRING,  peer_acct_name, 0),\
	APP_DEFSDMEMBER(T_STRING,  remarks, 0),\
	APP_DEFSDMEMBER(T_STRING,  is_check_flag, 0),\
	APP_DEFSDMEMBER(T_STRING,  extend_param1, 0),\
	APP_DEFSDMEMBER(T_STRING,  extend_param2, 0),\
	APP_DEFSDMEMBER(T_STRING,  extend_param3, 0)


	APP_DECLAREFIELDS(SD_ICPS_JT_FUND_DETAIL)
#undef SD_DATA
#undef SD_MEMBERS

#endif  /*end of __ICPS_JT_FUND_DETAIL_H__*/
