/***********************************************************************
版权所有:恒生电子股份有限公司
项目名称:综合技术平台(Turandot)项目
版    本:V1.00
操作系统:
数 据 库:db2
文 件 名:ICPS_WBC_TM_PSB_CHECK_INFO.h
文件描述:结构定义数据库开发嵌C头文件
项 目 组:
程 序 员:[fuwd22392]
发布时间:2018-06-12 10:00:00 [Gen]
修    订:
修改时间:
************************************************************************
表    名:ICPS_WBC_TM_PSB_CHECK_INFO
说    明:
************************************************************************
修改记录:
修改日期:
修改内容:
修 改 人:
修改内容:
************************************************************************/
#ifndef __ICPS_WBC_TM_PSB_CHECK_INFO_H__
#define __ICPS_WBC_TM_PSB_CHECK_INFO_H__
typedef struct TDB_ICPS_WBC_TM_PSB_CHECK_INFO
{
	char			busi_date[8+1];                  
	int				file_order;
	char			seq_no[32+1];                   /*查询流水号      */
	char			org[12+1];                      /*机构号          */
	char			app_no[20+1];                   /*申请件编号      */
	char			id_type[2+1];                   /*证件类型        */
	char			id_no[18+1];                    /*证件号码        */
	char			name[30+1];                     /*姓名            */
	char			gender[2+1];                    /*性别            */
	char			result_person_id[1+1];          /*证件号码核查结果*/
	char			result_person_name[1+1];        /*姓名核查结果    */
	char			photo_id[100+1];                /*照片文件id      */
	char			nation[40+1];                   /*民族            */
	char			photo_md5[100+1];               /*照片md5值       */
	char			old_name[80+1];                 /*曾用名          */
	char			birth[8+1];                     /*出生日期        */
	char			native_place[100+1];            /*籍贯省市县（区）*/
	char			address[100+1];                 /*住址            */
	char			work_place[100+1];              /*服务处所        */
	char			marital_status[40+1];           /*婚姻状况        */
	char			degree_of_education[100+1];     /*文化程度        */
	char			issued_authority[50+1];         /*签发机关        */
	char			birth_place[25+1];              /*出生地          */
	char			occupation[30+1];               /*职业            */
	char			bl0[20+1];                      /*在逃状态        */
	char			bl1[20+1];                      /*违法状态        */
	char			created_datetime[14+1];         /*创建时间        */
	char			last_modified_datetime[14+1];   /*最后修改时间    */
	int				jpa_version;                    /*乐观锁          */
	char			product_cd[6+1];                /*产品编号        */
	char			msg_serv_error[40+1];           /*服务异常描述    */
	char			msg_id_error[40+1];             /*查询结果描述    */
	char			flag[1+1];                      /*结果获取渠道    */
	char			is_check_flag[1+1];
	char			extend_param1[100+1];
	char			extend_param2[250+1];
	char			extend_param3[40+1];

}ICPS_WBC_TM_PSB_CHECK_INFO;

#define SD_DATA  ICPS_WBC_TM_PSB_CHECK_INFO
#define SD_MEMBERS \ 
	APP_DEFSDMEMBER(T_STRING,  busi_date               ,0),\
	APP_DEFSDMEMBER(T_LONG,    file_order              ,0),\
	APP_DEFSDMEMBER(T_STRING,  seq_no                  ,0),\
	APP_DEFSDMEMBER(T_STRING,  org                     ,0),\
	APP_DEFSDMEMBER(T_STRING,  app_no                  ,0),\
	APP_DEFSDMEMBER(T_STRING,  id_type                 ,0),\
	APP_DEFSDMEMBER(T_STRING,  id_no                   ,0),\
	APP_DEFSDMEMBER(T_STRING,  name                    ,0),\
	APP_DEFSDMEMBER(T_STRING,  gender                  ,0),\
	APP_DEFSDMEMBER(T_STRING,  result_person_id        ,0),\
	APP_DEFSDMEMBER(T_STRING,  result_person_name      ,0),\
	APP_DEFSDMEMBER(T_STRING,  photo_id                ,0),\
	APP_DEFSDMEMBER(T_STRING,  nation                  ,0),\
	APP_DEFSDMEMBER(T_STRING,  photo_md5               ,0),\
	APP_DEFSDMEMBER(T_STRING,  old_name                ,0),\
	APP_DEFSDMEMBER(T_STRING,  birth                   ,0),\
	APP_DEFSDMEMBER(T_STRING,  native_place            ,0),\
	APP_DEFSDMEMBER(T_STRING,  address                 ,0),\
	APP_DEFSDMEMBER(T_STRING,  work_place              ,0),\
	APP_DEFSDMEMBER(T_STRING,  marital_status          ,0),\
	APP_DEFSDMEMBER(T_STRING,  degree_of_education     ,0),\
	APP_DEFSDMEMBER(T_STRING,  issued_authority        ,0),\
	APP_DEFSDMEMBER(T_STRING,  birth_place             ,0),\
	APP_DEFSDMEMBER(T_STRING,  occupation              ,0),\
	APP_DEFSDMEMBER(T_STRING,  bl0                     ,0),\
	APP_DEFSDMEMBER(T_STRING,  bl1                     ,0),\
	APP_DEFSDMEMBER(T_STRING,  created_datetime        ,0),\
	APP_DEFSDMEMBER(T_STRING,  last_modified_datetime  ,0),\
	APP_DEFSDMEMBER(T_LONG,    jpa_version             ,0),\
	APP_DEFSDMEMBER(T_STRING,  product_cd              ,0),\
	APP_DEFSDMEMBER(T_STRING,  msg_serv_error          ,0),\
	APP_DEFSDMEMBER(T_STRING,  msg_id_error            ,0),\
	APP_DEFSDMEMBER(T_STRING,  flag                    ,0),\
	APP_DEFSDMEMBER(T_STRING,  is_check_flag           ,0),\
	APP_DEFSDMEMBER(T_STRING,  extend_param1           ,0),\
	APP_DEFSDMEMBER(T_STRING,  extend_param2           ,0),\
	APP_DEFSDMEMBER(T_STRING,  extend_param3           ,0)
  APP_DECLAREFIELDS(SD_ICPS_WBC_TM_PSB_CHECK_INFO)
#undef SD_DATA
#undef SD_MEMBERS

#endif  /*end of __ICPS_WBC_TM_PSB_CHECK_INFO_H__*/
                                                                                                                              
