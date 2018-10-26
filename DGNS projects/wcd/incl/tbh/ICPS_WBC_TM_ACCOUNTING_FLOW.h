 /***********************************************************************
��Ȩ����:�������ӹɷ����޹�˾
��Ŀ����:�ۺϼ���ƽ̨(Turandot)��Ŀ
��    ��:V1.00
����ϵͳ:
�� �� ��:db2
�� �� ��:ICPS_WBC_TM_ACCOUNTING_FLOW.h
�ļ�����:�ṹ�������ݿ⿪��ǶCͷ�ļ�
�� Ŀ ��:
�� �� Ա:[fuwd22392]
����ʱ��:2018-06-12 10:00:00 [Gen]
��    ��:
�޸�ʱ��:
************************************************************************
��    ��:ICPS_WBC_TM_ACCOUNTING_FLOW
˵    ��:��Ʒ�¼�ձ���
************************************************************************
�޸ļ�¼:
�޸�����:
�޸�����:
�� �� ��:
�޸�����:
************************************************************************/
#ifndef __ICPS_WBC_TM_ACCOUNTING_FLOW_H__
#define __ICPS_WBC_TM_ACCOUNTING_FLOW_H__
typedef struct TDB_ICPS_WBC_TM_ACCOUNTING_FLOW
{
 
    char            busi_date[8+1];        /*              */
    int             file_order;            /*              */
    char            org[12+1];             /*�ڲ�������    */
    char            cps_txn_seq[36+1];     /*���Ľ�����ˮ  */
    char            card_no[19+1];         /*����          */
    char            curr_cd[3+1];          /*����          */
    char            txn_code[4+1];         /*������        */
    char            txn_desc[80+1];        /*��������      */
    char            db_cr_ind[1+1];        /*������      */
    double          post_amt;              /*���˽��      */
    char            post_gl_ind[1+1];      /*���˷�ʽ      */
    char            owning_branch[9+1];    /*֧��          */
    char            subject[40+1];         /*��Ŀ          */
    char            red_flag[1+1];         /*�����ֱ�ʶ    */
    char            queue[20+1];                 /*���� fuwd22392 M        */
    char            product_cd[6+1];       /*��Ʒ��        */
    char            ref_nbr[23+1];         /*��ݺ�        */
    char            age_group[1+1];        /*������        */
    char            plan_nbr[6+1];         /*���üƻ���    */
    char            bnp_group[2+1];        /*���ɷ���    */
    char            bank_group_id[5+1];    /*���Ŵ���      */
    char            bank_no[10+1];         /*���д���      */
    int             term;                  /*����          */
    char            batchdate[14+1];        /*����          */
    char            is_check_flag[1+1];    /*              */
    char            extend_param1[100+1];  /*              */
    char            extend_param2[250+1];  /*              */
	char			extend_param3[40+1];
}ICPS_WBC_TM_ACCOUNTING_FLOW;
#define SD_DATA  ICPS_WBC_TM_ACCOUNTING_FLOW
#define SD_MEMBERS \ 
      APP_DEFSDMEMBER(T_STRING,  busi_date      ,0),\
      APP_DEFSDMEMBER(T_LONG,    file_order     ,0),\
      APP_DEFSDMEMBER(T_STRING,  org            ,0),\
      APP_DEFSDMEMBER(T_STRING,  cps_txn_seq    ,0),\
      APP_DEFSDMEMBER(T_STRING,  card_no        ,0),\
      APP_DEFSDMEMBER(T_STRING,  curr_cd        ,0),\
      APP_DEFSDMEMBER(T_STRING,  txn_code       ,0),\
      APP_DEFSDMEMBER(T_STRING,  txn_desc       ,0),\
      APP_DEFSDMEMBER(T_STRING,  db_cr_ind      ,0),\
      APP_DEFSDMEMBER(T_DOUBLE,  post_amt       ,2),\
      APP_DEFSDMEMBER(T_STRING,  post_gl_ind    ,0),\
      APP_DEFSDMEMBER(T_STRING,  owning_branch  ,0),\
      APP_DEFSDMEMBER(T_STRING,  subject        ,0),\
      APP_DEFSDMEMBER(T_STRING,  red_flag       ,0),\
      APP_DEFSDMEMBER(T_STRING,    queue          ,0),\
      APP_DEFSDMEMBER(T_STRING,  product_cd     ,0),\
      APP_DEFSDMEMBER(T_STRING,  ref_nbr        ,0),\
      APP_DEFSDMEMBER(T_STRING,  age_group      ,0),\
      APP_DEFSDMEMBER(T_STRING,  plan_nbr       ,0),\
      APP_DEFSDMEMBER(T_STRING,  bnp_group      ,0),\
      APP_DEFSDMEMBER(T_STRING,  bank_group_id  ,0),\
      APP_DEFSDMEMBER(T_STRING,  bank_no        ,0),\
      APP_DEFSDMEMBER(T_LONG,    term           ,0),\
      APP_DEFSDMEMBER(T_STRING,  batchdate      ,0),\
      APP_DEFSDMEMBER(T_STRING,  is_check_flag  ,0),\
      APP_DEFSDMEMBER(T_STRING,  extend_param1  ,0),\
      APP_DEFSDMEMBER(T_STRING,  extend_param2  ,0),\
	  APP_DEFSDMEMBER(T_STRING,  extend_param3  ,0)
      APP_DECLAREFIELDS(SD_ICPS_WBC_TM_ACCOUNTING_FLOW)   
    #undef SD_DATA                               
    #undef SD_MEMBERS                            
                                             
    #endif  /*end of __ICPS_WBC_TM_ACCOUNTING_FLOW_H__*/
