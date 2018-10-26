/*********************************
��Ȩ����:�������ӹɷ����޹�˾                   
��Ŀ����:�ۺϼ���ƽ̨[Turandot+1]��Ŀ           
��    ��:V1.00                      
����ϵͳ:                             
�� �� ��:INFORMIX                    
�� �� ��:ICPS_WBC_TM_APP_MAIN.h      
�ļ�����:�ṹ�������ݿ⿪��ǶCͷ��                
�� Ŀ ��:                            
�� �� Ա:[fuwd22392]               
����ʱ��:2018-06-12 10:00:00 [Gen]    
��    ��:                           
�޸�ʱ��:                             
**********************************
��    ��:ICPS_WBC_TM_APP_MAIN       
˵    ��:�˻���Ϣ��-��������                           
**********************************
�޸ļ�¼:                             
�޸�����:                             
�޸�����:                             
�� �� ��:                            
�޸�����:                             
************************************/
#ifndef __ICPS_WBC_TM_ACCOUNT_H__
#define __ICPS_WBC_TM_ACCOUNT_H__
typedef struct TDB_ICPS_WBC_TM_ACCOUNT 
{
   char     busi_date[8+1];                            /*ҵ������*/
   int      file_order;                                /*�ļ����*/
   char     org[12+1];                                 /*������                       */
   char     acct_no[20+1];                             /*�˻����                     */
   char     acct_type[1+1];                            /*�˻�����                     */
   char     cust_id[20+1];                             /*�ͻ����                     */
   char     cust_limit_id[20+1];                       /*�ͻ����ID                   */
   char     product_cd[6+1];                           /*��Ʒ����                     */
   char     default_logical_card_no[19+1];              /*Ĭ���߼�����                 */
   char     curr_cd[3+1];                              /*����                         */
   double   credit_limit;                        /*���ö��                     */
   double   temp_limit;                          /*��ʱ���                     */
   char     temp_limit_begin_date[8+1];                /*��ʱ��ȿ�ʼ����             */
   char     temp_limit_end_date[8+1];                  /*��ʱ��Ƚ�������             */
   double   cash_limit_rt;                             /*ȡ�ֶ�ȱ���                 */
   double   ovrlmt_rate;                               /*��Ȩ���ޱ���                 */
   double   loan_limit_rt;                             /*����ڷ��ڶ�ȱ���           */
   double   curr_bal;                                  /*��ǰ���                     */
   double   cash_bal;                                  /*ȡ�����                     */
   double   principal_bal;                             /*�������                     */
   double   loan_bal;                                  /*����ڷ������               */
   double   dispute_amt;                               /*������                     */
   double   begin_bal;                                 /*�ڳ����                     */
   double   pmt_due_day_bal;                           /*���ڻ��������               */
   double   qual_grace_bal;                            /*ȫ��Ӧ�����                 */
   char     grace_days_full_ind[1+1];                  /*�Ƿ���ȫ���               */
   double   point_begin_bal;                     /*�ڳ��������                 */
   double   ctd_earned_points;                   /*������������                 */
   double   ctd_disb_points;                     /*���ڶһ�����                 */
   double   ctd_adj_points;                      /*���ڵ�������                 */
   double   point_bal;                           /*�������                     */
   char     setup_date[8+1];                           /*��������                     */
   char     dorment_date[8+1];                         /*�˻�˯������                 */
   char     reinstate_date[8+1];                       /*�˻��ָ������             */
   char     ovrlmt_date[8+1];                          /*��������                     */
   int      ovrlmt_nbr_of_cyc;                         /*������������                 */
   char     name[80+1];                                /*����                         */
   char     gender[1+1];                               /*�Ա�                         */
   char     owning_branch[9+1];                        /*��������                     */
   char     mobile_no[20+1];                           /*�ƶ��绰                     */
   char     corp_name[200+1];                          /*��˾����                     */
   char     billing_cycle[2+1];                        /*�˵�����                     */
   char     stmt_flag[1+1];                            /*�˵���־                     */
   char     stmt_mail_addr_ind[1+1];                   /*�˵����͵�ַ��־             */
   char     stmt_media_type[1+1];                      /*�˵���������                 */
   char     stmt_country_cd[3+1];                      /*�˵���ַ���Ҵ���             */
   char     stmt_state[40+1];                          /*�˵���ַʡ��                 */
   char     stmt_city[40+1];                           /*�˵���ַ����                 */
   char     stmt_district[40+1];                       /*�˵���ַ������               */
   char     stmt_address[200+1];                       /*�˵���ַ                     */
   char     stmt_zip[10+1];                            /*�˵���ַ��������             */
   char     email[80+1];                               /*��������                     */
   char     block_code[27+1];                          /*������                       */
   char     age_cd[1+1];                               /*����                         */
   char     gl_age_cd[1+1];                            /*��������                     */
   double   unmatch_db;                                /*δƥ���ǽ��               */
   double   unmatch_cash;                              /*δƥ��ȡ�ֽ��               */
   double   unmatch_cr;                                /*δƥ����ǽ��               */
   char     dd_ind[1+1];                               /*Լ����������                 */
   char     dd_bank_name[80+1];                        /*Լ��������������             */
   char     dd_bank_branch[14+1];                      /*Լ��������к�             */
   char     dd_bank_acct_no[40+1];                     /*Լ������ۿ��˺�             */
   char     dd_bank_acct_name[80+1];                   /*Լ������ۿ��˻�����         */
   double   last_dd_amt;                               /*����Լ��������             */
   char     last_dd_date[14+1];                        /*����Լ����������             */
   char     dual_billing_flag[1+1];                    /*������ɿ���ָʾ         */
   double   last_pmt_amt;                              /*�ϱʻ�����                 */
   char     last_pmt_date[14+1];                       /*�ϸ���������                 */
   char     last_stmt_date[14+1];                      /*�ϸ��˵�����                 */
   char     last_pmt_due_date[14+1];                   /*�ϸ����ڻ�������             */
   char     last_aging_date[14+1];                     /*�ϸ�������������             */
   char     collect_date[14+1];                        /*�������                     */
   char     collect_out_date[14+1];                    /*�����ն�������               */
   char     next_stmt_date[14+1];                      /*�¸��˵�����                 */
   char     pmt_due_date[14+1];                        /*���ڻ�������                 */
   char     dd_date[14+1];                             /*Լ����������                 */
   char     grace_date[14+1];                          /*��������                     */
   char     dlbl_date[14+1];                           /*���һ��������               */
   char     closed_date[14+1];                         /*������������                 */
   char     first_stmt_date[14+1];                     /*�׸��˵�����                 */
   char     cancel_date[14+1];                         /*������������                 */
   char     charge_off_date[14+1];                     /*ת��������                   */
   char     first_purchase_date[14+1];                 /*�״���������                 */
   double   first_purchase_amt;                        /*�״����ѽ��                 */
   double   tot_due_amt;                               /*��С�����                   */
   double   curr_due_amt;                              /*������С�����               */
   double   past_due_amt1;                             /*�ϸ�����С�����             */
   double   past_due_amt2;                             /*��2������С�����            */
   double   past_due_amt3;                             /*��3������С�����            */
   double   past_due_amt4;                             /*��4������С�����            */
   double   past_due_amt5;                             /*��5������С�����            */
   double   past_due_amt6;                             /*��6������С�����            */
   double   past_due_amt7;                             /*��7������С�����            */
   double   past_due_amt8;                             /*��8������С�����            */
   double   ctd_cash_amt;                              /*����ȡ�ֽ��                 */
   int      ctd_cash_cnt;                              /*����ȡ�ֱ���                 */
   double   ctd_retail_amt;                            /*�������ѽ��                  */
   int      ctd_retail_cnt;                            /*�������ѱ���                  */
   double   ctd_payment_amt;                           /*���ڻ�����                  */
   int      ctd_payment_cnt;                           /*���ڻ������                  */
   double   ctd_db_adj_amt;                            /*���ڽ�ǵ������              */
   int      ctd_db_adj_cnt;                            /*���ڽ�ǵ�������              */
   int      ctd_cr_adj_amt;                            /*���ڴ��ǵ������              */
   double   ctd_cr_adj_cnt;                            /*���ڴ��ǵ�������              */
   double   ctd_fee_amt;                               /*���ڷ��ý��                  */
   int      ctd_fee_cnt;                               /*���ڷ��ñ���                  */
   double   ctd_interest_amt;                          /*������Ϣ���                  */
   int      ctd_interest_cnt;                          /*������Ϣ����                  */
   double   ctd_refund_amt;                            /*�����˻����                  */
   int      ctd_refund_cnt;                            /*�����˻�����                  */
   double   ctd_hi_ovrlmt_amt;                         /*������߳��޽��              */
   double   mtd_retail_amt;                            /*�������ѽ��                  */
   int      mtd_retail_cnt;                            /*�������ѱ���                  */
   double   mtd_cash_amt;                              /*����ȡ�ֽ��                  */
   int      mtd_cash_cnt;                              /*����ȡ�ֱ���                  */
   double   mtd_refund_amt;                            /*�����˻����                  */
   int      mtd_refund_cnt;                            /*�����˻�����                  */
   double   ytd_retail_amt;                            /*�������ѽ��                  */
   int      ytd_retail_cnt;                            /*�������ѱ���                  */
   double   ytd_cash_amt;                              /*����ȡ�ֽ��                  */
   int      ytd_cash_cnt;                              /*����ȡ�ֱ���                  */
   double   ytd_refund_amt;                            /*�����˻����                  */
   int      ytd_refund_cnt;                            /*�����˻�����                  */
   double   ytd_ovrlmt_fee_amt;                        /*���곬�޷���ȡ���            */
   int      ytd_ovrlmt_fee_cnt;                        /*���곬�޷���ȡ����            */
   double   ytd_lpc_amt;                               /*�������ɽ���ȡ���            */
   int      ytd_lpc_cnt;                               /*�������ɽ���ȡ����            */
   double   ltd_retail_amt;                            /*��ʷ���ѽ��                  */
   int      ltd_retail_cnt;                            /*��ʷ���ѱ���                  */
   double   ltd_cash_amt;                              /*��ʷȡ�ֽ��                  */
   int      ltd_cash_cnt;                              /*��ʷȡ�ֱ���                  */
   double   ltd_refund_amt;                            /*��ʷ�˻����                  */
   int      ltd_refund_cnt;                            /*��ʷ�˻�����                  */
   double   ltd_highest_principal;                     /*��ʷ��߱���Ƿ��              */
   double   ltd_highest_cr_bal;                        /*��ʷ�����ɿ�                */
   double   ltd_highest_bal;                           /*��ʷ������                  */
   double   collect_times;                             /*��ߴ���                      */
   char     collect_colr[8+1];                         /*����Ա����                    */
   char     collect_reason[2+1];                       /*���ԭ��                      */
   char     age_hist[24+1];                            /*������ʷ��Ϣ                  */
   char     payment_hist[24+1];                        /*������ʷ��Ϣ                  */
   char     waive_ovlfee_ind[1+1];                     /*�Ƿ�������޷�                */
   char     waive_cardfee_ind[1+1];                    /*�Ƿ�������                  */
   char     waive_latefee_ind[1+1];                    /*�Ƿ�������ɽ�                */
   char     waive_svcfee_ind[1+1];                     /*�Ƿ���������                */
   char     user_code1[4+1];                           /*�û��Զ������1               */
   char     user_code2[4+1];                           /*�û��Զ������2               */
   char     user_code3[4+1];                           /*�û��Զ������3               */
   char     user_code4[4+1];                           /*�û��Զ������4               */
   char     user_code5[4+1];                           /*�û��Զ������5               */
   char     user_code6[4+1];                           /*�û��Զ������6               */
   char     user_date1[14+1];                          /*�û��Զ�������1               */
   char     user_date2[14+1];                          /*�ϴε�������                  */
   char     user_date3[14+1];                          /*�û��Զ�������3               */
   char     user_date4[14+1];                          /*�û��Զ�������4               */
   char     user_date5[14+1];                          /*�û��Զ�������5               */
   char     user_date6[14+1];                          /*�û��Զ�������6               */
   int      user_number1;                              /*�û��Զ������1               */
   int      user_number2;                              /*�û��Զ������2               */
   int      user_number3;                              /*�û��Զ������3               */
   int      user_number4;                              /*�û��Զ������4               */
   int      user_number5;                              /*�û��Զ������5               */
   int      user_number6;                              /*�û��Զ������6               */
   char     user_field1[40+1];                         /*�û��Զ�����1                 */
   char     user_field2[40+1];                         /*�û��Զ�����2                 */
   char     user_field3[40+1];                         /*�û��Զ�����3                 */
   char     user_field4[40+1];                         /*�û��Զ�����4                 */
   char     user_field5[40+1];                         /*�û��Զ�����5                 */
   char     user_field6[40+1];                         /*�û��Զ�����6                 */
   double   user_amt1;                                 /*�û��Զ�����1               */
   double   user_amt2;                                 /*�û��Զ�����2               */
   double   user_amt3;                                 /*�û��Զ�����3               */
   double   user_amt4;                                 /*�û��Զ�����4               */
   double   user_amt5;                                 /*�û��Զ�����5               */
   double   user_amt6;                                 /*���մ��ǿ���ŵ���            */
   int      jpa_version;                               /*�ֹ����汾��                  */
   double   mtd_payment_amt;                           /*���»�����                  */
   int      mtd_payment_cnt;                           /*���»������                  */
   double   ytd_payment_amt;                           /*���껹����                  */
   int      ytd_payment_cnt;                           /*���껹�����                  */
   double   ltd_payment_amt;                           /*��ʷ������                  */
   int      ltd_payment_cnt;                           /*��ʷ�������                  */
   char     sms_ind[1+1];                              /*���ŷ��ͱ�ʶ                  */
   double   user_sms_amt;                              /*���Ի����˶��ŷ�����ֵ        */
   int      ytd_cycle_chag_cnt;                        /*������˵����޸Ĵ���          */
   char     last_post_date[8+1];                       /*�ϸ���������                  */
   char     last_modified_datetime[14+1];              /*�޸�ʱ��                      */
   char     lock_date[8+1];                            /*�Զ�������                    */
   char     last_sync_date[8+1];                       /*��һ�����˵���������          */
   char     created_datetime[14+1];                    /*����ʱ��                      */
   double   delay_bal;                                 /*�˻����ڽ��                  */
   char     bank_group_id[5+1];                        /*���ű��                      */
   char     customer_type[3+1];                        /*��Ⱥ����                      */
   char     is_check_flag[1+1];                        /*���˱�־                      */
   char     extend_param1[100+1];                      /*��չ                          */
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
