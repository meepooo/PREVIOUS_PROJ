/***********************************************************************
版权所有:恒生电子股份有限公司
项目名称:综合技术平台(Turandot)项目
版    本:V1.00
操作系统:
数 据 库:INFORMIX
文 件 名:ICPS_WB_TM_AUTH_HST.h
文件描述:结构定义数据库开发嵌C头文件
项 目 组:
程 序 员:[wangzh14925]
发布时间:2009-4-29 19:40:39 [Gen]
修    订:
修改时间:
************************************************************************
表    名:ICPS_WB_TM_AUTH_HST (F_WB15.授权交易历史表)
说    明:
************************************************************************
修改记录:
修改日期:
修改内容:
修 改 人:
修改内容:
************************************************************************/
#ifndef __ICPS_WB_TM_AUTH_HST_H__
#define __ICPS_WB_TM_AUTH_HST_H__
typedef struct TDB_ICPS_WB_TM_AUTH_HST
{
	char   busi_date[8+1];  /*业务日期*/
		/*业务日期*/
	int   file_order;  /*文件序号*/
		/*文件序号*/
	char   org[12+1];  /*机构号*/
		/*机构号*/
	char   log_kv[20+1];  /*LOG的键值*/
		/*LOG的键值*/
	char   acct_no[20+1];  /*账户编号*/
		/*账户编号*/
	char   acct_type[1+1];  /*账户类型*/
		/*账户类型*/
	char   logical_card_no[19+1];  /*逻辑卡号*/
		/*逻辑卡号*/
	long   acq_ref_no;  /*受理机构交易编码*/
		/*受理机构交易编码*/
	double   trans_amt;  /*交易金额*/
		/*交易金额*/
	char   txn_curr_cd[3+1];  /*交易币种代码*/
		/*交易币种代码*/
	char   user_field269[6+1];  /*备用字段269*/
		/*备用字段269*/
	char   acq_name_addr[40+1];  /*受理机构名称地址*/
		/*受理机构名称地址*/
	double   chb_txn_amt;  /*持卡人账户币种金额*/
		/*持卡人账户币种金额*/
	char   chb_curr_cd[3+1];  /*持卡人账户币种*/
		/*持卡人账户币种*/
	char   user_field270[15+1];  /*备用字段270*/
		/*备用字段270*/
	char   mcc[4+1];  /*商户类别代码*/
		/*商户类别代码*/
	char   acq_branch_id[9+1];  /*受理分行代码*/
		/*受理分行代码*/
	char   fwd_inst_id[11+1];  /*转发机构号*/
		/*转发机构号*/
	char   transmission_timestamp[10+1];  /*传送日期*/
		/*传送日期*/
	char   settle_date[4+1];  /*清算日期*/
		/*清算日期*/
	char   txn_direction[20+1];  /*交易方向*/
		/*交易方向*/
	char   txn_terminal[40+1];  /*交易终端*/
		/*交易终端*/
	char   trans_status[1+1];  /*交易状态*/
		/*交易状态*/
	char   trans_type[20+1];  /*交易类型*/
		/*交易类型*/
	char   log_ol_time[14+1];  /*LOG联机时间*/
		/*LOG联机时间*/
	char   log_biz_date[14+1];  /*联机业务日期*/
		/*联机业务日期*/
	char   mti[4+1];  /*交易类型标识*/
		/*交易类型标识*/
	char   orig_txn_type[20+1];  /*原交易类型*/
		/*原交易类型*/
	char   orig_fwd_inst_id[11+1];  /*原始转发机构号*/
		/*原始转发机构号*/
	char   orig_acq_inst_id[11+1];  /*原始受理机构号*/
		/*原始受理机构号*/
	char   orig_mti[4+1];  /*原交易MTI*/
		/*原交易MTI*/
	char   orig_trans_date[14+1];  /*原始交易日期*/
		/*原始交易日期*/
	int   orig_trace_no;  /*原始系统跟踪号*/
		/*原始系统跟踪号*/
	char   orig_txn_proc[6+1];  /*原交易处理码*/
		/*原交易处理码*/
	double   orig_txn_amt;  /*原始交易币种金额*/
		/*原始交易币种金额*/
	char   orig_log_kv[20+1];  /*原交易LOG键值*/
		/*原交易LOG键值*/
	char   orig_txn_val_1[38+1];  /*原交易键值1*/
		/*原交易键值1*/
	char   orig_txn_val_2[40+1];  /*原交易键值2*/
		/*原交易键值2*/
	double   orig_chb_txn_amt;  /*原始入账币种金额*/
		/*原始入账币种金额*/
	char   orig_biz_date[14+1];  /*原交易的联机业务处理日期*/
		/*原交易的联机业务处理日期*/
	char   last_reversal_date[14+1];  /*最后一次冲撤时间*/
		/*最后一次冲撤时间*/
	int   void_count;  /*撤销次数*/
		/*撤销次数*/
	char   manual_auth_flag[1+1];  /*人工授权标志*/
		/*人工授权标志*/
	char   opera_id[40+1];  /*操作员ID*/
		/*操作员ID*/
	char   brand[2+1];  /*品牌*/
		/*品牌*/
	char   product_code[6+1];  /*产品代码*/
		/*产品代码*/
	char   mcc_type[2+1];  /*商户类型分组*/
		/*商户类型分组*/
	char   user_field271[4+1];  /*备用字段271*/
		/*备用字段271*/
	char   user_field272[1+1];  /*备用字段272*/
		/*备用字段272*/
	double   comp_amt;  /*最终授权金额*/
		/*最终授权金额*/
	char   final_upd_direction[1+1];  /*最终更新方向*/
		/*最终更新方向*/
	double   final_upd_amt;  /*最终更新金额*/
		/*最终更新金额*/
	char   ic_ind[1+1];  /*是否IC卡*/
		/*是否IC卡*/
	char   the_3dsecure_type[1+1];  /*是否3D电子安全交易*/
		/*是否3D电子安全交易*/
	char   vip_status[1+1];  /*VIP状态*/
		/*VIP状态*/
	double   curr_balance;  /*当前余额*/
		/*当前余额*/
	double   cash_amt;  /*取现金额*/
		/*取现金额*/
	double   otb;  /*可用额度*/
		/*可用额度*/
	double   cash_otb;  /*取现可用额度*/
		/*取现可用额度*/
	double   cust_otb;  /*客户可用额度*/
		/*客户可用额度*/
	char   user_field273[20+1];  /*备用字段273*/
		/*备用字段273*/
	char   user_field274[20+1];  /*备用字段274*/
		/*备用字段274*/
	char   expire_date[4+1];  /*有效日期*/
		/*有效日期*/
	char   track_one_result[20+1];  /*一磁道完整性结果*/
		/*一磁道完整性结果*/
	char   track_two_result[20+1];  /*二磁道完整性结果*/
		/*二磁道完整性结果*/
	char   track_three_result[20+1];  /*三磁道完整性结果*/
		/*三磁道完整性结果*/
	char   pwd_type[1+1];  /*密码种类*/
		/*密码种类*/
	char   check_pwd_result[20+1];  /*验证密码结果*/
		/*验证密码结果*/
	int   pay_pwd_err_num;  /*支付密码错误次数*/
		/*支付密码错误次数*/
	char   check_cvv_result[20+1];  /*CVV验证结果*/
		/*CVV验证结果*/
	char   check_cvv2_result[20+1];  /*CVV2验证结果*/
		/*CVV2验证结果*/
	char   check_icvn_result[20+1];  /*ICVN验证结果*/
		/*ICVN验证结果*/
	char   check_arqc_result[20+1];  /*ARQC验证结果*/
		/*ARQC验证结果*/
	char   check_atc_result[20+1];  /*ATC验证结果*/
		/*ATC验证结果*/
	char   check_cvr_result[20+1];  /*CVR验证结果*/
		/*CVR验证结果*/
	char   check_tvr_result[20+1];  /*TVR验证结果*/
		/*TVR验证结果*/
	char   user_field275[40+1];  /*备用字段275*/
		/*备用字段275*/
	double   unmatch_cr;  /*未匹配贷记金额*/
		/*未匹配贷记金额*/
	double   unmatch_db;  /*未匹配借记金额*/
		/*未匹配借记金额*/
	char   b002[20+1];  /*介质卡号-B002*/
		/*介质卡号-B002*/
	char   b003[6+1];  /*交易处理码-B003*/
		/*交易处理码-B003*/
	char   b007[10+1];  /*交易传输时间-B007*/
		/*交易传输时间-B007*/
	char   b011[6+1];  /*系统跟踪号-B011*/
		/*系统跟踪号-B011*/
	char   b022[3+1];  /*服务点PIN获取码-B022*/
		/*服务点PIN获取码-B022*/
	char   b025[4+1];  /*服务点条件码-B025*/
		/*服务点条件码-B025*/
	char   b032[15+1];  /*受理机构标识码-B032*/
		/*受理机构标识码-B032*/
	char   b033[40+1];  /*受理机构名称地址-B033*/
		/*受理机构名称地址-B033*/
	char   b039[2+1];  /*返回码-B039*/
		/*返回码-B039*/
	char   b042[15+1];  /*受卡方(商户)标识码-B042*/
		/*受卡方(商户)标识码-B042*/
	char   user_field277[103+1];  /*备用字段276*/
		/*备用字段276*/
	char   user_field278[400+1];  /*备用字段277*/
		/*备用字段277*/
	char   b090[42+1];  /*原始数据元*/
		/*原始数据元*/
	char   opera_term_id[20+1];  /*操作用户终端编号*/
		/*操作用户终端编号*/
	int   jpa_version;  /*乐观锁版本号*/
		/*乐观锁版本号*/
	double   b004;  /*交易货币金额-B004*/
		/*交易货币金额-B004*/
	double   b006;  /*账户货币金额-B006*/
		/*账户货币金额-B006*/
	char   b049[3+1];  /*交易货币代码-B049*/
		/*交易货币代码-B049*/
	char   b051[3+1];  /*账户货币代码-B051*/
		/*账户货币代码-B051*/
	char   b037[23+1];  /*检索参考号-B037*/
		/*检索参考号-B037*/
	double   b028;  /*手续费-B028*/
		/*手续费-B028*/
	char   b048[999+1];  /*附加数据-B048*/
		/*附加数据-B048*/
	char   b054[60+1];  /*返回余额数组-B054*/
		/*返回余额数组-B054*/
	char   user_field279[27+1];  /*备用字段278*/
		/*备用字段278*/
	char   user_field280[27+1];  /*备用字段279*/
		/*备用字段279*/
	char   user_field281[27+1];  /*备用字段280*/
		/*备用字段280*/
	char   busi_serial[32+1];  /*业务流水号*/
		/*业务流水号*/
	char   sys_trans_id[32+1];  /*系统调用流水号*/
		/*系统调用流水号*/
	char   user_field282[15+1];  /*备用字段281*/
		/*备用字段281*/
	char   sub_terminal_type[15+1];  /*终端类型*/
		/*终端类型*/
	char   sub_merch_id[40+1];  /*二级商户编码*/
		/*二级商户编码*/
	char   sub_merch_name[60+1];  /*二级商户名称*/
		/*二级商户名称*/
	char   wares_desc[60+1];  /*商品信息*/
		/*商品信息*/
	char   last_modified_datetime[14+1];  /*修改时间*/
		/*修改时间*/
	int   part_month;  /*分区用的月份*/
		/*分区用的月份*/
	char   paid_stmt_date[14+1];  /*还款账单日*/
		/*还款账单日*/
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

}ICPS_WB_TM_AUTH_HST;

