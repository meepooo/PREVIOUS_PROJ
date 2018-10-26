/***********************************************************************
版权所有:恒生电子股份有限公司
项目名称:综合技术平台(Turandot)项目
版    本:V1.00
操作系统:
数 据 库:db2
文 件 名:ICPS_WBC_TM_AGREEMENT_NO_MAP.h
文件描述:结构定义数据库开发嵌C头文件
项 目 组:
程 序 员:[fuwd22392]
发布时间:2018-06-12 10:00:00 [Gen]
修    订:
修改时间:
************************************************************************
表    名:ICPS_WBC_TM_AGREEMENT_NO_MAP
说    明:订单号映射表
************************************************************************
修改记录:
修改日期:
修改内容:
修 改 人:
修改内容:
************************************************************************/
#ifndef __ICPS_WBC_TM_AGREEMENT_NO_MAP_H__
#define __ICPS_WBC_TM_AGREEMENT_NO_MAP_H__
typedef struct TDB_ICPS_WBC_TM_AGREEMENT_NO_MAP
{
	char			busi_date[8+1];                      
	int				file_order; 
	char			agreement_no[50+1];                     /*NBS订单号   */
	char			merchant_id[20+1];                      /*平台ID号    */
	char			mer_order_no[50+1];                     /*平台订单号  */
	char			txn_status[4+1];                        /*平台协议状态*/
	char			biz_data[8+1];                       /*业务日期    */
	char			created_datetime[14+1];                 /*创建时间    */
	char			last_modified_datetime[14+1];           /*修改时间    */
	char			is_check_flag[1+1];
	char			extend_param1[100+1];
	char			extend_param2[250+1];
	char			extend_param3[40+1];
}ICPS_WBC_TM_AGREEMENT_NO_MAP;

#define SD_DATA  ICPS_WBC_TM_AGREEMENT_NO_MAP
#define SD_MEMBERS \ 
	APP_DEFSDMEMBER(T_STRING,  busi_date               ,0),\
	APP_DEFSDMEMBER(T_LONG,    file_order              ,0),\
	APP_DEFSDMEMBER(T_STRING,  agreement_no            ,0),\
	APP_DEFSDMEMBER(T_STRING,  merchant_id             ,0),\
	APP_DEFSDMEMBER(T_STRING,  mer_order_no            ,0),\
	APP_DEFSDMEMBER(T_STRING,  txn_status              ,0),\
	APP_DEFSDMEMBER(T_STRING,  biz_data                ,0),\
	APP_DEFSDMEMBER(T_STRING,  created_datetime        ,0),\
	APP_DEFSDMEMBER(T_STRING,  last_modified_datetime  ,0),\
	APP_DEFSDMEMBER(T_STRING,  is_check_flag           ,0),\
	APP_DEFSDMEMBER(T_STRING,  extend_param1           ,0),\
	APP_DEFSDMEMBER(T_STRING,  extend_param2           ,0),\
	APP_DEFSDMEMBER(T_STRING,  extend_param3           ,0)
  	APP_DECLAREFIELDS(SD_ICPS_WBC_TM_AGREEMENT_NO_MAP)
#undef SD_DATA
#undef SD_MEMBERS

#endif  /*end of __ICPS_WBC_TM_AGREEMENT_NO_MAP_H__*/
                              
