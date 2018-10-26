/***********************************************************************
版权所有:恒生电子股份有限公司
项目名称:综合技术平台(Turandot)项目
版    本:V1.00
操作系统:
数 据 库:INFORMIX
文 件 名:ICPS_JB_TOTAL.h
文件描述:结构定义数据库开发嵌C头文件
项 目 组:
程 序 员:[wangzh14925]
发布时间:2009-4-29 19:40:39 [Gen]
修    订:
修改时间:
************************************************************************
表    名:ICPS_JB_TOTAL (F_JB1.汇总记账文件表)
说    明:
************************************************************************
修改记录:
修改日期:
修改内容:
修 改 人:
修改内容:
************************************************************************/
#ifndef __ICPS_JB_TOTAL_H__
#define __ICPS_JB_TOTAL_H__
typedef struct TDB_ICPS_JB_TOTAL
{
	char   busi_date[8+1];  /*业务日期*/
		/*业务日期*/
	double   encash_amt;  /*当天贷款发放金额*/
		/*当天贷款发放金额*/
	double   withhold_amt;  /*当天网商备付金代扣金额*/
		/*当天网商备付金代扣金额*/
	double   refund_amt;  /*当天退回网商备付金金额*/
		/*当天退回网商备付金金额*/
	double   accrued_int_amt;  /*短期正常/逾期90天以内（含）贷款计提每日利息*/
		/*短期正常/逾期90天以内（含）贷款计提每日利息*/
	double   non_accrued_int_amt;  /*短期逾期90天以上贷款计提每日利息*/
		/*短期逾期90天以上贷款计提每日利息*/
	double   accrued_ovd_prin_pnlt_amt;  /*短期逾期90天以内（含）贷款计提每日逾期本金罚息*/
		/*短期逾期90天以内（含）贷款计提每日逾期本金罚息*/
	double   non_accrued_ovd_prin_pnlt_amt;  /*短期逾期90天以上贷款计提每日逾期本金罚息*/
		/*短期逾期90天以上贷款计提每日逾期本金罚息*/
	double   accrued_ovd_int_pnlt_amt;  /*短期逾期90天以内（含）贷款计提每日逾期利息罚息*/
		/*短期逾期90天以内（含）贷款计提每日逾期利息罚息*/
	double   non_accrued_ovd_int_pnlt_amt;  /*短期逾期90天以上贷款计提每日逾期利息罚息*/
		/*短期逾期90天以上贷款计提每日逾期利息罚息*/
	double   prin_to_ovd_prin_amt;  /*正常本金转逾期本金*/
		/*正常本金转逾期本金*/
	double   int_to_ovd_int_amt;  /*正常利息转逾期利息*/
		/*正常利息转逾期利息*/
	double   accrued_to_non_prin_amt;  /*正常本金（应计）转正常本金（非应计）*/
		/*正常本金（应计）转正常本金（非应计）*/
	double   accrued_to_non_ovd_prin_amt;  /*逾期本金（应计）转逾期本金（非应计）*/
		/*逾期本金（应计）转逾期本金（非应计）*/
	double   in_to_out_int_amt;  /*正常利息（表内）转正常利息（表外）*/
		/*正常利息（表内）转正常利息（表外）*/
	double   in_to_out_ovd_int_amt;  /*逾期利息（表内）转逾期利息（表外）*/
		/*逾期利息（表内）转逾期利息（表外）*/
	double   in_to_out_ovd_prin_pnlt_amt;  /*逾期本金罚息（表内）转逾期本金罚息（表外）*/
		/*逾期本金罚息（表内）转逾期本金罚息（表外）*/
	double   in_to_out_ovd_int_pnlt_amt;  /*逾期利息罚息（表内）转逾期利息罚息（表外）*/
		/*逾期利息罚息（表内）转逾期利息罚息（表外）*/
	double   non_to_accrued_prin_amt;  /*正常本金（非应计）转正常本金（应计）*/
		/*正常本金（非应计）转正常本金（应计）*/
	double   non_to_accrued_ovd_prin_amt;  /*逾期本金（非应计）转逾期本金（应计）*/
		/*逾期本金（非应计）转逾期本金（应计）*/
	double   out_to_in_int_amt;  /*正常利息（表外）转正常利息（表内）*/
		/*正常利息（表外）转正常利息（表内）*/
	double   out_to_in_ovd_int_amt;  /*逾期利息（表外）转逾期利息（表内）*/
		/*逾期利息（表外）转逾期利息（表内）*/
	double   out_to_in_ovd_prin_pnlt_amt;  /*逾期本金罚息（表外）转逾本金罚息（表内）*/
		/*逾期本金罚息（表外）转逾本金罚息（表内）*/
	double   out_to_in_ovd_int_pnlt_amt;  /*逾期利息罚息（表外）转逾期利息罚息（表内）*/
		/*逾期利息罚息（表外）转逾期利息罚息（表内）*/
	double   paid_prin_amt;  /*实还正常本金（应计）*/
		/*实还正常本金（应计）*/
	double   paid_non_accrued_prin_amt;  /*实还正常本金（非应计）*/
		/*实还正常本金（非应计）*/
	double   paid_accrued_ovd_prin_amt;  /*实还逾期本金（应计）*/
		/*实还逾期本金（应计）*/
	double   paid_non_accrued_ovd_prin_amt;  /*实还逾期本金（非应计）*/
		/*实还逾期本金（非应计）*/
	double   paid_int_amt;  /*实还正常利息（表内）*/
		/*实还正常利息（表内）*/
	double   paid_out_int_amt;  /*实还正常利息（表外）*/
		/*实还正常利息（表外）*/
	double   paid_in_ovd_int_amt;  /*实还逾期利息（表内）*/
		/*实还逾期利息（表内）*/
	double   paid_out_ovd_int_amt;  /*实还逾期利息（表外）*/
		/*实还逾期利息（表外）*/
	double   paid_in_ovd_prin_pnlt_int_amt;  /*实还逾期本金罚息（表内）*/
		/*实还逾期本金罚息（表内）*/
	double   paid_out_ovd_prin_pnlt_int_amt;  /*实还逾期本金罚息（表外）*/
		/*实还逾期本金罚息（表外）*/
	double   paid_in_ovd_int_pnlt_int_amt;  /*实还逾期利息罚息（表内）*/
		/*实还逾期利息罚息（表内）*/
	double   paid_out_ovd_int_pnlt_int_amt;  /*实还逾期利息罚息（表外）*/
		/*实还逾期利息罚息（表外）*/
	double   xpt_in_int_amt;  /*减免正常利息（表内）*/
		/*减免正常利息（表内）*/
	double   xpt_out_int_amt;  /*减免正常利息（表外）*/
		/*减免正常利息（表外）*/
	double   xpt_in_ovd_int_amt;  /*减免逾期利息（表内）*/
		/*减免逾期利息（表内）*/
	double   xpt_out_ovd_int_amt;  /*减免逾期利息（表外）*/
		/*减免逾期利息（表外）*/
	double   xpt_in_ovd_prin_pnlt_int_amt;  /*减免逾期本金罚息（表内）*/
		/*减免逾期本金罚息（表内）*/
	double   xpt_out_ovd_prin_pnlt_int_amt;  /*减免逾期本金罚息（表外）*/
		/*减免逾期本金罚息（表外）*/
	double   xpt_in_ovd_int_pnlt_int_amt;  /*减免逾期利息罚息（表内）*/
		/*减免逾期利息罚息（表内）*/
	double   xpt_out_ovd_int_pnlt_int_amt;  /*减免逾期利息罚息（表外）*/
		/*减免逾期利息罚息（表外）*/
	double fee_amt;    /*平台服务费汇总金额*/
		/*平台服务费汇总金额*/
	char   extend_param1[100+1];  /*扩展1*/
		/*扩展1*/
	char   extend_param2[250+1];  /*扩展2*/
		/*扩展2*/
	char   extend_param3[40+1];  /*扩展3*/
		/*扩展3*/

}ICPS_JB_TOTAL;

