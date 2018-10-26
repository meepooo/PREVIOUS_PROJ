/***********************************************************************
��Ȩ����:�������ӹɷ����޹�˾
��Ŀ����:�ۺϼ���ƽ̨(Turandot)��Ŀ
��    ��:V1.00
����ϵͳ:
�� �� ��:INFORMIX
�� �� ��:ICPS_WBC_TM_APP_MAIN.h
�ļ�����:�ṹ�������ݿ⿪��ǶCͷ�ļ�
�� Ŀ ��:
�� �� Ա:[liaohw21982]
����ʱ��:2018-06-12 10:00:00 [Gen]
��    ��:
�޸�ʱ��:
************************************************************************
��    ��:ICPS_WBC_TM_APP_MAIN
˵    ��:
************************************************************************
�޸ļ�¼:
�޸�����:
�޸�����:
�� �� ��:
�޸�����:
************************************************************************/
#ifndef __ICPS_WBC_TM_APP_MAIN_H__
#define __ICPS_WBC_TM_APP_MAIN_H__
typedef struct TDB_ICPS_WBC_TM_APP_MAIN
{
  char     busi_date[8+1];                        /*ҵ������                       */
  int      file_order;                            /*�ļ����                       */
  char     org[12+1];                             /*������                         */
  char     app_no[20+1];                          /*��������                     */
  char     app_type[1+1];                         /*��������                       */
  double   app_lmt;                               /*������                       */
  double   sug_lmt;                               /*ϵͳ������                   */
  double   acc_lmt;                               /*��׼���                       */
  char     product_cd[6+1];                       /*����Ʒ����                     */
  double   business_limit;                        /*���񿨶��                     */
  double   micro_loan_limit;                      /*С�������                   */
  double   vehicle_loan;                          /*ר���ȳ���                   */
  double   house_loan;                            /*ר���ȷ���                   */
  double   renovation_loan;                       /*ר����װ�޴�                 */
  double   travel_loan;                           /*ר�������δ�                 */
  double   wedding_loan;                          /*ר���Ȼ����                 */
  double   durable_loan;                          /*ר����������                 */
  char     priority[1+1];                         /*�ͻ��ȼ�                       */
  char     client_type[3+1];                      /*�ͻ�����                       */
  char     approve_quick_flag[1+1];               /*����������־                   */
  char     busns_num[20+1];                       /*��˾���                       */
  char     rtf_state[3+1];                        /*����״̬                       */
  int      point_result;                          /*����ֵ                         */
  double   cust_rate_discount;                    /*�ͻ����ʸ�������               */
  char     pro_num[20+1];                         /*����ʵ����                     */
  char     pro_name[400+1];                       /*���̽ڵ�����                   */
  char     refuse_code[1000+1];                   /*�ܾ�ԭ����                     */
  int      answer_err_cnt;                        /*����ش�������               */
  char     is_clt[1+1];                           /*�Ƿ����                     */
  char     spreader_num[20+1];                    /*�ƹ��˱��                     */
  char     spreader_org[20+1];                    /*�ƹ����                       */
  char     spreader_bank[9+1];                    /*�ƹ�����������                 */
  char     spreader_way[20+1];                    /*�ƹ㷽ʽ                       */
  char     spreader_type[1+1];                    /*�ƹ�����                       */
  char     spreader_name[80+1];                   /*�ƹ�������                     */
  char     spreader_num_pre[20+1];                /*�ƹ㵥λԤ���˱��             */
  char     spreader_phone[20+1];                  /*�ƹ����ֻ�����                 */
  char     sales_ind[1+1];                        /*�Ƿ�����ƹ��ʼ�               */
  char     owning_branch[9+1];                    /*��������                       */
  char     app_promotion_cd[15+1];                /*������                         */
  char     app_source[20+1];                      /*������Դ                       */
  char     bank_customer_id[32+1];                /*���ڿͻ���                     */
  char     dd_flag[1+1];                          /*Լ���ۿ��Ƿ�ͨ��ʶ           */
  char     deduct_deal_no[40+1];                  /*�Կ�Э���                     */
  char     if_refuse[1+1];                        /*�Ƿ�ܾ�                       */
  char     if_end[1+1];                           /*�Ƿ�����ɼ�                 */
  char     apply_from_type[1+1];                  /*������Դ���                   */
  char     appno_external[20+1];                  /*������_�ⲿ����              */
  char     appno_attach_external[20+1];           /*����������_�ⲿ����          */
  char     remark[400+1];                         /*��ע                           */
  char     create_user[40+1];                     /*������                         */
  char     update_user[40+1];                     /*�޸���                         */
  char     biz_no[32+1];                          /*ҵ����ˮ��                     */
  char     trace_no[32+1];                        /*������ˮ��                   */
  char     called_no[32+1];                       /*��������ˮ��                   */
  char     result_code[10+1];                     /*���������                     */
  char     created_datetime[14+1];                /*����ʱ��                       */
  char     last_modified_datetime[14+1];          /*����޸�ʱ��                   */
  int      jpa_version;                           /*�ֹ���                         */
  char     is_shared_credit_limit[1+1];           /*�Ƿ�����                   */
  char     approval_datetime[14+1];               /*����ͨ��ʱ��                   */
  char     is_check_flag[1+1];                    /*������˱�ʶ                   */
  char     extend_param1[100+1];                  /*��չ1                          */
  char     extend_param2[250+1];                  /*��չ2                          */
  char     extend_param3[40+1];                   /*��չ3                          */

}ICPS_WBC_TM_APP_MAIN;

