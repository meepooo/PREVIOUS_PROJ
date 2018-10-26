/***********************************************************************
��Ȩ����:�������ӹɷ����޹�˾
��Ŀ����:�ۺϼ���ƽ̨(Turandot)��Ŀ
��    ��:V1.00
����ϵͳ:
�� �� ��:
�� �� ��:ICPS_WBC_TM_PLAN.h
�ļ�����:�ṹ�������ݿ⿪��ǶCͷ�ļ�
�� Ŀ ��:
�� �� Ա:[fuwd22392]
����ʱ��:2018-06-12 10:00:00 [Gen]
��    ��:
�޸�ʱ��:
************************************************************************
��    ��:ICPS_WBC_TM_PLAN
˵    ��:���üƻ���
************************************************************************
�޸ļ�¼:195
�޸�����:
�޸�����:
�� �� ��:
�޸�����:
************************************************************************/
#ifndef __ICPS_WBC_TM_PLAN_H__
#define __ICPS_WBC_TM_PLAN_H__
typedef struct TDB_ICPS_WBC_TM_PLAN
{
  char         busi_date[8+1];                               
  int          file_order;
  char         org[12+1];                                      /*������                              */
  char         plan_id[20+1];                                  /*���üƻ�ID fuwd22392 modify         */
  char         acct_no[20+1];                                  /*�˻����   fuwd22392 modify           */
  char         acct_type[1+1];                                 /*�˻�����                            */
  char         logical_card_no[19+1];                          /*�߼�����                            */
  char         plan_nbr[6+1];                                  /*���üƻ���                          */
  char         plan_type[1+1];                                 /*���üƻ�����                        */
  char         product_cd[6+1];                                /*��Ʒ����                            */
  char         ref_nbr[23+1];                                  /*���ײο���                          */
  double       curr_bal;                                       /*��ǰ���                            */
  double       begin_bal;                                      /*�ڳ����                            */
  double       dispute_amt;                                    /*������                            */
  double       tot_due_amt;                                    /*��С�����                          */
  char         plan_add_date[8+1];                             /*���üƻ���������                    */
  char         paid_out_date[8+1];                             /*��������                            */
  double       past_principal;                                 /*�ѳ��˵�����                        */
  double       past_interest;                                  /*�ѳ��˵���Ϣ                        */
  double       past_card_fee;                                  /*�ѳ��˵����                        */
  double       past_ovrlmt_fee;                                /*�ѳ��˵����޷�                      */
  double       past_lpc;                                       /*�ѳ��˵����ɽ�                      */
  double       past_nsf_fee;                                   /*�ѳ��˵��ʽ����                  */
  double       past_txn_fee;                                   /*�ѳ��˵����׷�                      */
  double       past_svc_fee;                                   /*�ѳ��˵������                      */
  double       past_ins;                                       /*�ѳ��˵����ս��                    */
  double       past_user_fee1;                                 /*�ѳ��˵��Զ������1                 */
  double       past_user_fee2;                                 /*�ѳ��˵��Զ������2                 */
  double       past_user_fee3;                                 /*�ѳ��˵��Զ������3                 */
  double       past_user_fee4;                                 /*�ѳ��˵��Զ������4                 */
  double       past_user_fee5;                                 /*�ѳ��˵��Զ������5                 */
  double       past_user_fee6;                                 /*�ѳ��˵��Զ������6                 */
  double       ctd_principal;                                  /*���ڱ���                            */
  double       ctd_interest;                                   /*������Ϣ                            */
  double       ctd_card_fee;                                   /*�������                            */
  double       ctd_ovrlmt_fee;                                 /*���ڳ��޷�                          */
  double       ctd_lpc;                                        /*�������ɽ�                          */
  double       ctd_nsf_fee;                                    /*�����ʽ����                      */
  double       ctd_svc_fee;                                    /*���ڷ����                          */
  double       ctd_txn_fee;                                    /*���ڽ��׷�                          */
  double       ctd_ins;                                        /*���ڱ��ս��                        */
  double       ctd_user_fee1;                                  /*���������Զ������1                 */
  double       ctd_user_fee2;                                  /*���������Զ������2                 */
  double       ctd_user_fee3;                                  /*���������Զ������3                 */
  double       ctd_user_fee4;                                  /*���������Զ������4                 */
  double       ctd_user_fee5;                                  /*���������Զ������5                 */
  double       ctd_user_fee6;                                  /*���������Զ������6                 */
  double       ctd_amt_db;                                     /*���ڽ�ǽ��                        */
  double       ctd_amt_cr;                                     /*���ڴ��ǽ��                        */
  int          ctd_nbr_db;                                     /*���ڽ�ǽ��ױ���                    */
  int          ctd_nbr_cr;                                     /*���ڴ��ǽ��ױ���                    */
  double       nodefbnp_int_acru;                              /*���ӳ���Ϣ                          */
  double       beg_defbnp_int_acru;                            /*�����ۻ���ʱ��Ϣ                    */
  double       ctd_defbnp_int_acru;                            /*�����ۻ���ʱ��Ϣ                    */
  char         user_code1[4+1];                                /*�û��Զ������1                     */
  char         user_code2[4+1];                                /*�û��Զ������2                     */
  char         user_code3[4+1];                                /*�û��Զ������3                     */
  char         user_code4[4+1];                                /*�û��Զ������4                     */
  char         user_code5[4+1];                                /*�û��Զ������5                     */
  char         user_code6[4+1];                                /*�û��Զ������6                     */
  int          user_number1;                                   /*�û��Զ������1                     */
  int          user_number2;                                   /*�û��Զ������2                     */
  int          user_number3;                                   /*�û��Զ������3                     */
  int          user_number4;                                   /*�û��Զ������4                     */
  int          user_number5;                                   /*�û��Զ������5                     */
  int          user_number6;                                   /*�û��Զ������6                     */
  char         user_field1[40+1];                              /*�û��Զ�����1                       */
  char         user_field2[40+1];                              /*�û��Զ�����2                       */
  char         user_field3[40+1];                              /*�û��Զ�����3                       */
  char         user_field4[40+1];                              /*�û��Զ�����4                       */
  char         user_field5[40+1];                              /*�û��Զ�����5                       */
  char         user_field6[40+1];                              /*�û��Զ�����6                       */
  char         user_date1[8+1];                                /*�û��Զ�������1                     */
  char         user_date2[8+1];                                /*�û��Զ�������2                     */
  char         user_date3[8+1];                                /*�û��Զ�������3                     */
  char         user_date4[8+1];                                /*�û��Զ�������4                     */
  char         user_date5[8+1];                                /*�û��Զ�������5                     */
  char         user_date6[8+1];                                /*�û��Զ�������6                     */
  double       user_amt1;                                      /*�û��Զ�����1                     */
  double       user_amt2;                                      /*�û��Զ�����2                     */
  double       user_amt3;                                      /*�û��Զ�����3                     */
  double       user_amt4;                                      /*�û��Զ�����4                     */
  double       user_amt5;                                      /*�û��Զ�����5                     */
  double       user_amt6;                                      /*���մ��ǿ���ŵ���                  */
  int          jpa_version;                                    /*�ֹ����汾��                        */
  double       past_penalty;                                   /*���ڷ�Ϣ                            */
  double       ctd_penalty;                                    /*���ڷ�Ϣ                            */
  double       past_compound;                                  /*���ڸ���                            */
  double       ctd_compound;                                   /*���ڸ���                            */
  double       penalty_acru;                                   /*��Ϣ�ۼ�                            */
  double       compound_acru;                                  /*�����ۼ�                            */
  double       interest_rate;                                  /*��������                            */
  double       penalty_rate;                                   /*��Ϣ����                            */
  double       compound_rate;                                  /*��������                            */
  char         use_plan_rate[1+1];                             /*�Ƿ�ʹ��plan������                  */
  char         last_pmt_date[8+1];                             /*��һ��������                        */
  int          term;                                           /*���ڷ�������                        */
  char         calc_type[1+1];                                 /*�Ʒ�����                            */
  int          calc_cycle;                                     /*�Ʒ�����                            */
  double       fee_rate;                                       /*����                                */
  char         last_fee_date[8+1];                             /*��һ�շ���                          */
  char         next_fee_date[8+1];                             /*��һ�շ���                          */
  char         txn_seq[20+1];                                        /*������ˮ��                          */
  char         first_dd_date[8+1];                             /*�״�Լ����������                    */
  char         consumer_trans_id[32+1];                        /*ҵ����ˮ��                          */
  char         sys_trans_id[32+1];                             /*ϵͳ������ˮ��                      */
  char         qchannel_id[15+1];                              /*�������                            */
  char         sub_terminal_type[15+1];                        /*�ն�����                            */
  char         sub_merch_id[40+1];                             /*�����̻�����                        */
  char         sub_merch_name[60+1];                           /*�����̻�����                        */
  char         wares_desc[60+1];                               /*��Ʒ��Ϣ                            */
  char         last_modified_datetime[14+1];                   /*�޸�ʱ��                            */
  double       original_amt;                                   /*ԭʼ���ױ���                        */
  char         interest_calc_base[1+1];                        /*��Ϣ����                            */
  char         created_datetime[14+1];                         /*����ʱ��                            */
  char         is_check_flag[1+1];
  char         extend_param1[100+1];
  char         extend_param2[250+1];
  char         extend_param3[40+1];
}ICPS_WBC_TM_PLAN;

