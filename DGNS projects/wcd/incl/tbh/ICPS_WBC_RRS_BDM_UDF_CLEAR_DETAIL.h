/***********************************************************************
版权所有:恒生电子股份有限公司
项目名称:综合技术平台(Turandot)项目
版    本:V1.00
操作系统:
数 据 库:db2
文 件 名:ICPS_WBC_RRS_BDM_UDF_CLEAR_DETAIL.h
文件描述:结构定义数据库开发嵌C头文件
项 目 组:
程 序 员:[fuwd22392]
发布时间:2018-06-12 10:00:00 [Gen]
修    订:
修改时间:
************************************************************************
表    名:ICPS_WBC_RRS_BDM_UDF_CLEAR_DETAIL
说    明:备付金资金清算明细
************************************************************************
修改记录:
修改日期:
修改内容:
修 改 人:
修改内容:
************************************************************************/
#ifndef __ICPS_WBC_RRS_BDM_UDF_CLEAR_DETAIL_H__
#define __ICPS_WBC_RRS_BDM_UDF_CLEAR_DETAIL_H__
typedef struct TDB_ICPS_WBC_RRS_BDM_UDF_CLEAR_DETAIL
{
	char			busi_date[8+1];
	int				file_order;
	char			data_dt[10+1];            /*数据日期  */
	char			acct_no[40+1];            /*备付金帐号*/
	char			ccy[3+1];                 /*币种      */
	char			bank_group_code[5+1];     /*银团编号  */
	char			data_type[6+1];           /*数据类型  */
	double			amount;                   /*发生额    */
	char			ds[10+1];                 /*日期分区  */
	char			is_check_flag[1+1];
	char			extend_param1[100+1];
	char			extend_param2[250+1];
	char			extend_param3[40+1];
}ICPS_WBC_RRS_BDM_UDF_CLEAR_DETAIL;

#define SD_DATA  ICPS_WBC_RRS_BDM_UDF_CLEAR_DETAIL
#define SD_MEMBERS \ 
  APP_DEFSDMEMBER(T_STRING,  busi_date        ,0),\
  APP_DEFSDMEMBER(T_LONG,    file_order       ,0),\
  APP_DEFSDMEMBER(T_STRING,  data_dt          ,0),\
  APP_DEFSDMEMBER(T_STRING,  acct_no          ,0),\
  APP_DEFSDMEMBER(T_STRING,  ccy              ,0),\
  APP_DEFSDMEMBER(T_STRING,  bank_group_code  ,0),\
  APP_DEFSDMEMBER(T_STRING,  data_type        ,0),\
  APP_DEFSDMEMBER(T_DOUBLE,  amount           ,4),\
  APP_DEFSDMEMBER(T_STRING,  ds               ,0),\
  APP_DEFSDMEMBER(T_STRING,  is_check_flag    ,0),\
  APP_DEFSDMEMBER(T_STRING,  extend_param1    ,0),\
  APP_DEFSDMEMBER(T_STRING,  extend_param2    ,0),\
  APP_DEFSDMEMBER(T_STRING,  extend_param3    ,0)
  APP_DECLAREFIELDS(SD_ICPS_WBC_RRS_BDM_UDF_CLEAR_DETAIL)
#undef SD_DATA
#undef SD_MEMBERS

#endif  /*end of __ICPS_WBC_RRS_BDM_UDF_CLEAR_DETAIL_H__*/
