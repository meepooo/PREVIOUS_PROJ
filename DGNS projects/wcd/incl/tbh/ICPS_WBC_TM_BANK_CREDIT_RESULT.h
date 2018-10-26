/***********************************************************************
��Ȩ����:�������ӹɷ����޹�˾
��Ŀ����:�ۺϼ���ƽ̨(Turandot)��Ŀ
��    ��:V1.00
����ϵͳ:
�� �� ��:db2
�� �� ��:ICPS_WBC_TM_BANK_CREDIT_RESULT.h
�ļ�����:�ṹ�������ݿ⿪��ǶCͷ�ļ�
�� Ŀ ��:
�� �� Ա:[fuwd22392]
����ʱ��:2018-06-12 10:00:00 [Gen]
��    ��:
�޸�ʱ��:
************************************************************************
��    ��:ICPS_WBC_TM_BANK_CREDIT_RESULT
˵    ��:
************************************************************************
�޸ļ�¼:
�޸�����:
�޸�����:
�� �� ��:
�޸�����:
************************************************************************/
#ifndef __ICPS_WBC_TM_BANK_CREDIT_RESULT_H__
#define __ICPS_WBC_TM_BANK_CREDIT_RESULT_H__
typedef struct TDB_ICPS_WBC_TM_BANK_CREDIT_RESULT
{  
  char		busi_date[8+1];
  int		file_order;
  char		seq_no[32+1];                     /*������ˮ            */
  char		bank_no[20+1];                    /*���б��            */
  char		bank_name[80+1];                  /*������              */
  char		id_no[30+1];                      /*֤����              */
  char		id_type[2+1];                     /*֤������            */
  char		name[80+1];                       /*����                */
  char		nbs_order_no[32+1];               /*������              */
  char		credit_info[1024+1];              /*������Ϣ            */
  char		rule_action_type[2+1];            /*���Ź�������״̬    */
  char		rule_code[50+1];                  /*���Ź������ܾ���  */
  char		ruile_desc[500+1];                /*���������߾ܾ�����*/
  char		is_bl_rej[2+1];                   /*����������״̬      */
  char		bl_rej_code[50+1];                /*�������ܾ�����      */
  char		bl_rej_desc[500+1];               /*�������ܾ�����      */
  char		credit_datetime[14+1];            /*�����ж�ʱ��        */
  char		result_code[9+1];                 /*���߽��            */
  char		result_desc[100+1];               /*���߽������        */
  char		created_datetime[14+1];           /*����ʱ��            */
  char		last_modified_datetime[14+1];     /*����ʱ��            */
  char		is_check_flag[1+1];
  char		extend_param1[100+1];
  char		extend_param2[250+1];
  char		extend_param3[40+1];

}ICPS_WBC_TM_BANK_CREDIT_RESULT;

#define SD_DATA  ICPS_WBC_TM_BANK_CREDIT_RESULT
#define SD_MEMBERS \ 
   APP_DEFSDMEMBER(T_STRING,  busi_date               ,0),\
   APP_DEFSDMEMBER(T_LONG,    file_order              ,0),\
   APP_DEFSDMEMBER(T_STRING,  seq_no                  ,0),\
   APP_DEFSDMEMBER(T_STRING,  bank_no                 ,0),\
   APP_DEFSDMEMBER(T_STRING,  bank_name               ,0),\
   APP_DEFSDMEMBER(T_STRING,  id_no                   ,0),\
   APP_DEFSDMEMBER(T_STRING,  id_type                 ,0),\
   APP_DEFSDMEMBER(T_STRING,  name                    ,0),\
   APP_DEFSDMEMBER(T_STRING,  nbs_order_no            ,0),\
   APP_DEFSDMEMBER(T_STRING,  credit_info             ,0),\
   APP_DEFSDMEMBER(T_STRING,  rule_action_type        ,0),\
   APP_DEFSDMEMBER(T_STRING,  rule_code               ,0),\
   APP_DEFSDMEMBER(T_STRING,  ruile_desc              ,0),\
   APP_DEFSDMEMBER(T_STRING,  is_bl_rej               ,0),\
   APP_DEFSDMEMBER(T_STRING,  bl_rej_code             ,0),\
   APP_DEFSDMEMBER(T_STRING,  bl_rej_desc             ,0),\
   APP_DEFSDMEMBER(T_STRING,  credit_datetime         ,0),\
   APP_DEFSDMEMBER(T_STRING,  result_code             ,0),\
   APP_DEFSDMEMBER(T_STRING,  result_desc             ,0),\
   APP_DEFSDMEMBER(T_STRING,  created_datetime        ,0),\
   APP_DEFSDMEMBER(T_STRING,  last_modified_datetime  ,0),\
   APP_DEFSDMEMBER(T_STRING,  is_check_flag           ,0),\
   APP_DEFSDMEMBER(T_STRING,  extend_param1           ,0),\
   APP_DEFSDMEMBER(T_STRING,  extend_param2           ,0),\
   APP_DEFSDMEMBER(T_STRING,  extend_param3           ,0)
  APP_DECLAREFIELDS(SD_ICPS_WBC_TM_BANK_CREDIT_RESULT)
#undef SD_DATA
#undef SD_MEMBERS

#endif  /*end of __ICPS_WBC_TM_BANK_CREDIT_RESULT_H__*/
                                                                              
