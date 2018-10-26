/***********************************************************************
版权所有:恒生电子股份有限公司
项目名称:综合技术平台(Turandot)项目
版    本:V1.00
操作系统:
数 据 库:INFORMIX
文 件 名:ICPS_WB_TM_ACCOUNT.h
文件描述:结构定义数据库开发嵌C头文件
项 目 组:
程 序 员:[wangzh14925]
发布时间:2009-4-29 19:40:39 [Gen]
修    订:
修改时间:
************************************************************************
表    名:ICPS_WB_TM_ACCOUNT (F_WB1.账户信息表-核心批量表)
说    明:
************************************************************************
修改记录:
修改日期:
修改内容:
修 改 人:
修改内容:
************************************************************************/
#ifndef __ICPS_WB_TM_ACCOUNT_H__
#define __ICPS_WB_TM_ACCOUNT_H__
typedef struct TDB_ICPS_WB_TM_ACCOUNT
{
	char   busi_date[8+1];  /*业务日期*/
		/*业务日期*/
	int   file_order;  /*文件序号*/
		/*文件序号*/
	char   org[12+1];  /*机构号*/
		/*机构号*/
	char   acct_no[20+1];  /*账户编号*/
		/*账户编号*/
	char   acct_type[1+1];  /*账户类型*/
		/*账户类型*/
	char   cust_id[20+1];  /*客户编号*/
		/*客户编号*/
	char   cust_limit_id[20+1];  /*客户额度ID*/
		/*客户额度ID*/
	char   product_code[6+1];  /*产品代码*/
		/*产品代码*/
	char   default_logical_card_no[19+1];  /*默认逻辑卡号*/
		/*默认逻辑卡号*/
	char   currency[3+1];  /*币种*/
		/*币种*/
	double   credit_limit;  /*授信额度*/
		/*授信额度*/
	double   temp_limit;  /*临时额度*/
		/*临时额度*/
	char   temp_limit_begin_date[8+1];  /*临时额度开始日期*/
		/*临时额度开始日期*/
	char   temp_limit_end_date[8+1];  /*临时额度结束日期*/
		/*临时额度结束日期*/
	double   user_field1;  /*备用字段1*/
		/*备用字段1*/
	double   user_field2;  /*备用字段2*/
		/*备用字段2*/
	double   user_field3;  /*备用字段3*/
		/*备用字段3*/
	double   curr_balance;  /*当前余额*/
		/*当前余额*/
	double   user_field4;  /*备用字段4*/
		/*备用字段4*/
	double   principal_bal;  /*本金余额*/
		/*本金余额*/
	double   user_field5;  /*备用字段5*/
		/*备用字段5*/
	double   user_field6;  /*备用字段6*/
		/*备用字段6*/
	double   begin_bal;  /*上一到期日余额*/
		/*上一到期日余额*/
	double   pmt_due_day_bal;  /*到期还款日余额*/
		/*到期还款日余额*/
	double   user_field7;  /*备用字段7*/
		/*备用字段7*/
	char   user_field8[1+1];  /*备用字段8*/
		/*备用字段8*/
	double   user_field9;  /*备用字段9*/
		/*备用字段9*/
	double   user_field10;  /*备用字段10*/
		/*备用字段10*/
	double   user_field11;  /*备用字段11*/
		/*备用字段11*/
	double   user_field12;  /*备用字段12*/
		/*备用字段12*/
	double   user_field13;  /*备用字段13*/
		/*备用字段13*/
	char   user_field14[8+1];  /*备用字段14*/
		/*备用字段14*/
	char   user_field15[8+1];  /*备用字段15*/
		/*备用字段15*/
	char   user_field16[8+1];  /*备用字段16*/
		/*备用字段16*/
	char   user_field17[8+1];  /*备用字段17*/
		/*备用字段17*/
	int   user_field18;  /*备用字段18*/
		/*备用字段18*/
	char   name[80+1];  /*姓名*/
		/*姓名*/
	char   gender[1+1];  /*性别*/
		/*性别*/
	char   user_field19[9+1];  /*备用字段19*/
		/*备用字段19*/
	char   mobile_no[20+1];  /*移动电话*/
		/*移动电话*/
	char   user_field20[200+1];  /*备用字段20*/
		/*备用字段20*/
	char   billint_cycle[2+1];  /*还款日*/
		/*还款日*/
	char   user_field21[1+1];  /*备用字段21*/
		/*备用字段21*/
	char   user_field22[1+1];  /*备用字段22*/
		/*备用字段22*/
	char   user_field23[1+1];  /*备用字段23*/
		/*备用字段23*/
	char   user_field24[3+1];  /*备用字段24*/
		/*备用字段24*/
	char   user_field25[40+1];  /*备用字段25*/
		/*备用字段25*/
	char   user_field26[40+1];  /*备用字段26*/
		/*备用字段26*/
	char   user_field27[40+1];  /*备用字段27*/
		/*备用字段27*/
	char   user_field28[200+1];  /*备用字段28*/
		/*备用字段28*/
	char   user_field29[10+1];  /*备用字段29*/
		/*备用字段29*/
	char   user_field30[80+1];  /*备用字段30*/
		/*备用字段30*/
	char   user_field31[27+1];  /*备用字段31*/
		/*备用字段31*/
	char   AGE_CD[1+1];  /*拖欠月数*/
		/*拖欠月数*/
	char   user_field32[1+1];  /*备用字段32*/
		/*备用字段32*/
	double   UNMATCH_DB;  /*未入账借记金额*/
		/*未入账借记金额*/
	double   user_field33;  /*备用字段33*/
		/*备用字段33*/
	double   unmatch_cr;  /*未入账贷记金额*/
		/*未入账贷记金额*/
	char   dd_ind[1+1];  /*约定还款类型*/
		/*约定还款类型*/
	char   dd_bank_name[80+1];  /*约定还款银行名称*/
		/*约定还款银行名称*/
	char   dd_bank_branch[14+1];  /*约定还款开户行号*/
		/*约定还款开户行号*/
	char   dd_bank_acct_no[40+1];  /*约定还款扣款账号*/
		/*约定还款扣款账号*/
	char   dd_bank_acct_name[80+1];  /*约定还款扣款账户姓名*/
		/*约定还款扣款账户姓名*/
	double   last_dd_amt;  /*上期约定还款金额*/
		/*上期约定还款金额*/
	char   last_dd_date[14+1];  /*上期约定还款日期*/
		/*上期约定还款日期*/
	char   user_field34[1+1];  /*备用字段34*/
		/*备用字段34*/
	double   last_pmt_amt;  /*上期还款金额*/
		/*上期还款金额*/
	char   last_pmt_date[14+1];  /*上个还款日期*/
		/*上个还款日期*/
	char   last_stmt_date[14+1];  /*上个到期还款日期*/
		/*上个到期还款日期*/
	char   last_pmt_due_date[14+1];  /*上个到期还款日期1*/
		/*上个到期还款日期1*/
	char   last_agint_date[14+1];  /*上课逾期月数提升日期*/
		/*上课逾期月数提升日期*/
	char   collect_date[14+1];  /*入催日期*/
		/*入催日期*/
	char   collect_out_date[14+1];  /*出催收队列日期*/
		/*出催收队列日期*/
	char   next_stmt_date[14+1];  /*下个到期还款日期*/
		/*下个到期还款日期*/
	char   pmt_due_date[14+1];  /*到期还款日期*/
		/*到期还款日期*/
	char   dd_date[14+1];  /*约定还款日期*/
		/*约定还款日期*/
	char   grace_date[14+1];  /*宽限日期*/
		/*宽限日期*/
	char   user_field35[14+1];  /*备用字段35*/
		/*备用字段35*/
	char   closed_date[14+1];  /*最终销户日期*/
		/*最终销户日期*/
	char   first_stmt_date[14+1];  /*首个到期还款日期*/
		/*首个到期还款日期*/
	char   cancel_date[14+1];  /*销户日期*/
		/*销户日期*/
	char   charge_off_date[14+1];  /*转呆账日期*/
		/*转呆账日期*/
	char   user_field36[14+1];  /*备用字段36*/
		/*备用字段36*/
	double   usesr_field37;  /*备用字段37*/
		/*备用字段37*/
	double   usesr_field38;  /*备用字段38*/
		/*备用字段38*/
	double   usesr_field39;  /*备用字段39*/
		/*备用字段39*/
	double   usesr_field40;  /*备用字段40*/
		/*备用字段40*/
	double   usesr_field41;  /*备用字段41*/
		/*备用字段41*/
	double   usesr_field42;  /*备用字段42*/
		/*备用字段42*/
	double   usesr_field43;  /*备用字段43*/
		/*备用字段43*/
	double   usesr_field44;  /*备用字段44*/
		/*备用字段44*/
	double   usesr_field45;  /*备用字段45*/
		/*备用字段45*/
	double   usesr_field46;  /*备用字段46*/
		/*备用字段46*/
	double   usesr_field47;  /*备用字段47*/
		/*备用字段47*/
	double   usesr_field48;  /*备用字段48*/
		/*备用字段48*/
	int   usesr_field49;  /*备用字段49*/
		/*备用字段49*/
	double   ctd_retail_amt;  /*当期消费金额*/
		/*当期消费金额*/
	int   ctd_retail_cnt;  /*当期消费笔数*/
		/*当期消费笔数*/
	double   ctd_payment_amt;  /*当期还款金额*/
		/*当期还款金额*/
	int   ctd_payment_cnt;  /*当期还款笔数*/
		/*当期还款笔数*/
	double   ctd_db_adj_amt;  /*当期借记调整金额*/
		/*当期借记调整金额*/
	int   ctd_db_adj_cnt;  /*当期借记调整笔数*/
		/*当期借记调整笔数*/
	int   ctd_cr_adj_cnt;  /*当期贷记调整笔数*/
		/*当期贷记调整笔数*/
	double   ctd_cr_adj_amt;  /*当期贷记调整金额*/
		/*当期贷记调整金额*/
	double   ctd_fee_amt;  /*当期费用金额*/
		/*当期贷记调整金额*/
	int   ctd_fee_cnt;  /*当期费用笔数*/
		/*当期费用笔数*/
	double   ctd_interest_amt;  /*当期利息金额*/
		/*当期利息金额*/
	int   ctd_interest_cnt;  /*当期利息笔数*/
		/*当期利息笔数*/
	double   user_field50;  /*备用字段50*/
		/*备用字段50*/
	int   user_field51;  /*备用字段51*/
		/*备用字段51*/
	double   user_field52;  /*备用字段52*/
		/*备用字段52*/
	double   mtd_retail_amt;  /*本月消费金额*/
		/*本月消费金额*/
	int   mtd_retail_cnt;  /*本月消费笔数*/
		/*本月消费笔数*/
	double   user_field53;  /*备用字段53*/
		/*备用字段53*/
	int   user_field54;  /*备用字段54*/
		/*备用字段54*/
	double   user_field55;  /*备用字段55*/
		/*备用字段55*/
	int   user_field56;  /*备用字段56*/
		/*备用字段56*/
	double   ytd_retail_amt;  /*本年消费金额*/
		/*本年消费金额*/
	int   ytd_retail_cnt;  /*本年消费笔数*/
		/*本年消费笔数*/
	double   user_field57;  /*备用字段57*/
		/*备用字段57*/
	int   user_field58;  /*备用字段58*/
		/*备用字段58*/
	double   user_field59;  /*备用字段59*/
		/*备用字段59*/
	int   user_field60;  /*备用字段60*/
		/*备用字段60*/
	double   user_field61;  /*备用字段61*/
		/*备用字段61*/
	int   user_field62;  /*备用字段62*/
		/*备用字段62*/
	double   user_field63;  /*备用字段63*/
		/*备用字段63*/
	int   user_field64;  /*备用字段64*/
		/*备用字段64*/
	double   user_field65;  /*备用字段65*/
		/*备用字段64*/
	int   user_field66;  /*备用字段66*/
		/*备用字段66*/
	double   user_field67;  /*备用字段67*/
		/*备用字段67*/
	int   user_field68;  /*备用字段68*/
		/*备用字段68*/
	double   user_field69;  /*备用字段69*/
		/*备用字段69*/
	int   user_field70;  /*备用字段70*/
		/*备用字段70*/
	double   user_field71;  /*备用字段71*/
		/*备用字段71*/
	double   user_field72;  /*备用字段72*/
		/*备用字段72*/
	double   user_field73;  /*备用字段73*/
		/*备用字段73*/
	double   user_field74;  /*备用字段74*/
		/*备用字段74*/
	char   user_field75[8+1];  /*备用字段75*/
		/*备用字段75*/
	char   user_field76[2+1];  /*备用字段76*/
		/*备用字段76*/
	char   user_field77[24+1];  /*备用字段77*/
		/*备用字段77*/
	char   user_field78[24+1];  /*备用字段78*/
		/*备用字段78*/
	char   user_field79[1+1];  /*备用字段79*/
		/*备用字段79*/
	char   user_field80[1+1];  /*备用字段80*/
		/*备用字段80*/
	char   user_field81[1+1];  /*备用字段81*/
		/*备用字段81*/
	char   waive_svcfee_ind[1+1];  /*是否免除服务费*/
		/*是否免除服务费*/
	char   user_field82[4+1];  /*备用字段82*/
		/*备用字段82*/
	char   user_field83[4+1];  /*备用字段83*/
		/*备用字段83*/
	char   user_field84[4+1];  /*备用字段84*/
		/*备用字段84*/
	char   user_field85[4+1];  /*备用字段85*/
		/*备用字段85*/
	char   user_field86[4+1];  /*备用字段86*/
		/*备用字段86*/
	char   user_field87[4+1];  /*备用字段87*/
		/*备用字段87*/
	char   user_field88[14+1];  /*备用字段88*/
		/*备用字段88*/
	char   user_date2[14+1];  /*上期调额日期*/
		/*上期调额日期*/
	char   user_field89[14+1];  /*备用字段89*/
		/*备用字段89*/
	char   user_field90[14+1];  /*备用字段90*/
		/*备用字段90*/
	char   user_field91[14+1];  /*备用字段91*/
		/*备用字段91*/
	char   user_field92[14+1];  /*备用字段92*/
		/*备用字段92*/
	int   user_field93;  /*备用字段93*/
		/*备用字段93*/
	int   user_field94;  /*备用字段94*/
		/*备用字段94*/
	int   user_field95;  /*备用字段95*/
		/*备用字段95*/
	int   user_field96;  /*备用字段96*/
		/*备用字段96*/
	int   user_field97;  /*备用字段97*/
		/*备用字段97*/
	int   user_field98;  /*备用字段98*/
		/*备用字段98*/
	char   user_field99[40+1];  /*备用字段99*/
		/*备用字段99*/
	char   user_field100[40+1];  /*备用字段100*/
		/*备用字段100*/
	char   user_field101[40+1];  /*备用字段101*/
		/*备用字段101*/
	char   user_field102[40+1];  /*备用字段102*/
		/*备用字段102*/
	char   user_field103[40+1];  /*备用字段103*/
		/*备用字段103*/
	char   user_field104[40+1];  /*备用字段104*/
		/*备用字段104*/
	double   user_field105;  /*备用字段105*/
		/*备用字段105*/
	double   user_field106;  /*备用字段106*/
		/*备用字段106*/
	double   user_field107;  /*备用字段107*/
		/*备用字段107*/
	double   user_field108;  /*备用字段108*/
		/*备用字段108*/
	double   user_field109;  /*备用字段109*/
		/*备用字段109*/
	double   user_field110;  /*备用字段110*/
		/*备用字段110*/
	int   jpa_version;  /*乐观锁版本号*/
		/*乐观锁版本号*/
	double   mtd_payment_amt;  /*当月还款金额*/
		/*当月还款金额*/
	int   mtd_payment_cnt;  /*当月还款笔数*/
		/*当月还款笔数*/
	double   ytd_payment_amt;  /*当年还款金额*/
		/*当年还款金额*/
	int   ytd_payment_cnt;  /*当年还款笔数*/
		/*当年还款笔数*/
	double   ltd_payment_amt;  /*历史还款金额*/
		/*历史还款金额*/
	int   ltd_payment_cnt;  /*历史还款笔数*/
		/*历史还款笔数*/
	char   user_field111[1+1];  /*备用字段111*/
		/*备用字段111*/
	double   user_field112;  /*备用字段112*/
		/*备用字段112*/
	int   user_field113;  /*备用字段113*/
		/*备用字段113*/
	char   last_post_date[8+1];  /*上个批量处理时间*/
		/*上个批量处理时间*/
	char   last_modified_datetime[14+1];  /*修改时间*/
		/*修改时间*/
	char   user_field114[8+1];  /*备用字段114*/
		/*备用字段114*/
	char   last_sync_date[8+1];  /*上一次入账的批量日期*/
		/*上一次入账的批量日期*/
	char   user_field115[14+1];  /*备用字段115*/
		/*备用字段115*/
	double   user_field116;  /*备用字段116*/
		/*备用字段116*/
	char   user_field117[16+1];  /*备用字段117*/
		/*备用字段117*/
	char   bank_group_id[5+1];  /*银团编号*/
		/*银团编号*/
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

}ICPS_WB_TM_ACCOUNT;

