/***********************************************************************
版权所有:恒生电子股份有限公司
项目名称:综合技术平台(Turandot)项目
版    本:V1.00
操作系统:
数 据 库:
文 件 名:ICPS_WBC_TT_TXN_POST.h
文件描述:结构定义数据库开发嵌C头文件
项 目 组:
程 序 员:[fuwd22392]
发布时间:2018-06-12 10:00:00 [Gen]
修    订:
修改时间:
************************************************************************
表    名:ICPS_WBC_TT_TXN_POST
说    明:当日入账交易表
************************************************************************
修改记录:195
修改日期:
修改内容:
修 改 人:
修改内容:
************************************************************************/

#ifndef __ICPS_WBC_TT_TXN_POST_H__
#define __ICPS_WBC_TT_TXN_POST_H__
typedef struct TDB_ICPS_WBC_TT_TXN_POST
{
   char			busi_date[8+1];                   
   int			file_order;
   char			org[12+1];                              /*机构号                       */
   char			txn_seq[20+1];                          /*交易流水号fuwd22392 modify           */
   char			acct_no[20+1];	                        /*账户编号   fuwd22392 modify          */
   char 		acct_type[1+1];	                       /*账户类型                     */
   char 		card_no[19+1];	                         /*卡号                         */
   char 		logical_card_no[19+1];	                 /*逻辑卡号                     */
   char 		bsc_logiccard_no[19+1];	               /*逻辑卡主卡卡号               */
   char 		product_cd[6+1];	                       /*产品代码                     */
   char 		txn_date[8+1];	                         /*交易日期                     */
   char 		txn_time[14+1];	                       /*交易时间                     */
   char 		post_txn_type[1+1];	                   /*入账交易类型                 */
   char 		txn_code[4+1];	                         /*交易码                       */
   char 		db_cr_ind[1+1];	                       /*借贷标志                     */
   double		txn_amt;                                /*交易金额                     */
   double		post_amt;                               /*入账币种金额                 */
   char			post_date[8+1];	                       /*入账日期                     */
   char			auth_code[6+1];	                       /*授权码                       */
   char			card_block_code[27+1];                  /*卡片锁定码                   */
   char			txn_curr_cd[3+1];	                     /*交易币种代码                 */
   char			post_curr_cd[3+1];	                     /*入账币种代码                 */
   char			orig_trans_date[8+1];	                 /*原始交易日期                 */
   char			plan_nbr[6+1];	                         /*信用计划号                   */
   char			ref_nbr[23+1];                          /*交易参考号                   */
   char			txn_desc[80+1];                         /*交易描述                     */
   char			txn_short_desc[80+1];                   /*账单交易描述                 */
   double      	point;                                  /*积分数值                     */
   char			posting_flag[3+1];                      /*入账结果标示码               */
   char			pre_posting_flag[3+1];                  /*往日入账结果标示码           */
   double	    rel_pmt_amt;                            /*公司卡还款金额               */
   double	    orig_pmt_amt;                           /*还款交易原始金额             */
   char			acq_branch_id[9+1];	                   /*受理分行代码                 */
   char			acq_terminal_id[8+1];	                 /*受理机构终端标识码           */
   char			acq_acceptor_id[15+1];	                 /*受卡方标识码                 */
   char			acq_name_addr[40+1];	                   /*受理机构名称地址             */
   char			mcc[4+1];	                             /*商户类别代码                 */
   char			input_txn_code[4+1];	                   /*原交易交易码                 */
   double		input_txn_amt;                          /*原交易交易金额               */
   double		input_sett_amt;                         /*原交易清算金额               */
   double		interchange_fee;                        /*原交易货币转换费             */
   double		fee_payout;                              /*发卡方应付手续费             */
   double		fee_profit;                              /*发卡方应得手续费             */
   double		loan_issue_profit;                       /*分期交易发卡行收益           */
   char			stmt_date[8+1];	                       /*账单日期                     */
   char			voucher_no[7+1];	                       /*销售单凭证号                 */
   int			jpa_version;                            /*乐观锁版本号                 */
   int			term;                                   /*所在分期期数                 */
   char         consumer_trans_id[32+1];	               /*业务流水号                   */
   char         sys_trans_id[32+1];	                   /*系统调用流水号               */
   char         qchannel_id[15+1];	                     /*渠道编号                     */
   char         sub_terminal_type[15+1];	               /*终端类型                     */
   char         sub_merch_id[40+1];	                   /*二级商户编码                 */
   char         sub_merch_name[60+1];	                 /*二级商户名称                 */
   char         wares_desc[60+1];	                     /*商品信息                     */
   char         last_modified_datetime[14+1];	         /*修改时间                     */
   char         paid_stmt_date[8+1];	                   /*还款账单日                   */
   double		repay_amt;                              /*应还款额                     */
   char			counter_acct[32+1];	                   /*对手方账户                   */
   char			counter_name[120+1];                    /*对手方姓名                   */
   char			counter_brno[14+1];	                   /*对手方行号                   */
   char			counter_brname[180+1];                  /*对手方行名                   */
   char			is_check_flag[1+1];	
   char			extend_param1[100+1];
   char			extend_param2[250+1];
   char			extend_param3[40+1];	

}ICPS_WBC_TT_TXN_POST;

