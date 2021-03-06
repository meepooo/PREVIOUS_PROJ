/***********************************************************************
版权所有:恒生电子股份有限公司
项目名称:综合技术平台(Turandot)项目
版    本:V1.00
操作系统:
数 据 库:db2
文 件 名:ICPS_WBC_RRS_BDM_UDF_CLEAR_TOT.h
文件描述:结构定义数据库开发嵌C头文件
项 目 组:
程 序 员:[fuwd22392]
发布时间:2018-06-12 10:00:00 [Gen]
修    订:
修改时间:
************************************************************************
表    名:ICPS_WBC_RRS_BDM_UDF_CLEAR_TOT
说    明:
************************************************************************
修改记录:
修改日期:
修改内容:
修 改 人:
修改内容:
************************************************************************/
#ifndef __ICPS_WBC_RRS_BDM_UDF_CLEAR_TOT_H__
#define __ICPS_WBC_RRS_BDM_UDF_CLEAR_TOT_H__
typedef struct TDB_ICPS_WBC_RRS_BDM_UDF_CLEAR_TOT
{
	char		busi_date[8+1];
	int			file_order;
	char		data_dt[10+1];            /*数据日期        */
	char		acct_no[40+1];            /*备付金帐号      */
	char		ccy[3+1];                 /*币种            */
	char		acct_name[100+1];         /*户名            */
	double		last_balance;             /*上日账户余额    */
	double		balance;                  /*本日账户余额    */
	double		payment_amt;              /*当日放款总金额  */
	double		repayment_amt;            /*当日还款总金额  */
	double		other_credit_amt;         /*当日其他划入款项*/
	double		other_debit_amt;          /*当日其他划出款项*/
	char		ds[10+1];                 /*日期分区        */
	char		is_check_flag[1+1];
	char		extend_param1[100+1];
	char		extend_param2[250+1];
	char		extend_param3[40+1];
}ICPS_WBC_RRS_BDM_UDF_CLEAR_TOT;

#define SD_DATA  ICPS_WBC_RRS_BDM_UDF_CLEAR_TOT
#define SD_MEMBERS \ 
   APP_DEFSDMEMBER(T_STRING,  busi_date         ,0),\
   APP_DEFSDMEMBER(T_LONG,    file_order        ,0),\
   APP_DEFSDMEMBER(T_STRING,  data_dt           ,0),\
   APP_DEFSDMEMBER(T_STRING,  acct_no           ,0),\
   APP_DEFSDMEMBER(T_STRING,  ccy               ,0),\
   APP_DEFSDMEMBER(T_STRING,  acct_name         ,0),\
   APP_DEFSDMEMBER(T_DOUBLE,  last_balance      ,4),\
   APP_DEFSDMEMBER(T_DOUBLE,  balance           ,4),\
   APP_DEFSDMEMBER(T_DOUBLE,  payment_amt       ,4),\
   APP_DEFSDMEMBER(T_DOUBLE,  repayment_amt     ,4),\
   APP_DEFSDMEMBER(T_DOUBLE,  other_credit_amt  ,4),\
   APP_DEFSDMEMBER(T_DOUBLE,  other_debit_amt   ,4),\
   APP_DEFSDMEMBER(T_STRING,  ds                ,0),\
   APP_DEFSDMEMBER(T_STRING,  is_check_flag     ,0),\
   APP_DEFSDMEMBER(T_STRING,  extend_param1     ,0),\
   APP_DEFSDMEMBER(T_STRING,  extend_param2     ,0),\
   APP_DEFSDMEMBER(T_STRING,  extend_param3     ,0)
   APP_DECLAREFIELDS(SD_ICPS_WBC_RRS_BDM_UDF_CLEAR_TOT)
#undef SD_DATA
#undef SD_MEMBERS

#endif  /*end of __ICPS_WBC_RRS_BDM_UDF_CLEAR_TOT_H__*/
                                              
