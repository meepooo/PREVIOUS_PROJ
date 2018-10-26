/***********************************************************************
版权所有:恒生电子股份有限公司
项目名称:综合技术平台(Turandot)项目
版    本:V1.00
操作系统:
数 据 库:INFORMIX
文 件 名:ICPS_WB_TM_FREE_COUPONS_INFO.h
文件描述:结构定义数据库开发嵌C头文件
项 目 组:
程 序 员:[wangzh14925]
发布时间:2009-4-29 19:40:39 [Gen]
修    订:
修改时间:
************************************************************************
表    名:ICPS_WB_TM_FREE_COUPONS_INFO (F_WB25.免息卷信息表)
说    明:
************************************************************************
修改记录:
修改日期:
修改内容:
修 改 人:
修改内容:
************************************************************************/
#ifndef __ICPS_WB_TM_FREE_COUPONS_INFO_H__
#define __ICPS_WB_TM_FREE_COUPONS_INFO_H__
typedef struct TDB_ICPS_WB_TM_FREE_COUPONS_INFO
{
	char   busi_date[8+1];  /*业务日期*/
		/*业务日期*/
	int   file_order;  /*文件序号*/
		/*文件序号*/
	char   org[12+1];  /*机构号*/
		/*机构号*/
	char   list_no[21+1];  /*资格编号*/
		/*资格编号*/
	char   act_no[11+1];  /*活动编号*/
		/*活动编号*/
	char   equity_no[8+1];  /*权益编号*/
		/*权益编号*/
	char   equity_type[10+1];  /*权益类型*/
		/*权益类型*/
	long   equity_value;  /*权益值*/
		/*权益值*/
	char   loan_receipt_nbr[20+1];  /*借据号*/
		/*借据号*/
	char   card_no[19+1];  /*介质卡号*/
		/*介质卡号*/
	char   ref_nbr[23+1];  /*交易参考*/
		/*交易参考*/
	char   bank_group_id[5+1];  /*银团编号*/
		/*银团编号*/
	char   bank_no[10+1];  /*银行编号*/
		/*银行编号*/
	char   is_check_flag[1+1];  /*参与对账标识*/
		/*参与对账标识*/
	char   extend_param1[100+1];  /*扩展1*/
		/*扩展1*/
	char   extend_param2[250+1];  /*扩展2*/
		/*扩展2*/
	char   extend_param3[40+1];  /*扩展3*/
		/*扩展3*/

}ICPS_WB_TM_FREE_COUPONS_INFO;

#define SD_DATA  ICPS_WB_TM_FREE_COUPONS_INFO
#define SD_MEMBERS \ 
	APP_DEFSDMEMBER(T_STRING,  busi_date, 0),\
	APP_DEFSDMEMBER(T_LONG,  file_order, 0),\
	APP_DEFSDMEMBER(T_STRING,  org, 0),\
	APP_DEFSDMEMBER(T_STRING,  list_no, 0),\
	APP_DEFSDMEMBER(T_STRING,  act_no, 0),\
	APP_DEFSDMEMBER(T_STRING,  equity_no, 0),\
	APP_DEFSDMEMBER(T_STRING,  equity_type, 0),\
	APP_DEFSDMEMBER(T_LONG,  equity_value, 0),\
	APP_DEFSDMEMBER(T_STRING,  loan_receipt_nbr, 0),\
	APP_DEFSDMEMBER(T_STRING,  card_no, 0),\
	APP_DEFSDMEMBER(T_STRING,  ref_nbr, 0),\
	APP_DEFSDMEMBER(T_STRING,  bank_group_id, 0),\
	APP_DEFSDMEMBER(T_STRING,  bank_no, 0),\
	APP_DEFSDMEMBER(T_STRING,  is_check_flag, 0),\
	APP_DEFSDMEMBER(T_STRING,  extend_param1, 0),\
	APP_DEFSDMEMBER(T_STRING,  extend_param2, 0),\
	APP_DEFSDMEMBER(T_STRING,  extend_param3, 0)


	APP_DECLAREFIELDS(SD_ICPS_WB_TM_FREE_COUPONS_INFO)
#undef SD_DATA
#undef SD_MEMBERS

#endif  /*end of __ICPS_WB_TM_FREE_COUPONS_INFO_H__*/
