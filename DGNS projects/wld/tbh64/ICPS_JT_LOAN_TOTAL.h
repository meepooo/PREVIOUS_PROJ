/***********************************************************************
版权所有:恒生电子股份有限公司
项目名称:综合技术平台(Turandot)项目
版    本:V1.00
操作系统:
数 据 库:INFORMIX
文 件 名:ICPS_JT_LOAN_TOTAL.h
文件描述:结构定义数据库开发嵌C头文件
项 目 组:
程 序 员:[wangzh14925]
发布时间:2009-4-29 19:40:39 [Gen]
修    订:
修改时间:
************************************************************************
表    名:ICPS_JT_LOAN_TOTAL (F_JT1.汇总记账表)
说    明:
************************************************************************
修改记录:
修改日期:
修改内容:
修 改 人:
修改内容:
************************************************************************/
#ifndef __ICPS_JT_LOAN_TOTAL_H__
#define __ICPS_JT_LOAN_TOTAL_H__
typedef struct TDB_ICPS_JT_LOAN_TOTAL
{
	char   busi_date[8+1];  /*业务日期*/
		/*业务日期*/
	double   encash_amt;  /*短期贷款放款资金*/
		/*短期贷款放款资金*/
	double   prin_to_ovd_prin_amt;  /*短期贷款正常本金转逾期本金（应计）*/
		/*短期贷款正常本金转逾期本金（应计）*/
	double   non_prin_to_ovd_prin_amt;  /*短期贷款正常本金转逾期本金（非应计）*/
		/*短期贷款正常本金转逾期本金（非应计）*/
	double   accrued_to_non_ovd_prin_amt;  /*短期贷款逾期本金（应计）转逾期本金（非应计）*/
		/*短期贷款逾期本金（应计）转逾期本金（非应计）*/
	double   in_int_to_ovd_int_amt;  /*短期贷款正常利息转逾期利息（表内）*/
		/*短期贷款正常利息转逾期利息（表内）*/
	double   out_int_to_ovd_int_amt;  /*短期贷款正常利息转逾期利息（表外）*/
		/*短期贷款正常利息转逾期利息（表外）*/
	double   in_to_out_ovd_int_amt;  /*短期贷款逾期利息（表内）转逾期利息（表外）*/
		/*短期贷款逾期利息（表内）转逾期利息（表外）*/
	double   in_to_out_pnlt_int_amt;  /*短期贷款罚息（表内）转罚息（表外）*/
		/*短期贷款罚息（表内）转罚息（表外）*/
	double   in_refund_ovd_int_amt;  /*短期退货还款冲销的逾期利息（表内）*/
		/*短期退货还款冲销的逾期利息（表内）*/
	double   paid_prin_amt;  /*实还短期正常贷款本金*/
		/*实还短期正常贷款本金*/
	double   paid_accrued_ovd_prin_amt;  /*实还短期逾期贷款本金（应计）*/
		/*实还短期逾期贷款本金（应计）*/
	double   paid_non_accrued_ovd_prin_amt;  /*实还短期逾期贷款本金（非应计）*/
		/*实还短期逾期贷款本金（非应计）*/
	double   paid_int_amt;  /*实还短期正常贷款利息*/
		/*实还短期正常贷款利息*/
	double   paid_in_ovd_int_amt;  /*实还短期逾期贷款利息（表内）*/
		/*实还短期逾期贷款利息（表内）*/
	double   paid_out_ovd_int_amt;  /*实还短期逾期贷款利息（表外）*/
		/*实还短期逾期贷款利息（表外）*/
	double   paid_in_pnlt_int_amt;  /*实还短期贷款罚息（表内）*/
		/*实还短期贷款罚息（表内）*/
	double   paid_out_pnlt_int_amt;  /*实还短期贷款罚息（表外）*/
		/*实还短期贷款罚息（表外）*/
	double   ahead_prin_amt;  /*提前归还短期贷款正常本金*/
		/*提前归还短期贷款正常本金*/
	double   ahead_int_amt;  /*提前归还短期贷款正常利息*/
		/*提前归还短期贷款正常利息*/
	double   refund_prin_amt;  /*退货短期贷款本金*/
		/*退货短期贷款本金*/
	double   refund_ovd_prin_amt;  /*退货短期贷款逾期本金（应计）*/
		/*退货短期贷款逾期本金（应计）*/
	double   refund_in_pnlt_int;  /*退货短期贷款罚息（表内）*/
		/*退货短期贷款罚息（表内）*/
	double   encash_amt2;  /*中长期贷款放款资金*/
		/*中长期贷款放款资金*/
	double   prin_to_ovd_prin_amt2;  /*中长期贷款正常本金转逾期本金（应计）*/
		/*中长期贷款正常本金转逾期本金（应计）*/
	double   non_prin_to_ovd_prin_amt2;  /*中长期贷款正常本金转逾期本金（非应计）*/
		/*中长期贷款正常本金转逾期本金（非应计）*/
	double   accrued_to_non_ovd_prin_amt2;  /*中长期贷款逾期本金（应计）转逾期本金（非应计）*/
		/*中长期贷款逾期本金（应计）转逾期本金（非应计）*/
	double   in_int_to_ovd_int_amt2;  /*中长期贷款正常利息转逾期利息（表内）*/
		/*中长期贷款正常利息转逾期利息（表内）*/
	double   out_int_to_ovd_int_amt2;  /*中长期贷款正常利息转逾期利息（表外）*/
		/*中长期贷款正常利息转逾期利息（表外）*/
	double   in_to_out_ovd_int_amt2;  /*中长期贷款逾期利息（表内）转逾期利息（表外）*/
		/*中长期贷款逾期利息（表内）转逾期利息（表外）*/
	double   in_to_out_pnlt_int_amt2;  /*中长期贷款罚息（表内）转罚息（表外）*/
		/*中长期贷款罚息（表内）转罚息（表外）*/
	double   in_refund_ovd_int_amt2;  /*中长期退货还款冲销的逾期利息（表内）*/
		/*中长期退货还款冲销的逾期利息（表内）*/
	double   paid_prin_amt2;  /*实还中长期正常贷款本金*/
		/*实还中长期正常贷款本金*/
	double   paid_accrued_ovd_prin_amt2;  /*实还中长期逾期贷款本金（应计）*/
		/*实还中长期逾期贷款本金（应计）*/
	double   paid_non_accrued_ovd_prin_amt2;  /*实还中长期逾期贷款本金（非应计）*/
		/*实还中长期逾期贷款本金（非应计）*/
	double   paid_int_amt2;  /*实还中长期正常贷款利息*/
		/*实还中长期正常贷款利息*/
	double   paid_in_ovd_int_amt2;  /*实还中长期逾期贷款利息（表内）*/
		/*实还中长期逾期贷款利息（表内）*/
	double   paid_out_ovd_int_amt2;  /*实还中长期逾期贷款利息（表外）*/
		/*实还中长期逾期贷款利息（表外）*/
	double   paid_in_pnlt_int_amt2;  /*实还中长期贷款罚息（表内）*/
		/*实还中长期贷款罚息（表内）*/
	double   paid_out_pnlt_int_amt2;  /*实还中长期贷款罚息（表外）*/
		/*实还中长期贷款罚息（表外）*/
	double   ahead_prin_amt2;  /*提前归还中长期贷款正常本金*/
		/*提前归还中长期贷款正常本金*/
	double   ahead_int_amt2;  /*提前归还中长期贷款正常利息*/
		/*提前归还中长期贷款正常利息*/
	double   refund_prin_amt2;  /*退货中长期贷款本金*/
		/*退货中长期贷款本金*/
	double   refund_ovd_prin_amt2;  /*退货中长期贷款逾期本金（应计）*/
		/*退货中长期贷款逾期本金（应计）*/
	double   refund_in_pnlt_int_amt2;  /*退货中长期贷款罚息（表内）*/
		/*退货中长期贷款罚息（表内）*/
	char   extend_param1[100+1];  /*扩展1*/
		/*扩展1*/
	char   extend_param2[250+1];  /*扩展2*/
		/*扩展2*/
	char   extend_param3[40+1];  /*扩展3*/
		/*扩展3*/

}ICPS_JT_LOAN_TOTAL;