#define SD_DATA  ICPS_WBC_TM_PLAN
#define SD_MEMBERS \ 
     APP_DEFSDMEMBER(T_STRING,             busi_date                       ,0),\
     APP_DEFSDMEMBER(T_LONG,               file_order                      ,0),\
     APP_DEFSDMEMBER(T_STRING,             org                             ,0),\
     APP_DEFSDMEMBER(T_STRING,             plan_id                         ,0),\
     APP_DEFSDMEMBER(T_STRING,             acct_no                         ,0),\
     APP_DEFSDMEMBER(T_STRING,             acct_type                       ,0),\
     APP_DEFSDMEMBER(T_STRING,             logical_card_no                 ,0),\
     APP_DEFSDMEMBER(T_STRING,             plan_nbr                        ,0),\
     APP_DEFSDMEMBER(T_STRING,             plan_type                       ,0),\
     APP_DEFSDMEMBER(T_STRING,             product_cd                      ,0),\
     APP_DEFSDMEMBER(T_STRING,             ref_nbr                         ,0),\
     APP_DEFSDMEMBER(T_DOUBLE,             curr_bal                        ,2),\
     APP_DEFSDMEMBER(T_DOUBLE,             begin_bal                       ,2),\
     APP_DEFSDMEMBER(T_DOUBLE,             dispute_amt                     ,2),\
     APP_DEFSDMEMBER(T_DOUBLE,             tot_due_amt                     ,2),\
     APP_DEFSDMEMBER(T_STRING,             plan_add_date                   ,0),\
     APP_DEFSDMEMBER(T_STRING,             paid_out_date                   ,0),\
     APP_DEFSDMEMBER(T_DOUBLE,             past_principal                  ,2),\
     APP_DEFSDMEMBER(T_DOUBLE,             past_interest                   ,2),\
     APP_DEFSDMEMBER(T_DOUBLE,             past_card_fee                   ,2),\
     APP_DEFSDMEMBER(T_DOUBLE,             past_ovrlmt_fee                 ,2),\
     APP_DEFSDMEMBER(T_DOUBLE,             past_lpc                        ,2),\
     APP_DEFSDMEMBER(T_DOUBLE,             past_nsf_fee                    ,2),\
     APP_DEFSDMEMBER(T_DOUBLE,             past_txn_fee                    ,2),\
     APP_DEFSDMEMBER(T_DOUBLE,             past_svc_fee                    ,2),\
     APP_DEFSDMEMBER(T_DOUBLE,             past_ins                        ,2),\
     APP_DEFSDMEMBER(T_DOUBLE,             past_user_fee1                  ,2),\
     APP_DEFSDMEMBER(T_DOUBLE,             past_user_fee2                  ,2),\
     APP_DEFSDMEMBER(T_DOUBLE,             past_user_fee3                  ,2),\
     APP_DEFSDMEMBER(T_DOUBLE,             past_user_fee4                  ,2),\
     APP_DEFSDMEMBER(T_DOUBLE,             past_user_fee5                  ,2),\
     APP_DEFSDMEMBER(T_DOUBLE,             past_user_fee6                  ,2),\
     APP_DEFSDMEMBER(T_DOUBLE,             ctd_principal                   ,2),\
     APP_DEFSDMEMBER(T_DOUBLE,             ctd_interest                    ,2),\
     APP_DEFSDMEMBER(T_DOUBLE,             ctd_card_fee                    ,2),\
     APP_DEFSDMEMBER(T_DOUBLE,             ctd_ovrlmt_fee                  ,2),\
     APP_DEFSDMEMBER(T_DOUBLE,             ctd_lpc                         ,2),\
     APP_DEFSDMEMBER(T_DOUBLE,             ctd_nsf_fee                     ,2),\
     APP_DEFSDMEMBER(T_DOUBLE,             ctd_svc_fee                     ,2),\
     APP_DEFSDMEMBER(T_DOUBLE,             ctd_txn_fee                     ,2),\
     APP_DEFSDMEMBER(T_DOUBLE,             ctd_ins                         ,2),\
     APP_DEFSDMEMBER(T_DOUBLE,             ctd_user_fee1                   ,2),\
     APP_DEFSDMEMBER(T_DOUBLE,             ctd_user_fee2                   ,2),\
     APP_DEFSDMEMBER(T_DOUBLE,             ctd_user_fee3                   ,2),\
     APP_DEFSDMEMBER(T_DOUBLE,             ctd_user_fee4                   ,2),\
     APP_DEFSDMEMBER(T_DOUBLE,             ctd_user_fee5                   ,2),\
     APP_DEFSDMEMBER(T_DOUBLE,             ctd_user_fee6                   ,2),\
     APP_DEFSDMEMBER(T_DOUBLE,             ctd_amt_db                      ,2),\
     APP_DEFSDMEMBER(T_DOUBLE,             ctd_amt_cr                      ,2),\
     APP_DEFSDMEMBER(T_LONG,               ctd_nbr_db                      ,0),\
     APP_DEFSDMEMBER(T_LONG,               ctd_nbr_cr                      ,0),\
     APP_DEFSDMEMBER(T_DOUBLE,             nodefbnp_int_acru               ,4),\
     APP_DEFSDMEMBER(T_DOUBLE,             beg_defbnp_int_acru             ,4),\
     APP_DEFSDMEMBER(T_DOUBLE,             ctd_defbnp_int_acru             ,4),\
     APP_DEFSDMEMBER(T_STRING,             user_code1                      ,0),\
     APP_DEFSDMEMBER(T_STRING,             user_code2                      ,0),\
     APP_DEFSDMEMBER(T_STRING,             user_code3                      ,0),\
     APP_DEFSDMEMBER(T_STRING,             user_code4                      ,0),\
     APP_DEFSDMEMBER(T_STRING,             user_code5                      ,0),\
     APP_DEFSDMEMBER(T_STRING,             user_code6                      ,0),\
     APP_DEFSDMEMBER(T_LONG,               user_number1                    ,0),\
     APP_DEFSDMEMBER(T_LONG,               user_number2                    ,0),\
     APP_DEFSDMEMBER(T_LONG,               user_number3                    ,0),\
     APP_DEFSDMEMBER(T_LONG,               user_number4                    ,0),\
     APP_DEFSDMEMBER(T_LONG,               user_number5                    ,0),\
     APP_DEFSDMEMBER(T_LONG,               user_number6                    ,0),\
     APP_DEFSDMEMBER(T_STRING,             user_field1                     ,0),\
     APP_DEFSDMEMBER(T_STRING,             user_field2                     ,0),\
     APP_DEFSDMEMBER(T_STRING,             user_field3                     ,0),\
     APP_DEFSDMEMBER(T_STRING,             user_field4                     ,0),\
     APP_DEFSDMEMBER(T_STRING,             user_field5                     ,0),\
     APP_DEFSDMEMBER(T_STRING,             user_field6                     ,0),\
     APP_DEFSDMEMBER(T_STRING,             user_date1                      ,0),\
     APP_DEFSDMEMBER(T_STRING,             user_date2                      ,0),\
     APP_DEFSDMEMBER(T_STRING,             user_date3                      ,0),\
     APP_DEFSDMEMBER(T_STRING,             user_date4                      ,0),\
     APP_DEFSDMEMBER(T_STRING,             user_date5                      ,0),\
     APP_DEFSDMEMBER(T_STRING,             user_date6                      ,0),\
     APP_DEFSDMEMBER(T_DOUBLE,             user_amt1                       ,2),\
     APP_DEFSDMEMBER(T_DOUBLE,             user_amt2                       ,2),\
     APP_DEFSDMEMBER(T_DOUBLE,             user_amt3                       ,2),\
     APP_DEFSDMEMBER(T_DOUBLE,             user_amt4                       ,2),\
     APP_DEFSDMEMBER(T_DOUBLE,             user_amt5                       ,2),\
     APP_DEFSDMEMBER(T_DOUBLE,             user_amt6                       ,0),\
     APP_DEFSDMEMBER(T_LONG,               jpa_version                     ,0),\
     APP_DEFSDMEMBER(T_DOUBLE,             past_penalty                    ,2),\
     APP_DEFSDMEMBER(T_DOUBLE,             ctd_penalty                     ,2),\
     APP_DEFSDMEMBER(T_DOUBLE,             past_compound                   ,2),\
     APP_DEFSDMEMBER(T_DOUBLE,             ctd_compound                    ,2),\
     APP_DEFSDMEMBER(T_DOUBLE,             penalty_acru                    ,2),\
     APP_DEFSDMEMBER(T_DOUBLE,             compound_acru                   ,2),\
     APP_DEFSDMEMBER(T_DOUBLE,             interest_rate                   ,4),\
     APP_DEFSDMEMBER(T_DOUBLE,             penalty_rate                    ,2),\
     APP_DEFSDMEMBER(T_DOUBLE,             compound_rate                   ,2),\
     APP_DEFSDMEMBER(T_STRING,             use_plan_rate                   ,0),\
     APP_DEFSDMEMBER(T_STRING,             last_pmt_date                   ,0),\
     APP_DEFSDMEMBER(T_LONG,               term                            ,0),\
     APP_DEFSDMEMBER(T_STRING,             calc_type                       ,0),\
     APP_DEFSDMEMBER(T_LONG,               calc_cycle                      ,0),\
     APP_DEFSDMEMBER(T_DOUBLE,             fee_rate                        ,2),\
     APP_DEFSDMEMBER(T_STRING,             last_fee_date                   ,0),\
     APP_DEFSDMEMBER(T_STRING,             next_fee_date                   ,0),\
     APP_DEFSDMEMBER(T_LONG,               txn_seq                         ,0),\
     APP_DEFSDMEMBER(T_STRING,             first_dd_date                   ,0),\
     APP_DEFSDMEMBER(T_STRING,             consumer_trans_id               ,0),\
     APP_DEFSDMEMBER(T_STRING,             sys_trans_id                    ,0),\
     APP_DEFSDMEMBER(T_STRING,             qchannel_id                     ,0),\
     APP_DEFSDMEMBER(T_STRING,             sub_terminal_type               ,0),\
     APP_DEFSDMEMBER(T_STRING,             sub_merch_id                    ,0),\
     APP_DEFSDMEMBER(T_STRING,             sub_merch_name                  ,0),\
     APP_DEFSDMEMBER(T_STRING,             wares_desc                      ,0),\
     APP_DEFSDMEMBER(T_STRING,             last_modified_datetime          ,0),\
     APP_DEFSDMEMBER(T_DOUBLE,             original_amt                    ,4),\
     APP_DEFSDMEMBER(T_STRING,             interest_calc_base              ,0),\
     APP_DEFSDMEMBER(T_STRING,             created_datetime                ,0),\
     APP_DEFSDMEMBER(T_STRING,             is_check_flag                   ,0),\
     APP_DEFSDMEMBER(T_STRING,             extend_param1                   ,0),\
     APP_DEFSDMEMBER(T_STRING,             extend_param2                   ,0),\
     APP_DEFSDMEMBER(T_STRING,             extend_param3                   ,0)
  APP_DECLAREFIELDS(SD_ICPS_WBC_TM_PLAN)
#undef SD_DATA
#undef SD_MEMBERS

#endif
