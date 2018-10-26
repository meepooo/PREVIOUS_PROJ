/***********************************************************************
版权所有:恒生电子股份有限公司
项目名称:综合技术平台(Turandot)项目
版    本:V1.00
操作系统:
数 据 库:INFORMIX
文 件 名:ICPS_JT_CUS.h
文件描述:结构定义数据库开发嵌C头文件
项 目 组:
程 序 员:[wangzh14925]
发布时间:2009-4-29 19:40:39 [Gen]
修    订:
修改时间:
************************************************************************
表    名:ICPS_JT_CUS (F_JT2.客户信息文件)
说    明:
************************************************************************
修改记录:
修改日期:
修改内容:
修 改 人:
修改内容:
************************************************************************/
#ifndef __ICPS_JT_CUS_H__
#define __ICPS_JT_CUS_H__
typedef struct TDB_ICPS_JT_CUS
{
	char   busi_date[8+1];  /*业务日期*/
		/*业务日期YYYYMMDD*/
	int   file_order;  /*文件序号*/
		/**/
	char   customer_code[60+1];  /*客户编号*/
		/*客户编号*/
	char   customer_name[250+1];  /*客户姓名*/
		/*客户姓名*/
	char   gender[1+1];  /*客户性别*/
		/*客户性别*/
	char   brith_date[8+1];  /*出生日期*/
		/*出生日期YYYYMMDD*/
	char   resident_flag[1+1];  /*居民标志*/
		/*居民标志*/
	char   customer_status[1+1];  /*客户状态*/
		/*客户状态*/
	char   border_in_out_flag[1+1];  /*境内境外标志*/
		/*境内境外标志*/
	char   id_type[5+1];  /*证件类型*/
		/*证件类型*/
	char   id_num[60+1];  /*证件号码*/
		/*证件号码*/
	char   mobile_no[60+1];  /*手机号码*/
		/*手机号码*/
	char   addr[250+1];  /*通讯地址*/
		/*通讯地址*/
	char   bank_name[100+1];  /*绑定银行卡行名*/
		/*绑定银行卡行名*/
	char   bank_acct[60+1];  /*绑定银行卡卡号*/
		/*绑定银行卡卡号*/
	char   is_check_flag[1+1];  /*参与对账标识*/
		/*参与对账标识*/
	char   extend_param1[100+1];  /*扩展1*/
		/*扩展1*/
	char   extend_param2[250+1];  /*扩展2*/
		/*扩展2*/
	char   extend_param3[40+1];  /*扩展3*/
		/*扩展3*/

}ICPS_JT_CUS;

#define SD_DATA  ICPS_JT_CUS
#define SD_MEMBERS \ 
	APP_DEFSDMEMBER(T_STRING,  busi_date, 0),\
	APP_DEFSDMEMBER(T_LONG,  file_order, 0),\
	APP_DEFSDMEMBER(T_STRING,  customer_code, 0),\
	APP_DEFSDMEMBER(T_STRING,  customer_name, 0),\
	APP_DEFSDMEMBER(T_STRING,  gender, 0),\
	APP_DEFSDMEMBER(T_STRING,  brith_date, 0),\
	APP_DEFSDMEMBER(T_STRING,  resident_flag, 0),\
	APP_DEFSDMEMBER(T_STRING,  customer_status, 0),\
	APP_DEFSDMEMBER(T_STRING,  border_in_out_flag, 0),\
	APP_DEFSDMEMBER(T_STRING,  id_type, 0),\
	APP_DEFSDMEMBER(T_STRING,  id_num, 0),\
	APP_DEFSDMEMBER(T_STRING,  mobile_no, 0),\
	APP_DEFSDMEMBER(T_STRING,  addr, 0),\
	APP_DEFSDMEMBER(T_STRING,  bank_name, 0),\
	APP_DEFSDMEMBER(T_STRING,  bank_acct, 0),\
	APP_DEFSDMEMBER(T_STRING,  is_check_flag, 0),\
	APP_DEFSDMEMBER(T_STRING,  extend_param1, 0),\
	APP_DEFSDMEMBER(T_STRING,  extend_param2, 0),\
	APP_DEFSDMEMBER(T_STRING,  extend_param3, 0)


	APP_DECLAREFIELDS(SD_ICPS_JT_CUS)
#undef SD_DATA
#undef SD_MEMBERS

#endif  /*end of __ICPS_JT_CUS_H__*/
