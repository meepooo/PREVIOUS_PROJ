/***********************************************************************
版权所有:恒生电子股份有限公司
项目名称:综合技术平台(Turandot)项目
版    本:V1.00
操作系统:
数 据 库:INFORMIX
文 件 名:ICPS_JB_ARG_STATUS_CHANGE.h
文件描述:结构定义数据库开发嵌C头文件
项 目 组:
程 序 员:[wangzh14925]
发布时间:2009-4-29 19:40:39 [Gen]
修    订:
修改时间:
************************************************************************
表    名:ICPS_JB_ARG_STATUS_CHANGE (F_JB12.借据形态转移流水文件)
说    明:
************************************************************************
修改记录:
修改日期:
修改内容:
修 改 人:
修改内容:
************************************************************************/
#ifndef __ICPS_JB_ARG_STATUS_CHANGE_H__
#define __ICPS_JB_ARG_STATUS_CHANGE_H__
typedef struct TDB_ICPS_JB_ARG_STATUS_CHANGE
{
	char   busi_date[8+1];  /*业务日期*/
		/*业务日期*/
	int   file_order;  /*文件序号*/
		/*文件序号*/
	char   contract_no[32+1];  /*借呗平台贷款合同号*/
		/*借呗平台贷款合同号*/
	char   settle_date[8+1];  /*会计日期*/
		/*会计日期*/
	char   status_seq_no[64+1];  /*状态变化流水号*/
		/*状态变化流水号*/
	char   event_code[16+1];  /*事件码*/
		/*事件码，转逾期11020007，转非应计11020014，转应计11020015*/
	char   before_status[10+1];  /*借据转移前状态*/
		/*借据转移前状态（包括应计） ，取值为NORMAL（应计变更取值切0或1）*/
	char   after_status[10+1];  /*借据转移后状态*/
		/*借据转移后状态（包括应计），取值为OVD（应计变更取值为0或1）*/
	double   prin_amt;  /*本金发生额*/
		/*本金发生额*/
	double   int_amt;  /*利息发生额*/
		/*利息发生额*/
	double   ovd_prin_pnlt_amt;  /*逾期本金罚息发生额*/
		/*逾期本金罚息发生额*/
	double   ovd_int_pnlt_amt;  /*逾期利息罚息发生额*/
		/*逾期利息罚息发生额*/
	char   is_check_flag[1+1];  /*参与对账标识*/
		/*参与对账标识*/
	char   extend_param1[100+1];  /*扩展1*/
		/*扩展1*/
	char   extend_param2[250+1];  /*扩展2*/
		/*扩展2*/
	char   extend_param3[40+1];  /*扩展3*/
		/*扩展3*/

}ICPS_JB_ARG_STATUS_CHANGE;

#define SD_DATA  ICPS_JB_ARG_STATUS_CHANGE
#define SD_MEMBERS \
	APP_DEFSDMEMBER(T_STRING,  busi_date, 0),\
	APP_DEFSDMEMBER(T_LONG,  file_order, 0),\
	APP_DEFSDMEMBER(T_STRING,  contract_no, 0),\
	APP_DEFSDMEMBER(T_STRING,  settle_date, 0),\
	APP_DEFSDMEMBER(T_STRING,  status_seq_no, 0),\
	APP_DEFSDMEMBER(T_STRING,  event_code, 0),\
	APP_DEFSDMEMBER(T_STRING,  before_status, 0),\
	APP_DEFSDMEMBER(T_STRING,  after_status, 0),\
	APP_DEFSDMEMBER(T_DOUBLE,  prin_amt, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  int_amt, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  ovd_prin_pnlt_amt, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  ovd_int_pnlt_amt, 2),\
	APP_DEFSDMEMBER(T_STRING,  is_check_flag, 0),\
	APP_DEFSDMEMBER(T_STRING,  extend_param1, 0),\
	APP_DEFSDMEMBER(T_STRING,  extend_param2, 0),\
	APP_DEFSDMEMBER(T_STRING,  extend_param3, 0)


	APP_DECLAREFIELDS(SD_ICPS_JB_ARG_STATUS_CHANGE)
#undef SD_DATA
#undef SD_MEMBERS

#endif  /*end of __ICPS_JB_ARG_STATUS_CHANGE_H__*/
