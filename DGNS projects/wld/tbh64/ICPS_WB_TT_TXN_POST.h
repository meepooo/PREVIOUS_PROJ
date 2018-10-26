/***********************************************************************
版权所有:恒生电子股份有限公司
项目名称:综合技术平台(Turandot)项目
版    本:V1.00
操作系统:
数 据 库:INFORMIX
文 件 名:ICPS_WB_TT_TXN_POST.h
文件描述:结构定义数据库开发嵌C头文件
项 目 组:
程 序 员:[wangzh14925]
发布时间:2009-4-29 19:40:39 [Gen]
修    订:
修改时间:
************************************************************************
表    名:ICPS_WB_TT_TXN_POST (F_WB9.当日入账交易表)
说    明:
************************************************************************
修改记录:
修改日期:
修改内容:
修 改 人:
修改内容:
************************************************************************/
#ifndef __ICPS_WB_TT_TXN_POST_H__
#define __ICPS_WB_TT_TXN_POST_H__
typedef struct TDB_ICPS_WB_TT_TXN_POST
{
	char   busi_date[8+1];  /*业务日期*/
		/*业务日期*/
	int   file_order;  /*文件序号*/
		/*文件序号*/
	char   org[12+1];  /*机构号*/
		/*机构号*/
	char   trans_serial[20+1];  /*交易流水号*/
		/*交易流水号*/
	char   acct_no[20+1];  /*账户编号*/
		/*账户编号*/
	char   acct_type[1+1];  /*账户类型*/
		/*账户类型*/
	char   card_no[19+1];  /*卡号*/
		/*卡号*/
	char   logical_card_no[19+1];  /*逻辑卡号*/
		/*逻辑卡号*/
	char   bsc_logiccard_no[19+1];  /*逻辑卡主卡卡号*/
		/*逻辑卡主卡卡号*/
	char   product_code[6+1];  /*产品代码*/
		/*产品代码*/
	char   trans_date[14+1];  /*交易日期*/
		/*交易日期*/
	char   trans_time[14+1];  /*交易时间*/
		/*交易时间*/
	char   post_txn_type[1+1];  /*入账交易类型*/
		/*入账交易类型*/
	char   txn_code[4+1];  /*交易码*/
		/*交易码*/
	char   loan_flag[1+1];  /*借贷标志*/
		/*借贷标志*/
	double   trans_amt;  /*交易金额*/
		/*交易金额*/
	double   post_amt;  /*入账币种金额*/
		/*入账币种金额*/
	char   transfer_in_date[14+1];  /*入账日期*/
		/*入账日期*/
	char   user_field235[6+1];  /*备用字段235*/
		/*备用字段235*/
	char   user_field236[27+1];  /*备用字段236*/
		/*备用字段236*/
	char   txn_curr_cd[3+1];  /*交易币种代码*/
		/*交易币种代码*/
	char   post_curr_cd[3+1];  /*入账币种代码*/
		/*入账币种代码*/
	char   orig_trans_date[14+1];  /*原始交易日期*/
		/*原始交易日期*/
	char   plan_nbr[6+1];  /*信用计划号*/
		/*信用计划号*/
	char   ref_nbr[23+1];  /*交易参考号*/
		/*交易参考号*/
	char   txn_desc[80+1];  /*交易描述*/
		/*交易描述*/
	char   txn_short_desc[80+1];  /*账单交易描述*/
		/*账单交易描述*/
	double   user_field237;  /*备用字段237*/
		/*备用字段237*/
	char   posting_flag[3+1];  /*入账结果标示码*/
		/*入账结果标示码*/
	char   pre_posting_flag[3+1];  /*往日入账结果标示码*/
		/*往日入账结果标示码*/
	double   user_field238;  /*备用字段238*/
		/*备用字段238*/
	double   orig_pmt_amt;  /*还款交易原始金额*/
		/*还款交易原始金额*/
	char   user_field239[9+1];  /*备用字段239*/
		/*备用字段239*/
	char   user_field240[8+1];  /*备用字段240*/
		/*备用字段240*/
	char   user_field241[15+1];  /*备用字段241*/
		/*备用字段241*/
	char   user_field242[15+1];  /*备用字段242*/
		/*备用字段242*/
	char   mcc[4+1];  /*商户类别代码*/
		/*商户类别代码*/
	char   input_txn_code[4+1];  /*原交易交易码*/
		/*原交易交易码*/
	double   input_txn_amt;  /*原交易交易金额*/
		/*原交易交易金额*/
	double   input_sett_amt;  /*原交易清算金额*/
		/*原交易清算金额*/
	double   user_field246;  /*备用字段246*/
		/*备用字段246*/
	char   stmt_date[14+1];  /*下一到期还款日*/
		/*下一到期还款日*/
	char   user_field247[7+1];  /*备用字段247*/
		/*备用字段247*/
	int   jpa_version;  /*乐观锁版本号*/
		/*乐观锁版本号*/
	int   term;  /*所在贷款期数*/
		/*所在贷款期数*/
	char   busi_serial[32+1];  /*业务流水号*/
		/*业务流水号*/
	char   sys_trans_id[32+1];  /*系统调用流水号*/
		/*系统调用流水号*/
	char   user_field248[15+1];  /*备用字段248*/
		/*备用字段248*/
	char   sub_terminal_type[15+1];  /*终端类型*/
		/*终端类型*/
	char   last_modified_datetime[14+1];  /*修改时间*/
		/*修改时间 */
	char   paid_stmt_date[14+1];  /*还款对应出单日（没用）*/
		/*还款对应出单日（没用）*/
	double   repay_amt;  /*应还款额*/
		/*应还款额*/
	double   bank_proportion;  /*银行出资比例*/
		/*银行出资比例*/
	char   is_check_flag[1+1];  /*参与对账标识*/
		/*参与对账标识*/
	char   extend_param1[100+1];  /*扩展1*/
		/*扩展1*/
	char   extend_param2[250+1];  /*扩展2*/
		/*扩展2*/
	char   extend_param3[40+1];  /*扩展3*/
		/*扩展3*/

}ICPS_WB_TT_TXN_POST;

