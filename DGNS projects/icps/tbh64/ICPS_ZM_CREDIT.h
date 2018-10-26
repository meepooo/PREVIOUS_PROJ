/***********************************************************************
版权所有:恒生电子股份有限公司
项目名称:综合技术平台(Turandot)项目
版    本:V1.00
操作系统:
数 据 库:INFORMIX
文 件 名:ICPS_ZM_CREDIT.h
文件描述:结构定义数据库开发嵌C头文件
项 目 组:
程 序 员:[wangzh14925]
发布时间:2009-4-29 19:40:39 [Gen]
修    订:
修改时间:
************************************************************************
表    名:ICPS_ZM_CREDIT (4.芝麻信用信息表)
说    明:
************************************************************************
修改记录:
修改日期:
修改内容:
修 改 人:
修改内容:
************************************************************************/
#ifndef __ICPS_ZM_CREDIT_H__
#define __ICPS_ZM_CREDIT_H__
typedef struct TDB_ICPS_ZM_CREDIT
{
	char   apply_no[64+1];  /*申请单号*/
		/*申请单号*/
	char   plt_date[8+1];  /*平台日期*/
		/*平台日期*/
	char   plt_serial[16+1];  /*平台流水号*/
		/*平台流水号*/
	char   id_type[2+1];  /*证件类型*/
		/*证件类型*/
	char   id_num[32+1];  /*证件号码*/
		/*证件号码*/
	char   company_name[255+1];  /*所在公司*/
		/*所在公司*/
	char   occupation[64+1];  /*职业类型*/
		/*职业类型*/
	char   have_car_flag[1+1];  /*是否有车*/
		/*是否有车*/
	char   have_house_flag[1+1];  /*是否有房*/
		/*是否有房*/
	int   auth_fin_last_1m_cnt;  /*最近一个月主动查询金融机构数*/
		/*最近一个月主动查询金融机构数*/
	int   auth_fin_last_3m_cnt;  /*最近三个月主动查询金融机构数*/
		/*最近三个月主动查询金融机构数*/
	int   auth_fin_last_6m_cnt;  /*最近六个月主动查询金融机构数*/
		/*最近六个月主动查询金融机构数*/
	int   ovd_order_cnt_6m;  /*最近六个月逾期总笔数*/
		/*最近六个月逾期总笔数*/
	double   ovd_order_amt_6m;  /*最近六个月逾期总金额*/
		/*最近六个月逾期总金额*/
	int   mobile_fixed_days;  /*手机号稳定天数*/
		/*手机号稳定天数*/
	int   adr_stability_days;  /*地址稳定天数*/
		/*地址稳定天数*/
	double   last_6m_avg_asset_total;  /*最近六个月流动资产日均值*/
		/*最近六个月流动资产日均值*/
	double   tot_pay_amt_6m;  /*最近六个月支付总金额*/
		/*最近六个月支付总金额*/
	char   xfdc_index[64+1];  /*消费档次*/
		/*消费档次*/
	int   positive_biz_cnt_1y;  /*最近一年履约场景数*/
		/*最近一年履约场景数*/
	char   extend_param1[100+1];  /*扩展1*/
		/*扩展1*/
	char   extend_param2[250+1];  /*扩展2*/
		/*扩展2*/
	char   extend_param3[40+1];  /*扩展3*/
		/*扩展3*/

}ICPS_ZM_CREDIT;

#define SD_DATA  ICPS_ZM_CREDIT
#define SD_MEMBERS \ 
	APP_DEFSDMEMBER(T_STRING,  apply_no, 0),\
	APP_DEFSDMEMBER(T_STRING,  plt_date, 0),\
	APP_DEFSDMEMBER(T_STRING,  plt_serial, 0),\
	APP_DEFSDMEMBER(T_STRING,  id_type, 0),\
	APP_DEFSDMEMBER(T_STRING,  id_num, 0),\
	APP_DEFSDMEMBER(T_STRING,  company_name, 0),\
	APP_DEFSDMEMBER(T_STRING,  occupation, 0),\
	APP_DEFSDMEMBER(T_STRING,  have_car_flag, 0),\
	APP_DEFSDMEMBER(T_STRING,  have_house_flag, 0),\
	APP_DEFSDMEMBER(T_LONG,  auth_fin_last_1m_cnt, 0),\
	APP_DEFSDMEMBER(T_LONG,  auth_fin_last_3m_cnt, 0),\
	APP_DEFSDMEMBER(T_LONG,  auth_fin_last_6m_cnt, 0),\
	APP_DEFSDMEMBER(T_LONG,  ovd_order_cnt_6m, 0),\
	APP_DEFSDMEMBER(T_DOUBLE,  ovd_order_amt_6m, 2),\
	APP_DEFSDMEMBER(T_LONG,  mobile_fixed_days, 0),\
	APP_DEFSDMEMBER(T_LONG,  adr_stability_days, 0),\
	APP_DEFSDMEMBER(T_DOUBLE,  last_6m_avg_asset_total, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  tot_pay_amt_6m, 2),\
	APP_DEFSDMEMBER(T_STRING,  xfdc_index, 0),\
	APP_DEFSDMEMBER(T_LONG,  positive_biz_cnt_1y, 0),\
	APP_DEFSDMEMBER(T_STRING,  extend_param1, 0),\
	APP_DEFSDMEMBER(T_STRING,  extend_param2, 0),\
	APP_DEFSDMEMBER(T_STRING,  extend_param3, 0)


	APP_DECLAREFIELDS(SD_ICPS_ZM_CREDIT)
#undef SD_DATA
#undef SD_MEMBERS

#endif  /*end of __ICPS_ZM_CREDIT_H__*/
