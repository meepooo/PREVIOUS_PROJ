/***********************************************************************
版权所有:恒生电子股份有限公司
项目名称:综合技术平台(Turandot)项目
版    本:V1.00
操作系统:
数 据 库:INFORMIX
文 件 名:ICPS_WB_DS_ACCOUNTING_FLOW.h
文件描述:结构定义数据库开发嵌C头文件
项 目 组:
程 序 员:[wangzh14925]
发布时间:2009-4-29 19:40:39 [Gen]
修    订:
修改时间:
************************************************************************
表    名:ICPS_WB_DS_ACCOUNTING_FLOW (F_WB13.会计分录日报表)
说    明:
************************************************************************
修改记录:
修改日期:
修改内容:
修 改 人:
修改内容:
************************************************************************/
#ifndef __ICPS_WB_DS_ACCOUNTING_FLOW_H__
#define __ICPS_WB_DS_ACCOUNTING_FLOW_H__
typedef struct TDB_ICPS_WB_DS_ACCOUNTING_FLOW
{
	char   busi_date[8+1];  /*业务日期*/
		/*业务日期*/
	int   file_order;  /*文件序号*/
		/*文件序号*/
	char   org[12+1];  /*内部机构号*/
		/*内部机构号*/
	char   host_trans_serial[36+1];  /*核心交易流水*/
		/*核心交易流水*/
	char   card_no[19+1];  /*卡号*/
		/*卡号*/
	char   currency[3+1];  /*币种*/
		/*币种*/
	char   txn_code[4+1];  /*交易码*/
		/*交易码*/
	char   txn_desc[80+1];  /*交易描述*/
		/*交易描述*/
	char   db_cr_ind[1+1];  /*借贷标记*/
		/*借贷标记*/
	double   post_amt;  /*入账金额*/
		/*入账金额*/
	char   post_gl_ind[1+1];  /*入账方式*/
		/*入账方式*/
	char   owning_branch[9+1];  /*支行*/
		/*支行*/
	char   subject[40+1];  /*科目*/
		/*科目*/
	char   red_flag[1+1];  /*红蓝字标识*/
		/*红蓝字标识*/
	long   queue;  /*排序*/
		/*排序*/
	char   product_cd[10+1];  /*产品号*/
		/*产品号*/
	char   ref_nbr[25+1];  /*借据号*/
		/*借据号*/
	char   age_group[5+1];  /*账龄组*/
		/*账龄组*/
	char   plan_nbr[10+1];  /*信用计划号*/
		/*信用计划号*/
	char   bnp_group[5+1];  /*余额成分组*/
		/*余额成分组*/
	char   bank_group_id[10+1];  /*银团代码*/
		/*银团代码*/
	char   bank_no[15+1];  /*银行代码*/
		/*银行代码*/
	int   term;  /*期数*/
		/*期数*/
	char   batchDate[14+1];  /*批量*/
		/*批量*/
	char   is_check_flag[1+1];  /*参与对账标识*/
		/*参与对账标识*/
	char   extend_param1[100+1];  /*扩展1*/
		/*扩展1*/
	char   extend_param2[250+1];  /*扩展2*/
		/*扩展2*/
	char   extend_param3[40+1];  /*扩展3*/
		/*扩展3*/

}ICPS_WB_DS_ACCOUNTING_FLOW;

#define SD_DATA  ICPS_WB_DS_ACCOUNTING_FLOW
#define SD_MEMBERS \ 
	APP_DEFSDMEMBER(T_STRING,  busi_date, 0),\
	APP_DEFSDMEMBER(T_LONG,  file_order, 0),\
	APP_DEFSDMEMBER(T_STRING,  org, 0),\
	APP_DEFSDMEMBER(T_STRING,  host_trans_serial, 0),\
	APP_DEFSDMEMBER(T_STRING,  card_no, 0),\
	APP_DEFSDMEMBER(T_STRING,  currency, 0),\
	APP_DEFSDMEMBER(T_STRING,  txn_code, 0),\
	APP_DEFSDMEMBER(T_STRING,  txn_desc, 0),\
	APP_DEFSDMEMBER(T_STRING,  db_cr_ind, 0),\
	APP_DEFSDMEMBER(T_DOUBLE,  post_amt, 2),\
	APP_DEFSDMEMBER(T_STRING,  post_gl_ind, 0),\
	APP_DEFSDMEMBER(T_STRING,  owning_branch, 0),\
	APP_DEFSDMEMBER(T_STRING,  subject, 0),\
	APP_DEFSDMEMBER(T_STRING,  red_flag, 0),\
	APP_DEFSDMEMBER(T_LONG,  queue, 0),\
	APP_DEFSDMEMBER(T_STRING,  product_cd, 0),\
	APP_DEFSDMEMBER(T_STRING,  ref_nbr, 0),\
	APP_DEFSDMEMBER(T_STRING,  age_group, 0),\
	APP_DEFSDMEMBER(T_STRING,  plan_nbr, 0),\
	APP_DEFSDMEMBER(T_STRING,  bnp_group, 0),\
	APP_DEFSDMEMBER(T_STRING,  bank_group_id, 0),\
	APP_DEFSDMEMBER(T_STRING,  bank_no, 0),\
	APP_DEFSDMEMBER(T_LONG,  term, 0),\
	APP_DEFSDMEMBER(T_STRING,  batchDate, 0),\
	APP_DEFSDMEMBER(T_STRING,  is_check_flag, 0),\
	APP_DEFSDMEMBER(T_STRING,  extend_param1, 0),\
	APP_DEFSDMEMBER(T_STRING,  extend_param2, 0),\
	APP_DEFSDMEMBER(T_STRING,  extend_param3, 0)


	APP_DECLAREFIELDS(SD_ICPS_WB_DS_ACCOUNTING_FLOW)
#undef SD_DATA
#undef SD_MEMBERS

#endif  /*end of __ICPS_WB_DS_ACCOUNTING_FLOW_H__*/
