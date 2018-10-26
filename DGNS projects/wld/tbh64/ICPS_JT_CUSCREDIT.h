/***********************************************************************
版权所有:恒生电子股份有限公司
项目名称:综合技术平台(Turandot)项目
版    本:V1.00
操作系统:
数 据 库:INFORMIX
文 件 名:ICPS_JT_CUSCREDIT.h
文件描述:结构定义数据库开发嵌C头文件
项 目 组:
程 序 员:[wangzh14925]
发布时间:2009-4-29 19:40:39 [Gen]
修    订:
修改时间:
************************************************************************
表    名:ICPS_JT_CUSCREDIT (F_JT3.授信额度信息文件)
说    明:
************************************************************************
修改记录:
修改日期:
修改内容:
修 改 人:
修改内容:
************************************************************************/
#ifndef __ICPS_JT_CUSCREDIT_H__
#define __ICPS_JT_CUSCREDIT_H__
typedef struct TDB_ICPS_JT_CUSCREDIT
{
	char   busi_date[8+1];  /*业务日期*/
		/*业务日期YYYYMMDD*/
	int   file_order;  /*文件序号*/
		/**/
	char   customer_code[60+1];  /*客户编号*/
		/*客户编号*/
	char   product_code[4+1];  /*产品编号*/
		/*产品编号*/
	char   quota_code[60+1];  /*额度编号*/
		/*额度编号*/
	char   currency[3+1];  /*币种*/
		/*币种*/
	char   cycle_quota_flag[1+1];  /*循环额度标志*/
		/*循环额度标志*/
	char   start_date[8+1];  /*授信生效起始日期*/
		/*授信生效起始日期*/
	char   end_date[8+1];  /*授信到期日*/
		/*授信到期日*/
	double   quota;  /*授信额度*/
		/*授信额度*/
	int   limit;  /*授信期限*/
		/*授信期限*/
	double   nouse_quota;  /*未动拨授信额度*/
		/*未动拨授信额度*/
	char   tmp_quota_flag[4+1];  /*是否临时额度*/
		/*是否临时额度*/
	char   auth_status[3+1];  /*授信状态*/
		/*授信状态*/
	char   is_check_flag[1+1];  /*参与对账标识*/
		/*参与对账标识*/
	char   extend_param1[100+1];  /*扩展1*/
		/*扩展1*/
	char   extend_param2[250+1];  /*扩展2*/
		/*扩展2*/
	char   extend_param3[40+1];  /*扩展3*/
		/*扩展3*/

}ICPS_JT_CUSCREDIT;

#define SD_DATA  ICPS_JT_CUSCREDIT
#define SD_MEMBERS \ 
	APP_DEFSDMEMBER(T_STRING,  busi_date, 0),\
	APP_DEFSDMEMBER(T_LONG,  file_order, 0),\
	APP_DEFSDMEMBER(T_STRING,  customer_code, 0),\
	APP_DEFSDMEMBER(T_STRING,  product_code, 0),\
	APP_DEFSDMEMBER(T_STRING,  quota_code, 0),\
	APP_DEFSDMEMBER(T_STRING,  currency, 0),\
	APP_DEFSDMEMBER(T_STRING,  cycle_quota_flag, 0),\
	APP_DEFSDMEMBER(T_STRING,  start_date, 0),\
	APP_DEFSDMEMBER(T_STRING,  end_date, 0),\
	APP_DEFSDMEMBER(T_DOUBLE,  quota, 2),\
	APP_DEFSDMEMBER(T_LONG,  limit, 0),\
	APP_DEFSDMEMBER(T_DOUBLE,  nouse_quota, 2),\
	APP_DEFSDMEMBER(T_STRING,  tmp_quota_flag, 0),\
	APP_DEFSDMEMBER(T_STRING,  auth_status, 0),\
	APP_DEFSDMEMBER(T_STRING,  is_check_flag, 0),\
	APP_DEFSDMEMBER(T_STRING,  extend_param1, 0),\
	APP_DEFSDMEMBER(T_STRING,  extend_param2, 0),\
	APP_DEFSDMEMBER(T_STRING,  extend_param3, 0)


	APP_DECLAREFIELDS(SD_ICPS_JT_CUSCREDIT)
#undef SD_DATA
#undef SD_MEMBERS

#endif  /*end of __ICPS_JT_CUSCREDIT_H__*/
