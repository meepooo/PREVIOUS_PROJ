/***********************************************************************
版权所有:恒生电子股份有限公司
项目名称:综合技术平台(Turandot)项目
版    本:V1.00
操作系统:
数 据 库:INFORMIX
文 件 名:ICPS_WB_TM_COLL_REC.h
文件描述:结构定义数据库开发嵌C头文件
项 目 组:
程 序 员:[wangzh14925]
发布时间:2009-4-29 19:40:39 [Gen]
修    订:
修改时间:
************************************************************************
表    名:ICPS_WB_TM_COLL_REC (F_WB23.催收记录表)
说    明:
************************************************************************
修改记录:
修改日期:
修改内容:
修 改 人:
修改内容:
************************************************************************/
#ifndef __ICPS_WB_TM_COLL_REC_H__
#define __ICPS_WB_TM_COLL_REC_H__
typedef struct TDB_ICPS_WB_TM_COLL_REC
{
	char   busi_date[8+1];  /*业务日期*/
		/*业务日期*/
	int   file_order;  /*文件序号*/
		/*文件序号*/
	char   org[12+1];  /*机构号*/
		/*机构号*/
	int   coll_rec_id;  /*催记流水号*/
		/*催记流水号*/
	char   case_no[32+1];  /*案件编号*/
		/*案件编号*/
	char   cust_id[20+1];  /*客户编号*/
		/*客户编号*/
	char   coll_rec_type[10+1];  /*催记类型*/
		/*催记类型*/
	char   action_code[32+1];  /*催收动作*/
		/*催收动作*/
	char   user_field1[1+1];  /*备用字段*/
		/*备用字段*/
	char   user_field2[4+1];  /*备用字段2*/
		/*备用字段2*/
	char   coll_time[14+1];  /*催收时间*/
		/*催收时间*/
	char   coll_conseq[10+1];  /*催收结果*/
		/*催收结果*/
	double   prom_amt;  /*承诺金额*/
		/*承诺金额*/
	char   prom_date[14+1];  /*承诺日期*/
		/*承诺日期*/
	char   user_field3[400+1];  /*备用字段3*/
		/*备用字段3*/
	double   user_field4;  /*备用字段4*/
		/*备用字段4*/
	char   user_field5[10+1];  /*备用字段5*/
		/*备用字段5*/
	char   user_field6[10+1];  /*备用字段6*/
		/*备用字段6*/
	char   user_field7[10+1];  /*备用字段7*/
		/*备用字段7*/
	char   user_field8[10+1];  /*备用字段8*/
		/*备用字段8*/
	char   user_field9[10+1];  /*备用字段9*/
		/*备用字段9*/
	char   user_field10[10+1];  /*备用字段10*/
		/*备用字段10*/
	char   user_field11[20+1];  /*备用字段11*/
		/*备用字段11*/
	char   user_field12[50+1];  /*备用字段12*/
		/*备用字段12*/
	char   user_field13[50+1];  /*备用字段13*/
		/*备用字段13*/
	char   user_field14[10+1];  /*备用字段14*/
		/*备用字段14*/
	char   user_field15[10+1];  /*备用字段15*/
		/*备用字段15*/
	char   user_field16[50+1];  /*备用字段16*/
		/*备用字段16*/
	char   user_field17[50+1];  /*备用字段17*/
		/*备用字段17*/
	char   user_field18[14+1];  /*备用字段18*/
		/*备用字段18*/
	char   user_field19[14+1];  /*备用字段19*/
		/*备用字段19*/
	int   user_field20;  /*备用字段20*/
		/*备用字段20*/
	char   is_check_flag[1+1];  /*参与对账标识*/
		/*参与对账标识*/
	char   extend_param1[100+1];  /*扩展1*/
		/*扩展1*/
	char   extend_param2[250+1];  /*扩展2*/
		/*扩展2*/
	char   extend_param3[40+1];  /*扩展3*/
		/*扩展3*/

}ICPS_WB_TM_COLL_REC;

#define SD_DATA  ICPS_WB_TM_COLL_REC
#define SD_MEMBERS \ 
	APP_DEFSDMEMBER(T_STRING,  busi_date, 0),\
	APP_DEFSDMEMBER(T_LONG,  file_order, 0),\
	APP_DEFSDMEMBER(T_STRING,  org, 0),\
	APP_DEFSDMEMBER(T_LONG,  coll_rec_id, 0),\
	APP_DEFSDMEMBER(T_STRING,  case_no, 0),\
	APP_DEFSDMEMBER(T_STRING,  cust_id, 0),\
	APP_DEFSDMEMBER(T_STRING,  coll_rec_type, 0),\
	APP_DEFSDMEMBER(T_STRING,  action_code, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field1, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field2, 0),\
	APP_DEFSDMEMBER(T_STRING,  coll_time, 0),\
	APP_DEFSDMEMBER(T_STRING,  coll_conseq, 0),\
	APP_DEFSDMEMBER(T_DOUBLE,  prom_amt, 2),\
	APP_DEFSDMEMBER(T_STRING,  prom_date, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field3, 0),\
	APP_DEFSDMEMBER(T_DOUBLE,  user_field4, 2),\
	APP_DEFSDMEMBER(T_STRING,  user_field5, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field6, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field7, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field8, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field9, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field10, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field11, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field12, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field13, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field14, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field15, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field16, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field17, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field18, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field19, 0),\
	APP_DEFSDMEMBER(T_LONG,  user_field20, 0),\
	APP_DEFSDMEMBER(T_STRING,  is_check_flag, 0),\
	APP_DEFSDMEMBER(T_STRING,  extend_param1, 0),\
	APP_DEFSDMEMBER(T_STRING,  extend_param2, 0),\
	APP_DEFSDMEMBER(T_STRING,  extend_param3, 0)


	APP_DECLAREFIELDS(SD_ICPS_WB_TM_COLL_REC)
#undef SD_DATA
#undef SD_MEMBERS

#endif  /*end of __ICPS_WB_TM_COLL_REC_H__*/
