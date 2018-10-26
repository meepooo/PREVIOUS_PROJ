/***********************************************************************
版权所有:恒生电子股份有限公司
项目名称:综合技术平台(Turandot)项目
版    本:V1.00
操作系统:
数 据 库:INFORMIX
文 件 名:ICPS_JB_FUND_DETAIL.h
文件描述:结构定义数据库开发嵌C头文件
项 目 组:
程 序 员:[wangzh14925]
发布时间:2009-4-29 19:40:39 [Gen]
修    订:
修改时间:
************************************************************************
表    名:ICPS_JB_FUND_DETAIL (F_JB13.网商银行资金对账文件)
说    明:
************************************************************************
修改记录:
修改日期:
修改内容:
修 改 人:
修改内容:
************************************************************************/
#ifndef __ICPS_JB_FUND_DETAIL_H__
#define __ICPS_JB_FUND_DETAIL_H__
typedef struct TDB_ICPS_JB_FUND_DETAIL
{
	char   busi_date[8+1];  /*业务日期*/
		/*业务日期*/
	int   file_order;  /*文件序号*/
		/*文件序号*/
	char   third_busi_serial[64+1];  /*网商银行交易流水号*/
		/*网商银行交易流水号*/
	char   third_busi_type[32+1];  /*业务操作*/
		/*业务操作，代收P_DLGATE，代扣P_WITHDRAW（如果收费账户是独立的，则P_FEE代表是收费）*/
	double   trans_amt;  /*交易金额*/
		/*交易金额 代扣为负数，代收为正数*/
	double   trans_refund_amt;  /*交易退款金额*/
		/*交易退款金额 如果此金额大于0则代表是代扣退款*/
	char   trans_dttm[14+1];  /*交易时间*/
		/*交易时间 YYYYMMDDHHMMSS*/
	char   third_trans_name[256+1];  /*交易名称*/
		/*交易名称 代收，代扣*/
	char   peer_org_name[32+1];  /*对方机构名称*/
		/*对方机构名称*/
	char   trans_sub_detail[128+1];  /*业务单号*/
		/*业务单号*/
	char   is_check_flag[1+1];  /*参与对账标识*/
		/*参与对账标识*/
	char   extend_param1[100+1];  /*扩展1*/
		/*扩展1*/
	char   extend_param2[250+1];  /*扩展2*/
		/*扩展2*/
	char   extend_param3[40+1];  /*扩展3*/
		/*扩展3*/

}ICPS_JB_FUND_DETAIL;

#define SD_DATA  ICPS_JB_FUND_DETAIL
#define SD_MEMBERS \ 
	APP_DEFSDMEMBER(T_STRING,  busi_date, 0),\
	APP_DEFSDMEMBER(T_LONG,  file_order, 0),\
	APP_DEFSDMEMBER(T_STRING,  third_busi_serial, 0),\
	APP_DEFSDMEMBER(T_STRING,  third_busi_type, 0),\
	APP_DEFSDMEMBER(T_DOUBLE,  trans_amt, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  trans_refund_amt, 2),\
	APP_DEFSDMEMBER(T_STRING,  trans_dttm, 0),\
	APP_DEFSDMEMBER(T_STRING,  third_trans_name, 0),\
	APP_DEFSDMEMBER(T_STRING,  peer_org_name, 0),\
	APP_DEFSDMEMBER(T_STRING,  trans_sub_detail, 0),\
	APP_DEFSDMEMBER(T_STRING,  is_check_flag, 0),\
	APP_DEFSDMEMBER(T_STRING,  extend_param1, 0),\
	APP_DEFSDMEMBER(T_STRING,  extend_param2, 0),\
	APP_DEFSDMEMBER(T_STRING,  extend_param3, 0)


	APP_DECLAREFIELDS(SD_ICPS_JB_FUND_DETAIL)
#undef SD_DATA
#undef SD_MEMBERS

#endif  /*end of __ICPS_JB_FUND_DETAIL_H__*/
