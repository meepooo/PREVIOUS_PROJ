/***********************************************************************
版权所有:恒生电子股份有限公司
项目名称:综合技术平台(Turandot)项目
版    本:V1.00
操作系统:
数 据 库:db2
文 件 名:ICPS_WBC_TM_CUST_LIMIT_O.h
文件描述:结构定义数据库开发嵌C头文件
项 目 组:
程 序 员:[fuwd22392]
发布时间:2018-06-12 10:00:00 [Gen]
修    订:
修改时间:
************************************************************************
表    名:ICPS_WBC_TM_CUST_LIMIT_O
说    明:自定义额度信息表-授权
************************************************************************
修改记录:195
修改日期:
修改内容:
修 改 人:
修改内容:
************************************************************************/
#ifndef __ICPS_WBC_TM_CUST_LIMIT_O_H__
#define __ICPS_WBC_TM_CUST_LIMIT_O_H__
typedef struct TDB_ICPS_WBC_TM_CUST_LIMIT_O
{
  char		busi_date[8+1];                     /*              */
  int		file_order;                         /*              */
  char		org[12+1];                          /* 机构号       */
  char		cust_limit_id[20+1];                /* 客户额度ID fuwd22392  */
  char		limit_category[20+1];               /* 额度种类     */
  char		limit_type[1+1];                    /* 额度类型     */
  double	credit_limit;                 /* 信用额度     */
  int		jpa_version;                        /* 乐观锁版本号 */
  char		last_modified_datetime[14+1];       /* 修改时间     */
  char		created_datetime[14+1];             /* 创建时间     */
  char		is_check_flag[1+1];                 /*              */
  char		extend_param1[100+1];               /*              */
  char		extend_param2[250+1];               /*              */
  char		extend_param3[40+1];                /*              */
}ICPS_WBC_TM_CUST_LIMIT_O;

#define SD_DATA  ICPS_WBC_TM_CUST_LIMIT_O
#define SD_MEMBERS \ 
   APP_DEFSDMEMBER(T_STRING,  busi_date               ,0),\
   APP_DEFSDMEMBER(T_LONG,    file_order              ,0),\
   APP_DEFSDMEMBER(T_STRING,  org                     ,0),\
   APP_DEFSDMEMBER(T_STRING,    cust_limit_id           ,0),\
   APP_DEFSDMEMBER(T_STRING,  limit_category          ,0),\
   APP_DEFSDMEMBER(T_STRING,  limit_type              ,0),\
   APP_DEFSDMEMBER(T_DOUBLE,  credit_limit            ,2),\
   APP_DEFSDMEMBER(T_LONG,    jpa_version             ,0),\
   APP_DEFSDMEMBER(T_STRING,  last_modified_datetime  ,0),\
   APP_DEFSDMEMBER(T_STRING,  created_datetime        ,0),\
   APP_DEFSDMEMBER(T_STRING,  is_check_flag           ,0),\
   APP_DEFSDMEMBER(T_STRING,  extend_param1           ,0),\
   APP_DEFSDMEMBER(T_STRING,  extend_param2           ,0),\
   APP_DEFSDMEMBER(T_STRING,  extend_param3           ,0)

  APP_DECLAREFIELDS(SD_ICPS_WBC_TM_CUST_LIMIT_O)
#undef SD_DATA
#undef SD_MEMBERS

#endif  /*end of __ICPS_WBC_TM_CUST_LIMIT_O_H__*/
