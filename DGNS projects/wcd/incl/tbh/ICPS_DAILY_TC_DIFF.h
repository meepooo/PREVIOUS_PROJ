/***********************************************************************
版权所有:恒生电子股份有限公司
项目名称:综合技术平台(Turandot)项目
版    本:V1.00
操作系统:
数 据 库:DB2
文 件 名:ICPS_DAILY_TC_DIFF.h
文件描述:结构定义数据库开发嵌C头文件
项 目 组:
程 序 员:[wangzh14925]
发布时间:2009-4-29 19:40:39 [Gen]
修    订:
修改时间:
************************************************************************
表    名:ICPS_DAILY_TC_DIFF (F_WB30.总分核对差错表)
说    明:
************************************************************************
修改记录:
修改日期:
修改内容:
修 改 人:
修改内容:
************************************************************************/
#ifndef __ICPS_DAILY_TC_DIFF_H__
#define __ICPS_DAILY_TC_DIFF_H__
typedef struct TDB_ICPS_DAILY_TC_DIFF
{
	char   busi_date[8+1];  /*业务日期*/
		/*业务日期*/
	double   total_bal;  /*本行账户余额*/
		/*本行账户余额*/
	double   reserve_bal;  /*备付金账户*/
		/*备付金账户*/
	double   t_bal;  /*T日切差异*/
		/*T日切差异*/
	double   reserve_diff; /*备付金清算尾差*/
	   /*备付金清算尾差*/
	double   financial_diff;  /*账务清算尾差*/
		/*账务清算尾差*/
	double   person_diff;  /*人工还款差异*/
		/*人工还款差异*/
	double   overplay_diff; /*溢缴款还款尾差*/
	   /*溢缴款还款尾差*/       
	double   interest_diff; /*结息*/  
	    /*结息*/                                 
	double   daily_diff; /*差异金额*/     
	    /*差异金额*/                         
  char   extend_param1[100+1];  /*扩展1*/
		/*扩展1*/
	char   extend_param2[250+1];  /*扩展2*/
		/*扩展2*/
	char   extend_param3[40+1];  /*扩展3*/
		/*扩展3*/

}ICPS_DAILY_TC_DIFF;

#define SD_DATA ICPS_DAILY_TC_DIFF 
#define SD_MEMBERS \ 
	APP_DEFSDMEMBER(T_STRING,  busi_date, 0),\
	APP_DEFSDMEMBER(T_DOUBLE,  total_bal, 0),\
	APP_DEFSDMEMBER(T_DOUBLE,  reserve_bal,2),\
	APP_DEFSDMEMBER(T_DOUBLE,  t_bal,2),\
	APP_DEFSDMEMBER(T_DOUBLE,  reserve_diff, 0),\
	APP_DEFSDMEMBER(T_DOUBLE,  financial_diff, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  person_diff, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  overplay_diff, 0),\
	APP_DEFSDMEMBER(T_DOUBLE,  interest_diff, 0),\
	APP_DEFSDMEMBER(T_DOUBLE,  daily_diff, 0),\
  APP_DEFSDMEMBER(T_STRING,  extend_param1, 0),\
  APP_DEFSDMEMBER(T_STRING,  extend_param2, 0),\
	APP_DEFSDMEMBER(T_STRING,  extend_param3, 0)

	APP_DECLAREFIELDS(SD_ICPS_DAILY_TC_DIFF)
#undef SD_DATA
#undef SD_MEMBERS

#endif  /*end of __ICPS_DAILY_TC_DIFF__*/
