/***********************************************************************
版权所有:恒生电子股份有限公司
项目名称:综合技术平台(Turandot)项目
版    本:V1.00
操作系统:
数 据 库:INFORMIX
文 件 名:ICPS_JB_XPT_INSTMNT_DETAIL.h
文件描述:结构定义数据库开发嵌C头文件
项 目 组:
程 序 员:[wangzh14925]
发布时间:2009-4-29 19:40:39 [Gen]
修    订:
修改时间:
************************************************************************
表    名:ICPS_JB_XPT_INSTMNT_DETAIL (F_JB8.减免（分期）明细文件)
说    明:
************************************************************************
修改记录:
修改日期:
修改内容:
修 改 人:
修改内容:
************************************************************************/
#ifndef __ICPS_JB_XPT_INSTMNT_DETAIL_H__
#define __ICPS_JB_XPT_INSTMNT_DETAIL_H__
typedef struct TDB_ICPS_JB_XPT_INSTMNT_DETAIL
{
	char   busi_date[8+1];  /*业务日期*/
		/*业务日期*/
	int   file_order;  /*文件序号*/
		/*文件序号*/
	char   contract_no[32+1];  /*借呗平台贷款合同号*/
		/*借呗平台贷款合同号*/
	char   xpt_seq_no[64+1];  /*减免流水号*/
		/*减免流水号*/
	int   term_no;  /*期次号*/
		/*期次号*/
	char   settle_date[8+1];  /*减免会计日期*/
		/*减免会计日期 YYYYMMDD*/
	double   curr_int_bal;  /*本次还款前的应收未收利息*/
		/*本次还款前的应收未收利息*/
	double   curr_ovd_prin_pnlt_bal;  /*本次还款前的应收未收逾期本金罚息*/
		/*本次还款前的应收未收逾期本金罚息*/
	double   curr_ovd_int_pnlt_bal;  /*本次还款前的应收未收逾期利息罚息*/
		/*本次还款前的应收未收逾期利息罚息*/
	double   xpt_amt;  /*本次减免总金额*/
		/*本次减免总金额*/
	double   xpt_int_amt;  /*本次减免利息金额*/
		/*本次减免利息金额*/
	double   xpt_ovd_prin_pnlt_amt;  /*本次减免逾期本金罚息金额*/
		/*本次减免逾期本金罚息金额*/
	double   xpt_ovd_int_pnlt_amt;  /*本次减免逾期利息罚息金额*/
		/*本次减免逾期利息罚息金额*/
	char   is_check_flag[1+1];  /*参与对账标识*/
		/*参与对账标识*/
	char   extend_param1[100+1];  /*扩展1*/
		/*扩展1*/
	char   extend_param2[250+1];  /*扩展2*/
		/*扩展2*/
	char   extend_param3[40+1];  /*扩展3*/
		/*扩展3*/

}ICPS_JB_XPT_INSTMNT_DETAIL;

#define SD_DATA  ICPS_JB_XPT_INSTMNT_DETAIL
#define SD_MEMBERS \ 
	APP_DEFSDMEMBER(T_STRING,  busi_date, 0),\
	APP_DEFSDMEMBER(T_LONG,  file_order, 0),\
	APP_DEFSDMEMBER(T_STRING,  contract_no, 0),\
	APP_DEFSDMEMBER(T_STRING,  xpt_seq_no, 0),\
	APP_DEFSDMEMBER(T_LONG,  term_no, 0),\
	APP_DEFSDMEMBER(T_STRING,  settle_date, 0),\
	APP_DEFSDMEMBER(T_DOUBLE,  curr_int_bal, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  curr_ovd_prin_pnlt_bal, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  curr_ovd_int_pnlt_bal, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  xpt_amt, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  xpt_int_amt, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  xpt_ovd_prin_pnlt_amt, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  xpt_ovd_int_pnlt_amt, 2),\
	APP_DEFSDMEMBER(T_STRING,  is_check_flag, 0),\
	APP_DEFSDMEMBER(T_STRING,  extend_param1, 0),\
	APP_DEFSDMEMBER(T_STRING,  extend_param2, 0),\
	APP_DEFSDMEMBER(T_STRING,  extend_param3, 0)


	APP_DECLAREFIELDS(SD_ICPS_JB_XPT_INSTMNT_DETAIL)
#undef SD_DATA
#undef SD_MEMBERS

#endif  /*end of __ICPS_JB_XPT_INSTMNT_DETAIL_H__*/
