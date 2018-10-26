/***********************************************************************
版权所有:恒生电子股份有限公司
项目名称:综合技术平台(Turandot)项目
版    本:V1.00
操作系统:
数 据 库:INFORMIX
文 件 名:ICPS_WB_DS_DCA_COMMISSION.h
文件描述:结构定义数据库开发嵌C头文件
项 目 组:
程 序 员:[wangzh14925]
发布时间:2009-4-29 19:40:39 [Gen]
修    订:
修改时间:
************************************************************************
表    名:ICPS_WB_DS_DCA_COMMISSION (F_WB27.委外催收借据级费用分摊明细表)
说    明:
************************************************************************
修改记录:
修改日期:
修改内容:
修 改 人:
修改内容:
************************************************************************/
#ifndef __ICPS_WB_DS_DCA_COMMISSION_H__
#define __ICPS_WB_DS_DCA_COMMISSION_H__
typedef struct TDB_ICPS_WB_DS_DCA_COMMISSION
{
	char   busi_date[8+1];  /*业务日期*/
		/*业务日期*/
	int   file_order;  /*文件序号*/
		/*文件序号*/
	double   out_amt;  /*委外金额*/
		/*委外金额*/
	double   out_prin;  /*委外本金*/
		/*委外本金*/
	double   out_interest;  /*委外利息*/
		/*委外利息*/
	double   out_penatly;  /*委外罚息*/
		/*委外罚息*/
	int   out_due_days;  /*委外逾期天数*/
		/*委外逾期天数*/
	char   out_age_cd[6+1];  /*委外逾期时段*/
		/*委外逾期时段*/
	double   repay_amt;  /*还款金额*/
		/*还款金额*/
	double   commision_ratio;  /*委外费率*/
		/*委外费率*/
	char   bank_group_id[5+1];  /*银团编号*/
		/*银团编号*/
	double   bank_proportion;  /*银团比例*/
		/*银团比例*/
	double   out_expense;  /*委外费用*/
		/*委外费用*/
	char   name[80+1];  /*名字*/
		/*名字*/
	char   logical_card_no[19+1];  /*卡号*/
		/*卡号*/
	char   cust_id[20+1];  /*客户号*/
		/*客户号*/
	char   acct_no[20+1];  /*账户号*/
		/*账户号*/
	char   loan_receipt_nbr[20+1];  /*借据号*/
		/*借据号*/
	char   bn[20+1];  /*银行号*/
		/*银行号*/
	char   partition_date[10+1];  /*分区日期*/
		/*分区日期*/
	char   is_check_flag[1+1];  /*参与对账标识*/
		/*参与对账标识*/
	char   extend_param1[100+1];  /*扩展1*/
		/*扩展1*/
	char   extend_param2[250+1];  /*扩展2*/
		/*扩展2*/
	char   extend_param3[40+1];  /*扩展3*/
		/*扩展3*/

}ICPS_WB_DS_DCA_COMMISSION;

#define SD_DATA  ICPS_WB_DS_DCA_COMMISSION
#define SD_MEMBERS \ 
	APP_DEFSDMEMBER(T_STRING,  busi_date, 0),\
	APP_DEFSDMEMBER(T_LONG,  file_order, 0),\
	APP_DEFSDMEMBER(T_DOUBLE,  out_amt, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  out_prin, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  out_interest, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  out_penatly, 2),\
	APP_DEFSDMEMBER(T_LONG,  out_due_days, 0),\
	APP_DEFSDMEMBER(T_STRING,  out_age_cd, 0),\
	APP_DEFSDMEMBER(T_DOUBLE,  repay_amt, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  commision_ratio, 2),\
	APP_DEFSDMEMBER(T_STRING,  bank_group_id, 0),\
	APP_DEFSDMEMBER(T_DOUBLE,  bank_proportion, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  out_expense, 2),\
	APP_DEFSDMEMBER(T_STRING,  name, 0),\
	APP_DEFSDMEMBER(T_STRING,  logical_card_no, 0),\
	APP_DEFSDMEMBER(T_STRING,  cust_id, 0),\
	APP_DEFSDMEMBER(T_STRING,  acct_no, 0),\
	APP_DEFSDMEMBER(T_STRING,  loan_receipt_nbr, 0),\
	APP_DEFSDMEMBER(T_STRING,  bn, 0),\
	APP_DEFSDMEMBER(T_STRING,  partition_date, 0),\
	APP_DEFSDMEMBER(T_STRING,  is_check_flag, 0),\
	APP_DEFSDMEMBER(T_STRING,  extend_param1, 0),\
	APP_DEFSDMEMBER(T_STRING,  extend_param2, 0),\
	APP_DEFSDMEMBER(T_STRING,  extend_param3, 0)


	APP_DECLAREFIELDS(SD_ICPS_WB_DS_DCA_COMMISSION)
#undef SD_DATA
#undef SD_MEMBERS

#endif  /*end of __ICPS_WB_DS_DCA_COMMISSION_H__*/
