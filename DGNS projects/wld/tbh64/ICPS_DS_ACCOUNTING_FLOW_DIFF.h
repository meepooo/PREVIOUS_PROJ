/***********************************************************************
版权所有:恒生电子股份有限公司
项目名称:综合技术平台(Turandot)项目
版    本:V1.00
操作系统:
数 据 库:INFORMIX
文 件 名:WB_DS_ACCOUNTING_FLOW_DIFF.h
文件描述:结构定义数据库开发嵌C头文件
项 目 组:
程 序 员:[wangzh14925]
发布时间:2009-4-29 19:40:39 [Gen]
修    订:
修改时间:
************************************************************************
表    名:WB_DS_ACCOUNTING_FLOW_DIFF (F_WB30.总分核对差错表)
说    明:
************************************************************************
修改记录:
修改日期:
修改内容:
修 改 人:
修改内容:
************************************************************************/
#ifndef __ICPS_DS_ACCOUNTING_FLOW_DIFF_H__
#define __ICPS_DS_ACCOUNTING_FLOW_DIFF_H__
typedef struct TDB_ICPS_DS_ACCOUNTING_FLOW_DIFF
{
	char   busi_date[8+1];  /*业务日期*/
	char   busi_no[16+1];  /*业务种类*/
	char   subject[40+1];  /*科目*/
	char   product_cd[6+1];  /*产品编号*/
	char   bank_group_id[5+1];  /*银团代码*/
	double   db_amt;  /*明细汇总借方金额*/
	int   db_count;  /*借方明细汇总笔数*/
	double   db_pmt;  /*总账借方发生额*/
	int   db_tcnt;  /*总账借方笔数*/
	char   dr_check_flag[1+1]; /*借方核对标识*/
	double   cr_amt;  /*贷方发生额汇总*/
	int   cr_count;  /*贷方明细汇总笔数*/
	double   cr_pmt;  /*贷方发生额*/ 
	int   cr_tcnt;  /*总账贷方笔数*/
	char   cr_check_flag[1+1]; /*贷方胶硕员晔�*/
	char   extend_param1[100+1];  /*扩展1*/
	char   extend_param2[250+1];  /*扩展2*/
	char   extend_param3[40+1];  /*扩展3*/

}ICPS_DS_ACCOUNTING_FLOW_DIFF;

#define SD_DATA  ICPS_DS_ACCOUNTING_FLOW_DIFF
#define SD_MEMBERS \ 
	APP_DEFSDMEMBER(T_STRING,  busi_date, 0),\
	APP_DEFSDMEMBER(T_STRING,  busi_no, 0),\
	APP_DEFSDMEMBER(T_STRING,  subject, 0),\
	APP_DEFSDMEMBER(T_STRING,  product_cd, 0),\
	APP_DEFSDMEMBER(T_STRING,  bank_group_id, 0),\
	APP_DEFSDMEMBER(T_DOUBLE,  db_amt, 2),\
	APP_DEFSDMEMBER(T_LONG,    db_count, 0),\
	APP_DEFSDMEMBER(T_DOUBLE,  db_pmt, 2),\
	APP_DEFSDMEMBER(T_LONG,    db_tcnt, 0),\
	APP_DEFSDMEMBER(T_STRING,  dr_check_flag, 0),\
	APP_DEFSDMEMBER(T_DOUBLE,  cr_amt, 2),\
	APP_DEFSDMEMBER(T_LONG,    cr_count, 0),\
	APP_DEFSDMEMBER(T_DOUBLE,  cr_pmt, 2),\
	APP_DEFSDMEMBER(T_LONG,    cr_tcnt, 0),\
	APP_DEFSDMEMBER(T_STRING,  cr_check_flag, 0),\
	APP_DEFSDMEMBER(T_STRING,  extend_param1, 0),\
	APP_DEFSDMEMBER(T_STRING,  extend_param2, 0),\
	APP_DEFSDMEMBER(T_STRING,  extend_param3, 0)

	APP_DECLAREFIELDS(SD_ICPS_DS_ACCOUNTING_FLOW_DIFF)
#undef SD_DATA
#undef SD_MEMBERS

#endif  /*end of __ICPS_DS_ACCOUNTING_FLOW_DIFF_H__*/
