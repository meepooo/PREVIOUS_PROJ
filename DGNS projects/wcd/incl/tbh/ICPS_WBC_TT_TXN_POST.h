/***********************************************************************
��Ȩ����:�������ӹɷ����޹�˾
��Ŀ����:�ۺϼ���ƽ̨(Turandot)��Ŀ
��    ��:V1.00
����ϵͳ:
�� �� ��:
�� �� ��:ICPS_WBC_TT_TXN_POST.h
�ļ�����:�ṹ�������ݿ⿪��ǶCͷ�ļ�
�� Ŀ ��:
�� �� Ա:[fuwd22392]
����ʱ��:2018-06-12 10:00:00 [Gen]
��    ��:
�޸�ʱ��:
************************************************************************
��    ��:ICPS_WBC_TT_TXN_POST
˵    ��:�������˽��ױ�
************************************************************************
�޸ļ�¼:195
�޸�����:
�޸�����:
�� �� ��:
�޸�����:
************************************************************************/

#ifndef __ICPS_WBC_TT_TXN_POST_H__
#define __ICPS_WBC_TT_TXN_POST_H__
typedef struct TDB_ICPS_WBC_TT_TXN_POST
{
   char			busi_date[8+1];                   
   int			file_order;
   char			org[12+1];                              /*������                       */
   char			txn_seq[20+1];                          /*������ˮ��fuwd22392 modify           */
   char			acct_no[20+1];	                        /*�˻����   fuwd22392 modify          */
   char 		acct_type[1+1];	                       /*�˻�����                     */
   char 		card_no[19+1];	                         /*����                         */
   char 		logical_card_no[19+1];	                 /*�߼�����                     */
   char 		bsc_logiccard_no[19+1];	               /*�߼�����������               */
   char 		product_cd[6+1];	                       /*��Ʒ����                     */
   char 		txn_date[8+1];	                         /*��������                     */
   char 		txn_time[14+1];	                       /*����ʱ��                     */
   char 		post_txn_type[1+1];	                   /*���˽�������                 */
   char 		txn_code[4+1];	                         /*������                       */
   char 		db_cr_ind[1+1];	                       /*�����־                     */
   double		txn_amt;                                /*���׽��                     */
   double		post_amt;                               /*���˱��ֽ��                 */
   char			post_date[8+1];	                       /*��������                     */
   char			auth_code[6+1];	                       /*��Ȩ��                       */
   char			card_block_code[27+1];                  /*��Ƭ������                   */
   char			txn_curr_cd[3+1];	                     /*���ױ��ִ���                 */
   char			post_curr_cd[3+1];	                     /*���˱��ִ���                 */
   char			orig_trans_date[8+1];	                 /*ԭʼ��������                 */
   char			plan_nbr[6+1];	                         /*���üƻ���                   */
   char			ref_nbr[23+1];                          /*���ײο���                   */
   char			txn_desc[80+1];                         /*��������                     */
   char			txn_short_desc[80+1];                   /*�˵���������                 */
   double      	point;                                  /*������ֵ                     */
   char			posting_flag[3+1];                      /*���˽����ʾ��               */
   char			pre_posting_flag[3+1];                  /*�������˽����ʾ��           */
   double	    rel_pmt_amt;                            /*��˾��������               */
   double	    orig_pmt_amt;                           /*�����ԭʼ���             */
   char			acq_branch_id[9+1];	                   /*������д���                 */
   char			acq_terminal_id[8+1];	                 /*��������ն˱�ʶ��           */
   char			acq_acceptor_id[15+1];	                 /*�ܿ�����ʶ��                 */
   char			acq_name_addr[40+1];	                   /*����������Ƶ�ַ             */
   char			mcc[4+1];	                             /*�̻�������                 */
   char			input_txn_code[4+1];	                   /*ԭ���׽�����                 */
   double		input_txn_amt;                          /*ԭ���׽��׽��               */
   double		input_sett_amt;                         /*ԭ����������               */
   double		interchange_fee;                        /*ԭ���׻���ת����             */
   double		fee_payout;                              /*������Ӧ��������             */
   double		fee_profit;                              /*������Ӧ��������             */
   double		loan_issue_profit;                       /*���ڽ��׷���������           */
   char			stmt_date[8+1];	                       /*�˵�����                     */
   char			voucher_no[7+1];	                       /*���۵�ƾ֤��                 */
   int			jpa_version;                            /*�ֹ����汾��                 */
   int			term;                                   /*���ڷ�������                 */
   char         consumer_trans_id[32+1];	               /*ҵ����ˮ��                   */
   char         sys_trans_id[32+1];	                   /*ϵͳ������ˮ��               */
   char         qchannel_id[15+1];	                     /*�������                     */
   char         sub_terminal_type[15+1];	               /*�ն�����                     */
   char         sub_merch_id[40+1];	                   /*�����̻�����                 */
   char         sub_merch_name[60+1];	                 /*�����̻�����                 */
   char         wares_desc[60+1];	                     /*��Ʒ��Ϣ                     */
   char         last_modified_datetime[14+1];	         /*�޸�ʱ��                     */
   char         paid_stmt_date[8+1];	                   /*�����˵���                   */
   double		repay_amt;                              /*Ӧ�����                     */
   char			counter_acct[32+1];	                   /*���ַ��˻�                   */
   char			counter_name[120+1];                    /*���ַ�����                   */
   char			counter_brno[14+1];	                   /*���ַ��к�                   */
   char			counter_brname[180+1];                  /*���ַ�����                   */
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