#define SD_DATA  ICPS_WBC_TM_APP_MAIN
#define SD_MEMBERS \ 
  APP_DEFSDMEMBER(T_STRING,       busi_date             ,0),\
  APP_DEFSDMEMBER(T_LONG,         file_order            ,0),\
  APP_DEFSDMEMBER(T_STRING,       org                   ,0),\
  APP_DEFSDMEMBER(T_STRING,       app_no                ,0),\
  APP_DEFSDMEMBER(T_STRING,       app_type              ,0),\
  APP_DEFSDMEMBER(T_DOUBLE,       app_lmt               ,2),\
  APP_DEFSDMEMBER(T_DOUBLE,       sug_lmt               ,2),\
  APP_DEFSDMEMBER(T_DOUBLE,       acc_lmt               ,2),\
  APP_DEFSDMEMBER(T_STRING,       product_cd            ,0),\
  APP_DEFSDMEMBER(T_DOUBLE,       business_limit        ,2),\
  APP_DEFSDMEMBER(T_DOUBLE,       micro_loan_limit      ,2),\
  APP_DEFSDMEMBER(T_DOUBLE,       vehicle_loan          ,2),\
  APP_DEFSDMEMBER(T_DOUBLE,       house_loan            ,2),\
  APP_DEFSDMEMBER(T_DOUBLE,       renovation_loan       ,2),\
  APP_DEFSDMEMBER(T_DOUBLE,       travel_loan           ,2),\
  APP_DEFSDMEMBER(T_DOUBLE,       wedding_loan          ,2),\
  APP_DEFSDMEMBER(T_DOUBLE,       durable_loan          ,2),\
  APP_DEFSDMEMBER(T_STRING,       priority              ,0),\
  APP_DEFSDMEMBER(T_STRING,       client_type           ,0),\
  APP_DEFSDMEMBER(T_STRING,       approve_quick_flag    ,0),\
  APP_DEFSDMEMBER(T_STRING,       busns_num             ,0),\
  APP_DEFSDMEMBER(T_STRING,       rtf_state             ,0),\
  APP_DEFSDMEMBER(T_LONG,         point_result          ,0),\
  APP_DEFSDMEMBER(T_DOUBLE,       cust_rate_discount    ,4),\
  APP_DEFSDMEMBER(T_STRING,       pro_num               ,0),\
  APP_DEFSDMEMBER(T_STRING,       pro_name              ,0),\
  APP_DEFSDMEMBER(T_STRING,       refuse_code           ,0),\
  APP_DEFSDMEMBER(T_LONG,         answer_err_cnt        ,0),\
  APP_DEFSDMEMBER(T_STRING,       is_clt                ,0),\
  APP_DEFSDMEMBER(T_STRING,       spreader_num          ,0),\
  APP_DEFSDMEMBER(T_STRING,       spreader_org          ,0),\
  APP_DEFSDMEMBER(T_STRING,       spreader_bank         ,0),\
  APP_DEFSDMEMBER(T_STRING,       spreader_way          ,0),\
  APP_DEFSDMEMBER(T_STRING,       spreader_type         ,0),\
  APP_DEFSDMEMBER(T_STRING,       spreader_name         ,0),\
  APP_DEFSDMEMBER(T_STRING,       spreader_num_pre      ,0),\
  APP_DEFSDMEMBER(T_STRING,       spreader_phone        ,0),\
  APP_DEFSDMEMBER(T_STRING,       sales_ind             ,0),\
  APP_DEFSDMEMBER(T_STRING,       owning_branch         ,0),\
  APP_DEFSDMEMBER(T_STRING,       app_promotion_cd      ,0),\
  APP_DEFSDMEMBER(T_STRING,       app_source            ,0),\
  APP_DEFSDMEMBER(T_STRING,       bank_customer_id      ,0),\
  APP_DEFSDMEMBER(T_STRING,       dd_flag               ,0),\
  APP_DEFSDMEMBER(T_STRING,       deduct_deal_no        ,0),\
  APP_DEFSDMEMBER(T_STRING,       if_refuse             ,0),\
  APP_DEFSDMEMBER(T_STRING,       if_end                ,0),\
  APP_DEFSDMEMBER(T_STRING,       apply_from_type       ,0),\
  APP_DEFSDMEMBER(T_STRING,       appno_external        ,0),\
  APP_DEFSDMEMBER(T_STRING,       appno_attach_external ,0),\
  APP_DEFSDMEMBER(T_STRING,       remark                ,0),\
  APP_DEFSDMEMBER(T_STRING,       create_user           ,0),\
  APP_DEFSDMEMBER(T_STRING,       update_user           ,0),\
  APP_DEFSDMEMBER(T_STRING,       biz_no                ,0),\
  APP_DEFSDMEMBER(T_STRING,       trace_no              ,0),\
  APP_DEFSDMEMBER(T_STRING,       called_no             ,0),\
  APP_DEFSDMEMBER(T_STRING,       result_code           ,0),\
  APP_DEFSDMEMBER(T_STRING,       created_datetime      ,0),\
  APP_DEFSDMEMBER(T_STRING,       last_modified_datetime,0),\
  APP_DEFSDMEMBER(T_LONG,         jpa_version           ,0),\
  APP_DEFSDMEMBER(T_STRING,       is_shared_credit_limit,0),\
  APP_DEFSDMEMBER(T_STRING,       approval_datetime     ,0),\
  APP_DEFSDMEMBER(T_STRING,       is_check_flag         ,0),\
  APP_DEFSDMEMBER(T_STRING,       extend_param1         ,0),\
  APP_DEFSDMEMBER(T_STRING,       extend_param2         ,0),\
  APP_DEFSDMEMBER(T_STRING,       extend_param3         ,0)

  APP_DECLAREFIELDS(SD_ICPS_WBC_TM_APP_MAIN)
#undef SD_DATA
#undef SD_MEMBERS

#endif  /*end of __ICPS_WBC_TM_APP_MAIN_H__*/
