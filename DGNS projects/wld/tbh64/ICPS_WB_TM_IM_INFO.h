/***********************************************************************
版权所有:恒生电子股份有限公司
项目名称:综合技术平台(Turandot)项目
版    本:V1.00
操作系统:
数 据 库:INFORMIX
文 件 名:ICPS_WB_TM_IM_INFO.h
文件描述:结构定义数据库开发嵌C头文件
项 目 组:
程 序 员:[wangzh14925]
发布时间:2009-4-29 19:40:39 [Gen]
修    订:
修改时间:
************************************************************************
表    名:ICPS_WB_TM_IM_INFO (F_WB16.客户即时通讯信息表)
说    明:
************************************************************************
修改记录:
修改日期:
修改内容:
修 改 人:
修改内容:
************************************************************************/
#ifndef __ICPS_WB_TM_IM_INFO_H__
#define __ICPS_WB_TM_IM_INFO_H__
typedef struct TDB_ICPS_WB_TM_IM_INFO
{
	char   busi_date[8+1];  /*业务日期*/
		/*业务日期*/
	int   file_order;  /*文件序号*/
		/*文件序号*/
	char   seq_no[20+1];  /*序号*/
		/*序号*/
	char   org[12+1];  /*机构号*/
		/*机构号*/
	char   product_code[6+1];  /*产品代码*/
		/*产品代码*/
	char   cust_id[20+1];  /*客户编号*/
		/*客户编号*/
	char   acct_no[20+1];  /*账户编号*/
		/*账户编号*/
	char   app_type[3+1];  /*应用类型*/
		/*应用类型*/
	char   app_acct_no[40+1];  /*应用账号*/
		/*应用账号*/
	char   user_field282[255+1];  /*备用字段282*/
		/*备用字段282*/
	char   created_datetime[14+1];  /*创建时间*/
		/*创建时间*/
	char   update_time[14+1];  /*更新时间*/
		/*更新时间*/
	int   jpa_version;  /*乐观锁版本号*/
		/*乐观锁版本号*/
	char   last_update_biz_date[14+1];  /*上次联机更新业务日期*/
		/*上次联机更新业务日期*/
	char   is_check_flag[1+1];  /*参与对账标识*/
		/*参与对账标识*/
	char   extend_param1[100+1];  /*扩展1*/
		/*扩展1*/
	char   extend_param2[250+1];  /*扩展2*/
		/*扩展2*/
	char   extend_param3[40+1];  /*扩展3*/
		/*扩展3*/

}ICPS_WB_TM_IM_INFO;

#define SD_DATA  ICPS_WB_TM_IM_INFO
#define SD_MEMBERS \ 
	APP_DEFSDMEMBER(T_STRING,  busi_date, 0),\
	APP_DEFSDMEMBER(T_LONG,  file_order, 0),\
	APP_DEFSDMEMBER(T_STRING,  seq_no, 0),\
	APP_DEFSDMEMBER(T_STRING,  org, 0),\
	APP_DEFSDMEMBER(T_STRING,  product_code, 0),\
	APP_DEFSDMEMBER(T_STRING,  cust_id, 0),\
	APP_DEFSDMEMBER(T_STRING,  acct_no, 0),\
	APP_DEFSDMEMBER(T_STRING,  app_type, 0),\
	APP_DEFSDMEMBER(T_STRING,  app_acct_no, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field282, 0),\
	APP_DEFSDMEMBER(T_STRING,  created_datetime, 0),\
	APP_DEFSDMEMBER(T_STRING,  update_time, 0),\
	APP_DEFSDMEMBER(T_LONG,  jpa_version, 0),\
	APP_DEFSDMEMBER(T_STRING,  last_update_biz_date, 0),\
	APP_DEFSDMEMBER(T_STRING,  is_check_flag, 0),\
	APP_DEFSDMEMBER(T_STRING,  extend_param1, 0),\
	APP_DEFSDMEMBER(T_STRING,  extend_param2, 0),\
	APP_DEFSDMEMBER(T_STRING,  extend_param3, 0)


	APP_DECLAREFIELDS(SD_ICPS_WB_TM_IM_INFO)
#undef SD_DATA
#undef SD_MEMBERS

#endif  /*end of __ICPS_WB_TM_IM_INFO_H__*/
