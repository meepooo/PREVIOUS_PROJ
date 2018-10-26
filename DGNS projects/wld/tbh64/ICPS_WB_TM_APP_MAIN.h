/***********************************************************************
版权所有:恒生电子股份有限公司
项目名称:综合技术平台(Turandot)项目
版    本:V1.00
操作系统:
数 据 库:INFORMIX
文 件 名:ICPS_WB_TM_APP_MAIN.h
文件描述:结构定义数据库开发嵌C头文件
项 目 组:
程 序 员:[wangzh14925]
发布时间:2009-4-29 19:40:39 [Gen]
修    订:
修改时间:
************************************************************************
表    名:ICPS_WB_TM_APP_MAIN (F_WB6.申请主表)
说    明:
************************************************************************
修改记录:
修改日期:
修改内容:
修 改 人:
修改内容:
************************************************************************/
#ifndef __ICPS_WB_TM_APP_MAIN_H__
#define __ICPS_WB_TM_APP_MAIN_H__
typedef struct TDB_ICPS_WB_TM_APP_MAIN
{
	char   busi_date[8+1];  /*业务日期*/
		/*业务日期*/
	int   file_order;  /*文件序号*/
		/*文件序号*/
	char   org[12+1];  /*机构号*/
		/*机构号*/
	char   app_no[20+1];  /*申请件编号*/
		/*申请件编号*/
	char   user_field1[1+1];  /*备用字段*/
		/*备用字段*/
	double   user_field2;  /*备用字段2*/
		/*备用字段2*/
	double   user_field3;  /*备用字段3*/
		/*备用字段3*/
	double   acc_lmt;  /*核准额度*/
		/*核准额度*/
	char   product_cd[6+1];  /*卡产品代码*/
		/*卡产品代码*/
	double   user_field4;  /*备用字段4*/
		/*备用字段4*/
	double   user_field5;  /*备用字段5*/
		/*备用字段5*/
	double   user_field6;  /*备用字段6*/
		/*备用字段6*/
	double   user_field7;  /*备用字段7*/
		/*备用字段7*/
	double   user_field8;  /*备用字段8*/
		/*备用字段8*/
	double   user_field9;  /*备用字段9*/
		/*备用字段9*/
	double   user_field10;  /*备用字段10*/
		/*备用字段10*/
	double   user_field11;  /*备用字段11*/
		/*备用字段11*/
	char   user_field12[1+1];  /*备用字段12*/
		/*备用字段12*/
	char   user_field13[3+1];  /*备用字段13*/
		/*备用字段13*/
	char   user_field14[1+1];  /*备用字段14*/
		/*备用字段14*/
	char   user_field15[20+1];  /*备用字段15*/
		/*备用字段15*/
	char   user_field16[3+1];  /*备用字段16*/
		/*备用字段16*/
	int   user_field17;  /*备用字段17*/
		/*备用字段17*/
	double   user_field18;  /*备用字段18*/
		/*备用字段18*/
	char   user_field19[20+1];  /*备用字段19*/
		/*备用字段19*/
	char   user_field20[400+1];  /*备用字段20*/
		/*备用字段20*/
	char   user_field21[1000+1];  /*备用字段21*/
		/*备用字段21*/
	int   user_field22;  /*备用字段22*/
		/*备用字段22*/
	char   user_field23[1+1];  /*备用字段23*/
		/*备用字段23*/
	char   user_field24[20+1];  /*备用字段24*/
		/*备用字段24*/
	char   user_field25[20+1];  /*备用字段25*/
		/*备用字段25*/
	char   user_field26[9+1];  /*备用字段26*/
		/*备用字段26*/
	char   user_field27[20+1];  /*备用字段27*/
		/*备用字段27*/
	char   user_field28[1+1];  /*备用字段28*/
		/*备用字段28*/
	char   user_field29[80+1];  /*备用字段29*/
		/*备用字段29*/
	char   user_field30[20+1];  /*备用字段30*/
		/*备用字段30*/
	char   user_field31[20+1];  /*备用字段31*/
		/*备用字段31*/
	char   user_field32[1+1];  /*备用字段32*/
		/*备用字段32*/
	char   user_field33[9+1];  /*备用字段33*/
		/*备用字段33*/
	char   user_field34[15+1];  /*备用字段34*/
		/*备用字段34*/
	char   user_field35[20+1];  /*备用字段35*/
		/*备用字段35*/
	char   user_field36[32+1];  /*备用字段36*/
		/*备用字段36*/
	char   user_field37[1+1];  /*备用字段37*/
		/*备用字段37*/
	char   user_field38[40+1];  /*备用字段38*/
		/*备用字段38*/
	char   user_field39[1+1];  /*备用字段39*/
		/*备用字段39*/
	char   user_field40[1+1];  /*备用字段40*/
		/*备用字段40*/
	char   user_field41[1+1];  /*备用字段41*/
		/*备用字段41*/
	char   user_field42[20+1];  /*备用字段42*/
		/*备用字段42*/
	char   user_field43[20+1];  /*备用字段43*/
		/*备用字段43*/
	char   user_field44[400+1];  /*备用字段44*/
		/*备用字段44*/
	char   user_field45[40+1];  /*备用字段45*/
		/*备用字段45*/
	char   user_field46[40+1];  /*备用字段46*/
		/*备用字段46*/
	char   user_field47[32+1];  /*备用字段47*/
		/*备用字段47*/
	char   user_field48[32+1];  /*备用字段48*/
		/*备用字段48*/
	char   user_field49[32+1];  /*备用字段49*/
		/*备用字段49*/
	char   user_field50[10+1];  /*备用字段50*/
		/*备用字段50*/
	char   user_field51[14+1];  /*备用字段51*/
		/*备用字段51*/
	char   last_modified_datetime[14+1];  /*最后修改时间*/
		/*最后修改时间*/
	int   jpa_Vversion;  /*乐观锁*/
		/*乐观锁*/
	char   uesr_field52[1+1];  /*备用字段52*/
		/*备用字段52*/
	char   is_check_flag[1+1];  /*参与对账标识*/
		/*参与对账标识*/
	char   extend_param1[100+1];  /*扩展1*/
		/*扩展1*/
	char   extend_param2[250+1];  /*扩展2*/
		/*扩展2*/
	char   extend_param3[40+1];  /*扩展3*/
		/*扩展3*/

}ICPS_WB_TM_APP_MAIN;

