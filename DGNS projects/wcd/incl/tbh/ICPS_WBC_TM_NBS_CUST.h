/***********************************************************************
版权所有:恒生电子股份有限公司
项目名称:综合技术平台(Turandot)项目
版    本:V1.00
操作系统:
数 据 库:db2
文 件 名:ICPS_WBC_TM_NBS_CUST.h
文件描述:结构定义数据库开发嵌C头文件
项 目 组:
程 序 员:[fuwd22392]
发布时间:2018-06-12 10:00:00 [Gen]
修    订:
修改时间:
************************************************************************
表    名:ICPS_WBC_TM_NBS_CUST
说    明:nbs客户表
************************************************************************
修改记录:
修改日期:
修改内容:
修 改 人:
修改内容:
************************************************************************/
#ifndef __ICPS_WBC_TM_NBS_CUST_H__
#define __ICPS_WBC_TM_NBS_CUST_H__
typedef struct TDB_ICPS_WBC_TM_NBS_CUST
{
	char			busi_date[8+1];                
	int				file_order;
	char			nbs_cust_id[20+1];                  /*NBS客户ID   */
	char			name[80+1];                         /*姓名        */
	char			id_type[2+1];                       /*证件类型    */
	char			id_no[30+1];                        /*证件号码    */
	char			ecif_no[40+1];                      /*ecif客户号  */
	char			reserve1[20+1];                     /*保留字段1   */
	char			reserve2[20+1];                     /*身份证有效期*/
	char			reserve3[50+1];                     /*保留字段3   */
	char			biz_date[8+1];                      /*业务日期    */
	char			created_datetime[14+1];             /*创建时间日期*/
	char			last_modified_datetime[14+1];       /*更新时间日期*/
	char			is_check_flag[1+1];
	char			extend_param1[100+1];
	char			extend_param2[250+1];
	char			extend_param3[40+1];

}ICPS_WBC_TM_NBS_CUST;

#define SD_DATA  ICPS_WBC_TM_NBS_CUST
#define SD_MEMBERS \ 
   APP_DEFSDMEMBER(T_STRING,  busi_date               ,0),\
   APP_DEFSDMEMBER(T_LONG,    file_order              ,0),\
   APP_DEFSDMEMBER(T_STRING,  nbs_cust_id             ,0),\
   APP_DEFSDMEMBER(T_STRING,  name                    ,0),\
   APP_DEFSDMEMBER(T_STRING,  id_type                 ,0),\
   APP_DEFSDMEMBER(T_STRING,  id_no                   ,0),\
   APP_DEFSDMEMBER(T_STRING,  ecif_no                 ,0),\
   APP_DEFSDMEMBER(T_STRING,  reserve1                ,0),\
   APP_DEFSDMEMBER(T_STRING,  reserve2                ,0),\
   APP_DEFSDMEMBER(T_STRING,  reserve3                ,0),\
   APP_DEFSDMEMBER(T_STRING,  biz_date                ,0),\
   APP_DEFSDMEMBER(T_STRING,  created_datetime        ,0),\
   APP_DEFSDMEMBER(T_STRING,  last_modified_datetime  ,0),\
   APP_DEFSDMEMBER(T_STRING,  is_check_flag           ,0),\
   APP_DEFSDMEMBER(T_STRING,  extend_param1           ,0),\
   APP_DEFSDMEMBER(T_STRING,  extend_param2           ,0),\
   APP_DEFSDMEMBER(T_STRING,  extend_param3           ,0)
  APP_DECLAREFIELDS(SD_ICPS_WBC_TM_NBS_CUST)
#undef SD_DATA
#undef SD_MEMBERS

#endif  /*end of __ICPS_WBC_TM_NBS_CUSTN_H__*/