#define SD_DATA  ICPS_WB_TM_ACCOUNT
#define SD_MEMBERS \ 
	APP_DEFSDMEMBER(T_STRING,  busi_date, 0),\
	APP_DEFSDMEMBER(T_LONG,  file_order, 0),\
	APP_DEFSDMEMBER(T_STRING,  org, 0),\
	APP_DEFSDMEMBER(T_STRING,  acct_no, 0),\
	APP_DEFSDMEMBER(T_STRING,  acct_type, 0),\
	APP_DEFSDMEMBER(T_STRING,  cust_id, 0),\
	APP_DEFSDMEMBER(T_STRING,  cust_limit_id, 0),\
	APP_DEFSDMEMBER(T_STRING,  product_code, 0),\
	APP_DEFSDMEMBER(T_STRING,  default_logical_card_no, 0),\
	APP_DEFSDMEMBER(T_STRING,  currency, 0),\
	APP_DEFSDMEMBER(T_DOUBLE,  credit_limit, 4),\
	APP_DEFSDMEMBER(T_DOUBLE,  temp_limit, 4),\
	APP_DEFSDMEMBER(T_STRING,  temp_limit_begin_date, 0),\
	APP_DEFSDMEMBER(T_STRING,  temp_limit_end_date, 0),\
	APP_DEFSDMEMBER(T_DOUBLE,  user_field1, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  user_field2, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  user_field3, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  curr_balance, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  user_field4, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  principal_bal, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  user_field5, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  user_field6, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  begin_bal, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  pmt_due_day_bal, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  user_field7, 2),\
	APP_DEFSDMEMBER(T_STRING,  user_field8, 0),\
	APP_DEFSDMEMBER(T_DOUBLE,  user_field9, 4),\
	APP_DEFSDMEMBER(T_DOUBLE,  user_field10, 4),\
	APP_DEFSDMEMBER(T_DOUBLE,  user_field11, 4),\
	APP_DEFSDMEMBER(T_DOUBLE,  user_field12, 4),\
	APP_DEFSDMEMBER(T_DOUBLE,  user_field13, 4),\
	APP_DEFSDMEMBER(T_STRING,  user_field14, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field15, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field16, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field17, 0),\
	APP_DEFSDMEMBER(T_LONG,  user_field18, 0),\
	APP_DEFSDMEMBER(T_STRING,  name, 0),\
	APP_DEFSDMEMBER(T_STRING,  gender, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field19, 0),\
	APP_DEFSDMEMBER(T_STRING,  mobile_no, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field20, 0),\
	APP_DEFSDMEMBER(T_STRING,  billint_cycle, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field21, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field22, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field23, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field24, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field25, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field26, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field27, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field28, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field29, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field30, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field31, 0),\
	APP_DEFSDMEMBER(T_STRING,  AGE_CD, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field32, 0),\
	APP_DEFSDMEMBER(T_DOUBLE,  UNMATCH_DB, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  user_field33, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  unmatch_cr, 2),\
	APP_DEFSDMEMBER(T_STRING,  dd_ind, 0),\
	APP_DEFSDMEMBER(T_STRING,  dd_bank_name, 0),\
	APP_DEFSDMEMBER(T_STRING,  dd_bank_branch, 0),\
	APP_DEFSDMEMBER(T_STRING,  dd_bank_acct_no, 0),\
	APP_DEFSDMEMBER(T_STRING,  dd_bank_acct_name, 0),\
	APP_DEFSDMEMBER(T_DOUBLE,  last_dd_amt, 2),\
	APP_DEFSDMEMBER(T_STRING,  last_dd_date, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field34, 0),\
	APP_DEFSDMEMBER(T_DOUBLE,  last_pmt_amt, 2),\
	APP_DEFSDMEMBER(T_STRING,  last_pmt_date, 0),\
	APP_DEFSDMEMBER(T_STRING,  last_stmt_date, 0),\
	APP_DEFSDMEMBER(T_STRING,  last_pmt_due_date, 0),\
	APP_DEFSDMEMBER(T_STRING,  last_agint_date, 0),\
	APP_DEFSDMEMBER(T_STRING,  collect_date, 0),\
	APP_DEFSDMEMBER(T_STRING,  collect_out_date, 0),\
	APP_DEFSDMEMBER(T_STRING,  next_stmt_date, 0),\
	APP_DEFSDMEMBER(T_STRING,  pmt_due_date, 0),\
	APP_DEFSDMEMBER(T_STRING,  dd_date, 0),\
	APP_DEFSDMEMBER(T_STRING,  grace_date, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field35, 0),\
	APP_DEFSDMEMBER(T_STRING,  closed_date, 0),\
	APP_DEFSDMEMBER(T_STRING,  first_stmt_date, 0),\
	APP_DEFSDMEMBER(T_STRING,  cancel_date, 0),\
	APP_DEFSDMEMBER(T_STRING,  charge_off_date, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field36, 0),\
	APP_DEFSDMEMBER(T_DOUBLE,  usesr_field37, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  usesr_field38, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  usesr_field39, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  usesr_field40, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  usesr_field41, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  usesr_field42, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  usesr_field43, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  usesr_field44, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  usesr_field45, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  usesr_field46, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  usesr_field47, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  usesr_field48, 2),\
	APP_DEFSDMEMBER(T_LONG,  usesr_field49, 0),\
	APP_DEFSDMEMBER(T_DOUBLE,  ctd_retail_amt, 2),\
	APP_DEFSDMEMBER(T_LONG,  ctd_retail_cnt, 0),\
	APP_DEFSDMEMBER(T_DOUBLE,  ctd_payment_amt, 2),\
	APP_DEFSDMEMBER(T_LONG,  ctd_payment_cnt, 0),\
	APP_DEFSDMEMBER(T_DOUBLE,  ctd_db_adj_amt, 2),\
	APP_DEFSDMEMBER(T_LONG,  ctd_db_adj_cnt, 0),\
	APP_DEFSDMEMBER(T_LONG,  ctd_cr_adj_cnt, 0),\
	APP_DEFSDMEMBER(T_DOUBLE,  ctd_cr_adj_amt, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  ctd_fee_amt, 2),\
	APP_DEFSDMEMBER(T_LONG,  ctd_fee_cnt, 0),\
	APP_DEFSDMEMBER(T_DOUBLE,  ctd_interest_amt, 2),\
	APP_DEFSDMEMBER(T_LONG,  ctd_interest_cnt, 0),\
	APP_DEFSDMEMBER(T_DOUBLE,  user_field50, 2),\
	APP_DEFSDMEMBER(T_LONG,  user_field51, 0),\
	APP_DEFSDMEMBER(T_DOUBLE,  user_field52, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  mtd_retail_amt, 2),\
	APP_DEFSDMEMBER(T_LONG,  mtd_retail_cnt, 0),\
	APP_DEFSDMEMBER(T_DOUBLE,  user_field53, 2),\
	APP_DEFSDMEMBER(T_LONG,  user_field54, 0),\
	APP_DEFSDMEMBER(T_DOUBLE,  user_field55, 2),\
	APP_DEFSDMEMBER(T_LONG,  user_field56, 0),\
	APP_DEFSDMEMBER(T_DOUBLE,  ytd_retail_amt, 2),\
	APP_DEFSDMEMBER(T_LONG,  ytd_retail_cnt, 0),\
	APP_DEFSDMEMBER(T_DOUBLE,  user_field57, 2),\
	APP_DEFSDMEMBER(T_LONG,  user_field58, 0),\
	APP_DEFSDMEMBER(T_DOUBLE,  user_field59, 2),\
	APP_DEFSDMEMBER(T_LONG,  user_field60, 0),\
	APP_DEFSDMEMBER(T_DOUBLE,  user_field61, 2),\
	APP_DEFSDMEMBER(T_LONG,  user_field62, 0),\
	APP_DEFSDMEMBER(T_DOUBLE,  user_field63, 2),\
	APP_DEFSDMEMBER(T_LONG,  user_field64, 0),\
	APP_DEFSDMEMBER(T_DOUBLE,  user_field65, 2),\
	APP_DEFSDMEMBER(T_LONG,  user_field66, 0),\
	APP_DEFSDMEMBER(T_DOUBLE,  user_field67, 2),\
	APP_DEFSDMEMBER(T_LONG,  user_field68, 0),\
	APP_DEFSDMEMBER(T_DOUBLE,  user_field69, 2),\
	APP_DEFSDMEMBER(T_LONG,  user_field70, 0),\
	APP_DEFSDMEMBER(T_DOUBLE,  user_field71, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  user_field72, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  user_field73, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  user_field74, 2),\
	APP_DEFSDMEMBER(T_STRING,  user_field75, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field76, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field77, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field78, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field79, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field80, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field81, 0),\
	APP_DEFSDMEMBER(T_STRING,  waive_svcfee_ind, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field82, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field83, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field84, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field85, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field86, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field87, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field88, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_date2, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field89, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field90, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field91, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field92, 0),\
	APP_DEFSDMEMBER(T_LONG,  user_field93, 0),\
	APP_DEFSDMEMBER(T_LONG,  user_field94, 0),\
	APP_DEFSDMEMBER(T_LONG,  user_field95, 0),\
	APP_DEFSDMEMBER(T_LONG,  user_field96, 0),\
	APP_DEFSDMEMBER(T_LONG,  user_field97, 0),\
	APP_DEFSDMEMBER(T_LONG,  user_field98, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field99, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field100, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field101, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field102, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field103, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field104, 0),\
	APP_DEFSDMEMBER(T_DOUBLE,  user_field105, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  user_field106, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  user_field107, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  user_field108, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  user_field109, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  user_field110, 2),\
	APP_DEFSDMEMBER(T_LONG,  jpa_version, 0),\
	APP_DEFSDMEMBER(T_DOUBLE,  mtd_payment_amt, 2),\
	APP_DEFSDMEMBER(T_LONG,  mtd_payment_cnt, 0),\
	APP_DEFSDMEMBER(T_DOUBLE,  ytd_payment_amt, 2),\
	APP_DEFSDMEMBER(T_LONG,  ytd_payment_cnt, 0),\
	APP_DEFSDMEMBER(T_DOUBLE,  ltd_payment_amt, 2),\
	APP_DEFSDMEMBER(T_LONG,  ltd_payment_cnt, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field111, 0),\
	APP_DEFSDMEMBER(T_DOUBLE,  user_field112, 2),\
	APP_DEFSDMEMBER(T_LONG,  user_field113, 0),\
	APP_DEFSDMEMBER(T_STRING,  last_post_date, 0),\
	APP_DEFSDMEMBER(T_STRING,  last_modified_datetime, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field114, 0),\
	APP_DEFSDMEMBER(T_STRING,  last_sync_date, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field115, 0),\
	APP_DEFSDMEMBER(T_DOUBLE,  user_field116, 2),\
	APP_DEFSDMEMBER(T_STRING,  user_field117, 0),\
	APP_DEFSDMEMBER(T_STRING,  bank_group_id, 0),\
	APP_DEFSDMEMBER(T_DOUBLE,  bank_proportion, 2),\
	APP_DEFSDMEMBER(T_STRING,  is_check_flag, 0),\
	APP_DEFSDMEMBER(T_STRING,  extend_param1, 0),\
	APP_DEFSDMEMBER(T_STRING,  extend_param2, 0),\
	APP_DEFSDMEMBER(T_STRING,  extend_param3, 0)


	APP_DECLAREFIELDS(SD_ICPS_WB_TM_ACCOUNT)
#undef SD_DATA
#undef SD_MEMBERS

#endif  /*end of __ICPS_WB_TM_ACCOUNT_H__*/