#define SD_DATA  ICPS_WBC_TT_TXN_POST                         
#define SD_MEMBERS \                                          
  APP_DEFSDMEMBER(T_STRING,     busi_date              ,0),\
  APP_DEFSDMEMBER(T_LONG,     	file_order             ,0),\
  APP_DEFSDMEMBER(T_STRING,     org                    ,0),\
  APP_DEFSDMEMBER(T_STRING,     txn_seq                ,0),\
  APP_DEFSDMEMBER(T_STRING,     acct_no                ,0),\
  APP_DEFSDMEMBER(T_STRING,     acct_type              ,0),\
  APP_DEFSDMEMBER(T_STRING,     card_no                ,0),\
  APP_DEFSDMEMBER(T_STRING,     logical_card_no        ,0),\
  APP_DEFSDMEMBER(T_STRING,     bsc_logiccard_no       ,0),\
  APP_DEFSDMEMBER(T_STRING,     product_cd             ,0),\
  APP_DEFSDMEMBER(T_STRING,     txn_date               ,0),\
  APP_DEFSDMEMBER(T_STRING,     txn_time               ,0),\
  APP_DEFSDMEMBER(T_STRING,     post_txn_type          ,0),\
  APP_DEFSDMEMBER(T_STRING,     txn_code               ,0),\
  APP_DEFSDMEMBER(T_STRING,     db_cr_ind              ,0),\
  APP_DEFSDMEMBER(T_DOUBLE,     txn_amt                ,2),\
  APP_DEFSDMEMBER(T_DOUBLE,     post_amt               ,2),\
  APP_DEFSDMEMBER(T_STRING,     post_date              ,0),\
  APP_DEFSDMEMBER(T_STRING,     auth_code              ,0),\
  APP_DEFSDMEMBER(T_STRING,     card_block_code        ,0),\
  APP_DEFSDMEMBER(T_STRING,     txn_curr_cd            ,0),\
  APP_DEFSDMEMBER(T_STRING,     post_curr_cd           ,0),\
  APP_DEFSDMEMBER(T_STRING,     orig_trans_date        ,0),\
  APP_DEFSDMEMBER(T_STRING,     plan_nbr               ,0),\
  APP_DEFSDMEMBER(T_STRING,     ref_nbr                ,0),\
  APP_DEFSDMEMBER(T_STRING,     txn_desc               ,0),\
  APP_DEFSDMEMBER(T_STRING,     txn_short_desc         ,0),\
  APP_DEFSDMEMBER(T_DOUBLE,     point                  ,2),\
  APP_DEFSDMEMBER(T_STRING,     posting_flag           ,0),\
  APP_DEFSDMEMBER(T_STRING,     pre_posting_flag       ,0),\
  APP_DEFSDMEMBER(T_DOUBLE,     rel_pmt_amt            ,2),\
  APP_DEFSDMEMBER(T_DOUBLE,     orig_pmt_amt           ,2),\
  APP_DEFSDMEMBER(T_STRING,     acq_branch_id          ,0),\
  APP_DEFSDMEMBER(T_STRING,     acq_terminal_id        ,0),\
  APP_DEFSDMEMBER(T_STRING,     acq_acceptor_id        ,0),\
  APP_DEFSDMEMBER(T_STRING,     acq_name_addr          ,0),\
  APP_DEFSDMEMBER(T_STRING,     mcc                    ,0),\
  APP_DEFSDMEMBER(T_STRING,     input_txn_code         ,0),\
  APP_DEFSDMEMBER(T_DOUBLE,     input_txn_amt          ,2),\
  APP_DEFSDMEMBER(T_DOUBLE,     input_sett_amt         ,2),\
  APP_DEFSDMEMBER(T_DOUBLE,     interchange_fee        ,2),\
  APP_DEFSDMEMBER(T_DOUBLE,     fee_payout             ,2),\
  APP_DEFSDMEMBER(T_DOUBLE,     fee_profit             ,2),\
  APP_DEFSDMEMBER(T_DOUBLE,     loan_issue_profit      ,2),\
  APP_DEFSDMEMBER(T_STRING,     stmt_date              ,0),\
  APP_DEFSDMEMBER(T_STRING,     voucher_no             ,0),\
  APP_DEFSDMEMBER(T_LONG,       jpa_version            ,0),\
  APP_DEFSDMEMBER(T_LONG,       term                   ,0),\
  APP_DEFSDMEMBER(T_STRING,     consumer_trans_id      ,0),\
  APP_DEFSDMEMBER(T_STRING,     sys_trans_id           ,0),\
  APP_DEFSDMEMBER(T_STRING,     qchannel_id            ,0),\
  APP_DEFSDMEMBER(T_STRING,     sub_terminal_type      ,0),\
  APP_DEFSDMEMBER(T_STRING,     sub_merch_id           ,0),\
  APP_DEFSDMEMBER(T_STRING,     sub_merch_name         ,0),\
  APP_DEFSDMEMBER(T_STRING,     wares_desc             ,0),\
  APP_DEFSDMEMBER(T_STRING,     last_modified_datetime ,0),\
  APP_DEFSDMEMBER(T_STRING,     paid_stmt_date         ,0),\
  APP_DEFSDMEMBER(T_DOUBLE,     repay_amt              ,2),\
  APP_DEFSDMEMBER(T_STRING,     counter_acct           ,0),\
  APP_DEFSDMEMBER(T_STRING,     counter_name           ,0),\
  APP_DEFSDMEMBER(T_STRING,     counter_brno           ,0),\
  APP_DEFSDMEMBER(T_STRING,     counter_brname         ,0),\
  APP_DEFSDMEMBER(T_STRING,     is_check_flag          ,0),\
  APP_DEFSDMEMBER(T_STRING,     extend_param1          ,0),\
  APP_DEFSDMEMBER(T_STRING,     extend_param2          ,0),\
  APP_DEFSDMEMBER(T_STRING,     extend_param3          ,0)
  APP_DECLAREFIELDS(SD_ICPS_WBC_TT_TXN_POST)                
#undef SD_DATA
#undef SD_MEMBERS
                                                             
#endif  /*end of __ICPS_WBC_TT_TXN_POST_H__*/                
