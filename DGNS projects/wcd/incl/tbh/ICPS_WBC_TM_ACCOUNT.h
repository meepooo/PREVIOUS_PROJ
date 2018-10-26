/*********************************
版权所有:恒生电子股份有限公司                   
项目名称:综合技术平台[Turandot+1]项目           
版    本:V1.00                      
操作系统:                             
数 据 库:INFORMIX                    
文 件 名:ICPS_WBC_TM_APP_MAIN.h      
文件描述:结构定义数据库开发嵌C头文                
项 目 组:                            
程 序 员:[fuwd22392]               
发布时间:2018-06-12 10:00:00 [Gen]    
修    订:                           
修改时间:                             
**********************************
表    名:ICPS_WBC_TM_APP_MAIN       
说    明:账户信息表-核心批量                           
**********************************
修改记录:                             
修改日期:                             
修改内容:                             
修 改 人:                            
修改内容:                             
************************************/
#ifndef __ICPS_WBC_TM_ACCOUNT_H__
#define __ICPS_WBC_TM_ACCOUNT_H__
typedef struct TDB_ICPS_WBC_TM_ACCOUNT 
{
   char     busi_date[8+1];                            /*业务日期*/
   int      file_order;                                /*文件序号*/
   char     org[12+1];                                 /*机构号                       */
   char     acct_no[20+1];                             /*账户编号                     */
   char     acct_type[1+1];                            /*账户类型                     */
   char     cust_id[20+1];                             /*客户编号                     */
   char     cust_limit_id[20+1];                       /*客户额度ID                   */
   char     product_cd[6+1];                           /*产品代码                     */
   char     default_logical_card_no[19+1];              /*默认逻辑卡号                 */
   char     curr_cd[3+1];                              /*币种                         */
   double   credit_limit;                        /*信用额度                     */
   double   temp_limit;                          /*临时额度                     */
   char     temp_limit_begin_date[8+1];                /*临时额度开始日期             */
   char     temp_limit_end_date[8+1];                  /*临时额度结束日期             */
   double   cash_limit_rt;                             /*取现额度比例                 */
   double   ovrlmt_rate;                               /*授权超限比例                 */
   double   loan_limit_rt;                             /*额度内分期额度比例           */
   double   curr_bal;                                  /*当前余额                     */
   double   cash_bal;                                  /*取现余额                     */
   double   principal_bal;                             /*本金余额                     */
   double   loan_bal;                                  /*额度内分期余额               */
   double   dispute_amt;                               /*争议金额                     */
   double   begin_bal;                                 /*期初余额                     */
   double   pmt_due_day_bal;                           /*到期还款日余额               */
   double   qual_grace_bal;                            /*全部应还款额                 */
   char     grace_days_full_ind[1+1];                  /*是否已全额还款               */
   double   point_begin_bal;                     /*期初积分余额                 */
   double   ctd_earned_points;                   /*当期新增积分                 */
   double   ctd_disb_points;                     /*当期兑换积分                 */
   double   ctd_adj_points;                      /*当期调整积分                 */
   double   point_bal;                           /*积分余额                     */
   char     setup_date[8+1];                           /*创建日期                     */
   char     dorment_date[8+1];                         /*账户睡眠日期                 */
   char     reinstate_date[8+1];                       /*账户恢复活动日期             */
   char     ovrlmt_date[8+1];                          /*超限日期                     */
   int      ovrlmt_nbr_of_cyc;                         /*连续超限账期                 */
   char     name[80+1];                                /*姓名                         */
   char     gender[1+1];                               /*性别                         */
   char     owning_branch[9+1];                        /*发卡网点                     */
   char     mobile_no[20+1];                           /*移动电话                     */
   char     corp_name[200+1];                          /*公司名称                     */
   char     billing_cycle[2+1];                        /*账单周期                     */
   char     stmt_flag[1+1];                            /*账单标志                     */
   char     stmt_mail_addr_ind[1+1];                   /*账单寄送地址标志             */
   char     stmt_media_type[1+1];                      /*账单介质类型                 */
   char     stmt_country_cd[3+1];                      /*账单地址国家代码             */
   char     stmt_state[40+1];                          /*账单地址省份                 */
   char     stmt_city[40+1];                           /*账单地址城市                 */
   char     stmt_district[40+1];                       /*账单地址行政区               */
   char     stmt_address[200+1];                       /*账单地址                     */
   char     stmt_zip[10+1];                            /*账单地址邮政编码             */
   char     email[80+1];                               /*电子邮箱                     */
   char     block_code[27+1];                          /*锁定码                       */
   char     age_cd[1+1];                               /*账龄                         */
   char     gl_age_cd[1+1];                            /*总账账龄                     */
   double   unmatch_db;                                /*未匹配借记金额               */
   double   unmatch_cash;                              /*未匹配取现金额               */
   double   unmatch_cr;                                /*未匹配贷记金额               */
   char     dd_ind[1+1];                               /*约定还款类型                 */
   char     dd_bank_name[80+1];                        /*约定还款银行名称             */
   char     dd_bank_branch[14+1];                      /*约定还款开户行号             */
   char     dd_bank_acct_no[40+1];                     /*约定还款扣款账号             */
   char     dd_bank_acct_name[80+1];                   /*约定还款扣款账户姓名         */
   double   last_dd_amt;                               /*上期约定还款金额             */
   char     last_dd_date[14+1];                        /*上期约定还款日期             */
   char     dual_billing_flag[1+1];                    /*本币溢缴款还外币指示         */
   double   last_pmt_amt;                              /*上笔还款金额                 */
   char     last_pmt_date[14+1];                       /*上个还款日期                 */
   char     last_stmt_date[14+1];                      /*上个账单日期                 */
   char     last_pmt_due_date[14+1];                   /*上个到期还款日期             */
   char     last_aging_date[14+1];                     /*上个账龄提升日期             */
   char     collect_date[14+1];                        /*入催日期                     */
   char     collect_out_date[14+1];                    /*出催收队列日期               */
   char     next_stmt_date[14+1];                      /*下个账单日期                 */
   char     pmt_due_date[14+1];                        /*到期还款日期                 */
   char     dd_date[14+1];                             /*约定还款日期                 */
   char     grace_date[14+1];                          /*宽限日期                     */
   char     dlbl_date[14+1];                           /*本币还外币日期               */
   char     closed_date[14+1];                         /*最终销户日期                 */
   char     first_stmt_date[14+1];                     /*首个账单日期                 */
   char     cancel_date[14+1];                         /*销卡销户日期                 */
   char     charge_off_date[14+1];                     /*转呆账日期                   */
   char     first_purchase_date[14+1];                 /*首次消费日期                 */
   double   first_purchase_amt;                        /*首次消费金额                 */
   double   tot_due_amt;                               /*最小还款额                   */
   double   curr_due_amt;                              /*当期最小还款额               */
   double   past_due_amt1;                             /*上个月最小还款额             */
   double   past_due_amt2;                             /*上2个月最小还款额            */
   double   past_due_amt3;                             /*上3个月最小还款额            */
   double   past_due_amt4;                             /*上4个月最小还款额            */
   double   past_due_amt5;                             /*上5个月最小还款额            */
   double   past_due_amt6;                             /*上6个月最小还款额            */
   double   past_due_amt7;                             /*上7个月最小还款额            */
   double   past_due_amt8;                             /*上8个月最小还款额            */
   double   ctd_cash_amt;                              /*当期取现金额                 */
   int      ctd_cash_cnt;                              /*当期取现笔数                 */
   double   ctd_retail_amt;                            /*当期消费金额                  */
   int      ctd_retail_cnt;                            /*当期消费笔数                  */
   double   ctd_payment_amt;                           /*当期还款金额                  */
   int      ctd_payment_cnt;                           /*当期还款笔数                  */
   double   ctd_db_adj_amt;                            /*当期借记调整金额              */
   int      ctd_db_adj_cnt;                            /*当期借记调整笔数              */
   int      ctd_cr_adj_amt;                            /*当期贷记调整金额              */
   double   ctd_cr_adj_cnt;                            /*当期贷记调整笔数              */
   double   ctd_fee_amt;                               /*当期费用金额                  */
   int      ctd_fee_cnt;                               /*当期费用笔数                  */
   double   ctd_interest_amt;                          /*当期利息金额                  */
   int      ctd_interest_cnt;                          /*当期利息笔数                  */
   double   ctd_refund_amt;                            /*当期退货金额                  */
   int      ctd_refund_cnt;                            /*当期退货笔数                  */
   double   ctd_hi_ovrlmt_amt;                         /*当期最高超限金额              */
   double   mtd_retail_amt;                            /*本月消费金额                  */
   int      mtd_retail_cnt;                            /*本月消费笔数                  */
   double   mtd_cash_amt;                              /*本月取现金额                  */
   int      mtd_cash_cnt;                              /*本月取现笔数                  */
   double   mtd_refund_amt;                            /*本月退货金额                  */
   int      mtd_refund_cnt;                            /*本月退货笔数                  */
   double   ytd_retail_amt;                            /*本年消费金额                  */
   int      ytd_retail_cnt;                            /*本年消费笔数                  */
   double   ytd_cash_amt;                              /*本年取现金额                  */
   int      ytd_cash_cnt;                              /*本年取现笔数                  */
   double   ytd_refund_amt;                            /*本年退货金额                  */
   int      ytd_refund_cnt;                            /*本年退货笔数                  */
   double   ytd_ovrlmt_fee_amt;                        /*本年超限费收取金额            */
   int      ytd_ovrlmt_fee_cnt;                        /*本年超限费收取笔数            */
   double   ytd_lpc_amt;                               /*本年滞纳金收取金额            */
   int      ytd_lpc_cnt;                               /*本年滞纳金收取笔数            */
   double   ltd_retail_amt;                            /*历史消费金额                  */
   int      ltd_retail_cnt;                            /*历史消费笔数                  */
   double   ltd_cash_amt;                              /*历史取现金额                  */
   int      ltd_cash_cnt;                              /*历史取现笔数                  */
   double   ltd_refund_amt;                            /*历史退货金额                  */
   int      ltd_refund_cnt;                            /*历史退货笔数                  */
   double   ltd_highest_principal;                     /*历史最高本金欠款              */
   double   ltd_highest_cr_bal;                        /*历史最高溢缴款                */
   double   ltd_highest_bal;                           /*历史最高余额                  */
   double   collect_times;                             /*入催次数                      */
   char     collect_colr[8+1];                         /*催收员代码                    */
   char     collect_reason[2+1];                       /*入催原因                      */
   char     age_hist[24+1];                            /*账龄历史信息                  */
   char     payment_hist[24+1];                        /*还款历史信息                  */
   char     waive_ovlfee_ind[1+1];                     /*是否免除超限费                */
   char     waive_cardfee_ind[1+1];                    /*是否免除年费                  */
   char     waive_latefee_ind[1+1];                    /*是否免除滞纳金                */
   char     waive_svcfee_ind[1+1];                     /*是否免除服务费                */
   char     user_code1[4+1];                           /*用户自定义代码1               */
   char     user_code2[4+1];                           /*用户自定义代码2               */
   char     user_code3[4+1];                           /*用户自定义代码3               */
   char     user_code4[4+1];                           /*用户自定义代码4               */
   char     user_code5[4+1];                           /*用户自定义代码5               */
   char     user_code6[4+1];                           /*用户自定义代码6               */
   char     user_date1[14+1];                          /*用户自定义日期1               */
   char     user_date2[14+1];                          /*上次调额日期                  */
   char     user_date3[14+1];                          /*用户自定义日期3               */
   char     user_date4[14+1];                          /*用户自定义日期4               */
   char     user_date5[14+1];                          /*用户自定义日期5               */
   char     user_date6[14+1];                          /*用户自定义日期6               */
   int      user_number1;                              /*用户自定义笔数1               */
   int      user_number2;                              /*用户自定义笔数2               */
   int      user_number3;                              /*用户自定义笔数3               */
   int      user_number4;                              /*用户自定义笔数4               */
   int      user_number5;                              /*用户自定义笔数5               */
   int      user_number6;                              /*用户自定义笔数6               */
   char     user_field1[40+1];                         /*用户自定义域1                 */
   char     user_field2[40+1];                         /*用户自定义域2                 */
   char     user_field3[40+1];                         /*用户自定义域3                 */
   char     user_field4[40+1];                         /*用户自定义域4                 */
   char     user_field5[40+1];                         /*用户自定义域5                 */
   char     user_field6[40+1];                         /*用户自定义域6                 */
   double   user_amt1;                                 /*用户自定义金额1               */
   double   user_amt2;                                 /*用户自定义金额2               */
   double   user_amt3;                                 /*用户自定义金额3               */
   double   user_amt4;                                 /*用户自定义金额4               */
   double   user_amt5;                                 /*用户自定义金额5               */
   double   user_amt6;                                 /*昨日贷记卡承诺余额            */
   int      jpa_version;                               /*乐观锁版本号                  */
   double   mtd_payment_amt;                           /*当月还款金额                  */
   int      mtd_payment_cnt;                           /*当月还款笔数                  */
   double   ytd_payment_amt;                           /*当年还款金额                  */
   int      ytd_payment_cnt;                           /*当年还款笔数                  */
   double   ltd_payment_amt;                           /*历史还款金额                  */
   int      ltd_payment_cnt;                           /*历史还款笔数                  */
   char     sms_ind[1+1];                              /*短信发送标识                  */
   double   user_sms_amt;                              /*个性化动账短信发送阈值        */
   int      ytd_cycle_chag_cnt;                        /*本年度账单日修改次数          */
   char     last_post_date[8+1];                       /*上个入账日期                  */
   char     last_modified_datetime[14+1];              /*修改时间                      */
   char     lock_date[8+1];                            /*自动锁定日                    */
   char     last_sync_date[8+1];                       /*上一次入账的批量日期          */
   char     created_datetime[14+1];                    /*创建时间                      */
   double   delay_bal;                                 /*账户逾期金额                  */
   char     bank_group_id[5+1];                        /*银团编号                      */
   char     customer_type[3+1];                        /*客群分类                      */
   char     is_check_flag[1+1];                        /*对账标志                      */
   char     extend_param1[100+1];                      /*扩展                          */
   char     extend_param2[250+1];                      /*                              */
   char     extend_param3[40+1];                       /*                              */
 }ICPS_WBC_TM_ACCOUNT;
 
 #define SD_DATA  ICPS_WBC_TM_ACCOUNT                                                                         
 #define SD_MEMBERS \                                         
   APP_DEFSDMEMBER(T_STRING,       busi_date              ,0),\  
   APP_DEFSDMEMBER(T_LONG,         file_order             ,0),\  
   APP_DEFSDMEMBER(T_STRING,       org                    ,0),\  
   APP_DEFSDMEMBER(T_STRING,       acct_no                ,0),\  
   APP_DEFSDMEMBER(T_STRING,       acct_type              ,0),\  
   APP_DEFSDMEMBER(T_STRING,       cust_id                ,0),\  
   APP_DEFSDMEMBER(T_STRING,       cust_limit_id          ,0),\  
   APP_DEFSDMEMBER(T_STRING,       product_cd             ,0),\  
   APP_DEFSDMEMBER(T_STRING,       default_logical_card_no ,0),\  
   APP_DEFSDMEMBER(T_STRING,       curr_cd                ,0),\  
   APP_DEFSDMEMBER(T_DOUBLE,       credit_limit           ,2),\  
   APP_DEFSDMEMBER(T_DOUBLE,       temp_limit             ,2),\  
   APP_DEFSDMEMBER(T_STRING,       temp_limit_begin_date  ,0),\  
   APP_DEFSDMEMBER(T_STRING,       temp_limit_end_date    ,0),\  
   APP_DEFSDMEMBER(T_DOUBLE,       cash_limit_rt          ,2),\  
   APP_DEFSDMEMBER(T_DOUBLE,       ovrlmt_rate            ,2),\  
   APP_DEFSDMEMBER(T_DOUBLE,       loan_limit_rt          ,2),\  
   APP_DEFSDMEMBER(T_DOUBLE,       curr_bal               ,2),\  
   APP_DEFSDMEMBER(T_DOUBLE,       cash_bal               ,2),\  
   APP_DEFSDMEMBER(T_DOUBLE,       principal_bal          ,2),\  
   APP_DEFSDMEMBER(T_DOUBLE,       loan_bal               ,2),\  
   APP_DEFSDMEMBER(T_DOUBLE,       dispute_amt            ,2),\  
   APP_DEFSDMEMBER(T_DOUBLE,       begin_bal              ,2),\  
   APP_DEFSDMEMBER(T_DOUBLE,       pmt_due_day_bal        ,2),\  
   APP_DEFSDMEMBER(T_DOUBLE,       qual_grace_bal         ,2),\  
   APP_DEFSDMEMBER(T_STRING,       grace_days_full_ind    ,0),\  
   APP_DEFSDMEMBER(T_DOUBLE,       point_begin_bal     ,2),\  
   APP_DEFSDMEMBER(T_DOUBLE,       ctd_earned_points   ,2),\  
   APP_DEFSDMEMBER(T_DOUBLE,       ctd_disb_points     ,2),\  
   APP_DEFSDMEMBER(T_DOUBLE,       ctd_adj_points      ,2),\  
   APP_DEFSDMEMBER(T_DOUBLE,       point_bal           ,2),\  
   APP_DEFSDMEMBER(T_STRING,       setup_date             ,0),\  
   APP_DEFSDMEMBER(T_STRING,       dorment_date           ,0),\  
   APP_DEFSDMEMBER(T_STRING,       reinstate_date         ,0),\  
   APP_DEFSDMEMBER(T_STRING,       ovrlmt_date            ,0),\  
   APP_DEFSDMEMBER(T_LONG,         ovrlmt_nbr_of_cyc      ,0),\  
   APP_DEFSDMEMBER(T_STRING,       name                   ,0),\  
   APP_DEFSDMEMBER(T_STRING,       gender                 ,0),\  
   APP_DEFSDMEMBER(T_STRING,       owning_branch          ,0),\  
   APP_DEFSDMEMBER(T_STRING,       mobile_no              ,0),\  
   APP_DEFSDMEMBER(T_STRING,       corp_name              ,0),\  
   APP_DEFSDMEMBER(T_STRING,       billing_cycle          ,0),\  
   APP_DEFSDMEMBER(T_STRING,       stmt_flag              ,0),\  
   APP_DEFSDMEMBER(T_STRING,       stmt_mail_addr_ind     ,0),\  
   APP_DEFSDMEMBER(T_STRING,       stmt_media_type        ,0),\  
   APP_DEFSDMEMBER(T_STRING,       stmt_country_cd        ,0),\  
   APP_DEFSDMEMBER(T_STRING,       stmt_state             ,0),\  
   APP_DEFSDMEMBER(T_STRING,       stmt_city              ,0),\  
   APP_DEFSDMEMBER(T_STRING,       stmt_district          ,0),\  
   APP_DEFSDMEMBER(T_STRING,       stmt_address           ,0),\  
   APP_DEFSDMEMBER(T_STRING,       stmt_zip               ,0),\  
   APP_DEFSDMEMBER(T_STRING,       email                  ,0),\  
   APP_DEFSDMEMBER(T_STRING,       block_code             ,0),\  
   APP_DEFSDMEMBER(T_STRING,       age_cd                 ,0),\  
   APP_DEFSDMEMBER(T_STRING,       gl_age_cd              ,0),\  
   APP_DEFSDMEMBER(T_DOUBLE,       unmatch_db             ,2),\  
   APP_DEFSDMEMBER(T_DOUBLE,       unmatch_cash           ,2),\  
   APP_DEFSDMEMBER(T_DOUBLE,       unmatch_cr             ,2),\  
   APP_DEFSDMEMBER(T_STRING,       dd_ind                 ,0),\  
   APP_DEFSDMEMBER(T_STRING,       dd_bank_name           ,0),\  
   APP_DEFSDMEMBER(T_STRING,       dd_bank_branch         ,0),\  
   APP_DEFSDMEMBER(T_STRING,       dd_bank_acct_no        ,0),\  
   APP_DEFSDMEMBER(T_STRING,       dd_bank_acct_name      ,0),\  
   APP_DEFSDMEMBER(T_DOUBLE,       last_dd_amt            ,2),\  
   APP_DEFSDMEMBER(T_STRING,       last_dd_date           ,0),\  
   APP_DEFSDMEMBER(T_STRING,       dual_billing_flag      ,0),\                              
   APP_DEFSDMEMBER(T_DOUBLE,       last_pmt_amt           ,2),\ 
   APP_DEFSDMEMBER(T_STRING,       last_pmt_date          ,0),\ 
   APP_DEFSDMEMBER(T_STRING,       last_stmt_date         ,0),\ 
   APP_DEFSDMEMBER(T_STRING,       last_pmt_due_date      ,0),\ 
   APP_DEFSDMEMBER(T_STRING,       last_aging_date        ,0),\ 
   APP_DEFSDMEMBER(T_STRING,       collect_date           ,0),\ 
   APP_DEFSDMEMBER(T_STRING,       collect_out_date       ,0),\ 
   APP_DEFSDMEMBER(T_STRING,       next_stmt_date         ,0),\ 
   APP_DEFSDMEMBER(T_STRING,       pmt_due_date           ,0),\ 
   APP_DEFSDMEMBER(T_STRING,       dd_date                ,0),\ 
   APP_DEFSDMEMBER(T_STRING,       grace_date             ,0),\ 
   APP_DEFSDMEMBER(T_STRING,       dlbl_date              ,0),\ 
   APP_DEFSDMEMBER(T_STRING,       closed_date            ,0),\ 
   APP_DEFSDMEMBER(T_STRING,       first_stmt_date        ,0),\ 
   APP_DEFSDMEMBER(T_STRING,       cancel_date            ,0),\ 
   APP_DEFSDMEMBER(T_STRING,       charge_off_date    ,0),\ 
   APP_DEFSDMEMBER(T_STRING,       first_purchase_date    ,0),\ 
   APP_DEFSDMEMBER(T_DOUBLE,       first_purchase_amt     ,2),\ 
   APP_DEFSDMEMBER(T_DOUBLE,       tot_due_amt            ,2),\ 
   APP_DEFSDMEMBER(T_DOUBLE,       curr_due_amt           ,2),\ 
   APP_DEFSDMEMBER(T_DOUBLE,       past_due_amt1          ,2),\ 
   APP_DEFSDMEMBER(T_DOUBLE,       past_due_amt2          ,2),\ 
   APP_DEFSDMEMBER(T_DOUBLE,       past_due_amt3          ,2),\ 
   APP_DEFSDMEMBER(T_DOUBLE,       past_due_amt4          ,2),\ 
   APP_DEFSDMEMBER(T_DOUBLE,       past_due_amt5          ,2),\ 
   APP_DEFSDMEMBER(T_DOUBLE,       past_due_amt6          ,2),\ 
   APP_DEFSDMEMBER(T_DOUBLE,       past_due_amt7          ,2),\ 
   APP_DEFSDMEMBER(T_DOUBLE,       past_due_amt8          ,2),\ 
   APP_DEFSDMEMBER(T_DOUBLE,       ctd_cash_amt           ,2),\ 
   APP_DEFSDMEMBER(T_LONG,         ctd_cash_cnt           ,0),\  
   APP_DEFSDMEMBER(T_DOUBLE,       ctd_retail_amt         ,2),\ 
   APP_DEFSDMEMBER(T_LONG,         ctd_retail_cnt         ,0),\  
   APP_DEFSDMEMBER(T_DOUBLE,       ctd_payment_amt        ,2),\ 
   APP_DEFSDMEMBER(T_LONG,         ctd_payment_cnt        ,0),\  
   APP_DEFSDMEMBER(T_DOUBLE,       ctd_db_adj_amt         ,2),\ 
   APP_DEFSDMEMBER(T_LONG,         ctd_db_adj_cnt         ,0),\  
   APP_DEFSDMEMBER(T_LONG,         ctd_cr_adj_amt         ,0),\  
   APP_DEFSDMEMBER(T_DOUBLE,       ctd_cr_adj_cnt         ,2),\ 
   APP_DEFSDMEMBER(T_DOUBLE,       ctd_fee_amt            ,2),\ 
   APP_DEFSDMEMBER(T_LONG,         ctd_fee_cnt            ,0),\  
   APP_DEFSDMEMBER(T_DOUBLE,       ctd_interest_amt    ,2),\    
   APP_DEFSDMEMBER(T_LONG,         ctd_interest_cnt    ,0),\     
   APP_DEFSDMEMBER(T_DOUBLE,       ctd_refund_amt         ,2),\ 
   APP_DEFSDMEMBER(T_LONG,         ctd_refund_cnt         ,0),\  
   APP_DEFSDMEMBER(T_DOUBLE,       ctd_hi_ovrlmt_amt      ,2),\ 
   APP_DEFSDMEMBER(T_DOUBLE,       mtd_retail_amt         ,2),\ 
   APP_DEFSDMEMBER(T_LONG,         mtd_retail_cnt         ,0),\  
   APP_DEFSDMEMBER(T_DOUBLE,       mtd_cash_amt           ,2),\ 
   APP_DEFSDMEMBER(T_LONG,         mtd_cash_cnt           ,0),\  
   APP_DEFSDMEMBER(T_DOUBLE,       mtd_refund_amt         ,2),\ 
   APP_DEFSDMEMBER(T_LONG,         mtd_refund_cnt         ,0),\  
   APP_DEFSDMEMBER(T_DOUBLE,       ytd_retail_amt         ,2),\ 
   APP_DEFSDMEMBER(T_LONG,         ytd_retail_cnt         ,0),\  
   APP_DEFSDMEMBER(T_DOUBLE,       ytd_cash_amt           ,2),\ 
   APP_DEFSDMEMBER(T_LONG,         ytd_cash_cnt           ,0),\  
   APP_DEFSDMEMBER(T_DOUBLE,       ytd_refund_amt         ,2),\ 
   APP_DEFSDMEMBER(T_LONG,         ytd_refund_cnt         ,0),\  
   APP_DEFSDMEMBER(T_DOUBLE,       ytd_ovrlmt_fee_amt     ,2),\ 
   APP_DEFSDMEMBER(T_LONG,         ytd_ovrlmt_fee_cnt     ,0),\  
   APP_DEFSDMEMBER(T_DOUBLE,       ytd_lpc_amt            ,2),\ 
   APP_DEFSDMEMBER(T_LONG,         ytd_lpc_cnt            ,0),\  
   APP_DEFSDMEMBER(T_DOUBLE,       ltd_retail_amt         ,2),\ 
   APP_DEFSDMEMBER(T_LONG,         ltd_retail_cnt         ,0),\  
   APP_DEFSDMEMBER(T_DOUBLE,       ltd_cash_amt           ,2),\ 
   APP_DEFSDMEMBER(T_LONG,         ltd_cash_cnt           ,0),\  
   APP_DEFSDMEMBER(T_DOUBLE,       ltd_refund_amt         ,2),\ 
   APP_DEFSDMEMBER(T_LONG,         ltd_refund_cnt         ,0),\  
   APP_DEFSDMEMBER(T_DOUBLE,       ltd_highest_principal  ,2),\ 
   APP_DEFSDMEMBER(T_DOUBLE,       ltd_highest_cr_bal     ,2),\ 
   APP_DEFSDMEMBER(T_DOUBLE,       ltd_highest_bal        ,2),\ 
   APP_DEFSDMEMBER(T_DOUBLE,       collect_times          ,2),\ 
   APP_DEFSDMEMBER(T_STRING,       collect_colr           ,0),\      
   APP_DEFSDMEMBER(T_STRING,       collect_reason         ,0),\      
   APP_DEFSDMEMBER(T_STRING,       age_hist               ,0),\      
   APP_DEFSDMEMBER(T_STRING,       payment_hist           ,0),\      
   APP_DEFSDMEMBER(T_STRING,       waive_ovlfee_ind       ,0),\      
   APP_DEFSDMEMBER(T_STRING,       waive_cardfee_ind      ,0),\      
   APP_DEFSDMEMBER(T_STRING,       waive_latefee_ind      ,0),\      
   APP_DEFSDMEMBER(T_STRING,       waive_svcfee_ind       ,0),\      
   APP_DEFSDMEMBER(T_STRING,       user_code1             ,0),\      
   APP_DEFSDMEMBER(T_STRING,       user_code2             ,0),\      
   APP_DEFSDMEMBER(T_STRING,       user_code3             ,0),\      
   APP_DEFSDMEMBER(T_STRING,       user_code4             ,0),\      
   APP_DEFSDMEMBER(T_STRING,       user_code5             ,0),\      
   APP_DEFSDMEMBER(T_STRING,       user_code6             ,0),\      
   APP_DEFSDMEMBER(T_STRING,       user_date1             ,0),\      
   APP_DEFSDMEMBER(T_STRING,       user_date2             ,0),\      
   APP_DEFSDMEMBER(T_STRING,       user_date3             ,0),\      
   APP_DEFSDMEMBER(T_STRING,       user_date4             ,0),\      
   APP_DEFSDMEMBER(T_STRING,       user_date5             ,0),\      
   APP_DEFSDMEMBER(T_STRING,       user_date6             ,0),\      
   APP_DEFSDMEMBER(T_LONG,         user_number1           ,0),\         
   APP_DEFSDMEMBER(T_LONG,         user_number2           ,0),\         
   APP_DEFSDMEMBER(T_LONG,         user_number3           ,0),\         
   APP_DEFSDMEMBER(T_LONG,         user_number4           ,0),\         
   APP_DEFSDMEMBER(T_LONG,         user_number5           ,0),\         
   APP_DEFSDMEMBER(T_LONG,         user_number6           ,0),\         
   APP_DEFSDMEMBER(T_STRING,       user_field1            ,0),\      
   APP_DEFSDMEMBER(T_STRING,       user_field2            ,0),\      
   APP_DEFSDMEMBER(T_STRING,       user_field3            ,0),\      
   APP_DEFSDMEMBER(T_STRING,       user_field4            ,0),\      
   APP_DEFSDMEMBER(T_STRING,       user_field5            ,0),\
   APP_DEFSDMEMBER(T_STRING,       user_field6            ,0),\
   APP_DEFSDMEMBER(T_DOUBLE,       user_amt1              ,2),\
   APP_DEFSDMEMBER(T_DOUBLE,       user_amt2              ,2),\
   APP_DEFSDMEMBER(T_DOUBLE,       user_amt3              ,2),\
   APP_DEFSDMEMBER(T_DOUBLE,       user_amt4              ,2),\
   APP_DEFSDMEMBER(T_DOUBLE,       user_amt5              ,2),\
   APP_DEFSDMEMBER(T_DOUBLE,       user_amt6              ,2),\
   APP_DEFSDMEMBER(T_LONG,         jpa_version            ,0),\
   APP_DEFSDMEMBER(T_DOUBLE,       mtd_payment_amt        ,2),\
   APP_DEFSDMEMBER(T_LONG,         mtd_payment_cnt        ,0),\
   APP_DEFSDMEMBER(T_DOUBLE,       ytd_payment_amt        ,2),\
   APP_DEFSDMEMBER(T_LONG,         ytd_payment_cnt        ,0),\
   APP_DEFSDMEMBER(T_DOUBLE,       ltd_payment_amt        ,2),\
   APP_DEFSDMEMBER(T_LONG,         ltd_payment_cnt        ,0),\
   APP_DEFSDMEMBER(T_STRING,       sms_ind                ,0),\
   APP_DEFSDMEMBER(T_DOUBLE,       user_sms_amt           ,2),\
   APP_DEFSDMEMBER(T_LONG,         ytd_cycle_chag_cnt     ,0),\
   APP_DEFSDMEMBER(T_STRING,       last_post_date         ,0),\
   APP_DEFSDMEMBER(T_STRING,       last_modified_datetime ,0),\
   APP_DEFSDMEMBER(T_STRING,       lock_date              ,0),\
   APP_DEFSDMEMBER(T_STRING,       last_sync_date         ,0),\
   APP_DEFSDMEMBER(T_STRING,       created_datetime       ,0),\
   APP_DEFSDMEMBER(T_DOUBLE,       delay_bal              ,2),\
   APP_DEFSDMEMBER(T_STRING,       bank_group_id          ,0),\
   APP_DEFSDMEMBER(T_STRING,       customer_type          ,0),\
   APP_DEFSDMEMBER(T_STRING,       is_check_flag          ,2),\
   APP_DEFSDMEMBER(T_STRING,       extend_param1          ,0),\
   APP_DEFSDMEMBER(T_STRING,       extend_param2          ,0),\
   APP_DEFSDMEMBER(T_STRING,       extend_param3          ,2)
   APP_DECLAREFIELDS(SD_ICPS_WBC_TM_ACCOUNT)
#undef SD_DATA
#undef SD_MEMBERS

#endif 