#define SD_DATA  ICPS_WB_TT_TXN_POST
#define SD_MEMBERS \ 
	APP_DEFSDMEMBER(T_STRING,  busi_date, 0),\
	APP_DEFSDMEMBER(T_LONG,  file_order, 0),\
	APP_DEFSDMEMBER(T_STRING,  org, 0),\
	APP_DEFSDMEMBER(T_STRING,  trans_serial, 0),\
	APP_DEFSDMEMBER(T_STRING,  acct_no, 0),\
	APP_DEFSDMEMBER(T_STRING,  acct_type, 0),\
	APP_DEFSDMEMBER(T_STRING,  card_no, 0),\
	APP_DEFSDMEMBER(T_STRING,  logical_card_no, 0),\
	APP_DEFSDMEMBER(T_STRING,  bsc_logiccard_no, 0),\
	APP_DEFSDMEMBER(T_STRING,  product_code, 0),\
	APP_DEFSDMEMBER(T_STRING,  trans_date, 0),\
	APP_DEFSDMEMBER(T_STRING,  trans_time, 0),\
	APP_DEFSDMEMBER(T_STRING,  post_txn_type, 0),\
	APP_DEFSDMEMBER(T_STRING,  txn_code, 0),\
	APP_DEFSDMEMBER(T_STRING,  loan_flag, 0),\
	APP_DEFSDMEMBER(T_DOUBLE,  trans_amt, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  post_amt, 2),\
	APP_DEFSDMEMBER(T_STRING,  transfer_in_date, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field235, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field236, 0),\
	APP_DEFSDMEMBER(T_STRING,  txn_curr_cd, 0),\
	APP_DEFSDMEMBER(T_STRING,  post_curr_cd, 0),\
	APP_DEFSDMEMBER(T_STRING,  orig_trans_date, 0),\
	APP_DEFSDMEMBER(T_STRING,  plan_nbr, 0),\
	APP_DEFSDMEMBER(T_STRING,  ref_nbr, 0),\
	APP_DEFSDMEMBER(T_STRING,  txn_desc, 0),\
	APP_DEFSDMEMBER(T_STRING,  txn_short_desc, 0),\
	APP_DEFSDMEMBER(T_DOUBLE,  user_field237, 4),\
	APP_DEFSDMEMBER(T_STRING,  posting_flag, 0),\
	APP_DEFSDMEMBER(T_STRING,  pre_posting_flag, 0),\
	APP_DEFSDMEMBER(T_DOUBLE,  user_field238, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  orig_pmt_amt, 2),\
	APP_DEFSDMEMBER(T_STRING,  user_field239, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field240, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field241, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field242, 0),\
	APP_DEFSDMEMBER(T_STRING,  mcc, 0),\
	APP_DEFSDMEMBER(T_STRING,  input_txn_code, 0),\
	APP_DEFSDMEMBER(T_DOUBLE,  input_txn_amt, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  input_sett_amt, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  user_field246, 2),\
	APP_DEFSDMEMBER(T_STRING,  stmt_date, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field247, 0),\
	APP_DEFSDMEMBER(T_LONG,  jpa_version, 0),\
	APP_DEFSDMEMBER(T_LONG,  term, 0),\
	APP_DEFSDMEMBER(T_STRING,  busi_serial, 0),\
	APP_DEFSDMEMBER(T_STRING,  sys_trans_id, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field248, 0),\
	APP_DEFSDMEMBER(T_STRING,  sub_terminal_type, 0),\
	APP_DEFSDMEMBER(T_STRING,  last_modified_datetime, 0),\
	APP_DEFSDMEMBER(T_STRING,  paid_stmt_date, 0),\
	APP_DEFSDMEMBER(T_DOUBLE,  repay_amt, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  bank_proportion, 2),\
	APP_DEFSDMEMBER(T_STRING,  is_check_flag, 0),\
	APP_DEFSDMEMBER(T_STRING,  extend_param1, 0),\
	APP_DEFSDMEMBER(T_STRING,  extend_param2, 0),\
	APP_DEFSDMEMBER(T_STRING,  extend_param3, 0)


	APP_DECLAREFIELDS(SD_ICPS_WB_TT_TXN_POST)
#undef SD_DATA
#undef SD_MEMBERS

#endif  /*end of __ICPS_WB_TT_TXN_POST_H__*/
