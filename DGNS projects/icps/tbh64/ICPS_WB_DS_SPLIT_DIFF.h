/***********************************************************************
版权所有:恒生电子股份有限公司
项目名称:综合技术平台(Turandot)项目
版    本:V1.00
操作系统:
数 据 库:INFORMIX
文 件 名:ICPS_WB_DS_SPLIT_DIFF.h
文件描述:结构定义数据库开发嵌C头文件
项 目 组:
程 序 员:[wangzh14925]
发布时间:2009-4-29 19:40:39 [Gen]
修    订:
修改时间:
************************************************************************
表    名:ICPS_WB_DS_SPLIT_DIFF (F_WB26.银团尾差调整表)
说    明:
************************************************************************
修改记录:
修改日期:
修改内容:
修 改 人:
修改内容:
************************************************************************/
#ifndef __ICPS_WB_DS_SPLIT_DIFF_H__
#define __ICPS_WB_DS_SPLIT_DIFF_H__
typedef struct TDB_ICPS_WB_DS_SPLIT_DIFF
{
	char   busi_date[8+1];  /*业务日期*/
		/*业务日期*/
	int   file_order;  /*文件序号*/
		/*文件序号*/
	char   partition_date[8+1];  /*批量日期*/
		/*批量日期*/
	char   error_type[40+1];  /*异常类型*/
		/*异常类型*/
	char   bank_group_id[5+1];  /*银团编号*/
		/*银团编号*/
	char   bank_no[10+1];  /*银行编号*/
		/*银行编号*/
	char   busi_serial[40+1];  /*业务流水号*/
		/*业务流水号*/
	char   trans_type[10+1];  /*交易类型*/
		/*交易类型*/
	char   name[80+1];  /*姓名*/
		/*姓名*/
	char   logical_card_no[19+1];  /*逻辑卡号*/
		/*逻辑卡号*/
	double   bf_amt;  /*备付金清算金额*/
		/*备付金清算金额*/
	double   account_amt;  /*CNC记账金额*/
		/*CNC记账金额*/
	double   error_amt;  /*应调整差额*/
		/*应调整差额*/
	char   is_check_flag[1+1];  /*参与对账标识*/
		/*参与对账标识*/
	char   extend_param1[100+1];  /*扩展1*/
		/*扩展1*/
	char   extend_param2[250+1];  /*扩展2*/
		/*扩展2*/
	char   extend_param3[40+1];  /*扩展3*/
		/*扩展3*/

}ICPS_WB_DS_SPLIT_DIFF;

#define SD_DATA  ICPS_WB_DS_SPLIT_DIFF
#define SD_MEMBERS \ 
	APP_DEFSDMEMBER(T_STRING,  busi_date, 0),\
	APP_DEFSDMEMBER(T_LONG,  file_order, 0),\
	APP_DEFSDMEMBER(T_STRING,  partition_date, 0),\
	APP_DEFSDMEMBER(T_STRING,  error_type, 0),\
	APP_DEFSDMEMBER(T_STRING,  bank_group_id, 0),\
	APP_DEFSDMEMBER(T_STRING,  bank_no, 0),\
	APP_DEFSDMEMBER(T_STRING,  busi_serial, 0),\
	APP_DEFSDMEMBER(T_STRING,  trans_type, 0),\
	APP_DEFSDMEMBER(T_STRING,  name, 0),\
	APP_DEFSDMEMBER(T_STRING,  logical_card_no, 0),\
	APP_DEFSDMEMBER(T_DOUBLE,  bf_amt, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  account_amt, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  error_amt, 2),\
	APP_DEFSDMEMBER(T_STRING,  is_check_flag, 0),\
	APP_DEFSDMEMBER(T_STRING,  extend_param1, 0),\
	APP_DEFSDMEMBER(T_STRING,  extend_param2, 0),\
	APP_DEFSDMEMBER(T_STRING,  extend_param3, 0)


	APP_DECLAREFIELDS(SD_ICPS_WB_DS_SPLIT_DIFF)
#undef SD_DATA
#undef SD_MEMBERS

#endif  /*end of __ICPS_WB_DS_SPLIT_DIFF_H__*/
