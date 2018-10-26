/***********************************************************************
版权所有:恒生电子股份有限公司
项目名称:综合技术平台(Turandot)项目
版    本:V1.00
操作系统:
数 据 库:db2
文 件 名:ICPS_WBC_TM_NBS_CUST_EXT_INFO.h
文件描述:结构定义数据库开发嵌C头文件
项 目 组:
程 序 员:[fuwd22392]
发布时间:2018-06-12 10:00:00 [Gen]
修    订:
修改时间:
************************************************************************
表    名:ICPS_WBC_TM_NBS_CUST_EXT_INFO
说    明:nbs客户延展表
************************************************************************
修改记录:
修改日期:
修改内容:
修 改 人:
修改内容:
************************************************************************/
#ifndef __ICPS_WBC_TM_NBS_CUST_EXT_INFO_H__
#define __ICPS_WBC_TM_NBS_CUST_EXT_INFO_H__
typedef struct TDB_ICPS_WBC_TM_NBS_CUST_EXT_INFO
{
	char			busi_date[8+1];
	int				file_order;
	char			nbs_cust_id[20+1];            /*NBS客户ID   */
	char			product_cd[6+1];              /*产品号      */
	char			merchant_id[20+1];            /*平台ID      */
	char			name[80+1];                   /*姓名        */
	char			id_type[2+1];                 /*证件类型    */
	char			id_no[30+1];                  /*证件号码    */
	char			id_no_expiry[30+1];           /*身份证有效期*/
	char			residential_address[100+1];   /*地址        */
	char			gender[1+1];                  /*性别        */
	char			nationality[20+1];            /*国籍        */
	char			marriage[20+1];               /*婚姻状况    */
	char			education[20+1];              /*学历        */
	char			cust_ext_inf1[30+1];          /*民族        */
	char			cust_ext_inf2[30+1];          /*保留字段    */
	char			cust_ext_inf3[30+1];          /*保留字段    */
	char			cust_ext_inf4[30+1];          /*保留字段    */
	char			cust_ext_inf5[30+1];          /*保留字段    */
	char			cust_ext_inf6[30+1];          /*保留字段    */
	char			cust_ext_inf7[30+1];          /*保留字段    */
	char			cust_ext_inf8[30+1];          /*保留字段    */
	char			cust_ext_inf9[30+1];          /*保留字段    */
	char			cust_ext_inf10[30+1];         /*保留字段    */
	char			cust_ext_inf11[30+1];         /*保留字段    */
	char			cust_ext_inf12[30+1];         /*保留字段    */
	char			cust_ext_inf13[30+1];         /*保留字段    */
	char			cust_ext_inf14[30+1];         /*保留字段    */
	char			cust_ext_inf15[30+1];         /*保留字段    */
	char			cust_ext_inf16[30+1];         /*保留字段    */
	char			cust_ext_inf17[50+1];         /*保留字段    */
	char			cust_ext_inf18[50+1];         /*保留字段    */
	char			cust_ext_inf19[100+1];        /*保留字段    */
	char			cust_ext_inf20[100+1];        /*保留字段    */
	char			created_datetime[14+1];       /*创建时间日期*/
	char			last_modified_datetime[14+1]; /*更新时间日期*/
	char			is_check_flag[1+1];
	char			extend_param1[100+1];
	char			extend_param2[250+1];
	char			extend_param3[40+1];
}ICPS_WBC_TM_NBS_CUST_EXT_INFO;

#define SD_DATA  ICPS_WBC_TM_NBS_CUST_EXT_INFO
#define SD_MEMBERS \ 
	APP_DEFSDMEMBER(T_STRING,  busi_date               ,0),\
	APP_DEFSDMEMBER(T_LONG,    file_order              ,0),\
	APP_DEFSDMEMBER(T_STRING,  nbs_cust_id             ,0),\
	APP_DEFSDMEMBER(T_STRING,  product_cd              ,0),\
	APP_DEFSDMEMBER(T_STRING,  merchant_id             ,0),\
	APP_DEFSDMEMBER(T_STRING,  name                    ,0),\
	APP_DEFSDMEMBER(T_STRING,  id_type                 ,0),\
	APP_DEFSDMEMBER(T_STRING,  id_no                   ,0),\
	APP_DEFSDMEMBER(T_STRING,  id_no_expiry            ,0),\
	APP_DEFSDMEMBER(T_STRING,  residential_address     ,0),\
	APP_DEFSDMEMBER(T_STRING,  gender                  ,0),\
	APP_DEFSDMEMBER(T_STRING,  nationality             ,0),\
	APP_DEFSDMEMBER(T_STRING,  marriage                ,0),\
	APP_DEFSDMEMBER(T_STRING,  education               ,0),\
	APP_DEFSDMEMBER(T_STRING,  cust_ext_inf1           ,0),\
	APP_DEFSDMEMBER(T_STRING,  cust_ext_inf2           ,0),\
	APP_DEFSDMEMBER(T_STRING,  cust_ext_inf3           ,0),\
	APP_DEFSDMEMBER(T_STRING,  cust_ext_inf4           ,0),\
	APP_DEFSDMEMBER(T_STRING,  cust_ext_inf5           ,0),\
	APP_DEFSDMEMBER(T_STRING,  cust_ext_inf6           ,0),\
	APP_DEFSDMEMBER(T_STRING,  cust_ext_inf7           ,0),\
	APP_DEFSDMEMBER(T_STRING,  cust_ext_inf8           ,0),\
	APP_DEFSDMEMBER(T_STRING,  cust_ext_inf9           ,0),\
	APP_DEFSDMEMBER(T_STRING,  cust_ext_inf10          ,0),\
	APP_DEFSDMEMBER(T_STRING,  cust_ext_inf11          ,0),\
	APP_DEFSDMEMBER(T_STRING,  cust_ext_inf12          ,0),\
	APP_DEFSDMEMBER(T_STRING,  cust_ext_inf13          ,0),\
	APP_DEFSDMEMBER(T_STRING,  cust_ext_inf14          ,0),\
	APP_DEFSDMEMBER(T_STRING,  cust_ext_inf15          ,0),\
	APP_DEFSDMEMBER(T_STRING,  cust_ext_inf16          ,0),\
	APP_DEFSDMEMBER(T_STRING,  cust_ext_inf17          ,0),\
	APP_DEFSDMEMBER(T_STRING,  cust_ext_inf18          ,0),\
	APP_DEFSDMEMBER(T_STRING,  cust_ext_inf19          ,0),\
	APP_DEFSDMEMBER(T_STRING,  cust_ext_inf20          ,0),\
	APP_DEFSDMEMBER(T_STRING,  created_datetime        ,0),\
	APP_DEFSDMEMBER(T_STRING,  last_modified_datetime  ,0),\
	APP_DEFSDMEMBER(T_STRING,  is_check_flag           ,0),\
	APP_DEFSDMEMBER(T_STRING,  extend_param1           ,0),\
	APP_DEFSDMEMBER(T_STRING,  extend_param2           ,0),\
	APP_DEFSDMEMBER(T_STRING,  extend_param3           ,0)

  APP_DECLAREFIELDS(SD_ICPS_WBC_TM_NBS_CUST_EXT_INFO)
#undef SD_DATA
#undef SD_MEMBERS

#endif  /*end of __ICPS_WBC_TM_NBS_CUST_EXT_INFO_H__*/
                                                                                                                                          
