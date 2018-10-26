/***********************************************************************
版权所有:恒生电子股份有限公司
项目名称:综合技术平台(Turandot)项目
版    本:V1.00
操作系统:
数 据 库:
文 件 名:ICPS_WB_CAV_INFO.h
文件描述:结构定义数据库开发嵌C头文件
项 目 组:
程 序 员:
发布时间:2009-4-29 19:40:39 [Gen]
修    订:
修改时间:
************************************************************************
表    名:ICPS_WB_CAV_INFO (微粒贷核销信息表)
说    明:
************************************************************************
修改记录:
修改日期:
修改内容:
修 改 人:
修改内容:
************************************************************************/
#ifndef __ICPS_WB_CAV_INFO_H__
#define __ICPS_WB_CAV_INFO_H__
typedef struct TDB_ICPS_WB_CAV_INFO
{
	char   BUSI_DATE[8+1];  /*业务日期*/
	char   NAME[90+1];  /*客户姓名*/
	char   CERTI_NO[18+1];  /*身份证号*/
	char   CARD_NO[19+1];  /*银行卡号*/
	char   CUST_ID[32+1];  /*CNC客户ID*/
	char   LOGICAL_CARD_NO[19+1];  /*逻辑卡号*/
	char   PRODUCT_CD[6+1];  /*产品号*/
	char   REF_NBR[23+1];  /*借据号（交易参考号）*/
	double LOAN_INIT_PRIN;  /*借据本金*/
	char   BANK_GROUP_ID[5+1];  /*银团编号*/
	char   EXTEND_PARAM1[100+1];  /*扩展1*/
	char   EXTEND_PARAM2[250+1];  /*扩展2*/
	char   EXTEND_PARAM3[40+1];  /*扩展3*/

}ICPS_WB_CAV_INFO;

#define SD_DATA  ICPS_WB_CAV_INFO
#define SD_MEMBERS \ 
	APP_DEFSDMEMBER(T_STRING,  BUSI_DATE, 0),\
	APP_DEFSDMEMBER(T_STRING,  NAME, 0),\
	APP_DEFSDMEMBER(T_STRING,  CERTI_NO, 0),\
	APP_DEFSDMEMBER(T_STRING,  CARD_NO, 0),\
	APP_DEFSDMEMBER(T_STRING,  CUST_ID, 0),\
	APP_DEFSDMEMBER(T_STRING,  LOGICAL_CARD_NO, 0),\
	APP_DEFSDMEMBER(T_STRING,  PRODUCT_CD, 0),\
	APP_DEFSDMEMBER(T_STRING,  REF_NBR, 0),\
	APP_DEFSDMEMBER(T_DOUBLE,  LOAN_INIT_PRIN, 2),\
	APP_DEFSDMEMBER(T_STRING,  BANK_GROUP_ID, 0),\
	APP_DEFSDMEMBER(T_STRING,  EXTEND_PARAM1, 0),\
	APP_DEFSDMEMBER(T_STRING,  EXTEND_PARAM2, 0),\
	APP_DEFSDMEMBER(T_STRING,  EXTEND_PARAM3, 0)

	APP_DECLAREFIELDS(SD_ICPS_WB_CAV_INFO)
#undef SD_DATA
#undef SD_MEMBERS

#endif  /*end of __ICPS_WB_CAV_INFO_H__*/