#define SD_DATA  ICPS_WB_TM_APP_MAIN
#define SD_MEMBERS \ 
	APP_DEFSDMEMBER(T_STRING,  busi_date, 0),\
	APP_DEFSDMEMBER(T_LONG,  file_order, 0),\
	APP_DEFSDMEMBER(T_STRING,  org, 0),\
	APP_DEFSDMEMBER(T_STRING,  app_no, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field1, 0),\
	APP_DEFSDMEMBER(T_DOUBLE,  user_field2, 4),\
	APP_DEFSDMEMBER(T_DOUBLE,  user_field3, 4),\
	APP_DEFSDMEMBER(T_DOUBLE,  acc_lmt, 4),\
	APP_DEFSDMEMBER(T_STRING,  product_cd, 0),\
	APP_DEFSDMEMBER(T_DOUBLE,  user_field4, 4),\
	APP_DEFSDMEMBER(T_DOUBLE,  user_field5, 4),\
	APP_DEFSDMEMBER(T_DOUBLE,  user_field6, 4),\
	APP_DEFSDMEMBER(T_DOUBLE,  user_field7, 4),\
	APP_DEFSDMEMBER(T_DOUBLE,  user_field8, 4),\
	APP_DEFSDMEMBER(T_DOUBLE,  user_field9, 4),\
	APP_DEFSDMEMBER(T_DOUBLE,  user_field10, 4),\
	APP_DEFSDMEMBER(T_DOUBLE,  user_field11, 4),\
	APP_DEFSDMEMBER(T_STRING,  user_field12, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field13, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field14, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field15, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field16, 0),\
	APP_DEFSDMEMBER(T_LONG,  user_field17, 0),\
	APP_DEFSDMEMBER(T_DOUBLE,  user_field18, 2),\
	APP_DEFSDMEMBER(T_STRING,  user_field19, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field20, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field21, 0),\
	APP_DEFSDMEMBER(T_LONG,  user_field22, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field23, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field24, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field25, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field26, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field27, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field28, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field29, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field30, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field31, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field32, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field33, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field34, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field35, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field36, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field37, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field38, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field39, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field40, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field41, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field42, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field43, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field44, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field45, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field46, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field47, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field48, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field49, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field50, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field51, 0),\
	APP_DEFSDMEMBER(T_STRING,  last_modified_datetime, 0),\
	APP_DEFSDMEMBER(T_LONG,  jpa_Vversion, 0),\
	APP_DEFSDMEMBER(T_STRING,  uesr_field52, 0),\
	APP_DEFSDMEMBER(T_STRING,  is_check_flag, 0),\
	APP_DEFSDMEMBER(T_STRING,  extend_param1, 0),\
	APP_DEFSDMEMBER(T_STRING,  extend_param2, 0),\
	APP_DEFSDMEMBER(T_STRING,  extend_param3, 0)


	APP_DECLAREFIELDS(SD_ICPS_WB_TM_APP_MAIN)
#undef SD_DATA
#undef SD_MEMBERS

#endif  /*end of __ICPS_WB_TM_APP_MAIN_H__*/
