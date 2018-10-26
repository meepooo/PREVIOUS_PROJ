/***********************************************************************
版权所有:恒生电子股份有限公司
项目名称:综合技术平台(Turandot)项目
版    本:V1.00
操作系统:
数 据 库:INFORMIX
文 件 名:ICPS_WB_TM_CARD.h
文件描述:结构定义数据库开发嵌C头文件
项 目 组:
程 序 员:[wangzh14925]
发布时间:2009-4-29 19:40:39 [Gen]
修    订:
修改时间:
************************************************************************
表    名:ICPS_WB_TM_CARD (F_WB3.逻辑卡表)
说    明:
************************************************************************
修改记录:
修改日期:
修改内容:
修 改 人:
修改内容:
************************************************************************/
#ifndef __ICPS_WB_TM_CARD_H__
#define __ICPS_WB_TM_CARD_H__
typedef struct TDB_ICPS_WB_TM_CARD
{
	char   busi_date[8+1];  /*业务日期*/
		/*业务日期*/
	int   file_order;  /*文件序号*/
		/*文件序号*/
	char   org[12+1];  /*机构号*/
		/*机构号*/
	char   logical_card_no[19+1];  /*逻辑卡号*/
		/*逻辑卡号*/
	char   acct_no[20+1];  /*账户编号*/
		/*账户编号*/
	char   cust_id[20+1];  /*客户编号*/
		/*客户编号*/
	char   user_field118[15+1];  /*备用字段118*/
		/*备用字段118*/
	char   product_cd[6+1];  /*产品代码*/
		/*产品代码*/
	char   app_no[20+1];  /*申请件编号*/
		/*申请件编号*/
	char   user_field119[40+1];  /*备用字段119*/
		/*备用字段119*/
	char   user_field120[1+1];  /*备用字段120*/
		/*备用字段120*/
	char   bsc_logiccard_no[19+1];  /*逻辑卡主卡卡号*/
		/*逻辑卡主卡卡号*/
	char   user_field121[9+1];  /*备用字段121*/
		/*备用字段121*/
	char   user_field122[15+1];  /*备用字段122*/
		/*备用字段122*/
	char   user_field123[80+1];  /*备用字段123*/
		/*备用字段123*/
	char   user_field124[19+1];  /*备用字段124*/
		/*备用字段124*/
	char   user_field125[14+1];  /*备用字段125*/
		/*备用字段125*/
	char   user_field126[27+1];  /*备用字段126*/
		/*备用字段126*/
	char   activate_ind[1+1];  /*是否已激活*/
		/*是否已激活*/
	char   cancel_date[14+1];  /*销卡销户日期*/
		/*销卡销户日期*/
	char   latest_card_no[19+1];  /*最新介质卡号*/
		/*最新介质卡号*/
	char   user_field127[1+1];  /*备用字段127*/
		/*备用字段127*/
	char   user_field128[20+1];  /*备用字段128*/
		/*备用字段128*/
	char   user_field129[80+1];  /*备用字段129*/
		/*备用字段129*/
	char   user_field130[1+1];  /*备用字段130*/
		/*备用字段130*/
	char   user_field131[1+1];  /*备用字段131*/
		/*备用字段131*/
	char   card_expire_date[14+1];  /*卡片有效日期*/
		/*卡片有效日期*/
	double   user_field132;  /*备用字段132*/
		/*备用字段132*/
	char   user_field133[1+1];  /*备用字段133*/
		/*备用字段133*/
	char   user_field134[3+1];  /*备用字段134*/
		/*备用字段134*/
	char   user_field135[14+1];  /*备用字段135*/
		/*备用字段135*/
	char   user_field136[14+1];  /*备用字段136*/
		/*备用字段136*/
	char   user_field137[1+1];  /*备用字段137*/
		/*备用字段137*/
	char   user_field138[14+1];  /*备用字段138*/
		/*备用字段138*/
	char   user_field139[1+1];  /*备用字段139*/
		/*备用字段139*/
	char   user_field140[1+1];  /*备用字段140*/
		/*备用字段140*/
	char   user_field141[1+1];  /*备用字段141*/
		/*备用字段141*/
	int   jpa_version;  /*乐观锁版本号*/
		/*乐观锁版本号*/
	char   user_field142[14+1];  /*备用字段142*/
		/*备用字段142*/
	char   user_field143[14+1];  /*备用字段143*/
		/*备用字段143*/
	char   user_field144[14+1];  /*备用字段144*/
		/*备用字段144*/
	char   user_field145[14+1];  /*备用字段145*/
		/*备用字段145*/
	char   is_check_flag[1+1];  /*参与对账标识*/
		/*参与对账标识*/
	char   extend_param1[100+1];  /*扩展1*/
		/*扩展1*/
	char   extend_param2[250+1];  /*扩展2*/
		/*扩展2*/
	char   extend_param3[40+1];  /*扩展3*/
		/*扩展3*/

}ICPS_WB_TM_CARD;

#define SD_DATA  ICPS_WB_TM_CARD
#define SD_MEMBERS \ 
	APP_DEFSDMEMBER(T_STRING,  busi_date, 0),\
	APP_DEFSDMEMBER(T_LONG,  file_order, 0),\
	APP_DEFSDMEMBER(T_STRING,  org, 0),\
	APP_DEFSDMEMBER(T_STRING,  logical_card_no, 0),\
	APP_DEFSDMEMBER(T_STRING,  acct_no, 0),\
	APP_DEFSDMEMBER(T_STRING,  cust_id, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field118, 0),\
	APP_DEFSDMEMBER(T_STRING,  product_cd, 0),\
	APP_DEFSDMEMBER(T_STRING,  app_no, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field119, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field120, 0),\
	APP_DEFSDMEMBER(T_STRING,  bsc_logiccard_no, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field121, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field122, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field123, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field124, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field125, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field126, 0),\
	APP_DEFSDMEMBER(T_STRING,  activate_ind, 0),\
	APP_DEFSDMEMBER(T_STRING,  cancel_date, 0),\
	APP_DEFSDMEMBER(T_STRING,  latest_card_no, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field127, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field128, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field129, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field130, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field131, 0),\
	APP_DEFSDMEMBER(T_STRING,  card_expire_date, 0),\
	APP_DEFSDMEMBER(T_DOUBLE,  user_field132, 2),\
	APP_DEFSDMEMBER(T_STRING,  user_field133, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field134, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field135, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field136, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field137, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field138, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field139, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field140, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field141, 0),\
	APP_DEFSDMEMBER(T_LONG,  jpa_version, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field142, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field143, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field144, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field145, 0),\
	APP_DEFSDMEMBER(T_STRING,  is_check_flag, 0),\
	APP_DEFSDMEMBER(T_STRING,  extend_param1, 0),\
	APP_DEFSDMEMBER(T_STRING,  extend_param2, 0),\
	APP_DEFSDMEMBER(T_STRING,  extend_param3, 0)


	APP_DECLAREFIELDS(SD_ICPS_WB_TM_CARD)
#undef SD_DATA
#undef SD_MEMBERS

#endif  /*end of __ICPS_WB_TM_CARD_H__*/
