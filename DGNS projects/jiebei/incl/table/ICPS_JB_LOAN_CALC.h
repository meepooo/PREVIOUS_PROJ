/***********************************************************************
版权所有:恒生电子股份有限公司
项目名称:综合技术平台(Turandot)项目
版    本:V1.00
操作系统:
数 据 库:INFORMIX
文 件 名:ICPS_JB_LOAN_CALC.h
文件描述:结构定义数据库开发嵌C头文件
项 目 组:
程 序 员:[wangzh14925]
发布时间:2009-4-29 19:40:39 [Gen]
修    订:
修改时间:
************************************************************************
表    名:ICPS_JB_LOAN_CALC (F_JB11.利息计提明细文件)
说    明:
************************************************************************
修改记录:
修改日期:
修改内容:
修 改 人:
修改内容:
************************************************************************/
#ifndef __ICPS_JB_LOAN_CALC_H__
#define __ICPS_JB_LOAN_CALC_H__
typedef struct TDB_ICPS_JB_LOAN_CALC
{
	char   busi_date[8+1];  /*业务日期*/
		/*业务日期*/
	int   file_order;  /*文件序号*/
		/*文件序号*/
	char   contract_no[64+1];  /*借呗平台贷款合同号*/
		/*借呗平台贷款合同号*/
	char   calc_date[8+1];  /*计息日期*/
		/*计息日期 YYYYMMDD*/
	char   accrued_status[2+1];  /*应计非应计标识*/
		/*应计非应计标识 应计0，非应计1*/
	double   prin_bal;  /*正常本金余额*/
		/*正常本金余额*/
	double   ovd_prin_bal;  /*逾期本金余额*/
		/*逾期本金余额*/
	double   ovd_int_bal;  /*逾期利息余额*/
		/*逾期利息余额*/
	double   real_rate;  /*贷款实际日利率*/
		/*贷款实际日利率*/
	double   pnlt_rate;  /*贷款罚息日利率*/
		/*贷款罚息日利率*/
	double   int_amt;  /*正常利息*/
		/*正常利息*/
	double   ovd_prin_pnlt_amt;  /*逾期本金罚息*/
		/*逾期本金罚息*/
	double   ovd_int_pnlt_amt;  /*逾期利息罚息*/
		/*逾期利息罚息*/
	char   is_check_flag[1+1];  /*参与对账标识*/
		/*参与对账标识*/
	char   extend_param1[100+1];  /*扩展1*/
		/*扩展1*/
	char   extend_param2[250+1];  /*扩展2*/
		/*扩展2*/
	char   extend_param3[40+1];  /*扩展3*/
		/*扩展3*/

}ICPS_JB_LOAN_CALC;

#define SD_DATA  ICPS_JB_LOAN_CALC
#define SD_MEMBERS \
	APP_DEFSDMEMBER(T_STRING,  busi_date, 0),\
	APP_DEFSDMEMBER(T_LONG,  file_order, 0),\
	APP_DEFSDMEMBER(T_STRING,  contract_no, 0),\
	APP_DEFSDMEMBER(T_STRING,  calc_date, 0),\
	APP_DEFSDMEMBER(T_STRING,  accrued_status, 0),\
	APP_DEFSDMEMBER(T_DOUBLE,  prin_bal, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  ovd_prin_bal, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  ovd_int_bal, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  real_rate, 6),\
	APP_DEFSDMEMBER(T_DOUBLE,  pnlt_rate, 6),\
	APP_DEFSDMEMBER(T_DOUBLE,  int_amt, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  ovd_prin_pnlt_amt, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  ovd_int_pnlt_amt, 2),\
	APP_DEFSDMEMBER(T_STRING,  is_check_flag, 0),\
	APP_DEFSDMEMBER(T_STRING,  extend_param1, 0),\
	APP_DEFSDMEMBER(T_STRING,  extend_param2, 0),\
	APP_DEFSDMEMBER(T_STRING,  extend_param3, 0)


	APP_DECLAREFIELDS(SD_ICPS_JB_LOAN_CALC)
#undef SD_DATA
#undef SD_MEMBERS

#endif  /*end of __ICPS_JB_LOAN_CALC_H__*/
