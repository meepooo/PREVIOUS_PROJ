/***********************************************************************
版权所有:恒生电子股份有限公司
项目名称:综合技术平台(Turandot)项目
版    本:V1.00
操作系统:
数 据 库:INFORMIX
文 件 名:ICPS_WB_TM_LOAN_VMS.h
文件描述:结构定义数据库开发嵌C头文件
项 目 组:
程 序 员:[wangzh14925]
发布时间:2009-4-29 19:40:39 [Gen]
修    订:
修改时间:
************************************************************************
表    名:ICPS_WB_TM_LOAN_VMS (F_WB24.借据纳税加工表)
说    明:
************************************************************************
修改记录:
修改日期:
修改内容:
修 改 人:
修改内容:
************************************************************************/
#ifndef __ICPS_WB_TM_LOAN_VMS_H__
#define __ICPS_WB_TM_LOAN_VMS_H__
typedef struct TDB_ICPS_WB_TM_LOAN_VMS
{
	char   busi_date[8+1];  /*业务日期*/
		/*业务日期*/
	int   file_order;  /*文件序号*/
		/*文件序号*/
	char   id[20+1];  /*纳税借据ID*/
		/*纳税借据ID*/
	char   org[12+1];  /*机构号*/
		/*机构号*/
	char   card_no[19+1];  /*介质卡号*/
		/*介质卡号*/
	char   ref_nbr[23+1];  /*交易参考号*/
		/*交易参考号*/
	char   bank_group_id[5+1];  /*银团编号*/
		/*银团编号*/
	char   bank_no[10+1];  /*银行编号*/
		/*银行编号*/
	char   product_cd[6+1];  /*产品号*/
		/*产品号*/
	double   biz_tax_interes;  /*营业税下的应计和应收息*/
		/*营业税下的应计和应收息*/
	double   vat_int_bal;  /*90天内的应纳税息余额*/
		/*90天内的应纳税息余额*/
	double   norevoke_vat_int_bal;  /*不冲抵算法下应纳税息（含90天内+90天外还款补记部分）*/
		/*不冲抵算法下应纳税息（含90天内+90天外还款补记部分）*/
	double   vat_tax;  /*记账增值税*/
		/*记账增值税*/
	int   loan_int_term;  /*贷款总期数*/
		/*贷款总期数*/
	char   last_modified_time[14+1];  /*上次修改时间*/
		/*上次修改时间*/
	char   paid_out_date[14+1];  /*结清日期*/
		/*结清日期*/
	char   age_no[1+1];  /*账龄*/
		/*账龄*/
	char   batch_date[14+1];  /*批量日期*/
		/*批量日期*/
	int   lpa_version;  /*乐观锁版本号*/
		/*乐观锁版本号*/
	char   is_check_flag[1+1];  /*参与对账标识*/
		/*参与对账标识*/
	char   extend_param1[100+1];  /*扩展1*/
		/*扩展1*/
	char   extend_param2[250+1];  /*扩展2*/
		/*扩展2*/
	char   extend_param3[40+1];  /*扩展3*/
		/*扩展3*/

}ICPS_WB_TM_LOAN_VMS;

#define SD_DATA  ICPS_WB_TM_LOAN_VMS
#define SD_MEMBERS \ 
	APP_DEFSDMEMBER(T_STRING,  busi_date, 0),\
	APP_DEFSDMEMBER(T_LONG,  file_order, 0),\
	APP_DEFSDMEMBER(T_STRING,  id, 0),\
	APP_DEFSDMEMBER(T_STRING,  org, 0),\
	APP_DEFSDMEMBER(T_STRING,  card_no, 0),\
	APP_DEFSDMEMBER(T_STRING,  ref_nbr, 0),\
	APP_DEFSDMEMBER(T_STRING,  bank_group_id, 0),\
	APP_DEFSDMEMBER(T_STRING,  bank_no, 0),\
	APP_DEFSDMEMBER(T_STRING,  product_cd, 0),\
	APP_DEFSDMEMBER(T_DOUBLE,  biz_tax_interes, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  vat_int_bal, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  norevoke_vat_int_bal, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  vat_tax, 2),\
	APP_DEFSDMEMBER(T_LONG,  loan_int_term, 0),\
	APP_DEFSDMEMBER(T_STRING,  last_modified_time, 0),\
	APP_DEFSDMEMBER(T_STRING,  paid_out_date, 0),\
	APP_DEFSDMEMBER(T_STRING,  age_no, 0),\
	APP_DEFSDMEMBER(T_STRING,  batch_date, 0),\
	APP_DEFSDMEMBER(T_LONG,  lpa_version, 0),\
	APP_DEFSDMEMBER(T_STRING,  is_check_flag, 0),\
	APP_DEFSDMEMBER(T_STRING,  extend_param1, 0),\
	APP_DEFSDMEMBER(T_STRING,  extend_param2, 0),\
	APP_DEFSDMEMBER(T_STRING,  extend_param3, 0)


	APP_DECLAREFIELDS(SD_ICPS_WB_TM_LOAN_VMS)
#undef SD_DATA
#undef SD_MEMBERS

#endif  /*end of __ICPS_WB_TM_LOAN_VMS_H__*/