#define SD_DATA  ICPS_JT_LOAN_TOTAL
#define SD_MEMBERS \ 
	APP_DEFSDMEMBER(T_STRING,  busi_date, 0),\
	APP_DEFSDMEMBER(T_DOUBLE,  encash_amt, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  prin_to_ovd_prin_amt, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  non_prin_to_ovd_prin_amt, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  accrued_to_non_ovd_prin_amt, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  in_int_to_ovd_int_amt, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  out_int_to_ovd_int_amt, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  in_to_out_ovd_int_amt, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  in_to_out_pnlt_int_amt, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  in_refund_ovd_int_amt, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  paid_prin_amt, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  paid_accrued_ovd_prin_amt, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  paid_non_accrued_ovd_prin_amt, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  paid_int_amt, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  paid_in_ovd_int_amt, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  paid_out_ovd_int_amt, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  paid_in_pnlt_int_amt, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  paid_out_pnlt_int_amt, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  ahead_prin_amt, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  ahead_int_amt, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  refund_prin_amt, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  refund_ovd_prin_amt, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  refund_in_pnlt_int, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  encash_amt2, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  prin_to_ovd_prin_amt2, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  non_prin_to_ovd_prin_amt2, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  accrued_to_non_ovd_prin_amt2, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  in_int_to_ovd_int_amt2, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  out_int_to_ovd_int_amt2, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  in_to_out_ovd_int_amt2, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  in_to_out_pnlt_int_amt2, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  in_refund_ovd_int_amt2, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  paid_prin_amt2, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  paid_accrued_ovd_prin_amt2, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  paid_non_accrued_ovd_prin_amt2, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  paid_int_amt2, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  paid_in_ovd_int_amt2, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  paid_out_ovd_int_amt2, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  paid_in_pnlt_int_amt2, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  paid_out_pnlt_int_amt2, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  ahead_prin_amt2, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  ahead_int_amt2, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  refund_prin_amt2, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  refund_ovd_prin_amt2, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  refund_in_pnlt_int_amt2, 2),\
	APP_DEFSDMEMBER(T_STRING,  extend_param1, 0),\
	APP_DEFSDMEMBER(T_STRING,  extend_param2, 0),\
	APP_DEFSDMEMBER(T_STRING,  extend_param3, 0)


	APP_DECLAREFIELDS(SD_ICPS_JT_LOAN_TOTAL)
#undef SD_DATA
#undef SD_MEMBERS

#endif  /*end of __ICPS_JT_LOAN_TOTAL_H__*/
