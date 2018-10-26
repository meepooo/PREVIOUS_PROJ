/***********************************************************************
版权所有:恒生电子股份有限公司
项目名称:综合技术平台(Turandot)项目
版    本:V1.00
操作系统:
数 据 库:INFORMIX
文 件 名:ICPS_WB_TM_RE_HST.h
文件描述:结构定义数据库开发嵌C头文件
项 目 组:
程 序 员:[wangzh14925]
发布时间:2009-4-29 19:40:39 [Gen]
修    订:
修改时间:
************************************************************************
表    名:ICPS_WB_TM_RE_HST (F_WB18.还款借据清单表历史)
说    明:
************************************************************************
修改记录:
修改日期:
修改内容:
修 改 人:
修改内容:
************************************************************************/
#ifndef __ICPS_WB_TM_RE_HST_H__
#define __ICPS_WB_TM_RE_HST_H__
typedef struct TDB_ICPS_WB_TM_RE_HST
{
	char   busi_date[8+1];  /*业务日期*/
		/*业务日期*/
	int   file_order;  /*文件序号*/
		/*文件序号*/
	char   busi_serial[32+1];  /*业务流水号*/
		/*业务流水号*/
	char   sys_trans_id[32+1];  /*系统调用流水号*/
		/*系统调用流水号*/
	char   loan_receipt_nbr[20+1];  /*借据号*/
		/*借据号*/
	char   acct_no[20+1];  /*账户编号*/
		/*账户编号*/
	char   acct_type[1+1];  /*账户类型*/
		/*账户类型*/
	char   card_no[19+1];  /*卡号*/
		/*卡号*/
	char   transfer_in_date[14+1];  /*入账日期*/
		/*入账日期*/
	char   last_modified_datetime[14+1];  /*时间戳*/
		/*时间戳*/
	char   move_date[14+1];  /*转移日期(大数据提取用)*/
		/*转移日期(大数据提取用)*/
	int   part_month;  /*分区用的月份*/
		/*分区用的月份*/
	double   pay_amt;  /*还款金额*/
		/*还款金额*/
	char   bank_group_id[5+1];  /*银团编号*/
		/*银团编号*/
	char   is_check_flag[1+1];  /*参与对账标识*/
		/*参与对账标识*/
	char   extend_param1[100+1];  /*扩展1*/
		/*扩展1*/
	char   extend_param2[250+1];  /*扩展2*/
		/*扩展2*/
	char   extend_param3[40+1];  /*扩展3*/
		/*扩展3*/

}ICPS_WB_TM_RE_HST;

#define SD_DATA  ICPS_WB_TM_RE_HST
#define SD_MEMBERS \ 
	APP_DEFSDMEMBER(T_STRING,  busi_date, 0),\
	APP_DEFSDMEMBER(T_LONG,  file_order, 0),\
	APP_DEFSDMEMBER(T_STRING,  busi_serial, 0),\
	APP_DEFSDMEMBER(T_STRING,  sys_trans_id, 0),\
	APP_DEFSDMEMBER(T_STRING,  loan_receipt_nbr, 0),\
	APP_DEFSDMEMBER(T_STRING,  acct_no, 0),\
	APP_DEFSDMEMBER(T_STRING,  acct_type, 0),\
	APP_DEFSDMEMBER(T_STRING,  card_no, 0),\
	APP_DEFSDMEMBER(T_STRING,  transfer_in_date, 0),\
	APP_DEFSDMEMBER(T_STRING,  last_modified_datetime, 0),\
	APP_DEFSDMEMBER(T_STRING,  move_date, 0),\
	APP_DEFSDMEMBER(T_LONG,  part_month, 0),\
	APP_DEFSDMEMBER(T_DOUBLE,  pay_amt, 2),\
	APP_DEFSDMEMBER(T_STRING,  bank_group_id, 0),\
	APP_DEFSDMEMBER(T_STRING,  is_check_flag, 0),\
	APP_DEFSDMEMBER(T_STRING,  extend_param1, 0),\
	APP_DEFSDMEMBER(T_STRING,  extend_param2, 0),\
	APP_DEFSDMEMBER(T_STRING,  extend_param3, 0)


	APP_DECLAREFIELDS(SD_ICPS_WB_TM_RE_HST)
#undef SD_DATA
#undef SD_MEMBERS

#endif  /*end of __ICPS_WB_TM_RE_HST_H__*/