#define SD_DATA  ICPS_WB_TM_AUTH_HST
#define SD_MEMBERS \ 
	APP_DEFSDMEMBER(T_STRING,  busi_date, 0),\
	APP_DEFSDMEMBER(T_LONG,  file_order, 0),\
	APP_DEFSDMEMBER(T_STRING,  org, 0),\
	APP_DEFSDMEMBER(T_STRING,  log_kv, 0),\
	APP_DEFSDMEMBER(T_STRING,  acct_no, 0),\
	APP_DEFSDMEMBER(T_STRING,  acct_type, 0),\
	APP_DEFSDMEMBER(T_STRING,  logical_card_no, 0),\
	APP_DEFSDMEMBER(T_LONG,  acq_ref_no, 0),\
	APP_DEFSDMEMBER(T_DOUBLE,  trans_amt, 2),\
	APP_DEFSDMEMBER(T_STRING,  txn_curr_cd, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field269, 0),\
	APP_DEFSDMEMBER(T_STRING,  acq_name_addr, 0),\
	APP_DEFSDMEMBER(T_DOUBLE,  chb_txn_amt, 2),\
	APP_DEFSDMEMBER(T_STRING,  chb_curr_cd, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field270, 0),\
	APP_DEFSDMEMBER(T_STRING,  mcc, 0),\
	APP_DEFSDMEMBER(T_STRING,  acq_branch_id, 0),\
	APP_DEFSDMEMBER(T_STRING,  fwd_inst_id, 0),\
	APP_DEFSDMEMBER(T_STRING,  transmission_timestamp, 0),\
	APP_DEFSDMEMBER(T_STRING,  settle_date, 0),\
	APP_DEFSDMEMBER(T_STRING,  txn_direction, 0),\
	APP_DEFSDMEMBER(T_STRING,  txn_terminal, 0),\
	APP_DEFSDMEMBER(T_STRING,  trans_status, 0),\
	APP_DEFSDMEMBER(T_STRING,  trans_type, 0),\
	APP_DEFSDMEMBER(T_STRING,  log_ol_time, 0),\
	APP_DEFSDMEMBER(T_STRING,  log_biz_date, 0),\
	APP_DEFSDMEMBER(T_STRING,  mti, 0),\
	APP_DEFSDMEMBER(T_STRING,  orig_txn_type, 0),\
	APP_DEFSDMEMBER(T_STRING,  orig_fwd_inst_id, 0),\
	APP_DEFSDMEMBER(T_STRING,  orig_acq_inst_id, 0),\
	APP_DEFSDMEMBER(T_STRING,  orig_mti, 0),\
	APP_DEFSDMEMBER(T_STRING,  orig_trans_date, 0),\
	APP_DEFSDMEMBER(T_LONG,  orig_trace_no, 0),\
	APP_DEFSDMEMBER(T_STRING,  orig_txn_proc, 0),\
	APP_DEFSDMEMBER(T_DOUBLE,  orig_txn_amt, 2),\
	APP_DEFSDMEMBER(T_STRING,  orig_log_kv, 0),\
	APP_DEFSDMEMBER(T_STRING,  orig_txn_val_1, 0),\
	APP_DEFSDMEMBER(T_STRING,  orig_txn_val_2, 0),\
	APP_DEFSDMEMBER(T_DOUBLE,  orig_chb_txn_amt, 2),\
	APP_DEFSDMEMBER(T_STRING,  orig_biz_date, 0),\
	APP_DEFSDMEMBER(T_STRING,  last_reversal_date, 0),\
	APP_DEFSDMEMBER(T_LONG,  void_count, 0),\
	APP_DEFSDMEMBER(T_STRING,  manual_auth_flag, 0),\
	APP_DEFSDMEMBER(T_STRING,  opera_id, 0),\
	APP_DEFSDMEMBER(T_STRING,  brand, 0),\
	APP_DEFSDMEMBER(T_STRING,  product_code, 0),\
	APP_DEFSDMEMBER(T_STRING,  mcc_type, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field271, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field272, 0),\
	APP_DEFSDMEMBER(T_DOUBLE,  comp_amt, 2),\
	APP_DEFSDMEMBER(T_STRING,  final_upd_direction, 0),\
	APP_DEFSDMEMBER(T_DOUBLE,  final_upd_amt, 2),\
	APP_DEFSDMEMBER(T_STRING,  ic_ind, 0),\
	APP_DEFSDMEMBER(T_STRING,  the_3dsecure_type, 0),\
	APP_DEFSDMEMBER(T_STRING,  vip_status, 0),\
	APP_DEFSDMEMBER(T_DOUBLE,  curr_balance, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  cash_amt, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  otb, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  cash_otb, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  cust_otb, 2),\
	APP_DEFSDMEMBER(T_STRING,  user_field273, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field274, 0),\
	APP_DEFSDMEMBER(T_STRING,  expire_date, 0),\
	APP_DEFSDMEMBER(T_STRING,  track_one_result, 0),\
	APP_DEFSDMEMBER(T_STRING,  track_two_result, 0),\
	APP_DEFSDMEMBER(T_STRING,  track_three_result, 0),\
	APP_DEFSDMEMBER(T_STRING,  pwd_type, 0),\
	APP_DEFSDMEMBER(T_STRING,  check_pwd_result, 0),\
	APP_DEFSDMEMBER(T_LONG,  pay_pwd_err_num, 0),\
	APP_DEFSDMEMBER(T_STRING,  check_cvv_result, 0),\
	APP_DEFSDMEMBER(T_STRING,  check_cvv2_result, 0),\
	APP_DEFSDMEMBER(T_STRING,  check_icvn_result, 0),\
	APP_DEFSDMEMBER(T_STRING,  check_arqc_result, 0),\
	APP_DEFSDMEMBER(T_STRING,  check_atc_result, 0),\
	APP_DEFSDMEMBER(T_STRING,  check_cvr_result, 0),\
	APP_DEFSDMEMBER(T_STRING,  check_tvr_result, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field275, 0),\
	APP_DEFSDMEMBER(T_DOUBLE,  unmatch_cr, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  unmatch_db, 2),\
	APP_DEFSDMEMBER(T_STRING,  b002, 0),\
	APP_DEFSDMEMBER(T_STRING,  b003, 0),\
	APP_DEFSDMEMBER(T_STRING,  b007, 0),\
	APP_DEFSDMEMBER(T_STRING,  b011, 0),\
	APP_DEFSDMEMBER(T_STRING,  b022, 0),\
	APP_DEFSDMEMBER(T_STRING,  b025, 0),\
	APP_DEFSDMEMBER(T_STRING,  b032, 0),\
	APP_DEFSDMEMBER(T_STRING,  b033, 0),\
	APP_DEFSDMEMBER(T_STRING,  b039, 0),\
	APP_DEFSDMEMBER(T_STRING,  b042, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field277, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field278, 0),\
	APP_DEFSDMEMBER(T_STRING,  b090, 0),\
	APP_DEFSDMEMBER(T_STRING,  opera_term_id, 0),\
	APP_DEFSDMEMBER(T_LONG,  jpa_version, 0),\
	APP_DEFSDMEMBER(T_DOUBLE,  b004, 4),\
	APP_DEFSDMEMBER(T_DOUBLE,  b006, 4),\
	APP_DEFSDMEMBER(T_STRING,  b049, 0),\
	APP_DEFSDMEMBER(T_STRING,  b051, 0),\
	APP_DEFSDMEMBER(T_STRING,  b037, 0),\
	APP_DEFSDMEMBER(T_DOUBLE,  b028, 4),\
	APP_DEFSDMEMBER(T_STRING,  b048, 0),\
	APP_DEFSDMEMBER(T_STRING,  b054, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field279, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field280, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field281, 0),\
	APP_DEFSDMEMBER(T_STRING,  busi_serial, 0),\
	APP_DEFSDMEMBER(T_STRING,  sys_trans_id, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field282, 0),\
	APP_DEFSDMEMBER(T_STRING,  sub_terminal_type, 0),\
	APP_DEFSDMEMBER(T_STRING,  sub_merch_id, 0),\
	APP_DEFSDMEMBER(T_STRING,  sub_merch_name, 0),\
	APP_DEFSDMEMBER(T_STRING,  wares_desc, 0),\
	APP_DEFSDMEMBER(T_STRING,  last_modified_datetime, 0),\
	APP_DEFSDMEMBER(T_LONG,  part_month, 0),\
	APP_DEFSDMEMBER(T_STRING,  paid_stmt_date, 0),\
	APP_DEFSDMEMBER(T_DOUBLE,  repay_amt, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  bank_proportion, 2),\
	APP_DEFSDMEMBER(T_STRING,  is_check_flag, 0),\
	APP_DEFSDMEMBER(T_STRING,  extend_param1, 0),\
	APP_DEFSDMEMBER(T_STRING,  extend_param2, 0),\
	APP_DEFSDMEMBER(T_STRING,  extend_param3, 0)


	APP_DECLAREFIELDS(SD_ICPS_WB_TM_AUTH_HST)
#undef SD_DATA
#undef SD_MEMBERS

#endif  /*end of __ICPS_WB_TM_AUTH_HST_H__*/