#define SD_DATA  ICPS_JB_TOTAL
#define SD_MEMBERS \
	APP_DEFSDMEMBER(T_STRING,  busi_date, 0),\
	APP_DEFSDMEMBER(T_DOUBLE,  encash_amt, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  withhold_amt, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  refund_amt, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  accrued_int_amt, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  non_accrued_int_amt, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  accrued_ovd_prin_pnlt_amt, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  non_accrued_ovd_prin_pnlt_amt, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  accrued_ovd_int_pnlt_amt, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  non_accrued_ovd_int_pnlt_amt, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  prin_to_ovd_prin_amt, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  int_to_ovd_int_amt, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  accrued_to_non_prin_amt, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  accrued_to_non_ovd_prin_amt, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  in_to_out_int_amt, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  in_to_out_ovd_int_amt, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  in_to_out_ovd_prin_pnlt_amt, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  in_to_out_ovd_int_pnlt_amt, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  non_to_accrued_prin_amt, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  non_to_accrued_ovd_prin_amt, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  out_to_in_int_amt, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  out_to_in_ovd_int_amt, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  out_to_in_ovd_prin_pnlt_amt, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  out_to_in_ovd_int_pnlt_amt, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  paid_prin_amt, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  paid_non_accrued_prin_amt, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  paid_accrued_ovd_prin_amt, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  paid_non_accrued_ovd_prin_amt, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  paid_int_amt, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  paid_out_int_amt, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  paid_in_ovd_int_amt, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  paid_out_ovd_int_amt, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  paid_in_ovd_prin_pnlt_int_amt, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  paid_out_ovd_prin_pnlt_int_amt, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  paid_in_ovd_int_pnlt_int_amt, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  paid_out_ovd_int_pnlt_int_amt, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  xpt_in_int_amt, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  xpt_out_int_amt, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  xpt_in_ovd_int_amt, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  xpt_out_ovd_int_amt, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  xpt_in_ovd_prin_pnlt_int_amt, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  xpt_out_ovd_prin_pnlt_int_amt, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  xpt_in_ovd_int_pnlt_int_amt, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  xpt_out_ovd_int_pnlt_int_amt, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  fee_amt,2),\
	APP_DEFSDMEMBER(T_STRING,  extend_param1, 0),\
	APP_DEFSDMEMBER(T_STRING,  extend_param2, 0),\
	APP_DEFSDMEMBER(T_STRING,  extend_param3, 0)


	APP_DECLAREFIELDS(SD_ICPS_JB_TOTAL)
#undef SD_DATA
#undef SD_MEMBERS

#endif  /*end of __ICPS_JB_TOTAL_H__*/
