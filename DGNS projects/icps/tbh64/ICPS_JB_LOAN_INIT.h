/***********************************************************************
版权所有:恒生电子股份有限公司
项目名称:综合技术平台(Turandot)项目
版    本:V1.00
操作系统:
数 据 库:INFORMIX
文 件 名:ICPS_JB_LOAN_INIT.h
文件描述:结构定义数据库开发嵌C头文件
项 目 组:
程 序 员:[wangzh14925]
发布时间:2009-4-29 19:40:39 [Gen]
修    订:
修改时间:
************************************************************************
表    名:ICPS_JB_LOAN_INIT (F_JB9.日初（借据）信息文件)
说    明:
************************************************************************
修改记录:
修改日期:
修改内容:
修 改 人:
修改内容:
************************************************************************/
#ifndef __ICPS_JB_LOAN_INIT_H__
#define __ICPS_JB_LOAN_INIT_H__
typedef struct TDB_ICPS_JB_LOAN_INIT
{
	char   busi_date[8+1];  /*业务日期*/
		/*业务日期*/
	int   file_order;  /*文件序号*/
		/*文件序号*/
	char   contract_no[32+1];  /*借呗平台贷款合同号*/
		/*借呗平台贷款合同号*/
	char   settle_date[8+1];  /*会计日期*/
		/*会计日期，格式YYYYMMdd*/
	char   status[10+1];  /*借据状态*/
		/*借据状态，正常NORMAL,逾期OVD,结清CLEAR */
	char   clear_date[8+1];  /*结清日期*/
		/*结清日期，格式YYYYMMdd*/
	char   asset_class[2+1];  /*五级分类标识*/
		/*五级分类标识，正常1，关注2，次级3，可疑4，损失5*/
	char   accrued_status[2+1];  /*应计非应计标识*/
		/*应计非应计标识，应计0，非应计1*/
	char   next_repay_date[8+1];  /*下一还款日期*/
		/*下一还款日期 YYYYMMDD*/
	int   unclear_terms;  /*未结清期数*/
		/*未结清期数*/
	int   ovd_terms;  /*逾期期次数*/
		/*逾期期次数*/
	int   prin_ovd_days;  /*本金逾期天数*/
		/*本金逾期天数*/
	int   int_ovd_days;  /*利息逾期天数*/
		/*利息逾期天数*/
	double   prin_bal;  /*正常本金余额*/
		/*正常本金余额*/
	double   ovd_prin_bal;  /*逾期本金余额*/
		/*逾期本金余额*/
	double   int_bal;  /*正常利息余额*/
		/*正常利息余额*/
	double   ovd_int_bal;  /*逾期利息余额*/
		/*逾期利息余额*/
	double   ovd_prin_pnlt_bal;  /*逾期本金罚息余额*/
		/*逾期本金罚息余额*/
	double   ovd_int_pnlt_bal;  /*逾期利息罚息余额*/
		/*逾期利息罚息余额*/
	char   is_check_flag[1+1];  /*参与对账标识*/
		/*参与对账标识*/
	char   extend_param1[100+1];  /*扩展1*/
		/*扩展1*/
	char   extend_param2[250+1];  /*扩展2*/
		/*扩展2*/
	char   extend_param3[40+1];  /*扩展3*/
		/*扩展3*/

}ICPS_JB_LOAN_INIT;

#define SD_DATA  ICPS_JB_LOAN_INIT
#define SD_MEMBERS \ 
	APP_DEFSDMEMBER(T_STRING,  busi_date, 0),\
	APP_DEFSDMEMBER(T_LONG,  file_order, 0),\
	APP_DEFSDMEMBER(T_STRING,  contract_no, 0),\
	APP_DEFSDMEMBER(T_STRING,  settle_date, 0),\
	APP_DEFSDMEMBER(T_STRING,  status, 0),\
	APP_DEFSDMEMBER(T_STRING,  clear_date, 0),\
	APP_DEFSDMEMBER(T_STRING,  asset_class, 0),\
	APP_DEFSDMEMBER(T_STRING,  accrued_status, 0),\
	APP_DEFSDMEMBER(T_STRING,  next_repay_date, 0),\
	APP_DEFSDMEMBER(T_LONG,  unclear_terms, 0),\
	APP_DEFSDMEMBER(T_LONG,  ovd_terms, 0),\
	APP_DEFSDMEMBER(T_LONG,  prin_ovd_days, 0),\
	APP_DEFSDMEMBER(T_LONG,  int_ovd_days, 0),\
	APP_DEFSDMEMBER(T_DOUBLE,  prin_bal, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  ovd_prin_bal, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  int_bal, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  ovd_int_bal, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  ovd_prin_pnlt_bal, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  ovd_int_pnlt_bal, 2),\
	APP_DEFSDMEMBER(T_STRING,  is_check_flag, 0),\
	APP_DEFSDMEMBER(T_STRING,  extend_param1, 0),\
	APP_DEFSDMEMBER(T_STRING,  extend_param2, 0),\
	APP_DEFSDMEMBER(T_STRING,  extend_param3, 0)


	APP_DECLAREFIELDS(SD_ICPS_JB_LOAN_INIT)
#undef SD_DATA
#undef SD_MEMBERS

#endif  /*end of __ICPS_JB_LOAN_INIT_H__*/
