/***********************************************************************
��Ȩ����:�������ӹɷ����޹�˾
��Ŀ����:�ۺϼ���ƽ̨(Turandot)��Ŀ
��    ��:V1.00
����ϵͳ:
�� �� ��:db2
�� �� ��:ICPS_WBC_TM_LOAN_RECEIPT_LIST.h
�ļ�����:�ṹ�������ݿ⿪��ǶCͷ�ļ�
�� Ŀ ��:
�� �� Ա:[fuwd22392]
����ʱ��:2018-06-12 10:00:00 [Gen]
��    ��:
�޸�ʱ��:
************************************************************************
��    ��:ICPS_WBC_TM_LOAN_RECEIPT_LIST
˵    ��:�������嵥��
************************************************************************
�޸ļ�¼:
�޸�����:
�޸�����:
�� �� ��:
�޸�����:
************************************************************************/
#ifndef __ICPS_WBC_TM_LOAN_RECEIPT_LIST_H__
#define __ICPS_WBC_TM_LOAN_RECEIPT_LIST_H__
typedef struct TDB_ICPS_WBC_TM_LOAN_RECEIPT_LIST
{
    char            busi_date[8+1];                      /*                                */
    int             file_order;                          /*                                */
    char            consumer_trans_id[32+1];             /*    ҵ����ˮ��                  */
    char            sys_trans_id[32+1];                  /*    ϵͳ������ˮ��              */
    char            loan_receipt_nbr[20+1];              /*    ��ݺ�                      */
    char            acct_no[20+1];                             /*    fuwd22392 modify�˻����                    */
    char            acct_type[1+1];                      /*    �˻�����                    */
    char            card_no[19+1];                       /*    ����                        */
    char            post_date[8+1];                      /*    ��������                    */
    char            last_modified_datetime[14+1];        /*    ʱ���                      */
    double          pay_amt;                             /*    ������                    */
    char            bank_group_id[5+1];                  /*    ���ű��                    */
    char            is_check_flag[1+1];                  /*                                */
    char            extend_param1[100+1];                /*                                */
    char            extend_param2[250+1];                /*                                */
    char            extend_param3[40+1];                 /*                                */
}ICPS_WBC_TM_LOAN_RECEIPT_LIST;

#define SD_DATA  ICPS_WBC_TM_LOAN_RECEIPT_LIST
#define SD_MEMBERS \ 
  APP_DEFSDMEMBER(T_STRING,  busi_date               ,0),\
  APP_DEFSDMEMBER(T_LONG,    file_order              ,0),\
  APP_DEFSDMEMBER(T_STRING,  consumer_trans_id       ,0),\
  APP_DEFSDMEMBER(T_STRING,  sys_trans_id            ,0),\
  APP_DEFSDMEMBER(T_STRING,  loan_receipt_nbr        ,0),\
  APP_DEFSDMEMBER(T_STRING,  acct_no                 ,0),\
  APP_DEFSDMEMBER(T_STRING,  acct_type               ,0),\
  APP_DEFSDMEMBER(T_STRING,  card_no                 ,0),\
  APP_DEFSDMEMBER(T_STRING,  post_date               ,0),\
  APP_DEFSDMEMBER(T_STRING,  last_modified_datetime  ,0),\
  APP_DEFSDMEMBER(T_DOUBLE,  pay_amt                 ,2),\
  APP_DEFSDMEMBER(T_STRING,  bank_group_id           ,0),\
  APP_DEFSDMEMBER(T_STRING,  is_check_flag           ,0),\
  APP_DEFSDMEMBER(T_STRING,  extend_param1           ,0),\
  APP_DEFSDMEMBER(T_STRING,  extend_param2           ,0),\
  APP_DEFSDMEMBER(T_STRING,  extend_param3           ,0)
  APP_DECLAREFIELDS(SD_ICPS_WBC_TM_LOAN_RECEIPT_LIST)
#undef SD_DATA
#undef SD_MEMBERS

#endif  /*end of __ICPS_ICPS_WBC_TM_LOAN_RECEIPT_LIST_H__*/s
