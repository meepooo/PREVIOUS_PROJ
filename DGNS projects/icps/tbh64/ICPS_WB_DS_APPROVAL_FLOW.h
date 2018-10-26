/***********************************************************************
版权所有:恒生电子股份有限公司
项目名称:综合技术平台(Turandot)项目
版    本:V1.00
操作系统:
数 据 库:INFORMIX
文 件 名:ICPS_WB_DS_APPROVAL_FLOW.h
文件描述:结构定义数据库开发嵌C头文件
项 目 组:
程 序 员:[wangzh14925]
发布时间:2009-4-29 19:40:39 [Gen]
修    订:
修改时间:
************************************************************************
表    名:ICPS_WB_DS_APPROVAL_FLOW (F_WB30.审批结果流水表)
说    明:
************************************************************************
修改记录:
修改日期:
修改内容:
修 改 人:
修改内容:
************************************************************************/
#ifndef __ICPS_WB_DS_APPROVAL_FLOW_H__
#define __ICPS_WB_DS_APPROVAL_FLOW_H__
typedef struct TDB_ICPS_WB_DS_APPROVAL_FLOW
{
	char   busi_date[8+1];  /*业务日期*/
		/*业务日期*/
	int   file_order;  /*文件序号*/
		/*文件序号*/
	char   partition_date[10+1];  /*分区日期*/
		/*分区日期*/
	char   busi_no[40+1];  /*流水号*/
		/*流水号*/
	char   bank_no[20+1];  /*银行号*/
		/*银行号*/
	char   final_ret[20+1];  /*最终审批结果*/
		/*最终审批结果*/
	char   ours_approval_ret[40+1];  /*合作行审批结果*/
		/*合作行审批结果*/
	char   code_block[200+1];  /*拒绝码*/
		/*拒绝码*/
	char   is_first[2+1];  /*是否首借*/
		/*是否首借*/
	char   outer_ret[40+1];  /*合作行机房审批结果*/
		/*合作行机房审批结果*/
	char   psz_ret[40+1];  /*Psz区审批结果*/
		/*Psz区审批结果*/
	char   is_check_flag[1+1];  /*参与对账标识*/
		/*参与对账标识*/
	char   extend_param1[100+1];  /*扩展1*/
		/*扩展1*/
	char   extend_param2[250+1];  /*扩展2*/
		/*扩展2*/
	char   extend_param3[40+1];  /*扩展3*/
		/*扩展3*/

}ICPS_WB_DS_APPROVAL_FLOW;

#define SD_DATA  ICPS_WB_DS_APPROVAL_FLOW
#define SD_MEMBERS \ 
	APP_DEFSDMEMBER(T_STRING,  busi_date, 0),\
	APP_DEFSDMEMBER(T_LONG,  file_order, 0),\
	APP_DEFSDMEMBER(T_STRING,  partition_date, 0),\
	APP_DEFSDMEMBER(T_STRING,  busi_no, 0),\
	APP_DEFSDMEMBER(T_STRING,  bank_no, 0),\
	APP_DEFSDMEMBER(T_STRING,  final_ret, 0),\
	APP_DEFSDMEMBER(T_STRING,  ours_approval_ret, 0),\
	APP_DEFSDMEMBER(T_STRING,  code_block, 0),\
	APP_DEFSDMEMBER(T_STRING,  is_first, 0),\
	APP_DEFSDMEMBER(T_STRING,  outer_ret, 0),\
	APP_DEFSDMEMBER(T_STRING,  psz_ret, 0),\
	APP_DEFSDMEMBER(T_STRING,  is_check_flag, 0),\
	APP_DEFSDMEMBER(T_STRING,  extend_param1, 0),\
	APP_DEFSDMEMBER(T_STRING,  extend_param2, 0),\
	APP_DEFSDMEMBER(T_STRING,  extend_param3, 0)


	APP_DECLAREFIELDS(SD_ICPS_WB_DS_APPROVAL_FLOW)
#undef SD_DATA
#undef SD_MEMBERS

#endif  /*end of __ICPS_WB_DS_APPROVAL_FLOW_H__*/
