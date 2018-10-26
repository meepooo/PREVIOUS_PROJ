/***********************************************************************
版权所有:恒生电子股份有限公司
项目名称:综合技术平台(Turandot)项目
版    本:V1.00
操作系统:
数 据 库:INFORMIX
文 件 名:ICPS_WBC_TM_AUTH_BANK_COST_DTL.h
文件描述:结构定义数据库开发嵌C头文件
项 目 组:
程 序 员:[fuwd22392]
发布时间:2018-06-12 10:00:00 [Gen]
修    订:
修改时间:
************************************************************************
表    名:ICPS_WBC_TM_AUTH_BANK_COST_DTL
说    明:授权流水银团拆分明细表
************************************************************************
修改记录:
修改日期:
修改内容:
修 改 人:
修改内容:
************************************************************************/
#ifndef __ICPS_WBC_TM_AUTH_BANK_COST_DTL_H__
#define __ICPS_WBC_TM_AUTH_BANK_COST_DTL_H__
typedef struct TDB_ICPS_WBC_TM_AUTH_BANK_COST_DTL
{
	char	busi_date[8+1];
	int		file_order;
	char	consumer_trans_id[32+1];
	char	bank_group_id[5+1];
	char	bank_no[10+1];
	char	loan_receipt_nbr[20+1];
	char	reg_type[10+1];
	double	reg_amt;
	char	biz_date[8+1];
	char	cust_id[20+1];/*fuwd22392 modify*/
	char	acct_no[20+1];/*fuwd22392 modify*/
	char	acct_type[1+1];
	char	created_datetime[14+1];
	char	last_modified_datetime[14+1];
	char	card_no[19+1];
	char	is_check_flag[1+1];
	char	extend_param1[100+1];
	char	extend_param2[250+1];
	char	extend_param3[40+1];
}ICPS_WBC_TM_AUTH_BANK_COST_DTL;
 
#define SD_DATA  ICPS_WBC_TM_AUTH_BANK_COST_DTL
#define SD_MEMBERS \ 
  APP_DEFSDMEMBER(T_STRING,  busi_date               ,0),\
  APP_DEFSDMEMBER(T_LONG,    file_order              ,0),\
  APP_DEFSDMEMBER(T_STRING,  consumer_trans_id       ,0),\
  APP_DEFSDMEMBER(T_STRING,  bank_group_id           ,0),\
  APP_DEFSDMEMBER(T_STRING,  bank_no                 ,0),\
  APP_DEFSDMEMBER(T_STRING,  loan_receipt_nbr        ,0),\
  APP_DEFSDMEMBER(T_STRING,  reg_type                ,0),\
  APP_DEFSDMEMBER(T_DOUBLE,  reg_amt                 ,2),\
  APP_DEFSDMEMBER(T_STRING,  biz_date                ,0),\
  APP_DEFSDMEMBER(T_STRING,  cust_id                 ,0),\
  APP_DEFSDMEMBER(T_STRING,  acct_no                 ,0),\
  APP_DEFSDMEMBER(T_STRING,  acct_type               ,0),\
  APP_DEFSDMEMBER(T_STRING,  created_datetime        ,0),\
  APP_DEFSDMEMBER(T_STRING,  last_modified_datetime  ,0),\
  APP_DEFSDMEMBER(T_STRING,  card_no                 ,0),\
  APP_DEFSDMEMBER(T_STRING,  is_check_flag           ,0),\
  APP_DEFSDMEMBER(T_STRING,  extend_param1           ,0),\
  APP_DEFSDMEMBER(T_STRING,  extend_param2           ,0),\
  APP_DEFSDMEMBER(T_STRING,  extend_param3           ,0)
  APP_DECLAREFIELDS(SD_ICPS_WBC_TM_AUTH_BANK_COST_DTL)       
  #undef SD_DATA                                     
  #undef SD_MEMBERS                                  
                                                     
  #endif  /*end of __ICPS_WBC_TM_AUTH_BANK_COST_DTL_H__*/      
